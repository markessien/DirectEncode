// EncodeParameters.h: interface for the CEncodeParameters class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENCODEPARAMETERS_H__539E6BCF_0BDA_414F_BBD1_9CB615091C9D__INCLUDED_)
#define AFX_ENCODEPARAMETERS_H__539E6BCF_0BDA_414F_BBD1_9CB615091C9D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// #include <avcodec.h>
// #include <avformat.h>
// #include <stdio.h>
#include "erdmpglib.h"

class CEncodeParameters  
{
public:
	HRESULT SetEncodeParameter(char* pstrParameterName, char* pstrParameterValue);
	void SetEncodeParams(EncodeParameters* params);
	struct FormatResult
	{
		FormatResult() {pstrSystems = NULL; 
						pstrVideo = NULL; 
						pstrAudio = NULL; 
						bMultiplexing = true; 
						audioCodec = CODEC_ID_NONE;
						videoCodec = CODEC_ID_NONE;}

		void FreeAll();
		char* pstrSystems;
		char* pstrVideo;
		char* pstrAudio;
		bool  bMultiplexing;
		CodecID   audioCodec; // in case it changes in muxed file
		CodecID   videoCodec;
	};

	CEncodeParameters();
	virtual ~CEncodeParameters();

	EncodeParameters& GetParams() {return m_EncodeParams;}
	void ApplyConstraints();
	void SetDefaults();
	CEncodeParameters::FormatResult ConfigureForSelectedFormat();

	long GetNearestValidBitrate(long nBitrate, long nMode);

private:
	void SetText(char** pp, char* p);

	void ConfigureForStill();
	void ConfigureForMPEG4();

	FormatResult ConfigureForFLV();
	FormatResult ConfigureForVCDStill();
	FormatResult ConfigureForSVCDStill();
	FormatResult ConfigureFor3GP();
	FormatResult ConfigureForMOV();
	FormatResult ConfigureFor3G2();
	FormatResult ConfigureForPSP();
	FormatResult ConfigureForStandardMP4();
	FormatResult ConfigureForStandardMPEG1();
	FormatResult ConfigureForStandardMPEG2();
	FormatResult ConfigureForVCD();
	FormatResult ConfigureForSVCD();
	FormatResult ConfigureForDVD();
	FormatResult ConfigureForDVB();
	FormatResult ConfigureForRM();

private:
	EncodeParameters m_EncodeParams;
};

#endif // !defined(AFX_ENCODEPARAMETERS_H__539E6BCF_0BDA_414F_BBD1_9CB615091C9D__INCLUDED_)
