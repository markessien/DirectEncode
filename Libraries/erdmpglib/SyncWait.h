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

// SyncWait.h: interface for the CSyncWait class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYNCWAIT_H__CC960801_0729_46C1_8CE0_BBC164BAD2A8__INCLUDED_)
#define AFX_SYNCWAIT_H__CC960801_0729_46C1_8CE0_BBC164BAD2A8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSyncWait  
{
public:
	CSyncWait();
	virtual ~CSyncWait();

	BOOL IsFrozen();
	void UnFreeze();
	void Freeze();
	BOOL IsLocked();
	void Unlock();
	void Lock();
	DWORD WaitForUnlock(DWORD dwMilliseconds);
	DWORD WaitForLock(DWORD dwMilliseconds);

private:
	HANDLE m_hEvent;
	HANDLE m_hEventUnlock;
	BOOL   m_bIsLocked;
	BOOL   m_bFreeze;
};

#endif // !defined(AFX_SYNCWAIT_H__CC960801_0729_46C1_8CE0_BBC164BAD2A8__INCLUDED_)
