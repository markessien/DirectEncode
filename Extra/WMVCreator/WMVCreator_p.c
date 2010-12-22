
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the proxy stub code */


 /* File created by MIDL compiler version 6.00.0347 */
/* at Sun Oct 30 16:02:09 2005
 */
/* Compiler settings for WMVCreator.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#if !defined(_M_IA64) && !defined(_M_AMD64)
#define USE_STUBLESS_PROXY


/* verify that the <rpcproxy.h> version is high enough to compile this file*/
#ifndef __REDQ_RPCPROXY_H_VERSION__
#define __REQUIRED_RPCPROXY_H_VERSION__ 440
#endif


#include "rpcproxy.h"
#ifndef __RPCPROXY_H_VERSION__
#error this stub requires an updated version of <rpcproxy.h>
#endif // __RPCPROXY_H_VERSION__


#include "WMVCreator.h"

#define TYPE_FORMAT_STRING_SIZE   111                               
#define PROC_FORMAT_STRING_SIZE   2115                              
#define TRANSMIT_AS_TABLE_SIZE    0            
#define WIRE_MARSHAL_TABLE_SIZE   1            

typedef struct _MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } MIDL_TYPE_FORMAT_STRING;

typedef struct _MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } MIDL_PROC_FORMAT_STRING;


static RPC_SYNTAX_IDENTIFIER  _RpcTransferSyntax = 
{{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}};


extern const MIDL_TYPE_FORMAT_STRING __MIDL_TypeFormatString;
extern const MIDL_PROC_FORMAT_STRING __MIDL_ProcFormatString;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IWMVCodec_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IWMVCodec_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IWMVProfile_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IWMVProfile_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IWMVCreatorObj_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IWMVCreatorObj_ProxyInfo;


extern const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[ WIRE_MARSHAL_TABLE_SIZE ];

#if !defined(__RPC_WIN32__)
#error  Invalid build platform for this stub.
#endif

#if !(TARGET_IS_NT40_OR_LATER)
#error You need a Windows NT 4.0 or later to run this stub because it uses these features:
#error   -Oif or -Oicf, [wire_marshal] or [user_marshal] attribute, float, double or hyper in -Oif or -Oicf, more than 32 methods in the interface.
#error However, your C/C++ compilation flags indicate you intend to run this app on earlier systems.
#error This app will die there with the RPC_X_WRONG_STUB_VERSION error.
#endif


static const MIDL_PROC_FORMAT_STRING __MIDL_ProcFormatString =
    {
        0,
        {

	/* Procedure get_ProfileName */


	/* Procedure get_CodecName */

			0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/*  2 */	NdrFcLong( 0x0 ),	/* 0 */
/*  6 */	NdrFcShort( 0x7 ),	/* 7 */
/*  8 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 10 */	NdrFcShort( 0x0 ),	/* 0 */
/* 12 */	NdrFcShort( 0x8 ),	/* 8 */
/* 14 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x2,		/* 2 */

	/* Parameter pVal */


	/* Parameter pVal */

/* 16 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 18 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 20 */	NdrFcShort( 0x1e ),	/* Type Offset=30 */

	/* Return value */


	/* Return value */

/* 22 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 24 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 26 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_ProfileName */


	/* Procedure put_CodecName */

/* 28 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 30 */	NdrFcLong( 0x0 ),	/* 0 */
/* 34 */	NdrFcShort( 0x8 ),	/* 8 */
/* 36 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 38 */	NdrFcShort( 0x0 ),	/* 0 */
/* 40 */	NdrFcShort( 0x8 ),	/* 8 */
/* 42 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x2,		/* 2 */

	/* Parameter newVal */


	/* Parameter newVal */

/* 44 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 46 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 48 */	NdrFcShort( 0x2c ),	/* Type Offset=44 */

	/* Return value */


	/* Return value */

/* 50 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 52 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 54 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_ProfileDescription */


	/* Procedure get_CodecDescription */

/* 56 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 58 */	NdrFcLong( 0x0 ),	/* 0 */
/* 62 */	NdrFcShort( 0x9 ),	/* 9 */
/* 64 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 66 */	NdrFcShort( 0x0 ),	/* 0 */
/* 68 */	NdrFcShort( 0x8 ),	/* 8 */
/* 70 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x2,		/* 2 */

	/* Parameter pVal */


	/* Parameter pVal */

/* 72 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 74 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 76 */	NdrFcShort( 0x1e ),	/* Type Offset=30 */

	/* Return value */


	/* Return value */

/* 78 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 80 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 82 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_ProfileDescription */


	/* Procedure put_CodecDescription */

/* 84 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 86 */	NdrFcLong( 0x0 ),	/* 0 */
/* 90 */	NdrFcShort( 0xa ),	/* 10 */
/* 92 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 94 */	NdrFcShort( 0x0 ),	/* 0 */
/* 96 */	NdrFcShort( 0x8 ),	/* 8 */
/* 98 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x2,		/* 2 */

	/* Parameter newVal */


	/* Parameter newVal */

/* 100 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 102 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 104 */	NdrFcShort( 0x2c ),	/* Type Offset=44 */

	/* Return value */


	/* Return value */

/* 106 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 108 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 110 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_MajorType */

/* 112 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 114 */	NdrFcLong( 0x0 ),	/* 0 */
/* 118 */	NdrFcShort( 0xb ),	/* 11 */
/* 120 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 122 */	NdrFcShort( 0x0 ),	/* 0 */
/* 124 */	NdrFcShort( 0x24 ),	/* 36 */
/* 126 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 128 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 130 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 132 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 134 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 136 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 138 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_MaxPasses */

/* 140 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 142 */	NdrFcLong( 0x0 ),	/* 0 */
/* 146 */	NdrFcShort( 0xc ),	/* 12 */
/* 148 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 150 */	NdrFcShort( 0x0 ),	/* 0 */
/* 152 */	NdrFcShort( 0x24 ),	/* 36 */
/* 154 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 156 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 158 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 160 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 162 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 164 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 166 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_SystemProfileCount */


	/* Procedure get_Passes */

/* 168 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 170 */	NdrFcLong( 0x0 ),	/* 0 */
/* 174 */	NdrFcShort( 0xd ),	/* 13 */
/* 176 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 178 */	NdrFcShort( 0x0 ),	/* 0 */
/* 180 */	NdrFcShort( 0x24 ),	/* 36 */
/* 182 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */


	/* Parameter pVal */

/* 184 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 186 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 188 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */


	/* Return value */

/* 190 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 192 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 194 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_Passes */

/* 196 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 198 */	NdrFcLong( 0x0 ),	/* 0 */
/* 202 */	NdrFcShort( 0xe ),	/* 14 */
/* 204 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 206 */	NdrFcShort( 0x8 ),	/* 8 */
/* 208 */	NdrFcShort( 0x8 ),	/* 8 */
/* 210 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter newVal */

/* 212 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 214 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 216 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 218 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 220 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 222 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Bitrate */


	/* Procedure get_Quality */

/* 224 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 226 */	NdrFcLong( 0x0 ),	/* 0 */
/* 230 */	NdrFcShort( 0xf ),	/* 15 */
/* 232 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 234 */	NdrFcShort( 0x0 ),	/* 0 */
/* 236 */	NdrFcShort( 0x24 ),	/* 36 */
/* 238 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */


	/* Parameter pVal */

/* 240 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 242 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 244 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */


	/* Return value */

/* 246 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 248 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 250 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_Bitrate */


	/* Procedure put_Quality */

/* 252 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 254 */	NdrFcLong( 0x0 ),	/* 0 */
/* 258 */	NdrFcShort( 0x10 ),	/* 16 */
/* 260 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 262 */	NdrFcShort( 0x8 ),	/* 8 */
/* 264 */	NdrFcShort( 0x8 ),	/* 8 */
/* 266 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter newVal */


	/* Parameter newVal */

/* 268 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 270 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 272 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */


	/* Return value */

/* 274 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 276 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 278 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Bitrate */

/* 280 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 282 */	NdrFcLong( 0x0 ),	/* 0 */
/* 286 */	NdrFcShort( 0x11 ),	/* 17 */
/* 288 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 290 */	NdrFcShort( 0x0 ),	/* 0 */
/* 292 */	NdrFcShort( 0x24 ),	/* 36 */
/* 294 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 296 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 298 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 300 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 302 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 304 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 306 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_Bitrate */

/* 308 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 310 */	NdrFcLong( 0x0 ),	/* 0 */
/* 314 */	NdrFcShort( 0x12 ),	/* 18 */
/* 316 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 318 */	NdrFcShort( 0x8 ),	/* 8 */
/* 320 */	NdrFcShort( 0x8 ),	/* 8 */
/* 322 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter newVal */

/* 324 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 326 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 328 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 330 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 332 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 334 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_VideoWidth */


	/* Procedure get_VBRMode */

/* 336 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 338 */	NdrFcLong( 0x0 ),	/* 0 */
/* 342 */	NdrFcShort( 0x13 ),	/* 19 */
/* 344 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 346 */	NdrFcShort( 0x0 ),	/* 0 */
/* 348 */	NdrFcShort( 0x24 ),	/* 36 */
/* 350 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */


	/* Parameter pVal */

/* 352 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 354 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 356 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */


	/* Return value */

/* 358 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 360 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 362 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_VideoWidth */


	/* Procedure put_VBRMode */

/* 364 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 366 */	NdrFcLong( 0x0 ),	/* 0 */
/* 370 */	NdrFcShort( 0x14 ),	/* 20 */
/* 372 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 374 */	NdrFcShort( 0x8 ),	/* 8 */
/* 376 */	NdrFcShort( 0x8 ),	/* 8 */
/* 378 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter newVal */


	/* Parameter newVal */

/* 380 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 382 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 384 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */


	/* Return value */

/* 386 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 388 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 390 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_VideoHeight */


	/* Procedure get_KeyframeFrequency */

/* 392 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 394 */	NdrFcLong( 0x0 ),	/* 0 */
/* 398 */	NdrFcShort( 0x15 ),	/* 21 */
/* 400 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 402 */	NdrFcShort( 0x0 ),	/* 0 */
/* 404 */	NdrFcShort( 0x24 ),	/* 36 */
/* 406 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */


	/* Parameter pVal */

/* 408 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 410 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 412 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */


	/* Return value */

/* 414 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 416 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 418 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_VideoHeight */


	/* Procedure put_KeyframeFrequency */

/* 420 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 422 */	NdrFcLong( 0x0 ),	/* 0 */
/* 426 */	NdrFcShort( 0x16 ),	/* 22 */
/* 428 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 430 */	NdrFcShort( 0x8 ),	/* 8 */
/* 432 */	NdrFcShort( 0x8 ),	/* 8 */
/* 434 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter newVal */


	/* Parameter newVal */

/* 436 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 438 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 440 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */


	/* Return value */

/* 442 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 444 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 446 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Framerate */

/* 448 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 450 */	NdrFcLong( 0x0 ),	/* 0 */
/* 454 */	NdrFcShort( 0x17 ),	/* 23 */
/* 456 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 458 */	NdrFcShort( 0x0 ),	/* 0 */
/* 460 */	NdrFcShort( 0x2c ),	/* 44 */
/* 462 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 464 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 466 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 468 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 470 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 472 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 474 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_Framerate */

/* 476 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 478 */	NdrFcLong( 0x0 ),	/* 0 */
/* 482 */	NdrFcShort( 0x18 ),	/* 24 */
/* 484 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 486 */	NdrFcShort( 0x10 ),	/* 16 */
/* 488 */	NdrFcShort( 0x8 ),	/* 8 */
/* 490 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter newVal */

/* 492 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 494 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 496 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 498 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 500 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 502 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Complexity */

/* 504 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 506 */	NdrFcLong( 0x0 ),	/* 0 */
/* 510 */	NdrFcShort( 0x19 ),	/* 25 */
/* 512 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 514 */	NdrFcShort( 0x0 ),	/* 0 */
/* 516 */	NdrFcShort( 0x24 ),	/* 36 */
/* 518 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 520 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 522 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 524 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 526 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 528 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 530 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_Complexity */

/* 532 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 534 */	NdrFcLong( 0x0 ),	/* 0 */
/* 538 */	NdrFcShort( 0x1a ),	/* 26 */
/* 540 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 542 */	NdrFcShort( 0x8 ),	/* 8 */
/* 544 */	NdrFcShort( 0x8 ),	/* 8 */
/* 546 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter newVal */

/* 548 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 550 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 552 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 554 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 556 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 558 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_KeyFrameSpacing */


	/* Procedure get_FormatIndex */

/* 560 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 562 */	NdrFcLong( 0x0 ),	/* 0 */
/* 566 */	NdrFcShort( 0x1b ),	/* 27 */
/* 568 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 570 */	NdrFcShort( 0x0 ),	/* 0 */
/* 572 */	NdrFcShort( 0x24 ),	/* 36 */
/* 574 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */


	/* Parameter pVal */

/* 576 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 578 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 580 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */


	/* Return value */

/* 582 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 584 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 586 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_KeyFrameSpacing */


	/* Procedure put_FormatIndex */

/* 588 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 590 */	NdrFcLong( 0x0 ),	/* 0 */
/* 594 */	NdrFcShort( 0x1c ),	/* 28 */
/* 596 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 598 */	NdrFcShort( 0x8 ),	/* 8 */
/* 600 */	NdrFcShort( 0x8 ),	/* 8 */
/* 602 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter newVal */


	/* Parameter newVal */

/* 604 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 606 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 608 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */


	/* Return value */

/* 610 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 612 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 614 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_CodecGuid */

/* 616 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 618 */	NdrFcLong( 0x0 ),	/* 0 */
/* 622 */	NdrFcShort( 0x1d ),	/* 29 */
/* 624 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 626 */	NdrFcShort( 0x0 ),	/* 0 */
/* 628 */	NdrFcShort( 0x8 ),	/* 8 */
/* 630 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 632 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 634 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 636 */	NdrFcShort( 0x1e ),	/* Type Offset=30 */

	/* Return value */

/* 638 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 640 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 642 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_ComplexityMax */

/* 644 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 646 */	NdrFcLong( 0x0 ),	/* 0 */
/* 650 */	NdrFcShort( 0x1e ),	/* 30 */
/* 652 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 654 */	NdrFcShort( 0x0 ),	/* 0 */
/* 656 */	NdrFcShort( 0x24 ),	/* 36 */
/* 658 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 660 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 662 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 664 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 666 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 668 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 670 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Quality */


	/* Procedure get_ComplexityOffline */

/* 672 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 674 */	NdrFcLong( 0x0 ),	/* 0 */
/* 678 */	NdrFcShort( 0x1f ),	/* 31 */
/* 680 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 682 */	NdrFcShort( 0x0 ),	/* 0 */
/* 684 */	NdrFcShort( 0x24 ),	/* 36 */
/* 686 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */


	/* Parameter pVal */

/* 688 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 690 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 692 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */


	/* Return value */

/* 694 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 696 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 698 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_ComplexityLive */

/* 700 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 702 */	NdrFcLong( 0x0 ),	/* 0 */
/* 706 */	NdrFcShort( 0x20 ),	/* 32 */
/* 708 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 710 */	NdrFcShort( 0x0 ),	/* 0 */
/* 712 */	NdrFcShort( 0x24 ),	/* 36 */
/* 714 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 716 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 718 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 720 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 722 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 724 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 726 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_IsVBRSupported */

/* 728 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 730 */	NdrFcLong( 0x0 ),	/* 0 */
/* 734 */	NdrFcShort( 0x21 ),	/* 33 */
/* 736 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 738 */	NdrFcShort( 0x0 ),	/* 0 */
/* 740 */	NdrFcShort( 0x22 ),	/* 34 */
/* 742 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 744 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 746 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 748 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 750 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 752 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 754 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure SupportedVBRModes */

/* 756 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 758 */	NdrFcLong( 0x0 ),	/* 0 */
/* 762 */	NdrFcShort( 0x22 ),	/* 34 */
/* 764 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 766 */	NdrFcShort( 0x0 ),	/* 0 */
/* 768 */	NdrFcShort( 0x8c ),	/* 140 */
/* 770 */	0x4,		/* Oi2 Flags:  has return, */
			0x6,		/* 6 */

	/* Parameter CBR1Pass */

/* 772 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 774 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 776 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter CBR2Pass */

/* 778 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 780 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 782 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter VBR1Pass */

/* 784 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 786 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 788 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter VBR2Pass */

/* 790 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 792 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 794 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Parameter ConstrainValue */

/* 796 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 798 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 800 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 802 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 804 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 806 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_AudioBitrate */


	/* Procedure get_FormatCount */

/* 808 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 810 */	NdrFcLong( 0x0 ),	/* 0 */
/* 814 */	NdrFcShort( 0x23 ),	/* 35 */
/* 816 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 818 */	NdrFcShort( 0x0 ),	/* 0 */
/* 820 */	NdrFcShort( 0x24 ),	/* 36 */
/* 822 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */


	/* Parameter pVal */

/* 824 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 826 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 828 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */


	/* Return value */

/* 830 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 832 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 834 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure LoadCodecFormats */

/* 836 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 838 */	NdrFcLong( 0x0 ),	/* 0 */
/* 842 */	NdrFcShort( 0x24 ),	/* 36 */
/* 844 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 846 */	NdrFcShort( 0x0 ),	/* 0 */
/* 848 */	NdrFcShort( 0x8 ),	/* 8 */
/* 850 */	0x4,		/* Oi2 Flags:  has return, */
			0x1,		/* 1 */

	/* Return value */

/* 852 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 854 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 856 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_FormatName */

/* 858 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 860 */	NdrFcLong( 0x0 ),	/* 0 */
/* 864 */	NdrFcShort( 0x25 ),	/* 37 */
/* 866 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 868 */	NdrFcShort( 0x8 ),	/* 8 */
/* 870 */	NdrFcShort( 0x8 ),	/* 8 */
/* 872 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x3,		/* 3 */

	/* Parameter Index */

/* 874 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 876 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 878 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pVal */

/* 880 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 882 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 884 */	NdrFcShort( 0x1e ),	/* Type Offset=30 */

	/* Return value */

/* 886 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 888 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 890 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_CodecIndex */

/* 892 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 894 */	NdrFcLong( 0x0 ),	/* 0 */
/* 898 */	NdrFcShort( 0x26 ),	/* 38 */
/* 900 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 902 */	NdrFcShort( 0x0 ),	/* 0 */
/* 904 */	NdrFcShort( 0x24 ),	/* 36 */
/* 906 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 908 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 910 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 912 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 914 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 916 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 918 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_HasVideoStream */

/* 920 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 922 */	NdrFcLong( 0x0 ),	/* 0 */
/* 926 */	NdrFcShort( 0xb ),	/* 11 */
/* 928 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 930 */	NdrFcShort( 0x0 ),	/* 0 */
/* 932 */	NdrFcShort( 0x22 ),	/* 34 */
/* 934 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 936 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 938 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 940 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 942 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 944 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 946 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_HasVideoStream */

/* 948 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 950 */	NdrFcLong( 0x0 ),	/* 0 */
/* 954 */	NdrFcShort( 0xc ),	/* 12 */
/* 956 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 958 */	NdrFcShort( 0x6 ),	/* 6 */
/* 960 */	NdrFcShort( 0x8 ),	/* 8 */
/* 962 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter newVal */

/* 964 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 966 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 968 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 970 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 972 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 974 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_HasAudioStream */

/* 976 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 978 */	NdrFcLong( 0x0 ),	/* 0 */
/* 982 */	NdrFcShort( 0xd ),	/* 13 */
/* 984 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 986 */	NdrFcShort( 0x0 ),	/* 0 */
/* 988 */	NdrFcShort( 0x22 ),	/* 34 */
/* 990 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 992 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 994 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 996 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 998 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1000 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1002 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_HasAudioStream */

/* 1004 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1006 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1010 */	NdrFcShort( 0xe ),	/* 14 */
/* 1012 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1014 */	NdrFcShort( 0x6 ),	/* 6 */
/* 1016 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1018 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter newVal */

/* 1020 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1022 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1024 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 1026 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1028 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1030 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_StringEquivalent */

/* 1032 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1034 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1038 */	NdrFcShort( 0x11 ),	/* 17 */
/* 1040 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1042 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1044 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1046 */	0x7,		/* Oi2 Flags:  srv must size, clt must size, has return, */
			0x3,		/* 3 */

	/* Parameter Param */

/* 1048 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1050 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1052 */	NdrFcShort( 0x2c ),	/* Type Offset=44 */

	/* Parameter pVal */

/* 1054 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 1056 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1058 */	NdrFcShort( 0x1e ),	/* Type Offset=30 */

	/* Return value */

/* 1060 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1062 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1064 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_StringEquivalent */

/* 1066 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1068 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1072 */	NdrFcShort( 0x12 ),	/* 18 */
/* 1074 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1076 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1078 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1080 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x3,		/* 3 */

	/* Parameter Param */

/* 1082 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1084 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1086 */	NdrFcShort( 0x2c ),	/* Type Offset=44 */

	/* Parameter newVal */

/* 1088 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1090 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1092 */	NdrFcShort( 0x2c ),	/* Type Offset=44 */

	/* Return value */

/* 1094 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1096 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1098 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_VideoCodec */

/* 1100 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1102 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1106 */	NdrFcShort( 0x17 ),	/* 23 */
/* 1108 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1110 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1112 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1114 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 1116 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 1118 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1120 */	NdrFcShort( 0x42 ),	/* Type Offset=66 */

	/* Return value */

/* 1122 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1124 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1126 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_VideoCodec */

/* 1128 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1130 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1134 */	NdrFcShort( 0x18 ),	/* 24 */
/* 1136 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1138 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1140 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1142 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x2,		/* 2 */

	/* Parameter newVal */

/* 1144 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 1146 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1148 */	NdrFcShort( 0x46 ),	/* Type Offset=70 */

	/* Return value */

/* 1150 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1152 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1154 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_AudioCodec */

/* 1156 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1158 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1162 */	NdrFcShort( 0x19 ),	/* 25 */
/* 1164 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1166 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1168 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1170 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 1172 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 1174 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1176 */	NdrFcShort( 0x42 ),	/* Type Offset=66 */

	/* Return value */

/* 1178 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1180 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1182 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_AudioCodec */

/* 1184 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1186 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1190 */	NdrFcShort( 0x1a ),	/* 26 */
/* 1192 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1194 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1196 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1198 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x2,		/* 2 */

	/* Parameter newVal */

/* 1200 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 1202 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1204 */	NdrFcShort( 0x46 ),	/* Type Offset=70 */

	/* Return value */

/* 1206 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1208 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1210 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Framerate */

/* 1212 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1214 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1218 */	NdrFcShort( 0x1d ),	/* 29 */
/* 1220 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1222 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1224 */	NdrFcShort( 0x2c ),	/* 44 */
/* 1226 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 1228 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1230 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1232 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 1234 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1236 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1238 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_Framerate */

/* 1240 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1242 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1246 */	NdrFcShort( 0x1e ),	/* 30 */
/* 1248 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1250 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1252 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1254 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter newVal */

/* 1256 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1258 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1260 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 1262 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1264 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1266 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_Quality */

/* 1268 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1270 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1274 */	NdrFcShort( 0x20 ),	/* 32 */
/* 1276 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1278 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1280 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1282 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter newVal */

/* 1284 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1286 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1288 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1290 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1292 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1294 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_VideoBitrate */

/* 1296 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1298 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1302 */	NdrFcShort( 0x21 ),	/* 33 */
/* 1304 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1306 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1308 */	NdrFcShort( 0x24 ),	/* 36 */
/* 1310 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 1312 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1314 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1316 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1318 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1320 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1322 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_VideoBitrate */

/* 1324 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1326 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1330 */	NdrFcShort( 0x22 ),	/* 34 */
/* 1332 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1334 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1336 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1338 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter newVal */

/* 1340 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1342 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1344 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1346 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1348 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1350 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_AudioBitrate */

/* 1352 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1354 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1358 */	NdrFcShort( 0x24 ),	/* 36 */
/* 1360 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1362 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1364 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1366 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter newVal */

/* 1368 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1370 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1372 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1374 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1376 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1378 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure CopyProfile */

/* 1380 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1382 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1386 */	NdrFcShort( 0x25 ),	/* 37 */
/* 1388 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1390 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1392 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1394 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x2,		/* 2 */

	/* Parameter ProfileToCopy */

/* 1396 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 1398 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1400 */	NdrFcShort( 0x58 ),	/* Type Offset=88 */

	/* Return value */

/* 1402 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1404 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1406 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Seekable */

/* 1408 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1410 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1414 */	NdrFcShort( 0x26 ),	/* 38 */
/* 1416 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1418 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1420 */	NdrFcShort( 0x22 ),	/* 34 */
/* 1422 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 1424 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1426 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1428 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 1430 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1432 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1434 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_Seekable */

/* 1436 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1438 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1442 */	NdrFcShort( 0x27 ),	/* 39 */
/* 1444 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1446 */	NdrFcShort( 0x6 ),	/* 6 */
/* 1448 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1450 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter newVal */

/* 1452 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1454 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1456 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 1458 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1460 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1462 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure StartConversion */

/* 1464 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1466 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1470 */	NdrFcShort( 0x7 ),	/* 7 */
/* 1472 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1474 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1476 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1478 */	0x4,		/* Oi2 Flags:  has return, */
			0x1,		/* 1 */

	/* Return value */

/* 1480 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1482 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1484 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure StopConversion */

/* 1486 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1488 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1492 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1494 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1496 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1498 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1500 */	0x4,		/* Oi2 Flags:  has return, */
			0x1,		/* 1 */

	/* Return value */

/* 1502 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1504 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1506 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Duration */

/* 1508 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1510 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1514 */	NdrFcShort( 0x9 ),	/* 9 */
/* 1516 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1518 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1520 */	NdrFcShort( 0x2c ),	/* 44 */
/* 1522 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 1524 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1526 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1528 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 1530 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1532 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1534 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Progress */

/* 1536 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1538 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1542 */	NdrFcShort( 0xa ),	/* 10 */
/* 1544 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1546 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1548 */	NdrFcShort( 0x2c ),	/* 44 */
/* 1550 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 1552 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1554 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1556 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 1558 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1560 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1562 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_Progress */

/* 1564 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1566 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1570 */	NdrFcShort( 0xb ),	/* 11 */
/* 1572 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1574 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1576 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1578 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter newVal */

/* 1580 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1582 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1584 */	0xc,		/* FC_DOUBLE */
			0x0,		/* 0 */

	/* Return value */

/* 1586 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1588 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1590 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure LoadSystemProfiles */

/* 1592 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1594 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1598 */	NdrFcShort( 0xc ),	/* 12 */
/* 1600 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1602 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1604 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1606 */	0x4,		/* Oi2 Flags:  has return, */
			0x1,		/* 1 */

	/* Return value */

/* 1608 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1610 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1612 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_SystemProfile */

/* 1614 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1616 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1620 */	NdrFcShort( 0xe ),	/* 14 */
/* 1622 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1624 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1626 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1628 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x3,		/* 3 */

	/* Parameter Index */

/* 1630 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1632 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1634 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pVal */

/* 1636 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 1638 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1640 */	NdrFcShort( 0x6a ),	/* Type Offset=106 */

	/* Return value */

/* 1642 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1644 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1646 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure LoadSystemCodecs */

/* 1648 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1650 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1654 */	NdrFcShort( 0xf ),	/* 15 */
/* 1656 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1658 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1660 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1662 */	0x4,		/* Oi2 Flags:  has return, */
			0x1,		/* 1 */

	/* Return value */

/* 1664 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1666 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1668 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_VideoCodecCount */

/* 1670 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1672 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1676 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1678 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1680 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1682 */	NdrFcShort( 0x24 ),	/* 36 */
/* 1684 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 1686 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1688 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1690 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1692 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1694 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1696 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_VideoCodec */

/* 1698 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1700 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1704 */	NdrFcShort( 0x11 ),	/* 17 */
/* 1706 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1708 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1710 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1712 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x3,		/* 3 */

	/* Parameter Index */

/* 1714 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1716 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1718 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pVal */

/* 1720 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 1722 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1724 */	NdrFcShort( 0x42 ),	/* Type Offset=66 */

	/* Return value */

/* 1726 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1728 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1730 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_InputFile */

/* 1732 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1734 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1738 */	NdrFcShort( 0x12 ),	/* 18 */
/* 1740 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1742 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1744 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1746 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 1748 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 1750 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1752 */	NdrFcShort( 0x1e ),	/* Type Offset=30 */

	/* Return value */

/* 1754 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1756 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1758 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_InputFile */

/* 1760 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1762 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1766 */	NdrFcShort( 0x13 ),	/* 19 */
/* 1768 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1770 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1772 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1774 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x2,		/* 2 */

	/* Parameter newVal */

/* 1776 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1778 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1780 */	NdrFcShort( 0x2c ),	/* Type Offset=44 */

	/* Return value */

/* 1782 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1784 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1786 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_OutputFile */

/* 1788 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1790 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1794 */	NdrFcShort( 0x14 ),	/* 20 */
/* 1796 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1798 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1800 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1802 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 1804 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 1806 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1808 */	NdrFcShort( 0x1e ),	/* Type Offset=30 */

	/* Return value */

/* 1810 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1812 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1814 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_OutputFile */

/* 1816 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1818 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1822 */	NdrFcShort( 0x15 ),	/* 21 */
/* 1824 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1826 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1828 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1830 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x2,		/* 2 */

	/* Parameter newVal */

/* 1832 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 1834 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1836 */	NdrFcShort( 0x2c ),	/* Type Offset=44 */

	/* Return value */

/* 1838 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1840 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1842 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_ConversionProfile */

/* 1844 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1846 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1850 */	NdrFcShort( 0x16 ),	/* 22 */
/* 1852 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1854 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1856 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1858 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 1860 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 1862 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1864 */	NdrFcShort( 0x6a ),	/* Type Offset=106 */

	/* Return value */

/* 1866 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1868 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1870 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure putref_ConversionProfile */

/* 1872 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1874 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1878 */	NdrFcShort( 0x17 ),	/* 23 */
/* 1880 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1882 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1884 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1886 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x2,		/* 2 */

	/* Parameter newVal */

/* 1888 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 1890 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1892 */	NdrFcShort( 0x58 ),	/* Type Offset=88 */

	/* Return value */

/* 1894 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1896 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1898 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_ProfileCount */

/* 1900 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1902 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1906 */	NdrFcShort( 0x18 ),	/* 24 */
/* 1908 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1910 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1912 */	NdrFcShort( 0x24 ),	/* 36 */
/* 1914 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 1916 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 1918 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1920 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 1922 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1924 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1926 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_Profile */

/* 1928 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1930 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1934 */	NdrFcShort( 0x19 ),	/* 25 */
/* 1936 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1938 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1940 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1942 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x3,		/* 3 */

	/* Parameter Index */

/* 1944 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1946 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1948 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pVal */

/* 1950 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 1952 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1954 */	NdrFcShort( 0x6a ),	/* Type Offset=106 */

	/* Return value */

/* 1956 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1958 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1960 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure putref_Profile */

/* 1962 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1964 */	NdrFcLong( 0x0 ),	/* 0 */
/* 1968 */	NdrFcShort( 0x1a ),	/* 26 */
/* 1970 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 1972 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1974 */	NdrFcShort( 0x8 ),	/* 8 */
/* 1976 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x3,		/* 3 */

	/* Parameter Index */

/* 1978 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 1980 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 1982 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter newVal */

/* 1984 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 1986 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 1988 */	NdrFcShort( 0x58 ),	/* Type Offset=88 */

	/* Return value */

/* 1990 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 1992 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 1994 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_AudioCodec */

/* 1996 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 1998 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2002 */	NdrFcShort( 0x1b ),	/* 27 */
/* 2004 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 2006 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2008 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2010 */	0x5,		/* Oi2 Flags:  srv must size, has return, */
			0x3,		/* 3 */

	/* Parameter Index */

/* 2012 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 2014 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2016 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pVal */

/* 2018 */	NdrFcShort( 0x13 ),	/* Flags:  must size, must free, out, */
/* 2020 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2022 */	NdrFcShort( 0x42 ),	/* Type Offset=66 */

	/* Return value */

/* 2024 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2026 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2028 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_AudioCodecCount */

/* 2030 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2032 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2036 */	NdrFcShort( 0x1c ),	/* 28 */
/* 2038 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2040 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2042 */	NdrFcShort( 0x24 ),	/* 36 */
/* 2044 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 2046 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 2048 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2050 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 2052 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2054 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2056 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure get_EncodeFramerate */

/* 2058 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2060 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2064 */	NdrFcShort( 0x1d ),	/* 29 */
/* 2066 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2068 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2070 */	NdrFcShort( 0x24 ),	/* 36 */
/* 2072 */	0x4,		/* Oi2 Flags:  has return, */
			0x2,		/* 2 */

	/* Parameter pVal */

/* 2074 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 2076 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2078 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 2080 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2082 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2084 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure put_LicenseKey */

/* 2086 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 2088 */	NdrFcLong( 0x0 ),	/* 0 */
/* 2092 */	NdrFcShort( 0x1e ),	/* 30 */
/* 2094 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 2096 */	NdrFcShort( 0x0 ),	/* 0 */
/* 2098 */	NdrFcShort( 0x8 ),	/* 8 */
/* 2100 */	0x6,		/* Oi2 Flags:  clt must size, has return, */
			0x2,		/* 2 */

	/* Parameter newVal */

/* 2102 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 2104 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 2106 */	NdrFcShort( 0x2c ),	/* Type Offset=44 */

	/* Return value */

/* 2108 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 2110 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 2112 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

			0x0
        }
    };

static const MIDL_TYPE_FORMAT_STRING __MIDL_TypeFormatString =
    {
        0,
        {
			NdrFcShort( 0x0 ),	/* 0 */
/*  2 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/*  4 */	NdrFcShort( 0x1a ),	/* Offset= 26 (30) */
/*  6 */	
			0x13, 0x0,	/* FC_OP */
/*  8 */	NdrFcShort( 0xc ),	/* Offset= 12 (20) */
/* 10 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 12 */	NdrFcShort( 0x2 ),	/* 2 */
/* 14 */	0x9,		/* Corr desc: FC_ULONG */
			0x0,		/*  */
/* 16 */	NdrFcShort( 0xfffc ),	/* -4 */
/* 18 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 20 */	
			0x17,		/* FC_CSTRUCT */
			0x3,		/* 3 */
/* 22 */	NdrFcShort( 0x8 ),	/* 8 */
/* 24 */	NdrFcShort( 0xfffffff2 ),	/* Offset= -14 (10) */
/* 26 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 28 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 30 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 32 */	NdrFcShort( 0x0 ),	/* 0 */
/* 34 */	NdrFcShort( 0x4 ),	/* 4 */
/* 36 */	NdrFcShort( 0x0 ),	/* 0 */
/* 38 */	NdrFcShort( 0xffffffe0 ),	/* Offset= -32 (6) */
/* 40 */	
			0x12, 0x0,	/* FC_UP */
/* 42 */	NdrFcShort( 0xffffffea ),	/* Offset= -22 (20) */
/* 44 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 46 */	NdrFcShort( 0x0 ),	/* 0 */
/* 48 */	NdrFcShort( 0x4 ),	/* 4 */
/* 50 */	NdrFcShort( 0x0 ),	/* 0 */
/* 52 */	NdrFcShort( 0xfffffff4 ),	/* Offset= -12 (40) */
/* 54 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 56 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/* 58 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 60 */	0xc,		/* FC_DOUBLE */
			0x5c,		/* FC_PAD */
/* 62 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 64 */	0x6,		/* FC_SHORT */
			0x5c,		/* FC_PAD */
/* 66 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 68 */	NdrFcShort( 0x2 ),	/* Offset= 2 (70) */
/* 70 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 72 */	NdrFcLong( 0x27dce088 ),	/* 668786824 */
/* 76 */	NdrFcShort( 0x4143 ),	/* 16707 */
/* 78 */	NdrFcShort( 0x4e1b ),	/* 19995 */
/* 80 */	0x8a,		/* 138 */
			0x52,		/* 82 */
/* 82 */	0x49,		/* 73 */
			0x6e,		/* 110 */
/* 84 */	0x96,		/* 150 */
			0x3d,		/* 61 */
/* 86 */	0xa0,		/* 160 */
			0x94,		/* 148 */
/* 88 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 90 */	NdrFcLong( 0xde417bb1 ),	/* -566133839 */
/* 94 */	NdrFcShort( 0xa32f ),	/* -23761 */
/* 96 */	NdrFcShort( 0x477f ),	/* 18303 */
/* 98 */	0xa7,		/* 167 */
			0x3b,		/* 59 */
/* 100 */	0xad,		/* 173 */
			0x47,		/* 71 */
/* 102 */	0x8c,		/* 140 */
			0x25,		/* 37 */
/* 104 */	0x9c,		/* 156 */
			0x57,		/* 87 */
/* 106 */	
			0x11, 0x10,	/* FC_RP [pointer_deref] */
/* 108 */	NdrFcShort( 0xffffffec ),	/* Offset= -20 (88) */

			0x0
        }
    };

static const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[ WIRE_MARSHAL_TABLE_SIZE ] = 
        {
            
            {
            BSTR_UserSize
            ,BSTR_UserMarshal
            ,BSTR_UserUnmarshal
            ,BSTR_UserFree
            }

        };



/* Object interface: IUnknown, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IDispatch, ver. 0.0,
   GUID={0x00020400,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IWMVCodec, ver. 0.0,
   GUID={0x27DCE088,0x4143,0x4E1B,{0x8A,0x52,0x49,0x6E,0x96,0x3D,0xA0,0x94}} */

#pragma code_seg(".orpc")
static const unsigned short IWMVCodec_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    0,
    28,
    56,
    84,
    112,
    140,
    168,
    196,
    224,
    252,
    280,
    308,
    336,
    364,
    392,
    420,
    448,
    476,
    504,
    532,
    560,
    588,
    616,
    644,
    672,
    700,
    728,
    756,
    808,
    836,
    858,
    892
    };

static const MIDL_STUBLESS_PROXY_INFO IWMVCodec_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IWMVCodec_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IWMVCodec_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IWMVCodec_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(39) _IWMVCodecProxyVtbl = 
{
    &IWMVCodec_ProxyInfo,
    &IID_IWMVCodec,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfoCount */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfo */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* IWMVCodec::get_CodecName */ ,
    (void *) (INT_PTR) -1 /* IWMVCodec::put_CodecName */ ,
    (void *) (INT_PTR) -1 /* IWMVCodec::get_CodecDescription */ ,
    (void *) (INT_PTR) -1 /* IWMVCodec::put_CodecDescription */ ,
    (void *) (INT_PTR) -1 /* IWMVCodec::get_MajorType */ ,
    (void *) (INT_PTR) -1 /* IWMVCodec::get_MaxPasses */ ,
    (void *) (INT_PTR) -1 /* IWMVCodec::get_Passes */ ,
    (void *) (INT_PTR) -1 /* IWMVCodec::put_Passes */ ,
    (void *) (INT_PTR) -1 /* IWMVCodec::get_Quality */ ,
    (void *) (INT_PTR) -1 /* IWMVCodec::put_Quality */ ,
    (void *) (INT_PTR) -1 /* IWMVCodec::get_Bitrate */ ,
    (void *) (INT_PTR) -1 /* IWMVCodec::put_Bitrate */ ,
    (void *) (INT_PTR) -1 /* IWMVCodec::get_VBRMode */ ,
    (void *) (INT_PTR) -1 /* IWMVCodec::put_VBRMode */ ,
    (void *) (INT_PTR) -1 /* IWMVCodec::get_KeyframeFrequency */ ,
    (void *) (INT_PTR) -1 /* IWMVCodec::put_KeyframeFrequency */ ,
    (void *) (INT_PTR) -1 /* IWMVCodec::get_Framerate */ ,
    (void *) (INT_PTR) -1 /* IWMVCodec::put_Framerate */ ,
    (void *) (INT_PTR) -1 /* IWMVCodec::get_Complexity */ ,
    (void *) (INT_PTR) -1 /* IWMVCodec::put_Complexity */ ,
    (void *) (INT_PTR) -1 /* IWMVCodec::get_FormatIndex */ ,
    (void *) (INT_PTR) -1 /* IWMVCodec::put_FormatIndex */ ,
    (void *) (INT_PTR) -1 /* IWMVCodec::get_CodecGuid */ ,
    (void *) (INT_PTR) -1 /* IWMVCodec::get_ComplexityMax */ ,
    (void *) (INT_PTR) -1 /* IWMVCodec::get_ComplexityOffline */ ,
    (void *) (INT_PTR) -1 /* IWMVCodec::get_ComplexityLive */ ,
    (void *) (INT_PTR) -1 /* IWMVCodec::get_IsVBRSupported */ ,
    (void *) (INT_PTR) -1 /* IWMVCodec::SupportedVBRModes */ ,
    (void *) (INT_PTR) -1 /* IWMVCodec::get_FormatCount */ ,
    (void *) (INT_PTR) -1 /* IWMVCodec::LoadCodecFormats */ ,
    (void *) (INT_PTR) -1 /* IWMVCodec::get_FormatName */ ,
    (void *) (INT_PTR) -1 /* IWMVCodec::get_CodecIndex */
};


static const PRPC_STUB_FUNCTION IWMVCodec_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IWMVCodecStubVtbl =
{
    &IID_IWMVCodec,
    &IWMVCodec_ServerInfo,
    39,
    &IWMVCodec_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IWMVProfile, ver. 0.0,
   GUID={0xDE417BB1,0xA32F,0x477F,{0xA7,0x3B,0xAD,0x47,0x8C,0x25,0x9C,0x57}} */

#pragma code_seg(".orpc")
static const unsigned short IWMVProfile_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    0,
    28,
    56,
    84,
    920,
    948,
    976,
    1004,
    224,
    252,
    1032,
    1066,
    336,
    364,
    392,
    420,
    1100,
    1128,
    1156,
    1184,
    560,
    588,
    1212,
    1240,
    672,
    1268,
    1296,
    1324,
    808,
    1352,
    1380,
    1408,
    1436
    };

static const MIDL_STUBLESS_PROXY_INFO IWMVProfile_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IWMVProfile_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IWMVProfile_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IWMVProfile_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(40) _IWMVProfileProxyVtbl = 
{
    &IWMVProfile_ProxyInfo,
    &IID_IWMVProfile,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfoCount */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfo */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* IWMVProfile::get_ProfileName */ ,
    (void *) (INT_PTR) -1 /* IWMVProfile::put_ProfileName */ ,
    (void *) (INT_PTR) -1 /* IWMVProfile::get_ProfileDescription */ ,
    (void *) (INT_PTR) -1 /* IWMVProfile::put_ProfileDescription */ ,
    (void *) (INT_PTR) -1 /* IWMVProfile::get_HasVideoStream */ ,
    (void *) (INT_PTR) -1 /* IWMVProfile::put_HasVideoStream */ ,
    (void *) (INT_PTR) -1 /* IWMVProfile::get_HasAudioStream */ ,
    (void *) (INT_PTR) -1 /* IWMVProfile::put_HasAudioStream */ ,
    (void *) (INT_PTR) -1 /* IWMVProfile::get_Bitrate */ ,
    (void *) (INT_PTR) -1 /* IWMVProfile::put_Bitrate */ ,
    (void *) (INT_PTR) -1 /* IWMVProfile::get_StringEquivalent */ ,
    (void *) (INT_PTR) -1 /* IWMVProfile::put_StringEquivalent */ ,
    (void *) (INT_PTR) -1 /* IWMVProfile::get_VideoWidth */ ,
    (void *) (INT_PTR) -1 /* IWMVProfile::put_VideoWidth */ ,
    (void *) (INT_PTR) -1 /* IWMVProfile::get_VideoHeight */ ,
    (void *) (INT_PTR) -1 /* IWMVProfile::put_VideoHeight */ ,
    (void *) (INT_PTR) -1 /* IWMVProfile::get_VideoCodec */ ,
    (void *) (INT_PTR) -1 /* IWMVProfile::put_VideoCodec */ ,
    (void *) (INT_PTR) -1 /* IWMVProfile::get_AudioCodec */ ,
    (void *) (INT_PTR) -1 /* IWMVProfile::put_AudioCodec */ ,
    (void *) (INT_PTR) -1 /* IWMVProfile::get_KeyFrameSpacing */ ,
    (void *) (INT_PTR) -1 /* IWMVProfile::put_KeyFrameSpacing */ ,
    (void *) (INT_PTR) -1 /* IWMVProfile::get_Framerate */ ,
    (void *) (INT_PTR) -1 /* IWMVProfile::put_Framerate */ ,
    (void *) (INT_PTR) -1 /* IWMVProfile::get_Quality */ ,
    (void *) (INT_PTR) -1 /* IWMVProfile::put_Quality */ ,
    (void *) (INT_PTR) -1 /* IWMVProfile::get_VideoBitrate */ ,
    (void *) (INT_PTR) -1 /* IWMVProfile::put_VideoBitrate */ ,
    (void *) (INT_PTR) -1 /* IWMVProfile::get_AudioBitrate */ ,
    (void *) (INT_PTR) -1 /* IWMVProfile::put_AudioBitrate */ ,
    (void *) (INT_PTR) -1 /* IWMVProfile::CopyProfile */ ,
    (void *) (INT_PTR) -1 /* IWMVProfile::get_Seekable */ ,
    (void *) (INT_PTR) -1 /* IWMVProfile::put_Seekable */
};


static const PRPC_STUB_FUNCTION IWMVProfile_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IWMVProfileStubVtbl =
{
    &IID_IWMVProfile,
    &IWMVProfile_ServerInfo,
    40,
    &IWMVProfile_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IWMVCreatorObj, ver. 0.0,
   GUID={0xA4AB6D61,0x6831,0x4535,{0xB3,0x9C,0x98,0x16,0x30,0xAD,0x31,0x09}} */

#pragma code_seg(".orpc")
static const unsigned short IWMVCreatorObj_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    1464,
    1486,
    1508,
    1536,
    1564,
    1592,
    168,
    1614,
    1648,
    1670,
    1698,
    1732,
    1760,
    1788,
    1816,
    1844,
    1872,
    1900,
    1928,
    1962,
    1996,
    2030,
    2058,
    2086
    };

static const MIDL_STUBLESS_PROXY_INFO IWMVCreatorObj_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IWMVCreatorObj_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IWMVCreatorObj_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IWMVCreatorObj_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(31) _IWMVCreatorObjProxyVtbl = 
{
    &IWMVCreatorObj_ProxyInfo,
    &IID_IWMVCreatorObj,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfoCount */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetTypeInfo */ ,
    0 /* (void *) (INT_PTR) -1 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* IWMVCreatorObj::StartConversion */ ,
    (void *) (INT_PTR) -1 /* IWMVCreatorObj::StopConversion */ ,
    (void *) (INT_PTR) -1 /* IWMVCreatorObj::get_Duration */ ,
    (void *) (INT_PTR) -1 /* IWMVCreatorObj::get_Progress */ ,
    (void *) (INT_PTR) -1 /* IWMVCreatorObj::put_Progress */ ,
    (void *) (INT_PTR) -1 /* IWMVCreatorObj::LoadSystemProfiles */ ,
    (void *) (INT_PTR) -1 /* IWMVCreatorObj::get_SystemProfileCount */ ,
    (void *) (INT_PTR) -1 /* IWMVCreatorObj::get_SystemProfile */ ,
    (void *) (INT_PTR) -1 /* IWMVCreatorObj::LoadSystemCodecs */ ,
    (void *) (INT_PTR) -1 /* IWMVCreatorObj::get_VideoCodecCount */ ,
    (void *) (INT_PTR) -1 /* IWMVCreatorObj::get_VideoCodec */ ,
    (void *) (INT_PTR) -1 /* IWMVCreatorObj::get_InputFile */ ,
    (void *) (INT_PTR) -1 /* IWMVCreatorObj::put_InputFile */ ,
    (void *) (INT_PTR) -1 /* IWMVCreatorObj::get_OutputFile */ ,
    (void *) (INT_PTR) -1 /* IWMVCreatorObj::put_OutputFile */ ,
    (void *) (INT_PTR) -1 /* IWMVCreatorObj::get_ConversionProfile */ ,
    (void *) (INT_PTR) -1 /* IWMVCreatorObj::putref_ConversionProfile */ ,
    (void *) (INT_PTR) -1 /* IWMVCreatorObj::get_ProfileCount */ ,
    (void *) (INT_PTR) -1 /* IWMVCreatorObj::get_Profile */ ,
    (void *) (INT_PTR) -1 /* IWMVCreatorObj::putref_Profile */ ,
    (void *) (INT_PTR) -1 /* IWMVCreatorObj::get_AudioCodec */ ,
    (void *) (INT_PTR) -1 /* IWMVCreatorObj::get_AudioCodecCount */ ,
    (void *) (INT_PTR) -1 /* IWMVCreatorObj::get_EncodeFramerate */ ,
    (void *) (INT_PTR) -1 /* IWMVCreatorObj::put_LicenseKey */
};


static const PRPC_STUB_FUNCTION IWMVCreatorObj_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IWMVCreatorObjStubVtbl =
{
    &IID_IWMVCreatorObj,
    &IWMVCreatorObj_ServerInfo,
    31,
    &IWMVCreatorObj_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};

static const MIDL_STUB_DESC Object_StubDesc = 
    {
    0,
    NdrOleAllocate,
    NdrOleFree,
    0,
    0,
    0,
    0,
    0,
    __MIDL_TypeFormatString.Format,
    1, /* -error bounds_check flag */
    0x20000, /* Ndr library version */
    0,
    0x600015b, /* MIDL Version 6.0.347 */
    0,
    UserMarshalRoutines,
    0,  /* notify & notify_flag routine table */
    0x1, /* MIDL flag */
    0, /* cs routines */
    0,   /* proxy/server info */
    0   /* Reserved5 */
    };

const CInterfaceProxyVtbl * _WMVCreator_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_IWMVCreatorObjProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IWMVCodecProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IWMVProfileProxyVtbl,
    0
};

const CInterfaceStubVtbl * _WMVCreator_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_IWMVCreatorObjStubVtbl,
    ( CInterfaceStubVtbl *) &_IWMVCodecStubVtbl,
    ( CInterfaceStubVtbl *) &_IWMVProfileStubVtbl,
    0
};

PCInterfaceName const _WMVCreator_InterfaceNamesList[] = 
{
    "IWMVCreatorObj",
    "IWMVCodec",
    "IWMVProfile",
    0
};

const IID *  _WMVCreator_BaseIIDList[] = 
{
    &IID_IDispatch,
    &IID_IDispatch,
    &IID_IDispatch,
    0
};


#define _WMVCreator_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _WMVCreator, pIID, n)

int __stdcall _WMVCreator_IID_Lookup( const IID * pIID, int * pIndex )
{
    IID_BS_LOOKUP_SETUP

    IID_BS_LOOKUP_INITIAL_TEST( _WMVCreator, 3, 2 )
    IID_BS_LOOKUP_NEXT_TEST( _WMVCreator, 1 )
    IID_BS_LOOKUP_RETURN_RESULT( _WMVCreator, 3, *pIndex )
    
}

const ExtendedProxyFileInfo WMVCreator_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _WMVCreator_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _WMVCreator_StubVtblList,
    (const PCInterfaceName * ) & _WMVCreator_InterfaceNamesList,
    (const IID ** ) & _WMVCreator_BaseIIDList,
    & _WMVCreator_IID_Lookup, 
    3,
    2,
    0, /* table of [async_uuid] interfaces */
    0, /* Filler1 */
    0, /* Filler2 */
    0  /* Filler3 */
};


#endif /* !defined(_M_IA64) && !defined(_M_AMD64)*/

