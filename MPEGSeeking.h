// MuxSeeking.h: interface for the CMPEGSeeking class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MUXSEEKING_H__4DE8C81C_1B8F_4B3E_915C_DA2B84D27A87__INCLUDED_)
#define AFX_MUXSEEKING_H__4DE8C81C_1B8F_4B3E_915C_DA2B84D27A87__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMPEGObj;

class CMPEGSeeking : public IMediaSeeking, public CMediaPosition
{
public:
	CMPEGSeeking(const char * pName, 
				 LPUNKNOWN pUnk, 
				 HRESULT* phr, 
				 IPin * pVideoPin, 
				 IPin * pAudioPin, 
				 CMPEGObj* pMPEGObj);
	
	IPin *m_pVideoPin;
	IPin *m_pAudioPin;
	CMPEGObj* m_pMPEGObj;

    HRESULT GetPeer(IMediaPosition **ppMP);
    HRESULT GetPeerSeeking(IMediaSeeking **ppMS);

public:

    DECLARE_IUNKNOWN

    HRESULT ForceRefresh() {
        return S_OK;
    };

    // override to return an accurate current position. THIS IS OUR FNC
    virtual HRESULT GetMediaTime(LONGLONG *pStartTime,LONGLONG *pEndTime);

    STDMETHODIMP NonDelegatingQueryInterface(REFIID riid,void **ppv);

    // IMediaSeeking methods
    STDMETHODIMP GetCapabilities( DWORD * pCapabilities );
    STDMETHODIMP CheckCapabilities( DWORD * pCapabilities );
    STDMETHODIMP SetTimeFormat(const GUID * pFormat);
    STDMETHODIMP GetTimeFormat(GUID *pFormat);
    STDMETHODIMP IsUsingTimeFormat(const GUID * pFormat);
    STDMETHODIMP IsFormatSupported( const GUID * pFormat);
    STDMETHODIMP QueryPreferredFormat( GUID *pFormat);
    STDMETHODIMP ConvertTimeFormat(LONGLONG * pTarget, const GUID * pTargetFormat,
                                   LONGLONG    Source, const GUID * pSourceFormat );
    STDMETHODIMP SetPositions( LONGLONG * pCurrent, DWORD CurrentFlags
                             , LONGLONG * pStop, DWORD StopFlags );

    STDMETHODIMP GetPositions( LONGLONG * pCurrent, LONGLONG * pStop );
    STDMETHODIMP GetCurrentPosition( LONGLONG * pCurrent );
    STDMETHODIMP GetStopPosition( LONGLONG * pStop );
    STDMETHODIMP SetRate( double dRate);
    STDMETHODIMP GetRate( double * pdRate);
    STDMETHODIMP GetDuration( LONGLONG *pDuration);
    STDMETHODIMP GetAvailable( LONGLONG *pEarliest, LONGLONG *pLatest );
    STDMETHODIMP GetPreroll( LONGLONG *pllPreroll );

    // IMediaPosition properties
    STDMETHODIMP get_Duration(REFTIME * plength);
    STDMETHODIMP put_CurrentPosition(REFTIME llTime);
    STDMETHODIMP get_StopTime(REFTIME * pllTime);
    STDMETHODIMP put_StopTime(REFTIME llTime);
    STDMETHODIMP get_PrerollTime(REFTIME * pllTime);
    STDMETHODIMP put_PrerollTime(REFTIME llTime);
    STDMETHODIMP get_Rate(double * pdRate);
    STDMETHODIMP put_Rate(double dRate);
    STDMETHODIMP get_CurrentPosition(REFTIME * pllTime);
    STDMETHODIMP CanSeekForward(LONG *pCanSeekForward);
    STDMETHODIMP CanSeekBackward(LONG *pCanSeekBackward);

private:
    HRESULT GetSeekingLongLong( HRESULT (__stdcall IMediaSeeking::*pMethod)( LONGLONG * ),
                                LONGLONG * pll );
};

#endif // !defined(AFX_MUXSEEKING_H__4DE8C81C_1B8F_4B3E_915C_DA2B84D27A87__INCLUDED_)
