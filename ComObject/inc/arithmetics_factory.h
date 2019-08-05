#pragma once

#include <comdef.h>
#include <atomic>

class CoArithmeticsFactory : public IClassFactory
{
public:
  CoArithmeticsFactory();
  ~CoArithmeticsFactory();

  // IUnknown
  STDMETHODIMP QueryInterface( REFIID iface_id, void** iface_ptr ) override;
  STDMETHODIMP_(ULONG) AddRef() override;
  STDMETHODIMP_(ULONG) Release() override;

  // IClassFactory
  STDMETHODIMP CreateInstance( IUnknown* outer_ptr, REFIID iface_id, void** iface_ptr ) override;
  STDMETHODIMP LockServer( BOOL lock ) override;

  static size_t GetInstancesNum();

private:
  std::atomic<ULONG> m_references;
};