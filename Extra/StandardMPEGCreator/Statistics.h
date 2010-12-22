// Statistics.h : Declaration of the CStatistics

#ifndef __STATISTICS_H_
#define __STATISTICS_H_

#include "resource.h"       // main symbols
#include "convert.h"

/////////////////////////////////////////////////////////////////////////////
// CStatistics
class ATL_NO_VTABLE CStatistics : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CStatistics, &CLSID_Statistics>,
	public IDispatchImpl<IStatistics, &IID_IStatistics, &LIBID_STANDARDMPEGCREATORLib>
{
public:
	CStatistics() : m_pConvert(NULL)
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_STATISTICS)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CStatistics)
	COM_INTERFACE_ENTRY(IStatistics)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// IStatistics
public:
	STDMETHOD(get_TimeElapsed)(/*[out, retval]*/ double *pVal);
	STDMETHOD(get_EncodeFramerate)(/*[out, retval]*/ long *pVal);
	STDMETHOD(get_FramesEncoded)(/*[out, retval]*/ long *pVal);
	STDMETHOD(SetInstance)(/*[in]*/ long Ptr);
	STDMETHOD(get_Duration)(/*[out, retval]*/ double *pVal);
	STDMETHOD(get_Progress)(/*[out, retval]*/ double *pVal);

private:
	CConvert* m_pConvert;
};

#endif //__STATISTICS_H_
