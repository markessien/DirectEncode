// SequenceHeaders.h: interface for the CSequenceHeaders class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SEQUENCEHEADERS_H__DA358C39_A829_49CF_9B24_08A650DF7C66__INCLUDED_)
#define AFX_SEQUENCEHEADERS_H__DA358C39_A829_49CF_9B24_08A650DF7C66__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSequenceHeaders  
{
public:
	CSequenceHeaders();
	virtual ~CSequenceHeaders();

private:
	/*
	uint8_t* FindStartCode(const uint8_t * restrict p, const uint8_t *end, uint32_t * restrict state);
	void ExtractSequenceHeaders(char* pBuf, long nLen);
	*/
};

#endif // !defined(AFX_SEQUENCEHEADERS_H__DA358C39_A829_49CF_9B24_08A650DF7C66__INCLUDED_)
