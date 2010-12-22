
#pragma once

#include <cassert>

// FOR GCC COMPILATION
#define DECLARE_OUTPUT_FORMAT
#define NEW_VERSION
#define _ASSERT(x)

// #include <avformat.h>
#ifndef CONFIG_WIN32
#define CONFIG_WIN32
#endif

#define __STDC_CONSTANT_MACROS
#include <stdint.h>

// ESSIEN
// #define INT64_C(val) val##i64 

#define EPSILON 0.001 
#define FLOAT_EQ(x,v) (((v - EPSILON) < x) && (x <( v + EPSILON)))
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
//#include <Mmreg.h>
#include <mmsystem.h>
// #include <crtdbg.h>
// #include <atlconv.h>

char* WideCharToChar(wchar_t* pstr);

const LONGLONG MILLISECONDS = (1000);            // 10 ^ 3
const LONGLONG NANOSECONDS = (1000000000);       // 10 ^ 9
const LONGLONG UNITS = (NANOSECONDS / 100);      // 10 ^ 7

#if defined (TRACE_VERBOSE)
#define TraceVerbose Trace
#else
#define TraceVerbose
#endif

#if defined(DEBUG)
void Trace(LPCTSTR pStr, ...);
#else
#define Trace
#endif

#include <math.h>
#include <mmsystem.h>
#include "mmreg.h"
#include "msacm.h"

extern "C" {
	#include <avio.h>
	#include <fifo.h>
	#include <avcodec.h>
	#include <avformat.h>
};






//	};