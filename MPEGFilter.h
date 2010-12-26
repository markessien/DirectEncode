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


#pragma once

class CMPEGObj;
class CMPEGSeeking;
class CMPEGInputPin;
class CMPEGOutputPin;

// Main filter object. This object routes all calls the the mpegobj

class CMPEGFilter : public CBaseFilter
{
	friend class CMPEGObj;
	friend class CMPEGOutputPin;
public:
	CMPEGInputPin* GetVideoPin();
	CCritSec* GetMainLock();
	
    CMPEGFilter(CMPEGObj *pMPEG, LPUNKNOWN pUnk, HRESULT *phr);
	virtual ~CMPEGFilter();

    // Pin enumeration
    CBasePin * GetPin(int n);
    int GetPinCount();

    // Open and close the file as necessary
    STDMETHODIMP Run(REFERENCE_TIME tStart);
    STDMETHODIMP Pause();
    STDMETHODIMP Stop();
	STDMETHODIMP QueryVendorInfo(LPWSTR *pVendorInfo);

	STDMETHODIMP GetState(DWORD dwMilliSecsTimeout, FILTER_STATE *State);

	virtual HRESULT GetMediaPositionInterface(REFIID riid, void **ppv);

private:
	CMPEGObj* const m_pMPEGObj;
    CMPEGInputPin *m_pPinVideo;
    CMPEGInputPin *m_pPinAudio;

	CMPEGOutputPin* m_pOutPinSystems;
	CMPEGOutputPin* m_pOutPinVideo;
	CMPEGOutputPin* m_pOutPinAudio;

    CCritSec m_Lock;                // Main renderer critical section
    CCritSec m_ReceiveLock;         // Sublock for received samples
	CMPEGSeeking* m_pPosition;
	CCritSec m_ObjectCreationLock;      // This lock protects the creation and
                                        // of m_pPosition and m_pInputPin.  It
                                        // ensures that two threads cannot create
                                        // either object simultaneously.
	CAMEvent m_evComplete;              // Signalled when state complete
};




