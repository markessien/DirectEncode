#include "StdAfx.h"
#include "buffer.h"

CBufferArray::CBufferArray(void)
{
}

CBufferArray::~CBufferArray(void)
{
}

void CBufferArray::AddBuffer(BYTE* ptr, long len, bool bCopy)
{
	if (m_nStackTop == 10)
		m_nStackTop = 0;
	
	m_arrPtrs[m_nStackTop].ptr = ptr;
	m_arrPtrs[m_nStackTop].len = len;
}

bool CBufferArray::ReadExactMinimizeCopy(BYTE* pDestination, long nRequiredLength)
{
	if (m_nStackBot == 10)
		m_nStackBot = 0;

	return false;
}
