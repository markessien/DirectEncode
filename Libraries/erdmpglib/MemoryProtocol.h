// MemoryProtocol.h: interface for the CMemoryProtocol class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MEMORYPROTOCOL_H__E777F520_6602_4833_AA68_E4C55E86683D__INCLUDED_)
#define AFX_MEMORYPROTOCOL_H__E777F520_6602_4833_AA68_E4C55E86683D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <avcodec.h>
#include <avformat.h>
#include <map>

class IMemoryProtocol
{
public:
	char szName[128];

	virtual int MemWrite(int nID, unsigned char *buf, int size) = 0;
	virtual int MemClose(int nID) = 0;
	virtual int MemOpen(int nID) = 0;
	virtual signed __int64 MemSeek(int nID, signed __int64 newPos) = 0;
}; 

class CMemoryProtocol  
{

public:
	typedef struct _MemInfo
	{
		int nID;
		char szName[128];
		CMemoryProtocol* pProtocolPtr;
	} MemInfo;


	void Register();
	void SetCallback(IMemoryProtocol* pCallback);
	void AddID(int nID, char* pstrName);
	long GetCount();

private:
	static int Open(URLContext *h, const char *filename, int flags);
	static int Read(URLContext *h, unsigned char *buf, int size);
	static int Write(URLContext *h, unsigned char *buf, int size);
	static offset_t Seek(URLContext *h, offset_t pos, int whence);
	static int Close(URLContext *h);
	static CMemoryProtocol* GetThis(int nID);

private:
	static URLProtocol mem_protocol;
	IMemoryProtocol* m_pCallback;
	static std::map<int, CMemoryProtocol::MemInfo*> m_idMap;
	static bool m_bRegistered;
};

#endif // !defined(AFX_MEMORYPROTOCOL_H__E777F520_6602_4833_AA68_E4C55E86683D__INCLUDED_)
