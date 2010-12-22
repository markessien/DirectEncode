// Settings.h : Declaration of the CSettings

#ifndef __SETTINGS_H_
#define __SETTINGS_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CSettings
class ATL_NO_VTABLE CSettings : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSettings, &CLSID_Settings>,
	public IDispatchImpl<ISettings, &IID_ISettings, &LIBID_STANDARDMPEGCREATORLib>
{
public:
	CSettings()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_SETTINGS)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CSettings)
	COM_INTERFACE_ENTRY(ISettings)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// ISettings
public:
};

#endif //__SETTINGS_H_
