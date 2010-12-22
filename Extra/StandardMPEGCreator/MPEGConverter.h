// MPEGConverter.h : Declaration of the CMPEGConverter

#ifndef __MPEGCONVERTER_H_
#define __MPEGCONVERTER_H_

#include "resource.h"       // main symbols
#include <atlctl.h>
#include "convert.h"
#include "mpegsettings.h"
#include "StandardMPEGCreatorCP.h"

/////////////////////////////////////////////////////////////////////////////
// CMPEGConverter
class ATL_NO_VTABLE CMPEGConverter : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDispatchImpl<IMPEGConverter, &IID_IMPEGConverter, &LIBID_STANDARDMPEGCREATORLib>,
	public CComControl<CMPEGConverter>,
	public IPersistStreamInitImpl<CMPEGConverter>,
	public IOleControlImpl<CMPEGConverter>,
	public IOleObjectImpl<CMPEGConverter>,
	public IOleInPlaceActiveObjectImpl<CMPEGConverter>,
	public IViewObjectExImpl<CMPEGConverter>,
	public IOleInPlaceObjectWindowlessImpl<CMPEGConverter>,
	public IConnectionPointContainerImpl<CMPEGConverter>,
	public IPersistStorageImpl<CMPEGConverter>,
	public ISpecifyPropertyPagesImpl<CMPEGConverter>,
	public IQuickActivateImpl<CMPEGConverter>,
	public IDataObjectImpl<CMPEGConverter>,
	public IProvideClassInfo2Impl<&CLSID_MPEGConverter, &DIID__IMPEGConverterEvents, &LIBID_STANDARDMPEGCREATORLib>,
	public IPropertyNotifySinkCP<CMPEGConverter>,
	public CComCoClass<CMPEGConverter, &CLSID_MPEGConverter>,
	public IConvertCallback,
	public CProxy_IMPEGConverterEvents< CMPEGConverter >
{
public:
	CMPEGConverter() : m_pConvert(NULL)
	{
		m_bWindowOnly = TRUE;

		if (m_pConvert == NULL) {
			m_pConvert = new CConvert(this);
			
			m_pConvert->SetSettings(&m_Settings);
			HRESULT hr = m_pStatistics.CoCreateInstance(CLSID_Statistics);
			m_pStatistics->SetInstance((long)m_pConvert);
		}
	}

	void FinalRelease() 
	{
		delete m_pConvert;
		m_pConvert = NULL;
	}


DECLARE_REGISTRY_RESOURCEID(IDR_MPEGCONVERTER)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CMPEGConverter)
	COM_INTERFACE_ENTRY(IMPEGConverter)
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
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(ISpecifyPropertyPages)
	COM_INTERFACE_ENTRY(IQuickActivate)
	COM_INTERFACE_ENTRY(IPersistStorage)
	COM_INTERFACE_ENTRY(IDataObject)
	COM_INTERFACE_ENTRY(IProvideClassInfo)
	COM_INTERFACE_ENTRY(IProvideClassInfo2)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
END_COM_MAP()

BEGIN_PROP_MAP(CMPEGConverter)
	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
	// Example entries
	// PROP_ENTRY("Property Description", dispid, clsid)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()

BEGIN_CONNECTION_POINT_MAP(CMPEGConverter)
	CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
	CONNECTION_POINT_ENTRY(DIID__IMPEGConverterEvents)
END_CONNECTION_POINT_MAP()

BEGIN_MSG_MAP(CMPEGConverter)
	CHAIN_MSG_MAP(CComControl<CMPEGConverter>)
	DEFAULT_REFLECTION_HANDLER()
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);



// IViewObjectEx
	DECLARE_VIEW_STATUS(VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE)

// IMPEGConverter
public:
	STDMETHOD(get_Statistics)(/*[out, retval]*/ IStatistics* *pVal);
	STDMETHOD(LoadPreset)(/*[in]*/ BSTR PresetName);
	STDMETHOD(StopConversion)();
	STDMETHOD(StartConversion)();
	STDMETHOD(get_TargetFile)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_TargetFile)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_SourceFile)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_SourceFile)(/*[in]*/ BSTR newVal);
	STDMETHOD(PassThruCmd)(/*[in]*/ BSTR Param1);

	HRESULT OnDraw(ATL_DRAWINFO& di)
	{
		RECT& rc = *(RECT*)di.prcBounds;
		::FillRect(di.hdcDraw, &rc, (HBRUSH)GetStockObject(BLACK_BRUSH));
		m_rcScreen = rc;

		return S_OK;
	}

	virtual void ConversionComplete() 
	{
		this->Fire_OnComplete();
	}

	
	STDMETHOD(SetObjectRects)(LPCRECT prcPos,LPCRECT prcClip)
	{
		HRESULT hr = IOleInPlaceObjectWindowlessImpl<CMPEGConverter>::SetObjectRects(prcPos, prcClip);

		RECT rc = m_rcPos;

		if (m_pConvert)
			m_pConvert->Resize(rc);

		return hr;
	}


private:
	RECT m_rcScreen;
	CConvert* m_pConvert;
	CMPEGSettings m_Settings;
	CComPtr<IStatistics> m_pStatistics;
};

#endif //__MPEGCONVERTER_H_
