#include "stdafx.h"
#include "arithmetics_factory.h"
#include "arithmetics_impl.h"

#include <memory>

namespace
{
  std::atomic_size_t g_instances = 0;
  std::atomic_size_t g_locks = 0;
}

CoArithmeticsFactory::CoArithmeticsFactory() : m_references( 0 )
{
  ++g_instances;
}

CoArithmeticsFactory::~CoArithmeticsFactory()
{
  --g_instances;
}

STDMETHODIMP CoArithmeticsFactory::QueryInterface( REFIID iface_id, void ** iface_ptr )
{
  assert( iface_ptr );
  *iface_ptr = nullptr;

  if ( iface_id == IID_IUnknown )
  {
    *iface_ptr = static_cast<IUnknown*>( this );
  }
  else if ( iface_id == IID_IClassFactory )
  {
    *iface_ptr = static_cast<IClassFactory*>( this );
  }

  if (*iface_ptr)
  {
	  AddRef();
  }

  return *iface_ptr ? S_OK : E_NOINTERFACE;
}

STDMETHODIMP_( ULONG ) CoArithmeticsFactory::AddRef()
{
  return ++m_references;
}

STDMETHODIMP_( ULONG ) CoArithmeticsFactory::Release()
{
  auto updated_refs = --m_references;
  if ( updated_refs == 0 )
  {
    delete this;
  }

  return updated_refs;
}

STDMETHODIMP CoArithmeticsFactory::CreateInstance( IUnknown* outer_ptr, REFIID iface_id, void** iface_ptr )
{
  if ( outer_ptr )
  {
    return CLASS_E_NOAGGREGATION;
  }

  auto arithmetics_ptr = std::make_unique<CoArithmetics>();
  const HRESULT res = arithmetics_ptr->QueryInterface( iface_id, iface_ptr );

  if ( SUCCEEDED( res ) )
  {
    arithmetics_ptr.release();
  }
  return res;
}

STDMETHODIMP CoArithmeticsFactory::LockServer( BOOL lock )
{
  lock ? ++g_locks : --g_locks;

  return S_OK;
}

size_t CoArithmeticsFactory::GetInstancesNum()
{
  return g_instances + g_locks;
}
