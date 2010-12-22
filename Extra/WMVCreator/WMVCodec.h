// WMVCodec.h : Declaration of the CWMVCodec

#pragma once
#include "resource.h"       // main symbols

#include "WMVCreator.h"
#include "codec.h"

// CWMVCodec

class ATL_NO_VTABLE CWMVCodec : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CWMVCodec, &CLSID_WMVCodec>,
	public IDispatchImpl<IWMVCodec, &IID_IWMVCodec, &LIBID_WMVCreatorLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CWMVCodec()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_WMVCODEC)


BEGIN_COM_MAP(CWMVCodec)
	COM_INTERFACE_ENTRY(IWMVCodec)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()


	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}
	
	void FinalRelease() 
	{
	}

public:
	STDMETHOD(get_CodecName)(BSTR* pVal);
	STDMETHOD(put_CodecName)(BSTR newVal);
	STDMETHOD(get_CodecDescription)(BSTR* pVal);
	STDMETHOD(put_CodecDescription)(BSTR newVal);

	CCodec* m_pCodec;
	STDMETHOD(get_MajorType)(long* pVal);
	STDMETHOD(get_MaxPasses)(long* pVal);
	STDMETHOD(get_Passes)(LONG* pVal);
	STDMETHOD(put_Passes)(LONG newVal);
	STDMETHOD(get_Quality)(LONG* pVal);
	STDMETHOD(put_Quality)(LONG newVal);
	STDMETHOD(get_Bitrate)(LONG* pVal);
	STDMETHOD(put_Bitrate)(LONG newVal);
	STDMETHOD(get_VBRMode)(LONG* pVal);
	STDMETHOD(put_VBRMode)(LONG newVal);
	STDMETHOD(get_KeyframeFrequency)(LONG* pVal);
	STDMETHOD(put_KeyframeFrequency)(LONG newVal);
	STDMETHOD(get_Framerate)(DOUBLE* pVal);
	STDMETHOD(put_Framerate)(DOUBLE newVal);
	STDMETHOD(get_Complexity)(LONG* pVal);
	STDMETHOD(put_Complexity)(LONG newVal);
	STDMETHOD(get_FormatIndex)(LONG* pVal);
	STDMETHOD(put_FormatIndex)(LONG newVal);
	STDMETHOD(get_CodecGuid)(BSTR* pVal);
	STDMETHOD(get_ComplexityMax)(LONG* pVal);
	STDMETHOD(get_ComplexityOffline)(LONG* pVal);
	STDMETHOD(get_ComplexityLive)(long* pVal);
	STDMETHOD(get_IsVBRSupported)(VARIANT_BOOL* pVal);
	STDMETHOD(SupportedVBRModes)(VARIANT_BOOL* CBR1Pass, VARIANT_BOOL* CBR2Pass, VARIANT_BOOL* VBR1Pass, VARIANT_BOOL* VBR2Pass, LONG* ConstrainValue);
	STDMETHOD(get_FormatCount)(long* pVal);
	STDMETHOD(LoadCodecFormats)(void);
	STDMETHOD(get_FormatName)(LONG Index, BSTR* pVal);
	STDMETHOD(get_CodecIndex)(LONG* pVal);
};

OBJECT_ENTRY_AUTO(__uuidof(WMVCodec), CWMVCodec)
