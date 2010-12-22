// WMVProfile.h : Declaration of the CWMVProfile

#pragma once
#include "resource.h"       // main symbols

#include "WMVCreator.h"
#include "profile.h"
#include "wmvcodec.h"

// CWMVProfile

class ATL_NO_VTABLE CWMVProfile : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CWMVProfile, &CLSID_WMVProfile>,
	public IDispatchImpl<IWMVProfile, &IID_IWMVProfile, &LIBID_WMVCreatorLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CWMVProfile()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_WMVPROFILE)


BEGIN_COM_MAP(CWMVProfile)
	COM_INTERFACE_ENTRY(IWMVProfile)
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

	CProfile* m_pProfile;
	STDMETHOD(get_ProfileName)(BSTR* pVal);
	STDMETHOD(put_ProfileName)(BSTR newVal);
	STDMETHOD(get_ProfileDescription)(BSTR* pVal);
	STDMETHOD(put_ProfileDescription)(BSTR newVal);
	STDMETHOD(get_HasVideoStream)(VARIANT_BOOL* pVal);
	STDMETHOD(put_HasVideoStream)(VARIANT_BOOL newVal);
	STDMETHOD(get_HasAudioStream)(VARIANT_BOOL* pVal);
	STDMETHOD(put_HasAudioStream)(VARIANT_BOOL newVal);
	STDMETHOD(get_Bitrate)(LONG* pVal);
	STDMETHOD(put_Bitrate)(LONG newVal);
	STDMETHOD(get_StringEquivalent)(BSTR Param, BSTR* pVal);
	STDMETHOD(put_StringEquivalent)(BSTR Param, BSTR newVal);
	STDMETHOD(get_VideoWidth)(LONG* pVal);
	STDMETHOD(put_VideoWidth)(LONG newVal);
	STDMETHOD(get_VideoHeight)(LONG* pVal);
	STDMETHOD(put_VideoHeight)(LONG newVal);
	STDMETHOD(get_VideoCodec)(IWMVCodec** pVal);
	STDMETHOD(put_VideoCodec)(IWMVCodec* newVal);
	STDMETHOD(get_AudioCodec)(IWMVCodec** pVal);
	STDMETHOD(put_AudioCodec)(IWMVCodec* newVal);
	STDMETHOD(get_KeyFrameSpacing)(long* pVal);
	STDMETHOD(put_KeyFrameSpacing)(long newVal);
	STDMETHOD(get_Framerate)(DOUBLE* pVal);
	STDMETHOD(put_Framerate)(DOUBLE newVal);
	STDMETHOD(get_Quality)(long* pVal);
	STDMETHOD(put_Quality)(long newVal);
	STDMETHOD(get_VideoBitrate)(long* pVal);
	STDMETHOD(put_VideoBitrate)(long newVal);
	STDMETHOD(get_AudioBitrate)(long* pVal);
	STDMETHOD(put_AudioBitrate)(long newVal);
	STDMETHOD(CopyProfile)(IWMVProfile* ProfileToCopy);
	STDMETHOD(get_Seekable)(VARIANT_BOOL* pVal);
	STDMETHOD(put_Seekable)(VARIANT_BOOL newVal);
};

OBJECT_ENTRY_AUTO(__uuidof(WMVProfile), CWMVProfile)
