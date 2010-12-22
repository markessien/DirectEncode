// VideoRect.h : Deklaration von CVideoRect

#ifndef __VIDEORECT_H_
#define __VIDEORECT_H_

#include "resource.h"       // Hauptsymbole

/////////////////////////////////////////////////////////////////////////////
// CVideoRect
class ATL_NO_VTABLE CVideoRect : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CVideoRect, &CLSID_VideoRect>,
	public IDispatchImpl<IVideoRect, &IID_IVideoRect, &LIBID_VIDEOEDITLib>
{
public:
	CVideoRect()
	{
		nLeft = 0;
		nTop = 0;
		nRight = 0;
		nBottom = 0;
	}

DECLARE_REGISTRY_RESOURCEID(IDR_VIDEORECT)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CVideoRect)
	COM_INTERFACE_ENTRY(IVideoRect)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// IVideoRect
public:
	STDMETHOD(get_Height)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_Height)(/*[in]*/ long newVal);
	STDMETHOD(get_Width)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_Width)(/*[in]*/ long newVal);
	STDMETHOD(get_Bottom)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_Bottom)(/*[in]*/ long newVal);
	STDMETHOD(get_Left)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_Left)(/*[in]*/ long newVal);
	STDMETHOD(get_Top)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_Top)(/*[in]*/ long newVal);
	STDMETHOD(get_Right)(/*[out, retval]*/ long *pVal);
	STDMETHOD(put_Right)(/*[in]*/ long newVal);

private:
	long nLeft;
	long nTop;
	long nRight;
	long nBottom;
};

#endif //__VIDEORECT_H_
