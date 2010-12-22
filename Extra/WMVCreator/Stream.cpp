#include "StdAfx.h"
#include "stream.h"

CStream::CStream(void) : m_dwBitrate(0), m_pCodec(NULL), m_pCodecArray(NULL)
{
}

CStream::~CStream(void)
{
}

///////////////////////////////////////////////////////////////////////////////
HRESULT CStream::SetStreamBasics(IWMStreamConfig *pIWMStreamConfig, WORD wStreamNum, 
                                       LPWSTR pwszStreamName, LPWSTR pwszConnectionName,
                                       DWORD dwBitrate, WM_MEDIA_TYPE *pmt)
{
    HRESULT hr = S_OK;
    CComPtr<IWMMediaProps> pIWMMediaProps = NULL;

    do
    {
        hr = pIWMStreamConfig->SetStreamNumber( wStreamNum );
        if( FAILED( hr ) )
        {
            break;
        }

        hr = pIWMStreamConfig->SetStreamName( pwszStreamName );
        if( FAILED( hr ) )
        {
            break;
        }

        hr = pIWMStreamConfig->SetConnectionName( pwszConnectionName );
        if( FAILED( hr ) )
        {
            break;
        }

		/*
        if (dwBitrate != 0)
        {
            hr = pIWMStreamConfig->SetBitrate( dwBitrate );
            if( FAILED( hr ) )
            {
                break;
            }
        }*/

        hr = pIWMStreamConfig->QueryInterface( IID_IWMMediaProps,
                                               (void **) &pIWMMediaProps );
        if( FAILED( hr ) )
        {
            break;
        }

        hr = pIWMMediaProps->SetMediaType( pmt );
        if( FAILED( hr ) )
        {
            break;
        }
    }
    while( FALSE );

    return( hr );
}


HRESULT CStream::GetStreamConfig(IWMProfile* pWMProfile, GUID guidMediaType, IWMStreamConfig** ppStreamConfig)
{
	_ASSERT(ppStreamConfig); // chk ptrs, fx ths if asrt, crit

	// check number of streams so we can loop through and
	// get the stream type for this codec
	DWORD dwStreamCount = 0;
	HRESULT hr = pWMProfile->GetStreamCount(&dwStreamCount);
	if (FAILED(hr))
		return hr;

	int iStreamCount = 0;

	// get the stream config of the media type that
	// corresponds to the media type of the codec.
	// I.e, we get the audio streamcofig for the audio codec
	// and the video streamconfig for the video codec
	
	CComPtr<IWMStreamConfig> pStreamConfig;
	for (int i=0;i<(int)dwStreamCount;i++)
	{
		hr = pWMProfile->GetStream(i, &pStreamConfig);
		if (SUCCEEDED(hr) && pStreamConfig)
		{
			GUID guidType;
			pStreamConfig->GetStreamType(&guidType);
			if (guidMediaType == guidType)
			{
				iStreamCount++;
				ASSERT(iStreamCount == 1); // why more than one audio stream? Which do we use?
				break;
			}
		}

		pStreamConfig = NULL;
	}
	
	if (pStreamConfig)
		pStreamConfig.CopyTo(ppStreamConfig);
	else
		*ppStreamConfig = NULL;

	return hr;
}

HRESULT CStream::SetDWORDProperty(IWMPropertyVault* pPropertyVault, const WCHAR* pstrSetting, DWORD dwVal)
{
	if (pPropertyVault == NULL)
		return E_POINTER;

	HRESULT hr = pPropertyVault->SetProperty(pstrSetting, WMT_TYPE_DWORD, (BYTE*)&dwVal, sizeof(DWORD));
	if (FAILED(hr))
	{
		_ASSERT(!"Could not set DWORD property");
		return hr;
	}
	
	return hr;
}

HRESULT CStream::GetStreamMediaType(IWMStreamConfig* pStreamConfig, IWMVideoMediaProps** ppProps, WM_MEDIA_TYPE **ppmt)
{
    HRESULT hr;
    CComPtr<IWMMediaProps> pProps = NULL;
    hr = pStreamConfig->QueryInterface( IID_IWMMediaProps ,
                                        (void **) &pProps );
    if( FAILED( hr ) )
    {
        *ppProps = NULL;
        return hr;
    }
 
    DWORD cbMT;
    hr = pProps->GetMediaType( NULL, &cbMT );
    if( FAILED( hr ) )
    {
        return hr;
    }

    *ppmt = (WM_MEDIA_TYPE *) new BYTE[ cbMT ];
    if( !*ppmt )
    {
        hr = E_OUTOFMEMORY;
        return hr;
    }

    hr = pProps->GetMediaType( *ppmt, &cbMT );
    if( FAILED( hr ) )
    {
        return hr;
    }

	if (ppProps)
		*ppProps = NULL;

	// get video media props
	CComPtr<IWMVideoMediaProps> pVideoProps = NULL;
    hr = pStreamConfig->QueryInterface( IID_IWMVideoMediaProps,
                                        (void **) &pVideoProps );
    if( SUCCEEDED( hr ) )
    {
        pVideoProps.CopyTo(ppProps);
        return hr;
    }
	else hr = S_OK;

    return hr;
}
DWORD CStream::GetBitrate(void)
{
	return m_dwBitrate;
}

CCodec* CStream::GetCodec(void)
{
	return m_pCodec;
}

void CStream::MapCodec(WM_MEDIA_TYPE *pMT)
{
	CComBSTR strGuid(pMT->subtype);
	for (unsigned int i=0;i<m_pCodecArray->GetCount();i++)
	{
		CCodec* p = m_pCodecArray->GetAt(i);
		//OutputDebugStringW(p->GetCodecGuid());
		//OutputDebugStringW(L"\n");
		if (p->GetCodecGuid() == strGuid)
		{
			m_pCodec = p;
			break;
		}
	}
}

void CStream::SetCodecArray(CCodecArray* pCodecArray)
{
	m_pCodecArray = pCodecArray;
}

void CStream::SetBitrate(long nBitrate)
{
	m_dwBitrate = (DWORD)nBitrate;
}
