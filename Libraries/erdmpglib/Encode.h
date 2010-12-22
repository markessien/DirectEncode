#pragma once



#include <stdio.h>
#include "erdmpglib.h"
#include "bipbuffer.h"
#include "Multiplex.h"
#include "MemoryProtocol.h"
#include "logooverlay.h"
#include "timestamps.h"
#include "EncodeParameters.h"
#include "SyncWait.h"
#include "AudioResample.h"

/*
#ifndef NEW_VERSION // put to 0 when you upgrade
#define AVFifoBuffer FifoBuffer
#define av_fifo_init fifo_init
#define av_fifo_write fifo_write
#define av_fifo_free fifo_free
#define av_fifo_read fifo_read
#endif
*/

class CAudioResample;

typedef signed __int64 (__cdecl *BufferCallback)(unsigned char* pUserData, unsigned char* ptr, int buflen, int flags, signed __int64 seekPos, int nID);

#define STREAM_PIX_FMT PIX_FMT_YUV420P // default pix_fmt

class CEncode : IMemoryProtocol
{

public:
	CEncode(void);
	~CEncode(void);

	HRESULT   StartConversion();
	HRESULT   StopConversion(void);
	HRESULT   EncodeVideoSample(unsigned __int8* pBuf, long nLen, LONGLONG llStartTime, LONGLONG llEndTime);
	HRESULT   EncodeAudioSample(unsigned __int8* pBuf, long nLen, LONGLONG llStartTime, LONGLONG llEndTime);
	HRESULT   SetEncodeParams(EncodeParameters* params);
	HRESULT   CreateMediaFile(bool bSystems, bool bVideo, bool bAudio);
	HRESULT   EncodeRemainingFrames(void);
	HRESULT   SetBufferCallback(unsigned char* pUserData, BufferCallback pCallback);
	HRESULT   FileMultiplex(char* pstrFile1, char* pstrFile2, char* pstrOutputFile, int nFormat, int nExtra);
	HRESULT   SetEncodeParameter(char* pstrParameterName, char* pstrParameterValue);
	void      SetRegistered(bool b);

	int MemWrite(int nID, unsigned char *buf, int size);
	int MemClose(int nID);
	int MemOpen(int nID);
	signed __int64 MemSeek(int nID, signed __int64 seekPos);

private:
	HRESULT   OpenVideo (AVFormatContext *oc, AVStream *st);
	HRESULT   OpenAudio (AVFormatContext *oc, AVStream *st);
	void      CloseVideo();
	void      CloseAudio();
	
	void      Error(char* pstr);
	
	AVFrame*  AdjustFrameToOutput(unsigned __int8* pBuf, long nLen, LONGLONG llStartTime, LONGLONG llEndTime);
	AVFrame*  AllocPicture  (int pix_fmt, int width, int height);
	AVStream* AddVideoStream(AVFormatContext *oc, int codec_id);
	AVStream* AddAudioStream(AVFormatContext *oc, int codec_id);
	HRESULT   GetAVFiles(char *pstrOutputFile);
	void      RemoveExtension(char *pstr);
	int       StreamOpen(ByteIOContext *s);
	HRESULT   WriteVideoSample(AVFrame* pFrameToEncode);
	HRESULT   EncodeAudioWithDriftCorrection(unsigned __int8* pBuf, long nLen, LONGLONG llStartTime, LONGLONG llEndTime);
	HRESULT   EncodeAudioBuffer(unsigned __int8* pBuf, long nLen, LONGLONG llStartTime, LONGLONG llEndTime);
	

private:
	CAudioResample* m_pResample;
	CTimestamps m_Timestamps;
	CLogoOverlay m_logoOverlay;
	AVStream* m_pAudioStream;
	AVStream* m_pVideoStream;
	
	bool m_bFramerateCorrection;
	bool m_bAudioCorrection;

	unsigned char* m_pUserData;
	BufferCallback m_pCallbackFunc;

	unsigned __int8* m_pAudioInBuf;
	uint8_t* m_pAudioOutBuf;
	long m_nAudioOutBufSize;
	long m_nAudioInputFrameSize;
	long m_nAudioValidData;
	bool m_bResizeRequired;
	bool m_bResampleRequired;
	bool m_bPostMultiplex;
	bool m_bHeaderWritten;
	bool m_bStillImageEncoding;
	long m_nVideoOutBufSize;
	long m_nAudioSamplesWritten;
	uint8_t* m_pVideoOutBuf;

	AVFrame* m_pPictureRGB;
	AVFrame* m_pPictureYUV_before_resize;
	AVFrame* m_pPictureYUV_after_resize;
	AVFrame* m_pPictureYUV_after_deinterlace;

	AVOutputFormat* m_pOutputFormatVideo;
	AVOutputFormat* m_pOutputFormatAudio;
	AVOutputFormat* m_pOutputFormat;
	AVFormatContext* m_pFormatContextAudio;
	AVFormatContext* m_pFormatContextVideo;
	AVFormatContext* m_pFormatContext;

	ReSampleContext *m_pAudioResampleCtx;
	ImgReSampleContext* m_pImgResampleCtx;
	
	CMemoryProtocol m_memProtocol;

	CMultiplex m_Multiplex;

	AVFifoBuffer m_fifo;

	char m_szVideoFileName[1024];
	char m_szAudioFileName[1024];
	bool m_bRegistered;

	CEncodeParameters m_EncodeParams;

	CSyncWait m_lockStop;
};
