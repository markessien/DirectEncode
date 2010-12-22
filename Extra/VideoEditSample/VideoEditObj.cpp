// VideoEditObj.cpp : Implementierung von CVideoEditObj

#include "stdafx.h"
#include "VideoEdit.h"
#include "mediafile.h"
#include "VideoEditObj.h"
#include "videoclip.h"


/////////////////////////////////////////////////////////////////////////////
// CVideoEditObj


STDMETHODIMP CVideoEditObj::StartPreview(long ParentHwnd, long x, long y, long width, long height, VARIANT_BOOL *pResult)
{
	CHelper::Trace("StartPreview\n");

	if (m_pClip)
	{
		m_videoEdit.ConstructGraph(m_pClip->GetMediaFileList(), 1);
		m_videoEdit.Preview(ParentHwnd, x, y, width, height);
	}
	else
		MessageBox("Please specify a clip");

	return S_OK;
}


STDMETHODIMP CVideoEditObj::Stop()
{
	CHelper::Trace("Stop\n");
	m_videoEdit.Stop();

	return S_OK;
}


STDMETHODIMP CVideoEditObj::get_Progress(double *pVal)
{
	CHelper::Trace("get_Progress\n");
	*pVal = m_videoEdit.GetProgress();

	return S_OK;
}

STDMETHODIMP CVideoEditObj::get_Duration(double *pVal)
{
	CHelper::Trace("get_Duration\n");
	*pVal = m_videoEdit.GetDuration();

	return S_OK;
}

STDMETHODIMP CVideoEditObj::CompileToFile(BSTR OutputPath, long Format, VARIANT_BOOL *pResult)
{
	CHelper::Trace("CompileToFile\n");
	*pResult = VARIANT_TRUE;

	HRESULT hr;

	if (m_pClip)
	{
		hr = m_videoEdit.ConstructGraph(m_pClip->GetMediaFileList(), Format);

		if (FAILED(hr))
			*pResult = VARIANT_FALSE;

		hr = m_videoEdit.OutputToFile(OutputPath);
		
		if (FAILED(hr))
			*pResult = VARIANT_FALSE;
	}
	else
		MessageBox("Please specify a clip");


	return S_OK;
}

STDMETHODIMP CVideoEditObj::EnumerateTransitions()
{
	CHelper::Trace("EnumerateTransitions\n");
	HRESULT hr;
	CComPtr<ICreateDevEnum> pCreateDevEnum;
	CComPtr<IEnumMoniker>   pEnumMoniker;

	Fire_TransitionListed(CComBSTR(L"No Transition"), L"");

	hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC_SERVER,
				     IID_ICreateDevEnum, (void**)&pCreateDevEnum);

	if (FAILED(hr))
		return S_OK;

	hr = pCreateDevEnum->CreateClassEnumerator(CLSID_VideoEffects2Category, &pEnumMoniker, 0);
	
	if (FAILED(hr) || pEnumMoniker == NULL)
		return S_OK;

	CComPtr <IBindCtx> pBindCtx;
	CreateBindCtx(0, &pBindCtx);

	ULONG cFetched;
	CComPtr<IMoniker> pMoniker;
	while(S_OK == pEnumMoniker->Next(1, &pMoniker, &cFetched))
	{
		HRESULT hr;
		CComPtr<IPropertyBag> pBag;
		hr = pMoniker->BindToStorage(0, 0, IID_IPropertyBag, (void **)&pBag);
		
		if(SUCCEEDED(hr))
		{
			VARIANT var;
			var.vt = VT_BSTR;
			hr = pBag->Read(OLESTR("FriendlyName"), &var, NULL);
			
			if (SUCCEEDED(hr))
			{
				CComBSTR strName = var.bstrVal;

                VARIANT var2;
				var2.vt = VT_BSTR;
                hr = pBag->Read(OLESTR("guid"), &var2, NULL);

				CComBSTR strGuid = var2.bstrVal;
                SysFreeString(var2.bstrVal);

				Fire_TransitionListed(strName, strGuid);
            }

            SysFreeString(var.bstrVal);
        }
        pBag = NULL;

		pMoniker = NULL;
    }

	return S_OK;
}


STDMETHODIMP CVideoEditObj::get_CurrentClip(IVideoClip **pVal)
{
	CHelper::Trace("get_CurrentClip\n");
	*pVal = NULL;
	*pVal = (IVideoClip*)m_pClip;
	if (*pVal) (*pVal)->AddRef();

	return S_OK;
}

STDMETHODIMP CVideoEditObj::put_CurrentClip(IVideoClip **newVal)
{
	CHelper::Trace("put_CurrentClip\n");
	if (m_pClip)
	{
		m_pClip->Release();
		m_pClip = NULL;
	}

	IVideoClip* pClip = *newVal;
	m_pClip = (CVideoClip*)pClip;

	if (m_pClip)
		m_pClip->AddRef();

	return S_OK;
}

STDMETHODIMP CVideoEditObj::InsertTemplate(IVideoClip **pVideoClip)
{
	// this function merges this clip with another one

	return S_OK;
}
