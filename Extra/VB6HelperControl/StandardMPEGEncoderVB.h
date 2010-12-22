// StandardMPEGEncoderVB.h : Declaration of the CStandardMPEGEncoderVB

#ifndef __STANDARDMPEGENCODERVB_H_
#define __STANDARDMPEGENCODERVB_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CStandardMPEGEncoderVB
class ATL_NO_VTABLE CStandardMPEGEncoderVB : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CStandardMPEGEncoderVB, &CLSID_StandardMPEGEncoderVB>,
	public IDispatchImpl<IStandardMPEGEncoderVB, &IID_IStandardMPEGEncoderVB, &LIBID_DIRECTENCODEVBLib>
{
public:
	CStandardMPEGEncoderVB()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_STANDARDMPEGENCODERVB)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CStandardMPEGEncoderVB)
	COM_INTERFACE_ENTRY(IStandardMPEGEncoderVB)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// IStandardMPEGEncoderVB
public:
	STDMETHOD(PromptForGraph)(/*[in]*/ IUnknown* pGraph);
	STDMETHOD(SetOutputFileOnFileWriter)(/*[in]*/ IUnknown* pFileWriter, /*[in]*/ BSTR FilePath, long* pResult);
	STDMETHOD(GetSMPEG)(/*[out]*/ IStandardMpegEncoder** pEncoder);
	STDMETHOD(CreateFilter)();
	STDMETHOD(SetObject)(/*[in]*/ IUnknown* pUnk);
	STDMETHOD(CheckObjects)(/*[out, reval]*/ VARIANT_BOOL* pb);
	STDMETHOD(Test)();

private:
	CComPtr<IBaseFilter> m_pMPEGWriter;
	CComPtr<IStandardMpegEncoder> m_pIMPEGEncoder;
};

#endif //__STANDARDMPEGENCODERVB_H_
