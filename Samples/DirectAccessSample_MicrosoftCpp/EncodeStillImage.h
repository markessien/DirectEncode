// EncodeErdLib.h: interface for the CEncodeErdLib class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENCODEERDLIB_H__6C518D30_9691_41C8_8F2A_7628CCD0D5AE__INCLUDED_)
#define AFX_ENCODEERDLIB_H__6C518D30_9691_41C8_8F2A_7628CCD0D5AE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CEncoder
{

public:
	CEncoder(void);
	~CEncoder(void);

	HRESULT CreateHighResolutionStill(BSTR strInputFilePath, BSTR strOutputFilePath);
	HRESULT CreateLowResolutionStill(BSTR strInputFilePath, BSTR strOutputFilePath);
	HRESULT SetOutputFormat(SystemsOutputFormat outputFormat, Constraint outputConstraint);
	HRESULT Multiplex(BSTR strLoResMpeg, BSTR strHiResMpeg, BSTR strOutputFile);
	HRESULT StartEncode(BSTR strOutputFile, int nWidth, int nHeight, bool bHasAudio, bool bHasVideo);
	HRESULT EncodeVideo(unsigned char* pBuf, long len, double dStart, double dEnd);
	HRESULT EncodeAudio(unsigned char* pBuf, long len);
	HRESULT EndEncode();

private:
	HRESULT StartEncode();
	HRESULT CreateStill(BSTR strInputFilePath, BSTR strOutputFilePath);
	HRESULT SetOutputFormat();
	HRESULT SetOutputFormatForMP4();
	HRESULT SetVideoEncoder(char* pstrPath);
	HRESULT Flip(BYTE *pBuffer, long nActualLength);

	static signed __int64 __cdecl WriteToFile(unsigned char* pUserData, unsigned char* pBuf, int nBufLen, int flags, signed __int64 seekPos, int nID);

private:
	bool                m_bHasAudio;
	bool                m_bHasVideo;
	CComBSTR            m_strOutputFile;
	SystemsOutputFormat m_outputFormat;
	Constraint          m_outputConstraint;
	int                 m_nSourceWidth;
	int                 m_nSourceHeight;
	EncodeParameters    m_EncodeParameters;
	CComBSTR            m_strLibraryPath;
	HINSTANCE           m_hEncodeDLL;
	int                 m_fileHandle;
	BYTE*               m_pBuffer;
};

#endif // !defined(AFX_ENCODEERDLIB_H__6C518D30_9691_41C8_8F2A_7628CCD0D5AE__INCLUDED_)
