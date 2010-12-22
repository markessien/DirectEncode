/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Mon Oct 20 18:01:28 2008
 */
/* Compiler settings for Z:\Development\DirectEncode\DirectEncodeVB\DirectEncodeVB.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )
#ifdef __cplusplus
extern "C"{
#endif 


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

const IID LIBID_DIRECTENCODEVBLib = {0xABFB7D65,0xF937,0x428D,{0x8E,0xA1,0x37,0x74,0xA9,0x40,0x00,0x7A}};


const IID IID_IStandardMPEGEncoderVB = {0x5E4A1AE4,0x5A1D,0x4A70,{0xAD,0xB7,0x53,0xBD,0xD1,0x95,0xD9,0x62}};


const CLSID CLSID_StandardMPEGEncoderVB = {0x95D4CFC4,0xF499,0x4CB1,{0x8D,0x56,0x5A,0xE5,0x23,0x4D,0xBF,0x90}};


#ifdef __cplusplus
}
#endif

