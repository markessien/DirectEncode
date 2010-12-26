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

extern "C" int __stdcall AVMux(char* pstrAudioFile, char* pstrVideoFile, char* pstrOutputFile, int nMuxType, long nMuxRate, bool bVBR, int nPulldown);
extern "C" int __stdcall GetProgressPercent();
extern "C" int __stdcall GetMuxState();
extern "C" int __stdcall AbortMux();

#define MPEG_MPEG1  0
#define MPEG_VCD    1
#define MPEG_MPEG2  2
#define MPEG_SVCD   3
#define MPEG_DVD    4

#include "erdmpglib.h"

class CMultiplex
{
public:
	CMultiplex(void);
	~CMultiplex(void);

public:
	HRESULT StartMultiplex(bool bAsnychronous);
	void StopMultiplex(void);
	double GetProgress();
	double GetDuration();
	void SetDuration(double dDuration);
	void SetFiles(char* pstrAudioFile, char* pstrVideoFile, char* pstrSystemsFile);
	void SetParameters(SystemsOutputFormat outputFormat, int nMultiplexRate, bool bVBR, int nPulldown, bool bDeleteTmpFiles);

private:
	static DWORD __stdcall StartMultiplexEntry(LPVOID lpvThreadParm);
	HRESULT StartMultiplex();

private:
	char m_szSystemsFile[1024];
	char m_szVideoFile[1024];
	char m_szAudioFile[1024];
	SystemsOutputFormat m_outputFormat;
	long  m_nMuxRate;
	bool  m_bVBR;
	long  m_nPulldown;
	bool  m_bDeleteAfterMux;
};
