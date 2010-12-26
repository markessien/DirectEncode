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
