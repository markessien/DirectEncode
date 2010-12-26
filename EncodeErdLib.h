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

#pragma once

#include "encode.h"
#include "license.h"

// #define TEST_MANUAL_WRITE

class IDeliverCallback
{
public:
	virtual HRESULT Deliver(unsigned char* pBuf, int nBufLen, int nID) = 0;
	virtual signed __int64 SeekOutput(signed __int64 newPos, int nID) = 0;
};

class CEncodeErdLib : public CEncode
{
public:
	CEncodeErdLib(void);
	~CEncodeErdLib(void);

	HRESULT EncodeAudioSample(IMediaSample *pSample);
	HRESULT EncodeVideoSample(IMediaSample *pSample);
	HRESULT StartConversion();
	HRESULT StopConversion();
	HRESULT EndOfStream();

	static signed __int64 __cdecl WriteToFile(unsigned char* pUserData, unsigned char* pBuf, int nBufLen, int flags, signed __int64 seekPos, int nID);

	bool SetVideoEncoder(char* pstrPath);
	long GetWrittenBytes();
	void SetDeliverCallback(IDeliverCallback* pCallback) {m_pCallback = pCallback;}

private:
	IDeliverCallback* m_pCallback;
	CComBSTR m_strLibraryPath;
	HINSTANCE m_hEncodeDLL;
	CLicense* m_pLicense;
	int m_nFileHandle;
	__int64 m_nContext;
};
