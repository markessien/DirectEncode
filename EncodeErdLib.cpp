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

#include "stdafx.h"
#include "encodeerdlib.h"
// #include <ios> 
//#include <stdlib.h>
#include <fcntl.h>
#include <io.h>

// int CEncodeErdLib::m_nFileHandle = 0;

CEncodeErdLib::CEncodeErdLib(void) : m_hEncodeDLL(NULL), 
									 m_pLicense(NULL),
									 m_pCallback(NULL),
									 m_nFileHandle(0),
									 m_nContext(0)
{
}

CEncodeErdLib::~CEncodeErdLib(void)
{
	mediaFilePassThruCmd_MT(m_nContext, 0, 0, 1001);
	_ASSERT(m_pLicense == NULL);
	mediaFileUninitialize_MT(m_nContext);
	
}

HRESULT CEncodeErdLib::EncodeAudioSample(IMediaSample *pSample)
{
	// Pass an audio sample to the encoding dll
	if (pSample == NULL || mediaFileWriteAudio == NULL  || m_bWritingAudio == false)
		return E_POINTER;

	BYTE* ptr = NULL;
	HRESULT hr = pSample->GetPointer(&ptr);
	if (FAILED(hr) || ptr == NULL)
		return E_POINTER;

	long nLen = pSample->GetActualDataLength();

	LONGLONG llStart = 0, llEnd = 0;
	pSample->GetTime(&llStart, &llEnd);

	
	hr = (HRESULT)mediaFileWriteAudio_MT(m_nContext, ptr, nLen, llStart, llEnd);
	return hr;
}

HRESULT CEncodeErdLib::EndOfStream()
{
	if (mediaFileEndOfStream_MT == NULL)
		return E_FAIL;

	
	HRESULT hr = (HRESULT)mediaFileEndOfStream_MT(m_nContext);
	
	return hr;
}

HRESULT CEncodeErdLib::EncodeVideoSample(IMediaSample *pSample)
{
	// Flip a video sample, then pass to the encoding dll
	if (pSample == NULL || mediaFileWriteVideoRGB24_MT == NULL || m_pBuffer == NULL || m_bWritingVideo == false)
		return E_POINTER;

	BYTE* ptr = NULL;
	HRESULT hr = pSample->GetPointer(&ptr);
	if (FAILED(hr) || ptr == NULL)
	{
		_ASSERT(FALSE);
		return E_POINTER;
	}

	long nLen = pSample->GetActualDataLength();
	if (FAILED(Flip(ptr, nLen)))
		return S_FALSE;

	LONGLONG llStart = 0, llEnd = 0;
	pSample->GetTime(&llStart, &llEnd);
	
#ifdef _DEBUG
	double dSecs = llStart / UNITS;
	double dEnd = llEnd / UNITS;
#endif

	
	hr = (HRESULT)mediaFileWriteVideoRGB24_MT(m_nContext, m_pBuffer, nLen, llStart, llEnd);
	return hr;
}

HRESULT CEncodeErdLib::StartConversion()
{
	if (m_pEncodeProfile == NULL)
	{
		_ASSERT(m_pEncodeProfile);
		return E_POINTER;
	}


	long nSourceWidth = m_SourceSettings.nSourceWidth;
	long nSourceHeight = m_SourceSettings.nSourceHeight;

	EncodeParameters& encsettings = m_pEncodeProfile->GetEncodeParameters();
	memcpy(&encsettings.wfexAudioSrc, &m_SourceSettings.wfexSrc, sizeof(WAVEFORMATEX));

	encsettings.bInputHasAudio = m_SourceSettings.bHasAudio;
	if (encsettings.audioOutputFormat == AUDIOFORMAT_NONE)
		encsettings.bWriteAudioStream = false;
	else
		encsettings.bWriteAudioStream = m_SourceSettings.bHasAudio;

	if (encsettings.videoOutputFormat == VIDEOFORMAT_NONE)
		encsettings.bWriteVideoStream = false;
	else
		encsettings.bWriteVideoStream = m_SourceSettings.bHasVideo;

	encsettings.bUseVideoBitrates = true;
	encsettings.bUseAudioBitrates = true;
	encsettings.bAutoSelectBitrate = false;

	m_bWritingAudio = encsettings.bWriteAudioStream;
	m_bWritingVideo = encsettings.bWriteVideoStream;

	// encsettings.bWriteSystemsFile = true;
	encsettings.bInputHasVideo = m_SourceSettings.bHasVideo;
	encsettings.nInputX = nSourceWidth;
	encsettings.nInputY = nSourceHeight;

	if (encsettings.dInputFPS == 0.0f)
		encsettings.dInputFPS = m_SourceSettings.dSourceFPS;

	_ASSERT(mediaFilePassThruCmd_MT);
	if (mediaFilePassThruCmd_MT == NULL)
	{
		return E_POINTER;
	}

	USES_CONVERSION;
	strcpy_s(encsettings.szOutputFile, 1022, W2A(m_szOutputFile));

	
	if (m_pLicense == NULL)
	{
		m_pLicense = new CLicense();
		mediaFilePassThruCmd_MT(m_nContext, 0, (unsigned char*)m_pLicense->GenerateLicense(), 100000);
		delete m_pLicense;
		m_pLicense = NULL;
	}

	mediaFileSetBufferCallback_MT(m_nContext, (unsigned char*)this, WriteToFile);

	mediaFileSetEncodeParameters_MT(m_nContext, &encsettings);
	HRESULT hr = (HRESULT)mediaFileCreate_MT(m_nContext);
	if (FAILED(hr))
		return hr;

	long nBufferWidth = max(encsettings.nOutputX, nSourceWidth);
	long nBufferHeight = max(encsettings.nOutputY, nSourceHeight);

	m_pBuffer = new BYTE[nBufferWidth*nBufferHeight*4];
	memset(m_pBuffer, 0, nBufferWidth*nBufferHeight*4);
	

	return S_OK;
}

HRESULT CEncodeErdLib::StopConversion()
{
	// TODO : This call takes a long time, why block other thread?
	
	if (mediaFileClose_MT)
		mediaFileClose_MT(m_nContext);
	

	if (m_pBuffer)
		delete [] m_pBuffer;
	m_pBuffer = NULL;

	if (m_hEncodeDLL != NULL)
	{
	//	FreeLibrary(m_hEncodeDLL);
	//	m_hEncodeDLL = NULL;
	}

	return S_OK;
}

long CEncodeErdLib::GetWrittenBytes() 
{ 
	if (mediaFilePassThruCmd_MT)
	{
		return (long)mediaFilePassThruCmd_MT(m_nContext, "fs", 0, 0);
	}

	return 0; 
}

signed __int64 __cdecl CEncodeErdLib::WriteToFile(unsigned char* pUserData, unsigned char* pBuf, int nBufLen, int flags, signed __int64 newPos, int nID)
{
	CEncodeErdLib* pThis = (CEncodeErdLib*)pUserData;

	// sorry for this code, had to do some testing
	switch (flags)
	{
	case 0: // open
#if defined(TEST_MANUAL_WRITE)
		m_nFileHandle = _open("c:\\test_grab.mpg",  _O_WRONLY | _O_CREAT);
#endif
		break;
	case 1: // write
#if defined(TEST_MANUAL_WRITE)
		_write(m_nFileHandle, pBuf, nBufLen);
#else
		pThis->m_pCallback->Deliver(pBuf, nBufLen, nID);
#endif
		break;
	case 2: // close
#if defined(TEST_MANUAL_WRITE)
		_close(m_nFileHandle);
#endif
		break;
	case 3: // seek
#if defined(TEST_MANUAL_WRITE)
		return _lseek(m_nFileHandle, newPos, SEEK_SET);
#else
		{
			// if connected to a memory based filter, this will fail
			// -> streaming would not be possible with mp4 files
			// same with sample grabbing
			return pThis->m_pCallback->SeekOutput(newPos, nID);
		}
#endif
	}

	TraceVerbose("WriteToFile exit\n");
	return 0;
}

bool CEncodeErdLib::SetVideoEncoder(char* pstrPath)
{
	if (m_hEncodeDLL != NULL)
	{
		// this is a work around to make sure that the encoder
		// dll is reloaded. This resets all the parameters and
		// makes multiple mpeg-4 conversions work
		FreeLibrary(m_hEncodeDLL);
		m_hEncodeDLL = NULL;
	}

	// load the libraries
	 
	/*
	HINSTANCE hTmp = LoadLibrary("avutilerd-49.dll");
	hTmp = LoadLibrary("avformaterd-52.dll");
	hTmp = LoadLibrary("avcodecerd-51.dll");
	hTmp = LoadLibrary("libfaac.dll");
*/
	if (strchr(pstrPath, '\\') == NULL)
	{
		// in this case, we received a filename, and
		// not a pathname. We load the dll that is in
		// the module path first, before we use the standard
		// search path
		// _ASSERT(FALSE); // verify this!
		TCHAR szProgPath[1024] = {0};

		GetModuleFileName(NULL, szProgPath, 1023);
		// MessageBox(0, szProgPath, 0, 0);

		TCHAR* p = PathFindFileName(szProgPath);
		if (p && p != szProgPath)
			p[0] = 0;

		_tcscat_s(szProgPath, 1024, pstrPath);
		// MessageBox(0, szProgPath, 0, 0);

		m_hEncodeDLL = LoadLibrary(szProgPath);

		if (m_hEncodeDLL == NULL)
		{
#ifdef _DEBUG
			// m_hEncodeDLL = LoadLibrary(pstrPath);
			m_hEncodeDLL = LoadLibrary("C:\\Mark\\Development\\DirectEncode\\Libraries\\erdmpglib\\erdmpg-6.dll");
			// m_hEncodeDLL = LoadLibrary("C:\\Documents an	d Settings\\Mark\\Desktop\\erdmpglib\\Debug\\erdmpg-6.debug.dll");
#endif
		}
	}

	if (m_hEncodeDLL == NULL)
	{
		_ASSERT(FALSE);
		m_hEncodeDLL = LoadLibrary(pstrPath);
		if (m_hEncodeDLL == NULL)
		{
			char sz[1024];
			strcpy_s(sz, 1024, "Encode library erdmpg-6.dll is not available. Please copy it to your program or system path.");
#ifndef VS6
			sprintf(sz, "Encode library erdmpg-6.dll is not available. Please copy it to your program or system path. Error Number=%lu",  GetLastError());
#endif
			MessageBox(0, sz, "LoadLibrary Error", 0);
			_ASSERT(m_hEncodeDLL);
			return false;
		}
	}

	mediaFileCreate = (MediaFileCreate) GetProcAddress(m_hEncodeDLL, "MediaFileCreate");	
	ASSERT(mediaFileCreate);
	
	mediaFileInitialize = (MediaFileInitialize) GetProcAddress(m_hEncodeDLL, "MediaFileInitialize");	
	ASSERT(mediaFileInitialize);

	mediaFileUninitialize = (MediaFileUninitialize) GetProcAddress(m_hEncodeDLL, "MediaFileUninitialize");	
	ASSERT(mediaFileUninitialize);

	mediaFileClose = (MediaFileClose) GetProcAddress(m_hEncodeDLL, "MediaFileClose");
	ASSERT(mediaFileClose);

	mediaFileSetEncodeParameters = (MediaFileSetEncodeParameters) GetProcAddress(m_hEncodeDLL, "MediaFileSetEncodeParameters");
	ASSERT(mediaFileSetEncodeParameters);

	mediaFileWriteVideoBGR24 = (MediaFileWriteVideoBGR24) GetProcAddress(m_hEncodeDLL, "MediaFileWriteVideoBGR24");
	ASSERT(mediaFileWriteVideoBGR24);

	mediaFileWriteVideoRGB24 = (MediaFileWriteVideoRGB24) GetProcAddress(m_hEncodeDLL, "MediaFileWriteVideoRGB24");
	ASSERT(mediaFileWriteVideoRGB24);

	mediaFilePassThruCmd = (MediaFilePassThruCmd) GetProcAddress(m_hEncodeDLL, "MediaFilePassThruCmd");
	ASSERT(mediaFilePassThruCmd);

	mediaFilePassThruCmd(0, 0, 0);

	mediaFileWriteVideoYUV420 = (MediaFileWriteVideoYUV420) GetProcAddress(m_hEncodeDLL, "MediaFileWriteVideoYUV420");
	ASSERT(mediaFileWriteVideoYUV420);

	mediaFileWriteAudio = (MediaFileWriteAudio) GetProcAddress(m_hEncodeDLL, "MediaFileWriteAudio");
	ASSERT(mediaFileWriteAudio);

	mediaFileSetBufferCallback = (MediaFileSetBufferCallback) GetProcAddress(m_hEncodeDLL, "MediaFileSetBufferCallback");
	ASSERT(mediaFileSetBufferCallback);

	mediaFileEndOfStream = (MediaFileEndOfStream) GetProcAddress(m_hEncodeDLL, "MediaFileEndOfStream");
	ASSERT(mediaFileEndOfStream);

	// Load new multithreaded functions
	mediaFileCreate_MT = (MediaFileCreate_MT) GetProcAddress(m_hEncodeDLL, "MediaFileCreate_MT");
	ASSERT(mediaFileCreate_MT);
	if (mediaFileCreate_MT == NULL)
		MessageBox(0, _T("This version of the encoder requires a newer erdmpg-6.dll"), 0, 0);

	mediaFileClose_MT = (MediaFileClose_MT) GetProcAddress(m_hEncodeDLL, "MediaFileClose_MT");
	ASSERT(mediaFileClose_MT);
	
	mediaFileSetEncodeParameters_MT = (MediaFileSetEncodeParameters_MT) GetProcAddress(m_hEncodeDLL, "MediaFileSetEncodeParameters_MT");
	ASSERT(mediaFileSetEncodeParameters_MT);

	mediaFileWriteVideoRGB24_MT = (MediaFileWriteVideoRGB24_MT) GetProcAddress(m_hEncodeDLL, "MediaFileWriteVideoRGB24_MT");
	ASSERT(mediaFileWriteVideoRGB24_MT);

	mediaFileWriteAudio_MT = (MediaFileWriteAudio_MT) GetProcAddress(m_hEncodeDLL, "MediaFileWriteAudio_MT");
	ASSERT(mediaFileWriteAudio_MT);

	mediaFilePassThruCmd_MT = (MediaFilePassThruCmd_MT) GetProcAddress(m_hEncodeDLL, "MediaFilePassThruCmd_MT");
	ASSERT(mediaFilePassThruCmd_MT);

	mediaFileWriteAudio_MT = (MediaFileWriteAudio_MT) GetProcAddress(m_hEncodeDLL, "MediaFileWriteAudio_MT");
	ASSERT(mediaFileWriteAudio_MT);

	mediaFileSetBufferCallback_MT = (MediaFileSetBufferCallback_MT) GetProcAddress(m_hEncodeDLL, "MediaFileSetBufferCallback_MT");
	ASSERT(mediaFileSetBufferCallback_MT);

	mediaFileWriteAudio_MT = (MediaFileWriteAudio_MT) GetProcAddress(m_hEncodeDLL, "MediaFileWriteAudio_MT");
	ASSERT(mediaFileWriteAudio_MT);

	mediaFileInitialize_MT = (MediaFileInitialize_MT) GetProcAddress(m_hEncodeDLL, "MediaFileInitialize_MT");
	ASSERT(mediaFileInitialize_MT);

	mediaFileUninitialize_MT = (MediaFileUninitialize_MT) GetProcAddress(m_hEncodeDLL, "MediaFileUninitialize_MT");
	ASSERT(mediaFileUninitialize_MT);

	mediaFileEndOfStream_MT = (MediaFileEndOfStream_MT) GetProcAddress(m_hEncodeDLL, "MediaFileEndOfStream_MT");
	ASSERT(mediaFileEndOfStream_MT);

	mediaFileSetParameter_MT = (MediaFileSetParameter_MT) GetProcAddress(m_hEncodeDLL, "MediaFileSetParameter_MT");
	ASSERT(mediaFileSetParameter_MT);

	mediaFileSetFormat_MT = (MediaFileSetFormat_MT) GetProcAddress(m_hEncodeDLL, "MediaFileSetFormat_MT");
	ASSERT(mediaFileSetFormat_MT);

//	if (mediaFileUninitialize_MT)
//		mediaFileUninitialize_MT();

	m_nContext = mediaFileInitialize_MT();

	return true;
}

