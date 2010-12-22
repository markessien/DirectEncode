// WMVCreatorObj.h : Declaration of the CWMVCreatorObj
#pragma once
#include "resource.h"       // main symbols
#include <atlctl.h>
#include "WMVCreator.h"
#include "_IWMVCreatorObjEvents_CP.h"
#include "ConvertToWMV.h"
#include "wmvprofile.h"
#include "wmvcodec.h"

#define USE_OVERLAY_FILTER
#include "graph.h"

class CWMVCreatorObjLic
{
protected:
   static BOOL VerifyLicenseKey(BSTR bstr)
   {
      USES_CONVERSION;
      return !lstrcmp(OLE2T(bstr), _T("WMVCreatorObj license"));
   }

   static BOOL GetLicenseKey(DWORD dwReserved, BSTR* pBstr) 
   {
      USES_CONVERSION;
      *pBstr = SysAllocString( T2OLE(_T("WMVCreatorObj license"))); 
      return TRUE;
   }

   static BOOL IsLicenseValid() 
   {  
	   return TRUE; 
   }
};

// CWMVCreatorObj
class ATL_NO_VTABLE CWMVCreatorObj : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDispatchImpl<IWMVCreatorObj, &IID_IWMVCreatorObj, &LIBID_WMVCreatorLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public IPersistStreamInitImpl<CWMVCreatorObj>,
	public IOleControlImpl<CWMVCreatorObj>,
	public IOleObjectImpl<CWMVCreatorObj>,
	public IOleInPlaceActiveObjectImpl<CWMVCreatorObj>,
	public IViewObjectExImpl<CWMVCreatorObj>,
	public IOleInPlaceObjectWindowlessImpl<CWMVCreatorObj>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CWMVCreatorObj>,
	public CProxy_IWMVCreatorObjEvents<CWMVCreatorObj>, 
	public IPersistStorageImpl<CWMVCreatorObj>,
	public ISpecifyPropertyPagesImpl<CWMVCreatorObj>,
	public IQuickActivateImpl<CWMVCreatorObj>,
	public IDataObjectImpl<CWMVCreatorObj>,
	public IProvideClassInfo2Impl<&CLSID_WMVCreator, &__uuidof(_IWMVCreatorObjEvents), &LIBID_WMVCreatorLib>,
	public CComCoClass<CWMVCreatorObj, &CLSID_WMVCreator>,
	public CComControl<CWMVCreatorObj>,
	public IGraphEvents
{
public:

	CWMVCreatorObj()
	{
		m_hIcon = LoadIcon(_AtlBaseModule.m_hInstResource, (LPCTSTR) IDI_LOGO);
		m_Convert.SetCallback(this);

		CreateLicense();
	}

DECLARE_CLASSFACTORY2(CWMVCreatorObjLic)

DECLARE_OLEMISC_STATUS(OLEMISC_RECOMPOSEONRESIZE | 
	OLEMISC_INVISIBLEATRUNTIME |
	OLEMISC_CANTLINKINSIDE | 
	OLEMISC_INSIDEOUT | 
	OLEMISC_ACTIVATEWHENVISIBLE | 
	OLEMISC_SETCLIENTSITEFIRST
)

DECLARE_REGISTRY_RESOURCEID(IDR_WMVCREATOROBJ)

BEGIN_COM_MAP(CWMVCreatorObj)
	COM_INTERFACE_ENTRY(IWMVCreatorObj)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IViewObjectEx)
	COM_INTERFACE_ENTRY(IViewObject2)
	COM_INTERFACE_ENTRY(IViewObject)
	COM_INTERFACE_ENTRY(IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceObject)
	COM_INTERFACE_ENTRY2(IOleWindow, IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceActiveObject)
	COM_INTERFACE_ENTRY(IOleControl)
	COM_INTERFACE_ENTRY(IOleObject)
	COM_INTERFACE_ENTRY(IPersistStreamInit)
	COM_INTERFACE_ENTRY2(IPersist, IPersistStreamInit)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(ISpecifyPropertyPages)
	COM_INTERFACE_ENTRY(IQuickActivate)
	COM_INTERFACE_ENTRY(IPersistStorage)
	COM_INTERFACE_ENTRY(IDataObject)
	COM_INTERFACE_ENTRY(IProvideClassInfo)
	COM_INTERFACE_ENTRY(IProvideClassInfo2)
END_COM_MAP()

BEGIN_PROP_MAP(CWMVCreatorObj)
	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
	// Example entries
	// PROP_ENTRY("Property Description", dispid, clsid)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()

BEGIN_CONNECTION_POINT_MAP(CWMVCreatorObj)
	CONNECTION_POINT_ENTRY(__uuidof(_IWMVCreatorObjEvents))
END_CONNECTION_POINT_MAP()

BEGIN_MSG_MAP(CWMVCreatorObj)
	CHAIN_MSG_MAP(CComControl<CWMVCreatorObj>)
	DEFAULT_REFLECTION_HANDLER()
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid)
	{
		static const IID* arr[] = 
		{
			&IID_IWMVCreatorObj,
		};

		for (int i=0; i<sizeof(arr)/sizeof(arr[0]); i++)
		{
			if (InlineIsEqualGUID(*arr[i], riid))
				return S_OK;
		}
		return S_FALSE;
	}

// IViewObjectEx
	DECLARE_VIEW_STATUS(VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE)

// IWMVCreatorObj
public:
		HRESULT OnDraw(ATL_DRAWINFO& di)
		{
			RECT& rc = *(RECT*)di.prcBounds;
			DrawIcon(di.hdcDraw, rc.left, rc.top, m_hIcon);
		return S_OK;
	}


	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		SIZEL size = {32, 32};
		AtlPixelToHiMetric( &size, &m_sizeExtent );
		m_sizeNatural = m_sizeExtent;

		SIZEL szlPixels, szlMetric;
		szlPixels.cx = 32;
		szlPixels.cy = 32;

		AtlPixelToHiMetric(&szlPixels, &szlMetric);

		// IOleObjectImpl
		SetExtent(DVASPECT_CONTENT, &szlMetric);

		// update control sizing...
		m_rcPos.right= m_rcPos.left + 32;
		m_rcPos.bottom= m_rcPos.top + 32;

		m_bAutoSize = TRUE;

		return S_OK;
	}
	
	void FinalRelease() 
	{
	}

	STDMETHOD(StartConversion)(void);
	STDMETHOD(StopConversion)(void);
	STDMETHOD(get_Duration)(DOUBLE* pVal);
	STDMETHOD(get_Progress)(DOUBLE* pVal);
	STDMETHOD(put_Progress)(DOUBLE newVal);
	STDMETHOD(LoadSystemProfiles)(void);
	STDMETHOD(get_SystemProfileCount)(long* pVal);
	STDMETHOD(get_SystemProfile)(LONG Index, IWMVProfile** pVal);
	STDMETHOD(LoadSystemCodecs)(void);
	STDMETHOD(get_VideoCodecCount)(long* pVal);
	STDMETHOD(get_VideoCodec)(LONG Index, IWMVCodec** pVal);
	STDMETHOD(get_InputFile)(BSTR* pVal);
	STDMETHOD(put_InputFile)(BSTR newVal);
	STDMETHOD(get_OutputFile)(BSTR* pVal);
	STDMETHOD(put_OutputFile)(BSTR newVal);
	STDMETHOD(get_ConversionProfile)(IWMVProfile** pVal);
	STDMETHOD(putref_ConversionProfile)(IWMVProfile* newVal);

	HRESULT OnGraphEvent(CGraph* pGraph, long lEventCode, LONG_PTR lParam1, LONG_PTR lParam2)
	{
		switch (lEventCode)
		{
		case EC_COMPLETE:
			this->Fire_OnComplete();
			break;
		case EC_SEGMENT_STARTED:
			this->Fire_OnAboutToRun();
			break;
		case EC_ERRORABORT:
			CComBSTR str = (char*)lParam2;
			this->Fire_OnError(lParam1, str);
			break;
		}

		return S_OK;
	}

private:
	CConvertToWMV m_Convert;
	HICON m_hIcon;
	wchar_t m_strLicenseKey[128];
public:
	STDMETHOD(get_ProfileCount)(LONG* pVal);
	STDMETHOD(get_Profile)(long Index, IWMVProfile** pVal);
	STDMETHOD(putref_Profile)(long Index, IWMVProfile* newVal);
	STDMETHOD(get_AudioCodec)(long Index, IWMVCodec** pVal);
	STDMETHOD(get_AudioCodecCount)(long* pVal);
	STDMETHOD(get_EncodeFramerate)(long* pVal);
	bool Validate();
	STDMETHOD(put_LicenseKey)(BSTR newVal);
	void CreateLicense();
};



OBJECT_ENTRY_AUTO(__uuidof(WMVCreator), CWMVCreatorObj)
