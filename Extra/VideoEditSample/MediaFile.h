// MediaFile.h : Deklaration von CMediaFile

#ifndef __MEDIAFILE_H_
#define __MEDIAFILE_H_

#include "resource.h"       // Hauptsymbole

class CVideoEditObj;


typedef struct tagFRECT
{
	float left;
	float top;
	float right;
	float bottom;
} FRECT;

/////////////////////////////////////////////////////////////////////////////
// CMediaFile
class ATL_NO_VTABLE CMediaFile : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CMediaFile, &CLSID_MediaFile>,
	public IDispatchImpl<IMediaFile, &IID_IMediaFile, &LIBID_VIDEOEDITLib>
{
public:

	typedef struct tagMotionInfo
	{
		bool bPerformMotion;
		RECT rcStart;
		RECT rcEnd;
		RECT rcReference;
		double dDuration;
		long fps;
	} MotionInfo;

	CMediaFile()
	{
//		m_nWorkListCount = 0;
		m_dStartOffset = 0;
		m_dTransitionLength = 2;
		m_bIsImage = VARIANT_TRUE;
		m_bDoOverlay = VARIANT_FALSE;
		m_strTransitionGuid = L"{16B280C5-EE70-11D1-9066-00C04FD9189D}";
		m_overlayText.strFontFace = "Arial";
		m_overlayText.nFontHeight = 24;
		m_overlayText.nAlignment = 0;
		m_overlayText.xPos = 0;
		m_overlayText.yPos = 0;
		m_overlayText.nWidth = 100;
		m_overlayText.nHeight = 100;
		m_overlayText.strText = L"Demo Text";

		m_motionInfo.bPerformMotion = false;
	}

	void FinalRelease()
	{
//		DeleteWorkFiles();
	}

DECLARE_REGISTRY_RESOURCEID(IDR_MEDIAFILE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CMediaFile)
	COM_INTERFACE_ENTRY(IMediaFile)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// IMediaFile
public:
	void CorrectRect(RECT & rcReference, RECT & rcToCorrect, RECT & rcCorrected, long nScreenWidth, long nScreenHeight);
	MotionInfo& GetMotionInfo(long nScreenWidth, long nScreenHeight);
	RECT VideoRectToRect(IVideoRect **rc);
	FRECT VideoRectToFRect(IVideoRect **rc);
	STDMETHOD(ApplyMotionEffect)(/*[in]*/ long hwnd, IVideoRect **rcReferenceRect, /*[in]*/ IVideoRect ** rcStart, /*[in]*/ IVideoRect ** rcEnd,  /*[in]*/ long fps,  /*[in]*/ long duration);
	IVideoRect* CreateVideoRect(RECT rc);
	STDMETHOD(GetZoomOutRect)(/*[in]*/ IVideoRect** rcSource, /*[in]*/ IVideoRect** rcZoomIn, /*[out, retval]*/ IVideoRect**  ppResult);
	void SetCallback(CVideoEditObj* pCallback);
	HRESULT SaveBitmapToFile(char* pstrFile, HDC hdc, HBITMAP hbm, BITMAP& bmp);
	STDMETHOD(get_DoTextOverlay)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_DoTextOverlay)(/*[in]*/ VARIANT_BOOL newVal);
	STDMETHOD(OverlayText)(/*[in]*/ BSTR Text, /*[in]*/ long xPos, /*[in]*/ long yPos, long Width, long Height, BSTR FontFace, long FontHeight);
	STDMETHOD(get_TransitionLength)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_TransitionLength)(/*[in]*/ double newVal);
	STDMETHOD(get_IsImage)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_IsImage)(/*[in]*/ VARIANT_BOOL newVal);
	STDMETHOD(put_PosterFramePath)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_FileTitle)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_FileTitle)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_FilePath)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_FilePath)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_StartOffset)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_StartOffset)(/*[in]*/ double newVal);
	STDMETHOD(get_Transition)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_Transition)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_Duration)(/*[out, retval]*/ double *pVal);
	STDMETHOD(put_Duration)(double newVal);
	STDMETHOD(get_PosterFrame)(/*[out, retval]*/ IPictureDisp* *pVal);

private:
	int LoadPicture(char* pstrPath, IPicture** ppPicture);
private:

	enum
	{
		HIMETRIC_INCH	= 2540
	};

	typedef struct tagTextInfo
	{
		CComBSTR strText;
		CComBSTR strFontFace;
		long xPos;
		long yPos;
		long nWidth;
		long nHeight;
		long nFontHeight;
		long nAlignment;
	} TextInfo;


	CVideoEditObj* m_pCallback;
	TextInfo m_overlayText;
	MotionInfo m_motionInfoCorrected;
	MotionInfo m_motionInfo;
	CComBSTR m_strTransitionGuid;
	CComPtr<IPictureDisp> m_pictureDisp;
    CComPtr<IPicture> m_picture;
	CComBSTR m_strFileTitle;
	CComBSTR m_strFilePath;
	VARIANT_BOOL m_bIsImage;
	VARIANT_BOOL m_bDoOverlay;
	double m_dDuration;
	double m_dStartOffset;
	double m_dTransitionLength;
};

#endif //__MEDIAFILE_H_
