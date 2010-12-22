// Diagnostics.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <conio.h>
#include <atlbase.h>
extern CComModule _Module;
#include <atlcom.h>
#include <atlctl.h>

// dshow includes
#include <qedit.h>
#include <streams.h>

#include <initguid.h>
#include <StandardMPEGEncoderUIDs.h>

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "modulver.h"

#include <sys/stat.h>
#include <time.h>


#import  <DirectEncode.tlb> no_namespace raw_interfaces_only exclude("UINT_PTR", \
							"_VideoOutputFormat", \
							"_AudioOutputFormat", \
							"_SystemsOutputFormat", \
							"_Constraint", \
							"_EncodeMode", \
							"_AspectRatio", \
							"_BitrateMode") 

HANDLE hLogFile;

void print(char* str)
{
	DWORD dw = 0;
	printf(str);
	WriteFile(hLogFile, str, strlen(str), &dw, 0);
}

void println(char* str)
{
	if (str != NULL)
		print(str);

	print("\r\n");
}


void printhr(HRESULT hr, char* str)
{
	print(str);
	char sz[128];
	sprintf(sz, "   HRESULT: 0x%X", hr);
	println(sz);
}

void printptr(void* ptr)
{
	char sz[128];
	sprintf(sz, "   Ptr: 0x%X", ptr);
	println(sz);
}

void printmemleaks()
{

   _CrtSetReportMode( _CRT_WARN, _CRTDBG_MODE_FILE | _CRTDBG_MODE_DEBUG );
   _CrtSetReportFile(_CRT_WARN, hLogFile);
   _RPT0(_CRT_WARN, "Standard MPEG Encoder Snapshot\r\n");
	_CrtDumpMemoryLeaks();
}

void print_local_info()
{
	char buf[1024];
	GetSystemDirectory(buf, 1024);
	print("System Directory: ");
	println(buf);

	GetWindowsDirectory(buf, 1024);
	print("Windows Directory: ");
	println(buf);
	println(NULL);

}

void print_file_info(char* pstrPath, bool bAppendSys = false)
{
	if (bAppendSys)
	{
		char buf[1024];
		GetSystemDirectory(buf, 1024);
		strcat(buf, "\\");
		strcat(buf, pstrPath);
		pstrPath = buf;
	}

	print("    Read: ");
	print(pstrPath);

	CModuleVersion ver;
	if (ver.GetFileVersionInfo(pstrPath)) {
		WORD major = HIWORD(ver.dwFileVersionMS);
		WORD minor = LOWORD(ver.dwFileVersionMS);

		char sz[128];
		sprintf(sz, "###v%lu.%lu", major, minor);
		print(sz);
	}
	else
		print("### ---");



	struct stat attrib;
	int err = stat(pstrPath, &attrib);
	if (err == 0)
	{
		print("###");

		struct tm* clock;
		clock = gmtime(&(attrib.st_mtime));

		char sz[128];
		sprintf(sz, "d:%lu-%lu-%lu", clock->tm_mday, clock->tm_mon + 1, clock->tm_year - 100);
		println(sz);
	}
	else
		println("   File could not be found");
}

int main(int argc, char* argv[])
{
    hLogFile = CreateFile("standardmpeg_diagnostics.txt", GENERIC_WRITE, 
      FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, 
      FILE_ATTRIBUTE_NORMAL, NULL);

	println("--- Standard Mpeg Encoder 6.0 ---\n");
	println("Welcome to the Standard Mpeg Encoder diagnostics tool.");
	println("This tool will run a series of tests to find out if your");
	println("environment is correctly setup to run the Mpeg Encoder\n");

	print_local_info();

	println("Test 1: Can the DirectEncode.dll file be instanciated?");

	CoInitialize(0);

	CComPtr<IBaseFilter> pMPEGWriter;
	HRESULT hr = CoCreateInstance(CLSID_StandardMpegEncoder, NULL, 
								  CLSCTX_INPROC_SERVER, 
								  IID_IBaseFilter, 
								  (void **)&pMPEGWriter);
	
	if (FAILED(hr))
	{
		printhr(hr, "   FAILED: The Mpeg Object could not be created");
		printptr(pMPEGWriter.p);
	}
	else
	{
		printhr(hr, "   SUCCEEDED: The Mpeg Object was created successfully");
		printptr(pMPEGWriter.p);
	}

	println("Test 2: Attempting to load util");
	HMODULE h = LoadLibrary("avutilerd-49.dll");
	if (h != NULL)
	{
		print("   SUCCESS: Loaded util dll -- ");
		printptr(h);
		
		print("    Path: ");
		char* pszDllPath = new char[_MAX_PATH];
		GetModuleFileName(h, pszDllPath, _MAX_PATH);
		println(pszDllPath);
		print_file_info(pszDllPath);
		delete [] pszDllPath;
	}
	else
	{
		println("    FAILED. HModule = NULL");
		print_file_info("avutilerd-49.dll", true);
	}
	FreeLibrary(h);

	println("Test 3: Attempting to load aac");
	h = LoadLibrary("libfaac.dll");
	if (h != NULL)
	{
		print("   SUCCESS: Loaded aac dll -- ");
		printptr(h);
		
		print("    Path: ");
		char* pszDllPath = new char[_MAX_PATH];
		GetModuleFileName(h, pszDllPath, _MAX_PATH);
		println(pszDllPath);
		print_file_info(pszDllPath);
		delete [] pszDllPath;
	}
	else
	{
		println("    FAILED. HModule = NULL");
		print_file_info("libfaac.dll", true);
	}
	FreeLibrary(h);

	println("Test 4: Attempting to load format");
	h = LoadLibrary("avformaterd-52.dll");
	if (h != NULL)
	{
		print("   SUCCESS: Loaded format dll -- ");
		printptr(h);
		
		print("    Path: ");
		char* pszDllPath = new char[_MAX_PATH];
		GetModuleFileName(h, pszDllPath, _MAX_PATH);
		println(pszDllPath);
		print_file_info(pszDllPath);
		delete [] pszDllPath;
	}
	else
	{
		println("    FAILED. HModule = NULL");
		print_file_info("avformaterd-52.dll", true);
	}
	FreeLibrary(h);

	println("Test 5: Attempting to load codec");
	h = LoadLibrary("avcodecerd-51.dll");
	if (h != NULL)
	{
		print("   SUCCESS: Loaded codec dll -- ");
		printptr(h);
		
		print("    Path: ");
		char* pszDllPath = new char[_MAX_PATH];
		GetModuleFileName(h, pszDllPath, _MAX_PATH);
		println(pszDllPath);
		print_file_info(pszDllPath);
		delete [] pszDllPath;
	}
	else
	{
		println("    FAILED. HModule = NULL");
		print_file_info("avcodecerd-51.dll", true);
	}

	FreeLibrary(h);

	println("Test 6: Attempting to load erdmpg");
	h = LoadLibrary("erdmpg-6.dll");
	if (h != NULL)
	{
		print("   SUCCESS: Loaded erdmpg dll -- ");
		printptr(h);
		
		print("    Path: ");
		char* pszDllPath = new char[_MAX_PATH];
		GetModuleFileName(h, pszDllPath, _MAX_PATH);
		println(pszDllPath);

		print_file_info(pszDllPath);
		delete [] pszDllPath;
	}
	else
	{
		println("    FAILED. HModule = NULL");
		print_file_info("erdmpg-6.dll", true);
	}

	FreeLibrary(h);

	pMPEGWriter = NULL;
	println("Examining for memory leaks...");
	printmemleaks();
	println("    Done: Look in the log file");

	CloseHandle(hLogFile);

	println("Press any key to exit\n");
	_getch();

	return 0;
}

