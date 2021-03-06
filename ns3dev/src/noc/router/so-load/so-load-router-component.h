/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2009 Systems and Networking, University of Augsburg, Germany
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: Ciprian Radu <radu@informatik.uni-augsburg.de>
 */

#ifndef SOLOADROUTERCOMPONENT_H_
#define SOLOADROUTERCOMPONENT_H_

#include "ns3/load-router-component.h"

namespace ns3
{

  /**
   *
   * \brief Self optimized algorithm used to provide information about the load of a router
   *
   */
  class SoLoadRouterComponent : public LoadRouterComponent
  {
  public:

    static TypeId
    GetTypeId ();

    SoLoadRouterComponent ();

    virtual
    ~SoLoadRouterComponent ();

    /**
     * \param packet the current packet
     * \param sourceDevice the net device where the packet currently is in the router
     *
     * \return the load of the router
     */
    int
    GetLocalLoad (Ptr<Packet> packet, Ptr<NocNetDevice> sourceDevice);

    /**
     * Computes the load that is propagated from this router, in the specified direction.
     *
     * \param packet the current packet
     * \param sourceDevice the net device where the packet currently is in the router
     * \param selectedDevice the net device chosen for routing the packet forward
     *
     * \return the load for the specified direction
     */
    int
    GetLoadForDirection (Ptr<Packet> packet, Ptr<NocNetDevice> sourceDevice, Ptr<NocNetDevice> selectedDevice);

  protected:

  private:

  };

} // namespace ns3

#endif /* SOLOADROUTERCOMPONENT_H_ */
