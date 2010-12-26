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
