// $Id$
//
// ****              Code generated by the                 ****
// ****  Component Integrated ACE ORB (CIAO) CIDL Compiler ****
// CIAO has been developed by:
//       Center for Distributed Object Computing
//       Washington University
//       St. Louis, MO
//       USA
//       http://www.cs.wustl.edu/~schmidt/doc-center.html
// CIDL Compiler has been developed by:
//       Institute for Software Integrated Systems
//       Vanderbilt University
//       Nashville, TN
//       USA
//       http://www.isis.vanderbilt.edu/
//
// Information about CIAO is available at:
//    http://www.dre.vanderbilt.edu/CIAO

#include "SA_POP_Component_exec.h"
#include "ciao/CIAO_common.h"
#include "Planning_exec.h"

namespace CIAO
{
  namespace RACE
  {
    namespace SA_POP
    {
      namespace CIDL_SA_POP_Component_Impl
      {
        //==================================================================
        // Facet Executor Implementation Class:   Planning_exec_i
        //==================================================================

/*
        Planning_exec_i::Planning_exec_i (void)
        {
        }

        Planning_exec_i::~Planning_exec_i (void)
        {
        }

        // Operations from ::CIAO::RACE::SA_POP::Planning

        ::CORBA::Boolean
        Planning_exec_i::init (
          const char * ,
          const char * 
        )
        {
          // Your code here.
          return false;
        }

        ::CORBA::Boolean
        Planning_exec_i::generate_opstring (
          const ::CIAO::RACE::GoalStructure & ,
          ::CIAO::RACE::OperationalString_out 
        )
        {
          // Your code here.
          return false;
        }
*/

        //==================================================================
        // Component Executor Implementation Class:   SA_POP_Component_exec_i
        //==================================================================

        SA_POP_Component_exec_i::SA_POP_Component_exec_i (void)
        {
        }

        SA_POP_Component_exec_i::~SA_POP_Component_exec_i (void)
        {
        }

        // Supported or inherited operations.

        // Attribute operations.

        // Port operations.

        ::CIAO::RACE::SA_POP::CCM_Planning_ptr
        SA_POP_Component_exec_i::get_plan ()
        {
          // Your code here.
          return new Planning_exec_i();
        }

        // Operations from Components::SessionComponent

        void
        SA_POP_Component_exec_i::set_session_context (
          ::Components::SessionContext_ptr ctx)
        {
          this->context_ =
            CIAO_CIAO_RACE_SA_POP_SA_POP_Component_Impl::SA_POP_Component_Context::_narrow (
              ctx
              );

          if (this->context_ == 0)
          {
            throw ::CORBA::INTERNAL ();
          }
        }

        void
        SA_POP_Component_exec_i::ciao_preactivate ()
        {
          // Your code here.
        }

        void
        SA_POP_Component_exec_i::configuration_complete ()
        {
          // Your code here.
        }

        void
        SA_POP_Component_exec_i::ccm_activate ()
        {
          // Your code here.
        }

        void
        SA_POP_Component_exec_i::ccm_passivate ()
        {
          // Your code here.
        }

        void
        SA_POP_Component_exec_i::ccm_remove ()
        {
          // Your code here.
        }

        //==================================================================
        // Home Executor Implementation Class:   SA_POP_Component_Home_exec_i
        //==================================================================

        SA_POP_Component_Home_exec_i::SA_POP_Component_Home_exec_i (void)
        {
        }

        SA_POP_Component_Home_exec_i::~SA_POP_Component_Home_exec_i (void)
        {
        }

        // Supported or inherited operations.

        // Home operations.

        // Factory and finder operations.

        // Attribute operations.

        // Implicit operations.

        ::Components::EnterpriseComponent_ptr
        SA_POP_Component_Home_exec_i::create ()
        {
          ::Components::EnterpriseComponent_ptr retval =
            ::Components::EnterpriseComponent::_nil ();

          ACE_NEW_THROW_EX (
            retval,
            SA_POP_Component_exec_i,
            ::CORBA::NO_MEMORY ());

          return retval;
        }

        extern "C" SA_POP_COMPONENT_EXEC_Export ::Components::HomeExecutorBase_ptr
        create_CIAO_RACE_SA_POP_SA_POP_Component_Home_Impl (void)
        {
          ::Components::HomeExecutorBase_ptr retval =
            ::Components::HomeExecutorBase::_nil ();

          ACE_NEW_RETURN (
            retval,
            SA_POP_Component_Home_exec_i,
            ::Components::HomeExecutorBase::_nil ());

          return retval;
        }
      }
    }
  }
}
