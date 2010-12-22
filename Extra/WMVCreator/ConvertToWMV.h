#pragma once

#define USE_OVERLAY_FILTER
#include <graph.h>
#include "profile.h"
#include "imageoverlay.h"

class CProfile;
class CCodec;

class CConvertToWMV : protected IGraphEvents, public IAMWMBufferPassCallback, public CUnknown
{

public:
	DECLARE_IUNKNOWN
	CConvertToWMV(void);
	~CConvertToWMV(void);
 
	CProfileArray* GetSystemProfiles(void);
	void LoadSystemCodecs(void);
	CProfile* GetProfile(unsigned int nIndex);
	CProfile* GetSystemProfile(unsigned int nIndex);
	// CCodec* GetSystemCodec(unsigned int nIndex);

	void ThrowError(HRESULT hr, char* pstrMsg);
	HRESULT StartConversion(void);
	HRESULT StopConversion(void);
	void SetInputFile(BSTR str);
	void SetOutputFile(BSTR str);
	HRESULT Pause(void);
	double GetDuration(void);
	double GetProgress(void);
	CComBSTR GetInputFile(void);
	CComBSTR GetOutputFile(void);
	HRESULT Seek(double d);
	CProfile* GetConversionProfile(void);
	void SetConversionProfile(CProfile* pProfile);
	CProfileArray* GetProfiles(void);

	CCodec* GetVideoCodec(unsigned int nIndex);
	CCodec* GetAudioCodec(unsigned int nIndex);

	void SetCallback(IGraphEvents* pCallback);
	HRESULT OnGraphEvent(CGraph* pGraph, long lEventCode, LONG_PTR lParam1, LONG_PTR lParam2);
	HRESULT STDMETHODCALLTYPE Notify(INSSBuffer3 *pNSSBuffer3, IPin *pPin, REFERENCE_TIME *prtStart, REFERENCE_TIME *prtEnd);
	
private:
	void AddCustomProfile(char* pstrID);

private:
	CGraph m_Graph;
	CProfileArray m_arrProfiles;
	CProfileArray m_arrSysProfiles;
	CCodecArray m_arrVideoCodecs;
	CCodecArray m_arrAudioCodecs;
	CComBSTR m_strInputFile;
	CComBSTR m_strOutputFile;
	CLogoOverlay m_logoOverlay;
	CProfile* m_pCurProfile;
	bool m_bLicensed;
	LONGLONG m_llStart;
	LONGLONG m_llEnd;
	long m_nBestVideoCodec;
	long m_nBestAudioCodec;
	IGraphEvents* m_pCallback; // we call to superclass with this
public:
	CCodecArray* GetVideoCodecs(void);
	CCodecArray* GetAudioCodecs(void);
	long GetEncodeFramerate(void);
	void SetLicensed(bool bVal);
};
