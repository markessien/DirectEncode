// VerySimpleErdMpgSample.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <conio.h>  // for getch
#include <Mmreg.h>  // for WAVEFORMATEX
#include <crtdbg.h> // fr _ASSERT

// Define the helper parameters, so you already
// have variables to load the functions into
#define VARFUNCS
#define DECLARE_OUTPUT_FORMAT
#define DECLARE_FUNC_VARIABLES

// Include the functions declarations
#include "..\erdmpeg\erdmpglib\erdmpglib.h"

int main(int argc, char* argv[])
{
	printf("This sample shows you how to use the erdmpg-6.dll file!\n");

	// Load the dll
	HINSTANCE m_hEncodeDLL = LoadLibrary("Z:\\Development\\erdmpeg\\NewTest\\erdmpg-6.dll");

	// Retrieve some functions from the dll
	mediaFileInitialize = (MediaFileInitialize) GetProcAddress(m_hEncodeDLL, "MediaFileInitialize");
	mediaFileCreate = (MediaFileCreate) GetProcAddress(m_hEncodeDLL, "MediaFileCreate");	
	mediaFileClose = (MediaFileClose) GetProcAddress(m_hEncodeDLL, "MediaFileClose");
	mediaFileWriteVideoRGB24 = (MediaFileWriteVideoRGB24) GetProcAddress(m_hEncodeDLL, "MediaFileWriteVideoRGB24");

	
	mediaFileInitialize();

	printf("Press any key to exit");
	getch();

	return 0;
}

