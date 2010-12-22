// StandardMPEGEncoderVB.cpp : Implementation of CStandardMPEGEncoderVB
#include "stdafx.h"
#include "DirectEncodeVB.h"
#include "StandardMPEGEncoderVB.h"

/////////////////////////////////////////////////////////////////////////////
// CStandardMPEGEncoderVB

// initguid to prevent unresolved external when adding guids
#include <initguid.h>


#define REGISTER_IN_GRAPH

HRESULT AddToRot(IUnknown *pUnkGraph, DWORD *pdwRegister) 
{
#if defined(REGISTER_IN_GRAPH)
    IMoniker * pMoniker;
    IRunningObjectTable *pROT;
    if (FAILED(GetRunningObjectTable(0, &pROT))) {
        return E_FAIL;
    }
    WCHAR wsz[256];
    wsprintfW(wsz, L"FilterGraph %08p pid %08x", (DWORD_PTR)pUnkGraph, GetCurrentProcessId());
    HRESULT hr = CreateItemMoniker(L"!", wsz, &pMoniker);
    if (SUCCEEDED(hr)) {
        hr = pROT->Register(0, pUnkGraph, pMoniker, pdwRegister);
        pMoniker->Release();
    }
    pROT->Release();
#endif
    return S_OK;
}

void RemoveFromRot(DWORD pdwRegister)
{
#if defined(REGISTER_IN_GRAPH)
	IRunningObjectTable *pROT;
    if (SUCCEEDED(GetRunningObjectTable(0, &pROT))) {
        pROT->Revoke(pdwRegister);
        pROT->Release();
    }
#endif
}

void PromptForGraph(IGraphBuilder* pGraph, _TCHAR* pszGraphType)
{
#if defined(REGISTER_IN_GRAPH)
	DWORD dwGraphRegister = 0;
	AddToRot(pGraph, &dwGraphRegister);

	_TCHAR szMsg[1024];
	_tcscpy(szMsg, _T("You can connect to the "));
	_tcscat(szMsg, pszGraphType);
	_tcscat(szMsg, _T(" Graph right now. This is NOT an error."));

	MessageBox(::GetDesktopWindow(), szMsg, 
			   _T("Developer information"),
				MB_ICONINFORMATION|MB_OK|
				MB_SETFOREGROUND|MB_SYSTEMMODAL);

	RemoveFromRot(dwGraphRegister);
#endif
}


// CLSIDs
#include "..\StandardMPEGEncoderUIDs.h"


STDMETHODIMP CStandardMPEGEncoderVB::Test()
{
	MessageBox(0, _T("Test()"), 0, 0);

	return S_OK;
}

STDMETHODIMP CStandardMPEGEncoderVB::CheckObjects(VARIANT_BOOL *pb)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CStandardMPEGEncoderVB::SetObject(IUnknown *pUnk)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CStandardMPEGEncoderVB::CreateFilter()
{
	HRESULT hr = CoCreateInstance(CLSID_StandardMpegEncoder, NULL, 
								  CLSCTX_INPROC_SERVER, 
								  IID_IBaseFilter, 
								  (void **)&m_pMPEGWriter);
	
	if (FAILED(hr))
	{
		return hr;
	}


	hr = m_pMPEGWriter->QueryInterface(__uuidof(IStandardMpegEncoder), (void**)&m_pIMPEGEncoder);
//	ASSERT(m_pIMPEGEncoder);

	return S_OK;
}

STDMETHODIMP CStandardMPEGEncoderVB::GetSMPEG(IStandardMpegEncoder **pEncoder)
{
	m_pIMPEGEncoder.CopyTo(pEncoder);
	m_pIMPEGEncoder.p->AddRef();

	return S_OK;
}

STDMETHODIMP CStandardMPEGEncoderVB::SetOutputFileOnFileWriter(IUnknown *pFileWriter, BSTR FilePath, long* pResult)
{
	CComPtr<IFileSinkFilter > pFileWriterInterface;
	HRESULT hr = pFileWriter->QueryInterface(IID_IFileSinkFilter , (void**)&pFileWriterInterface);

	if (SUCCEEDED(hr) && pFileWriterInterface)
		*pResult = pFileWriterInterface->SetFileName(FilePath, 0);
	else
		*pResult = E_FAIL;

	return S_OK;
}

STDMETHODIMP CStandardMPEGEncoderVB::PromptForGraph(IUnknown *pGraph)
{
	HRESULT hr;
	CComPtr<IBaseFilter> pFilter;
	hr = pGraph->QueryInterface(IID_IBaseFilter, (void**)&pFilter);

	FILTER_INFO info;
	hr = pFilter->QueryFilterInfo(&info);

	CComPtr<IGraphBuilder> pBuilder;
	hr = info.pGraph->QueryInterface(IID_IGraphBuilder, (void**)&pBuilder);

	::PromptForGraph(pBuilder, _T("DirectShow"));


	info.pGraph->Release();

	return S_OK;
}
