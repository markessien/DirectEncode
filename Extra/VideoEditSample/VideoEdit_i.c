

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 6.00.0366 */
/* at Mon May 12 12:12:24 2008
 */
/* Compiler settings for .\VideoEdit.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#pragma warning( disable: 4049 )  /* more than 64k source lines */


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, LIBID_VIDEOEDITLib,0x939B0CFC,0xB68F,0x48FE,0x85,0xE9,0x02,0x00,0xE9,0x36,0x7B,0x0B);


MIDL_DEFINE_GUID(IID, IID_IVideoRect,0x7D8E84A6,0x81B2,0x4912,0x89,0x1C,0x91,0x47,0x03,0x60,0xA4,0x14);


MIDL_DEFINE_GUID(IID, DIID__IVideoEditObjEvents,0xAE6F165D,0x9469,0x41D5,0x9F,0xDA,0xCC,0xF8,0x64,0x2E,0x47,0x47);


MIDL_DEFINE_GUID(IID, IID_IMediaFile,0x4E224C6B,0xE3B5,0x4C86,0xBF,0xF5,0x15,0x18,0xCE,0x97,0x73,0xE4);


MIDL_DEFINE_GUID(IID, IID_IVideoClip,0x423C8CAA,0xD940,0x4958,0x96,0x03,0xEB,0x07,0xB9,0xF8,0xBD,0x36);


MIDL_DEFINE_GUID(IID, IID_IVideoEditObj,0xCC95A0DF,0x4F4A,0x44BE,0x9B,0xFA,0x02,0xA8,0xBA,0xB6,0x3A,0x27);


MIDL_DEFINE_GUID(CLSID, CLSID_VideoEdit,0x665A4D7D,0x91A5,0x4EA4,0x99,0x9A,0x4F,0xAA,0x4E,0x5A,0x8C,0x50);


MIDL_DEFINE_GUID(CLSID, CLSID_MediaFile,0xCF561283,0x7544,0x4B90,0x9C,0x68,0x49,0xD6,0x90,0x74,0x6B,0x3E);


MIDL_DEFINE_GUID(CLSID, CLSID_VideoClip,0x0527F33C,0xC731,0x4AC4,0xB7,0xAD,0x60,0x72,0x95,0x8B,0x11,0x79);


MIDL_DEFINE_GUID(CLSID, CLSID_VideoRect,0x95D60350,0xD4BF,0x48A4,0x81,0xC6,0x3D,0x25,0x95,0x48,0x47,0xA3);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



