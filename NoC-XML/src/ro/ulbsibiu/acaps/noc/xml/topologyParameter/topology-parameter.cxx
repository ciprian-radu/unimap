// Copyright (C) 2005-2010 Code Synthesis Tools CC
//
// This program was generated by CodeSynthesis XSD, an XML Schema to
// C++ data binding compiler.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License version 2 as
// published by the Free Software Foundation.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
//
// In addition, as a special exception, Code Synthesis Tools CC gives
// permission to link this program with the Xerces-C++ library (or with
// modified versions of Xerces-C++ that use the same license as Xerces-C++),
// and distribute linked combinations including the two. You must obey
// the GNU General Public License version 2 in all respects for all of
// the code used other than Xerces-C++. If you modify this copy of the
// program, you may extend this exception to your version of the program,
// but you are not obligated to do so. If you do not wish to do so, delete
// this exception statement from your version.
//
// Furthermore, Code Synthesis Tools CC makes a special exception for
// the Free/Libre and Open Source Software (FLOSS) which is described
// in the accompanying FLOSSE file.
//

// Begin prologue.
//
//
// End prologue.

#include <xsd/cxx/pre.hxx>

#include "topology-parameter.hxx"

namespace research
{
  namespace noc
  {
    namespace application_mapping
    {
      namespace unified_framework
      {
        namespace schema
        {
          namespace topologyParameter
          {
            // topologyType
            // 

            const topologyType::topologyParameter_sequence& topologyType::
            topologyParameter () const
            {
              return this->topologyParameter_;
            }

            topologyType::topologyParameter_sequence& topologyType::
            topologyParameter ()
            {
              return this->topologyParameter_;
            }

            void topologyType::
            topologyParameter (const topologyParameter_sequence& s)
            {
              this->topologyParameter_ = s;
            }

            const topologyType::id_type& topologyType::
            id () const
            {
              return this->id_.get ();
            }

            topologyType::id_type& topologyType::
            id ()
            {
              return this->id_.get ();
            }

            void topologyType::
            id (const id_type& x)
            {
              this->id_.set (x);
            }

            void topologyType::
            id (::std::auto_ptr< id_type > x)
            {
              this->id_.set (x);
            }

            const topologyType::name_type& topologyType::
            name () const
            {
              return this->name_.get ();
            }

            topologyType::name_type& topologyType::
            name ()
            {
              return this->name_.get ();
            }

            void topologyType::
            name (const name_type& x)
            {
              this->name_.set (x);
            }

            void topologyType::
            name (::std::auto_ptr< name_type > x)
            {
              this->name_.set (x);
            }


            // topologyParameterType
            // 

            const topologyParameterType::type_type& topologyParameterType::
            type () const
            {
              return this->type_.get ();
            }

            topologyParameterType::type_type& topologyParameterType::
            type ()
            {
              return this->type_.get ();
            }

            void topologyParameterType::
            type (const type_type& x)
            {
              this->type_.set (x);
            }

            void topologyParameterType::
            type (::std::auto_ptr< type_type > x)
            {
              this->type_.set (x);
            }
          }
        }
      }
    }
  }
}

#include <xsd/cxx/xml/dom/parsing-source.hxx>

namespace research
{
  namespace noc
  {
    namespace application_mapping
    {
      namespace unified_framework
      {
        namespace schema
        {
          namespace topologyParameter
          {
            // topologyType
            //

            topologyType::
            topologyType (const id_type& id,
                          const name_type& name)
            : ::xml_schema::type (),
              topologyParameter_ (::xml_schema::flags (), this),
              id_ (id, ::xml_schema::flags (), this),
              name_ (name, ::xml_schema::flags (), this)
            {
            }

            topologyType::
            topologyType (const topologyType& x,
                          ::xml_schema::flags f,
                          ::xml_schema::container* c)
            : ::xml_schema::type (x, f, c),
              topologyParameter_ (x.topologyParameter_, f, this),
              id_ (x.id_, f, this),
              name_ (x.name_, f, this)
            {
            }

            topologyType::
            topologyType (const ::xercesc::DOMElement& e,
                          ::xml_schema::flags f,
                          ::xml_schema::container* c)
            : ::xml_schema::type (e, f | ::xml_schema::flags::base, c),
              topologyParameter_ (f, this),
              id_ (f, this),
              name_ (f, this)
            {
              if ((f & ::xml_schema::flags::base) == 0)
              {
                ::xsd::cxx::xml::dom::parser< char > p (e, true, true);
                this->parse (p, f);
              }
            }

            void topologyType::
            parse (::xsd::cxx::xml::dom::parser< char >& p,
                   ::xml_schema::flags f)
            {
              for (; p.more_elements (); p.next_element ())
              {
                const ::xercesc::DOMElement& i (p.cur_element ());
                const ::xsd::cxx::xml::qualified_name< char > n (
                  ::xsd::cxx::xml::dom::name< char > (i));

                // topologyParameter
                //
                if (n.name () == "topologyParameter" && n.namespace_ () == "http://webspace.ulbsibiu.ro/ciprian.radu/research/noc/application_mapping/unified_framework/schema/topologyParameter")
                {
                  ::std::auto_ptr< topologyParameter_type > r (
                    topologyParameter_traits::create (i, f, this));

                  this->topologyParameter_.push_back (r);
                  continue;
                }

                break;
              }

              while (p.more_attributes ())
              {
                const ::xercesc::DOMAttr& i (p.next_attribute ());
                const ::xsd::cxx::xml::qualified_name< char > n (
                  ::xsd::cxx::xml::dom::name< char > (i));

                if (n.name () == "id" && n.namespace_ ().empty ())
                {
                  ::std::auto_ptr< id_type > r (
                    id_traits::create (i, f, this));

                  this->id_.set (r);
                  continue;
                }

                if (n.name () == "name" && n.namespace_ ().empty ())
                {
                  ::std::auto_ptr< name_type > r (
                    name_traits::create (i, f, this));

                  this->name_.set (r);
                  continue;
                }
              }

              if (!id_.present ())
              {
                throw ::xsd::cxx::tree::expected_attribute< char > (
                  "id",
                  "");
              }

              if (!name_.present ())
              {
                throw ::xsd::cxx::tree::expected_attribute< char > (
                  "name",
                  "");
              }
            }

            topologyType* topologyType::
            _clone (::xml_schema::flags f,
                    ::xml_schema::container* c) const
            {
              return new class topologyType (*this, f, c);
            }

            topologyType::
            ~topologyType ()
            {
            }

            // topologyParameterType
            //

            topologyParameterType::
            topologyParameterType (const type_type& type)
            : ::xml_schema::type (),
              type_ (type, ::xml_schema::flags (), this)
            {
            }

            topologyParameterType::
            topologyParameterType (const topologyParameterType& x,
                                   ::xml_schema::flags f,
                                   ::xml_schema::container* c)
            : ::xml_schema::type (x, f, c),
              type_ (x.type_, f, this)
            {
            }

            topologyParameterType::
            topologyParameterType (const ::xercesc::DOMElement& e,
                                   ::xml_schema::flags f,
                                   ::xml_schema::container* c)
            : ::xml_schema::type (e, f | ::xml_schema::flags::base, c),
              type_ (f, this)
            {
              if ((f & ::xml_schema::flags::base) == 0)
              {
                ::xsd::cxx::xml::dom::parser< char > p (e, false, true);
                this->parse (p, f);
              }
            }

            void topologyParameterType::
            parse (::xsd::cxx::xml::dom::parser< char >& p,
                   ::xml_schema::flags f)
            {
              while (p.more_attributes ())
              {
                const ::xercesc::DOMAttr& i (p.next_attribute ());
                const ::xsd::cxx::xml::qualified_name< char > n (
                  ::xsd::cxx::xml::dom::name< char > (i));

                if (n.name () == "type" && n.namespace_ ().empty ())
                {
                  ::std::auto_ptr< type_type > r (
                    type_traits::create (i, f, this));

                  this->type_.set (r);
                  continue;
                }
              }

              if (!type_.present ())
              {
                throw ::xsd::cxx::tree::expected_attribute< char > (
                  "type",
                  "");
              }
            }

            topologyParameterType* topologyParameterType::
            _clone (::xml_schema::flags f,
                    ::xml_schema::container* c) const
            {
              return new class topologyParameterType (*this, f, c);
            }

            topologyParameterType::
            ~topologyParameterType ()
            {
            }
          }
        }
      }
    }
  }
}

#include <istream>
#include <xsd/cxx/xml/sax/std-input-source.hxx>
#include <xsd/cxx/tree/error-handler.hxx>

namespace research
{
  namespace noc
  {
    namespace application_mapping
    {
      namespace unified_framework
      {
        namespace schema
        {
          namespace topologyParameter
          {
            ::std::auto_ptr< ::research::noc::application_mapping::unified_framework::schema::topologyParameter::topologyType >
            topology (const ::std::string& u,
                      ::xml_schema::flags f,
                      const ::xml_schema::properties& p)
            {
              ::xsd::cxx::xml::auto_initializer i (
                (f & ::xml_schema::flags::dont_initialize) == 0,
                (f & ::xml_schema::flags::keep_dom) == 0);

              ::xsd::cxx::tree::error_handler< char > h;

              ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
                ::xsd::cxx::xml::dom::parse< char > (
                  u, h, p, f));

              h.throw_if_failed< ::xsd::cxx::tree::parsing< char > > ();

              ::std::auto_ptr< ::research::noc::application_mapping::unified_framework::schema::topologyParameter::topologyType > r (
                ::research::noc::application_mapping::unified_framework::schema::topologyParameter::topology (
                  d, f | ::xml_schema::flags::own_dom, p));

              return r;
            }

            ::std::auto_ptr< ::research::noc::application_mapping::unified_framework::schema::topologyParameter::topologyType >
            topology (const ::std::string& u,
                      ::xml_schema::error_handler& h,
                      ::xml_schema::flags f,
                      const ::xml_schema::properties& p)
            {
              ::xsd::cxx::xml::auto_initializer i (
                (f & ::xml_schema::flags::dont_initialize) == 0,
                (f & ::xml_schema::flags::keep_dom) == 0);

              ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
                ::xsd::cxx::xml::dom::parse< char > (
                  u, h, p, f));

              if (!d.get ())
                throw ::xsd::cxx::tree::parsing< char > ();

              ::std::auto_ptr< ::research::noc::application_mapping::unified_framework::schema::topologyParameter::topologyType > r (
                ::research::noc::application_mapping::unified_framework::schema::topologyParameter::topology (
                  d, f | ::xml_schema::flags::own_dom, p));

              return r;
            }

            ::std::auto_ptr< ::research::noc::application_mapping::unified_framework::schema::topologyParameter::topologyType >
            topology (const ::std::string& u,
                      ::xercesc::DOMErrorHandler& h,
                      ::xml_schema::flags f,
                      const ::xml_schema::properties& p)
            {
              ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
                ::xsd::cxx::xml::dom::parse< char > (
                  u, h, p, f));

              if (!d.get ())
                throw ::xsd::cxx::tree::parsing< char > ();

              ::std::auto_ptr< ::research::noc::application_mapping::unified_framework::schema::topologyParameter::topologyType > r (
                ::research::noc::application_mapping::unified_framework::schema::topologyParameter::topology (
                  d, f | ::xml_schema::flags::own_dom, p));

              return r;
            }

            ::std::auto_ptr< ::research::noc::application_mapping::unified_framework::schema::topologyParameter::topologyType >
            topology (::std::istream& is,
                      ::xml_schema::flags f,
                      const ::xml_schema::properties& p)
            {
              ::xsd::cxx::xml::auto_initializer i (
                (f & ::xml_schema::flags::dont_initialize) == 0,
                (f & ::xml_schema::flags::keep_dom) == 0);

              ::xsd::cxx::xml::sax::std_input_source isrc (is);
              return ::research::noc::application_mapping::unified_framework::schema::topologyParameter::topology (isrc, f, p);
            }

            ::std::auto_ptr< ::research::noc::application_mapping::unified_framework::schema::topologyParameter::topologyType >
            topology (::std::istream& is,
                      ::xml_schema::error_handler& h,
                      ::xml_schema::flags f,
                      const ::xml_schema::properties& p)
            {
              ::xsd::cxx::xml::auto_initializer i (
                (f & ::xml_schema::flags::dont_initialize) == 0,
                (f & ::xml_schema::flags::keep_dom) == 0);

              ::xsd::cxx::xml::sax::std_input_source isrc (is);
              return ::research::noc::application_mapping::unified_framework::schema::topologyParameter::topology (isrc, h, f, p);
            }

            ::std::auto_ptr< ::research::noc::application_mapping::unified_framework::schema::topologyParameter::topologyType >
            topology (::std::istream& is,
                      ::xercesc::DOMErrorHandler& h,
                      ::xml_schema::flags f,
                      const ::xml_schema::properties& p)
            {
              ::xsd::cxx::xml::sax::std_input_source isrc (is);
              return ::research::noc::application_mapping::unified_framework::schema::topologyParameter::topology (isrc, h, f, p);
            }

            ::std::auto_ptr< ::research::noc::application_mapping::unified_framework::schema::topologyParameter::topologyType >
            topology (::std::istream& is,
                      const ::std::string& sid,
                      ::xml_schema::flags f,
                      const ::xml_schema::properties& p)
            {
              ::xsd::cxx::xml::auto_initializer i (
                (f & ::xml_schema::flags::dont_initialize) == 0,
                (f & ::xml_schema::flags::keep_dom) == 0);

              ::xsd::cxx::xml::sax::std_input_source isrc (is, sid);
              return ::research::noc::application_mapping::unified_framework::schema::topologyParameter::topology (isrc, f, p);
            }

            ::std::auto_ptr< ::research::noc::application_mapping::unified_framework::schema::topologyParameter::topologyType >
            topology (::std::istream& is,
                      const ::std::string& sid,
                      ::xml_schema::error_handler& h,
                      ::xml_schema::flags f,
                      const ::xml_schema::properties& p)
            {
              ::xsd::cxx::xml::auto_initializer i (
                (f & ::xml_schema::flags::dont_initialize) == 0,
                (f & ::xml_schema::flags::keep_dom) == 0);

              ::xsd::cxx::xml::sax::std_input_source isrc (is, sid);
              return ::research::noc::application_mapping::unified_framework::schema::topologyParameter::topology (isrc, h, f, p);
            }

            ::std::auto_ptr< ::research::noc::application_mapping::unified_framework::schema::topologyParameter::topologyType >
            topology (::std::istream& is,
                      const ::std::string& sid,
                      ::xercesc::DOMErrorHandler& h,
                      ::xml_schema::flags f,
                      const ::xml_schema::properties& p)
            {
              ::xsd::cxx::xml::sax::std_input_source isrc (is, sid);
              return ::research::noc::application_mapping::unified_framework::schema::topologyParameter::topology (isrc, h, f, p);
            }

            ::std::auto_ptr< ::research::noc::application_mapping::unified_framework::schema::topologyParameter::topologyType >
            topology (::xercesc::InputSource& i,
                      ::xml_schema::flags f,
                      const ::xml_schema::properties& p)
            {
              ::xsd::cxx::tree::error_handler< char > h;

              ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
                ::xsd::cxx::xml::dom::parse< char > (
                  i, h, p, f));

              h.throw_if_failed< ::xsd::cxx::tree::parsing< char > > ();

              ::std::auto_ptr< ::research::noc::application_mapping::unified_framework::schema::topologyParameter::topologyType > r (
                ::research::noc::application_mapping::unified_framework::schema::topologyParameter::topology (
                  d, f | ::xml_schema::flags::own_dom, p));

              return r;
            }

            ::std::auto_ptr< ::research::noc::application_mapping::unified_framework::schema::topologyParameter::topologyType >
            topology (::xercesc::InputSource& i,
                      ::xml_schema::error_handler& h,
                      ::xml_schema::flags f,
                      const ::xml_schema::properties& p)
            {
              ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
                ::xsd::cxx::xml::dom::parse< char > (
                  i, h, p, f));

              if (!d.get ())
                throw ::xsd::cxx::tree::parsing< char > ();

              ::std::auto_ptr< ::research::noc::application_mapping::unified_framework::schema::topologyParameter::topologyType > r (
                ::research::noc::application_mapping::unified_framework::schema::topologyParameter::topology (
                  d, f | ::xml_schema::flags::own_dom, p));

              return r;
            }

            ::std::auto_ptr< ::research::noc::application_mapping::unified_framework::schema::topologyParameter::topologyType >
            topology (::xercesc::InputSource& i,
                      ::xercesc::DOMErrorHandler& h,
                      ::xml_schema::flags f,
                      const ::xml_schema::properties& p)
            {
              ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
                ::xsd::cxx::xml::dom::parse< char > (
                  i, h, p, f));

              if (!d.get ())
                throw ::xsd::cxx::tree::parsing< char > ();

              ::std::auto_ptr< ::research::noc::application_mapping::unified_framework::schema::topologyParameter::topologyType > r (
                ::research::noc::application_mapping::unified_framework::schema::topologyParameter::topology (
                  d, f | ::xml_schema::flags::own_dom, p));

              return r;
            }

            ::std::auto_ptr< ::research::noc::application_mapping::unified_framework::schema::topologyParameter::topologyType >
            topology (const ::xercesc::DOMDocument& d,
                      ::xml_schema::flags f,
                      const ::xml_schema::properties& p)
            {
              if (f & ::xml_schema::flags::keep_dom)
              {
                ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > c (
                  static_cast< ::xercesc::DOMDocument* > (d.cloneNode (true)));

                ::std::auto_ptr< ::research::noc::application_mapping::unified_framework::schema::topologyParameter::topologyType > r (
                  ::research::noc::application_mapping::unified_framework::schema::topologyParameter::topology (
                    c, f | ::xml_schema::flags::own_dom, p));

                return r;
              }

              const ::xercesc::DOMElement& e (*d.getDocumentElement ());
              const ::xsd::cxx::xml::qualified_name< char > n (
                ::xsd::cxx::xml::dom::name< char > (e));

              if (n.name () == "topology" &&
                  n.namespace_ () == "http://webspace.ulbsibiu.ro/ciprian.radu/research/noc/application_mapping/unified_framework/schema/topologyParameter")
              {
                ::std::auto_ptr< ::research::noc::application_mapping::unified_framework::schema::topologyParameter::topologyType > r (
                  ::xsd::cxx::tree::traits< ::research::noc::application_mapping::unified_framework::schema::topologyParameter::topologyType, char >::create (
                    e, f, 0));
                return r;
              }

              throw ::xsd::cxx::tree::unexpected_element < char > (
                n.name (),
                n.namespace_ (),
                "topology",
                "http://webspace.ulbsibiu.ro/ciprian.radu/research/noc/application_mapping/unified_framework/schema/topologyParameter");
            }

            ::std::auto_ptr< ::research::noc::application_mapping::unified_framework::schema::topologyParameter::topologyType >
            topology (::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument >& d,
                      ::xml_schema::flags f,
                      const ::xml_schema::properties&)
            {
              ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > c (
                ((f & ::xml_schema::flags::keep_dom) &&
                 !(f & ::xml_schema::flags::own_dom))
                ? static_cast< ::xercesc::DOMDocument* > (d->cloneNode (true))
                : 0);

              ::xercesc::DOMDocument& doc (c.get () ? *c : *d);
              const ::xercesc::DOMElement& e (*doc.getDocumentElement ());

              const ::xsd::cxx::xml::qualified_name< char > n (
                ::xsd::cxx::xml::dom::name< char > (e));

              if (f & ::xml_schema::flags::keep_dom)
                doc.setUserData (::xml_schema::dom::tree_node_key,
                                 (c.get () ? &c : &d),
                                 0);

              if (n.name () == "topology" &&
                  n.namespace_ () == "http://webspace.ulbsibiu.ro/ciprian.radu/research/noc/application_mapping/unified_framework/schema/topologyParameter")
              {
                ::std::auto_ptr< ::research::noc::application_mapping::unified_framework::schema::topologyParameter::topologyType > r (
                  ::xsd::cxx::tree::traits< ::research::noc::application_mapping::unified_framework::schema::topologyParameter::topologyType, char >::create (
                    e, f, 0));
                return r;
              }

              throw ::xsd::cxx::tree::unexpected_element < char > (
                n.name (),
                n.namespace_ (),
                "topology",
                "http://webspace.ulbsibiu.ro/ciprian.radu/research/noc/application_mapping/unified_framework/schema/topologyParameter");
            }
          }
        }
      }
    }
  }
}

#include <ostream>
#include <xsd/cxx/tree/error-handler.hxx>
#include <xsd/cxx/xml/dom/serialization-source.hxx>

namespace research
{
  namespace noc
  {
    namespace application_mapping
    {
      namespace unified_framework
      {
        namespace schema
        {
          namespace topologyParameter
          {
            void
            operator<< (::xercesc::DOMElement& e, const topologyType& i)
            {
              e << static_cast< const ::xml_schema::type& > (i);

              // topologyParameter
              //
              for (topologyType::topologyParameter_const_iterator
                   b (i.topologyParameter ().begin ()), n (i.topologyParameter ().end ());
                   b != n; ++b)
              {
                ::xercesc::DOMElement& s (
                  ::xsd::cxx::xml::dom::create_element (
                    "topologyParameter",
                    "http://webspace.ulbsibiu.ro/ciprian.radu/research/noc/application_mapping/unified_framework/schema/topologyParameter",
                    e));

                s << *b;
              }

              // id
              //
              {
                ::xercesc::DOMAttr& a (
                  ::xsd::cxx::xml::dom::create_attribute (
                    "id",
                    e));

                a << i.id ();
              }

              // name
              //
              {
                ::xercesc::DOMAttr& a (
                  ::xsd::cxx::xml::dom::create_attribute (
                    "name",
                    e));

                a << i.name ();
              }
            }

            void
            topology (::std::ostream& o,
                      const ::research::noc::application_mapping::unified_framework::schema::topologyParameter::topologyType& s,
                      const ::xml_schema::namespace_infomap& m,
                      const ::std::string& e,
                      ::xml_schema::flags f)
            {
              ::xsd::cxx::xml::auto_initializer i (
                (f & ::xml_schema::flags::dont_initialize) == 0);

              ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
                ::research::noc::application_mapping::unified_framework::schema::topologyParameter::topology (s, m, f));

              ::xsd::cxx::tree::error_handler< char > h;

              ::xsd::cxx::xml::dom::ostream_format_target t (o);
              if (!::xsd::cxx::xml::dom::serialize (t, *d, e, h, f))
              {
                h.throw_if_failed< ::xsd::cxx::tree::serialization< char > > ();
              }
            }

            void
            topology (::std::ostream& o,
                      const ::research::noc::application_mapping::unified_framework::schema::topologyParameter::topologyType& s,
                      ::xml_schema::error_handler& h,
                      const ::xml_schema::namespace_infomap& m,
                      const ::std::string& e,
                      ::xml_schema::flags f)
            {
              ::xsd::cxx::xml::auto_initializer i (
                (f & ::xml_schema::flags::dont_initialize) == 0);

              ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
                ::research::noc::application_mapping::unified_framework::schema::topologyParameter::topology (s, m, f));
              ::xsd::cxx::xml::dom::ostream_format_target t (o);
              if (!::xsd::cxx::xml::dom::serialize (t, *d, e, h, f))
              {
                throw ::xsd::cxx::tree::serialization< char > ();
              }
            }

            void
            topology (::std::ostream& o,
                      const ::research::noc::application_mapping::unified_framework::schema::topologyParameter::topologyType& s,
                      ::xercesc::DOMErrorHandler& h,
                      const ::xml_schema::namespace_infomap& m,
                      const ::std::string& e,
                      ::xml_schema::flags f)
            {
              ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
                ::research::noc::application_mapping::unified_framework::schema::topologyParameter::topology (s, m, f));
              ::xsd::cxx::xml::dom::ostream_format_target t (o);
              if (!::xsd::cxx::xml::dom::serialize (t, *d, e, h, f))
              {
                throw ::xsd::cxx::tree::serialization< char > ();
              }
            }

            void
            topology (::xercesc::XMLFormatTarget& t,
                      const ::research::noc::application_mapping::unified_framework::schema::topologyParameter::topologyType& s,
                      const ::xml_schema::namespace_infomap& m,
                      const ::std::string& e,
                      ::xml_schema::flags f)
            {
              ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
                ::research::noc::application_mapping::unified_framework::schema::topologyParameter::topology (s, m, f));

              ::xsd::cxx::tree::error_handler< char > h;

              if (!::xsd::cxx::xml::dom::serialize (t, *d, e, h, f))
              {
                h.throw_if_failed< ::xsd::cxx::tree::serialization< char > > ();
              }
            }

            void
            topology (::xercesc::XMLFormatTarget& t,
                      const ::research::noc::application_mapping::unified_framework::schema::topologyParameter::topologyType& s,
                      ::xml_schema::error_handler& h,
                      const ::xml_schema::namespace_infomap& m,
                      const ::std::string& e,
                      ::xml_schema::flags f)
            {
              ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
                ::research::noc::application_mapping::unified_framework::schema::topologyParameter::topology (s, m, f));
              if (!::xsd::cxx::xml::dom::serialize (t, *d, e, h, f))
              {
                throw ::xsd::cxx::tree::serialization< char > ();
              }
            }

            void
            topology (::xercesc::XMLFormatTarget& t,
                      const ::research::noc::application_mapping::unified_framework::schema::topologyParameter::topologyType& s,
                      ::xercesc::DOMErrorHandler& h,
                      const ::xml_schema::namespace_infomap& m,
                      const ::std::string& e,
                      ::xml_schema::flags f)
            {
              ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
                ::research::noc::application_mapping::unified_framework::schema::topologyParameter::topology (s, m, f));
              if (!::xsd::cxx::xml::dom::serialize (t, *d, e, h, f))
              {
                throw ::xsd::cxx::tree::serialization< char > ();
              }
            }

            void
            topology (::xercesc::DOMDocument& d,
                      const ::research::noc::application_mapping::unified_framework::schema::topologyParameter::topologyType& s,
                      ::xml_schema::flags)
            {
              ::xercesc::DOMElement& e (*d.getDocumentElement ());
              const ::xsd::cxx::xml::qualified_name< char > n (
                ::xsd::cxx::xml::dom::name< char > (e));

              if (n.name () == "topology" &&
                  n.namespace_ () == "http://webspace.ulbsibiu.ro/ciprian.radu/research/noc/application_mapping/unified_framework/schema/topologyParameter")
              {
                e << s;
              }
              else
              {
                throw ::xsd::cxx::tree::unexpected_element < char > (
                  n.name (),
                  n.namespace_ (),
                  "topology",
                  "http://webspace.ulbsibiu.ro/ciprian.radu/research/noc/application_mapping/unified_framework/schema/topologyParameter");
              }
            }

            ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument >
            topology (const ::research::noc::application_mapping::unified_framework::schema::topologyParameter::topologyType& s,
                      const ::xml_schema::namespace_infomap& m,
                      ::xml_schema::flags f)
            {
              ::xml_schema::dom::auto_ptr< ::xercesc::DOMDocument > d (
                ::xsd::cxx::xml::dom::serialize< char > (
                  "topology",
                  "http://webspace.ulbsibiu.ro/ciprian.radu/research/noc/application_mapping/unified_framework/schema/topologyParameter",
                  m, f));

              ::research::noc::application_mapping::unified_framework::schema::topologyParameter::topology (*d, s, f);
              return d;
            }

            void
            operator<< (::xercesc::DOMElement& e, const topologyParameterType& i)
            {
              e << static_cast< const ::xml_schema::type& > (i);

              // type
              //
              {
                ::xercesc::DOMAttr& a (
                  ::xsd::cxx::xml::dom::create_attribute (
                    "type",
                    e));

                a << i.type ();
              }
            }
          }
        }
      }
    }
  }
}

#include <xsd/cxx/post.hxx>

// Begin epilogue.
//
//
// End epilogue.

