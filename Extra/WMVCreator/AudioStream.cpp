#include "StdAfx.h"
#include "audiostream.h"

CAudioStream::CAudioStream(void) : m_nCodecFormat(0)
{
}

CAudioStream::~CAudioStream(void)
{
}

HRESULT CAudioStream::Load(IWMProfile* pWMProfile)
{
	ASSERT(pWMProfile);
	if (pWMProfile == NULL)
		return E_POINTER;

	CComPtr<IWMStreamConfig> pStreamConfig;
	GetStreamConfig(pWMProfile, WMMEDIATYPE_Audio, &pStreamConfig);
	if (pStreamConfig == NULL)
		return E_FAIL;

	pStreamConfig->GetBitrate(&m_dwBitrate);

	WM_MEDIA_TYPE *pMT = NULL;
	HRESULT hr = GetStreamMediaType(pStreamConfig, NULL, &pMT);  
	if( FAILED( hr ) )
	{
		return hr;
	} 

	MapCodec(pMT);
//	m_Codec.LoadMediaProps(pStreamConfig);

	return S_OK;
}

BSTR CAudioStream::GetLanguage(void)
{
	return BSTR();
}

void CAudioStream::SetLanguage(BSTR str)
{
	// IWMStreamConfig3::GetLanguage
}

int CAudioStream::GetTransportType(void)
{
	return 0;
}

HRESULT CAudioStream::SetCBRSettings(IWMStreamConfig* pStreamConfig)
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

	/*
	hr = pStreamConfig->SetBitrate(m_dwBitrate);
	if (FAILED(hr))	return hr;
*/
	return hr;
}

HRESULT CAudioStream::CreateNew(IWMProfile* pWMProfile)
{
	HRESULT hr;

    CComPtr<IWMStreamConfig> pStreamConfig = NULL;
    
	if (m_nCodec == -1)
	{   
		// uncompressed
		hr = pWMProfile->CreateNewStream(WMMEDIATYPE_Audio, &pStreamConfig);
        if (FAILED(hr)) return hr;
        hr = pWMProfile->AddStream( pStreamConfig );
		return hr;
	}

	CComPtr <IWMProfileManager> pIWMProfileManager;
    hr = WMCreateProfileManager(&pIWMProfileManager);
    if(FAILED(hr)) return hr;
    
	CComPtr<IWMCodecInfo2> pICodecInfo;
    hr = pIWMProfileManager->QueryInterface(IID_IWMCodecInfo2, (void**)&pICodecInfo);
    if (!pICodecInfo || FAILED(hr)) return hr;

    hr = pICodecInfo->GetCodecFormat(WMMEDIATYPE_Audio, m_nCodec, m_nCodecFormat, &pStreamConfig);
    if (FAILED(hr)) return hr;

	WM_MEDIA_TYPE* pMT = NULL;
	hr = GetStreamMediaType(pStreamConfig, NULL, &pMT);
	if (FAILED(hr) || pMT == NULL) return hr;

    if( pMT->formattype != WMFORMAT_WaveFormatEx )
    {
        return E_FAIL;
    }

	WAVEFORMATEX *pWfx = (WAVEFORMATEX *) pMT->pbFormat;

	/*
    WM_MEDIA_TYPE mt;  
    ZeroMemory( &mt, sizeof( mt ) );
    
	
    mt.majortype = WMMEDIATYPE_Audio;
    mt.subtype = WMMEDIASUBTYPE_Base;
    mt.subtype.Data1 = pWfx->wFormatTag;
    mt.bFixedSizeSamples = TRUE;
    mt.bTemporalCompression = FALSE;
    mt.lSampleSize = pWfx->nBlockAlign;
    mt.formattype = WMFORMAT_WaveFormatEx;
    mt.pUnk = NULL;
    mt.cbFormat = sizeof( WAVEFORMATEX ) + pWfx->cbSize;
    mt.pbFormat = (BYTE *) pWfx;
    */

    pStreamConfig = NULL;
    hr = pWMProfile->CreateNewStream(WMMEDIATYPE_Audio, &pStreamConfig);
    if (FAILED(hr)) return hr;
    
//	SetCBRSettings(pStreamConfig);

    hr = SetStreamBasics( pStreamConfig, 
                          2,
                          L"Audio Stream",
                          L"Audio",
                          pWfx->nAvgBytesPerSec * 8,
                          pMT);
    if (FAILED(hr)) return hr;

    hr = pWMProfile->AddStream(pStreamConfig);
    if ( FAILED( hr ) )
    {
        return hr;
    }

    delete pMT;

    return hr;
}

void CAudioStream::SetAudioCodec(long nIndex)
{
	_ASSERT(m_pCodecArray);
	m_pCodec = m_pCodecArray->GetAt(nIndex);
	_ASSERT(m_pCodec);
	m_nCodec = nIndex;
}

void CAudioStream::SelectNearestFormat(bool bVBR, long nBitrate, long nPasses)
{
	// linear algorithm to get the closest format to the bitrate we want
	// TODO: Check to make sure after is not smaller than before, dig?

	long nNearestFormat = 0;
	DWORD dwNearestBitrateBefore = 0; // will go as close to the target bitrate as possible
									  // but will never reach it
	DWORD dwNearestBitrateAfter = -1; // max it out
	CFormatArray* pFormats = m_pCodec->GetFormats();
	for (unsigned int i=0;i<pFormats->GetCount();i++)
	{
		// get the nearest bitrates on either side
		DWORD dwBit = pFormats->GetAt(i)->dwBitrate;
		if (dwBit < (DWORD)nBitrate) // if the bitrate is smaller than the bitrate we want to have
		{
			if (dwBit > dwNearestBitrateBefore) // if the bitrate is nearer to our target than what we previously had
			{
				dwNearestBitrateBefore = dwBit;
				nNearestFormat = i;
			}
		}
		else // it is larger or equal
		{
			if (dwBit < dwNearestBitrateAfter) // if the bitrate is nearer to our target than what we previously had
			{
				dwNearestBitrateAfter = dwBit;
				nNearestFormat = i;
			}
		}
		
		/*
		if (dwBit < dwNearestBitrateAfter)
		{
			dwNearestBitrateBefore = dwBit;
			nNearestFormat = i;
		}
		else if (dwBit > dwNearestBitrateBefore)
		{
			dwNearestBitrateAfter = dwBit;
			nNearestFormat = i;
		}*/
	}

	m_nCodecFormat = nNearestFormat;
	CComBSTR strName = pFormats->GetAt(nNearestFormat)->strName;
}

void CAudioStream::DestroyObjects(void)
{
}
