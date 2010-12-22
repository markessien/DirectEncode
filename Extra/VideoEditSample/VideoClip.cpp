// VideoClip.cpp : Implementierung von CVideoClip
#include "stdafx.h"
#include "VideoEdit.h"
#include "VideoClip.h"
#include <stdio.h>

#include "helper.h"

/////////////////////////////////////////////////////////////////////////////
// CVideoClip


STDMETHODIMP CVideoClip::AddAudio(long Index, BSTR Path, IMediaFile **ppResult)
{
	CHelper::Trace("Addaudio\n");

	m_mediaList.AddAudioFile(Path, ppResult);

	return S_OK;
}

STDMETHODIMP CVideoClip::AddVideo(long Index, BSTR Path, IMediaFile **ppResult)
{
	CHelper::Trace("AddVideo\n");
	m_mediaList.AddVideoFile(Path, ppResult);

	return S_OK;
}

STDMETHODIMP CVideoClip::RemoveVideo(long Index)
{
	// ZU ERLEDIGEN: Implementierungscode hier hinzufügen

	return S_OK;
}

STDMETHODIMP CVideoClip::RemoveAudio(long Index)
{
	// ZU ERLEDIGEN: Implementierungscode hier hinzufügen

	return S_OK;
}

STDMETHODIMP CVideoClip::SaveClip(BSTR Path)
{
	CHelper::Trace("SaveClip\n");

	HRESULT hr = S_OK;
    MSXML::IXMLDOMDocument*  pDoc = NULL;
	MSXML::IXMLDOMNode*      pRootNode = NULL;
    MSXML::IXMLDOMNode*      pNode = NULL;
	MSXML::IXMLDOMNode*      pNode2 = NULL;
	MSXML::IXMLDOMNode*      pNodeFiles = NULL;
	MSXML::IXMLDOMElement*   pElement = NULL;

	 // Create an empty XML document
    hr = CoCreateInstance(MSXML::CLSID_DOMDocument, NULL, CLSCTX_INPROC_SERVER,
                          MSXML::IID_IXMLDOMDocument, (void**)&pDoc);
	
	hr = pDoc->createElement(L"VideoClip", &pElement);
	pDoc->appendChild(pElement, &pRootNode);
	
	hr = pDoc->createElement(L"VideoFiles", &pElement);
	pRootNode->appendChild(pElement, &pNodeFiles);

	int i = 0;
	for (i=0;i<m_mediaList.GetVideoFileCount();i++)
	{
		wchar_t wszName[50] = {0};
		swprintf(wszName, L"File%lu", i);

		pDoc->createElement(wszName, &pElement);
		pNodeFiles->appendChild(pElement, &pNode);
		
		// FilePath
		pDoc->createElement(L"FilePath", &pElement);
		pNode->appendChild(pElement, &pNode2);

		CComBSTR strPath;
		m_mediaList.GetVideoItem(i)->get_FilePath(&strPath);
		pElement->put_text(strPath);

		// Duration
		pDoc->createElement(L"Duration", &pElement);
		pNode->appendChild(pElement, &pNode2);

		double dDuration = 0;
		m_mediaList.GetVideoItem(i)->get_Duration(&dDuration);

		wchar_t wszDuration[50] = {0};
		swprintf(wszDuration, L"%.10f", dDuration);
		pElement->put_text(wszDuration);

		// Transition
		pDoc->createElement(L"Transition", &pElement);
		pNode->appendChild(pElement, &pNode2);

		CComBSTR strTransition;
		m_mediaList.GetVideoItem(i)->get_Transition(&strTransition);
		pElement->put_text(strTransition);

		// Transition length
		pDoc->createElement(L"TransitionLength", &pElement);
		pNode->appendChild(pElement, &pNode2);

		double dLength = 0;
		m_mediaList.GetVideoItem(i)->get_TransitionLength(&dLength);

		wchar_t wszLength[50] = {0};
		swprintf(wszLength, L"%.10f", dLength);
		pElement->put_text(wszLength);
	}


	hr = pDoc->createElement(L"AudioFiles", &pElement);
	pRootNode->appendChild(pElement, &pNodeFiles);

	for (i=0;i<m_mediaList.GetAudioFileCount();i++)
	{
		wchar_t wszName[50] = {0};
		swprintf(wszName, L"File%lu", i);

		pDoc->createElement(wszName, &pElement);
		pNodeFiles->appendChild(pElement, &pNode);
		
		// FilePath
		pDoc->createElement(L"FilePath", &pElement);
		pNode->appendChild(pElement, &pNode2);

		CComBSTR strPath;
		m_mediaList.GetAudioItem(i)->get_FilePath(&strPath);
		pElement->put_text(strPath);

		// Duration
		pDoc->createElement(L"Duration", &pElement);
		pNode->appendChild(pElement, &pNode2);

		double dDuration = 0;
		m_mediaList.GetAudioItem(i)->get_Duration(&dDuration);

		wchar_t wszDuration[50] = {0};
		swprintf(wszDuration, L"%.10f", dDuration);
		pElement->put_text(wszDuration);
	}

	CComBSTR strSavePath = Path;
	CComVariant var;
	var.ChangeType(VT_BSTR);
	strSavePath.CopyTo(&var.bstrVal);
	hr = pDoc->save(var);

	return S_OK;
}

STDMETHODIMP CVideoClip::LoadClip(BSTR Path)
{
	CHelper::Trace("LoadClip\n");
	USES_CONVERSION;

	HRESULT hr = S_OK;
    MSXML::IXMLDOMDocument*  pDoc = NULL;
    MSXML::IXMLDOMNode*      pNode = NULL;
	MSXML::IXMLDOMElement*   pElement = NULL;

	 // Create an empty XML document
    hr = CoCreateInstance(MSXML::CLSID_DOMDocument, NULL, CLSCTX_INPROC_SERVER,
                          MSXML::IID_IXMLDOMDocument, (void**)&pDoc);

	CComVariant var;
	var.ChangeType(VT_BSTR);

	CComBSTR strPath = Path;
	strPath.CopyTo(&var.bstrVal);

	VARIANT_BOOL bSuccess;
	pDoc->put_async(VARIANT_FALSE);
	hr = pDoc->load(var, &bSuccess);

	if (bSuccess == VARIANT_FALSE)
		return S_OK;

	pDoc->get_documentElement(&pElement);
	
	MSXML::IXMLDOMNodeList* pNodeList = NULL;
	pElement->get_childNodes(&pNodeList);

	long lCount;
	pNodeList->get_length(&lCount);
	for (int i=0;i<lCount;i++)
	{
		// This will list video and audio

		MSXML::IXMLDOMNode* pRootNode = NULL;
		pNodeList->get_item(i, &pRootNode);
		
		CComBSTR bstrNodeName;
		pRootNode->get_nodeName(&bstrNodeName);

		if (_wcsicmp(bstrNodeName, L"VideoFiles") == 0)
		{
			// Here we are going through each file
			MSXML::IXMLDOMNodeList* pUnderNodeList = NULL;
			pRootNode->get_childNodes(&pUnderNodeList);

			long lCount;
			pUnderNodeList->get_length(&lCount);

			for (int k=0;k<lCount;k++)
			{
				MSXML::IXMLDOMNode* pFileNode = NULL;
				pUnderNodeList->get_item(k, &pFileNode);
				
				//We should loop through the items (like duration) now.
				MSXML::IXMLDOMNodeList* pItemNodeList = NULL;
				pFileNode->get_childNodes(&pItemNodeList);
				
				IMediaFile* pItem = NULL;
				long lItemCount;
				pItemNodeList->get_length(&lItemCount);
				for (int g=0;g<lItemCount;g++)
				{
					MSXML::IXMLDOMNode* pSubItemNode = NULL;
					pItemNodeList->get_item(g, &pSubItemNode);
					
					CComBSTR bstrName;
					pSubItemNode->get_nodeName(&bstrName);

					if (_wcsicmp(bstrName, L"FilePath") == 0)
					{
						CComBSTR bstrPath;
						pSubItemNode->get_text(&bstrPath);

						m_mediaList.AddVideoFile(bstrPath, &pItem);
					}
					
					if (_wcsicmp(bstrName, L"Duration") == 0)
					{
						CComBSTR bstrDuration;
						pSubItemNode->get_text(&bstrDuration);
					//	if (pItem) pItem->put_Duration(atof(W2A(bstrDuration)));
					}

					if (_wcsicmp(bstrName, L"Transition") == 0)
					{
						CComBSTR bstrTransition;
						pSubItemNode->get_text(&bstrTransition);
						if (pItem) pItem->put_Transition(bstrTransition);
					}

					if (_wcsicmp(bstrName, L"TransitionLength") == 0)
					{
						CComBSTR bstrDuration;
						pSubItemNode->get_text(&bstrDuration);
					//	if (pItem) pItem->put_TransitionLength(atof(W2A(bstrDuration)));
					}
				}
			}
		}

		if (_wcsicmp(bstrNodeName, L"AudioFiles") == 0)
		{

		}
	}

	return S_OK;
}

STDMETHODIMP CVideoClip::get_AudioLength(double *pVal)
{
	CHelper::Trace("get_AudioLength\n");
	*pVal = m_mediaList.GetCurrentAudioLength();

	return S_OK;
}

STDMETHODIMP CVideoClip::get_AudioCount(long *pVal)
{
	CHelper::Trace("get_AudioCount\n");
	*pVal = m_mediaList.GetAudioFileCount();

	return S_OK;
}

STDMETHODIMP CVideoClip::get_MediaFile(MediaFormat format, long ItemIndex, IMediaFile **pVal)
{
	CHelper::Trace("get_MediaFile\n");

	*pVal = NULL;

	if (format == formatAudio)
	{
		*pVal = m_mediaList.GetAudioItem(ItemIndex);
		if (*pVal) (*pVal)->AddRef();
	}
	else
	{
		*pVal = m_mediaList.GetVideoItem(ItemIndex);
		if (*pVal) (*pVal)->AddRef();
	}


	return S_OK;
}

STDMETHODIMP CVideoClip::ForcePhotoDurations(double NewDuration)
{
	CHelper::Trace("ForcePhotoDurations\n");
	m_mediaList.SetAllImageDurations(NewDuration, false);

	return S_OK;
}

STDMETHODIMP CVideoClip::SpacePhotosToAudio(int iStartAudioItem, int iEndAudioItem)
{
	CHelper::Trace("SpacePhotosToAudio\n");
	m_mediaList.SpaceImages(iStartAudioItem, iEndAudioItem);

	return S_OK;
}

STDMETHODIMP CVideoClip::get_VideoCount(long *pVal)
{
	CHelper::Trace("get_VideoCount\n");
	*pVal = m_mediaList.GetVideoFileCount();

	return S_OK;
}

STDMETHODIMP CVideoClip::get_VideoLength(double *pVal)
{
	CHelper::Trace("get_VideoLength\n");
	*pVal = m_mediaList.GetCurrentVideoLength();

	return S_OK;
}

CMediaFileList* CVideoClip::GetMediaFileList()
{
	CHelper::Trace("GetMediaFileList\n");
	return &m_mediaList;
}
