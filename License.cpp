#include "StdAfx.h"
#include "license.h"
#include <time.h>
#undef lstrcpyW

#define chrtol(x) (x - 48)

#define d 4
#define nmax 501
#define mmax ((int)(3322L*nmax*d/1000))
#define r2 10000 

CLicense::CLicense(void)
{
	srand( (unsigned int )timeGetTime( ) );
	GenerateShortLicense();
}

CLicense::~CLicense(void)
{
}

char CLicense::GetRandomCapitalLetter()
{
	// chrtol for char to long
	// capitals are 65 - 90
	int n = rand() % 25;
	char c = (char)(int)(65 + n);
	return c;
}

long CLicense::GetPiDigit(int nDigit)
{
   int i, k, m, n;
    long q;
    static long a[mmax];
    n = nmax;
    m = (int)(3322L*n*d/1000);
    for (i = 0; i < m; i++)
        *(a+i) = 2;
    a[m] = 4;

	int nc = 0;
    for (i = 1; i <= n; i++) {
        q = 0;
        for (k = m; k > 0; k--) {
            long k2p1;

            k2p1 = k+k+1;
            *(a + k) = *(a + k)*r2+q;
            q = a[k]/(k2p1);
            *(a + k) -= (k2p1)*q;
            q *= k;
        }
        *a = *a*r2+q;
        q = *a/r2;
        *a -= q*r2;

		nc++;
		if (nc == nDigit)
			return (q / 1000);
        // printf("%04ld%s", q, i & 15 ? " " : "\n");
    }

	return 1;
}

char* CLicense::GenerateLicense()
{
	char sz[1024] = {0};
	
	char* pstr = sz;

	srand( (unsigned int )timeGetTime( ) );

	// get the number of hours system has been on
	long nHourNow = timeGetTime() / (1000 * 60 * 60);

	int i = 0;
	int u = 0;
	int j = 50;
	int k = 10;
	// first we get 4 random capital letters
	while (pstr)
	{
		for (i=0;i<4;i++)
		{
			pstr[i] = GetRandomCapitalLetter();
		}

		// now, we use pi combined with the current time
		// to match the license key values
		for (i=4;i<8;i++)
		{
			// get the long value of the corresponding character
			// which is the nearest one to it. This number lies
			// between 65 and 90
			long nVal = pstr[7-i];

			// get a pival based on the number of hours. This is
			// a single digit between 1 and 9
			long nPiVal = GetPiDigit(nHourNow + j);
			nPiVal = nPiVal * 2; // max of 9 * 9 = 81;
			nPiVal += GetPiDigit(nHourNow + k); // add a single digit
			nPiVal += nVal;

			pstr[i] = (char)nPiVal;
		}

		u++;
		if ( u == 1 )
		{
			pstr = sz + 8;
			j += 7;
			k -= 1;
		}
		else if ( u == 2 )
			pstr = NULL;
	}

	_tcscpy_s(m_szLibBuffer, 1024, sz);

	return m_szLibBuffer;
}


bool CLicense::IsLicenseKeyOld(char *pstrLicense)
{
	/*
	if (strlen(pstrLicense) < 24)
		return true;

	if (strcmp(pstrLicense, "ELDG-FEFH-STKT-RVGJ-OPGP") == 0)
		return true;

	if (strcmp(pstrLicense, "GKDH-FEFH-XZWU-PWGM-TVSQ") == 0)
		return true;

	if (strcmp(pstrLicense, "FLDG-FEFH-JVLU-QJGL-FRHQ") == 0)
		return true;

	if (strcmp(pstrLicense, "EIDH-FEFH-HSFS-TJGY-DOBO") == 0)
		return true;

	if (strcmp(pstrLicense, "FIDH-FEFH-UOVF-SLGM-QKRB") == 0)
		return true;

	if (strcmp(pstrLicense, "GKDH-FEFH-OHNF-PJGL-KDJB") == 0)
		return true;

	if (strcmp(pstrLicense, "GKDH-FEFH-XXYV-PKGH-TTUR") == 0)
		return true;

	if (strcmp(pstrLicense, "GNDH-4523-XSLS-9834-TOHO") == 0)
		return true;

	if (strcmp(pstrLicense, "EGDI-FEFH-VIHG-URGF-REDC") == 0)
		return true;

	if (strcmp(pstrLicense, "GIDH-FEFH-UQJM-RHGI-QMFI") == 0)
		return true;

	if (strcmp(pstrLicense, "GKDH-FEFH-OHNF-PJGL-KDJB") == 0)
		return true;

	if (strcmp(pstrLicense, "GKDH-FEFH-OHNF-PJGL-KDJB") == 0)
		return true;

	if (strcmp(pstrLicense, "FODI-FEFH-FNPH-LFGZ-BJLD") == 0)
		return true;

	return false;
	*/
	return false;
}

int CLicense::rotate_char(char input_char, int rotate_number)
{
    int val = int(input_char); // for example 84
    int distance = val + rotate_number;
    if (distance < 66)
        return 'P';
    
    if (distance > 85)
        return 'F';
    
    if (val == 77)
        rotate_number = rotate_number - 1;
        
    return char(val + rotate_number);
}

char get_item(char* pstrLicense, int list_index, int char_index)
{
	return pstrLicense[((list_index - 1)* 6) + char_index];
}

bool CLicense::IsLicenseValid(wchar_t *pstrLicenseKey, bool& bEnableNewFeatures)
{
//	return false;
	bEnableNewFeatures = false;

#if defined(COMPILE_AS_REGISTERED)
	return true;
#endif
	
	if (wcslen(pstrLicenseKey) < 35)
		return false;

	USES_CONVERSION;
	char* pstrLicense = W2A(pstrLicenseKey);

	// Let's verify the date
	int month = int(pstrLicense[9]) - 71;
	int year = int(pstrLicense[32]) - 65;
	
	char c = get_item(pstrLicense, 4, 2);
	char c1 = get_item(pstrLicense, 1, 0);

	if (year < 8 && month < 9)
		return false;

	#pragma message ("This project compiled on " __DATE__ ". All licenses generated after 22nd Sept 2008 are valid") 


	// block 1
	if (rotate_char(get_item(pstrLicense, 4, 2), 4) != get_item(pstrLicense, 1, 0))
		return false;

	if (rotate_char(get_item(pstrLicense, 4, 3), 5) != get_item(pstrLicense, 1, 1))
		return false;

	if (rotate_char(get_item(pstrLicense, 6, 4), 7) != get_item(pstrLicense, 1, 3))
		return false;

	// block 2
	if (rotate_char(get_item(pstrLicense, 6, 3), 10) != get_item(pstrLicense, 3, 3))
		return false;

	if (rotate_char(get_item(pstrLicense, 6, 2), 10) != get_item(pstrLicense, 3, 1))
		return false;

	// block 3
	if (rotate_char(get_item(pstrLicense, 3, 3), -7) != get_item(pstrLicense, 3, 4))
		return false;

	if (rotate_char(get_item(pstrLicense, 3, 3), -12) != get_item(pstrLicense, 4, 4))
		return false;

	if (rotate_char(get_item(pstrLicense, 4, 3), -6) == get_item(pstrLicense, 4, 1) &&
		get_item(pstrLicense, 1, 2) == get_item(pstrLicense, 4,1))
		bEnableNewFeatures = true;

	// at this point, we are authenticated. We just need to tell it if the new features
	// are also authenticated

	/*
	    # We make the digits of key 1 dependent on key 4
    key1[0] = rotate_char(key4[2], 4)
    key1[1] = rotate_char(key4[3], 5)
    key1[3] = rotate_char(key4[1], 7)

	/*
	
	char* pstrLicense = W2A(pstrLicenseKey);
	TCHAR szLoc[128] = {0};
	if (strlen(pstrLicense) == 20)
	{
		// Copy the licensekey into szLoc
		szLoc[4] = '-';
		szLoc[9] = '-';
		szLoc[14] = '-';
		szLoc[17] = '-';
		szLoc[19] = '-';
		_tcsncpy_s(szLoc, 128, pstrLicense, 4);
		_tcsncpy_s(&szLoc[5], 128,&pstrLicense[4], 4);
		_tcsncpy_s(&szLoc[10], 128,&pstrLicense[8], 4);
		_tcsncpy_s(&szLoc[15], 128,&pstrLicense[12], 4);
		_tcsncpy_s(&szLoc[20], 128,&pstrLicense[16], 4);

		pstrLicense = szLoc;
	}
	else if (strlen(pstrLicense) < 24)
		return false;

	// else do our real validation

	// Make 5 buffers of 4 chars each plus a closing 0
	char sz1[5] = {0};
	char sz2[5] = {0};
	char sz3[5] = {0};
	char sz4[5] = {0};
	char sz5[5] = {0};

	// copy each 4 chars of the licensekey into those spaces
	_tcsncpy_s(sz1, 5, pstrLicense, 4);
	_tcsncpy_s(sz2, 5, &pstrLicense[5], 4);
	_tcsncpy_s(sz3, 5, &pstrLicense[10], 4);
	_tcsncpy_s(sz4, 5, &pstrLicense[15], 4);
	_tcsncpy_s(sz5, 5, &pstrLicense[20], 4);
	
	// The date is in 
	char szDate[5] = {0};
	szDate[0] = (sz1[0] - 20) - 1;
	szDate[1] = (sz1[1] - 20) - 2;
	szDate[2] = (sz1[2] - 20) - 0;
	szDate[3] = (sz1[3] - 20) - 1;

	int nDateSumme = chrtol(szDate[0]) + chrtol(szDate[1]) + chrtol(szDate[2]) + chrtol(szDate[3]);
	if (sz4[0] != 90 - nDateSumme)
		return false;

	/*
	char szYear[5] = {0};
	szYear[0] = (sz2[0] - 20) - 0;
	szYear[1] = (sz2[1] - 20) - 1;
	szYear[2] = (sz2[2] - 20) - 2;
	szYear[3] = (sz2[3] - 20) - 0;

	int nYearSumme = chrtol(szYear[0]) + chrtol(szYear[1]) + chrtol(szYear[2]) + chrtol(szYear[3]);
	if (sz4[2] != 65 + nYearSumme)
		return false;

	if (sz3[0] != sz5[0] + 4)
		return false;

	if (sz3[1] != sz5[1] + 4)
		return false;

	if (sz3[3] != sz5[3] + 4)
		return false;

	int nYear = (chrtol(szYear[2]) * 10) + chrtol(szYear[3]);
	int nMonth = (chrtol(szDate[2]) * 10) + chrtol(szDate[3]);
	if (nYear == 6 && nMonth == 5)
		return false; // fake license key purchased

	if (nYear <= 6)
	{
		if (nYear < 6)
			return false;

	//	int nMonth = (chrtol(szDate[2]) * 10) + chrtol(szDate[3]);
		if (nMonth < 12)
			return false;
	}
*/

// #pragma message ("This project compiled on " __DATE__ ". License valid from 1st January 2006") 
// #pragma message("The licensekey routines have been disabled")

	return true;
}

bool CLicense::IsShortLicenseValid(wchar_t *pstrLicenseKey)
{
	return false;

#if defined(COMPILE_AS_REGISTERED)
	return true;
#endif

	USES_CONVERSION;

	// An additional license key scheme
	char* pstrLicense = W2A(pstrLicenseKey);

	// char 4 is dependent on char 0
	if (pstrLicense[0] != 65 + ((pstrLicense[4] * 513) % 25))
	{
		return false;
	}

	// char 3 is dependent of char 2
	if (pstrLicense[1] != 65 + ((pstrLicense[2] * pstrLicense[2] * 7) % 25))
	{
		return false;
	}

	// char 7 is dependent on char 3 and char 1
	if (pstrLicense[7] != 65 + ((pstrLicense[1] * pstrLicense[3] * 7) % 25))
	{
		return false;
	}

	// all the others are random

	return true;
}

void CLicense::GenerateShortLicense()
{
	/*
#if defined(DEBUG)

	srand( (unsigned int )timeGetTime( ) );

	char sz[9] = {0};
	
	// (pstrLicense[0] != 65 + ((pstrLicense[4] * 354) % 30))
	sz[4] = GetRandomCapitalLetter();
	sz[0] = 65 + ((sz[4] * 513) % 25);
	sz[2] = GetRandomCapitalLetter();
	sz[1] = 65 + ((sz[2] * sz[2] * 7) % 25);
	sz[3] = GetRandomCapitalLetter();
	sz[7] = 65 + ((sz[1] * sz[3] * 7) % 25);
	sz[5] = GetRandomCapitalLetter();
	sz[6] = GetRandomCapitalLetter();
	sz[8] = '\0';

	_ASSERT(IsShortLicenseValid(CComBSTR(sz)) == true);
	Trace("License Key for MPEG-4: %s\n", sz);
#endif
	*/
}
