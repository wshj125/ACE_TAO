// ******  Code generated by the The ACE ORB (TAO) IDL Compiler *******
// TAO ORB and the TAO IDL Compiler have been developed by Washington 
// University Computer Science's Distributed Object Computing Group.
//
// Information on TAO is available at
//                 http://www.cs.wustl.edu/~schmidt/TAO.html

#if !defined (_TAO_IDL_COSNAMINGS_H_)
#define _TAO_IDL_COSNAMINGS_H_

#include "CosNamingC.h"

class POA_CosNaming : public virtual CosNaming
{
public:
  class NamingContext;
  typedef NamingContext *NamingContext_ptr;
  class NamingContext : public virtual CosNaming::NamingContext
  {
  protected:
    NamingContext (const char *obj_name = 0);
    virtual ~NamingContext (void);
  public:
    virtual void bind (const CosNaming::Name & n, CORBA::Object_ptr  obj,  CORBA::Environment &env) = 0; // pure virtual
    static void bind_skel (CORBA::ServerRequest &req, CORBA::Object_ptr obj, CORBA::Environment &env);

    virtual void rebind (const CosNaming::Name & n, CORBA::Object_ptr  obj,  CORBA::Environment &env) = 0; // pure virtual
    static void rebind_skel (CORBA::ServerRequest &req, CORBA::Object_ptr obj, CORBA::Environment &env);

    virtual void bind_context (const CosNaming::Name & n, CosNaming::NamingContext_ptr  nc,  CORBA::Environment &env) = 0; // pure virtual
    static void bind_context_skel (CORBA::ServerRequest &req, CORBA::Object_ptr obj, CORBA::Environment &env);

    virtual void rebind_context (const CosNaming::Name & n, CosNaming::NamingContext_ptr  nc,  CORBA::Environment &env) = 0; // pure virtual
    static void rebind_context_skel (CORBA::ServerRequest &req, CORBA::Object_ptr obj, CORBA::Environment &env);

    virtual CORBA::Object_ptr resolve (const CosNaming::Name & n,  CORBA::Environment &env) = 0; // pure virtual
    static void resolve_skel (CORBA::ServerRequest &req, CORBA::Object_ptr obj, CORBA::Environment &env);

    virtual void unbind (const CosNaming::Name & n,  CORBA::Environment &env) = 0; // pure virtual
    static void unbind_skel (CORBA::ServerRequest &req, CORBA::Object_ptr obj, CORBA::Environment &env);
 
    virtual CosNaming::NamingContext_ptr  new_context ( CORBA::Environment &env) = 0; // pure virtual
    static void new_context_skel (CORBA::ServerRequest &req, CORBA::Object_ptr obj, CORBA::Environment &env);

    virtual CosNaming::NamingContext_ptr  bind_new_context (const CosNaming::Name & n,  CORBA::Environment &env) = 0; // pure virtual
    static void bind_new_context_skel (CORBA::ServerRequest &req, CORBA::Object_ptr obj, CORBA::Environment &env);

    virtual void destroy ( CORBA::Environment &env) = 0; // pure virtual
    static void destroy_skel (CORBA::ServerRequest &req, CORBA::Object_ptr obj, CORBA::Environment &env);

    virtual void list (CORBA::ULong how_many, CosNaming::BindingList_out bl, CosNaming::BindingIterator_out  bi,  CORBA::Environment &env) = 0; // pure virtual
    static void list_skel (CORBA::ServerRequest &req, CORBA::Object_ptr obj, CORBA::Environment &env);

    static void _is_a_skel (CORBA::ServerRequest &req, CORBA::Object_ptr obj, CORBA::Environment &env);

  };

  class BindingIterator;
  typedef BindingIterator *BindingIterator_ptr;
  class BindingIterator : public virtual CosNaming::BindingIterator
  {
  protected:
    BindingIterator (const char *obj_name = 0);
    virtual ~BindingIterator (void);
  public:
    virtual CORBA::Boolean next_one (CosNaming::Binding_out b,  CORBA::Environment &env) = 0; // pure virtual
    static void next_one_skel (CORBA::ServerRequest &req, CORBA::Object_ptr obj, CORBA::Environment &env);

    virtual CORBA::Boolean next_n (CORBA::ULong how_many, CosNaming::BindingList_out bl,  CORBA::Environment &env) = 0; // pure virtual
    static void next_n_skel (CORBA::ServerRequest &req, CORBA::Object_ptr obj, CORBA::Environment &env);

    virtual void destroy ( CORBA::Environment &env) = 0; // pure virtual
    static void destroy_skel (CORBA::ServerRequest &req, CORBA::Object_ptr obj, CORBA::Environment &env);

    static void _is_a_skel (CORBA::ServerRequest &req, CORBA::Object_ptr obj, CORBA::Environment &env);

  };

};


#if defined (__ACE_INLINE__)
#include "CosNamingS.i"
#endif // defined INLINE


#endif // if !defined
