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
