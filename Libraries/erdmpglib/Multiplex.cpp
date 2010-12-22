#include "StdAfx.h"
#include "multiplex.h"
#include <stdio.h>
// #include <domux.h>

CMultiplex::CMultiplex(void)
{
	m_szSystemsFile[0] = 0;
	m_szAudioFile[0] = 0;
	m_szVideoFile[0] = 0;
	m_bVBR = false;
	m_nMuxRate = 0;
	m_nPulldown = 0;
	m_outputFormat = SYSTEMSFORMAT_NONE;
	m_bDeleteAfterMux = true;
}

CMultiplex::~CMultiplex(void)
{
}

HRESULT CMultiplex::StartMultiplex(bool bAsnychronous)
{
	DeleteFile(m_szSystemsFile);

	if (bAsnychronous)
	{
		DWORD dwThreadID = 0;
		CreateThread(NULL,
					(DWORD) 0, 
					StartMultiplexEntry,
					(LPVOID) this,
					(DWORD) 0,
					&dwThreadID);
	}
	else
	{
		return StartMultiplex();
	}

	return S_FALSE;
}


HRESULT CMultiplex::StartMultiplex()
{
	/*
	int nFormat = MPEG_MPEG1;
	switch (m_outputFormat)
	{
	case SYSTEMSFORMAT_NONE:
		_ASSERT(FALSE);
		return E_UNEXPECTED;
		break;
	case SYSTEMSFORMAT_MPEG1:
		nFormat = MPEG_MPEG1;
		break;
	case SYSTEMSFORMAT_MPEG2:
		nFormat = MPEG_MPEG2;
		break;
	case SYSTEMSFORMAT_VCD_STILL:
		nFormat = 6;
		break;
	case SYSTEMSFORMAT_VCD:
		nFormat = MPEG_VCD;
		break;
	case SYSTEMSFORMAT_SVCD_STILL:
		nFormat = 7;
		break;
	case SYSTEMSFORMAT_SVCD:
		nFormat = MPEG_SVCD;
		break;
	case SYSTEMSFORMAT_DVD:
		nFormat = MPEG_DVD;
		break;
	}

	char* pstrAudioFile = m_szAudioFile[0] != 0 ? m_szAudioFile : NULL;
	char* pstrVideoFile = m_szVideoFile;
	char* pstrSystemsFile = m_szSystemsFile;

	BOOL b = FALSE;
	if (m_outputFormat == SYSTEMSFORMAT_SVCD_STILL || 
		m_outputFormat == SYSTEMSFORMAT_VCD_STILL)
	{
		TCHAR szOptions[128];
		sprintf(szOptions, "-f %lu", nFormat);
		
		// if (m_bVBR)
			strcat(szOptions, " -vbr");

	//	strcat(szOptions, " -r 2500 ");

		TCHAR szOutput[1024];
		sprintf(szOutput, "-o%s", pstrSystemsFile);

		TCHAR* szArgs[5];
		szArgs[0] = "erdmpglib.dll";
		szArgs[1] = szOptions;
		szArgs[2] = szOutput;
		
		if (pstrVideoFile)
		{
			 // video file
			szArgs[3] = pstrVideoFile;
		}
		else
		{
			// no video file, must have audio
			szArgs[3] = pstrAudioFile;
		}

		int nArgs = 4;
		if (pstrAudioFile && pstrVideoFile) {
			szArgs[4] = pstrAudioFile;
			nArgs = 5;
		}

		try {
		// StartMux(nArgs, szArgs);
		} 
		catch (...)
		{
			return E_FAIL;
		}
	}
	else
		b = AVMux(pstrAudioFile, pstrVideoFile, pstrSystemsFile, nFormat, m_nMuxRate, m_bVBR, m_nPulldown);

	if (b == TRUE)
	{
		if (m_bDeleteAfterMux)
		{
			
			DeleteFile(m_szVideoFile);
			DeleteFile(m_szAudioFile);
		}
	}

	return b ? S_OK : E_FAIL;
	*/
	return E_FAIL;
}

DWORD __stdcall CMultiplex::StartMultiplexEntry(LPVOID lpvThreadParm)
{
	CMultiplex* pThis = (CMultiplex*)lpvThreadParm;
	return pThis->StartMultiplex();
}

double CMultiplex::GetProgress()
{
	return 0.0;
}

double CMultiplex::GetDuration()
{
	return 0.0;
}

void CMultiplex::SetDuration(double dDuration)
{

}

void CMultiplex::StopMultiplex(void)
{
	// AbortMux();
}

void CMultiplex::SetFiles(char* pstrAudioFile, char* pstrVideoFile, char* pstrSystemsFile)
{
	if (pstrAudioFile)
		strcpy(m_szAudioFile, pstrAudioFile);
	
	if (pstrVideoFile)
		strcpy(m_szVideoFile, pstrVideoFile);
	
	if (pstrSystemsFile)
		strcpy(m_szSystemsFile, pstrSystemsFile);
}

void CMultiplex::SetParameters(SystemsOutputFormat outputFormat, int nMultiplexRate, bool bVBR, int nPulldown, bool bDeleteTmpFiles)
{
	m_bVBR = bVBR;
	m_nMuxRate = nMultiplexRate;
	m_outputFormat = outputFormat;
	m_nPulldown = nPulldown;
	m_bDeleteAfterMux = bDeleteTmpFiles;
}
