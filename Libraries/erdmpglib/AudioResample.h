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

// AudioResample.h: Schnittstelle für die Klasse CAudioResample.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AUDIORESAMPLE_H__4F8FA23E_41AC_4D20_9075_E661D6F039B7__INCLUDED_)
#define AFX_AUDIORESAMPLE_H__4F8FA23E_41AC_4D20_9075_E661D6F039B7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <mmsystem.h>
#include "mmreg.h"
#include "msacm.h"

class CAudioResample  
{
public:
	CAudioResample();
	virtual ~CAudioResample();
	
	HRESULT SpecifyFormats(WAVEFORMATEX &wfxSrc, WAVEFORMATEX &wfxDst);
	HRESULT Resample(BYTE* pBuffer, long nBufferLen, BYTE** pResult, long  & nResultLen);
	void Close();

private:
	long m_nSrcBufLen;
	long m_nDstBufLen;
	BYTE* m_pbDstBuffer;
	BYTE* m_pbSrcBuffer;
	HACMSTREAM m_hAcmStream;
	WAVEFORMATEX m_wfxSrc;
	WAVEFORMATEX m_wfxDst;
	ACMSTREAMHEADER m_streamheader;
};

#endif // !defined(AFX_AUDIORESAMPLE_H__4F8FA23E_41AC_4D20_9075_E661D6F039B7__INCLUDED_)
