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

// MemoryProtocol.cpp: implementation of the CMemoryProtocol class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MemoryProtocol.h"
#include <fcntl.h>
#include <io.h>

#define ENOENT 2

URLProtocol CMemoryProtocol::mem_protocol = {
    "memory",
    CMemoryProtocol::Open,
    CMemoryProtocol::Read,
    CMemoryProtocol::Write,
    CMemoryProtocol::Seek,
    CMemoryProtocol::Close,
};

// IMemoryProtocol*        CMemoryProtocol::m_pCallback = NULL;


std::map<int, CMemoryProtocol::MemInfo*> CMemoryProtocol::m_idMap;
bool					CMemoryProtocol::m_bRegistered = false;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////



int CMemoryProtocol::Open(URLContext *h, const char *filename, int flags)
{
	CMemoryProtocol* pThis = NULL;
	h->priv_data = 0;

	std::map<int, MemInfo*>::iterator it;
	for (it = m_idMap.begin(); it != m_idMap.end(); ++it)
	{
		MemInfo* pItem = it->second;

		if (strcmp(filename, pItem->szName) == 0)
		{
			_ASSERT(h->priv_data == NULL); // if this asserts, then two prots with same name!
			h->priv_data = (void*)pItem->nID;
			pThis = pItem->pProtocolPtr;
		} 
	}
	
	if (pThis)
		pThis->m_pCallback->MemOpen((int)h->priv_data);
	else
		MessageBox(0, "The code is faulty. The callback routines were not properly set", 0, 0);

    return 0;
}

CMemoryProtocol* CMemoryProtocol::GetThis(int nID)
{
	if (m_idMap.find(nID) != m_idMap.end())
		return m_idMap[nID]->pProtocolPtr;

	return NULL;
}

int CMemoryProtocol::Read(URLContext *h, unsigned char *buf, int size)
{
	_ASSERT(FALSE);
	return 0;
}
 
int CMemoryProtocol::Write(URLContext *h, unsigned char *buf, int size)
{
	CMemoryProtocol* pThis = GetThis((int)h->priv_data);
	if (pThis)
		pThis->m_pCallback->MemWrite((int)h->priv_data, buf, size);

    return size;
}

offset_t CMemoryProtocol::Seek(URLContext *h, offset_t pos, int whence)
{
	_ASSERT(whence == SEEK_SET);
	CMemoryProtocol* pThis = GetThis((int)h->priv_data);
	if (pThis)
		return pThis->m_pCallback->MemSeek((int)h->priv_data, pos);
	return 0;
	// return pos;
}

int CMemoryProtocol::Close(URLContext *h)
{
	// MessageBox(0, "Close", 0, 0);

	CMemoryProtocol* pThis = GetThis((int)h->priv_data);
	if (pThis)
		pThis->m_pCallback->MemClose((int)h->priv_data);
	
	MemInfo* pInfo = m_idMap[(int)h->priv_data];
	m_idMap.erase((int)h->priv_data);
	delete pInfo;

	/*
	m_nArrSize--;
	if (m_nArrSize < 0)
		m_nArrSize = 0;
*/
//	MessageBox(0, "Close Done", 0, 0);

	return 0;
}

void CMemoryProtocol::AddID(int nID, char* pstrName)
{
	// IMemoryProtocol is a ptr to the class that should receive the
	// functions we want to receive

	MemInfo* pInfo = new MemInfo();
	pInfo->nID = nID;
	pInfo->pProtocolPtr = this;
	strcpy(pInfo->szName, pstrName);
	m_idMap[nID] = pInfo;
}

void CMemoryProtocol::Register() 
{
	if (m_bRegistered == false)
		register_protocol(&mem_protocol);

	m_bRegistered = true;
}

void CMemoryProtocol::SetCallback(IMemoryProtocol* pCallback)
{
	m_pCallback = pCallback;
}

long CMemoryProtocol::GetCount()
{
	return m_idMap.size();
}
