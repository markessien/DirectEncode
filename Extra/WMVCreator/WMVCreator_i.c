
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


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

MIDL_DEFINE_GUID(IID, IID_IWMVCodec,0x27DCE088,0x4143,0x4E1B,0x8A,0x52,0x49,0x6E,0x96,0x3D,0xA0,0x94);


MIDL_DEFINE_GUID(IID, IID_IWMVProfile,0xDE417BB1,0xA32F,0x477F,0xA7,0x3B,0xAD,0x47,0x8C,0x25,0x9C,0x57);


MIDL_DEFINE_GUID(IID, IID_IWMVCreatorObj,0xA4AB6D61,0x6831,0x4535,0xB3,0x9C,0x98,0x16,0x30,0xAD,0x31,0x09);


MIDL_DEFINE_GUID(IID, LIBID_WMVCreatorLib,0xF7AFF85C,0xAC68,0x44F5,0xAE,0x03,0x18,0x96,0xB2,0x7E,0x42,0x3E);


MIDL_DEFINE_GUID(IID, DIID__IWMVCreatorObjEvents,0x7D38D249,0x06FC,0x4D98,0xAF,0x7D,0x6C,0x64,0x9C,0x11,0xF9,0x86);


MIDL_DEFINE_GUID(CLSID, CLSID_WMVCreator,0xB6C1EA13,0xA642,0x4078,0x8E,0x7F,0x5A,0x9E,0x62,0xF0,0xDB,0xE9);


MIDL_DEFINE_GUID(CLSID, CLSID_WMVCodec,0x804B1182,0x1C09,0x414C,0x85,0x1F,0x7F,0x4A,0xAA,0x81,0x30,0x91);


MIDL_DEFINE_GUID(CLSID, CLSID_WMVProfile,0xA27BF69D,0x5ACD,0x4A01,0x99,0x13,0x82,0x7B,0xBF,0xE5,0xBC,0x83);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



#endif /* !defined(_M_IA64) && !defined(_M_AMD64)*/

