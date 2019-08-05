#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

#include "arithmetics_factory.h"
#include "arithmetics_impl.h"

#include <memory>
#include <cassert>

#include <sdkddkver.h>
#include <comdef.h>

STDAPI DllGetClassObject( REFCLSID class_id, REFIID iface_id, void** iface_ptr )
{
  assert( iface_ptr );
  *iface_ptr = nullptr;

  if ( class_id != CLSID_CoArithmetics )
  {
    return CLASS_E_CLASSNOTAVAILABLE;
  }

  auto factory_ptr = std::make_unique<CoArithmeticsFactory>();
  const HRESULT res = factory_ptr->QueryInterface( iface_id, iface_ptr );

  if ( SUCCEEDED( res ) )
  {
    factory_ptr.release();  
  }
  return res;
}

STDAPI DllCanUnloadNow()
{
  const bool no_instances_left =
    ( CoArithmeticsFactory::GetInstancesNum() == 0 ) &&
    ( CoArithmetics::GetInstancesNum() == 0 );
  return no_instances_left ? S_OK : S_FALSE;
}

STDAPI DllRegisterServer()
{
  return S_OK;
}

STDAPI DllUnregisterServer()
{
  return S_OK;
}