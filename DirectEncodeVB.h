// DirectEncodeVB.h : Declaration of the CDirectEncodeVB

#ifndef __DIRECTENCODEVB_H_
#define __DIRECTENCODEVB_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CDirectEncodeVB
class ATL_NO_VTABLE CDirectEncodeVB : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CDirectEncodeVB, &CLSID_DirectEncodeVB>,
	public IDispatchImpl<IDirectEncodeVB, &IID_IDirectEncodeVB, &LIBID_StandardMpegEncoderLib>
{
public:
	CDirectEncodeVB()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_DIRECTENCODEVB)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CDirectEncodeVB)
	COM_INTERFACE_ENTRY(IDirectEncodeVB)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// IDirectEncodeVB
public:
	STDMETHOD(PassThru)(/*[in]*/ long nVal);
};

#endif //__DIRECTENCODEVB_H_
