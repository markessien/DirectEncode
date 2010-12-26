/** This file is part of The Standard Mpeg Encoder.

The Standard Mpeg Encoder is free software: you can redistribute it 
and/or modify it under the terms of the GNU General Public License 
as published by the Free Software Foundation, either version 3 of 
the License, or (at your option) any later version.

The Standard Mpeg Encoder is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with The Standard Mpeg Encoder.  
 
If not, see <http://www.gnu.org/licenses/>.
**/

// MuxSeeking.cpp: implementation of the CMPEGSeeking class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MpegSeeking.h"
// #include "IEssienMPEGEncoder.h"
#include "mpeginputpin.h"
#include "MPEGFilterInterface.h"
#include "mpegobj.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CMPEGSeeking::CMPEGSeeking(const char *pName,
						   LPUNKNOWN pUnk,
						   HRESULT *phr,
						   IPin * pVideoPin, 
						   IPin * pAudioPin, 
						   CMPEGObj* pMPEGObj) :

						   m_pMPEGObj(pMPEGObj),
						   CMediaPosition(pName, pUnk),
						   m_pVideoPin(pVideoPin),
						   m_pAudioPin(pAudioPin)
{
    if (pVideoPin == NULL) 
	{
        *phr = E_POINTER;
        return;
    }

	if (pAudioPin == NULL) 
	{
        *phr = E_POINTER;
        return;
    }
}


// Expose our IMediaSeeking and IMediaPosition interfaces

STDMETHODIMP
CMPEGSeeking::NonDelegatingQueryInterface(REFIID riid,void **ppv) {
    CheckPointer(ppv,E_POINTER);
    *ppv = NULL;

    if(riid == IID_IMediaSeeking) {
        return GetInterface(static_cast<IMediaSeeking *>(this), ppv);
    }
    return CMediaPosition::NonDelegatingQueryInterface(riid,ppv);
}


// Return the IMediaPosition interface from our peer

HRESULT
CMPEGSeeking::GetPeer(IMediaPosition ** ppMP) {
    *ppMP = NULL;

    IPin *pConnected;
    HRESULT hr = m_pVideoPin->ConnectedTo(&pConnected);
    if(FAILED(hr)) {
		hr = m_pAudioPin->ConnectedTo(&pConnected);
		if(FAILED(hr))
			return E_NOTIMPL;
    }

    IMediaPosition * pMP;
    hr = pConnected->QueryInterface(IID_IMediaPosition, (void **) &pMP);
    pConnected->Release();
    if(FAILED(hr)) {
        return E_NOTIMPL;
    }

    *ppMP = pMP;
    return S_OK;
}


// Return the IMediaSeeking interface from our peer

HRESULT
CMPEGSeeking::GetPeerSeeking(IMediaSeeking ** ppMS) {
    *ppMS = NULL;

	
    IPin *pConnected;
    HRESULT hr = m_pVideoPin->ConnectedTo(&pConnected);
    if(FAILED(hr)) {
		hr = m_pAudioPin->ConnectedTo(&pConnected);
		if (FAILED(hr))
			return E_NOTIMPL;
    }

    IMediaSeeking * pMS;
    hr = pConnected->QueryInterface(IID_IMediaSeeking, (void **) &pMS);
    pConnected->Release();
    if(FAILED(hr)) {
        return E_NOTIMPL;
    }

    *ppMS = pMS;

    return S_OK;
}


// --- IMediaSeeking methods ----------


STDMETHODIMP
CMPEGSeeking::GetCapabilities(DWORD * pCaps) {
    IMediaSeeking* pMS;
    HRESULT hr = GetPeerSeeking(&pMS);
    if(FAILED(hr)) {
        return hr;
    }

    hr = pMS->GetCapabilities(pCaps);
    pMS->Release();
    return hr;
}

STDMETHODIMP
CMPEGSeeking::CheckCapabilities(DWORD * pCaps) {
    IMediaSeeking* pMS;
    HRESULT hr = GetPeerSeeking(&pMS);
    if(FAILED(hr)) {
        return hr;
    }

    hr = pMS->CheckCapabilities(pCaps);
    pMS->Release();
    return hr;
}

STDMETHODIMP
CMPEGSeeking::IsFormatSupported(const GUID * pFormat) {
    IMediaSeeking* pMS;
    HRESULT hr = GetPeerSeeking(&pMS);
    if(FAILED(hr)) {
        return hr;
    }

    hr = pMS->IsFormatSupported(pFormat);
    pMS->Release();
    return hr;
}


STDMETHODIMP
CMPEGSeeking::QueryPreferredFormat(GUID *pFormat) {
    IMediaSeeking* pMS;
    HRESULT hr = GetPeerSeeking(&pMS);
    if(FAILED(hr)) {
        return hr;
    }

    hr = pMS->QueryPreferredFormat(pFormat);
    pMS->Release();
    return hr;
}


STDMETHODIMP
CMPEGSeeking::SetTimeFormat(const GUID * pFormat) {
    IMediaSeeking* pMS;
    HRESULT hr = GetPeerSeeking(&pMS);
    if(FAILED(hr)) {
        return hr;
    }

    hr = pMS->SetTimeFormat(pFormat);
    pMS->Release();
    return hr;
}


STDMETHODIMP
CMPEGSeeking::GetTimeFormat(GUID *pFormat) {
    IMediaSeeking* pMS;
    HRESULT hr = GetPeerSeeking(&pMS);
    if(FAILED(hr)) {
        return hr;
    }

    hr = pMS->GetTimeFormat(pFormat);
    pMS->Release();
    return hr;
}


STDMETHODIMP
CMPEGSeeking::IsUsingTimeFormat(const GUID * pFormat) {
    IMediaSeeking* pMS;
    HRESULT hr = GetPeerSeeking(&pMS);
    if(FAILED(hr)) {
        return hr;
    }

    hr = pMS->IsUsingTimeFormat(pFormat);
    pMS->Release();
    return hr;
}


STDMETHODIMP
CMPEGSeeking::ConvertTimeFormat(LONGLONG * pTarget, const GUID * pTargetFormat,
                LONGLONG    Source, const GUID * pSourceFormat ) {
    IMediaSeeking* pMS;
    HRESULT hr = GetPeerSeeking(&pMS);
    if(FAILED(hr)) {
        return hr;
    }

    hr = pMS->ConvertTimeFormat(pTarget, pTargetFormat, Source, pSourceFormat);
    pMS->Release();
    return hr;
}


STDMETHODIMP
CMPEGSeeking::SetPositions( LONGLONG * pCurrent, DWORD CurrentFlags
              , LONGLONG * pStop, DWORD StopFlags ) {
    IMediaSeeking* pMS;
    HRESULT hr = GetPeerSeeking(&pMS);
    if(FAILED(hr)) {
        return hr;
    }

    hr = pMS->SetPositions(pCurrent, CurrentFlags, pStop, StopFlags);
    pMS->Release();
    return hr;
}

STDMETHODIMP
CMPEGSeeking::GetPositions(LONGLONG *pCurrent, LONGLONG * pStop) {
	/*
    IMediaSeeking* pMS;
    HRESULT hr = GetPeerSeeking(&pMS);
    if(FAILED(hr)) {
        return hr;
    }

    hr = pMS->GetPositions(pCurrent,pStop);
    pMS->Release();
	*/

	*pCurrent = m_pMPEGObj->GetCurrentTime();
	*pStop = *pCurrent + 1000;

    return S_OK;
}

HRESULT
CMPEGSeeking::GetSeekingLongLong
( HRESULT(__stdcall IMediaSeeking::*pMethod)( LONGLONG * )
, LONGLONG * pll
) {
    IMediaSeeking* pMS;
    HRESULT hr = GetPeerSeeking(&pMS);
    if(SUCCEEDED(hr)) {
        hr = (pMS->*pMethod)(pll);
        pMS->Release();
    }
    return hr;
}

// If we don't have a current position then ask upstream

STDMETHODIMP
CMPEGSeeking::GetCurrentPosition(LONGLONG *pCurrent) {
    // Can we report the current position
    HRESULT hr = GetMediaTime(pCurrent,NULL);
    if(SUCCEEDED(hr)) 
        hr = NOERROR;
    else 
        hr = GetSeekingLongLong(&IMediaSeeking::GetCurrentPosition, pCurrent);
    return hr;
}


STDMETHODIMP
CMPEGSeeking::GetStopPosition(LONGLONG *pStop) 
{
	return GetSeekingLongLong(&IMediaSeeking::GetStopPosition, pStop);;
}

STDMETHODIMP
CMPEGSeeking::GetDuration(LONGLONG *pDuration) 
{
    return GetSeekingLongLong(&IMediaSeeking::GetDuration, pDuration);;
}


STDMETHODIMP
CMPEGSeeking::GetPreroll(LONGLONG *pllPreroll) {
    return GetSeekingLongLong(&IMediaSeeking::GetPreroll, pllPreroll);;
}


STDMETHODIMP
CMPEGSeeking::GetAvailable( LONGLONG *pEarliest, LONGLONG *pLatest ) {
    IMediaSeeking* pMS;
    HRESULT hr = GetPeerSeeking(&pMS);
    if(FAILED(hr)) {
        return hr;
    }

    hr = pMS->GetAvailable(pEarliest, pLatest);
    pMS->Release();
    return hr;
}


STDMETHODIMP
CMPEGSeeking::GetRate(double * pdRate) {
    IMediaSeeking* pMS;
    HRESULT hr = GetPeerSeeking(&pMS);
    if(FAILED(hr)) {
        return hr;
    }
    hr = pMS->GetRate(pdRate);
    pMS->Release();
    return hr;
}


STDMETHODIMP
CMPEGSeeking::SetRate(double dRate) {
    if(0.0 == dRate) {
        return E_INVALIDARG;
    }

    IMediaSeeking* pMS;
    HRESULT hr = GetPeerSeeking(&pMS);
    if(FAILED(hr)) {
        return hr;
    }
    hr = pMS->SetRate(dRate);
    pMS->Release();
    return hr;
}




// --- IMediaPosition methods ----------


STDMETHODIMP
CMPEGSeeking::get_Duration(REFTIME * plength) {
    IMediaPosition* pMP;
    HRESULT hr = GetPeer(&pMP);
    if(FAILED(hr)) {
        return hr;
    }

    hr = pMP->get_Duration(plength);
    pMP->Release();
    return hr;
}


STDMETHODIMP
CMPEGSeeking::get_CurrentPosition(REFTIME * pllTime) {
	
    IMediaPosition* pMP;
    HRESULT hr = GetPeer(&pMP);
    if(FAILED(hr)) {
        return hr;
    }
    hr = pMP->get_CurrentPosition(pllTime);
    pMP->Release();
    return hr;
}


STDMETHODIMP
CMPEGSeeking::put_CurrentPosition(REFTIME llTime) {
    IMediaPosition* pMP;
    HRESULT hr = GetPeer(&pMP);
    if(FAILED(hr)) {
        return hr;
    }
    hr = pMP->put_CurrentPosition(llTime);
    pMP->Release();
    return hr;
}


STDMETHODIMP
CMPEGSeeking::get_StopTime(REFTIME * pllTime) {
    IMediaPosition* pMP;
    HRESULT hr = GetPeer(&pMP);
    if(FAILED(hr)) {
        return hr;
    }
    hr = pMP->get_StopTime(pllTime);
    pMP->Release();
    return hr;
}


STDMETHODIMP
CMPEGSeeking::put_StopTime(REFTIME llTime) {
    IMediaPosition* pMP;
    HRESULT hr = GetPeer(&pMP);
    if(FAILED(hr)) {
        return hr;
    }
    hr = pMP->put_StopTime(llTime);
    pMP->Release();
    return hr;
}


STDMETHODIMP
CMPEGSeeking::get_PrerollTime(REFTIME * pllTime) {
    IMediaPosition* pMP;
    HRESULT hr = GetPeer(&pMP);
    if(FAILED(hr)) {
        return hr;
    }
    hr = pMP->get_PrerollTime(pllTime);
    pMP->Release();
    return hr;
}


STDMETHODIMP
CMPEGSeeking::put_PrerollTime(REFTIME llTime) {
    IMediaPosition* pMP;
    HRESULT hr = GetPeer(&pMP);
    if(FAILED(hr)) {
        return hr;
    }
    hr = pMP->put_PrerollTime(llTime);
    pMP->Release();
    return hr;
}


STDMETHODIMP
CMPEGSeeking::get_Rate(double * pdRate) {
    IMediaPosition* pMP;
    HRESULT hr = GetPeer(&pMP);
    if(FAILED(hr)) {
        return hr;
    }
    hr = pMP->get_Rate(pdRate);
    pMP->Release();
    return hr;
}


STDMETHODIMP
CMPEGSeeking::put_Rate(double dRate) {
    if(0.0 == dRate) {
        return E_INVALIDARG;
    }

    IMediaPosition* pMP;
    HRESULT hr = GetPeer(&pMP);
    if(FAILED(hr)) {
        return hr;
    }
    hr = pMP->put_Rate(dRate);
    pMP->Release();
    return hr;
}


STDMETHODIMP
CMPEGSeeking::CanSeekForward(LONG *pCanSeekForward) {
    IMediaPosition* pMP;
    HRESULT hr = GetPeer(&pMP);
    if(FAILED(hr)) {
        return hr;
    }
    hr = pMP->CanSeekForward(pCanSeekForward);
    pMP->Release();
    return hr;
}


STDMETHODIMP
CMPEGSeeking::CanSeekBackward(LONG *pCanSeekBackward) {
    IMediaPosition* pMP;
    HRESULT hr = GetPeer(&pMP);
    if(FAILED(hr)) {
        return hr;
    }
    hr = pMP->CanSeekBackward(pCanSeekBackward);
    pMP->Release();
    return hr;
}

HRESULT CMPEGSeeking::GetMediaTime(LONGLONG *pStartTime, LONGLONG *pEndTime) 
{
	if (pStartTime)
		*pStartTime = m_pMPEGObj->GetCurrentTime();

	if (pEndTime)
		*pEndTime = m_pMPEGObj->GetCurrentTime() + 1000;

    return S_OK;
}
