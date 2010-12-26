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
