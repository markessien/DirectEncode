#pragma once

#include <stdio.h>
#include <stdlib.h>

class CLicense
{
public:
	CLicense(void);
	~CLicense(void);

	char* GenerateLicense();
	bool IsLicenseKeyOld(char *pstrLicense);
	long GetPiDigit(int nDigit);
	char GetRandomCapitalLetter();
	bool IsLicenseValid(char *pstrLicense, bool& bEnableNewFeatures);
	int rotate_char(char input_char, int rotate_number);

private:
	char m_szLibBuffer[1024];
};
