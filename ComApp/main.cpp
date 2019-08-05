#include <sdkddkver.h>

#include <stdexcept>
#include <iostream>

#include <initguid.h>
#include <comdef.h>
#include <cassert>

#include "idl/Arithmetics.h"

#define ENSURE_RESULT(expr) if(FAILED(expr)) throw std::runtime_error( #expr " failed" )

namespace
{
  using IArithmeticsPtr = _com_ptr_t< _com_IIID<IArithmetics, & __uuidof(IArithmetics)>>;

  void safe_main()
  {
    const HRESULT initialized = ::CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
    ENSURE_RESULT(initialized);

    {
      IClassFactoryPtr iclass_factory;
      const HRESULT got_class_factory = ::CoGetClassObject(CLSID_CoArithmetics, CLSCTX_LOCAL_SERVER, nullptr, IID_PPV_ARGS(&iclass_factory));
      ENSURE_RESULT(got_class_factory);

      IArithmeticsPtr iarithmetics;
      const HRESULT got_arithmetics = iclass_factory->CreateInstance(nullptr, IID_PPV_ARGS(&iarithmetics));
      ENSURE_RESULT(got_arithmetics);

      long result = 0;
      const HRESULT is_added = iarithmetics->Add(2, 3, &result);
      ENSURE_RESULT(is_added);

      assert(result == 5);

      IConnectionPointContainerPtr conn_point_container;
      const HRESULT got_conn_point_container = iarithmetics->QueryInterface(IID_PPV_ARGS(&conn_point_container));
      ENSURE_RESULT(got_conn_point_container);

      IConnectionPointPtr conn_point;
      const HRESULT got_conn_point = conn_point_container->FindConnectionPoint(IID_IResultCallback, &conn_point);
      ENSURE_RESULT(got_conn_point);

      IResultCallback* cb = nullptr;
      DWORD cookie = 0;
      HRESULT advise_result = conn_point->Advise(cb, &cookie);
      ENSURE_RESULT(advise_result);

      HRESULT unadvise_result = conn_point->Unadvise(cookie);
      ENSURE_RESULT(unadvise_result);
    }

    ::CoUninitialize();
  }
}

int main()
{
  try
  {
    safe_main();
    return 0;
  }
  catch (const std::exception& ex)
  {
    std::cerr << "Unhandled exception: " << ex.what() << '\n';
  }
  catch (...)
  {
    std::cerr << "Unhandled unknown exception\n";
  }

  return 1;
}