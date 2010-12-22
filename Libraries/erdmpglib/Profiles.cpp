#include "stdafx.h"

#define DECLARE_OUTPUT_FORMAT
#include "erdmpglib.h"


void LoadProfilePreset(char* pstrPresetName, EncodeParameters* pTargetEncodeParameters)
{
	memset(pTargetEncodeParameters, 0, sizeof(EncodeParameters));

	pTargetEncodeParameters->bMultiplex = true;
	pTargetEncodeParameters->bDirectMultiplexing = true;
	pTargetEncodeParameters->bUseVideoBitrates = true;
	pTargetEncodeParameters->bUseAudioBitrates = true;
	pTargetEncodeParameters->bWriteSystemsFile = true;
	pTargetEncodeParameters->bWriteAudioStream = true;
	pTargetEncodeParameters->bWriteVideoStream = true;
	pTargetEncodeParameters->nOutputAudioChannels = 2;
	pTargetEncodeParameters->fPixelAspectRatio = (float)1.3333f;
	pTargetEncodeParameters->fMuxMaxDelay = 0.7f;
	pTargetEncodeParameters->fMuxPreload = 0.5f;
	pTargetEncodeParameters->bAutoSelectBitrate = true;
	pTargetEncodeParameters->bDeInterlace = false;
	pTargetEncodeParameters->bForceInterlaceDCT = false;
	pTargetEncodeParameters->bForceInterlaceME = false;
	pTargetEncodeParameters->nQualityMin = 2;
	pTargetEncodeParameters->nQualityMax = 31;
	pTargetEncodeParameters->nProfile = -1;
	pTargetEncodeParameters->nLevel = -1;
	pTargetEncodeParameters->systemsConstraint = CONSTRAINT_NONE;

	if (strcmp(pstrPresetName, "mpeg1-standard") == 0)
	{
		pTargetEncodeParameters->systemsOutputFormat = SYSTEMSFORMAT_MPEG1;
		pTargetEncodeParameters->audioOutputFormat = AUDIOFORMAT_MP2;
		pTargetEncodeParameters->videoOutputFormat = VIDEOFORMAT_MPEG1;
		pTargetEncodeParameters->vbrVideo = BITRATEMODE_MVBR;
		pTargetEncodeParameters->aspectRatio = ASPECTRATIO_4TO3;
		pTargetEncodeParameters->multiplexFormat = SYSTEMSFORMAT_MPEG1;
		pTargetEncodeParameters->nOutputAudioChannels = 2;
		pTargetEncodeParameters->nOutputAudioBitrate = 128 * 1000;
		pTargetEncodeParameters->nOutputX = 320;
		pTargetEncodeParameters->nOutputY = 240;
		pTargetEncodeParameters->nOutputFPSDen = 0;
		pTargetEncodeParameters->nOutputFPSNum = 0;
		pTargetEncodeParameters->nOutputVideoBitrate = 1140 * 1000;
		pTargetEncodeParameters->nOutputVideoBitrateMin = 0;
		pTargetEncodeParameters->nOutputVideoBitrateMax = 1150 * 1000;
		pTargetEncodeParameters->nOutputAudioSampleRate = 32000;
	}
	else if (strcmp(pstrPresetName, "mpeg1-vcd-ntsc") == 0)
	{
		pTargetEncodeParameters->videoOutputFormat = VIDEOFORMAT_MPEG1;
		pTargetEncodeParameters->audioOutputFormat =  AUDIOFORMAT_MP2;
		pTargetEncodeParameters->systemsOutputFormat = SYSTEMSFORMAT_VCD;
		pTargetEncodeParameters->multiplexFormat = SYSTEMSFORMAT_VCD;
		pTargetEncodeParameters->vbrVideo = BITRATEMODE_CBR;
		pTargetEncodeParameters->aspectRatio = ASPECTRATIO_4TO3;
		pTargetEncodeParameters->nOutputVideoBufferSize = 40*1024*8;
		pTargetEncodeParameters->nOutputAudioBitrate = 224 * 1000;
		pTargetEncodeParameters->nOutputX = 352;
		pTargetEncodeParameters->nOutputAudioChannels = 2;
		pTargetEncodeParameters->nOutputVideoBitrate = 1150 * 1000;
		pTargetEncodeParameters->nOutputVideoBitrateMin = 1150 * 1000;
		pTargetEncodeParameters->nOutputVideoBitrateMax = 1150 * 1000;
		pTargetEncodeParameters->nOutputAudioSampleRate = 32000;
		pTargetEncodeParameters->nOutputY = 240;
		pTargetEncodeParameters->dOutputFPS = 29.97;
		pTargetEncodeParameters->nOutputVideoGOPSize =  18;
		pTargetEncodeParameters->systemsConstraint = CONSTRAINT_NTSC;
	}
	else if (strcmp(pstrPresetName, "mpeg1-vcd-pal") == 0)
	{
		pTargetEncodeParameters->videoOutputFormat = VIDEOFORMAT_MPEG1;
		pTargetEncodeParameters->audioOutputFormat =  AUDIOFORMAT_MP2;
		pTargetEncodeParameters->systemsOutputFormat = SYSTEMSFORMAT_VCD;
		pTargetEncodeParameters->multiplexFormat = SYSTEMSFORMAT_VCD;
		pTargetEncodeParameters->vbrVideo = BITRATEMODE_CBR;
		pTargetEncodeParameters->aspectRatio = ASPECTRATIO_4TO3;
		pTargetEncodeParameters->nOutputVideoBufferSize = 40*1024*8;
		pTargetEncodeParameters->nOutputAudioBitrate = 224 * 1000;
		pTargetEncodeParameters->nOutputX = 352;
		pTargetEncodeParameters->nOutputAudioChannels = 2;
		pTargetEncodeParameters->nOutputVideoBitrate = 1150 * 1000;
		pTargetEncodeParameters->nOutputVideoBitrateMin = 1150 * 1000;
		pTargetEncodeParameters->nOutputVideoBitrateMax = 1150 * 1000;
		pTargetEncodeParameters->nOutputAudioSampleRate = 32000;
		pTargetEncodeParameters->nOutputY = 288;
		pTargetEncodeParameters->dOutputFPS = 25;
		pTargetEncodeParameters->nOutputVideoGOPSize =  15;
		pTargetEncodeParameters->systemsConstraint = CONSTRAINT_PAL;
	}
	else if (strcmp(pstrPresetName, "mpeg2-standard") == 0)
	{
		pTargetEncodeParameters->videoOutputFormat = VIDEOFORMAT_MPEG2;
		pTargetEncodeParameters->audioOutputFormat =  AUDIOFORMAT_MP2;
		pTargetEncodeParameters->systemsOutputFormat = SYSTEMSFORMAT_MPEG2;
		pTargetEncodeParameters->vbrVideo = BITRATEMODE_MVBR;
		pTargetEncodeParameters->aspectRatio = ASPECTRATIO_4TO3;
		pTargetEncodeParameters->multiplexFormat = SYSTEMSFORMAT_MPEG2;
		pTargetEncodeParameters->nOutputAudioBitrate = 192 * 1000;
		pTargetEncodeParameters->dOutputFPS = 0;
		pTargetEncodeParameters->nOutputX = 0;
		pTargetEncodeParameters->nOutputAudioChannels = 2;
		pTargetEncodeParameters->nOutputY = 0;
		pTargetEncodeParameters->nOutputVideoBitrate = 6000 * 1000;
		pTargetEncodeParameters->nOutputVideoBitrateMin = 0;
		pTargetEncodeParameters->nOutputVideoBitrateMax = 9000 * 1000;
		pTargetEncodeParameters->nOutputAudioSampleRate = 32000;
	}
	else if (strcmp(pstrPresetName, "mpeg2-hd") == 0)
	{
		pTargetEncodeParameters->videoOutputFormat = VIDEOFORMAT_MPEG2;
		pTargetEncodeParameters->audioOutputFormat =  AUDIOFORMAT_MP2;
		pTargetEncodeParameters->systemsOutputFormat = SYSTEMSFORMAT_MPEG2;
		pTargetEncodeParameters->vbrVideo = BITRATEMODE_MVBR;
		pTargetEncodeParameters->aspectRatio = ASPECTRATIO_4TO3;
		pTargetEncodeParameters->multiplexFormat = SYSTEMSFORMAT_MPEG2;
		pTargetEncodeParameters->nOutputAudioBitrate = 192 * 1000;
		pTargetEncodeParameters->dOutputFPS = 0;
		pTargetEncodeParameters->nOutputX = 0;
		pTargetEncodeParameters->nOutputAudioChannels = 2;
		pTargetEncodeParameters->nOutputY = 0;
		pTargetEncodeParameters->nOutputVideoBitrate = 6000 * 1000;
		pTargetEncodeParameters->nOutputVideoBitrateMin = 0;
		pTargetEncodeParameters->nOutputVideoBitrateMax = 9000 * 1000;
		pTargetEncodeParameters->nOutputAudioSampleRate = 32000;
		pTargetEncodeParameters->systemsConstraint = CONSTRAINT_HD;
		pTargetEncodeParameters->nOutputX = 960;
		pTargetEncodeParameters->nOutputY = 576;
		pTargetEncodeParameters->nOutputVideoBitrate = 20000 * 1000;
		pTargetEncodeParameters->nOutputVideoBitrateMin = 0;
		pTargetEncodeParameters->nOutputVideoBitrateMax = 20000 * 1000;
		pTargetEncodeParameters->nProfile = 1;
		pTargetEncodeParameters->nLevel = 4;
	}
	else if (strcmp(pstrPresetName, "mpeg2-svcd-ntsc") == 0)
	{
		pTargetEncodeParameters->videoOutputFormat = VIDEOFORMAT_MPEG2;
		pTargetEncodeParameters->audioOutputFormat =  AUDIOFORMAT_MP2;
		pTargetEncodeParameters->systemsOutputFormat = SYSTEMSFORMAT_SVCD;
		pTargetEncodeParameters->vbrVideo = BITRATEMODE_MVBR;
		pTargetEncodeParameters->aspectRatio = ASPECTRATIO_4TO3;
		pTargetEncodeParameters->multiplexFormat = SYSTEMSFORMAT_SVCD;
		pTargetEncodeParameters->nOutputAudioBitrate = 224 * 1000;
		pTargetEncodeParameters->nOutputX = 480;
		pTargetEncodeParameters->nOutputVideoBitrate = 2040000;
		pTargetEncodeParameters->nOutputVideoBitrateMin = 0;
		pTargetEncodeParameters->nOutputVideoBitrateMax = 2516000;
		pTargetEncodeParameters->nOutputAudioSampleRate = 32000;
		pTargetEncodeParameters->nOutputAudioChannels = 2;
		pTargetEncodeParameters->nOutputY = 480;
		pTargetEncodeParameters->dOutputFPS = 29.97;
		pTargetEncodeParameters->nOutputVideoGOPSize =  18;
		pTargetEncodeParameters->systemsConstraint = CONSTRAINT_NTSC;
	}
	else if (strcmp(pstrPresetName, "mpeg2-svcd-pal") == 0)
	{
		pTargetEncodeParameters->videoOutputFormat = VIDEOFORMAT_MPEG2;
		pTargetEncodeParameters->audioOutputFormat =  AUDIOFORMAT_MP2;
		pTargetEncodeParameters->systemsOutputFormat = SYSTEMSFORMAT_SVCD;
		pTargetEncodeParameters->vbrVideo = BITRATEMODE_MVBR;
		pTargetEncodeParameters->aspectRatio = ASPECTRATIO_4TO3;
		pTargetEncodeParameters->multiplexFormat = SYSTEMSFORMAT_SVCD;
		pTargetEncodeParameters->nOutputAudioBitrate = 224 * 1000;
		pTargetEncodeParameters->nOutputX = 480;
		pTargetEncodeParameters->nOutputVideoBitrate = 2040000;
		pTargetEncodeParameters->nOutputVideoBitrateMin = 0;
		pTargetEncodeParameters->nOutputVideoBitrateMax = 2516000;
		pTargetEncodeParameters->nOutputAudioSampleRate = 32000;
		pTargetEncodeParameters->nOutputAudioChannels = 2;
		pTargetEncodeParameters->nOutputY = 576;
		pTargetEncodeParameters->dOutputFPS = 25;
		pTargetEncodeParameters->nOutputVideoGOPSize =  15;
		pTargetEncodeParameters->systemsConstraint = CONSTRAINT_PAL;
	}
	else if (strcmp(pstrPresetName, "dvb") == 0)
	{
		pTargetEncodeParameters->videoOutputFormat = VIDEOFORMAT_MPEG2;
		pTargetEncodeParameters->audioOutputFormat =  AUDIOFORMAT_MP2;
		pTargetEncodeParameters->systemsOutputFormat = SYSTEMSFORMAT_DVB;
		pTargetEncodeParameters->vbrVideo = BITRATEMODE_MVBR;
		pTargetEncodeParameters->aspectRatio = ASPECTRATIO_4TO3;
		pTargetEncodeParameters->multiplexFormat = SYSTEMSFORMAT_DVB;
		pTargetEncodeParameters->nOutputAudioBitrate = 192 * 1000;
		pTargetEncodeParameters->dOutputFPS = 0;
		pTargetEncodeParameters->nOutputX = 0;
		pTargetEncodeParameters->nOutputAudioChannels = 2;
		pTargetEncodeParameters->nOutputY = 0;
		pTargetEncodeParameters->nOutputVideoBitrate = 6000 * 1000;
		pTargetEncodeParameters->nOutputVideoBitrateMin = 0;
		pTargetEncodeParameters->nOutputVideoBitrateMax = 9000 * 1000;
		pTargetEncodeParameters->nOutputAudioSampleRate = 32000;
	}
	else if (strcmp(pstrPresetName, "mpeg2-dvd-ntsc") == 0)
	{
		pTargetEncodeParameters->videoOutputFormat = VIDEOFORMAT_MPEG2;
		pTargetEncodeParameters->audioOutputFormat =  AUDIOFORMAT_AC3;
		pTargetEncodeParameters->systemsOutputFormat = SYSTEMSFORMAT_DVD;
		pTargetEncodeParameters->vbrVideo = BITRATEMODE_MVBR;
		pTargetEncodeParameters->aspectRatio = ASPECTRATIO_4TO3;
		pTargetEncodeParameters->multiplexFormat = SYSTEMSFORMAT_DVD;
		pTargetEncodeParameters->nOutputAudioBitrate = 448 * 1000;
		pTargetEncodeParameters->nOutputX = 720;
		pTargetEncodeParameters->nOutputVideoBitrate = 6000000;
		pTargetEncodeParameters->nOutputVideoBitrateMin = 0;
		pTargetEncodeParameters->nOutputAudioChannels = 2;
		pTargetEncodeParameters->nOutputVideoBitrateMax = 9000000;
		pTargetEncodeParameters->nOutputAudioSampleRate = 48000;
		pTargetEncodeParameters->nOutputY = 480;
		pTargetEncodeParameters->dOutputFPS = 29.97;
		pTargetEncodeParameters->nOutputVideoGOPSize =  18;
		pTargetEncodeParameters->systemsConstraint = CONSTRAINT_NTSC;
		pTargetEncodeParameters->nProfile = 4; // 4 = main
		pTargetEncodeParameters->nLevel = 8; // 6 = High-1440, 8 = main
	}
	else if (strcmp(pstrPresetName, "mpeg2-dvd-pal") == 0)
	{
		pTargetEncodeParameters->videoOutputFormat = VIDEOFORMAT_MPEG2;
		pTargetEncodeParameters->audioOutputFormat =  AUDIOFORMAT_AC3;
		pTargetEncodeParameters->systemsOutputFormat = SYSTEMSFORMAT_DVD;
		pTargetEncodeParameters->vbrVideo = BITRATEMODE_MVBR;
		pTargetEncodeParameters->aspectRatio = ASPECTRATIO_4TO3;
		pTargetEncodeParameters->multiplexFormat = SYSTEMSFORMAT_DVD;
		pTargetEncodeParameters->nOutputAudioBitrate = 448 * 1000;
		pTargetEncodeParameters->nOutputX = 720;
		pTargetEncodeParameters->nOutputVideoBitrate = 6000000;
		pTargetEncodeParameters->nOutputVideoBitrateMin = 0;
		pTargetEncodeParameters->nOutputAudioChannels = 2;
		pTargetEncodeParameters->nOutputVideoBitrateMax = 9000000;
		pTargetEncodeParameters->nOutputAudioSampleRate = 48000;
		pTargetEncodeParameters->nOutputY = 576;
		pTargetEncodeParameters->dOutputFPS = 25;
		pTargetEncodeParameters->nOutputVideoGOPSize =  15;
		pTargetEncodeParameters->systemsConstraint = CONSTRAINT_PAL;
		pTargetEncodeParameters->nProfile = 4; // 4 = main
		pTargetEncodeParameters->nLevel = 8; // 6 = High-1440, 8 = main
	}
	else if (strcmp(pstrPresetName, "mpeg4-standard") == 0)
	{
		pTargetEncodeParameters->systemsOutputFormat = SYSTEMSFORMAT_MP4;
		pTargetEncodeParameters->audioOutputFormat =  AUDIOFORMAT_AAC;
		pTargetEncodeParameters->videoOutputFormat = VIDEOFORMAT_MPEG4;
		pTargetEncodeParameters->dOutputFPS = 0;
		pTargetEncodeParameters->nOutputX = 0;
		pTargetEncodeParameters->nOutputY = 0;
		pTargetEncodeParameters->multiplexFormat = SYSTEMSFORMAT_MP4;
		pTargetEncodeParameters->nOutputAudioChannels = 2;
		pTargetEncodeParameters->nOutputAudioBitrate = 64 * 1000;
		pTargetEncodeParameters->nOutputVideoBitrate = 350 * 1000;
		pTargetEncodeParameters->nOutputVideoBitrateMin = 0;
		pTargetEncodeParameters->nOutputVideoBitrateMax = 750 * 1000;
		pTargetEncodeParameters->nOutputAudioSampleRate = 32000;
		pTargetEncodeParameters->vbrVideo = BITRATEMODE_MVBR;
	}
	else if (strcmp(pstrPresetName, "mpeg4-ipod") == 0)
	{
		pTargetEncodeParameters->systemsOutputFormat = SYSTEMSFORMAT_MP4;
		pTargetEncodeParameters->audioOutputFormat =  AUDIOFORMAT_AAC;
		pTargetEncodeParameters->videoOutputFormat = VIDEOFORMAT_MPEG4;
		pTargetEncodeParameters->dOutputFPS = 0;
		pTargetEncodeParameters->nOutputX = 0;
		pTargetEncodeParameters->nOutputY = 0;
		pTargetEncodeParameters->multiplexFormat = SYSTEMSFORMAT_MP4;
		pTargetEncodeParameters->nOutputAudioChannels = 2;
		pTargetEncodeParameters->nOutputAudioBitrate = 64 * 1000;
		pTargetEncodeParameters->nOutputVideoBitrate = 350 * 1000;
		pTargetEncodeParameters->nOutputVideoBitrateMin = 0;
		pTargetEncodeParameters->nOutputVideoBitrateMax = 750 * 1000;
		pTargetEncodeParameters->nOutputAudioSampleRate = 32000;
		pTargetEncodeParameters->vbrVideo = BITRATEMODE_MVBR;
		pTargetEncodeParameters->systemsConstraint = CONSTRAINT_IPOD;
		pTargetEncodeParameters->nOutputX = 320;
		pTargetEncodeParameters->nOutputY = 240;
		pTargetEncodeParameters->nOutputVideoGOPSize =  300;
		pTargetEncodeParameters->nOutputVideoBitrateMin = 750 * 1000;
		pTargetEncodeParameters->nOutputVideoBitrateMax = 750 * 1000;
		pTargetEncodeParameters->nOutputVideoBitrate = 750 * 1000;
		pTargetEncodeParameters->nQualityMin = 3; // qmin
		pTargetEncodeParameters->nQualityMax = 5; // qmax min video quantiser scale (VBR)
		pTargetEncodeParameters->nOutputVideoBufferSize = 4096 * 1000; //bufsize
		pTargetEncodeParameters->nOutputAudioBitrate = 92000;
	}
	else if (strcmp(pstrPresetName, "mpeg4-ipod-nano") == 0)
	{
		pTargetEncodeParameters->systemsOutputFormat = SYSTEMSFORMAT_MP4;
		pTargetEncodeParameters->audioOutputFormat =  AUDIOFORMAT_AAC;
		pTargetEncodeParameters->videoOutputFormat = VIDEOFORMAT_MPEG4;
		pTargetEncodeParameters->dOutputFPS = 0;
		pTargetEncodeParameters->nOutputX = 0;
		pTargetEncodeParameters->nOutputY = 0;
		pTargetEncodeParameters->multiplexFormat = SYSTEMSFORMAT_MP4;
		pTargetEncodeParameters->nOutputAudioChannels = 2;
		pTargetEncodeParameters->nOutputAudioBitrate = 64 * 1000;
		pTargetEncodeParameters->nOutputVideoBitrate = 350 * 1000;
		pTargetEncodeParameters->nOutputVideoBitrateMin = 0;
		pTargetEncodeParameters->nOutputVideoBitrateMax = 750 * 1000;
		pTargetEncodeParameters->nOutputAudioSampleRate = 32000;
		pTargetEncodeParameters->vbrVideo = BITRATEMODE_MVBR;
		pTargetEncodeParameters->systemsConstraint = CONSTRAINT_IPOD_NANO;
		pTargetEncodeParameters->nOutputX = 176;
		pTargetEncodeParameters->nOutputY = 128;
		pTargetEncodeParameters->nOutputVideoGOPSize =  300;
		pTargetEncodeParameters->nOutputVideoBitrateMin = 256 * 1000;
		pTargetEncodeParameters->nOutputVideoBitrateMax = 256 * 1000;
		pTargetEncodeParameters->nOutputVideoBitrate = 256 * 1000;
		pTargetEncodeParameters->nQualityMin = 3; // qmin
		pTargetEncodeParameters->nQualityMax = 5; // qmax min video quantiser scale (VBR)
		pTargetEncodeParameters->nOutputVideoBufferSize = 4096 * 1000; //bufsize
		pTargetEncodeParameters->nOutputAudioBitrate = 92000;
	}
	else if (strcmp(pstrPresetName, "mpeg4-iphone") == 0)
	{
		pTargetEncodeParameters->systemsOutputFormat = SYSTEMSFORMAT_MP4;
		pTargetEncodeParameters->audioOutputFormat =  AUDIOFORMAT_AAC;
		pTargetEncodeParameters->videoOutputFormat = VIDEOFORMAT_MPEG4;
		pTargetEncodeParameters->dOutputFPS = 0;
		pTargetEncodeParameters->nOutputX = 0;
		pTargetEncodeParameters->nOutputY = 0;
		pTargetEncodeParameters->multiplexFormat = SYSTEMSFORMAT_MP4;
		pTargetEncodeParameters->nOutputAudioChannels = 2;
		pTargetEncodeParameters->nOutputAudioBitrate = 64 * 1000;
		pTargetEncodeParameters->nOutputVideoBitrate = 350 * 1000;
		pTargetEncodeParameters->nOutputVideoBitrateMin = 0;
		pTargetEncodeParameters->nOutputVideoBitrateMax = 750 * 1000;
		pTargetEncodeParameters->nOutputAudioSampleRate = 32000;
		pTargetEncodeParameters->vbrVideo = BITRATEMODE_MVBR;
		pTargetEncodeParameters->systemsConstraint = CONSTRAINT_IPHONE;
		pTargetEncodeParameters->nOutputX = 320;
		pTargetEncodeParameters->nOutputY = 240;
		pTargetEncodeParameters->nOutputVideoGOPSize =  300;
		pTargetEncodeParameters->nOutputVideoBitrateMin = 750 * 1000;
		pTargetEncodeParameters->nOutputVideoBitrateMax = 750 * 1000;
		pTargetEncodeParameters->nOutputVideoBitrate = 750 * 1000;
		pTargetEncodeParameters->nQualityMin = 3; // qmin
		pTargetEncodeParameters->nQualityMax = 5; // qmax min video quantiser scale (VBR)
		pTargetEncodeParameters->nOutputVideoBufferSize = 4096 * 1000; //bufsize
		pTargetEncodeParameters->nOutputAudioBitrate = 92000;
	}
	else if (strcmp(pstrPresetName, "mpeg4-qt") == 0)
	{
		pTargetEncodeParameters->systemsOutputFormat = SYSTEMSFORMAT_MP4;
		pTargetEncodeParameters->audioOutputFormat =  AUDIOFORMAT_AAC;
		pTargetEncodeParameters->videoOutputFormat = VIDEOFORMAT_MPEG4;
		pTargetEncodeParameters->dOutputFPS = 0;
		pTargetEncodeParameters->nOutputX = 0;
		pTargetEncodeParameters->nOutputY = 0;
		pTargetEncodeParameters->multiplexFormat = SYSTEMSFORMAT_MP4;
		pTargetEncodeParameters->nOutputAudioChannels = 2;
		pTargetEncodeParameters->nOutputAudioBitrate = 64 * 1000;
		pTargetEncodeParameters->nOutputVideoBitrate = 350 * 1000;
		pTargetEncodeParameters->nOutputVideoBitrateMin = 0;
		pTargetEncodeParameters->nOutputVideoBitrateMax = 750 * 1000;
		pTargetEncodeParameters->nOutputAudioSampleRate = 32000;
		pTargetEncodeParameters->vbrVideo = BITRATEMODE_MVBR;
		pTargetEncodeParameters->systemsOutputFormat = SYSTEMSFORMAT_MOV;
		pTargetEncodeParameters->audioOutputFormat =  AUDIOFORMAT_AAC;
		pTargetEncodeParameters->videoOutputFormat = VIDEOFORMAT_MPEG4;
		pTargetEncodeParameters->dOutputFPS = 0;
		pTargetEncodeParameters->nOutputX = 0;
		pTargetEncodeParameters->nOutputY = 0;
		pTargetEncodeParameters->multiplexFormat = SYSTEMSFORMAT_MOV;
		pTargetEncodeParameters->nOutputAudioChannels = 2;
		pTargetEncodeParameters->nOutputAudioBitrate = 64 * 1000;
		pTargetEncodeParameters->nOutputVideoBitrate = 350 * 1000;
		pTargetEncodeParameters->nOutputVideoBitrateMin = 0;
		pTargetEncodeParameters->nOutputVideoBitrateMax = 750 * 1000;
		pTargetEncodeParameters->nOutputAudioSampleRate = 32000;
		pTargetEncodeParameters->vbrVideo = BITRATEMODE_MVBR;
	}
	else if (strcmp(pstrPresetName, "mpeg1-vcd-still-ntsc") == 0)
	{
		pTargetEncodeParameters->videoOutputFormat = VIDEOFORMAT_MPEG1;
		pTargetEncodeParameters->audioOutputFormat =  AUDIOFORMAT_NONE;
		pTargetEncodeParameters->systemsOutputFormat = SYSTEMSFORMAT_VCD_STILL;
		pTargetEncodeParameters->multiplexFormat = SYSTEMSFORMAT_VCD;
		pTargetEncodeParameters->vbrVideo = BITRATEMODE_CBR;
		pTargetEncodeParameters->aspectRatio = ASPECTRATIO_4TO3;
		pTargetEncodeParameters->nOutputVideoBufferSize = 40*1024*8;
		pTargetEncodeParameters->nOutputX = 352;
		pTargetEncodeParameters->nOutputVideoBitrate = 62 * 1000;
		pTargetEncodeParameters->nOutputVideoBitrateMin = 62 * 1000;
		pTargetEncodeParameters->nOutputVideoBitrateMax = 62 * 1000;
		pTargetEncodeParameters->nOutputY = 240;
		pTargetEncodeParameters->dOutputFPS = 29.97;
		pTargetEncodeParameters->nOutputVideoGOPSize =  18;
		pTargetEncodeParameters->systemsConstraint = CONSTRAINT_NTSC;
	}
	else if (strcmp(pstrPresetName, "mpeg1-vcd-still-pal") == 0)
	{
		pTargetEncodeParameters->videoOutputFormat = VIDEOFORMAT_MPEG1;
		pTargetEncodeParameters->audioOutputFormat =  AUDIOFORMAT_NONE;
		pTargetEncodeParameters->systemsOutputFormat = SYSTEMSFORMAT_VCD_STILL;
		pTargetEncodeParameters->multiplexFormat = SYSTEMSFORMAT_VCD;
		pTargetEncodeParameters->vbrVideo = BITRATEMODE_CBR;
		pTargetEncodeParameters->aspectRatio = ASPECTRATIO_4TO3;
		pTargetEncodeParameters->nOutputVideoBufferSize = 40*1024*8;
		pTargetEncodeParameters->nOutputX = 352;
		pTargetEncodeParameters->nOutputVideoBitrate = 62 * 1000;
		pTargetEncodeParameters->nOutputVideoBitrateMin = 62 * 1000;
		pTargetEncodeParameters->nOutputVideoBitrateMax = 62 * 1000;
		pTargetEncodeParameters->nOutputY = 288;
		pTargetEncodeParameters->dOutputFPS = 25;
		pTargetEncodeParameters->nOutputVideoGOPSize =  15;
		pTargetEncodeParameters->systemsConstraint = CONSTRAINT_PAL;
	}
	else if (strcmp(pstrPresetName, "mpeg2-svcd-still-ntsc") == 0)
	{
		pTargetEncodeParameters->videoOutputFormat = VIDEOFORMAT_MPEG2;
		pTargetEncodeParameters->audioOutputFormat =  AUDIOFORMAT_NONE;
		pTargetEncodeParameters->systemsOutputFormat = SYSTEMSFORMAT_SVCD_STILL;
		pTargetEncodeParameters->vbrVideo = BITRATEMODE_MVBR;
		pTargetEncodeParameters->aspectRatio = ASPECTRATIO_4TO3;
		pTargetEncodeParameters->multiplexFormat = SYSTEMSFORMAT_SVCD_STILL;
		pTargetEncodeParameters->nOutputX = 480;
		pTargetEncodeParameters->nOutputVideoBitrate = 6200;
		pTargetEncodeParameters->nOutputVideoBitrateMin = 6200;
		pTargetEncodeParameters->nOutputVideoBitrateMax = 6200;
		pTargetEncodeParameters->nOutputY = 480;
		pTargetEncodeParameters->dOutputFPS = 29.97;
		pTargetEncodeParameters->nOutputVideoGOPSize =  18;
		pTargetEncodeParameters->systemsConstraint = CONSTRAINT_NTSC;
	}
	else if (strcmp(pstrPresetName, "mpeg2-svcd-still-pal") == 0)
	{
		pTargetEncodeParameters->videoOutputFormat = VIDEOFORMAT_MPEG2;
		pTargetEncodeParameters->audioOutputFormat =  AUDIOFORMAT_NONE;
		pTargetEncodeParameters->systemsOutputFormat = SYSTEMSFORMAT_SVCD_STILL;
		pTargetEncodeParameters->vbrVideo = BITRATEMODE_MVBR;
		pTargetEncodeParameters->aspectRatio = ASPECTRATIO_4TO3;
		pTargetEncodeParameters->multiplexFormat = SYSTEMSFORMAT_SVCD_STILL;
		pTargetEncodeParameters->nOutputX = 480;
		pTargetEncodeParameters->nOutputVideoBitrate = 6200;
		pTargetEncodeParameters->nOutputVideoBitrateMin = 6200;
		pTargetEncodeParameters->nOutputVideoBitrateMax = 6200;
		pTargetEncodeParameters->nOutputY = 576;
		pTargetEncodeParameters->dOutputFPS = 25;
		pTargetEncodeParameters->nOutputVideoGOPSize =  15;
		pTargetEncodeParameters->systemsConstraint = CONSTRAINT_PAL;
	}
	else if (strcmp(pstrPresetName, "flv") == 0)
	{
		pTargetEncodeParameters->systemsOutputFormat = SYSTEMSFORMAT_FLV;
		pTargetEncodeParameters->audioOutputFormat =  AUDIOFORMAT_MP3;
		pTargetEncodeParameters->videoOutputFormat = VIDEOFORMAT_FLV;
		pTargetEncodeParameters->dOutputFPS = 0;
		pTargetEncodeParameters->nOutputX = 0;
		pTargetEncodeParameters->nOutputY = 0;
		pTargetEncodeParameters->multiplexFormat = SYSTEMSFORMAT_FLV;
		pTargetEncodeParameters->nOutputAudioChannels = 2;
		pTargetEncodeParameters->nOutputAudioBitrate = 64 * 1000;
		pTargetEncodeParameters->nOutputVideoBitrate = 350 * 1000;
		pTargetEncodeParameters->nOutputVideoBitrateMin = 0;
		pTargetEncodeParameters->nOutputVideoBitrateMax = 750 * 1000;
		pTargetEncodeParameters->nOutputAudioSampleRate = 22050; // allowed = 11025, 22050, 44100
		pTargetEncodeParameters->vbrVideo = BITRATEMODE_MVBR;
	}
	else if (strcmp(pstrPresetName, "rm") == 0)
	{
		pTargetEncodeParameters->systemsOutputFormat = SYSTEMSFORMAT_RM;
		pTargetEncodeParameters->audioOutputFormat =  AUDIOFORMAT_AAC;
		pTargetEncodeParameters->videoOutputFormat = VIDEOFORMAT_MPEG4;
		pTargetEncodeParameters->dOutputFPS = 0;
		pTargetEncodeParameters->nOutputX = 0;
		pTargetEncodeParameters->nOutputY = 0;
		pTargetEncodeParameters->multiplexFormat = SYSTEMSFORMAT_RM;
		pTargetEncodeParameters->nOutputAudioChannels = 2;
		pTargetEncodeParameters->nOutputAudioBitrate = 64 * 1000;
		pTargetEncodeParameters->nOutputVideoBitrate = 350 * 1000;
		pTargetEncodeParameters->nOutputVideoBitrateMin = 0;
		pTargetEncodeParameters->nOutputVideoBitrateMax = 750 * 1000;
		pTargetEncodeParameters->nOutputAudioSampleRate = 32000;
		pTargetEncodeParameters->vbrVideo = BITRATEMODE_MVBR;
	}
	else if (strcmp(pstrPresetName, "psp") == 0)
	{
		pTargetEncodeParameters->systemsOutputFormat = SYSTEMSFORMAT_PSP;
		pTargetEncodeParameters->audioOutputFormat =  AUDIOFORMAT_AAC;
		pTargetEncodeParameters->videoOutputFormat = VIDEOFORMAT_MPEG4;
		pTargetEncodeParameters->dOutputFPS = 29.97;
		pTargetEncodeParameters->nOutputX = 0;
		pTargetEncodeParameters->nOutputY = 0;
		pTargetEncodeParameters->multiplexFormat = SYSTEMSFORMAT_MP4;
		pTargetEncodeParameters->nOutputAudioChannels = 2;
		pTargetEncodeParameters->nOutputAudioBitrate = 64 * 1000;
		pTargetEncodeParameters->nOutputVideoBitrate = 512 * 1000;
		pTargetEncodeParameters->nOutputVideoBitrateMin = 0;
		pTargetEncodeParameters->nOutputVideoBitrateMax = 512 * 1000;
		pTargetEncodeParameters->nOutputAudioSampleRate = 24000;
		pTargetEncodeParameters->vbrVideo = BITRATEMODE_MVBR;
		pTargetEncodeParameters->nOutputX = 320;
		pTargetEncodeParameters->nOutputY = 240;
		pTargetEncodeParameters->nOutputVideoGOPSize =  300;
		pTargetEncodeParameters->nQualityMin = 3; // qmin
		pTargetEncodeParameters->nQualityMax = 5; // qmax min video quantiser scale (VBR)
		pTargetEncodeParameters->nOutputVideoBufferSize = 4096 * 1000; //bufsize
	}
	else if (strcmp(pstrPresetName, "3g2") == 0)
	{
		pTargetEncodeParameters->systemsOutputFormat = SYSTEMSFORMAT_3G2;
		pTargetEncodeParameters->audioOutputFormat =  AUDIOFORMAT_AAC;
		pTargetEncodeParameters->videoOutputFormat = VIDEOFORMAT_MPEG4;
		pTargetEncodeParameters->dOutputFPS = 0;
		pTargetEncodeParameters->nOutputX = 0;
		pTargetEncodeParameters->nOutputY = 0;
		pTargetEncodeParameters->multiplexFormat = SYSTEMSFORMAT_MP4;
		pTargetEncodeParameters->nOutputAudioChannels = 2;
		pTargetEncodeParameters->nOutputAudioBitrate = 64 * 1000;
		pTargetEncodeParameters->nOutputVideoBitrate = 350 * 1000;
		pTargetEncodeParameters->nOutputVideoBitrateMin = 0;
		pTargetEncodeParameters->nOutputVideoBitrateMax = 750 * 1000;
		pTargetEncodeParameters->nOutputAudioSampleRate = 32000;
		pTargetEncodeParameters->vbrVideo = BITRATEMODE_MVBR;
	}
	else if (strcmp(pstrPresetName, "3gp") == 0)
	{
		pTargetEncodeParameters->systemsOutputFormat = SYSTEMSFORMAT_3GP;
		pTargetEncodeParameters->audioOutputFormat =  AUDIOFORMAT_AAC;
		pTargetEncodeParameters->videoOutputFormat = VIDEOFORMAT_MPEG4;
		pTargetEncodeParameters->dOutputFPS = 0;
		pTargetEncodeParameters->nOutputX = 0;
		pTargetEncodeParameters->nOutputY = 0;
		pTargetEncodeParameters->multiplexFormat = SYSTEMSFORMAT_MP4;
		pTargetEncodeParameters->nOutputAudioChannels = 2;
		pTargetEncodeParameters->nOutputAudioBitrate = 64 * 1000;
		pTargetEncodeParameters->nOutputVideoBitrate = 350 * 1000;
		pTargetEncodeParameters->nOutputVideoBitrateMin = 0;
		pTargetEncodeParameters->nOutputVideoBitrateMax = 750 * 1000;
		pTargetEncodeParameters->nOutputAudioSampleRate = 32000;
		pTargetEncodeParameters->vbrVideo = BITRATEMODE_MVBR;
	}
	else if (strcmp(pstrPresetName, "elementary") == 0)
	{
		pTargetEncodeParameters->systemsOutputFormat = SYSTEMSFORMAT_NONE;
		pTargetEncodeParameters->audioOutputFormat =  AUDIOFORMAT_NONE;
		pTargetEncodeParameters->videoOutputFormat = VIDEOFORMAT_NONE;
		pTargetEncodeParameters->dOutputFPS = 0;
		pTargetEncodeParameters->nOutputX = 0;
		pTargetEncodeParameters->nOutputY = 0;
		pTargetEncodeParameters->multiplexFormat = SYSTEMSFORMAT_NONE;
		pTargetEncodeParameters->nOutputAudioChannels = 2;
		pTargetEncodeParameters->nOutputAudioBitrate = 64 * 1000;
		pTargetEncodeParameters->nOutputVideoBitrate = 350 * 1000;
		pTargetEncodeParameters->nOutputVideoBitrateMin = 0;
		pTargetEncodeParameters->nOutputVideoBitrateMax = 750 * 1000;
		pTargetEncodeParameters->nOutputAudioSampleRate = 32000;
		pTargetEncodeParameters->vbrVideo = BITRATEMODE_MVBR;
		pTargetEncodeParameters->nQualityMin = 3; // qmin
		pTargetEncodeParameters->nQualityMax = 5; // qmax min video quantiser scale (VBR)
		pTargetEncodeParameters->nOutputVideoBufferSize = 4096 * 1000; //bufsize
		pTargetEncodeParameters->nOutputAudioBitrate = 92000;
		pTargetEncodeParameters->bMultiplex = FALSE;
		pTargetEncodeParameters->bDirectMultiplexing = FALSE;
		pTargetEncodeParameters->bDeleteTmpAfterMultiplex = FALSE;
	}

}
