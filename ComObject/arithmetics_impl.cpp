#include "stdafx.h"
#include "arithmetics_impl.h"

#include <cassert>

namespace
{
  std::atomic_size_t g_instances = 0;
}

CoArithmetics::CoArithmetics() : m_references( 0 )
{
  ++g_instances;
}

CoArithmetics::~CoArithmetics()
{
  --g_instances;
}

STDMETHODIMP CoArithmetics::QueryInterface( REFIID iface_id, void** iface_ptr )
{
  assert( iface_ptr );
  *iface_ptr = nullptr;

  if ( iface_id == IID_IUnknown )
  {
    *iface_ptr = static_cast<IUnknown*>( static_cast<IArithmetics*>( this ) );
  }
  else if ( iface_id == IID_IArithmetics )
  {
    *iface_ptr = static_cast<IArithmetics*>( this );
  }
  else if (iface_id == IID_IConnectionPointContainer)
  {
    *iface_ptr = static_cast<IConnectionPointContainer*>( this );
  }
  else if (iface_id == IID_IConnectionPoint)
  {
    *iface_ptr = static_cast<IConnectionPoint*>(this);
  }

  if (*iface_ptr)
  {
	  AddRef();
  }

  return *iface_ptr ? S_OK : E_NOINTERFACE;
}

STDMETHODIMP_( ULONG ) CoArithmetics::AddRef()
{
  return ++m_references;
}

STDMETHODIMP_( ULONG ) CoArithmetics::Release()
{
  auto updated_refs = --m_references;
  if ( updated_refs == 0 )
  {
    delete this;
  }

  return updated_refs;
}

STDMETHODIMP CoArithmetics::Add( long a, long b, long* res )
{
  assert( res );
  *res = a + b;

  if (m_result_callback)
  {
    m_result_callback->GotResult(*res);
  }

  return S_OK;
}

STDMETHODIMP CoArithmetics::Sub( long a, long b, long* res )
{
  assert( res );
  *res = a - b;

  return S_OK;
}

STDMETHODIMP CoArithmetics::Mul( long a, long b, long* res )
{
  assert( res );
  *res = a * b;

  return S_OK;
}

STDMETHODIMP CoArithmetics::Div( long a, long b, long* res )
{
  assert( res );

  if (b == 0)
  {
	  return E_INVALIDARG;
  }

  *res = a / b;

  return S_OK;
}

STDMETHODIMP CoArithmetics::EnumConnectionPoints( IEnumConnectionPoints** )
{
  return E_NOTIMPL;
}
STDMETHODIMP CoArithmetics::FindConnectionPoint( REFIID riid, IConnectionPoint** ppCP)
{
  assert(ppCP);

  if (riid == IID_IResultCallback)
  {
    return QueryInterface(IID_PPV_ARGS(ppCP));
  }

  return E_NOINTERFACE;
}

STDMETHODIMP CoArithmetics::GetConnectionInterface( IID* )
{
  return E_NOTIMPL;
}
STDMETHODIMP CoArithmetics::GetConnectionPointContainer( IConnectionPointContainer** ppCPC )
{
  return E_NOTIMPL;
}

STDMETHODIMP CoArithmetics::Advise( IUnknown* pUnkSink, DWORD* pdwCookie )
{
  assert(pdwCookie);

  *pdwCookie = 1;
  return pUnkSink->QueryInterface(IID_PPV_ARGS(&m_result_callback));
}

STDMETHODIMP CoArithmetics::Unadvise( DWORD dwCookie )
{
  assert(dwCookie == 1);
  return S_OK;
}

STDMETHODIMP CoArithmetics::EnumConnections( IEnumConnections** )
{
  return E_NOTIMPL;
}

size_t CoArithmetics::GetInstancesNum()
{
  return g_instances;
}