#pragma once

#include "codec.h"
#include "videostream.h"
#include "audiostream.h"
struct IWMProfile;

class CProfile
{
	friend class CWMVProfile;
public:
	CProfile(void);
	~CProfile(void);

	HRESULT Load(IWMProfile* pWMProfile);
	IWMProfile* GetWMProfile(void);
	bool GetHasVideo(void);
	bool GetHasAudio(void);
	CVideoStream* GetVideoStream(void);
	CAudioStream* GetAudioStream(void);
	void SetCodecArray(CCodecArray* pVideoCodecArray, CCodecArray* pAudioCodecArray, long nBestVideo, long nBestAudio);
	HRESULT CreateNew(void);
	void ConfigureProfileFromSystemID(BSTR strID, bool bUpdate);
	void SetSourceInfo(double fps, long cx, long cy, long vbitrate, long abitrate);
	void SetSupportedStreams(bool bVideo, bool bAudio);
	void DestroyObjects(void);

private:
	HRESULT GetSupportedStreams();
	HRESULT GetNameAndDescription();

private:
	bool m_bHasAudio; // does it have an audio stream?
	bool m_bHasVideo; // does it have a video stream?
	
	CVideoStream m_VideoStream; // video compression
	CAudioStream m_AudioStream; // audio compression

	CComBSTR m_strSystemID;
	CComBSTR m_strName; // profile name. retrieved from sys list
    CComBSTR m_strDescription; // profile desc, loaded from list
	CCodecArray* m_pVideoCodecArray;
	CCodecArray* m_pAudioCodecArray;

	long m_nVideoCodecCount;
	long m_nBestVideoCodec;
	long m_nBestAudioCodec;
	long m_nBestAudioFormat;

	CComPtr<IWMProfile> m_pIWMProfile; // profile object with the profile data
};
