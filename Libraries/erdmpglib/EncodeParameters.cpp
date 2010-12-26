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

// EncodeParameters.cpp: implementation of the CEncodeParameters class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EncodeParameters.h"
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEncodeParameters::CEncodeParameters()
{
	SetDefaults();
}

CEncodeParameters::~CEncodeParameters()
{

}

void CEncodeParameters::FormatResult::FreeAll() 
{
	if (pstrSystems) 
		delete [] pstrSystems; 
	
	if (pstrVideo) 
		delete [] pstrVideo; 
	
	if (pstrAudio) 
		delete [] pstrAudio;
}


void CEncodeParameters::SetDefaults()
{
	memset(&m_EncodeParams, 0, sizeof(m_EncodeParams));
	m_EncodeParams.nOutputX = 0;
	m_EncodeParams.nOutputY = 0;
	m_EncodeParams.nOutputAudioBitrate= 64000;
	m_EncodeParams.nOutputAudioSampleRate = 44100;
	m_EncodeParams.nOutputAudioChannels = 2;
	m_EncodeParams.nOutputVideoBitrate = 400000;
	m_EncodeParams.nOutputVideoGOPSize = 12;

	m_EncodeParams.fMuxMaxDelay = 0.7f;
	m_EncodeParams.fMuxPreload = 0.5f;
	m_EncodeParams.bMultiplex = true;
	m_EncodeParams.bDirectMultiplexing = false;
	m_EncodeParams.bDeleteTmpAfterMultiplex = true;
	m_EncodeParams.fPixelAspectRatio = (float)1.3333f;
	m_EncodeParams.bDeInterlace = false;
	m_EncodeParams.nQualityMin = 2;
	m_EncodeParams.nQualityMax = 31;

}


void CEncodeParameters::ApplyConstraints()
{
	if (m_EncodeParams.nOutputX == 0)
		m_EncodeParams.nOutputX = m_EncodeParams.nInputX;

	if (m_EncodeParams.nOutputY == 0)
		m_EncodeParams.nOutputY = m_EncodeParams.nInputY;


	m_EncodeParams.nOutputXHiResStill = 704;
	m_EncodeParams.nOutputYHiResStill = 576;

	int d = m_EncodeParams.nOutputFPSDen;
	int n = m_EncodeParams.nOutputFPSNum;
	int g = 18;
	int x = m_EncodeParams.nOutputX;
	int y = m_EncodeParams.nOutputY;
	
	switch (m_EncodeParams.systemsConstraint)
	{
	case CONSTRAINT_PAL:
		{
			d = 25, n = 1, g = 15; 
			switch (m_EncodeParams.systemsOutputFormat) 
			{
				case SYSTEMSFORMAT_VCD: x = 352; y = 288; break;
				case SYSTEMSFORMAT_SVCD: x = 480; y = 576; break;
				case SYSTEMSFORMAT_DVD: x = 720; y = 576; break;
			}
		}
		break;
	case CONSTRAINT_NTSC:
		{
			d = 30000, n = 1001, g = 18;
			switch (m_EncodeParams.systemsOutputFormat) 
			{
				case SYSTEMSFORMAT_VCD: x = 352; y = 240; break;
				case SYSTEMSFORMAT_SVCD: x = 480; y = 480; break;
				case SYSTEMSFORMAT_DVD: x = 720; y = 480; break;
			}

			m_EncodeParams.nOutputXHiResStill = 480;
		}
		break;
	case CONSTRAINT_FILM:
		{
			d = 24000, n = 1001, g = 15; 
			switch (m_EncodeParams.systemsOutputFormat) 
			{
				case SYSTEMSFORMAT_VCD: x = 352; y = 288; break;
				case SYSTEMSFORMAT_SVCD: x = 352; y = 288; break;
				case SYSTEMSFORMAT_DVD: x = 720; y = 576; break;
			}
		}
		break;
	case CONSTRAINT_IPOD:
	case CONSTRAINT_IPHONE:
		{
			// ffmpeg -i "$1" -f mp4 -vcodec mpeg4 -maxrate 1000 -b 700 -qmin 3 -qmax 5 -bufsize 4096 -g 300 -acodec aac -ar 44100 -ab 192 -s 320x240 -aspect 4:3 $2.mp4

			x = 320; 
			y = 240;
			g = 300;
			m_EncodeParams.nOutputVideoBitrateMax = 700 * 1000; // maxrate
			m_EncodeParams.nOutputVideoBitrate = 700 * 1000; // bitrate = b
			m_EncodeParams.nOutputVideoBitrateMin = 700 * 1000; // maxrate
			m_EncodeParams.nQualityMin = 3; // qmin
			m_EncodeParams.nQualityMax = 5; // qmax min video quantiser scale (VBR)
			m_EncodeParams.nOutputVideoBufferSize = 4096 * 1000; //bufsize
			m_EncodeParams.nOutputAudioBitrate = 192000;
			m_EncodeParams.nOutputAudioSampleRate = 44100;

		}
		break;
	}

	m_EncodeParams.nOutputFPSDen = d;
	m_EncodeParams.nOutputFPSNum = n;
	m_EncodeParams.nOutputVideoGOPSize = g;	
	m_EncodeParams.nOutputX = x;
	m_EncodeParams.nOutputY = y;

}

void CEncodeParameters::SetText(char** pp, char* p)
{
	*pp = new char[strlen(p) + 1];
	strcpy(*pp, p);
}

void CEncodeParameters::ConfigureForStill()
{
	m_EncodeParams.vbrVideo = BITRATEMODE_MVBR;
	m_EncodeParams.bMultiplex = false;
	m_EncodeParams.bDirectMultiplexing = false;
	m_EncodeParams.bWriteSystemsFile = false;
	m_EncodeParams.bWriteAudioStream = false;
	m_EncodeParams.nOutputVideoBitrate = 6200;
	m_EncodeParams.nOutputVideoBitrateMax = 6200;
	m_EncodeParams.nOutputVideoBitrateMin = 0;
}

CEncodeParameters::FormatResult CEncodeParameters::ConfigureForVCDStill()
{
	FormatResult result;
	SetText(&(result.pstrVideo), "mpeg1video");	
	result.bMultiplexing = false;

	ApplyConstraints(); // this will set the dimensions for the low and hi res images
	ConfigureForStill();
	m_EncodeParams.nOutputVideoBufferSize =  65*1024*8;
	
	return result;
}

CEncodeParameters::FormatResult CEncodeParameters::ConfigureForSVCDStill()
{
	FormatResult result;
	SetText(&(result.pstrVideo), "mpeg2video");
	result.bMultiplexing = false;

	// note, we always create two files - a hi res and lo res
	ApplyConstraints(); // this will set the dimensions for the low and hi res images
	ConfigureForStill();
	m_EncodeParams.nOutputVideoBufferSize = 70*1024*8; // 5*1024*8;
	
	return result;
}

void CEncodeParameters::ConfigureForMPEG4()
{
	m_EncodeParams.nOutputVideoBitrate = m_EncodeParams.nOutputVideoBitrate;
	m_EncodeParams.nOutputVideoBitrateMax = m_EncodeParams.nOutputVideoBitrateMax;
	m_EncodeParams.nOutputVideoBitrateMin = m_EncodeParams.nOutputVideoBitrateMin;
	m_EncodeParams.nOutputVideoBufferSize = 4096 * 1000; //bufsize
	m_EncodeParams.nQualityMin = 1; // qmin
	m_EncodeParams.nQualityMax = 10; // qmax min video quantiser scale (VBR)

	ApplyConstraints();

	m_EncodeParams.bClosedGOP = true;

	m_EncodeParams.nMuxPacketSize = 0;
	m_EncodeParams.nMuxRate = 0;
	m_EncodeParams.fMuxPreload = 0.5; 
	m_EncodeParams.fMuxMaxDelay = (float)0.7; 
	m_EncodeParams.bUseScanOffset = false;
}

CEncodeParameters::FormatResult CEncodeParameters::ConfigureFor3GP()
{
	FormatResult result;
	SetText(&(result.pstrSystems), "mp4");
	SetText(&(result.pstrVideo), "mp4");
	SetText(&(result.pstrAudio), "amr_nb");
	// result.bMultiplexing = false;

	ConfigureForMPEG4();
	ApplyConstraints();

	return result;
}

CEncodeParameters::FormatResult CEncodeParameters::ConfigureForMOV()
{
	FormatResult result;
	SetText(&(result.pstrSystems), "mov");
	SetText(&(result.pstrVideo), "mpeg4");
	SetText(&(result.pstrAudio), "aac");
	result.bMultiplexing = m_EncodeParams.bWriteSystemsFile && m_EncodeParams.bDirectMultiplexing;

	ConfigureForMPEG4();
	ApplyConstraints();

	return result;
}

CEncodeParameters::FormatResult CEncodeParameters::ConfigureFor3G2()
{
	FormatResult result;
	SetText(&(result.pstrSystems), "mp4");
	SetText(&(result.pstrVideo), "mpeg4");
	SetText(&(result.pstrAudio), "amr_nb");
	result.bMultiplexing = m_EncodeParams.bWriteSystemsFile && m_EncodeParams.bDirectMultiplexing;

	ConfigureForMPEG4();
	ApplyConstraints();

	return result;
}




CEncodeParameters::FormatResult CEncodeParameters::ConfigureForRM()
{
	FormatResult result;
	SetText(&(result.pstrSystems), "rm");
	// SetText(&(result.pstrVideo), "flv");
	

	// SetText(&(result.pstrAudio), "mp2");
	result.bMultiplexing = m_EncodeParams.bWriteSystemsFile && m_EncodeParams.bDirectMultiplexing;

	ConfigureForMPEG4();
	ApplyConstraints();

	return result;
}

CEncodeParameters::FormatResult CEncodeParameters::ConfigureForFLV()
{
	FormatResult result;
	SetText(&(result.pstrSystems), "flv");
	// SetText(&(result.pstrVideo), "flv");
	SetText(&(result.pstrAudio), "mp2");

	if (m_EncodeParams.videoOutputFormat == VIDEOFORMAT_VP6)
		result.videoCodec = CODEC_ID_VP6;
	
	if (m_EncodeParams.audioOutputFormat == AUDIOFORMAT_MP3)
		result.audioCodec = CODEC_ID_MP3;

	result.bMultiplexing = m_EncodeParams.bWriteSystemsFile && m_EncodeParams.bDirectMultiplexing;

	ConfigureForMPEG4();
	ApplyConstraints();

	return result;
}


CEncodeParameters::FormatResult CEncodeParameters::ConfigureForPSP()
{
	FormatResult result;
	SetText(&(result.pstrSystems), "psp");
	SetText(&(result.pstrVideo), "mpeg4");
	SetText(&(result.pstrAudio), "aac");
	result.bMultiplexing = m_EncodeParams.bWriteSystemsFile && m_EncodeParams.bDirectMultiplexing;

	ConfigureForMPEG4();
	ApplyConstraints();

	return result;
}

CEncodeParameters::FormatResult CEncodeParameters::ConfigureForStandardMP4()
{
	FormatResult result;
	SetText(&(result.pstrSystems), "mp4");
	SetText(&(result.pstrVideo), "mpeg4");
	SetText(&(result.pstrAudio), "aac");
	result.bMultiplexing = m_EncodeParams.bWriteSystemsFile && m_EncodeParams.bDirectMultiplexing;

	ConfigureForMPEG4();
	ApplyConstraints();

	return result;
}

CEncodeParameters::FormatResult CEncodeParameters::ConfigureForStandardMPEG1()
{
	FormatResult result;
	SetText(&(result.pstrSystems), "mpeg");
	SetText(&(result.pstrVideo), "mpeg1video");
	SetText(&(result.pstrAudio), "mp2");
	

	m_EncodeParams.nOutputVideoBufferSize = 70*1024*8;
	m_EncodeParams.nMuxPacketSize = 2048;
	m_EncodeParams.nMuxRate = 0;
	m_EncodeParams.fMuxPreload = (float)((36000+3*1200) / 90000.0); 
	m_EncodeParams.fMuxMaxDelay = (float)0.7; 
	m_EncodeParams.bUseScanOffset = false;

	ApplyConstraints();

	return result;
}

CEncodeParameters::FormatResult CEncodeParameters::ConfigureForDVB()
{
	FormatResult result;
	SetText(&(result.pstrSystems), "mpegts");
	SetText(&(result.pstrVideo), "mpeg2video");

	if (m_EncodeParams.audioOutputFormat == AUDIOFORMAT_AC3)
	{
		result.audioCodec = CODEC_ID_AC3;
		SetText(&(result.pstrAudio), "ac3");
	}
	else
		SetText(&(result.pstrAudio), "mp2");
	
	m_EncodeParams.nOutputVideoBufferSize = 224*1024*8;
	m_EncodeParams.nMuxPacketSize = 2048;
	m_EncodeParams.nMuxRate = 0;
	m_EncodeParams.fMuxPreload = (float)0.5; 
	m_EncodeParams.fMuxMaxDelay = (float)0.7; 
	m_EncodeParams.bUseScanOffset = false;

	ApplyConstraints();

	return result;
}

CEncodeParameters::FormatResult CEncodeParameters::ConfigureForStandardMPEG2()
{
	FormatResult result;
	SetText(&(result.pstrSystems), "vob");
	SetText(&(result.pstrVideo), "mpeg2video");

	if (m_EncodeParams.audioOutputFormat == AUDIOFORMAT_AC3)
	{
		result.audioCodec = CODEC_ID_AC3;
		SetText(&(result.pstrAudio), "ac3");
	}
	else
		SetText(&(result.pstrAudio), "mp2");
	
	m_EncodeParams.nOutputVideoBufferSize = 224*1024*8;
	m_EncodeParams.nMuxPacketSize = 2048;
	m_EncodeParams.nMuxRate = 0;
	m_EncodeParams.fMuxPreload = (float)0.5; 
	m_EncodeParams.fMuxMaxDelay = (float)0.7; 
	m_EncodeParams.bUseScanOffset = false;

	ApplyConstraints();

	return result;
}

CEncodeParameters::FormatResult CEncodeParameters::ConfigureForVCD()
{
	/*
	        opt_video_codec("mpeg1video");
        opt_audio_codec("mp2");
        opt_format("vcd");

        opt_frame_size(norm ? "352x240" : "352x288");
        opt_frame_rate(frame_rates[norm]);
        opt_default("gop", norm ? "18" : "15");

        opt_default("b", "1150000");
        opt_default("maxrate", "1150000");
        opt_default("minrate", "1150000");
        opt_default("bufsize", "327680"); // 40*1024*8;

        opt_default("ab", "224000");
        audio_sample_rate = 44100;
        audio_channels = 2;

        opt_default("packetsize", "2324");
        opt_default("muxrate", "1411200"); // 2352 * 75 * 8;

        /* We have to offset the PTS, so that it is consistent with the SCR.
           SCR starts at 36000, but the first two packs contain only padding
           and the first pack from the other stream, respectively, may also have
           been written before.
           So the real data starts at SCR 36000+3*1200. */
        // mux_preload= (36000+3*1200) / 90000.0; //0.44

	FormatResult result;
	SetText(&(result.pstrSystems), "vcd");
	SetText(&(result.pstrVideo), "mpeg1video");
	SetText(&(result.pstrAudio), "mp2");

    m_EncodeParams.nMuxPacketSize= 2324;
    m_EncodeParams.nMuxRate= 2352 * 75 * 8;
	m_EncodeParams.nOutputVideoBufferSize = 40*1024*8;
    m_EncodeParams.fMuxPreload= (float)((36000+3*1200) / 90000.0); //0.44 // ask god to give you the faith to accept what you cannot understand
	m_EncodeParams.fMuxMaxDelay = (float)0.7; //(36000+3*1200) / 90000.0; 
	m_EncodeParams.bUseScanOffset = false;

	ApplyConstraints();

	return result;
}

CEncodeParameters::FormatResult CEncodeParameters::ConfigureForSVCD()
{
	FormatResult result;
	SetText(&(result.pstrSystems), "vob");
	SetText(&(result.pstrVideo), "mpeg2video");

	if (m_EncodeParams.audioOutputFormat == AUDIOFORMAT_AC3)
	{
		result.audioCodec = CODEC_ID_AC3;
		SetText(&(result.pstrAudio), "ac3");
	}
	else
		SetText(&(result.pstrAudio), "mp2");
	

	m_EncodeParams.nOutputVideoBufferSize = 224*1024*8;

    m_EncodeParams.nMuxPacketSize= 2324;
	m_EncodeParams.nMuxRate= 0;
	m_EncodeParams.fMuxPreload= (float)0.5;
	m_EncodeParams.fMuxMaxDelay = (float)0.7;
    m_EncodeParams.bUseScanOffset = true;

	ApplyConstraints();

	return result;
}

CEncodeParameters::FormatResult CEncodeParameters::ConfigureForDVD()
{
	FormatResult result;
	SetText(&(result.pstrSystems), "dvd");
	SetText(&(result.pstrVideo), "mpeg2video");

	if (m_EncodeParams.audioOutputFormat == AUDIOFORMAT_AC3)
	{
		result.audioCodec = CODEC_ID_AC3;
		SetText(&(result.pstrAudio), "ac3");
	}
	else if (m_EncodeParams.audioOutputFormat == AUDIOFORMAT_WAV)
	{
		SetText(&(result.pstrAudio), "wav");
	}
	else
		SetText(&(result.pstrAudio), "mp2");
	

	m_EncodeParams.nOutputVideoBufferSize = 224*1024*8;

 	m_EncodeParams.nMuxPacketSize = 2048;
	m_EncodeParams.nMuxRate = 10080000;
	m_EncodeParams.fMuxPreload = (float)0.5;
	m_EncodeParams.fMuxMaxDelay = (float)0.7;
	m_EncodeParams.bUseScanOffset = false;

	ApplyConstraints();

	return result;
}

long CEncodeParameters::GetNearestValidBitrate(long nBitrate, long nMode)
{
	if (nMode == 0) // mp2
	{
		int bitrates[] = {32000, 48000, 56000, 64000, 80000, 96000, 112000, 128000, 160000, 192000, 224000, 256000, 320000, 384000};
		for (int i=0;i<(sizeof(bitrates) / sizeof(int)) - 1;i++)
		{
			if (nBitrate >= bitrates[i] &&
				nBitrate < bitrates[i + 1])
				return bitrates[i];
		}

		if (nBitrate >= 384000)
			return 384000;

		if (nBitrate < 32000)
			return 32000;

		_ASSERT(FALSE);
	}
	else if (nMode == 1) // mp2
	{
	
		int bitrates[] = {32000, 64000, 96000, 128000, 160000, 192000, 224000, 256000, 288000, 320000, 352000, 384000, 416000, 448000};
		for (int i=0;i<(sizeof(bitrates) / sizeof(int)) - 1;i++)
		{
			if (nBitrate >= bitrates[i] &&
				nBitrate < bitrates[i + 1])
				return bitrates[i];
		}

		if (nBitrate >= 448000)
			return 448000;

		if (nBitrate < 32000)
			return 32000;

		_ASSERT(FALSE);
	}

	_ASSERT(FALSE);
	return 128000;
}


CEncodeParameters::FormatResult CEncodeParameters::ConfigureForSelectedFormat()
{
	/* NEW_FORMAT CHANGE POINT */

	FormatResult result;
	result.bMultiplexing = m_EncodeParams.bWriteSystemsFile && m_EncodeParams.bDirectMultiplexing;

	switch (m_EncodeParams.systemsOutputFormat)
	{
	case SYSTEMSFORMAT_VCD_STILL:  result = ConfigureForVCDStill(); break;
	case SYSTEMSFORMAT_SVCD_STILL: result = ConfigureForSVCDStill(); break;
	case SYSTEMSFORMAT_3GP:        result = ConfigureFor3GP();break;  
	case SYSTEMSFORMAT_FLV:        result = ConfigureForFLV();break;  
	case SYSTEMSFORMAT_MOV:        result = ConfigureForMOV();break;
	case SYSTEMSFORMAT_3G2:        result = ConfigureFor3G2();break;
	case SYSTEMSFORMAT_PSP:        result = ConfigureForPSP();break; 
	case SYSTEMSFORMAT_MP4:        result = ConfigureForStandardMP4();break;
	case SYSTEMSFORMAT_MPEG1:      result = ConfigureForStandardMPEG1(); break;
	case SYSTEMSFORMAT_MPEG2:      result = ConfigureForStandardMPEG2(); break;
	case SYSTEMSFORMAT_VCD:        result = ConfigureForVCD(); break;
	case SYSTEMSFORMAT_SVCD:       result = ConfigureForSVCD(); break;
	case SYSTEMSFORMAT_DVD:        result = ConfigureForDVD(); break;
	case SYSTEMSFORMAT_DVB:        result = ConfigureForDVB(); break;
	case SYSTEMSFORMAT_RM:         result = ConfigureForRM(); break;
	default:
		_ASSERT(FALSE);
		result = ConfigureForStandardMPEG1();
	}


	if ((m_EncodeParams.nOutputFPSDen == 0 ||
		m_EncodeParams.nOutputFPSNum == 0) &&
		m_EncodeParams.dOutputFPS > 0)
	{
		double fps = m_EncodeParams.dOutputFPS;
		if (FLOAT_EQ(fps, 29.97))
		{
			m_EncodeParams.nOutputFPSDen = 30000;
			m_EncodeParams.nOutputFPSNum = 1001;
		}
		else if (FLOAT_EQ(fps, 23.976))
		{
			m_EncodeParams.nOutputFPSDen = 24000;
			m_EncodeParams.nOutputFPSNum = 1001;
		}
		else if (FLOAT_EQ(fps, 59.94))
		{
			m_EncodeParams.nOutputFPSDen = 60000;
			m_EncodeParams.nOutputFPSNum = 1001;
		}
		else
		{
			m_EncodeParams.nOutputFPSDen = (long)fps;
			m_EncodeParams.nOutputFPSNum = 1;
		}
	}
	else if (m_EncodeParams.nOutputFPSDen == 0 || m_EncodeParams.nOutputFPSNum == 0)
	{
		m_EncodeParams.nOutputFPSDen = 25;
		m_EncodeParams.nOutputFPSNum = 1;
	}


	if (m_EncodeParams.audioOutputFormat == AUDIOFORMAT_AC3)
	{
		// Allowed bitrates for AC3 
		// {0, 32, 64, 96, 128, 160, 192, 224, 256, 288, 320, 352, 384, 416, 448 },

		m_EncodeParams.nOutputAudioBitrate = GetNearestValidBitrate(m_EncodeParams.nOutputAudioBitrate, 1);
	}
	else if (m_EncodeParams.audioOutputFormat == AUDIOFORMAT_MP2)
	{
		// 0, 32, 48, 56, 64, 80, 96, 112, 128, 160, 192, 224, 256, 320, 384
		
		m_EncodeParams.nOutputAudioBitrate = GetNearestValidBitrate(m_EncodeParams.nOutputAudioBitrate, 0);

	}

	if (m_EncodeParams.vbrVideo == BITRATEMODE_CBR)
	{
		m_EncodeParams.nOutputVideoBitrateMax = m_EncodeParams.nOutputVideoBitrate;
		m_EncodeParams.nOutputVideoBitrateMin = m_EncodeParams.nOutputVideoBitrate;
	}

	return result;
}

void CEncodeParameters::SetEncodeParams(EncodeParameters *params)
{
	memcpy(&m_EncodeParams, params, sizeof(m_EncodeParams));
}


HRESULT CEncodeParameters::SetEncodeParameter(char* pstrParameterName, char* pstrParameterValue)
{
	if (strcmp(pstrParameterName, "szOutputFile") == 0) {
		strcpy(m_EncodeParams.szOutputFile, pstrParameterValue);
	}

	if (strcmp(pstrParameterName, "wfexAudioSrc.cbSize") == 0)
		m_EncodeParams.wfexAudioSrc.cbSize = atol(pstrParameterValue);

	if (strcmp(pstrParameterName, "wfexAudioSrc.nAvgBytesPerSec") == 0)
		m_EncodeParams.wfexAudioSrc.nAvgBytesPerSec = atol(pstrParameterValue);

	if (strcmp(pstrParameterName, "wfexAudioSrc.nBlockAlign") == 0)
		m_EncodeParams.wfexAudioSrc.nBlockAlign = atol(pstrParameterValue);

	if (strcmp(pstrParameterName, "wfexAudioSrc.nChannels") == 0)
		m_EncodeParams.wfexAudioSrc.nChannels = atol(pstrParameterValue);

	if (strcmp(pstrParameterName, "wfexAudioSrc.nSamplesPerSec") == 0)
		m_EncodeParams.wfexAudioSrc.nSamplesPerSec = atol(pstrParameterValue);

	if (strcmp(pstrParameterName, "wfexAudioSrc.wBitsPerSample") == 0)
		m_EncodeParams.wfexAudioSrc.wBitsPerSample = atol(pstrParameterValue);

	if (strcmp(pstrParameterName, "wfexAudioSrc.wFormatTag") == 0)
		m_EncodeParams.wfexAudioSrc.wFormatTag = atol(pstrParameterValue);

	if (strcmp(pstrParameterName, "nOutputX") == 0)
		m_EncodeParams.nOutputX = atol(pstrParameterValue);

	if (strcmp(pstrParameterName, "nOutputY") == 0)
		m_EncodeParams.nOutputY = atol(pstrParameterValue);

	if (strcmp(pstrParameterName, "nInputX") == 0)
		m_EncodeParams.nInputX = atol(pstrParameterValue);

	if (strcmp(pstrParameterName, "nInputY") == 0)
		m_EncodeParams.nInputY = atol(pstrParameterValue);

	if (strcmp(pstrParameterName, "nOutputXHiResStill") == 0)
		m_EncodeParams.nOutputXHiResStill = atol(pstrParameterValue);

	if (strcmp(pstrParameterName, "nOutputYHiResStill") == 0)
		m_EncodeParams.nOutputYHiResStill = atol(pstrParameterValue);

	if (strcmp(pstrParameterName, "videoOutputFormat") == 0)
		m_EncodeParams.videoOutputFormat = (EnumVideoOutputFormat)atol(pstrParameterValue);

	if (strcmp(pstrParameterName, "audioOutputFormat") == 0)
		m_EncodeParams.audioOutputFormat = (EnumAudioOutputFormat)atol(pstrParameterValue);

	if (strcmp(pstrParameterName, "systemsOutputFormat") == 0)
		m_EncodeParams.systemsOutputFormat = (EnumSystemsOutputFormat)atol(pstrParameterValue);

	if (strcmp(pstrParameterName, "multiplexFormat") == 0)
		m_EncodeParams.multiplexFormat = (EnumSystemsOutputFormat)atol(pstrParameterValue);

	if (strcmp(pstrParameterName, "systemsConstraint") == 0)
		m_EncodeParams.systemsConstraint = (EnumConstraint)atol(pstrParameterValue);

	if (strcmp(pstrParameterName, "nOutputAudioBitrate") == 0)
		m_EncodeParams.nOutputAudioBitrate = atol(pstrParameterValue);

	if (strcmp(pstrParameterName, "nOutputAudioSampleRate") == 0)
		m_EncodeParams.nOutputAudioSampleRate = atol(pstrParameterValue);

	if (strcmp(pstrParameterName, "nOutputAudioChannels") == 0)
		m_EncodeParams.nOutputAudioChannels = atol(pstrParameterValue);

	if (strcmp(pstrParameterName, "nOutputVideoBitrate") == 0)
		m_EncodeParams.nOutputVideoBitrate = atol(pstrParameterValue);

	if (strcmp(pstrParameterName, "nOutputVideoGOPSize") == 0)
		m_EncodeParams.nOutputVideoGOPSize = atol(pstrParameterValue);

	if (strcmp(pstrParameterName, "nOutputVideoQuality") == 0)
		m_EncodeParams.nOutputVideoQuality = atol(pstrParameterValue);

	if (strcmp(pstrParameterName, "nOutputVideoBitrateMax") == 0)
		m_EncodeParams.nOutputVideoBitrateMax = atol(pstrParameterValue);

	if (strcmp(pstrParameterName, "nOutputVideoBitrateMin") == 0)
		m_EncodeParams.nOutputVideoBitrateMin = atol(pstrParameterValue);

	if (strcmp(pstrParameterName, "nOutputAudioBitrateMax") == 0)
		m_EncodeParams.nOutputAudioBitrateMax = atol(pstrParameterValue);

	if (strcmp(pstrParameterName, "nOutputAudioBitrateMin") == 0)
		m_EncodeParams.nOutputAudioBitrateMin = atol(pstrParameterValue);

	if (strcmp(pstrParameterName, "nOutputVideoBufferSize") == 0)
		m_EncodeParams.nOutputVideoBufferSize = atol(pstrParameterValue);

	if (strcmp(pstrParameterName, "fPixelAspectRatio") == 0)
		m_EncodeParams.fPixelAspectRatio = (float)atof(pstrParameterValue);

	if (strcmp(pstrParameterName, "dInputFPS") == 0)
		m_EncodeParams.dInputFPS = atol(pstrParameterValue);

	if (strcmp(pstrParameterName, "dOutputFPS") == 0)
		m_EncodeParams.dOutputFPS = atol(pstrParameterValue);

	if (strcmp(pstrParameterName, "nOutputFPSDen") == 0)
		m_EncodeParams.nOutputFPSDen = atol(pstrParameterValue);

	if (strcmp(pstrParameterName, "nOutputFPSNum") == 0)
		m_EncodeParams.nOutputFPSNum = atol(pstrParameterValue);

	if (strcmp(pstrParameterName, "nMuxPacketSize") == 0)
		m_EncodeParams.nMuxPacketSize = atol(pstrParameterValue);

	if (strcmp(pstrParameterName, "nMuxRate") == 0)
		m_EncodeParams.nMuxRate = atol(pstrParameterValue);

	if (strcmp(pstrParameterName, "fMuxPreload") == 0)
		m_EncodeParams.fMuxPreload = (float)atof(pstrParameterValue);

	if (strcmp(pstrParameterName, "fMuxMaxDelay") == 0)
		m_EncodeParams.fMuxMaxDelay = (float)atof(pstrParameterValue);

	if (strcmp(pstrParameterName, "aspectRatio") == 0)
		m_EncodeParams.aspectRatio = (EnumAspectRatio)atol(pstrParameterValue);

	if (strcmp(pstrParameterName, "bUseScanOffset") == 0)
		m_EncodeParams.bUseScanOffset = atol(pstrParameterValue) != 0;

	if (strcmp(pstrParameterName, "vbrVideo") == 0)
		m_EncodeParams.vbrVideo = (EnumBitrateMode)atol(pstrParameterValue);

	if (strcmp(pstrParameterName, "vbrAudio") == 0)
		m_EncodeParams.vbrAudio = (EnumBitrateMode)atol(pstrParameterValue);

	if (strcmp(pstrParameterName, "bWriteVideoStream") == 0)
		m_EncodeParams.bWriteVideoStream = atol(pstrParameterValue)!= 0;

	if (strcmp(pstrParameterName, "bWriteAudioStream") == 0)
		m_EncodeParams.bWriteAudioStream = atol(pstrParameterValue) != 0;

	if (strcmp(pstrParameterName, "bWriteSystemsFile") == 0)
		m_EncodeParams.bWriteSystemsFile = atol(pstrParameterValue)!= 0;

	if (strcmp(pstrParameterName, "bErrorProtection") == 0)
		m_EncodeParams.bErrorProtection = atol(pstrParameterValue)!= 0;

	if (strcmp(pstrParameterName, "bOriginal") == 0)
		m_EncodeParams.bOriginal = atol(pstrParameterValue)!= 0;

	if (strcmp(pstrParameterName, "bCopyright") == 0)
		m_EncodeParams.bCopyright = atol(pstrParameterValue)!= 0;

	if (strcmp(pstrParameterName, "bPrivate") == 0)
		m_EncodeParams.bPrivate = atol(pstrParameterValue)!= 0;

	if (strcmp(pstrParameterName, "bMultiplex") == 0)
		m_EncodeParams.bMultiplex = atol(pstrParameterValue)!= 0;

	if (strcmp(pstrParameterName, "encodeMode") == 0)
		m_EncodeParams.encodeMode = (EnumEncodeMode)atol(pstrParameterValue);

	if (strcmp(pstrParameterName, "bDirectMultiplexing") == 0)
		m_EncodeParams.bDirectMultiplexing = atol(pstrParameterValue) != 0;

	if (strcmp(pstrParameterName, "bUseVideoBitrates") == 0)
		m_EncodeParams.bUseVideoBitrates = atol(pstrParameterValue) != 0;

	if (strcmp(pstrParameterName, "bUseAudioBitrates") == 0)
		m_EncodeParams.bUseAudioBitrates = atol(pstrParameterValue) != 0;

	if (strcmp(pstrParameterName, "bDeleteTmpAfterMultiplex") == 0)
		m_EncodeParams.bDeleteTmpAfterMultiplex = atol(pstrParameterValue) != 0;

	if (strcmp(pstrParameterName, "bAutoSelectDimensions") == 0)
		m_EncodeParams.bAutoSelectDimensions = atol(pstrParameterValue) != 0;

	if (strcmp(pstrParameterName, "bAutoSelectBitrate") == 0)
		m_EncodeParams.bAutoSelectBitrate = atol(pstrParameterValue) != 0;

	if (strcmp(pstrParameterName, "bInputHasAudio") == 0)
		m_EncodeParams.bInputHasAudio = atol(pstrParameterValue) != 0;

	if (strcmp(pstrParameterName, "bInputHasVideo") == 0)	
		m_EncodeParams.bInputHasVideo = atol(pstrParameterValue) != 0;

	if (strcmp(pstrParameterName, "bDeInterlace") == 0)
		m_EncodeParams.bDeInterlace = atol(pstrParameterValue) != 0;

	if (strcmp(pstrParameterName, "bForceInterlaceME") == 0)
		m_EncodeParams.bForceInterlaceME = atol(pstrParameterValue) != 0;

	if (strcmp(pstrParameterName, "bForceInterlaceDCT") == 0)
		m_EncodeParams.bForceInterlaceDCT = atol(pstrParameterValue) != 0;

	if (strcmp(pstrParameterName, "bClosedGOP") == 0)	
		m_EncodeParams.bClosedGOP = atol(pstrParameterValue) != 0;

	if (strcmp(pstrParameterName, "nAdditionalFlags") == 0)
		m_EncodeParams.nAdditionalFlags = atol(pstrParameterValue);

	if (strcmp(pstrParameterName, "nVideoCodecTag") == 0)
		m_EncodeParams.nVideoCodecTag = atol(pstrParameterValue);

	if (strcmp(pstrParameterName, "bVideoStreamCopy") == 0)
		m_EncodeParams.bVideoStreamCopy = atol(pstrParameterValue) != 0;

	if (strcmp(pstrParameterName, "nVideoBitRateTolerance") == 0)	
		m_EncodeParams.nVideoBitRateTolerance = atol(pstrParameterValue);

	if (strcmp(pstrParameterName, "bIntraOnly") == 0)
		m_EncodeParams.bIntraOnly = atol(pstrParameterValue) != 0;

	if (strcmp(pstrParameterName, "nGlobalQuality") == 0)
		m_EncodeParams.nGlobalQuality = atol(pstrParameterValue);

	if (strcmp(pstrParameterName, "nIntraMatrix") == 0)
		m_EncodeParams.nIntraMatrix = atol(pstrParameterValue);

	if (strcmp(pstrParameterName, "nInterMatrix") == 0)
		m_EncodeParams.nInterMatrix = atol(pstrParameterValue);

	if (strcmp(pstrParameterName, "bShowMessageBox") == 0)
		m_EncodeParams.bShowMessageBox = atol(pstrParameterValue) != 0;

	if (strcmp(pstrParameterName, "nQualityMin") == 0)
		m_EncodeParams.nQualityMin = atol(pstrParameterValue);

	if (strcmp(pstrParameterName, "nQualityMax") == 0)
		m_EncodeParams.nQualityMax = atol(pstrParameterValue);

	if (strcmp(pstrParameterName, "nProfile") == 0)
		m_EncodeParams.nProfile = atol(pstrParameterValue);

	if (strcmp(pstrParameterName, "nLevel") == 0)
		m_EncodeParams.nLevel = atol(pstrParameterValue);


	return S_OK;
}