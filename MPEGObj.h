
#pragma once

#include "Profile.h"
#include "license.h"
#include "Encodeerdlib.h"
#include "LogoOverlay.h"

class CMPEGFilter;
class CMPEGFilterInterface;

class CMPEGObj : public CUnknown,
				 public ISpecifyPropertyPages,
				 public IDeliverCallback,
				 public CPersistStream

{
	STDMETHODIMP QueryInterface(REFIID riid, void **ppv) 
	{ 
        return GetOwner()->QueryInterface(riid,ppv);
    };
	
    STDMETHODIMP_(ULONG) AddRef() 
	{                          
        return GetOwner()->AddRef();                         
    };
	
    STDMETHODIMP_(ULONG) Release() 
	{                      
        return GetOwner()->Release();                     
    };
 
	friend class CMPEGFilterInterface;
	friend class CMPEGOutputPin;
	friend class CMPEGFilter;

public:
	CMPEGObj(LPUNKNOWN pUnk, HRESULT *phr);
    ~CMPEGObj();

    static CUnknown * WINAPI CreateInstance(LPUNKNOWN punk, HRESULT *phr);
 
	bool GetShouldMultiplex();
	void SetShouldMultiplex(bool b);
	bool IsWaitingInPause();
	bool IsPaused();
	void Pause();
	bool IsPrimed();
	REFERENCE_TIME GetCurrentTime();
	HRESULT PrimeForEncode();
	HRESULT ReceiveAudio(IMediaSample *pSample);
	HRESULT ReceiveVideo(IMediaSample *pSample);
	HRESULT EndOfStream(MediaFormat mediaFormat);
	HRESULT Stop();
	HRESULT Run();
	HRESULT LoadSettings(BSTR strKey);
	HRESULT SaveSettings(BSTR strKey);
	HRESULT PassThruCmd(BSTR strCmd, long nCmd, double dCmd, BYTE* pCmd);

	HRESULT Deliver(unsigned char* pBuf, int nBufLen, int nID);
	signed __int64 SeekOutput(signed __int64 newPos, int nID);

	STDMETHODIMP  SelectFormat(SystemsOutputFormat systemsFormat, Constraint constraint);
	CMPEGProfile& GetSettingsProfile(SystemsOutputFormat systemsFormat, Constraint constrain);
	CMPEGProfile& GetCurrentSettingsProfile();

	CEncodeErdLib* GetEncodeLib() { return m_pEncode; }
	
    // CPeristStream stuff
    HRESULT WriteToStream(IStream *pStream);
    HRESULT ReadFromStream(IStream *pStream);
	int SizeMax() {return 10;}

	 // CPersistStream override
    STDMETHODIMP GetClassID(CLSID *pClsid);

private:
    void StopConversion();

protected:
	STDMETHODIMP SetFileName(LPCOLESTR pszFileName,const AM_MEDIA_TYPE *pmt);
    STDMETHODIMP GetCurFile(LPOLESTR * ppszFileName,AM_MEDIA_TYPE *pmt);
    STDMETHODIMP NonDelegatingQueryInterface(REFIID riid, void ** ppv);
	STDMETHODIMP GetPages(CAUUID *pPages);
 

private:
	CComPtr<IDirectEncodeVB> m_pDirectEncodeVB;
	CCritSec m_ReceiveLock;

	CMPEGFilterInterface* m_pInterface;
    CMPEGFilter* m_pFilter;
	CEncodeErdLib* m_pEncode;
	CLicense* m_pLicense;
	CLogoOverlay m_LogoOverlay;

	CMPEGProfile* m_pCurrentProfile;

	/* NEW_FORMAT CHANGE POINT */
	CMPEGProfile m_prElementary; // special profile for just an elementary stream -> only audio or video
	CMPEGProfile m_prMPEG1;
	CMPEGProfile m_prMPEG2;
	CMPEGProfile m_prDVDPal;
	CMPEGProfile m_prDVDNtsc;
	CMPEGProfile m_prVCDPal;
	CMPEGProfile m_prVCDNtsc;
	CMPEGProfile m_prSVCDPal;
	CMPEGProfile m_prSVCDNtsc;
	CMPEGProfile m_prSVCDNtsc_Still;
	CMPEGProfile m_prSVCDPal_Still;
	CMPEGProfile m_prVCDNtsc_Still;
	CMPEGProfile m_prVCDPal_Still;
	CMPEGProfile m_prMP4;
	CMPEGProfile m_prMP4IPod;
	CMPEGProfile m_prMP4IPod_Nano;
	CMPEGProfile m_prMP4IPhone;
	CMPEGProfile m_prMP4H264;
	CMPEGProfile m_prMP4QT;
	CMPEGProfile m_prMP4AVI;
	CMPEGProfile m_pr3GP;
	CMPEGProfile m_pr3G2;
	CMPEGProfile m_prPSP;
	CMPEGProfile m_prFLV;
	CMPEGProfile m_prDVB;
	CMPEGProfile m_prRM;
	CMPEGProfile m_prMPEG2_HD;

	CAMEvent m_eventIsPrimed;
	
	wchar_t m_szOutputFile[1024];
	wchar_t m_szLicense[1024];
	wchar_t m_szEncodeLibrary[1024];
	bool  m_bPrimed;
	bool  m_bStopped;
	bool  m_bLicensed;
	bool  m_bLicensedMP4;
	bool  m_bAuthenticated;
	bool  m_bHasAudio;
	bool  m_bHasVideo;
	bool  m_bMultiplex;
	int   m_iStreamCount;
	int   m_iStreamsStopped;

	bool m_bAudioLocked;

	DWORD m_dwSleep;

	REFERENCE_TIME m_rtCurrentVideo;
	REFERENCE_TIME m_rtCurrentAudio;
	__int64 m_nVideoFramesReceived;
	__int64 m_nAudioSamplesReceived;
	__int64 m_nVideoFramesReceivedSincePause;
	__int64 m_nAudioSamplesReceivedSincePause;
};