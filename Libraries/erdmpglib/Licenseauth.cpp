#include "StdAfx.h"
#include "licenseauth.h"
// #include <math.h>
#include <Mmsystem.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define d 4
#define nmax 501
#define mmax ((int)(3322L*nmax*d/1000))
#define r2 10000 

CLicenseAuth::CLicenseAuth(void) : m_funcToCall(NULL)
{
	m_funcToCall = &(CLicenseAuth::DeadEnd);
}

CLicenseAuth::~CLicenseAuth(void)
{
}

void CLicenseAuth::DeadEnd()
{
	int gm = 423;
	int gd=gm;
	int xc = 54,yc = 211,r = 45,x = 7564,y = 2123;
	int i = 332,rx = 4545,ry = 55;
	i = i/34;
	for(i=0;i<=360;i++)
	{
		x=xc+(rx*(int)cos((double)i));
		y=yc+(ry*(int)sin((double)i));
	}

	for(i=0;i<=360;i++)
	{
//		TestGenerate();

		x=xc+(rx*(int)cos((double)i));
		y=yc+(ry*(int)sin((double)i));
	}

	for (i=0;i<1000;i++)
	{
		// GetRandomCapitalLetter();
	}
}

void CLicenseAuth::TestGenerate()
{

#if 0
	char sz[1024] = {0};
	
	char* pstr = sz;

	srand( (unsigned int )timeGetTime( ) );

	// get the number of hours system has been on
	long nHourNow = timeGetTime() / (1000 * 60 * 60);

	int u = 0;
	int j = 50;
	int k = 10;
	// first we get 4 random capital letters
	while (pstr)
	{
		for (int i=0;i<4;i++)
		{
			pstr[i] = GetRandomCapitalLetter();
		}

		// now, we use pi combined with the current time
		// to match the license key values
		for (int i=4;i<8;i++)
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

#endif
}

void CLicenseAuth::SetAuthenticationFunction(funcAuthentication pAuth)
{
	m_funcAuthenticationFunction = pAuth;
}

char CLicenseAuth::GetRandomCapitalLetter()
{
	// chrtol for char to long
	// capitals are 65 - 90
	int n = rand() % 25;
	char c = 65 + n;
	return c;
}

long CLicenseAuth::GetPiDigit(int nDigit)
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

void CLicenseAuth::AnalyseLicense(char* pBuffer)
{
	if (pBuffer)
	{
		// pBuffer is a character string
		// AAAA-FFFF-AAAA-GGGG
		char* pstr1 = (char*)pBuffer;
		char* pstr2 = pBuffer + 4;
		char* pstr3 = pBuffer + 8;
		char* pstr4 = pBuffer + 12;

		long nowtime = timeGetTime();

		int i = 0;
		bool bAnyWrong = false;
		// the relationship is pi based with time
		for (int k=0;k<2;k++)
		{
			long nHourNow = nowtime;
			nHourNow = nHourNow / (1000 * 60 * 60);
			if (k) nHourNow = nHourNow - 1;

			// check first four letter
			for (i=0;i<4;i++)
			{
				char c1 = pstr2[i];
				char cT = pstr1[3-i];
				long nPiVal = GetPiDigit(nHourNow + 50);
				nPiVal = nPiVal * 2; // max of 9 * 9 = 81;
				nPiVal += GetPiDigit(nHourNow + 10); // add a single digit
				
				if (cT + nPiVal != (long)c1)
				{
					bAnyWrong = true;
				}
			}

			// check 2nd four letters
			for (i=0;i<4;i++)
			{
				char c1 = pstr4[i];
				char cT = pstr3[3-i];
				long nPiVal = GetPiDigit(nHourNow + 57);
				nPiVal = nPiVal * 2; // max of 9 * 9 = 81;
				nPiVal += GetPiDigit(nHourNow + 9); // add a single digit
				
				if (cT + nPiVal != (long)c1)
				{
					bAnyWrong = true;
				}
			}

			if (bAnyWrong && k == 1)
				m_funcToCall = DeadEnd;

			if (bAnyWrong == false) {
				m_funcToCall = m_funcAuthenticationFunction;
				break;
			}

			bAnyWrong = false;
		}
	}
}

void CLicenseAuth::CallAuthenticationFunction()
{
	if (m_funcToCall)
		(*m_funcToCall)();
}
