// MediaFileList.cpp: Implementierung der Klasse CMediaFileList.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "VideoEdit.h"
#include "videoeditobj.h"
#include "mediafile.h"
#include "MediaFileList.h"

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

CMediaFileList::CMediaFileList() : m_audioList("Audio Files"),
								   m_videoList("Video Files")
{

}

CMediaFileList::~CMediaFileList()
{

}

HRESULT CMediaFileList::AddAudioFile(BSTR FilePath, IMediaFile **ppResult)
{
	HRESULT hr = CoCreateInstance(CLSID_MediaFile, NULL, 
							  CLSCTX_INPROC_SERVER, 
							  IID_IMediaFile, 
							  (void **)ppResult);

	if (FAILED(hr) || *ppResult == NULL)
		return E_POINTER;
	
	(*ppResult)->AddRef();
	(*ppResult)->put_FilePath(FilePath);
	
	double dDuration = 0;
	hr = GetFileInfo(FilePath, 0, &dDuration, 0, 0, 0, 0, 0, 0);
	
	if (SUCCEEDED(hr))
	{
		(*ppResult)->put_Duration(dDuration);
	}
	
	(*ppResult)->put_StartOffset(GetCurrentAudioLength());

	m_audioList.AddTail(*ppResult);
	
	(*ppResult)->AddRef();

	return S_OK;
}


HRESULT CMediaFileList::GetFileInfo(BSTR Filename, double *pFramerate, double *pDuration, VARIANT_BOOL *pVideoStreamAvailable, VARIANT_BOOL *pAudioStreamAvailable, long *pWidth, long *pHeight, long *pBitrate, BSTR *pPosterFramePath)
{
	if (pFramerate)
		*pFramerate = 0;
	
	if (pVideoStreamAvailable)
		*pVideoStreamAvailable = VARIANT_TRUE;
	
	if (pAudioStreamAvailable)
		*pAudioStreamAvailable = VARIANT_TRUE;
	
	if (pWidth)
		*pWidth = 0;
	
	if (pHeight)
		*pHeight = 0;
	
	if (pDuration)
		*pDuration = 0;

	HRESULT hr = S_OK;
	CComPtr<IMediaDet> pDet;
	
	hr = pDet.CoCreateInstance(__uuidof(MediaDet));
	if (FAILED(hr))
		return S_OK;

	hr = pDet->put_Filename(Filename);
	if (FAILED(hr))
		return S_OK;
	
	if (pVideoStreamAvailable)
		*pVideoStreamAvailable = VARIANT_FALSE;
	if (pAudioStreamAvailable)
		*pAudioStreamAvailable = VARIANT_FALSE;

	GUID videoSubtype = {0};
	long iAudioStream = 0;
	long lStreams;
	bool bFound = false;
	hr = pDet->get_OutputStreams(&lStreams);
	for (long i = 0; i < lStreams; i++)
	{
		GUID major_type;
		hr = pDet->put_CurrentStream(i);
		hr = pDet->get_StreamType(&major_type);
		if (major_type == MEDIATYPE_Video)  // Found a video stream.
		{
			if (pVideoStreamAvailable)
				*pVideoStreamAvailable = VARIANT_TRUE;
			
			if (pFramerate)
				pDet->get_FrameRate(pFramerate);
			
			if (pDuration)
				pDet->get_StreamLength(pDuration);
				
			AM_MEDIA_TYPE mt;
			hr = pDet->get_StreamMediaType(&mt);
			VIDEOINFOHEADER *pVih = (VIDEOINFOHEADER*)(mt.pbFormat);
			
			videoSubtype = mt.subtype;
				
			if (pWidth)
				*pWidth = pVih->bmiHeader.biWidth;
			
			if (pHeight)
				*pHeight = pVih->bmiHeader.biHeight;
			
			if (pBitrate)
				*pBitrate = pVih->dwBitRate;
			
			if (pHeight)
				if (*pHeight < 0) *pHeight *= -1;

			FreeMediaType(mt);
		}
		else if (major_type == MEDIATYPE_Audio)
		{
			iAudioStream = i;

			if (pAudioStreamAvailable)
				*pAudioStreamAvailable = VARIANT_TRUE;

			if (lStreams == 1 || pDuration && *pDuration == 0)
				if (pDuration)
					pDet->get_StreamLength(pDuration);
		}
	}
	
	if (pPosterFramePath)
	{
		char szTmp[MAX_PATH];
		GetTempPath(MAX_PATH, szTmp);
		strcat(szTmp, "videdit_poster.bmp");
		
		DeleteFile(szTmp);
		
		CComBSTR str = szTmp;
		str.CopyTo(pPosterFramePath);
		
		// USES_CONVERSION;

	//	if (pVideoStreamAvailable == NULL | *pVideoStreamAvailable == VARIANT_TRUE)
		{

			//char* pstrFile = W2A(Filename);
			// _strlwr(pstrFile);

			if (videoSubtype == MEDIASUBTYPE_Asf ||
				wcsstr(Filename, L"asf") || 
				wcsstr(Filename, L"wmv") ||
				wcsstr(Filename, L"ASF") || 
				wcsstr(Filename, L"WMV"))
			{
				pDet->WriteBitmapBits(0, 80, 60, str);
			}
			else
				pDet->WriteBitmapBits(1, 80, 60, str);
		}
//		else
//		{
			// we only have audio
//			pDet->put_CurrentStream(iAudioStream);

		//pDet->get_StreamLength(pDuration);
		//}
	}
	

	return S_OK;
}

double CMediaFileList::GetCurrentAudioLength()
{
	double dResult = 0;
	POSITION pos = m_audioList.GetHeadPosition();
	IMediaFile* pMediaFile = m_audioList.GetNext(pos);

	while (pMediaFile)
	{
		double d = 0;
		pMediaFile->get_Duration(&d);
		dResult += d;

		pMediaFile = m_audioList.GetNext(pos);
	}

	return dResult;
}

double CMediaFileList::GetCurrentVideoLength()
{
	double dResult = 0;
	POSITION pos = m_videoList.GetHeadPosition();
	IMediaFile* pMediaFile = m_videoList.GetNext(pos);

	while (pMediaFile)
	{
		double d = 0;
		pMediaFile->get_Duration(&d);
		dResult += d;

		pMediaFile = m_videoList.GetNext(pos);
	}

	return dResult;
}


long CMediaFileList::GetAudioFileCount()
{
	return m_audioList.GetCount();
}

IMediaFile* CMediaFileList::GetVideoItem(long nIndex)
{
	POSITION pos = m_videoList.GetHeadPosition();
	
	int nStep = 0;

	IMediaFile* pMediaFile = m_videoList.GetNext(pos);
	while (pMediaFile)
	{
		if (nStep == nIndex)
		{
			return pMediaFile;
		}

		pMediaFile = m_videoList.GetNext(pos);
		nStep++;
	}

	return NULL;
}

IMediaFile* CMediaFileList::GetAudioItem(long nIndex)
{
	POSITION pos = m_audioList.GetHeadPosition();
	
	int nStep = 0;

	IMediaFile* pMediaFile = m_audioList.GetNext(pos);
	while (pMediaFile)
	{
		if (nStep == nIndex)
		{
			return pMediaFile;
		}

		pMediaFile = m_audioList.GetNext(pos);
		nStep++;
	}

	return NULL;
}

HRESULT CMediaFileList::AddVideoFile(BSTR FilePath, IMediaFile **ppResult)
{
	HRESULT hr = CoCreateInstance(CLSID_MediaFile, NULL, 
							  CLSCTX_INPROC_SERVER, 
							  IID_IMediaFile, 
							  (void **)ppResult);

	if (FAILED(hr) || *ppResult == NULL)
		return E_POINTER;
	
	(*ppResult)->AddRef();
	(*ppResult)->put_FilePath(FilePath);
	
	CComBSTR strPosterPath;
	double dDuration = 0;
	hr = GetFileInfo(FilePath, 0, &dDuration, 0, 0, 0, 0, 0, &strPosterPath);
	
	if (SUCCEEDED(hr))
	{
		(*ppResult)->put_Duration(dDuration);
	}
	
	(*ppResult)->put_PosterFramePath(strPosterPath);
	(*ppResult)->put_StartOffset(GetCurrentVideoLength());

	if (dDuration == 0.0)
	{
		(*ppResult)->put_IsImage(VARIANT_TRUE);
		(*ppResult)->put_Duration(7);
	}
	else
		(*ppResult)->put_IsImage(VARIANT_FALSE);

//	USES_CONVERSION;
	DeleteFileW(strPosterPath);

	m_videoList.AddTail(*ppResult);
	
	(*ppResult)->AddRef();

	return S_OK;
}

long CMediaFileList::GetVideoFileCount()
{
	return m_videoList.GetCount();
}

void CMediaFileList::VerifyVisualMediaOffsets()
{
	// this function looks through the media lists
	// and reconstucts the offsets

	double dCurrent = 0;
	double dDuration = 0;
	double dTransitionLength = 0;

	bool bFirst = true;

	POSITION pos = m_videoList.GetHeadPosition();
	if (pos == NULL) return;

	IMediaFile* pMediaFile = m_videoList.GetNext(pos);
	while (pMediaFile)
	{
		// take transition length, and subtract from NEXT file
		dCurrent -= dTransitionLength; 
		 
		pMediaFile->put_StartOffset(bFirst ? 0 : dCurrent);
		pMediaFile->get_Duration(&dDuration);
		pMediaFile->get_TransitionLength(&dTransitionLength);

		dCurrent += dDuration;

		pMediaFile = m_videoList.GetNext(pos);
		bFirst = false;
	}
}

void CMediaFileList::SpaceImages(int iStartAudioItem, int iEndAudioItem)
{
	if (GetVideoFileCount() < 1)
		return;

	double dAudioLength = 0;

	int iIndex = 0;
	POSITION pos = m_audioList.GetHeadPosition();
	IMediaFile* pMediaFile = m_audioList.GetNext(pos);
	while (pMediaFile)
	{
		double d = 0;
		pMediaFile->get_Duration(&d);

		if (iIndex >= iStartAudioItem && iIndex <= iEndAudioItem)
			dAudioLength += d;

		pMediaFile = m_audioList.GetNext(pos);
		iIndex++;
	}

	long   nImageCount = 0;
	double dVideoLength = 0;
	double dImageLength = 0;
	double dTransition  = 0;

	pos = m_videoList.GetHeadPosition();

	pMediaFile = m_videoList.GetNext(pos);
	while (pMediaFile)
	{
		VARIANT_BOOL bIsImage = VARIANT_FALSE;
		pMediaFile->get_IsImage(&bIsImage);
	
		double dLength = 0;
		pMediaFile->get_Duration(&dLength);
		pMediaFile->get_TransitionLength(&dTransition);

		if (bIsImage == VARIANT_TRUE)
		{
			dImageLength += dLength;
			nImageCount++;
		}
		else
			dVideoLength += dLength;
		
		pMediaFile = m_videoList.GetNext(pos);

		if (pMediaFile)
			dImageLength -= dTransition;
	}

	// At this point, we have the combined length of the
	// video as well as the images. We do not change the length
	// of the video, since we cannot anyways, but we only adjust
	// the length of the photos to accomodate the entire audio

	if (nImageCount == 0)
		return;

	double dImageCombined = dAudioLength - dVideoLength;
	double dImageSingle = dImageCombined / nImageCount;

	// dImageSingle is the fractional lenght of each image clip
	SetAllImageDurations(dImageSingle, true);

	ASSERT((long)(dImageSingle * nImageCount) == (long)dAudioLength);
}

void CMediaFileList::SetAllImageDurations(double dDuration, bool bConsiderTransitions)
{
	double dTransition = 0;

	POSITION pos = m_videoList.GetHeadPosition();
	IMediaFile* pMediaFile = m_videoList.GetNext(pos);
	while (pMediaFile)
	{
		VARIANT_BOOL bIsImage = VARIANT_FALSE;
		pMediaFile->get_IsImage(&bIsImage);
		
		if (bIsImage == VARIANT_TRUE)
		{
			if (bConsiderTransitions)
				pMediaFile->put_Duration(dDuration + dTransition);
			else
				pMediaFile->put_Duration(dDuration);
		}
		
		pMediaFile->get_TransitionLength(&dTransition);
		pMediaFile = m_videoList.GetNext(pos);
	}
}

HRESULT CMediaFileList::AddAudioFile(IMediaFile **ppResult)
{
	HRESULT hr = CoCreateInstance(CLSID_MediaFile, NULL, 
							  CLSCTX_INPROC_SERVER, 
							  IID_IMediaFile, 
							  (void **)ppResult);

	if (FAILED(hr) || *ppResult == NULL)
		return E_POINTER;
	
	(*ppResult)->AddRef();
	m_audioList.AddTail(*ppResult);
	(*ppResult)->AddRef();

	return hr;
}

//DEL HRESULT CMediaFileList::AddVideoFile(IMediaFile **ppResult)
//DEL {
//DEL 	HRESULT hr = CoCreateInstance(CLSID_MediaFile, NULL, 
//DEL 							  CLSCTX_INPROC_SERVER, 
//DEL 							  IID_IMediaFile, 
//DEL 							  (void **)ppResult);
//DEL 
//DEL 	if (FAILED(hr) || *ppResult == NULL)
//DEL 		return E_POINTER;
//DEL 	
//DEL 	(*ppResult)->AddRef();
//DEL 	(*ppResult)->put_FilePath(FilePath);
//DEL 	
//DEL 	CComBSTR strPosterPath;
//DEL 	double dDuration = 0;
//DEL 	hr = GetFileInfo(FilePath, 0, &dDuration, 0, 0, 0, 0, 0, &strPosterPath);
//DEL 	
//DEL 	if (SUCCEEDED(hr))
//DEL 	{
//DEL 		(*ppResult)->put_Duration(dDuration);
//DEL 	}
//DEL 	
//DEL 	(*ppResult)->put_PosterFramePath(strPosterPath);
//DEL 	(*ppResult)->put_StartOffset(GetCurrentVideoLength());
//DEL 
//DEL 	if (dDuration == 0.0)
//DEL 	{
//DEL 		(*ppResult)->put_IsImage(VARIANT_TRUE);
//DEL 		(*ppResult)->put_Duration(7);
//DEL 	}
//DEL 	else
//DEL 		(*ppResult)->put_IsImage(VARIANT_FALSE);
//DEL 
//DEL 	USES_CONVERSION;
//DEL 	DeleteFile(W2A(strPosterPath));
//DEL 
//DEL 	m_videoList.AddTail(*ppResult);
//DEL 	
//DEL 	(*ppResult)->AddRef();
//DEL 
//DEL }
