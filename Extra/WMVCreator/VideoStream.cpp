#include "StdAfx.h"
#include "videostream.h"

CVideoStream::CVideoStream(void)
{
	m_nKeyFramerate = 15;
	m_dFramerate = 0;
	m_nVideoX = 0;
    m_nVideoY = 0;
	m_nKeyframe = 0;
    m_nQuality = 0;
	m_nVideoCodec = -2;
	m_nBestVideoCodec = -2;
	m_nSrcX = 0;
	m_nSrcY = 0;
	m_bAutoDimensions = false;
	m_nVBRConstrain = 0;
	m_nMinVideoBitrate = 0;
	m_nMaxVideoBitrate = 0;
	m_bSrcFramerate = false;
	m_bDimFromSrc = false;
	m_fSrcFramerate = 0;
}

CVideoStream::~CVideoStream(void)
{
}

HRESULT CVideoStream::Load(IWMProfile* pWMProfile)
{
	ASSERT(pWMProfile);
	if (pWMProfile == NULL)
		return E_POINTER;

	HRESULT hr;
	CComPtr<IWMStreamConfig> pStreamConfig;
	hr = GetStreamConfig(pWMProfile, WMMEDIATYPE_Video, &pStreamConfig);
	if (FAILED(hr) || pStreamConfig == NULL)
		return E_FAIL;

	CComPtr<IWMVideoMediaProps> pProps = NULL;
	WM_MEDIA_TYPE *pMT = NULL;

	hr = GetStreamMediaType(pStreamConfig, &pProps, &pMT);  
	if( FAILED( hr ) )
	{
		return hr;
	} 

	if (pMT->formattype != WMFORMAT_VideoInfo)
	{
		ASSERT(!"Wrong Media Type. Check this!");
		return hr;
	}

	MapCodec(pMT);

	WMVIDEOINFOHEADER *pVIH = (WMVIDEOINFOHEADER *) pMT->pbFormat;

	//DWORD dwBitrate = 0;
	pStreamConfig->GetBitrate(&m_dwBitrate);
	//nBitrate = dwBitrate;

	m_nVideoX = pVIH->bmiHeader.biWidth;
	m_nVideoY = pVIH->bmiHeader.biHeight;

	m_dFramerate = ((double)UNITS / (double)pVIH->AvgTimePerFrame);
	
	DWORD dwQuality;
	hr = pProps->GetQuality( &dwQuality );
	m_nQuality = dwQuality;
	
	LONGLONG llKeyFrame = 0;
	pProps->GetMaxKeyFrameSpacing(&llKeyFrame);
	m_nKeyframe = (long)((double)llKeyFrame / (double)UNITS);

	wchar_t szDesc[1024];
	swprintf(szDesc, L" [%.2f fps; %lu x %lu]", m_dFramerate, m_nVideoX, m_nVideoY);
	m_strDescription = szDesc;

	delete pMT;

	return hr;
}

long CVideoStream::GetVideoWidth(void)
{
	return m_nVideoX;
}

long CVideoStream::GetVideoHeight(void)
{
	return m_nVideoY;
}

long CVideoStream::GetKeyFrameFreq(void)
{
	return m_nKeyframe;
}

long CVideoStream::GetQuality(void)
{
	return m_nQuality;
}

double CVideoStream::GetFramerate(void)
{
	return m_dFramerate;
}

CComBSTR CVideoStream::GetDescription(void)
{
	return m_strDescription;
}

HRESULT CVideoStream::CreateNew(IWMProfile* pWMProfile)
{
	HRESULT hr = S_OK;

    CComPtr<IWMStreamConfig> pStreamConfig = NULL;

	// a little codec trickery so we use the best codec

	// first,
	long nCodec = -1;
	if (m_nVideoCodec == -2) // if codec is not specified
	{
		if (m_nBestVideoCodec == -2) // if best codec is not specified
			nCodec = 0; // then use the first codec
		else
			m_nVideoCodec  =m_nBestVideoCodec; // else use the best codec
	}
	else
		nCodec = m_nVideoCodec; // if codec is specified, use it

	if (nCodec == -1) // uncompressed
	{
        hr = pWMProfile->CreateNewStream(WMMEDIATYPE_Video, &pStreamConfig);
        if (FAILED(hr )) return hr;
	}
	else
	{
		CComPtr <IWMProfileManager> pIWMProfileManager;
		hr = WMCreateProfileManager(&pIWMProfileManager);
		if(FAILED(hr)) return hr;
		
		CComPtr<IWMCodecInfo2> pICodecInfo;
		hr = pIWMProfileManager->QueryInterface(IID_IWMCodecInfo2, (void**)&pICodecInfo);
		if (!pICodecInfo || FAILED(hr)) return hr;

        hr = pICodecInfo->GetCodecFormat(WMMEDIATYPE_Video, nCodec, 0, &pStreamConfig);
        if (FAILED(hr )) return hr;
    }
   
	CComPtr<IWMVideoMediaProps> pProps;
	WM_MEDIA_TYPE* pMT = NULL;
	hr = GetStreamMediaType(pStreamConfig, &pProps, &pMT);  
    if (FAILED(hr )) return hr;

    if (pMT->formattype != WMFORMAT_VideoInfo )
    {
		_ASSERT(FALSE);
        return E_FAIL;
    }

 
    //IWMStreamConfig: GetBufferWindow (latency)

    
    WMVIDEOINFOHEADER *pVIH = (WMVIDEOINFOHEADER *) pMT->pbFormat;

	int nVideoX = 0; //VideoFormatToPoint().x;
    int nVideoY = 0; //VideoFormatToPoint().y;

	if (m_bAutoDimensions && m_nSrcX && m_nSrcY)
	{
		// in this case, we do not make our video bigger than the source
		nVideoX = m_nVideoX;
		nVideoY = m_nVideoY;

		if (m_nVideoX > m_nSrcX &&
			nVideoY > m_nSrcY)
		{
			// if only one is bigger, we do not change it
			// because then we will have an aspect ratio problem
			nVideoX = m_nSrcX;
			nVideoY = m_nSrcY;
		}
	}
	else if (m_bDimFromSrc)
	{
		nVideoX = m_nSrcX;
		nVideoY = m_nSrcY;
	}
	else
	{
		nVideoX = m_nVideoX;
		nVideoY = m_nVideoY;
	}

	_ASSERT(nVideoX);
	_ASSERT(nVideoY);

//	m_dwBitrate = 1024;

	pVIH->rcSource.right = nVideoX;
	pVIH->rcSource.bottom = nVideoY;
	pVIH->rcTarget.right = nVideoX;
	pVIH->rcTarget.bottom = nVideoY;
	pVIH->bmiHeader.biWidth = nVideoX;
	pVIH->bmiHeader.biHeight = nVideoY;
	pVIH->dwBitRate = m_dwBitrate;

	hr = SetCBRSettings(pStreamConfig);

	/*
	DWORD dwVideoBitrate = 0;
    if (dwVideoBitrate != 0)
    {
        // only for compressed output. WHY????!??

        pVIH->dwBitRate = dwVideoBitrate;
	}*/

	if (m_bAutoFramerate)
	{
		// if the target framerate is larger than the source fps, then
		// use the source fps. This means we do not duplicate frames with
		// absolutely no gain in quality. Example, if we wanted 30fps and 
		// a file with 3 fps comes, the target file will just be the duplication
		// of the 3 frames

		if (m_dFramerate > m_fSrcFramerate)
		{
			m_dFramerate = m_fSrcFramerate;
		}
	}
	else if (m_bSrcFramerate)
	{
		// we want to use the source framerate
		m_dFramerate = m_fSrcFramerate;
	}
	

	pVIH->AvgTimePerFrame = (LONGLONG) ( 10000000.0f / m_dFramerate );

	/*
	long nQuality = 0;
    hr = pProps->SetQuality( nQuality );
    if( FAILED( hr ) )
    {
    }*/

    hr = pProps->SetMaxKeyFrameSpacing( (LONGLONG)(UNITS * m_nKeyFramerate) );
    if( FAILED( hr ) )
    {
    }

    hr = SetStreamBasics( pStreamConfig, 
                          1,
                          L"Video Stream",
                          L"Video",
                          0,
                          pMT );
    if( FAILED( hr ) )
    {
        return hr;
    }
    
	// complicated bitrate settings
	/*
	CComQIPtr<IWMPropertyVault> pPropertyVault(pStreamConfig);
	if (pPropertyVault)
	{
		if (m_bAutoBitrate)
		{
			// try to set the requested bitrate settings. If it fails
			// fall back on the other one
			if (FAILED(SetVBRSettings(pStreamConfig)))
				SetCBRSettings(pStreamConfig);
		}
		else
		{
			if (m_bVBR)
				SetVBRSettings(pStreamConfig);
			else
				SetCBRSettings(pStreamConfig);
		}
	}
	else
		SetCBRSettings(pStreamConfig);
*/
	

    hr = pWMProfile->AddStream( pStreamConfig );
    if( FAILED( hr ) )
    {
        return hr;
    }

    delete pMT;
      
    return( hr );
}


HRESULT CVideoStream::SetCBRSettings(IWMStreamConfig* pStreamConfig)
{
	HRESULT hr = E_FAIL;
	CComQIPtr<IWMPropertyVault> pPropertyVault(pStreamConfig);
	if (pPropertyVault)
	{
		BOOL bEnableVBR = FALSE;
		hr = pPropertyVault->SetProperty(g_wszVBREnabled, WMT_TYPE_BOOL, (BYTE*)&bEnableVBR, sizeof(BOOL));
		
		hr = SetDWORDProperty(pPropertyVault, g_wszVBRBitrateMax, 0);
		hr = SetDWORDProperty(pPropertyVault, g_wszVBRBufferWindowMax, 0);
	}

	hr = pStreamConfig->SetBitrate(m_dwBitrate);
	if (FAILED(hr))	return hr;

	return hr;
}

HRESULT CVideoStream::SetVBRSettings(IWMStreamConfig* pStreamConfig)
{
	if (m_bVBR == false)
		return false;

	_ASSERT(m_nQuality);

	HRESULT hr = E_FAIL;
	CComQIPtr<IWMPropertyVault> pPropertyVault(pStreamConfig);
	if (pPropertyVault)
	{
		BOOL bEnableVBR = TRUE;
		hr = pPropertyVault->SetProperty(g_wszVBREnabled, WMT_TYPE_BOOL, (BYTE*)&bEnableVBR, sizeof(BOOL));
		if (FAILED(hr))
		{
			_ASSERT(!"Could not set VBR");
			return hr;
		}

		if (m_nVBRConstrain == 0) // quality based
		{
			hr = SetDWORDProperty(pPropertyVault, g_wszVBRQuality, m_nQuality);
			if (FAILED(hr))	return hr;

			hr = SetDWORDProperty(pPropertyVault, g_wszVBRBitrateMax, 0);
			hr = SetDWORDProperty(pPropertyVault, g_wszVBRBufferWindowMax, 0);
		}
		else if (m_nVBRConstrain == 1) // unconstrained
		{
			// only works with two-pass!!

			hr = pStreamConfig->SetBitrate(m_dwBitrate);
			if (FAILED(hr))	return hr;

			hr = SetDWORDProperty(pPropertyVault, g_wszVBRQuality, 0);
			hr = SetDWORDProperty(pPropertyVault, g_wszVBRBitrateMax, 0);
			hr = SetDWORDProperty(pPropertyVault, g_wszVBRBufferWindowMax, 0);
		}
		else if (m_nVBRConstrain == 2) // constrained
		{
			// only works with two-pass!!

			hr = pStreamConfig->SetBitrate(m_dwBitrate);
			if (FAILED(hr))	return hr;

			hr = SetDWORDProperty(pPropertyVault, g_wszVBRQuality, 0);
			hr = SetDWORDProperty(pPropertyVault, g_wszVBRBitrateMax, m_nMaxVideoBitrate);
			hr = SetDWORDProperty(pPropertyVault, g_wszVBRBufferWindowMax, 500); // guesswork, have no idea what this is!
		}
	}
	else
		return hr;

	return hr;
}

void CVideoStream::SetVideoCodec(long nIndex)
{
	m_nVideoCodec = nIndex;
}

void CVideoStream::SetVideoDimensions(int cx, int cy)
{
	m_nVideoX = cx;
	m_nVideoY = cy;
}

void CVideoStream::SetVBR(bool bVBR)
{
	m_bVBR = bVBR;
}

void CVideoStream::SetQuality(long nQuality)
{
	m_nQuality = nQuality;
}

void CVideoStream::SetFramerate(double dFramerate)
{
	m_dFramerate = dFramerate;
}

void CVideoStream::SetKeyFramerate(long nRate)
{
	m_nKeyFramerate = nRate;
}

void CVideoStream::SetPasses(long nPasses)
{
}

void CVideoStream::SetBestVideoCodec(long nIndex)
{
	m_nBestVideoCodec = nIndex;
}

void CVideoStream::SetSourceInfo(double fps, long cx, long cy)
{
	m_fSrcFramerate = fps;
	m_nSrcX = cx;
	m_nSrcY = cy;
}

void CVideoStream::SetAutoDimensions(bool bVal)
{
	m_bAutoDimensions = bVal;
}

bool CVideoStream::GetAutoDimensions()
{
	return m_bAutoDimensions;
}

bool CVideoStream::GetAutoBitrate()
{
	return m_bAutoBitrate;
}

void CVideoStream::SetAutoBitrate(bool bVal)
{
	m_bAutoBitrate = bVal;
}

bool CVideoStream::GetAutomaticFramerate(void)
{
	return m_bAutoFramerate;
}

bool CVideoStream::GetDimensionsFromSrc(void)
{
	return m_bDimFromSrc;
}

void CVideoStream::SetAutoFramerate(bool bVal)
{
	m_bAutoFramerate = bVal;
}

void CVideoStream::SetFramerateFromSrc(bool bVal)
{
	m_bSrcFramerate = bVal;
}

void CVideoStream::SetDimensionsFromSrc(bool bVal)
{
	m_bDimFromSrc = bVal;
}

bool CVideoStream::GetFramerateFromSrc(void)
{
	return m_bSrcFramerate;
}

void CVideoStream::DestroyObjects(void)
{
}
