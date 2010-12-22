// VideoClip.h : Deklaration von CVideoClip

#ifndef __VIDEOCLIP_H_
#define __VIDEOCLIP_H_

#include "resource.h"       // Hauptsymbole

#include "MediaFileList.h"

/////////////////////////////////////////////////////////////////////////////
// CVideoClip
class ATL_NO_VTABLE CVideoClip : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CVideoClip, &CLSID_VideoClip>,
	public IDispatchImpl<IVideoClip, &IID_IVideoClip, &LIBID_VIDEOEDITLib>
{
public:
	CVideoClip()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_VIDEOCLIP)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CVideoClip)
	COM_INTERFACE_ENTRY(IVideoClip)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// IVideoClip
public:
	CMediaFileList* GetMediaFileList();
	STDMETHOD(get_VideoLength)(/*[out, retval]*/ double *pVal);
	STDMETHOD(get_VideoCount)(/*[out, retval]*/ long *pVal);
	STDMETHOD(SpacePhotosToAudio)(int iStartAudioItem, int iEndAudioItem);
	STDMETHOD(ForcePhotoDurations)(/*[in]*/ double NewDuration);
	STDMETHOD(get_MediaFile)(/*[in]*/ MediaFormat format, /*[in]*/ long ItemIndex, /*[out, retval]*/ IMediaFile* *pVal);
	STDMETHOD(get_AudioCount)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_AudioLength)(/*[out, retval]*/ double *pVal);
	STDMETHOD(LoadClip)(/*[in]*/ BSTR Path);
	STDMETHOD(SaveClip)(/*[in]*/ BSTR Path);
	STDMETHOD(RemoveAudio)(/*[in]*/ long Index);
	STDMETHOD(RemoveVideo)(/*[in]*/ long Index);
	STDMETHOD(AddVideo)(long Index, /*[in]*/ BSTR Path, IMediaFile **ppResult);
	STDMETHOD(AddAudio)(long Index, /*[in]*/ BSTR Path, IMediaFile **ppResult);

private:
	CMediaFileList m_mediaList;
};

#endif //__VIDEOCLIP_H_
