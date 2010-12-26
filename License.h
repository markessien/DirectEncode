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
