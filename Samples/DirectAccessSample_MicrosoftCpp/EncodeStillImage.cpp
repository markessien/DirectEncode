// EncodeErdLib.cpp: implementation of the CEncoder class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EncodeStillImage.h"
#include <fcntl.h>
#include <io.h>
#include "stillbitmap.h"
#include <math.h>
// #include <mmsystem.h>
// #include <windows.h>

#define ONE_SECOND 10000000

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEncoder::CEncoder() : m_hEncodeDLL(NULL)
{
	m_outputFormat = SYSTEMSFORMAT_NONE;
	m_outputConstraint = CONSTRAINT_NONE;
	m_nSourceWidth = 0;
	m_nSourceHeight = 0;
	m_pBuffer = NULL;
	m_bHasAudio = false;
	m_bHasVideo = false;
	
	m_EncodeParameters.bMultiplex = true;
	m_EncodeParameters.bDirectMultiplexing = true;
	m_EncodeParameters.bUseVideoBitrates = true;
	m_EncodeParameters.bUseAudioBitrates = true;
	m_EncodeParameters.bWriteSystemsFile = true;
	m_EncodeParameters.bWriteAudioStream = true;
	m_EncodeParameters.bWriteVideoStream = true;
	m_EncodeParameters.nOutputAudioChannels = 2;
	m_EncodeParameters.fPixelAspectRatio = (float)1.3333f;
	m_EncodeParameters.fMuxMaxDelay = 0.7f;
	m_EncodeParameters.fMuxPreload = 0.5f;
	m_EncodeParameters.bAutoSelectBitrate = true;
	m_EncodeParameters.bDeInterlace = false;
	m_EncodeParameters.bForceInterlaceDCT = false;
	m_EncodeParameters.bForceInterlaceME = false;
	m_EncodeParameters.nQualityMin = 2;
	m_EncodeParameters.nQualityMax = 31;
}



CEncoder::~CEncoder(void)
{
}



HRESULT CEncoder::CreateHighResolutionStill(BSTR strInputFilePath, BSTR strOutputFilePath)
{
	HRESULT hr = S_OK;

	// Get the correct dimensions for a high res MPEG still
	m_nSourceWidth = 704;
	m_nSourceHeight = m_outputConstraint == CONSTRAINT_PAL ? 576 : 480;

	return CreateStill(strInputFilePath, strOutputFilePath);
}


HRESULT CEncoder::CreateLowResolutionStill(BSTR strInputFilePath, BSTR strOutputFilePath)
{
	HRESULT hr = S_OK;

	// Get the correct dimensions for a high res MPEG still
	if (m_outputFormat == SYSTEMSFORMAT_SVCD_STILL)
	{
		if (m_outputConstraint == CONSTRAINT_PAL)
		{
			m_nSourceWidth = 480;
			m_nSourceHeight = 576;
		}
		else
		{
			m_nSourceWidth = 480;
			m_nSourceHeight = 480;
		}
	}
	else
	{
		if (m_outputConstraint == CONSTRAINT_PAL)
		{
			m_nSourceWidth = 352;
			m_nSourceHeight = 288;
		}
		else
		{
			m_nSourceWidth = 352;
			m_nSourceHeight = 240;
		}
	}

	return CreateStill(strInputFilePath, strOutputFilePath);
}

HRESULT CEncoder::CreateStill(BSTR strInputFilePath, BSTR strOutputFilePath)
{
		// Load and resize the input image
	CStillBitmap bmpStill;
	HRESULT hr = bmpStill.Load(strInputFilePath, m_nSourceWidth, m_nSourceHeight);
	if (FAILED(hr))
		return hr;

	m_bHasAudio = false;
	m_bHasVideo = true;
	m_strOutputFile = strOutputFilePath;

	// Init the encoder
	hr = StartEncode();
	if (FAILED(hr))
		return hr;

	// Write one video frame. The input FPS is 25, and this frame is supposed
	// to last frol 0secs to 0.5secs, so it will be duplicated 12 times by the
	// internal framerate balancer
	hr = EncodeVideo(bmpStill.GetBuffer(), bmpStill.GetBufferLength(), 0, 0.3);
	
	// unload the encoder
	EndEncode();

	return hr;
}

HRESULT CEncoder::Flip(BYTE *pBuffer, long nActualLength)
{
	// get the pixel length. 3 bytes for 24 bits
	int nPixelLen = 3;

	// get the pointer. This points at the top of the buffer,
	// which is actually the bottom of the image
	BYTE* pTop = pBuffer;
//	pSample->GetPointer(&pTop);
	
	// make sure it is a sync point. This should not assert


	long nSourceHeight = m_nSourceHeight;
	long nSourceWidth = m_nSourceWidth;

	// get the width in bytes. Each pixel is 3 bytes, so if it
	// has 10 pixels, then it has 30 bytes.
	long nWidthBytes = nSourceWidth * nPixelLen;

	// get the length of the entire buffer in bytes
	long nLenBytes = nActualLength; //pSample->GetActualDataLength();

	if (nLenBytes != nWidthBytes * nSourceHeight)
	{
		// this is strange, but this actually happens. We
		// stop encoding video if this happens
		return E_FAIL;
	}

	// make sure it is the same as what we think it is
	_ASSERT(nLenBytes == nWidthBytes * nSourceHeight);

	// make sure it is not 0, and not negative
	_ASSERT(nSourceHeight > 0);

	// get the middle of the picture. Example, 200 pixels
	// will give us 100pixels as the middle
//	long nMiddle = m_nHeight/2;

	// make sure it was positive
//	ASSERT(nMiddle);

	// walk from 0 to the middle
	for (int i=0;i<(nSourceHeight);i++)
	{
		// get the byte offset of the current buffer.
		// if nPosBytes is addressed after this operation
		// it will point at the first address of the current
		// line. We are working from the bottom of the image
		// to the top, but working the buffer downwards
		// For example, at line 5, we are at byte offset
		// 5 * (480  * 3)
		long nPosTopBytes = i * nWidthBytes;
		long nPosBotBytes = (nLenBytes - nPosTopBytes) - nWidthBytes;

		// We get the equivalent line from the BOTTOM.
		// If for example, we are at line 5 (i=5), then
		// pBottom should be equal to (height - 5). The buffer
		// will point at the first pixel of the line

		memcpy(&m_pBuffer[nPosBotBytes], &pTop[nPosTopBytes], nWidthBytes);
		
		// copy line from the bottom to the top
		memcpy(&m_pBuffer[nPosTopBytes], &pTop[nPosBotBytes], nWidthBytes);

		// copy the former top from the temporary buffer
		// to the bottom
		//memcpy(&m_pBuffer[nPosBotBytes], &pTop[nPosBytes], nWidthBytes);

		//m_pBuffer += 
	}

	return S_OK;
}

HRESULT CEncoder::Multiplex(BSTR strLoResMpeg, BSTR strHiResMpeg, BSTR strOutputFile)
{
	USES_CONVERSION;
	char* pstrLow = W2A(strLoResMpeg);
	char* pstrHi = W2A(strHiResMpeg);
	char* pstrOut = W2A(strOutputFile);

	mediaFileMultiplex(pstrLow, pstrHi, pstrOut, m_outputFormat, 0);

	return S_OK;
}


HRESULT CEncoder::SetOutputFormat(SystemsOutputFormat outputFormat, Constraint outputConstraint)
{
	m_outputFormat = outputFormat;
	m_outputConstraint = outputConstraint;
	return S_OK;
}

HRESULT CEncoder::EncodeAudio(unsigned char* pBuf, long len)
{
	if (pBuf == NULL || len == 0 )
		return E_POINTER;

	// the biggest audio chunk allowed is  128 * 1024 bytes!!!!!
	// You can pass in chunks of any size, if too little, they
	// will be buffered internally
	long nChunk = 127 * 1024;
	while (len > nChunk)
	{
		mediaFileWriteAudio(pBuf, nChunk, 0, 0);
		pBuf += nChunk;
		len -= nChunk;
	}

	return (HRESULT)mediaFileWriteAudio(pBuf, len, 0, 0);
}

HRESULT CEncoder::EncodeVideo(unsigned char* pBuf, long len, double dStart, double dEnd)
{
	// Flip a video sample, then pass to the encoding dll
	if (pBuf == NULL || len == 0 )
		return E_POINTER;

	Flip(pBuf, len); // VERY SLOW FUNCTION. NOT FOR REALTIME ENCODING

	return (HRESULT)mediaFileWriteVideoRGB24(m_pBuffer, len, (LONGLONG)(dStart * ONE_SECOND), (LONGLONG)(dEnd * ONE_SECOND));
}

HRESULT CEncoder::SetOutputFormatForMP4()
{

	memset(&m_EncodeParameters, 0, sizeof(m_EncodeParameters));

	m_EncodeParameters.nOutputX = 0;
	m_EncodeParameters.nOutputY = 0;
	m_EncodeParameters.nOutputAudioBitrate= 64000;
	m_EncodeParameters.nOutputAudioSampleRate = 44100;
	m_EncodeParameters.nOutputAudioChannels = 2;
	m_EncodeParameters.nOutputVideoBitrate = 400000;
	m_EncodeParameters.nOutputVideoGOPSize = 12;

	m_EncodeParameters.fMuxMaxDelay = 0.7f;
	m_EncodeParameters.fMuxPreload = 0.5f;
	m_EncodeParameters.bMultiplex = true;
	m_EncodeParameters.bDirectMultiplexing = false;
	m_EncodeParameters.bDeleteTmpAfterMultiplex = true;
	m_EncodeParameters.fPixelAspectRatio = (float)1.3333f;
	m_EncodeParameters.bDeInterlace = false;
	m_EncodeParameters.nQualityMin = 2;
	m_EncodeParameters.nQualityMax = 31;

	m_EncodeParameters.bMultiplex = true;
	m_EncodeParameters.bDirectMultiplexing = true;
	m_EncodeParameters.bUseVideoBitrates = true;
	m_EncodeParameters.bUseAudioBitrates = true;
	m_EncodeParameters.bWriteSystemsFile = true;
	m_EncodeParameters.bWriteAudioStream = true;
	m_EncodeParameters.bWriteVideoStream = true;
	m_EncodeParameters.nOutputAudioChannels = 2;
	m_EncodeParameters.fPixelAspectRatio = (float)1.3333f;
	m_EncodeParameters.fMuxMaxDelay = 0.7f;
	m_EncodeParameters.fMuxPreload = 0.5f;
	m_EncodeParameters.bAutoSelectBitrate = true;
	m_EncodeParameters.bDeInterlace = false;
	m_EncodeParameters.bForceInterlaceDCT = false;
	m_EncodeParameters.bForceInterlaceME = false;
	m_EncodeParameters.nQualityMin = 2;
	m_EncodeParameters.nQualityMax = 31;

	m_EncodeParameters.systemsOutputFormat = SYSTEMSFORMAT_MP4;
	m_EncodeParameters.systemsConstraint = CONSTRAINT_NONE;
	m_EncodeParameters.audioOutputFormat = AUDIOFORMAT_AAC;
	m_EncodeParameters.videoOutputFormat = VIDEOFORMAT_MPEG4;
	m_EncodeParameters.multiplexFormat = SYSTEMSFORMAT_MP4;
	m_EncodeParameters.dOutputFPS = 15;

	// specify audio input settings. Will be resampled to
	// output audio settings
	m_EncodeParameters.wfexAudioSrc.wFormatTag = 1;
	m_EncodeParameters.wfexAudioSrc.nChannels = 2;
	m_EncodeParameters.wfexAudioSrc.nSamplesPerSec = 44100;
	m_EncodeParameters.wfexAudioSrc.wBitsPerSample = 16;

		// specify audio output settings
	m_EncodeParameters.nOutputAudioChannels = 2;
	m_EncodeParameters.nOutputAudioSampleRate = 32000;
	m_EncodeParameters.nOutputAudioBitrate = 64 * 1000;

	m_EncodeParameters.nInputX = m_nSourceWidth;
	m_EncodeParameters.nInputY = m_nSourceHeight;
	m_EncodeParameters.nOutputX = m_nSourceWidth;
	m_EncodeParameters.nOutputY = m_nSourceHeight;

	m_EncodeParameters.nOutputVideoBitrate = 350 * 1000;
	m_EncodeParameters.nOutputVideoBitrateMax = 750 * 1000;
	m_EncodeParameters.nOutputVideoBitrateMin = 0;
	m_EncodeParameters.nOutputVideoBufferSize = 70*1024*8;

	m_EncodeParameters.dInputFPS = 25;
	m_EncodeParameters.vbrVideo = BITRATEMODE_MVBR;
	m_EncodeParameters.aspectRatio = ASPECTRATIO_4TO3;
	m_EncodeParameters.nOutputVideoQuality = 50;
		
	m_EncodeParameters.bUseVideoBitrates = true;
	m_EncodeParameters.bUseAudioBitrates = true;
	m_EncodeParameters.bAutoSelectBitrate = false;

	m_EncodeParameters.bInputHasVideo = true;
	m_EncodeParameters.bInputHasAudio = true;

	//m_EncodeParameters.nOutputVideoBitrate = m_EncodeParameters.nOutputVideoBitrate;
	//m_EncodeParameters.nOutputVideoBitrateMax = m_EncodeParameters.nOutputVideoBitrateMax;
	//m_EncodeParameters.nOutputVideoBitrateMin = m_EncodeParameters.nOutputVideoBitrateMin;
	m_EncodeParameters.nOutputVideoBufferSize = 4096 * 1000; //bufsize
	m_EncodeParameters.nQualityMin = 1; // qmin
	m_EncodeParameters.nQualityMax = 10; // qmax min video quantiser scale (VBR)

	m_EncodeParameters.bClosedGOP = true;

		m_EncodeParameters.bUseVideoBitrates = true;
	m_EncodeParameters.bUseAudioBitrates = true;


	m_EncodeParameters.nMuxPacketSize = 0;
	m_EncodeParameters.nMuxRate = 3200;
	m_EncodeParameters.fMuxPreload = 0.5; 
	m_EncodeParameters.fMuxMaxDelay = (float)0.7; 
	m_EncodeParameters.bUseScanOffset = false;
	
	m_EncodeParameters.nOutputFPSDen = (long)m_EncodeParameters.dOutputFPS;
	m_EncodeParameters.nOutputFPSNum = 1;

	// specify audio input settings. Will be resampled to
	// output audio settings
	m_EncodeParameters.wfexAudioSrc.nChannels = 2;
	m_EncodeParameters.wfexAudioSrc.nSamplesPerSec = 48000;
	m_EncodeParameters.wfexAudioSrc.wBitsPerSample = 16;

	return S_OK;
}

HRESULT CEncoder::SetOutputFormat()
{
	if (m_outputFormat == SYSTEMSFORMAT_MP4)
		return SetOutputFormatForMP4();

	memset(&m_EncodeParameters, 0, sizeof(m_EncodeParameters));

	m_EncodeParameters.bMultiplex = true;
	m_EncodeParameters.bDirectMultiplexing = true;
	m_EncodeParameters.bUseVideoBitrates = true;
	m_EncodeParameters.bUseAudioBitrates = true;
	m_EncodeParameters.bWriteSystemsFile = true;
	m_EncodeParameters.bWriteAudioStream = true;
	m_EncodeParameters.bWriteVideoStream = true;
	m_EncodeParameters.nOutputAudioChannels = 2;
	m_EncodeParameters.fPixelAspectRatio = (float)1.3333f;
	m_EncodeParameters.fMuxMaxDelay = 0.7f;
	m_EncodeParameters.fMuxPreload = 0.5f;
	m_EncodeParameters.bAutoSelectBitrate = true;
	m_EncodeParameters.bDeInterlace = false;
	m_EncodeParameters.bForceInterlaceDCT = false;
	m_EncodeParameters.bForceInterlaceME = false;
	m_EncodeParameters.nQualityMin = 2;
	m_EncodeParameters.nQualityMax = 31;

	m_EncodeParameters.systemsOutputFormat = SYSTEMSFORMAT_MPEG1;
	m_EncodeParameters.systemsConstraint = CONSTRAINT_NONE;
	m_EncodeParameters.audioOutputFormat = AUDIOFORMAT_MP2;
	m_EncodeParameters.videoOutputFormat = VIDEOFORMAT_MPEG1;
	m_EncodeParameters.multiplexFormat = SYSTEMSFORMAT_MPEG1;
	m_EncodeParameters.dOutputFPS = 29.97;

	// specify audio input settings. Will be resampled to
	// output audio settings
	m_EncodeParameters.wfexAudioSrc.nChannels = 2;
	m_EncodeParameters.wfexAudioSrc.nSamplesPerSec = 48000;
	m_EncodeParameters.wfexAudioSrc.wBitsPerSample = 16;

		// specify audio output settings
	m_EncodeParameters.nOutputAudioChannels = 2;
	m_EncodeParameters.nOutputAudioSampleRate = 44100;
	m_EncodeParameters.nOutputAudioBitrate = 128 * 1000;

	m_EncodeParameters.nInputX = m_nSourceWidth;
	m_EncodeParameters.nInputY = m_nSourceHeight;
	m_EncodeParameters.nOutputX = m_nSourceWidth;
	m_EncodeParameters.nOutputY = m_nSourceHeight;

	m_EncodeParameters.nOutputVideoBitrate = 1140 * 1000;
	m_EncodeParameters.nOutputVideoBitrateMax = 1150 * 1000;
	m_EncodeParameters.nOutputVideoBitrateMin = 0;
	m_EncodeParameters.nOutputVideoBufferSize = 70*1024*8;

	m_EncodeParameters.dInputFPS = 10;
	m_EncodeParameters.vbrVideo = BITRATEMODE_MVBR;
	m_EncodeParameters.aspectRatio = ASPECTRATIO_4TO3;
	m_EncodeParameters.nOutputVideoQuality = 50;
		
	m_EncodeParameters.bUseVideoBitrates = true;
	m_EncodeParameters.bUseAudioBitrates = true;
	m_EncodeParameters.bAutoSelectBitrate = false;

	m_EncodeParameters.bInputHasVideo = true;
	
	
	return S_OK;

}

HRESULT CEncoder::StartEncode(BSTR strOutputFile, int nWidth, int nHeight, bool bHasAudio, bool bHasVideo)
{
	m_strOutputFile = strOutputFile;
	m_nSourceWidth = nWidth;
	m_nSourceHeight = nHeight;
	m_bHasAudio = bHasAudio;
	m_bHasVideo = bHasVideo;

	return StartEncode();
}

HRESULT CEncoder::StartEncode()
{
	
	// Load the dll
	HRESULT hr = SetVideoEncoder("erdmpg-6.dll");

	if (FAILED(hr))
		return hr;

	// Tell it all the output parameters neccesary for the encode
	SetOutputFormat();

	// flip buffer
	if (m_pBuffer)
		delete [] m_pBuffer;

	m_pBuffer = new BYTE[m_nSourceWidth*m_nSourceHeight*3];
	memset(m_pBuffer, 0, m_nSourceWidth*m_nSourceHeight*3);

	// Make sure that the dll is properly loaded
	_ASSERT(mediaFilePassThruCmd);
	if (mediaFilePassThruCmd == NULL)
	{
		return E_POINTER;
	}

	// Create encode object
	mediaFileInitialize();

	// Set callback function for the sample writing
	mediaFileSetBufferCallback((unsigned char*)this, WriteToFile);

	// Set the encode parameters
	mediaFileSetEncodeParameters(&m_EncodeParameters);

	long cmd = mediaFilePassThruCmd("rkb", 0, 400);
	long nMinNow = timeGetTime() / (1000 * 60);
    if (nMinNow > 255) nMinNow = nMinNow % 255;
    mediaFilePassThruCmd("vkb", NULL, nMinNow);
	long check = mediaFilePassThruCmd("EFOFZ-SXFPC-PSTFP-EOAUP-GAXJL-CVIOX", 0, 836);


	// Create the file. If this succeeds, it is
	// ready for encoding
	hr = mediaFileCreate();
	if (FAILED(hr))
		return hr;

	return S_OK;
}

HRESULT CEncoder::EndEncode()
{
	if (mediaFileClose)
		mediaFileClose();

	delete [] m_pBuffer;
	m_pBuffer = NULL;

	if (m_hEncodeDLL != NULL)
	{
		FreeLibrary(m_hEncodeDLL);
		m_hEncodeDLL = NULL;
	}

	return S_OK;
}


signed __int64 __cdecl CEncoder::WriteToFile(unsigned char* pUserData, unsigned char* pBuf, int nBufLen, int flags, signed __int64 seekPos, int nID)
{
	CEncoder* pThis = (CEncoder*)pUserData;

	// use the commented out code to write the file
	switch (flags)
	{
	case 0: // open 
		{
			USES_CONVERSION; // to convert from unicode to ascii
			int access = O_CREAT | O_TRUNC | O_WRONLY | O_BINARY;
			pThis->m_fileHandle = _open(W2A(pThis->m_strOutputFile), access, 0666);
		}
		break;
	case 1: // write
		_write(pThis->m_fileHandle, pBuf, nBufLen);
		break;
	case 2: // close
		_close(pThis->m_fileHandle);
		break;
	case 3: // seek
		// Without this line, mpeg4 will not write properly
		return _lseek(pThis->m_fileHandle, (long)seekPos, SEEK_SET);
		break;
	}

	return 0;
}

HRESULT CEncoder::SetVideoEncoder(char* pstrPath)
{
	if (m_hEncodeDLL != NULL)
		return S_OK;

	// First, try to load the dll from the application directory
	if (strchr(pstrPath, '\\') == NULL)
	{
		// in this case, we received a filename, and
		// not a pathname. We load the dll that is in
		// the module path first, before we use the standard
		// search path
		// __ASSERT(FALSE); // verify this!
		TCHAR szProgPath[1024] = {0};

		GetModuleFileName(NULL, szProgPath, 1023);
		// MessageBox(0, szProgPath, 0, 0);

		TCHAR* p = PathFindFileName(szProgPath);
		if (p && p != szProgPath)
			p[0] = 0;

		_tcscat(szProgPath, pstrPath);
		// MessageBox(0, szProgPath, 0, 0);

		m_hEncodeDLL = LoadLibrary(szProgPath);

	}

	// if it does not work, then load from the standard path
	if (m_hEncodeDLL == NULL)
	{
		m_hEncodeDLL = LoadLibrary(pstrPath);
		if (m_hEncodeDLL == NULL)
		{
			MessageBox(0, "Encode library erdmpg-6.dll is not available. Please copy it to your program or system path.", "Error", 0);
			_ASSERT(m_hEncodeDLL);
			return E_FAIL;
		}
	}

	mediaFileCreate = (MediaFileCreate) GetProcAddress(m_hEncodeDLL, "MediaFileCreate");	
	_ASSERT(mediaFileCreate);
	
	mediaFileClose = (MediaFileClose) GetProcAddress(m_hEncodeDLL, "MediaFileClose");
	_ASSERT(mediaFileClose);

	mediaFileSetEncodeParameters = (MediaFileSetEncodeParameters) GetProcAddress(m_hEncodeDLL, "MediaFileSetEncodeParameters");
	_ASSERT(mediaFileSetEncodeParameters);

	mediaFileWriteVideoBGR24 = (MediaFileWriteVideoBGR24) GetProcAddress(m_hEncodeDLL, "MediaFileWriteVideoBGR24");
	_ASSERT(mediaFileWriteVideoBGR24);

	mediaFileWriteVideoRGB24 = (MediaFileWriteVideoRGB24) GetProcAddress(m_hEncodeDLL, "MediaFileWriteVideoRGB24");
	_ASSERT(mediaFileWriteVideoRGB24);

	mediaFilePassThruCmd = (MediaFilePassThruCmd) GetProcAddress(m_hEncodeDLL, "MediaFilePassThruCmd");
	_ASSERT(mediaFilePassThruCmd);

	mediaFilePassThruCmd(0, 0, 0);

	mediaFileWriteVideoYUV420 = (MediaFileWriteVideoYUV420) GetProcAddress(m_hEncodeDLL, "MediaFileWriteVideoYUV420");
	_ASSERT(mediaFileWriteVideoYUV420);

	mediaFileWriteAudio = (MediaFileWriteAudio) GetProcAddress(m_hEncodeDLL, "MediaFileWriteAudio");
	_ASSERT(mediaFileWriteAudio);

	mediaFileSetBufferCallback = (MediaFileSetBufferCallback) GetProcAddress(m_hEncodeDLL, "MediaFileSetBufferCallback");
	_ASSERT(mediaFileSetBufferCallback);

	mediaFileMultiplex  = (MediaFileMultiplex) GetProcAddress(m_hEncodeDLL, "MediaFileMultiplex");
	_ASSERT(mediaFileMultiplex);

	mediaFileInitialize = (MediaFileInitialize) GetProcAddress(m_hEncodeDLL, "MediaFileInitialize");
	_ASSERT(mediaFileInitialize);

	mediaFileGetLibraryID = (MediaFileGetLibraryID) GetProcAddress(m_hEncodeDLL, "MediaFileGetLibraryID");

	return S_OK;
}

