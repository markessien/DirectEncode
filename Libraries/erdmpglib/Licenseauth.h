#pragma once

typedef void (__cdecl *funcAuthentication)(void);

class CLicenseAuth
{
public:
	CLicenseAuth(void);
	~CLicenseAuth(void);
	void SetAuthenticationFunction(funcAuthentication pAuth);

private:
	
	funcAuthentication m_funcToCall;
	funcAuthentication m_funcAuthenticationFunction;
public:

	char GetRandomCapitalLetter();
	void AnalyseLicense(char* pBuffer);
	void CallAuthenticationFunction(void);
	void TestGenerate();
	long GetPiDigit(int nDigit);

private:
	static void __cdecl DeadEnd();
};
