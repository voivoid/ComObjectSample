#include <sdkddkver.h>
#include <comdef.h>
#include "idl/Arithmetics.h"
#include "arithmetics_factory.h"
#include <cassert>

int main( int argc, char** argv )
{
  if (argc != 2)
  {
    return -1;
  }

  if( strcmp( argv[1], "-Embedding" ) != 0 &&
      strcmp( argv[1], "/Embedding" ) != 0 )
  {
    return -1;
  }
  
  const HRESULT initialized = ::CoInitialize(nullptr);
  assert(SUCCEEDED(initialized));

  {
    CoArithmeticsFactory arithmetics_factory;

    IUnknownPtr iclass_factory = nullptr;
    const HRESULT got_iunknown = arithmetics_factory.QueryInterface(IID_PPV_ARGS(&iclass_factory));
    assert(SUCCEEDED(got_iunknown));

    DWORD class_object_id = 0;
    const HRESULT registered = ::CoRegisterClassObject(CLSID_CoArithmetics, iclass_factory, CLSCTX_LOCAL_SERVER, REGCLS_MULTIPLEUSE, &class_object_id);
    assert(SUCCEEDED(registered));


    MSG msg = {};
    while (::GetMessage(&msg, nullptr, 0, 0))
    {
      ::TranslateMessage(&msg);
      ::DispatchMessage(&msg);
    }


    const HRESULT revoked = ::CoRevokeClassObject(class_object_id);
    assert(SUCCEEDED(revoked));
  }

  

  ::CoUninitialize();
}
