// MPEGFilterInterface.h: interface for the CMPEGFilterInterface class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MPEGFILTERINTERFACE_H__385FE1A1_9A58_40FE_BEAB_085711A93D4D__INCLUDED_)
#define AFX_MPEGFILTERINTERFACE_H__385FE1A1_9A58_40FE_BEAB_085711A93D4D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "mpeginputpin.h"
#include "mpegobj.h"

class CMPEGFilterInterface : public CUnknown, 
							 public IStandardMpegEncoder, 
							 public IStandardMpegEncoderStats
{
public:
	DECLARE_IUNKNOWN

	CMPEGFilterInterface();
	virtual ~CMPEGFilterInterface();

	// mpegenc
	STDMETHODIMP GetProfile(SystemsOutputFormat systemsFormat, Constraint constraint, IStandardMpegEncoderProfile** pProfile);
	STDMETHODIMP GetSelectedProfile(IStandardMpegEncoderProfile** pProfile);
	STDMETHODIMP SelectProfile(IStandardMpegEncoderProfile* pProfile);
	STDMETHODIMP SelectFormat(SystemsOutputFormat systemsFormat, Constraint constraint);
	STDMETHODIMP SetFilterLicenseKey(BSTR strLicense);
	STDMETHODIMP SaveSettings(BSTR strKey); 
	STDMETHODIMP LoadSettings(BSTR strKey);
	STDMETHODIMP PassThruCmd(BSTR strCmd, long nCmd, double dCmd, BYTE* pCmd);
	STDMETHODIMP SetErrorBoxDisplay(BOOL bVal);
	STDMETHODIMP SetPass(long n);
	STDMETHODIMP SetSourceFramerate(double dSourceFramerate, double * dRequiredInputFramerate);
	STDMETHODIMP ActivateAudioVideoOutputPins(BOOL bVal);
	STDMETHODIMP GetAudioVideoOutputPinsActivated(BOOL* bVal);
	STDMETHODIMP EnableFramerateCorrection(BOOL bCorrectVideo, BOOL bCorrectAudio);
	

	// stats
	STDMETHODIMP GetFramesEncoded(long * pllFramesEncoded);
	STDMETHODIMP GetWrittenBytes(long * pllBytesWritten);
	STDMETHODIMP GetStatusString(BSTR* strValue);
	STDMETHODIMP GetVideoFramesDropped(long * lFramesDropped);
	STDMETHODIMP GetAudioTimeCorrected(double * dTimeCorrected);

	// helper
	bool IsFrameRateSupported(double dFPS);

	CMPEGObj* m_pObj;
};

#endif // !defined(AFX_MPEGFILTERINTERFACE_H__385FE1A1_9A58_40FE_BEAB_085711A93D4D__INCLUDED_)
