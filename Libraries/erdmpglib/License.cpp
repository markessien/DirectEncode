#include "StdAfx.h"
#include "license.h"
#include <time.h>
#undef lstrcpyW
#include <tchar.h>

#define chrtol(x) (x - 48)

#define d 4
#define nmax 501
#define mmax ((int)(3322L*nmax*d/1000))
#define r2 10000 

CLicense::CLicense(void)
{
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

	_tcscpy(m_szLibBuffer, sz);

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


bool CLicense::IsLicenseValid(char *pstrLicenseKey, bool& bEnableNewFeatures)
{
	bEnableNewFeatures = false;

	if (strlen(pstrLicenseKey) < 35)
		return false;

	char* pstrLicense = pstrLicenseKey;

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


	return true;
}
