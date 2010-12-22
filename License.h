#pragma once

class CLicense;

#include "encodeerdlib.h"

class CLicense
{
public:
	void GenerateShortLicense();
	CLicense(void);
	~CLicense(void);

	char* GenerateLicense();
	bool IsLicenseKeyOld(char *pstrLicense);
	long GetPiDigit(int nDigit);
	char GetRandomCapitalLetter();
	bool IsLicenseValid(wchar_t *pstrLicense, bool& bEnableNewFeatures);
	bool IsShortLicenseValid(wchar_t * pstrLicenseKey);
	int  rotate_char(char input_char, int rotate_number);

private:
	char m_szLibBuffer[1024];
};
