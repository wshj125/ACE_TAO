// $Id$

#include "tao/Exception.h"
#include "ace/Auto_Ptr.h"
#include "ace/Log_Msg.h"

#include "Property_Handler.h"
#include "Requirement_Handler.h"
#include "CPR_Handler.h"
#include "CompPkgDesc_Handler.h"
#include "TPD_Handler.h"
#include "Process_Element.h"
#include "Process_Basic_Type.h"

#include <iostream>

using std::cerr;
using std::endl;

BEGIN_DEPLOYMENT_NAMESPACE

/// handle the package configuration and populate it
ACE_TString TPD_Handler::process_TopLevelPackageDescription()
{
  for (DOMNode* node = this->iter_->nextNode();
       node != 0;
       node = this->iter_->nextNode())
    {
      XStr node_name (node->getNodeName());
      if (node_name == XStr 
          (ACE_TEXT ("Deployment:TopLevelPackageDescription")))
        {
        }
      else if (node_name == XStr(ACE_TEXT ("package")))
        {
          if (node->hasAttributes ())
            {
              DOMNamedNodeMap* named_node_map = node->getAttributes ();

              // the number of attributes
              int length = named_node_map->getLength();
              // iterate the attributes
              for (int j = 0; j < length; ++j)
                {
                  DOMNode* attribute_node = named_node_map->item (j);
                  XStr strattrnodename (attribute_node->getNodeName ());
                  ACE_TString aceattrnodevalue =
                    XMLString::transcode (attribute_node->getNodeValue ());
                  
                  // if href is given find out the referenced position
                  // and process the element
                  if (strattrnodename == XStr (ACE_TEXT ("href")))
                    {
                      XMLURL xml_url (aceattrnodevalue.c_str ());
                      XMLURL result (aceattrnodevalue.c_str ());
                      ACE_TString url_string = aceattrnodevalue.c_str ();
                      ACE_TString doc_path =
                        XMLString::transcode ( doc_->getDocumentURI ());
                      result.makeRelativeTo
                        (XMLString::transcode (doc_path.c_str ()));
                      ACE_TString final_url =
                        XMLString::transcode (result.getURLText ());
                      
                      if (xml_url.isRelative ())
                        {
                          return final_url;
                        }
                      else
                        {
                          return url_string;
                        }
                    }
                }
            }
        }
      else
        {
          break;
        }
    }
  ACE_THROW (CORBA::INTERNAL());
}

END_DEPLOYMENT_NAMESPACE
