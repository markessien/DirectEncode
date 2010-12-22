// MPEGSettings.cpp: implementation of the CMPEGSettings class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MPEGSettings.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include ".\mpegsettings.h"


CMPEGSettings::CMPEGSettings(void)
{
	
	videoOutputFormat = (_VideoOutputFormat)0;

	/*
	audioOutputFormat = 0;
	systemsOutputFormat = 0;
	constraint = 0;
	bitrateMode = 0;
	encodeMode = 0;
	aspectRatio = 0;
	*/
	nEncodePass = 0;
	nAudioBitrate = 0;
	nAudioChannels = 0;
	nAudioSampleRate = 0;
	bShowPreview = TRUE;
	dOutputFramerate = 0;
	nOutputHeight = 0;
	nOutputWidth = 0;
	nVideoBitrate = 0;
	nVideoBitrateMax = 0;
	nVideoBitrateMin = 0;
	nVideoQuality = 0;
	bPerformMultiplex = TRUE;
	dStartTime = 0;
	dEndTime = 0;
}

CMPEGSettings::~CMPEGSettings(void)
{
}

void CMPEGSettings::LoadSettingsFromFilter(CComPtr<IBaseFilter> pFilter)
{
	CComQIPtr<IStandardMpegEncoder> pMPEGWriterProps(pFilter);
	CComQIPtr<IStandardMpegEncoderProfile> pMPEGProfile(pFilter);
	CComQIPtr<IStandardMpegMultiplexerProfile> pMpegMuxProfile(pMPEGProfile);

	pMPEGProfile->GetVideoFormat(&videoOutputFormat);
	pMPEGProfile->GetAudioFormat(&audioOutputFormat);
	pMPEGProfile->GetSystemsFormat(&systemsOutputFormat);
	pMPEGProfile->GetConstraint(&constraint);
	pMPEGProfile->GetVideoVBRMode(&bitrateMode);
	pMPEGProfile->GetEncodeMode(&encodeMode);
	pMPEGProfile->GetAspectRatio(&aspectRatio);
	pMPEGProfile->GetAudioBitrate(&nAudioBitrate);
	pMPEGProfile->GetAudioChannels(&nAudioChannels);
	pMPEGProfile->GetAudioSampleRate(&nAudioSampleRate);
	pMPEGProfile->GetFramerate(&dOutputFramerate);
	pMPEGProfile->GetHeight(&nOutputHeight);
	pMPEGProfile->GetWidth(&nOutputWidth);
	pMPEGProfile->GetVideoBitrate(&nVideoBitrate);
	pMPEGProfile->GetVideoBitrateMin(&nVideoBitrateMin);
	pMPEGProfile->GetVideoBitrateMax(&nVideoBitrateMax);
	pMPEGProfile->GetVideoQuality(&nVideoQuality);

	LONG b = 0;
	pMpegMuxProfile->GetMultiplexStreams(&b);
	bPerformMultiplex = b != 0;

	b = 0;
	pMPEGProfile->GetClosedGOP(&b);
	bClosedGOP = b != 0;
}

void CMPEGSettings::ApplySettingsToFilter(CComPtr<IBaseFilter> pFilter)
{
	CComQIPtr<IStandardMpegEncoder> pMPEGWriterProps(pFilter);
	CComQIPtr<IStandardMpegEncoderProfile> pMPEGProfile(pFilter);
	CComQIPtr<IStandardMpegMultiplexerProfile> pMpegMuxProfile(pMPEGProfile);

	pMPEGProfile->SetAudioFormat(audioOutputFormat);
	pMPEGProfile->SetSystemsFormat(systemsOutputFormat);
	pMPEGProfile->SetEncodeMode(encodeMode);
	pMPEGProfile->SetAspectRatio(aspectRatio);
	pMPEGProfile->SetAudioChannels(nAudioChannels);
	pMPEGProfile->SetVideoBitrateMin(nVideoBitrateMin);
	pMPEGProfile->SetVideoBitrateMax(nVideoBitrateMax);
	pMPEGProfile->SetVideoBitrate(nVideoBitrate);
	pMPEGProfile->SetAudioBitrate(nAudioBitrate);
	pMPEGProfile->SetFramerate(dOutputFramerate);
	pMPEGProfile->SetHeight(nOutputHeight);
	pMPEGProfile->SetWidth(nOutputWidth);
	pMPEGProfile->SetVideoVBRMode(bitrateMode);
	pMPEGProfile->SetVideoQuality(nVideoQuality);
	pMPEGProfile->SetAudioSampleRate(nAudioSampleRate);
	pMPEGProfile->SetConstraint(constraint);
	pMPEGProfile->SetVideoFormat(videoOutputFormat);
	pMPEGProfile->SetClosedGOP(bClosedGOP);

	if (pMpegMuxProfile)
	{
		if (bPerformMultiplex)
		{
			pMpegMuxProfile->SetMultiplexOnStop(false);
			pMpegMuxProfile->SetOnFlyMultiplex(true);
			pMpegMuxProfile->SetMultiplexStreams(true);
			pMpegMuxProfile->SetDeleteElementaryStreams(true);
		}
		else
		{
			pMpegMuxProfile->SetMultiplexOnStop(false);
			pMpegMuxProfile->SetOnFlyMultiplex(false);
			pMpegMuxProfile->SetMultiplexStreams(false);
			pMpegMuxProfile->SetDeleteElementaryStreams(false);
		}
	}
}

void CMPEGSettings::SaveSettings(CComBSTR strPath)
{
}

void CMPEGSettings::LoadSettings(CComBSTR strPath)
{
}
