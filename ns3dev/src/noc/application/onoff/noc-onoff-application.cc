/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
//
// Copyright (c) 2006 Georgia Tech Research Corporation
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License version 2 as
// published by the Free Software Foundation;
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// Author: George F. Riley<riley@ece.gatech.edu>
//

// ns3 - On/Off Data Source Application class
// George F. Riley, Georgia Tech, Spring 2007
// Adapted from ApplicationOnOff in GTNetS.
// Adapted from OnOffApplication by Ciprian Radu.

#include "noc-onoff-application.h"
#include "ns3/log.h"
#include "ns3/address.h"
#include "ns3/node.h"
#include "ns3/nstime.h"
#include "ns3/data-rate.h"
#include "ns3/random-variable.h"
#include "ns3/socket.h"
#include "ns3/simulator.h"
#include "ns3/socket-factory.h"
#include "ns3/noc-packet.h"
#include "ns3/uinteger.h"
#include "ns3/trace-source-accessor.h"
#include "ns3/onoff-application.h"
#include "ns3/udp-socket-factory.h"

NS_LOG_COMPONENT_DEFINE ("NocOnOffApplication");

using namespace std;

namespace ns3 {

NS_OBJECT_ENSURE_REGISTERED (NocOnOffApplication);

TypeId
NocOnOffApplication::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::NocOnOffApplication")
    .SetParent<Application> ()
    .AddConstructor<NocOnOffApplication> ()
    .AddAttribute ("DataRate", "The data rate in on state.",
                   DataRateValue (DataRate ("500kb/s")),
                   MakeDataRateAccessor (&NocOnOffApplication::m_cbrRate),
                   MakeDataRateChecker ())
    .AddAttribute ("PacketSize", "The size of packets sent in on state",
                   UintegerValue (512),
                   MakeUintegerAccessor (&NocOnOffApplication::m_pktSize),
                   MakeUintegerChecker<uint32_t> (1))
    .AddAttribute ("Remote", "The address of the destination",
                   AddressValue (),
                   MakeAddressAccessor (&NocOnOffApplication::m_peer),
                   MakeAddressChecker ())
    .AddAttribute ("OnTime", "A RandomVariable used to pick the duration of the 'On' state.",
                   RandomVariableValue (ConstantVariable (1.0)),
                   MakeRandomVariableAccessor (&NocOnOffApplication::m_onTime),
                   MakeRandomVariableChecker ())
    .AddAttribute ("OffTime", "A RandomVariable used to pick the duration of the 'Off' state.",
                   RandomVariableValue (ConstantVariable (1.0)),
                   MakeRandomVariableAccessor (&NocOnOffApplication::m_offTime),
                   MakeRandomVariableChecker ())
    .AddAttribute ("MaxBytes", 
                   "The total number of bytes to send. Once these bytes are sent, "
                   "no packet is sent again, even in on state. The value zero means "
                   "that there is no limit.",
                   UintegerValue (0),
                   MakeUintegerAccessor (&NocOnOffApplication::m_maxBytes),
                   MakeUintegerChecker<uint32_t> ())
    .AddAttribute ("Protocol", "The type of protocol to use.",
                   TypeIdValue (UdpSocketFactory::GetTypeId ()),
                   MakeTypeIdAccessor (&NocOnOffApplication::m_tid),
                   MakeTypeIdChecker ())
    .AddTraceSource ("Tx", "A new packet is created and is sent",
                     MakeTraceSourceAccessor (&NocOnOffApplication::m_txTrace))
    ;
  return tid;
}


NocOnOffApplication::NocOnOffApplication ()
{
  NS_LOG_FUNCTION_NOARGS ();
  m_socket = 0;
  m_connected = false;
  m_residualBits = 0;
  m_lastStartTime = Seconds (0);
  m_totBytes = 0;
}

NocOnOffApplication::~NocOnOffApplication()
{
  NS_LOG_FUNCTION_NOARGS ();
}

void 
NocOnOffApplication::SetMaxBytes(uint32_t maxBytes)
{
  NS_LOG_FUNCTION (this << maxBytes);
  m_maxBytes = maxBytes;
}


void
NocOnOffApplication::DoDispose (void)
{
  NS_LOG_FUNCTION_NOARGS ();

  m_socket = 0;
  // chain up
  Application::DoDispose ();
}

// Application Methods
void NocOnOffApplication::StartApplication() // Called at time specified by Start
{
  NS_LOG_FUNCTION_NOARGS ();

  // Create the socket if not already
  if (!m_socket)
    {
      m_socket = Socket::CreateSocket (GetNode(), m_tid);
      m_socket->Bind ();
      m_socket->Connect (m_peer);
    }
  // Insure no pending event
  CancelEvents ();
  // If we are not yet connected, there is nothing to do here
  // The ConnectionComplete upcall will start timers at that time
  //if (!m_connected) return;
  ScheduleStartEvent();
}

void NocOnOffApplication::StopApplication() // Called at time specified by Stop
{
  NS_LOG_FUNCTION_NOARGS ();

  CancelEvents ();
  if(m_socket != 0)
    {
      m_socket->Close ();
    }
  else
    {
      NS_LOG_WARN("NocOnOffApplication found null socket to close in StopApplication");
    }
}

void NocOnOffApplication::CancelEvents ()
{
  NS_LOG_FUNCTION_NOARGS ();

  if (m_sendEvent.IsRunning ())
    { // Cancel the pending send packet event
      // Calculate residual bits since last packet sent
      Time delta(Simulator::Now() - m_lastStartTime);
      Scalar bits = delta * Scalar (m_cbrRate.GetBitRate ()) / Seconds (1.0);
      m_residualBits += (uint32_t)bits.GetDouble ();
    }
  Simulator::Cancel(m_sendEvent);
  Simulator::Cancel(m_startStopEvent);
}

// Event handlers
void NocOnOffApplication::StartSending()
{
  NS_LOG_FUNCTION_NOARGS ();
  m_lastStartTime = Simulator::Now();
  ScheduleNextTx();  // Schedule the send packet event
  ScheduleStopEvent();
}

void NocOnOffApplication::StopSending()
{
  NS_LOG_FUNCTION_NOARGS ();
  CancelEvents();

  ScheduleStartEvent();
}

// Private helpers
void NocOnOffApplication::ScheduleNextTx()
{
  NS_LOG_FUNCTION_NOARGS ();

  if (m_maxBytes == 0 || m_totBytes < m_maxBytes)
    {
      uint32_t bits = m_pktSize * 8 - m_residualBits;
      NS_LOG_LOGIC ("bits = " << bits);
      Time nextTime(Seconds (bits / 
        static_cast<double>(m_cbrRate.GetBitRate()))); // Time till next packet
      NS_LOG_LOGIC ("nextTime = " << nextTime);
      m_sendEvent = Simulator::Schedule(nextTime, 
                                        &NocOnOffApplication::SendPacket, this);
    }
  else
    { // All done, cancel any pending events
      StopApplication();
    }
}

void NocOnOffApplication::ScheduleStartEvent()
{  // Schedules the event to start sending data (switch to the "On" state)
  NS_LOG_FUNCTION_NOARGS ();

  Time offInterval = Seconds(m_offTime.GetValue());
  NS_LOG_LOGIC ("start at " << offInterval);
  m_startStopEvent = Simulator::Schedule(offInterval, &NocOnOffApplication::StartSending, this);
}

void NocOnOffApplication::ScheduleStopEvent()
{  // Schedules the event to stop sending data (switch to "Off" state)
  NS_LOG_FUNCTION_NOARGS ();

  Time onInterval = Seconds(m_onTime.GetValue());
  NS_LOG_LOGIC ("stop at " << onInterval);
  m_startStopEvent = Simulator::Schedule(onInterval, &NocOnOffApplication::StopSending, this);
}

  
void NocOnOffApplication::SendPacket()
{
  NS_LOG_FUNCTION_NOARGS ();
  NS_LOG_LOGIC ("sending packet at " << Simulator::Now());
  NS_ASSERT (m_sendEvent.IsExpired ());
  // FIXME how deal with source and destination address?
  Ptr<NocPacket> packet = Create<NocPacket> (2, 3, 3, 4, 1, m_pktSize);
  m_txTrace (packet);
  m_socket->Send (packet);
  m_totBytes += m_pktSize;
  m_lastStartTime = Simulator::Now();
  m_residualBits = 0;
  ScheduleNextTx();
}

void NocOnOffApplication::ConnectionSucceeded(Ptr<Socket>)
{
  NS_LOG_FUNCTION_NOARGS ();

  m_connected = true;
  ScheduleStartEvent();
}
  
void NocOnOffApplication::ConnectionFailed(Ptr<Socket>)
{
  NS_LOG_FUNCTION_NOARGS ();
  cout << "OnOffApplication, Connection Failed" << endl;
}

} // Namespace ns3
