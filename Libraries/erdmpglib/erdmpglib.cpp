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

// fflib.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
// #include <Mmreg.h>
#include "erdmpglib.h"
#include "encode.h"
#include "licenseauth.h"
#include "license.h"
#include <map>

char g_szPassThruCmd[12646];
CEncode* g_pCurEncoder = NULL;
CLicenseAuth g_License;

void LoadProfilePreset(char* pstrPresetName, EncodeParameters* pTargetEncodeParameters);

CEncode* GetEncoder()
{
	return g_pCurEncoder;
}

void DeleteEncoder()
{
	if (g_pCurEncoder)
		delete g_pCurEncoder;
	g_pCurEncoder = NULL;
}

/*
void CreateAll()
{
	if (g_pEncode == NULL)
		g_pEncode = new CEncode();
}
*/


BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
    return TRUE;
}

long __cdecl MediaFileSetBufferCallback(unsigned char* pUserData, signed __int64 (__cdecl *p)(unsigned char* pUserData, unsigned char* ptr, int buflen, int flags, signed __int64 seekPos, int nID))
{
	if (GetEncoder())
		return GetEncoder()->SetBufferCallback(pUserData, p);

	return 0;
}

long __cdecl MediaFileMultiplex(char* pstrFile1, char* pstrFile2, char* pstrOutputFile, int nFormat, int nExtra)
{
	if (GetEncoder())
		return GetEncoder()->FileMultiplex(pstrFile1, pstrFile2, pstrOutputFile, nFormat, nExtra);

	return 0;
}


bool g_bValidated = false;

long __cdecl MediaFilePassThruCmd(char* p1, unsigned char* p2, __int64 n)
{
	if (p1)
		strcpy(g_szPassThruCmd, p1);

	static int nValidate = 0;

	if (p1 && (strcmp(p1, "vkb") == 0))
	{
		int i = 0;
		while (i<2)
		{
			long nMinNow = (timeGetTime() / (1000 * 60)) + i;
			if (nMinNow > 255) nMinNow = nMinNow % 255;

			if (n == nMinNow)
				g_bValidated = true;

			i++;
		}

		return S_OK;
	}

	if (n == 836)
	{
		if (GetEncoder() == NULL) {
			MessageBox(0, "You need to initialize the dll first", 0, 0);
			return 0;
		}

		bool bEnableNewFeatures = false;
		CLicense* pLicense = new CLicense();
		bool bValid = pLicense->IsLicenseValid(p1, bEnableNewFeatures);

		if (bValid && bEnableNewFeatures && g_bValidated)
			GetEncoder()->SetRegistered(true);

		delete pLicense;
	}
	else if (n == 400)
	{
		if (strcmp(p1, "rkb") == 0)
		{
			srand( (unsigned int )timeGetTime( ) );
			nValidate = (rand() % 230) + 1;
			return nValidate;
		}
	}
	else if (n == 100000)
	{
		g_License.AnalyseLicense((char*)p2);
		g_License.CallAuthenticationFunction();
		if (GetEncoder())
			GetEncoder()->SetRegistered(true);
	}
	else if (n == 1001)
	{
		DeleteEncoder();
	}
	else if (n == 2000)
	{
		MessageBox(0, "Not used anymore! Uses MediaFileInitialize", 0, 0);
	}
	else if (n == 2001)
	{
		DeleteEncoder();
	}

	return E_NOTIMPL;
}

long __cdecl MediaFileSetEncodeParameters(EncodeParameters* params)
{
	if (GetEncoder())
		return GetEncoder()->SetEncodeParams(params);

	return E_FAIL;
}

long __cdecl MediaFileCreate()
{
	if (GetEncoder())
		return GetEncoder()->StartConversion();

	return E_FAIL;
}

long __cdecl MediaFileWriteVideoBGR24(unsigned char *imgDataP, long len, LONGLONG llStartTime, LONGLONG llEndTime)
{
	if (GetEncoder() && imgDataP)
		return GetEncoder()->EncodeVideoSample((unsigned __int8*)imgDataP, len, llStartTime, llEndTime);

	return E_FAIL;
}

long __cdecl MediaFileWriteVideoRGB24(unsigned char *imgDataP, long len, LONGLONG llStartTime, LONGLONG llEndTime)
{
	if (GetEncoder() && imgDataP)
		return GetEncoder()->EncodeVideoSample((unsigned __int8*)imgDataP, len, llStartTime, llEndTime);

	return E_FAIL;
}

long __cdecl MediaFileWriteVideoYUV420(unsigned char *imgDataP, long len, LONGLONG llStartTime, LONGLONG llEndTime)
{
	return E_NOTIMPL;
}

long __cdecl MediaFileGetLibraryID()
{
	return 440;
}

long __cdecl MediaFileClose()
{
	if (GetEncoder())
		return GetEncoder()->StopConversion();

	return E_FAIL;
}

long __cdecl MediaFileWriteAudio(unsigned char *audDataP, long len, LONGLONG llStartTime, LONGLONG llEndTime)
{
	if (GetEncoder())
		return GetEncoder()->EncodeAudioSample((unsigned __int8*)audDataP, len, llStartTime, llEndTime);
	
	return E_FAIL;
}

long __cdecl MediaFileSetParameter(char* pstrParameterName, char* pstrParameterValue)
{
	if (GetEncoder())
		return GetEncoder()->SetEncodeParameter(pstrParameterName, pstrParameterValue);
	
	return S_OK;
}

long __cdecl MediaFileSetFormat(char* pstrPresetName)
{
	EncodeParameters encodeParams;
	MediaFileLoadPreset(pstrPresetName, &encodeParams);
	MediaFileSetEncodeParameters(&encodeParams);

	return S_OK;
}

long __cdecl MediaFileLoadPreset(char* pstrPresetName, EncodeParameters* pTargetEncodeParameters)
{

	LoadProfilePreset(pstrPresetName, pTargetEncodeParameters);

	return S_OK;
}

long __cdecl MediaFileInitialize()
{
	// Delete any existing encoder from a previous init cal
	DeleteEncoder();

	// Create a new encoder
	g_pCurEncoder = new CEncode();

	return S_OK;
}

long __cdecl MediaFileUninitialize()
{
	DeleteEncoder();

	return S_OK;
}

long __cdecl MediaFileEndOfStream()
{
	if (GetEncoder())
		GetEncoder()->StopConversion();

	return S_OK;
}

__int64 __cdecl MediaFileCreate_MT(__int64 contextID)
{
	CEncode* pEncode = (CEncode*)contextID;
	return pEncode->StartConversion();
}

__int64 __cdecl MediaFileClose_MT(__int64 contextID)
{
	CEncode* pEncode = (CEncode*)contextID;
	return pEncode->StopConversion();
}

__int64 __cdecl MediaFileSetEncodeParameters_MT(__int64 contextID, EncodeParameters* params)
{
	CEncode* pEncode = (CEncode*)contextID;
	pEncode->SetEncodeParams(params);

	return S_OK;
}

__int64 __cdecl MediaFileWriteVideoRGB24_MT(__int64 contextID, unsigned char *imgDataP, long len, LONGLONG llStartTime, LONGLONG llEndTime)
{
	CEncode* pEncode = (CEncode*)contextID;
	return pEncode->EncodeVideoSample((unsigned __int8*)imgDataP, len, llStartTime, llEndTime);
}

__int64 __cdecl MediaFileWriteAudio_MT(__int64 contextID, unsigned char *audDataP, long len, LONGLONG llStartTime, LONGLONG llEndTime)
{
	CEncode* pEncode = (CEncode*)contextID;
	return pEncode->EncodeAudioSample((unsigned __int8*)audDataP, len, llStartTime, llEndTime);
}

__int64 __cdecl MediaFilePassThruCmd_MT(__int64 contextID, char* p1, unsigned char* p2, __int64 n)
{
	CEncode* pEncode = (CEncode*)contextID;

	// We don't want to duplicate the call. This function
	// should not be called in a thread unsafe manner
	g_pCurEncoder = pEncode;
	return MediaFilePassThruCmd(p1, p2, n);;
}

__int64 __cdecl MediaFileSetBufferCallback_MT(__int64 contextID, unsigned char* pUserData, signed __int64 (__cdecl *p)(unsigned char* pUserData, unsigned char* ptr, int buflen, int flags, signed __int64 seekPos, int nID))
{
	CEncode* pEncode = (CEncode*)contextID;
	return pEncode->SetBufferCallback(pUserData, p);
}

__int64 __cdecl MediaFileInitialize_MT()
{
	CEncode* pEncode = new CEncode();
	return (__int64)pEncode;
}

__int64 __cdecl MediaFileUninitialize_MT(__int64 contextID)
{
	CEncode* pEncode = (CEncode*)contextID;
	if (g_pCurEncoder == pEncode)
		g_pCurEncoder = NULL;
	delete pEncode;

	return S_OK;
}

__int64 __cdecl MediaFileEndOfStream_MT(__int64 contextID)
{
	CEncode* pEncode = (CEncode*)contextID;
	pEncode->StopConversion();

	return S_OK;
}

__int64 __cdecl MediaFileSetParameter_MT(__int64 contextID, char* pstrParameterName, char* pstrParameterValue)
{
	CEncode* pEncode = (CEncode*)contextID;
	return pEncode->SetEncodeParameter(pstrParameterName, pstrParameterValue);
}

__int64 __cdecl MediaFileSetFormat_MT(__int64 contextID, char* pstrPresetName)
{
	CEncode* pEncode = (CEncode*)contextID;
	
	EncodeParameters encodeParams;
	MediaFileLoadPreset(pstrPresetName, &encodeParams);
	MediaFileSetEncodeParameters_MT(contextID, &encodeParams);

	return S_OK;
}

