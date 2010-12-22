// VideoEditObj.h : Deklaration von CVideoEditObj

#ifndef __VIDEOEDITOBJ_H_
#define __VIDEOEDITOBJ_H_

#include "resource.h"       // Hauptsymbole
#include <atlctl.h>
#include "VideoEditCP.h"
#include "DESEdit.h"
#include "MediaFileList.h"

class CVideoClip;

/////////////////////////////////////////////////////////////////////////////
// CVideoEditObj
class ATL_NO_VTABLE CVideoEditObj : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDispatchImpl<IVideoEditObj, &IID_IVideoEditObj, &LIBID_VIDEOEDITLib>,
	public CComControl<CVideoEditObj>,
	public IPersistStreamInitImpl<CVideoEditObj>,
	public IOleControlImpl<CVideoEditObj>,
	public IOleObjectImpl<CVideoEditObj>,
	public IOleInPlaceActiveObjectImpl<CVideoEditObj>,
	public IViewObjectExImpl<CVideoEditObj>,
	public IOleInPlaceObjectWindowlessImpl<CVideoEditObj>,
	public IConnectionPointContainerImpl<CVideoEditObj>,
	public IPersistStorageImpl<CVideoEditObj>,
	public ISpecifyPropertyPagesImpl<CVideoEditObj>,
	public IQuickActivateImpl<CVideoEditObj>,
	public IDataObjectImpl<CVideoEditObj>,
	public IProvideClassInfo2Impl<&CLSID_VideoEdit, &DIID__IVideoEditObjEvents, &LIBID_VIDEOEDITLib>,
	public IPropertyNotifySinkCP<CVideoEditObj>,
	public CComCoClass<CVideoEditObj, &CLSID_VideoEdit>,
	public CProxy_IVideoEditObjEvents< CVideoEditObj >
{
public:
	CVideoEditObj() : m_videoEdit(this)
	{
		m_hIcon = LoadIcon(_Module.m_hInstResource, (LPCTSTR) IDI_LOGO);
		m_pClip = NULL;
	}
	
	HRESULT FinalConstruct( )
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

DECLARE_REGISTRY_RESOURCEID(IDR_VIDEOEDITOBJ)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CVideoEditObj)
	COM_INTERFACE_ENTRY(IVideoEditObj)
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

BEGIN_PROP_MAP(CVideoEditObj)
	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
	// Beispieleinträge
	// PROP_ENTRY("Eigenschaftenbeschreibung", dispid, clsid)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()

BEGIN_CONNECTION_POINT_MAP(CVideoEditObj)
	CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
	CONNECTION_POINT_ENTRY(DIID__IVideoEditObjEvents)
END_CONNECTION_POINT_MAP()

BEGIN_MSG_MAP(CVideoEditObj)
	CHAIN_MSG_MAP(CComControl<CVideoEditObj>)
	DEFAULT_REFLECTION_HANDLER()
END_MSG_MAP()
// Prototypen von Behandlungsroutinen:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);



// IViewObjectEx
	DECLARE_VIEW_STATUS(VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE)

// IVideoEditObj
public:
	STDMETHOD(InsertTemplate)(/*[in]*/ IVideoClip** pVideoClip);
	STDMETHOD(get_CurrentClip)(/*[out, retval]*/ IVideoClip* *pVal);
	STDMETHOD(put_CurrentClip)(/*[in]*/ IVideoClip** newVal);
	STDMETHOD(EnumerateTransitions)();
	STDMETHOD(CompileToFile)(/*[in]*/ BSTR OutputPath, /*[in]*/ long Format, /*[out, retval]*/ VARIANT_BOOL * pResult);
	STDMETHOD(get_Duration)(/*[out, retval]*/ double *pVal);
	STDMETHOD(get_Progress)(/*[out, retval]*/ double *pVal);
	STDMETHOD(Stop)();
	STDMETHOD(StartPreview)(/*[in]*/ long ParentHwnd, long x, long y, long width, long height, /*[out, retval]*/ VARIANT_BOOL * pResult);

	HRESULT OnDraw(ATL_DRAWINFO& di)
	{
		RECT& rc = *(RECT*)di.prcBounds;
		DrawIcon(di.hdcDraw, rc.left, rc.top, m_hIcon);

		return S_OK;
	}

private:
	HICON	 m_hIcon;
	CDESEdit m_videoEdit;
	CVideoClip* m_pClip;
};

#endif //__VIDEOEDITOBJ_H_
