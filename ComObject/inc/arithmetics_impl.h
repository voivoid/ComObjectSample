#pragma once

#include <comdef.h>
#include "idl/Arithmetics.h"

#include <atomic>

class CoArithmetics : public IArithmetics,
                      public IConnectionPointContainer,
                      public IConnectionPoint
{
public:
  CoArithmetics();
  ~CoArithmetics();

  // IUnknown
  STDMETHODIMP QueryInterface( REFIID iface_id, void** iface_ptr ) override;
  STDMETHODIMP_(ULONG) AddRef() override;
  STDMETHODIMP_(ULONG) Release() override;

  // IArithmetics
  STDMETHODIMP Add( long a, long b, long* res ) override;
  STDMETHODIMP Sub( long a, long b, long* res ) override;
  STDMETHODIMP Mul( long a, long b, long* res ) override;
  STDMETHODIMP Div( long a, long b, long* res ) override;

  // IConnectionPointContainer
  STDMETHODIMP EnumConnectionPoints( IEnumConnectionPoints** ppEnum ) override;
  STDMETHODIMP FindConnectionPoint( REFIID riid, IConnectionPoint** ppCP) override;

  // IConnectionPoint
  STDMETHODIMP GetConnectionInterface( IID* pIID ) override;
  STDMETHODIMP GetConnectionPointContainer( IConnectionPointContainer** ppCPC ) override;
  STDMETHODIMP Advise( IUnknown* pUnkSink, DWORD* pdwCookie ) override;
  STDMETHODIMP Unadvise( DWORD dwCookie ) override;
  STDMETHODIMP EnumConnections( IEnumConnections** ) override;

  static size_t GetInstancesNum();
  


private:
  std::atomic<ULONG> m_references;

  using IResultCallbackPtr = _com_ptr_t< _com_IIID<IResultCallback, & __uuidof(IResultCallback)>>;
  IResultCallbackPtr m_result_callback;
};