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
