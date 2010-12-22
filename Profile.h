// Profile.h: interface for the CMPEGProfile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROFILE_H__87AAFACA_50FA_4C48_BCCD_FF8006D1EC47__INCLUDED_)
#define AFX_PROFILE_H__87AAFACA_50FA_4C48_BCCD_FF8006D1EC47__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// change this to point at the same file in your install dirextory
#include "libraries/erdmpglib/erdmpglib.h"

class CMPEGProfile;

class CMPEGMultiplexProfile : public CUnknown, public IStandardMpegMultiplexerProfile
{
public:
	DECLARE_IUNKNOWN

	CMPEGMultiplexProfile();
	virtual ~CMPEGMultiplexProfile();

	// multiplex
	STDMETHODIMP SetDeleteElementaryStreams(BOOL bDelete);
	STDMETHODIMP GetDeleteElementaryStreams(BOOL * bDelete);
	STDMETHODIMP SetMultiplexRate(long nRate);
	STDMETHODIMP GetMultiplexRate(long * pnMux);
	STDMETHODIMP SetMultiplexPacketSize(long nSize);
	STDMETHODIMP GetMultiplexPacketSize(long * pnSize);
	STDMETHODIMP SetMultiplexPreload(float fPreload);
	STDMETHODIMP SetMultiplexMaxDelay(float fMaxDelay);
	STDMETHODIMP GetMultiplexPreload(float * pfMaxDelay);
	STDMETHODIMP SetMultiplexStreams(BOOL bMux);
	STDMETHODIMP GetMultiplexStreams(BOOL * bMux);
	STDMETHODIMP SetMultiplexFormat(SystemsOutputFormat format);
	STDMETHODIMP GetMultiplexFormat(SystemsOutputFormat *format);
	STDMETHODIMP AddMultiplexFile(BSTR strPath);
	STDMETHODIMP SetOnFlyMultiplex(BOOL bOnFlyMultiplex);
	STDMETHODIMP GetOnFlyMultiplex(BOOL * pbOnFlyMultiplex);
	STDMETHODIMP SetMultiplexFrameBalance(BOOL bVal);
	STDMETHODIMP SetMultiplexOnStop(BOOL bVal);
	STDMETHODIMP GetMultiplexProgress(double* dProgress);

public:
	EncodeParameters* m_pEncodeParameters;
};

class CMPEGProfile : public CUnknown, 
					 public IStandardMpegEncoderProfile

{
public:
	friend class CMPEGObj;

	DECLARE_IUNKNOWN

	CMPEGProfile();
	virtual ~CMPEGProfile();

	STDMETHODIMP SetAudioBitrateMin(long nBitrate);
	STDMETHODIMP GetAudioBitrateMin(long * nBitrate);
	STDMETHODIMP SetAudioBitrateMax(long nBitrate);
	STDMETHODIMP GetAudioBitrateMax(long * nBitrate);
	STDMETHODIMP ConfigureForSystemsFormat(SystemsOutputFormat systemsFormat, Constraint constraint);
	STDMETHODIMP SaveProfile(BSTR strKey);
	STDMETHODIMP LoadProfile(BSTR strKey);
	STDMETHODIMP GetProfileName(BSTR* strName);
	STDMETHODIMP GetHeight(long * pnHeight);
	STDMETHODIMP SetHeight(long nHeight);
	STDMETHODIMP SetFramerate(double fps);
	STDMETHODIMP GetFramerate(double* fps);
	STDMETHODIMP SetWidth(long nWidth);
	STDMETHODIMP GetWidth(long* nWidth);
	STDMETHODIMP SetVideoBitrate(long nBitrate);
	STDMETHODIMP GetVideoBitrate(long * nBitrate);
	STDMETHODIMP SetAudioBitrate(long nBitrate);
	STDMETHODIMP GetAudioBitrate(long * nBitrate);
	STDMETHODIMP SetVideoQuality(long nQualityPercent);
	STDMETHODIMP GetVideoQuality(long * nQualityPercent);
	STDMETHODIMP SetVideoVBRMode( BitrateMode vbrMode);
	STDMETHODIMP GetVideoVBRMode(BitrateMode * pvbrMode);
	STDMETHODIMP SetVideoVBVBufferSize( long vbvlen);
	STDMETHODIMP GetVideoVBVBufferSize(long * vbvlen);
	STDMETHODIMP SetAudioVBRMode( BitrateMode vbrMode);
	STDMETHODIMP GetAudioVBRMode(BitrateMode * vbrMode);
	STDMETHODIMP SetGOPStructure(BSTR strStructure);
	STDMETHODIMP GetGOPStructure(BSTR* pstrStructure);
	STDMETHODIMP SetAudioSampleRate(long nSampleRate); // Valid values are 44100, 48000, 32000 ONLY!
	STDMETHODIMP GetAudioSampleRate(long * pnSampleRate);
	STDMETHODIMP SetAudioChannels(long nChannelCount); // Valid values are 44100, 48000, 32000 ONLY!
	STDMETHODIMP GetAudioChannels(long * pnChannelCount);
	STDMETHODIMP SetAudioFlags(BOOL bErrorProtection, BOOL bOriginal, BOOL bCopyright, BOOL bPrivate);
	STDMETHODIMP SetEncodeMode(EncodeMode nValue);
	STDMETHODIMP GetEncodeMode(EncodeMode * pnValue);
	STDMETHODIMP SetAudioFormat(AudioOutputFormat audioFormat);
	STDMETHODIMP GetAudioFormat(AudioOutputFormat * audioFormat);
	STDMETHODIMP SetVideoFormat(VideoOutputFormat audioFormat);
	STDMETHODIMP GetVideoFormat(VideoOutputFormat * audioFormat);
	STDMETHODIMP SetSystemsFormat(SystemsOutputFormat systemsFormat);
	STDMETHODIMP GetSystemsFormat(SystemsOutputFormat * systemsFormat);
	STDMETHODIMP SetAspectRatio(AspectRatio mode);
	STDMETHODIMP GetAspectRatio(AspectRatio * pmode);
	STDMETHODIMP SetProfileAndLevel(BSTR strProfileAndLevel);
	STDMETHODIMP GetProfileAndLevel(BSTR * pstrProfileAndLevel);
	STDMETHODIMP SetMotionSearchPrecision(long nVal);
	STDMETHODIMP GetMotionSearchPrecision(long * nVal);
	STDMETHODIMP SetDetectSceneChange(BOOL bVal);
	STDMETHODIMP GetDetectSceneChange(BOOL * nVal);
	STDMETHODIMP SetSceneChangeThreshold(float f);
	STDMETHODIMP SetClosedGOP(BOOL bVal);
	STDMETHODIMP GetClosedGOP(BOOL * nVal);
	STDMETHODIMP SetOutputIntervalOfSequenceHeader(long nVal);
	STDMETHODIMP GetOutputIntervalOfSequenceHeader(long * nVal);
	STDMETHODIMP SetComments(BSTR strVal);
	STDMETHODIMP SetInformation(BSTR strTitle, BSTR strAuthor, BSTR strCopyright);
	STDMETHODIMP SetVideoQualityRange(long nMin, long nMax);
	STDMETHODIMP SetQuantBias(long nIntra, long nInter);
	STDMETHODIMP SetIDCT(long n);
	STDMETHODIMP SetStrictGOP(BOOL bVal);
	STDMETHODIMP SetGOPSize(long nGOPSize);
	STDMETHODIMP GetGOPSize(long * nGOPSize);
	STDMETHODIMP Set2PassLogFile(BSTR Path);
	STDMETHODIMP SetBWVideo(BOOL bVal);
	STDMETHODIMP SetQuantFactor(float fQuantFactor);
	STDMETHODIMP GetQuantFactor(float * pfQuantFactor);
	STDMETHODIMP SetVideoBitrateMin(long nBitrate);
	STDMETHODIMP GetVideoBitrateMin(long * nBitrate);
	STDMETHODIMP SetVideoBitrateMax(long nBitrate);
	STDMETHODIMP GetVideoBitrateMax(long * nBitrate);
	STDMETHODIMP SetConstraint(Constraint systemsConstraint);
	STDMETHODIMP GetConstraint(Constraint * systemsConstraint);
	STDMETHODIMP SetProfileName(BSTR strName);
	STDMETHODIMP SetAutoSelectBitrate(BOOL bVal);
	STDMETHODIMP GetAutoSelectBitrate(BOOL * pbVal);
	STDMETHODIMP SetAutoSelectDimensions(BOOL bVal);
	STDMETHODIMP GetAutoSelectDimensions(BOOL * pbVal);
	STDMETHODIMP SetInterlaceMode(BOOL bPreProcessDeinterlace, BOOL bInterlacedOutputDCT, BOOL bInterlacedOutputME);
	STDMETHODIMP GetInterlaceMode(BOOL * bPreProcessDeinterlace, BOOL * bInterlacedOutputDCT, BOOL * bInterlacedOutputME);

	EncodeParameters& GetEncodeParameters() {
		return m_EncodeParameters;
	}

	STDMETHODIMP NonDelegatingQueryInterface(REFIID riid, void ** ppv);

	CMPEGMultiplexProfile* GetMuxProfile() {return m_pMuxProfile;}

private:
	BOOL IsFrameRateSupported(double dFPS);
	void SetFixed(BOOL bFixed);

private:
	CMPEGObj* m_pObj;
	CMPEGMultiplexProfile* m_pMuxProfile;
	CComBSTR m_strProfileName;
	BOOL  m_bFixed;
	EncodeParameters m_EncodeParameters;
};

#endif // !defined(AFX_PROFILE_H__87AAFACA_50FA_4C48_BCCD_FF8006D1EC47__INCLUDED_)
