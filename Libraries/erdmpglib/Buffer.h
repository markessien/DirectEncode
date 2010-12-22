#pragma once

class CBufferArray
{
	typedef struct Buf
	{
		BYTE* ptr;
		long len;
	} Buf;

public:
	CBufferArray(void);
	~CBufferArray(void);
	void AddBuffer(BYTE* ptr, long nLen, bool bCopy);
	bool ReadExactMinimizeCopy(BYTE* pDestination, long nRequiredLength);

private:
	Buf  m_arrPtrs[10];
	long m_nStackTop;
	long m_nStackBot;
};
