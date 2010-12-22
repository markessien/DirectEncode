/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Mon Aug 21 16:35:01 2006
 */
/* Compiler settings for X:\Development\x86Win32\DirectEncode\DirectEncode.idl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __DirectEncode_h__
#define __DirectEncode_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IStandardMpegMultiplexerProfile_FWD_DEFINED__
#define __IStandardMpegMultiplexerProfile_FWD_DEFINED__
typedef interface IStandardMpegMultiplexerProfile IStandardMpegMultiplexerProfile;
#endif 	/* __IStandardMpegMultiplexerProfile_FWD_DEFINED__ */


#ifndef __IStandardMpegEncoderProfile_FWD_DEFINED__
#define __IStandardMpegEncoderProfile_FWD_DEFINED__
typedef interface IStandardMpegEncoderProfile IStandardMpegEncoderProfile;
#endif 	/* __IStandardMpegEncoderProfile_FWD_DEFINED__ */


#ifndef __IStandardMpegEncoderStats_FWD_DEFINED__
#define __IStandardMpegEncoderStats_FWD_DEFINED__
typedef interface IStandardMpegEncoderStats IStandardMpegEncoderStats;
#endif 	/* __IStandardMpegEncoderStats_FWD_DEFINED__ */


#ifndef __IStandardMpegEncoder_FWD_DEFINED__
#define __IStandardMpegEncoder_FWD_DEFINED__
typedef interface IStandardMpegEncoder IStandardMpegEncoder;
#endif 	/* __IStandardMpegEncoder_FWD_DEFINED__ */


#ifndef __StandardMpegEncoder_FWD_DEFINED__
#define __StandardMpegEncoder_FWD_DEFINED__

#ifdef __cplusplus
typedef class StandardMpegEncoder StandardMpegEncoder;
#else
typedef struct StandardMpegEncoder StandardMpegEncoder;
#endif /* __cplusplus */

#endif 	/* __StandardMpegEncoder_FWD_DEFINED__ */


#ifndef __StandardMpegEncoderStats_FWD_DEFINED__
#define __StandardMpegEncoderStats_FWD_DEFINED__

#ifdef __cplusplus
typedef class StandardMpegEncoderStats StandardMpegEncoderStats;
#else
typedef struct StandardMpegEncoderStats StandardMpegEncoderStats;
#endif /* __cplusplus */

#endif 	/* __StandardMpegEncoderStats_FWD_DEFINED__ */


#ifndef __StandardMpegEncoderProfile_FWD_DEFINED__
#define __StandardMpegEncoderProfile_FWD_DEFINED__

#ifdef __cplusplus
typedef class StandardMpegEncoderProfile StandardMpegEncoderProfile;
#else
typedef struct StandardMpegEncoderProfile StandardMpegEncoderProfile;
#endif /* __cplusplus */

#endif 	/* __StandardMpegEncoderProfile_FWD_DEFINED__ */


#ifndef __StandardMpegMultiplexerProfile_FWD_DEFINED__
#define __StandardMpegMultiplexerProfile_FWD_DEFINED__

#ifdef __cplusplus
typedef class StandardMpegMultiplexerProfile StandardMpegMultiplexerProfile;
#else
typedef struct StandardMpegMultiplexerProfile StandardMpegMultiplexerProfile;
#endif /* __cplusplus */

#endif 	/* __StandardMpegMultiplexerProfile_FWD_DEFINED__ */


#ifndef __StandardMpegEncoderGeneralProps_FWD_DEFINED__
#define __StandardMpegEncoderGeneralProps_FWD_DEFINED__

#ifdef __cplusplus
typedef class StandardMpegEncoderGeneralProps StandardMpegEncoderGeneralProps;
#else
typedef struct StandardMpegEncoderGeneralProps StandardMpegEncoderGeneralProps;
#endif /* __cplusplus */

#endif 	/* __StandardMpegEncoderGeneralProps_FWD_DEFINED__ */


#ifndef __StandardMpegEncoderVideoProps_FWD_DEFINED__
#define __StandardMpegEncoderVideoProps_FWD_DEFINED__

#ifdef __cplusplus
typedef class StandardMpegEncoderVideoProps StandardMpegEncoderVideoProps;
#else
typedef struct StandardMpegEncoderVideoProps StandardMpegEncoderVideoProps;
#endif /* __cplusplus */

#endif 	/* __StandardMpegEncoderVideoProps_FWD_DEFINED__ */


#ifndef __StandardMpegEncoderAudioProps_FWD_DEFINED__
#define __StandardMpegEncoderAudioProps_FWD_DEFINED__

#ifdef __cplusplus
typedef class StandardMpegEncoderAudioProps StandardMpegEncoderAudioProps;
#else
typedef struct StandardMpegEncoderAudioProps StandardMpegEncoderAudioProps;
#endif /* __cplusplus */

#endif 	/* __StandardMpegEncoderAudioProps_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_DirectEncode_0000 */
/* [local] */ 

typedef /* [public] */ 
enum _VideoOutputFormat
    {	VIDEOFORMAT_NONE	= 0,
	VIDEOFORMAT_MPEG1	= VIDEOFORMAT_NONE + 1,
	VIDEOFORMAT_MPEG2	= VIDEOFORMAT_MPEG1 + 1,
	VIDEOFORMAT_MPEG4	= VIDEOFORMAT_MPEG2 + 1,
	VIDEOFORMAT_H263	= VIDEOFORMAT_MPEG4 + 1,
	VIDEOFORMAT_H264	= VIDEOFORMAT_H263 + 1
    }	VideoOutputFormat;

typedef /* [public] */ 
enum _AudioOutputFormat
    {	AUDIOFORMAT_NONE	= 0,
	AUDIOFORMAT_MP3	= AUDIOFORMAT_NONE + 1,
	AUDIOFORMAT_MP2	= AUDIOFORMAT_MP3 + 1,
	AUDIOFORMAT_AC3	= AUDIOFORMAT_MP2 + 1,
	AUDIOFORMAT_PCM	= AUDIOFORMAT_AC3 + 1,
	AUDIOFORMAT_WAV	= AUDIOFORMAT_PCM + 1,
	AUDIOFORMAT_AAC	= AUDIOFORMAT_WAV + 1,
	AUDIOFORMAT_AMRNB	= AUDIOFORMAT_AAC + 1
    }	AudioOutputFormat;

typedef /* [public] */ 
enum _SystemsOutputFormat
    {	SYSTEMSFORMAT_NONE	= 0,
	SYSTEMSFORMAT_MPEG1	= SYSTEMSFORMAT_NONE + 1,
	SYSTEMSFORMAT_MPEG2	= SYSTEMSFORMAT_MPEG1 + 1,
	SYSTEMSFORMAT_VCD	= SYSTEMSFORMAT_MPEG2 + 1,
	SYSTEMSFORMAT_SVCD	= SYSTEMSFORMAT_VCD + 1,
	SYSTEMSFORMAT_DVD	= SYSTEMSFORMAT_SVCD + 1,
	SYSTEMSFORMAT_VCD_STILL	= SYSTEMSFORMAT_DVD + 1,
	SYSTEMSFORMAT_SVCD_STILL	= SYSTEMSFORMAT_VCD_STILL + 1,
	SYSTEMSFORMAT_MP4	= SYSTEMSFORMAT_SVCD_STILL + 1,
	SYSTEMSFORMAT_3GP	= SYSTEMSFORMAT_MP4 + 1,
	SYSTEMSFORMAT_MOV	= SYSTEMSFORMAT_3GP + 1,
	SYSTEMSFORMAT_3G2	= SYSTEMSFORMAT_MOV + 1,
	SYSTEMSFORMAT_PSP	= SYSTEMSFORMAT_3G2 + 1,
	SYSTEMSFORMAT_AVI	= SYSTEMSFORMAT_PSP + 1,
	SYSTEMSFORMAT_RM	= SYSTEMSFORMAT_AVI + 1,
	SYSTEMSFORMAT_KVCD	= SYSTEMSFORMAT_RM + 1
    }	SystemsOutputFormat;

typedef /* [public] */ 
enum _Constraint
    {	CONSTRAINT_NONE	= 0,
	CONSTRAINT_NTSC	= CONSTRAINT_NONE + 1,
	CONSTRAINT_FILM	= CONSTRAINT_NTSC + 1,
	CONSTRAINT_PAL	= CONSTRAINT_FILM + 1
    }	Constraint;

typedef /* [public] */ 
enum _BitrateMode
    {	BITRATEMODE_CBR	= 0,
	BITRATEMODE_VBR_2PASS	= BITRATEMODE_CBR + 1,
	BITRATEMODE_MVBR	= BITRATEMODE_VBR_2PASS + 1,
	BITRATEMODE_CQ_VBR	= BITRATEMODE_MVBR + 1,
	BITRATEMODE_CQ	= BITRATEMODE_CQ_VBR + 1
    }	BitrateMode;

typedef /* [public] */ 
enum _EncodeMode
    {	ENCODEMODE_NOINTERLACE	= 0,
	ENCODEMODE_INTERLACE	= ENCODEMODE_NOINTERLACE + 1,
	ENCODEMODE_32PULLDOWN	= ENCODEMODE_INTERLACE + 1,
	ENCODEMODE_32PULLDOWN_INVERSE	= ENCODEMODE_32PULLDOWN + 1
    }	EncodeMode;

typedef /* [public] */ 
enum _AspectRatio
    {	ASPECTRATIO_1TO1	= 0,
	ASPECTRATIO_4TO3	= ASPECTRATIO_1TO1 + 1,
	ASPECTRATIO_16TO9	= ASPECTRATIO_4TO3 + 1,
	ASPECTRATIO_2D11TO1	= ASPECTRATIO_16TO9 + 1
    }	AspectRatio;



extern RPC_IF_HANDLE __MIDL_itf_DirectEncode_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_DirectEncode_0000_v0_0_s_ifspec;

#ifndef __IStandardMpegMultiplexerProfile_INTERFACE_DEFINED__
#define __IStandardMpegMultiplexerProfile_INTERFACE_DEFINED__

/* interface IStandardMpegMultiplexerProfile */
/* [helpstring][unique][dual][uuid][object] */ 


EXTERN_C const IID IID_IStandardMpegMultiplexerProfile;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7E772181-B7ED-4d9d-A364-0E8771AAFF70")
    IStandardMpegMultiplexerProfile : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetDeleteElementaryStreams( 
            /* [in] */ BOOL bDelete) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDeleteElementaryStreams( 
            /* [out] */ BOOL __RPC_FAR *bDelete) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetMultiplexRate( 
            /* [in] */ long nRate) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMultiplexRate( 
            /* [out] */ long __RPC_FAR *pnMux) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetMultiplexPacketSize( 
            /* [in] */ long nSize) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMultiplexPacketSize( 
            /* [out] */ long __RPC_FAR *pnSize) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetMultiplexPreload( 
            /* [in] */ float fPreload) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMultiplexPreload( 
            /* [out] */ float __RPC_FAR *pfPreload) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetMultiplexMaxDelay( 
            /* [in] */ float fMaxDelay) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetMultiplexStreams( 
            /* [in] */ BOOL bMux) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMultiplexStreams( 
            /* [out] */ BOOL __RPC_FAR *bMux) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetMultiplexFormat( 
            /* [in] */ SystemsOutputFormat format) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMultiplexFormat( 
            /* [out] */ SystemsOutputFormat __RPC_FAR *format) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AddMultiplexFile( 
            /* [in] */ BSTR strPath) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetOnFlyMultiplex( 
            /* [in] */ BOOL bOnFlyMultiplex) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetOnFlyMultiplex( 
            /* [out] */ BOOL __RPC_FAR *pbOnFlyMultiplex) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetMultiplexFrameBalance( 
            /* [in] */ BOOL bVal) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetMultiplexOnStop( 
            /* [in] */ BOOL bVal) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMultiplexProgress( 
            /* [out] */ double __RPC_FAR *dProgress) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IStandardMpegMultiplexerProfileVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IStandardMpegMultiplexerProfile __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IStandardMpegMultiplexerProfile __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IStandardMpegMultiplexerProfile __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetDeleteElementaryStreams )( 
            IStandardMpegMultiplexerProfile __RPC_FAR * This,
            /* [in] */ BOOL bDelete);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDeleteElementaryStreams )( 
            IStandardMpegMultiplexerProfile __RPC_FAR * This,
            /* [out] */ BOOL __RPC_FAR *bDelete);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetMultiplexRate )( 
            IStandardMpegMultiplexerProfile __RPC_FAR * This,
            /* [in] */ long nRate);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMultiplexRate )( 
            IStandardMpegMultiplexerProfile __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *pnMux);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetMultiplexPacketSize )( 
            IStandardMpegMultiplexerProfile __RPC_FAR * This,
            /* [in] */ long nSize);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMultiplexPacketSize )( 
            IStandardMpegMultiplexerProfile __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *pnSize);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetMultiplexPreload )( 
            IStandardMpegMultiplexerProfile __RPC_FAR * This,
            /* [in] */ float fPreload);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMultiplexPreload )( 
            IStandardMpegMultiplexerProfile __RPC_FAR * This,
            /* [out] */ float __RPC_FAR *pfPreload);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetMultiplexMaxDelay )( 
            IStandardMpegMultiplexerProfile __RPC_FAR * This,
            /* [in] */ float fMaxDelay);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetMultiplexStreams )( 
            IStandardMpegMultiplexerProfile __RPC_FAR * This,
            /* [in] */ BOOL bMux);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMultiplexStreams )( 
            IStandardMpegMultiplexerProfile __RPC_FAR * This,
            /* [out] */ BOOL __RPC_FAR *bMux);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetMultiplexFormat )( 
            IStandardMpegMultiplexerProfile __RPC_FAR * This,
            /* [in] */ SystemsOutputFormat format);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMultiplexFormat )( 
            IStandardMpegMultiplexerProfile __RPC_FAR * This,
            /* [out] */ SystemsOutputFormat __RPC_FAR *format);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddMultiplexFile )( 
            IStandardMpegMultiplexerProfile __RPC_FAR * This,
            /* [in] */ BSTR strPath);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetOnFlyMultiplex )( 
            IStandardMpegMultiplexerProfile __RPC_FAR * This,
            /* [in] */ BOOL bOnFlyMultiplex);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetOnFlyMultiplex )( 
            IStandardMpegMultiplexerProfile __RPC_FAR * This,
            /* [out] */ BOOL __RPC_FAR *pbOnFlyMultiplex);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetMultiplexFrameBalance )( 
            IStandardMpegMultiplexerProfile __RPC_FAR * This,
            /* [in] */ BOOL bVal);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetMultiplexOnStop )( 
            IStandardMpegMultiplexerProfile __RPC_FAR * This,
            /* [in] */ BOOL bVal);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMultiplexProgress )( 
            IStandardMpegMultiplexerProfile __RPC_FAR * This,
            /* [out] */ double __RPC_FAR *dProgress);
        
        END_INTERFACE
    } IStandardMpegMultiplexerProfileVtbl;

    interface IStandardMpegMultiplexerProfile
    {
        CONST_VTBL struct IStandardMpegMultiplexerProfileVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IStandardMpegMultiplexerProfile_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IStandardMpegMultiplexerProfile_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IStandardMpegMultiplexerProfile_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IStandardMpegMultiplexerProfile_SetDeleteElementaryStreams(This,bDelete)	\
    (This)->lpVtbl -> SetDeleteElementaryStreams(This,bDelete)

#define IStandardMpegMultiplexerProfile_GetDeleteElementaryStreams(This,bDelete)	\
    (This)->lpVtbl -> GetDeleteElementaryStreams(This,bDelete)

#define IStandardMpegMultiplexerProfile_SetMultiplexRate(This,nRate)	\
    (This)->lpVtbl -> SetMultiplexRate(This,nRate)

#define IStandardMpegMultiplexerProfile_GetMultiplexRate(This,pnMux)	\
    (This)->lpVtbl -> GetMultiplexRate(This,pnMux)

#define IStandardMpegMultiplexerProfile_SetMultiplexPacketSize(This,nSize)	\
    (This)->lpVtbl -> SetMultiplexPacketSize(This,nSize)

#define IStandardMpegMultiplexerProfile_GetMultiplexPacketSize(This,pnSize)	\
    (This)->lpVtbl -> GetMultiplexPacketSize(This,pnSize)

#define IStandardMpegMultiplexerProfile_SetMultiplexPreload(This,fPreload)	\
    (This)->lpVtbl -> SetMultiplexPreload(This,fPreload)

#define IStandardMpegMultiplexerProfile_GetMultiplexPreload(This,pfPreload)	\
    (This)->lpVtbl -> GetMultiplexPreload(This,pfPreload)

#define IStandardMpegMultiplexerProfile_SetMultiplexMaxDelay(This,fMaxDelay)	\
    (This)->lpVtbl -> SetMultiplexMaxDelay(This,fMaxDelay)

#define IStandardMpegMultiplexerProfile_SetMultiplexStreams(This,bMux)	\
    (This)->lpVtbl -> SetMultiplexStreams(This,bMux)

#define IStandardMpegMultiplexerProfile_GetMultiplexStreams(This,bMux)	\
    (This)->lpVtbl -> GetMultiplexStreams(This,bMux)

#define IStandardMpegMultiplexerProfile_SetMultiplexFormat(This,format)	\
    (This)->lpVtbl -> SetMultiplexFormat(This,format)

#define IStandardMpegMultiplexerProfile_GetMultiplexFormat(This,format)	\
    (This)->lpVtbl -> GetMultiplexFormat(This,format)

#define IStandardMpegMultiplexerProfile_AddMultiplexFile(This,strPath)	\
    (This)->lpVtbl -> AddMultiplexFile(This,strPath)

#define IStandardMpegMultiplexerProfile_SetOnFlyMultiplex(This,bOnFlyMultiplex)	\
    (This)->lpVtbl -> SetOnFlyMultiplex(This,bOnFlyMultiplex)

#define IStandardMpegMultiplexerProfile_GetOnFlyMultiplex(This,pbOnFlyMultiplex)	\
    (This)->lpVtbl -> GetOnFlyMultiplex(This,pbOnFlyMultiplex)

#define IStandardMpegMultiplexerProfile_SetMultiplexFrameBalance(This,bVal)	\
    (This)->lpVtbl -> SetMultiplexFrameBalance(This,bVal)

#define IStandardMpegMultiplexerProfile_SetMultiplexOnStop(This,bVal)	\
    (This)->lpVtbl -> SetMultiplexOnStop(This,bVal)

#define IStandardMpegMultiplexerProfile_GetMultiplexProgress(This,dProgress)	\
    (This)->lpVtbl -> GetMultiplexProgress(This,dProgress)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IStandardMpegMultiplexerProfile_SetDeleteElementaryStreams_Proxy( 
    IStandardMpegMultiplexerProfile __RPC_FAR * This,
    /* [in] */ BOOL bDelete);


void __RPC_STUB IStandardMpegMultiplexerProfile_SetDeleteElementaryStreams_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegMultiplexerProfile_GetDeleteElementaryStreams_Proxy( 
    IStandardMpegMultiplexerProfile __RPC_FAR * This,
    /* [out] */ BOOL __RPC_FAR *bDelete);


void __RPC_STUB IStandardMpegMultiplexerProfile_GetDeleteElementaryStreams_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegMultiplexerProfile_SetMultiplexRate_Proxy( 
    IStandardMpegMultiplexerProfile __RPC_FAR * This,
    /* [in] */ long nRate);


void __RPC_STUB IStandardMpegMultiplexerProfile_SetMultiplexRate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegMultiplexerProfile_GetMultiplexRate_Proxy( 
    IStandardMpegMultiplexerProfile __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *pnMux);


void __RPC_STUB IStandardMpegMultiplexerProfile_GetMultiplexRate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegMultiplexerProfile_SetMultiplexPacketSize_Proxy( 
    IStandardMpegMultiplexerProfile __RPC_FAR * This,
    /* [in] */ long nSize);


void __RPC_STUB IStandardMpegMultiplexerProfile_SetMultiplexPacketSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegMultiplexerProfile_GetMultiplexPacketSize_Proxy( 
    IStandardMpegMultiplexerProfile __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *pnSize);


void __RPC_STUB IStandardMpegMultiplexerProfile_GetMultiplexPacketSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegMultiplexerProfile_SetMultiplexPreload_Proxy( 
    IStandardMpegMultiplexerProfile __RPC_FAR * This,
    /* [in] */ float fPreload);


void __RPC_STUB IStandardMpegMultiplexerProfile_SetMultiplexPreload_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegMultiplexerProfile_GetMultiplexPreload_Proxy( 
    IStandardMpegMultiplexerProfile __RPC_FAR * This,
    /* [out] */ float __RPC_FAR *pfPreload);


void __RPC_STUB IStandardMpegMultiplexerProfile_GetMultiplexPreload_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegMultiplexerProfile_SetMultiplexMaxDelay_Proxy( 
    IStandardMpegMultiplexerProfile __RPC_FAR * This,
    /* [in] */ float fMaxDelay);


void __RPC_STUB IStandardMpegMultiplexerProfile_SetMultiplexMaxDelay_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegMultiplexerProfile_SetMultiplexStreams_Proxy( 
    IStandardMpegMultiplexerProfile __RPC_FAR * This,
    /* [in] */ BOOL bMux);


void __RPC_STUB IStandardMpegMultiplexerProfile_SetMultiplexStreams_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegMultiplexerProfile_GetMultiplexStreams_Proxy( 
    IStandardMpegMultiplexerProfile __RPC_FAR * This,
    /* [out] */ BOOL __RPC_FAR *bMux);


void __RPC_STUB IStandardMpegMultiplexerProfile_GetMultiplexStreams_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegMultiplexerProfile_SetMultiplexFormat_Proxy( 
    IStandardMpegMultiplexerProfile __RPC_FAR * This,
    /* [in] */ SystemsOutputFormat format);


void __RPC_STUB IStandardMpegMultiplexerProfile_SetMultiplexFormat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegMultiplexerProfile_GetMultiplexFormat_Proxy( 
    IStandardMpegMultiplexerProfile __RPC_FAR * This,
    /* [out] */ SystemsOutputFormat __RPC_FAR *format);


void __RPC_STUB IStandardMpegMultiplexerProfile_GetMultiplexFormat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegMultiplexerProfile_AddMultiplexFile_Proxy( 
    IStandardMpegMultiplexerProfile __RPC_FAR * This,
    /* [in] */ BSTR strPath);


void __RPC_STUB IStandardMpegMultiplexerProfile_AddMultiplexFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegMultiplexerProfile_SetOnFlyMultiplex_Proxy( 
    IStandardMpegMultiplexerProfile __RPC_FAR * This,
    /* [in] */ BOOL bOnFlyMultiplex);


void __RPC_STUB IStandardMpegMultiplexerProfile_SetOnFlyMultiplex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegMultiplexerProfile_GetOnFlyMultiplex_Proxy( 
    IStandardMpegMultiplexerProfile __RPC_FAR * This,
    /* [out] */ BOOL __RPC_FAR *pbOnFlyMultiplex);


void __RPC_STUB IStandardMpegMultiplexerProfile_GetOnFlyMultiplex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegMultiplexerProfile_SetMultiplexFrameBalance_Proxy( 
    IStandardMpegMultiplexerProfile __RPC_FAR * This,
    /* [in] */ BOOL bVal);


void __RPC_STUB IStandardMpegMultiplexerProfile_SetMultiplexFrameBalance_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegMultiplexerProfile_SetMultiplexOnStop_Proxy( 
    IStandardMpegMultiplexerProfile __RPC_FAR * This,
    /* [in] */ BOOL bVal);


void __RPC_STUB IStandardMpegMultiplexerProfile_SetMultiplexOnStop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegMultiplexerProfile_GetMultiplexProgress_Proxy( 
    IStandardMpegMultiplexerProfile __RPC_FAR * This,
    /* [out] */ double __RPC_FAR *dProgress);


void __RPC_STUB IStandardMpegMultiplexerProfile_GetMultiplexProgress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IStandardMpegMultiplexerProfile_INTERFACE_DEFINED__ */


#ifndef __IStandardMpegEncoderProfile_INTERFACE_DEFINED__
#define __IStandardMpegEncoderProfile_INTERFACE_DEFINED__

/* interface IStandardMpegEncoderProfile */
/* [helpstring][unique][dual][uuid][object] */ 


EXTERN_C const IID IID_IStandardMpegEncoderProfile;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("182EB270-5FA5-46e8-83BA-40F7205C545B")
    IStandardMpegEncoderProfile : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SaveProfile( 
            /* [in] */ BSTR strKey) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE LoadProfile( 
            /* [in] */ BSTR strKey) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetProfileName( 
            /* [out] */ BSTR __RPC_FAR *strName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetProfileName( 
            /* [in] */ BSTR strName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetAudioFormat( 
            /* [in] */ AudioOutputFormat audioFormat) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetAudioFormat( 
            /* [out] */ AudioOutputFormat __RPC_FAR *audioFormat) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetVideoFormat( 
            /* [in] */ VideoOutputFormat videoFormat) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetVideoFormat( 
            /* [out] */ VideoOutputFormat __RPC_FAR *videoFormat) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetSystemsFormat( 
            /* [in] */ SystemsOutputFormat systemsFormat) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSystemsFormat( 
            /* [out] */ SystemsOutputFormat __RPC_FAR *systemsFormat) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ConfigureForSystemsFormat( 
            /* [in] */ SystemsOutputFormat systemsFormat,
            /* [in] */ Constraint constraint) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetConstraint( 
            /* [in] */ Constraint systemsConstraint) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetConstraint( 
            /* [out] */ Constraint __RPC_FAR *systemsConstraint) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetAspectRatio( 
            /* [in] */ AspectRatio aspectMode) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetAspectRatio( 
            /* [out] */ AspectRatio __RPC_FAR *pAspectMode) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetAutoSelectDimensions( 
            /* [in] */ BOOL bVal) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetAutoSelectDimensions( 
            /* [out] */ BOOL __RPC_FAR *pbVal) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetWidth( 
            /* [in] */ long nWidth) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetWidth( 
            /* [out] */ long __RPC_FAR *nWidth) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetHeight( 
            /* [out] */ long __RPC_FAR *pnHeight) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetHeight( 
            /* [in] */ long nHeight) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetVideoBitrate( 
            /* [in] */ long nBitrate) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetVideoBitrate( 
            /* [out] */ long __RPC_FAR *nBitrate) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetAutoSelectBitrate( 
            /* [in] */ BOOL bVal) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetAutoSelectBitrate( 
            /* [out] */ BOOL __RPC_FAR *pbVal) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetVideoBitrateMin( 
            /* [in] */ long nBitrate) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetVideoBitrateMin( 
            /* [out] */ long __RPC_FAR *nBitrate) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetVideoBitrateMax( 
            /* [in] */ long nBitrate) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetVideoBitrateMax( 
            /* [out] */ long __RPC_FAR *nBitrate) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetAudioBitrate( 
            /* [in] */ long nBitrate) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetAudioBitrate( 
            /* [out] */ long __RPC_FAR *nBitrate) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetAudioBitrateMin( 
            /* [in] */ long nBitrate) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetAudioBitrateMin( 
            /* [out] */ long __RPC_FAR *nBitrate) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetAudioBitrateMax( 
            /* [in] */ long nBitrate) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetAudioBitrateMax( 
            /* [out] */ long __RPC_FAR *nBitrate) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetVideoQuality( 
            /* [in] */ long nQualityPercent) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetVideoQuality( 
            /* [out] */ long __RPC_FAR *nQualityPercent) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetVideoVBRMode( 
            /* [in] */ BitrateMode vbrMode) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetVideoVBRMode( 
            /* [out] */ BitrateMode __RPC_FAR *pvbrMode) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetVideoVBVBufferSize( 
            /* [in] */ long vbvlen) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetVideoVBVBufferSize( 
            /* [out] */ long __RPC_FAR *vbvlen) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetAudioVBRMode( 
            /* [in] */ BitrateMode vbrMode) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetAudioVBRMode( 
            /* [out] */ BitrateMode __RPC_FAR *pvbrMode) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Set2PassLogFile( 
            /* [in] */ BSTR Path) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetVideoQualityRange( 
            /* [in] */ long nMin,
            /* [in] */ long nMax) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetFramerate( 
            /* [in] */ double fps) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetFramerate( 
            /* [out] */ double __RPC_FAR *fps) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetAudioSampleRate( 
            /* [in] */ long nSampleRate) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetAudioSampleRate( 
            /* [out] */ long __RPC_FAR *pnSampleRate) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetAudioChannels( 
            /* [in] */ long nChannelCount) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetAudioChannels( 
            /* [out] */ long __RPC_FAR *pnChannelCount) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetAudioFlags( 
            /* [in] */ BOOL bErrorProtection,
            /* [in] */ BOOL bOriginal,
            /* [in] */ BOOL bCopyright,
            /* [in] */ BOOL bPrivate) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetComments( 
            /* [in] */ BSTR strVal) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetInformation( 
            /* [in] */ BSTR strTitle,
            /* [in] */ BSTR strAuthor,
            /* [in] */ BSTR strCopyright) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetEncodeMode( 
            /* [in] */ EncodeMode nValue) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetEncodeMode( 
            /* [out] */ EncodeMode __RPC_FAR *pnValue) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetBWVideo( 
            /* [in] */ BOOL bVal) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetGOPSize( 
            /* [in] */ long nGOPSize) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetGOPSize( 
            /* [out] */ long __RPC_FAR *nGOPSize) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetDetectSceneChange( 
            /* [in] */ BOOL bVal) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDetectSceneChange( 
            /* [out] */ BOOL __RPC_FAR *nVal) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetSceneChangeThreshold( 
            /* [in] */ float f) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetClosedGOP( 
            /* [in] */ BOOL bVal) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetClosedGOP( 
            /* [out] */ BOOL __RPC_FAR *nVal) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetOutputIntervalOfSequenceHeader( 
            /* [in] */ long nVal) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetOutputIntervalOfSequenceHeader( 
            /* [in] */ long __RPC_FAR *nVal) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetGOPStructure( 
            /* [in] */ BSTR strStructure) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetGOPStructure( 
            /* [out] */ BSTR __RPC_FAR *pstrStructure) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetStrictGOP( 
            /* [in] */ BOOL bVal) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetProfileAndLevel( 
            /* [in] */ BSTR strProfileAndLevel) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetProfileAndLevel( 
            /* [out] */ BSTR __RPC_FAR *pstrProfileAndLevel) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetMotionSearchPrecision( 
            /* [in] */ long nVal) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMotionSearchPrecision( 
            /* [out] */ long __RPC_FAR *nVal) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetQuantBias( 
            /* [in] */ long nIntra,
            /* [in] */ long nInter) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetIDCT( 
            /* [in] */ long n) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetQuantFactor( 
            /* [in] */ float fQuantFactor) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetQuantFactor( 
            /* [out] */ float __RPC_FAR *pfQuantFactor) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetInterlaceMode( 
            /* [in] */ BOOL bPreProcessDeinterlace,
            /* [in] */ BOOL bInterlacedOutputDCT,
            /* [in] */ BOOL bInterlacedOutputME) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetInterlaceMode( 
            /* [out] */ BOOL __RPC_FAR *bPreProcessDeinterlace,
            /* [out] */ BOOL __RPC_FAR *bInterlacedOutputDCT,
            /* [out] */ BOOL __RPC_FAR *bInterlacedOutputME) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IStandardMpegEncoderProfileVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IStandardMpegEncoderProfile __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IStandardMpegEncoderProfile __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IStandardMpegEncoderProfile __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SaveProfile )( 
            IStandardMpegEncoderProfile __RPC_FAR * This,
            /* [in] */ BSTR strKey);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *LoadProfile )( 
            IStandardMpegEncoderProfile __RPC_FAR * This,
            /* [in] */ BSTR strKey);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetProfileName )( 
            IStandardMpegEncoderProfile __RPC_FAR * This,
            /* [out] */ BSTR __RPC_FAR *strName);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetProfileName )( 
            IStandardMpegEncoderProfile __RPC_FAR * This,
            /* [in] */ BSTR strName);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetAudioFormat )( 
            IStandardMpegEncoderProfile __RPC_FAR * This,
            /* [in] */ AudioOutputFormat audioFormat);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAudioFormat )( 
            IStandardMpegEncoderProfile __RPC_FAR * This,
            /* [out] */ AudioOutputFormat __RPC_FAR *audioFormat);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetVideoFormat )( 
            IStandardMpegEncoderProfile __RPC_FAR * This,
            /* [in] */ VideoOutputFormat videoFormat);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetVideoFormat )( 
            IStandardMpegEncoderProfile __RPC_FAR * This,
            /* [out] */ VideoOutputFormat __RPC_FAR *videoFormat);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetSystemsFormat )( 
            IStandardMpegEncoderProfile __RPC_FAR * This,
            /* [in] */ SystemsOutputFormat systemsFormat);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSystemsFormat )( 
            IStandardMpegEncoderProfile __RPC_FAR * This,
            /* [out] */ SystemsOutputFormat __RPC_FAR *systemsFormat);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ConfigureForSystemsFormat )( 
            IStandardMpegEncoderProfile __RPC_FAR * This,
            /* [in] */ SystemsOutputFormat systemsFormat,
            /* [in] */ Constraint constraint);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetConstraint )( 
            IStandardMpegEncoderProfile __RPC_FAR * This,
            /* [in] */ Constraint systemsConstraint);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetConstraint )( 
            IStandardMpegEncoderProfile __RPC_FAR * This,
            /* [out] */ Constraint __RPC_FAR *systemsConstraint);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetAspectRatio )( 
            IStandardMpegEncoderProfile __RPC_FAR * This,
            /* [in] */ AspectRatio aspectMode);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAspectRatio )( 
            IStandardMpegEncoderProfile __RPC_FAR * This,
            /* [out] */ AspectRatio __RPC_FAR *pAspectMode);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetAutoSelectDimensions )( 
            IStandardMpegEncoderProfile __RPC_FAR * This,
            /* [in] */ BOOL bVal);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAutoSelectDimensions )( 
            IStandardMpegEncoderProfile __RPC_FAR * This,
            /* [out] */ BOOL __RPC_FAR *pbVal);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetWidth )( 
            IStandardMpegEncoderProfile __RPC_FAR * This,
            /* [in] */ long nWidth);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetWidth )( 
            IStandardMpegEncoderProfile __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *nWidth);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetHeight )( 
            IStandardMpegEncoderProfile __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *pnHeight);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetHeight )( 
            IStandardMpegEncoderProfile __RPC_FAR * This,
            /* [in] */ long nHeight);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetVideoBitrate )( 
            IStandardMpegEncoderProfile __RPC_FAR * This,
            /* [in] */ long nBitrate);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetVideoBitrate )( 
            IStandardMpegEncoderProfile __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *nBitrate);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetAutoSelectBitrate )( 
            IStandardMpegEncoderProfile __RPC_FAR * This,
            /* [in] */ BOOL bVal);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAutoSelectBitrate )( 
            IStandardMpegEncoderProfile __RPC_FAR * This,
            /* [out] */ BOOL __RPC_FAR *pbVal);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetVideoBitrateMin )( 
            IStandardMpegEncoderProfile __RPC_FAR * This,
            /* [in] */ long nBitrate);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetVideoBitrateMin )( 
            IStandardMpegEncoderProfile __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *nBitrate);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetVideoBitrateMax )( 
            IStandardMpegEncoderProfile __RPC_FAR * This,
            /* [in] */ long nBitrate);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetVideoBitrateMax )( 
            IStandardMpegEncoderProfile __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *nBitrate);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetAudioBitrate )( 
            IStandardMpegEncoderProfile __RPC_FAR * This,
            /* [in] */ long nBitrate);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAudioBitrate )( 
            IStandardMpegEncoderProfile __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *nBitrate);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetAudioBitrateMin )( 
            IStandardMpegEncoderProfile __RPC_FAR * This,
            /* [in] */ long nBitrate);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAudioBitrateMin )( 
            IStandardMpegEncoderProfile __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *nBitrate);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetAudioBitrateMax )( 
            IStandardMpegEncoderProfile __RPC_FAR * This,
            /* [in] */ long nBitrate);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAudioBitrateMax )( 
            IStandardMpegEncoderProfile __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *nBitrate);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetVideoQuality )( 
            IStandardMpegEncoderProfile __RPC_FAR * This,
            /* [in] */ long nQualityPercent);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetVideoQuality )( 
            IStandardMpegEncoderProfile __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *nQualityPercent);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetVideoVBRMode )( 
            IStandardMpegEncoderProfile __RPC_FAR * This,
            /* [in] */ BitrateMode vbrMode);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetVideoVBRMode )( 
            IStandardMpegEncoderProfile __RPC_FAR * This,
            /* [out] */ BitrateMode __RPC_FAR *pvbrMode);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetVideoVBVBufferSize )( 
            IStandardMpegEncoderProfile __RPC_FAR * This,
            /* [in] */ long vbvlen);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetVideoVBVBufferSize )( 
            IStandardMpegEncoderProfile __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *vbvlen);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetAudioVBRMode )( 
            IStandardMpegEncoderProfile __RPC_FAR * This,
            /* [in] */ BitrateMode vbrMode);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAudioVBRMode )( 
            IStandardMpegEncoderProfile __RPC_FAR * This,
            /* [out] */ BitrateMode __RPC_FAR *pvbrMode);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Set2PassLogFile )( 
            IStandardMpegEncoderProfile __RPC_FAR * This,
            /* [in] */ BSTR Path);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetVideoQualityRange )( 
            IStandardMpegEncoderProfile __RPC_FAR * This,
            /* [in] */ long nMin,
            /* [in] */ long nMax);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetFramerate )( 
            IStandardMpegEncoderProfile __RPC_FAR * This,
            /* [in] */ double fps);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetFramerate )( 
            IStandardMpegEncoderProfile __RPC_FAR * This,
            /* [out] */ double __RPC_FAR *fps);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetAudioSampleRate )( 
            IStandardMpegEncoderProfile __RPC_FAR * This,
            /* [in] */ long nSampleRate);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAudioSampleRate )( 
            IStandardMpegEncoderProfile __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *pnSampleRate);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetAudioChannels )( 
            IStandardMpegEncoderProfile __RPC_FAR * This,
            /* [in] */ long nChannelCount);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAudioChannels )( 
            IStandardMpegEncoderProfile __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *pnChannelCount);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetAudioFlags )( 
            IStandardMpegEncoderProfile __RPC_FAR * This,
            /* [in] */ BOOL bErrorProtection,
            /* [in] */ BOOL bOriginal,
            /* [in] */ BOOL bCopyright,
            /* [in] */ BOOL bPrivate);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetComments )( 
            IStandardMpegEncoderProfile __RPC_FAR * This,
            /* [in] */ BSTR strVal);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetInformation )( 
            IStandardMpegEncoderProfile __RPC_FAR * This,
            /* [in] */ BSTR strTitle,
            /* [in] */ BSTR strAuthor,
            /* [in] */ BSTR strCopyright);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetEncodeMode )( 
            IStandardMpegEncoderProfile __RPC_FAR * This,
            /* [in] */ EncodeMode nValue);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetEncodeMode )( 
            IStandardMpegEncoderProfile __RPC_FAR * This,
            /* [out] */ EncodeMode __RPC_FAR *pnValue);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetBWVideo )( 
            IStandardMpegEncoderProfile __RPC_FAR * This,
            /* [in] */ BOOL bVal);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetGOPSize )( 
            IStandardMpegEncoderProfile __RPC_FAR * This,
            /* [in] */ long nGOPSize);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetGOPSize )( 
            IStandardMpegEncoderProfile __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *nGOPSize);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetDetectSceneChange )( 
            IStandardMpegEncoderProfile __RPC_FAR * This,
            /* [in] */ BOOL bVal);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDetectSceneChange )( 
            IStandardMpegEncoderProfile __RPC_FAR * This,
            /* [out] */ BOOL __RPC_FAR *nVal);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetSceneChangeThreshold )( 
            IStandardMpegEncoderProfile __RPC_FAR * This,
            /* [in] */ float f);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetClosedGOP )( 
            IStandardMpegEncoderProfile __RPC_FAR * This,
            /* [in] */ BOOL bVal);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetClosedGOP )( 
            IStandardMpegEncoderProfile __RPC_FAR * This,
            /* [out] */ BOOL __RPC_FAR *nVal);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetOutputIntervalOfSequenceHeader )( 
            IStandardMpegEncoderProfile __RPC_FAR * This,
            /* [in] */ long nVal);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetOutputIntervalOfSequenceHeader )( 
            IStandardMpegEncoderProfile __RPC_FAR * This,
            /* [in] */ long __RPC_FAR *nVal);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetGOPStructure )( 
            IStandardMpegEncoderProfile __RPC_FAR * This,
            /* [in] */ BSTR strStructure);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetGOPStructure )( 
            IStandardMpegEncoderProfile __RPC_FAR * This,
            /* [out] */ BSTR __RPC_FAR *pstrStructure);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetStrictGOP )( 
            IStandardMpegEncoderProfile __RPC_FAR * This,
            /* [in] */ BOOL bVal);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetProfileAndLevel )( 
            IStandardMpegEncoderProfile __RPC_FAR * This,
            /* [in] */ BSTR strProfileAndLevel);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetProfileAndLevel )( 
            IStandardMpegEncoderProfile __RPC_FAR * This,
            /* [out] */ BSTR __RPC_FAR *pstrProfileAndLevel);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetMotionSearchPrecision )( 
            IStandardMpegEncoderProfile __RPC_FAR * This,
            /* [in] */ long nVal);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMotionSearchPrecision )( 
            IStandardMpegEncoderProfile __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *nVal);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetQuantBias )( 
            IStandardMpegEncoderProfile __RPC_FAR * This,
            /* [in] */ long nIntra,
            /* [in] */ long nInter);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetIDCT )( 
            IStandardMpegEncoderProfile __RPC_FAR * This,
            /* [in] */ long n);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetQuantFactor )( 
            IStandardMpegEncoderProfile __RPC_FAR * This,
            /* [in] */ float fQuantFactor);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetQuantFactor )( 
            IStandardMpegEncoderProfile __RPC_FAR * This,
            /* [out] */ float __RPC_FAR *pfQuantFactor);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetInterlaceMode )( 
            IStandardMpegEncoderProfile __RPC_FAR * This,
            /* [in] */ BOOL bPreProcessDeinterlace,
            /* [in] */ BOOL bInterlacedOutputDCT,
            /* [in] */ BOOL bInterlacedOutputME);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetInterlaceMode )( 
            IStandardMpegEncoderProfile __RPC_FAR * This,
            /* [out] */ BOOL __RPC_FAR *bPreProcessDeinterlace,
            /* [out] */ BOOL __RPC_FAR *bInterlacedOutputDCT,
            /* [out] */ BOOL __RPC_FAR *bInterlacedOutputME);
        
        END_INTERFACE
    } IStandardMpegEncoderProfileVtbl;

    interface IStandardMpegEncoderProfile
    {
        CONST_VTBL struct IStandardMpegEncoderProfileVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IStandardMpegEncoderProfile_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IStandardMpegEncoderProfile_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IStandardMpegEncoderProfile_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IStandardMpegEncoderProfile_SaveProfile(This,strKey)	\
    (This)->lpVtbl -> SaveProfile(This,strKey)

#define IStandardMpegEncoderProfile_LoadProfile(This,strKey)	\
    (This)->lpVtbl -> LoadProfile(This,strKey)

#define IStandardMpegEncoderProfile_GetProfileName(This,strName)	\
    (This)->lpVtbl -> GetProfileName(This,strName)

#define IStandardMpegEncoderProfile_SetProfileName(This,strName)	\
    (This)->lpVtbl -> SetProfileName(This,strName)

#define IStandardMpegEncoderProfile_SetAudioFormat(This,audioFormat)	\
    (This)->lpVtbl -> SetAudioFormat(This,audioFormat)

#define IStandardMpegEncoderProfile_GetAudioFormat(This,audioFormat)	\
    (This)->lpVtbl -> GetAudioFormat(This,audioFormat)

#define IStandardMpegEncoderProfile_SetVideoFormat(This,videoFormat)	\
    (This)->lpVtbl -> SetVideoFormat(This,videoFormat)

#define IStandardMpegEncoderProfile_GetVideoFormat(This,videoFormat)	\
    (This)->lpVtbl -> GetVideoFormat(This,videoFormat)

#define IStandardMpegEncoderProfile_SetSystemsFormat(This,systemsFormat)	\
    (This)->lpVtbl -> SetSystemsFormat(This,systemsFormat)

#define IStandardMpegEncoderProfile_GetSystemsFormat(This,systemsFormat)	\
    (This)->lpVtbl -> GetSystemsFormat(This,systemsFormat)

#define IStandardMpegEncoderProfile_ConfigureForSystemsFormat(This,systemsFormat,constraint)	\
    (This)->lpVtbl -> ConfigureForSystemsFormat(This,systemsFormat,constraint)

#define IStandardMpegEncoderProfile_SetConstraint(This,systemsConstraint)	\
    (This)->lpVtbl -> SetConstraint(This,systemsConstraint)

#define IStandardMpegEncoderProfile_GetConstraint(This,systemsConstraint)	\
    (This)->lpVtbl -> GetConstraint(This,systemsConstraint)

#define IStandardMpegEncoderProfile_SetAspectRatio(This,aspectMode)	\
    (This)->lpVtbl -> SetAspectRatio(This,aspectMode)

#define IStandardMpegEncoderProfile_GetAspectRatio(This,pAspectMode)	\
    (This)->lpVtbl -> GetAspectRatio(This,pAspectMode)

#define IStandardMpegEncoderProfile_SetAutoSelectDimensions(This,bVal)	\
    (This)->lpVtbl -> SetAutoSelectDimensions(This,bVal)

#define IStandardMpegEncoderProfile_GetAutoSelectDimensions(This,pbVal)	\
    (This)->lpVtbl -> GetAutoSelectDimensions(This,pbVal)

#define IStandardMpegEncoderProfile_SetWidth(This,nWidth)	\
    (This)->lpVtbl -> SetWidth(This,nWidth)

#define IStandardMpegEncoderProfile_GetWidth(This,nWidth)	\
    (This)->lpVtbl -> GetWidth(This,nWidth)

#define IStandardMpegEncoderProfile_GetHeight(This,pnHeight)	\
    (This)->lpVtbl -> GetHeight(This,pnHeight)

#define IStandardMpegEncoderProfile_SetHeight(This,nHeight)	\
    (This)->lpVtbl -> SetHeight(This,nHeight)

#define IStandardMpegEncoderProfile_SetVideoBitrate(This,nBitrate)	\
    (This)->lpVtbl -> SetVideoBitrate(This,nBitrate)

#define IStandardMpegEncoderProfile_GetVideoBitrate(This,nBitrate)	\
    (This)->lpVtbl -> GetVideoBitrate(This,nBitrate)

#define IStandardMpegEncoderProfile_SetAutoSelectBitrate(This,bVal)	\
    (This)->lpVtbl -> SetAutoSelectBitrate(This,bVal)

#define IStandardMpegEncoderProfile_GetAutoSelectBitrate(This,pbVal)	\
    (This)->lpVtbl -> GetAutoSelectBitrate(This,pbVal)

#define IStandardMpegEncoderProfile_SetVideoBitrateMin(This,nBitrate)	\
    (This)->lpVtbl -> SetVideoBitrateMin(This,nBitrate)

#define IStandardMpegEncoderProfile_GetVideoBitrateMin(This,nBitrate)	\
    (This)->lpVtbl -> GetVideoBitrateMin(This,nBitrate)

#define IStandardMpegEncoderProfile_SetVideoBitrateMax(This,nBitrate)	\
    (This)->lpVtbl -> SetVideoBitrateMax(This,nBitrate)

#define IStandardMpegEncoderProfile_GetVideoBitrateMax(This,nBitrate)	\
    (This)->lpVtbl -> GetVideoBitrateMax(This,nBitrate)

#define IStandardMpegEncoderProfile_SetAudioBitrate(This,nBitrate)	\
    (This)->lpVtbl -> SetAudioBitrate(This,nBitrate)

#define IStandardMpegEncoderProfile_GetAudioBitrate(This,nBitrate)	\
    (This)->lpVtbl -> GetAudioBitrate(This,nBitrate)

#define IStandardMpegEncoderProfile_SetAudioBitrateMin(This,nBitrate)	\
    (This)->lpVtbl -> SetAudioBitrateMin(This,nBitrate)

#define IStandardMpegEncoderProfile_GetAudioBitrateMin(This,nBitrate)	\
    (This)->lpVtbl -> GetAudioBitrateMin(This,nBitrate)

#define IStandardMpegEncoderProfile_SetAudioBitrateMax(This,nBitrate)	\
    (This)->lpVtbl -> SetAudioBitrateMax(This,nBitrate)

#define IStandardMpegEncoderProfile_GetAudioBitrateMax(This,nBitrate)	\
    (This)->lpVtbl -> GetAudioBitrateMax(This,nBitrate)

#define IStandardMpegEncoderProfile_SetVideoQuality(This,nQualityPercent)	\
    (This)->lpVtbl -> SetVideoQuality(This,nQualityPercent)

#define IStandardMpegEncoderProfile_GetVideoQuality(This,nQualityPercent)	\
    (This)->lpVtbl -> GetVideoQuality(This,nQualityPercent)

#define IStandardMpegEncoderProfile_SetVideoVBRMode(This,vbrMode)	\
    (This)->lpVtbl -> SetVideoVBRMode(This,vbrMode)

#define IStandardMpegEncoderProfile_GetVideoVBRMode(This,pvbrMode)	\
    (This)->lpVtbl -> GetVideoVBRMode(This,pvbrMode)

#define IStandardMpegEncoderProfile_SetVideoVBVBufferSize(This,vbvlen)	\
    (This)->lpVtbl -> SetVideoVBVBufferSize(This,vbvlen)

#define IStandardMpegEncoderProfile_GetVideoVBVBufferSize(This,vbvlen)	\
    (This)->lpVtbl -> GetVideoVBVBufferSize(This,vbvlen)

#define IStandardMpegEncoderProfile_SetAudioVBRMode(This,vbrMode)	\
    (This)->lpVtbl -> SetAudioVBRMode(This,vbrMode)

#define IStandardMpegEncoderProfile_GetAudioVBRMode(This,pvbrMode)	\
    (This)->lpVtbl -> GetAudioVBRMode(This,pvbrMode)

#define IStandardMpegEncoderProfile_Set2PassLogFile(This,Path)	\
    (This)->lpVtbl -> Set2PassLogFile(This,Path)

#define IStandardMpegEncoderProfile_SetVideoQualityRange(This,nMin,nMax)	\
    (This)->lpVtbl -> SetVideoQualityRange(This,nMin,nMax)

#define IStandardMpegEncoderProfile_SetFramerate(This,fps)	\
    (This)->lpVtbl -> SetFramerate(This,fps)

#define IStandardMpegEncoderProfile_GetFramerate(This,fps)	\
    (This)->lpVtbl -> GetFramerate(This,fps)

#define IStandardMpegEncoderProfile_SetAudioSampleRate(This,nSampleRate)	\
    (This)->lpVtbl -> SetAudioSampleRate(This,nSampleRate)

#define IStandardMpegEncoderProfile_GetAudioSampleRate(This,pnSampleRate)	\
    (This)->lpVtbl -> GetAudioSampleRate(This,pnSampleRate)

#define IStandardMpegEncoderProfile_SetAudioChannels(This,nChannelCount)	\
    (This)->lpVtbl -> SetAudioChannels(This,nChannelCount)

#define IStandardMpegEncoderProfile_GetAudioChannels(This,pnChannelCount)	\
    (This)->lpVtbl -> GetAudioChannels(This,pnChannelCount)

#define IStandardMpegEncoderProfile_SetAudioFlags(This,bErrorProtection,bOriginal,bCopyright,bPrivate)	\
    (This)->lpVtbl -> SetAudioFlags(This,bErrorProtection,bOriginal,bCopyright,bPrivate)

#define IStandardMpegEncoderProfile_SetComments(This,strVal)	\
    (This)->lpVtbl -> SetComments(This,strVal)

#define IStandardMpegEncoderProfile_SetInformation(This,strTitle,strAuthor,strCopyright)	\
    (This)->lpVtbl -> SetInformation(This,strTitle,strAuthor,strCopyright)

#define IStandardMpegEncoderProfile_SetEncodeMode(This,nValue)	\
    (This)->lpVtbl -> SetEncodeMode(This,nValue)

#define IStandardMpegEncoderProfile_GetEncodeMode(This,pnValue)	\
    (This)->lpVtbl -> GetEncodeMode(This,pnValue)

#define IStandardMpegEncoderProfile_SetBWVideo(This,bVal)	\
    (This)->lpVtbl -> SetBWVideo(This,bVal)

#define IStandardMpegEncoderProfile_SetGOPSize(This,nGOPSize)	\
    (This)->lpVtbl -> SetGOPSize(This,nGOPSize)

#define IStandardMpegEncoderProfile_GetGOPSize(This,nGOPSize)	\
    (This)->lpVtbl -> GetGOPSize(This,nGOPSize)

#define IStandardMpegEncoderProfile_SetDetectSceneChange(This,bVal)	\
    (This)->lpVtbl -> SetDetectSceneChange(This,bVal)

#define IStandardMpegEncoderProfile_GetDetectSceneChange(This,nVal)	\
    (This)->lpVtbl -> GetDetectSceneChange(This,nVal)

#define IStandardMpegEncoderProfile_SetSceneChangeThreshold(This,f)	\
    (This)->lpVtbl -> SetSceneChangeThreshold(This,f)

#define IStandardMpegEncoderProfile_SetClosedGOP(This,bVal)	\
    (This)->lpVtbl -> SetClosedGOP(This,bVal)

#define IStandardMpegEncoderProfile_GetClosedGOP(This,nVal)	\
    (This)->lpVtbl -> GetClosedGOP(This,nVal)

#define IStandardMpegEncoderProfile_SetOutputIntervalOfSequenceHeader(This,nVal)	\
    (This)->lpVtbl -> SetOutputIntervalOfSequenceHeader(This,nVal)

#define IStandardMpegEncoderProfile_GetOutputIntervalOfSequenceHeader(This,nVal)	\
    (This)->lpVtbl -> GetOutputIntervalOfSequenceHeader(This,nVal)

#define IStandardMpegEncoderProfile_SetGOPStructure(This,strStructure)	\
    (This)->lpVtbl -> SetGOPStructure(This,strStructure)

#define IStandardMpegEncoderProfile_GetGOPStructure(This,pstrStructure)	\
    (This)->lpVtbl -> GetGOPStructure(This,pstrStructure)

#define IStandardMpegEncoderProfile_SetStrictGOP(This,bVal)	\
    (This)->lpVtbl -> SetStrictGOP(This,bVal)

#define IStandardMpegEncoderProfile_SetProfileAndLevel(This,strProfileAndLevel)	\
    (This)->lpVtbl -> SetProfileAndLevel(This,strProfileAndLevel)

#define IStandardMpegEncoderProfile_GetProfileAndLevel(This,pstrProfileAndLevel)	\
    (This)->lpVtbl -> GetProfileAndLevel(This,pstrProfileAndLevel)

#define IStandardMpegEncoderProfile_SetMotionSearchPrecision(This,nVal)	\
    (This)->lpVtbl -> SetMotionSearchPrecision(This,nVal)

#define IStandardMpegEncoderProfile_GetMotionSearchPrecision(This,nVal)	\
    (This)->lpVtbl -> GetMotionSearchPrecision(This,nVal)

#define IStandardMpegEncoderProfile_SetQuantBias(This,nIntra,nInter)	\
    (This)->lpVtbl -> SetQuantBias(This,nIntra,nInter)

#define IStandardMpegEncoderProfile_SetIDCT(This,n)	\
    (This)->lpVtbl -> SetIDCT(This,n)

#define IStandardMpegEncoderProfile_SetQuantFactor(This,fQuantFactor)	\
    (This)->lpVtbl -> SetQuantFactor(This,fQuantFactor)

#define IStandardMpegEncoderProfile_GetQuantFactor(This,pfQuantFactor)	\
    (This)->lpVtbl -> GetQuantFactor(This,pfQuantFactor)

#define IStandardMpegEncoderProfile_SetInterlaceMode(This,bPreProcessDeinterlace,bInterlacedOutputDCT,bInterlacedOutputME)	\
    (This)->lpVtbl -> SetInterlaceMode(This,bPreProcessDeinterlace,bInterlacedOutputDCT,bInterlacedOutputME)

#define IStandardMpegEncoderProfile_GetInterlaceMode(This,bPreProcessDeinterlace,bInterlacedOutputDCT,bInterlacedOutputME)	\
    (This)->lpVtbl -> GetInterlaceMode(This,bPreProcessDeinterlace,bInterlacedOutputDCT,bInterlacedOutputME)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IStandardMpegEncoderProfile_SaveProfile_Proxy( 
    IStandardMpegEncoderProfile __RPC_FAR * This,
    /* [in] */ BSTR strKey);


void __RPC_STUB IStandardMpegEncoderProfile_SaveProfile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegEncoderProfile_LoadProfile_Proxy( 
    IStandardMpegEncoderProfile __RPC_FAR * This,
    /* [in] */ BSTR strKey);


void __RPC_STUB IStandardMpegEncoderProfile_LoadProfile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegEncoderProfile_GetProfileName_Proxy( 
    IStandardMpegEncoderProfile __RPC_FAR * This,
    /* [out] */ BSTR __RPC_FAR *strName);


void __RPC_STUB IStandardMpegEncoderProfile_GetProfileName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegEncoderProfile_SetProfileName_Proxy( 
    IStandardMpegEncoderProfile __RPC_FAR * This,
    /* [in] */ BSTR strName);


void __RPC_STUB IStandardMpegEncoderProfile_SetProfileName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegEncoderProfile_SetAudioFormat_Proxy( 
    IStandardMpegEncoderProfile __RPC_FAR * This,
    /* [in] */ AudioOutputFormat audioFormat);


void __RPC_STUB IStandardMpegEncoderProfile_SetAudioFormat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegEncoderProfile_GetAudioFormat_Proxy( 
    IStandardMpegEncoderProfile __RPC_FAR * This,
    /* [out] */ AudioOutputFormat __RPC_FAR *audioFormat);


void __RPC_STUB IStandardMpegEncoderProfile_GetAudioFormat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegEncoderProfile_SetVideoFormat_Proxy( 
    IStandardMpegEncoderProfile __RPC_FAR * This,
    /* [in] */ VideoOutputFormat videoFormat);


void __RPC_STUB IStandardMpegEncoderProfile_SetVideoFormat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegEncoderProfile_GetVideoFormat_Proxy( 
    IStandardMpegEncoderProfile __RPC_FAR * This,
    /* [out] */ VideoOutputFormat __RPC_FAR *videoFormat);


void __RPC_STUB IStandardMpegEncoderProfile_GetVideoFormat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegEncoderProfile_SetSystemsFormat_Proxy( 
    IStandardMpegEncoderProfile __RPC_FAR * This,
    /* [in] */ SystemsOutputFormat systemsFormat);


void __RPC_STUB IStandardMpegEncoderProfile_SetSystemsFormat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegEncoderProfile_GetSystemsFormat_Proxy( 
    IStandardMpegEncoderProfile __RPC_FAR * This,
    /* [out] */ SystemsOutputFormat __RPC_FAR *systemsFormat);


void __RPC_STUB IStandardMpegEncoderProfile_GetSystemsFormat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegEncoderProfile_ConfigureForSystemsFormat_Proxy( 
    IStandardMpegEncoderProfile __RPC_FAR * This,
    /* [in] */ SystemsOutputFormat systemsFormat,
    /* [in] */ Constraint constraint);


void __RPC_STUB IStandardMpegEncoderProfile_ConfigureForSystemsFormat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegEncoderProfile_SetConstraint_Proxy( 
    IStandardMpegEncoderProfile __RPC_FAR * This,
    /* [in] */ Constraint systemsConstraint);


void __RPC_STUB IStandardMpegEncoderProfile_SetConstraint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegEncoderProfile_GetConstraint_Proxy( 
    IStandardMpegEncoderProfile __RPC_FAR * This,
    /* [out] */ Constraint __RPC_FAR *systemsConstraint);


void __RPC_STUB IStandardMpegEncoderProfile_GetConstraint_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegEncoderProfile_SetAspectRatio_Proxy( 
    IStandardMpegEncoderProfile __RPC_FAR * This,
    /* [in] */ AspectRatio aspectMode);


void __RPC_STUB IStandardMpegEncoderProfile_SetAspectRatio_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegEncoderProfile_GetAspectRatio_Proxy( 
    IStandardMpegEncoderProfile __RPC_FAR * This,
    /* [out] */ AspectRatio __RPC_FAR *pAspectMode);


void __RPC_STUB IStandardMpegEncoderProfile_GetAspectRatio_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegEncoderProfile_SetAutoSelectDimensions_Proxy( 
    IStandardMpegEncoderProfile __RPC_FAR * This,
    /* [in] */ BOOL bVal);


void __RPC_STUB IStandardMpegEncoderProfile_SetAutoSelectDimensions_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegEncoderProfile_GetAutoSelectDimensions_Proxy( 
    IStandardMpegEncoderProfile __RPC_FAR * This,
    /* [out] */ BOOL __RPC_FAR *pbVal);


void __RPC_STUB IStandardMpegEncoderProfile_GetAutoSelectDimensions_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegEncoderProfile_SetWidth_Proxy( 
    IStandardMpegEncoderProfile __RPC_FAR * This,
    /* [in] */ long nWidth);


void __RPC_STUB IStandardMpegEncoderProfile_SetWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegEncoderProfile_GetWidth_Proxy( 
    IStandardMpegEncoderProfile __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *nWidth);


void __RPC_STUB IStandardMpegEncoderProfile_GetWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegEncoderProfile_GetHeight_Proxy( 
    IStandardMpegEncoderProfile __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *pnHeight);


void __RPC_STUB IStandardMpegEncoderProfile_GetHeight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegEncoderProfile_SetHeight_Proxy( 
    IStandardMpegEncoderProfile __RPC_FAR * This,
    /* [in] */ long nHeight);


void __RPC_STUB IStandardMpegEncoderProfile_SetHeight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegEncoderProfile_SetVideoBitrate_Proxy( 
    IStandardMpegEncoderProfile __RPC_FAR * This,
    /* [in] */ long nBitrate);


void __RPC_STUB IStandardMpegEncoderProfile_SetVideoBitrate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegEncoderProfile_GetVideoBitrate_Proxy( 
    IStandardMpegEncoderProfile __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *nBitrate);


void __RPC_STUB IStandardMpegEncoderProfile_GetVideoBitrate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegEncoderProfile_SetAutoSelectBitrate_Proxy( 
    IStandardMpegEncoderProfile __RPC_FAR * This,
    /* [in] */ BOOL bVal);


void __RPC_STUB IStandardMpegEncoderProfile_SetAutoSelectBitrate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegEncoderProfile_GetAutoSelectBitrate_Proxy( 
    IStandardMpegEncoderProfile __RPC_FAR * This,
    /* [out] */ BOOL __RPC_FAR *pbVal);


void __RPC_STUB IStandardMpegEncoderProfile_GetAutoSelectBitrate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegEncoderProfile_SetVideoBitrateMin_Proxy( 
    IStandardMpegEncoderProfile __RPC_FAR * This,
    /* [in] */ long nBitrate);


void __RPC_STUB IStandardMpegEncoderProfile_SetVideoBitrateMin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegEncoderProfile_GetVideoBitrateMin_Proxy( 
    IStandardMpegEncoderProfile __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *nBitrate);


void __RPC_STUB IStandardMpegEncoderProfile_GetVideoBitrateMin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegEncoderProfile_SetVideoBitrateMax_Proxy( 
    IStandardMpegEncoderProfile __RPC_FAR * This,
    /* [in] */ long nBitrate);


void __RPC_STUB IStandardMpegEncoderProfile_SetVideoBitrateMax_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegEncoderProfile_GetVideoBitrateMax_Proxy( 
    IStandardMpegEncoderProfile __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *nBitrate);


void __RPC_STUB IStandardMpegEncoderProfile_GetVideoBitrateMax_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegEncoderProfile_SetAudioBitrate_Proxy( 
    IStandardMpegEncoderProfile __RPC_FAR * This,
    /* [in] */ long nBitrate);


void __RPC_STUB IStandardMpegEncoderProfile_SetAudioBitrate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegEncoderProfile_GetAudioBitrate_Proxy( 
    IStandardMpegEncoderProfile __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *nBitrate);


void __RPC_STUB IStandardMpegEncoderProfile_GetAudioBitrate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegEncoderProfile_SetAudioBitrateMin_Proxy( 
    IStandardMpegEncoderProfile __RPC_FAR * This,
    /* [in] */ long nBitrate);


void __RPC_STUB IStandardMpegEncoderProfile_SetAudioBitrateMin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegEncoderProfile_GetAudioBitrateMin_Proxy( 
    IStandardMpegEncoderProfile __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *nBitrate);


void __RPC_STUB IStandardMpegEncoderProfile_GetAudioBitrateMin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegEncoderProfile_SetAudioBitrateMax_Proxy( 
    IStandardMpegEncoderProfile __RPC_FAR * This,
    /* [in] */ long nBitrate);


void __RPC_STUB IStandardMpegEncoderProfile_SetAudioBitrateMax_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegEncoderProfile_GetAudioBitrateMax_Proxy( 
    IStandardMpegEncoderProfile __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *nBitrate);


void __RPC_STUB IStandardMpegEncoderProfile_GetAudioBitrateMax_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegEncoderProfile_SetVideoQuality_Proxy( 
    IStandardMpegEncoderProfile __RPC_FAR * This,
    /* [in] */ long nQualityPercent);


void __RPC_STUB IStandardMpegEncoderProfile_SetVideoQuality_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegEncoderProfile_GetVideoQuality_Proxy( 
    IStandardMpegEncoderProfile __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *nQualityPercent);


void __RPC_STUB IStandardMpegEncoderProfile_GetVideoQuality_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegEncoderProfile_SetVideoVBRMode_Proxy( 
    IStandardMpegEncoderProfile __RPC_FAR * This,
    /* [in] */ BitrateMode vbrMode);


void __RPC_STUB IStandardMpegEncoderProfile_SetVideoVBRMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegEncoderProfile_GetVideoVBRMode_Proxy( 
    IStandardMpegEncoderProfile __RPC_FAR * This,
    /* [out] */ BitrateMode __RPC_FAR *pvbrMode);


void __RPC_STUB IStandardMpegEncoderProfile_GetVideoVBRMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegEncoderProfile_SetVideoVBVBufferSize_Proxy( 
    IStandardMpegEncoderProfile __RPC_FAR * This,
    /* [in] */ long vbvlen);


void __RPC_STUB IStandardMpegEncoderProfile_SetVideoVBVBufferSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegEncoderProfile_GetVideoVBVBufferSize_Proxy( 
    IStandardMpegEncoderProfile __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *vbvlen);


void __RPC_STUB IStandardMpegEncoderProfile_GetVideoVBVBufferSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegEncoderProfile_SetAudioVBRMode_Proxy( 
    IStandardMpegEncoderProfile __RPC_FAR * This,
    /* [in] */ BitrateMode vbrMode);


void __RPC_STUB IStandardMpegEncoderProfile_SetAudioVBRMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegEncoderProfile_GetAudioVBRMode_Proxy( 
    IStandardMpegEncoderProfile __RPC_FAR * This,
    /* [out] */ BitrateMode __RPC_FAR *pvbrMode);


void __RPC_STUB IStandardMpegEncoderProfile_GetAudioVBRMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegEncoderProfile_Set2PassLogFile_Proxy( 
    IStandardMpegEncoderProfile __RPC_FAR * This,
    /* [in] */ BSTR Path);


void __RPC_STUB IStandardMpegEncoderProfile_Set2PassLogFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegEncoderProfile_SetVideoQualityRange_Proxy( 
    IStandardMpegEncoderProfile __RPC_FAR * This,
    /* [in] */ long nMin,
    /* [in] */ long nMax);


void __RPC_STUB IStandardMpegEncoderProfile_SetVideoQualityRange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegEncoderProfile_SetFramerate_Proxy( 
    IStandardMpegEncoderProfile __RPC_FAR * This,
    /* [in] */ double fps);


void __RPC_STUB IStandardMpegEncoderProfile_SetFramerate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegEncoderProfile_GetFramerate_Proxy( 
    IStandardMpegEncoderProfile __RPC_FAR * This,
    /* [out] */ double __RPC_FAR *fps);


void __RPC_STUB IStandardMpegEncoderProfile_GetFramerate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegEncoderProfile_SetAudioSampleRate_Proxy( 
    IStandardMpegEncoderProfile __RPC_FAR * This,
    /* [in] */ long nSampleRate);


void __RPC_STUB IStandardMpegEncoderProfile_SetAudioSampleRate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegEncoderProfile_GetAudioSampleRate_Proxy( 
    IStandardMpegEncoderProfile __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *pnSampleRate);


void __RPC_STUB IStandardMpegEncoderProfile_GetAudioSampleRate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegEncoderProfile_SetAudioChannels_Proxy( 
    IStandardMpegEncoderProfile __RPC_FAR * This,
    /* [in] */ long nChannelCount);


void __RPC_STUB IStandardMpegEncoderProfile_SetAudioChannels_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegEncoderProfile_GetAudioChannels_Proxy( 
    IStandardMpegEncoderProfile __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *pnChannelCount);


void __RPC_STUB IStandardMpegEncoderProfile_GetAudioChannels_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegEncoderProfile_SetAudioFlags_Proxy( 
    IStandardMpegEncoderProfile __RPC_FAR * This,
    /* [in] */ BOOL bErrorProtection,
    /* [in] */ BOOL bOriginal,
    /* [in] */ BOOL bCopyright,
    /* [in] */ BOOL bPrivate);


void __RPC_STUB IStandardMpegEncoderProfile_SetAudioFlags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegEncoderProfile_SetComments_Proxy( 
    IStandardMpegEncoderProfile __RPC_FAR * This,
    /* [in] */ BSTR strVal);


void __RPC_STUB IStandardMpegEncoderProfile_SetComments_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegEncoderProfile_SetInformation_Proxy( 
    IStandardMpegEncoderProfile __RPC_FAR * This,
    /* [in] */ BSTR strTitle,
    /* [in] */ BSTR strAuthor,
    /* [in] */ BSTR strCopyright);


void __RPC_STUB IStandardMpegEncoderProfile_SetInformation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegEncoderProfile_SetEncodeMode_Proxy( 
    IStandardMpegEncoderProfile __RPC_FAR * This,
    /* [in] */ EncodeMode nValue);


void __RPC_STUB IStandardMpegEncoderProfile_SetEncodeMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegEncoderProfile_GetEncodeMode_Proxy( 
    IStandardMpegEncoderProfile __RPC_FAR * This,
    /* [out] */ EncodeMode __RPC_FAR *pnValue);


void __RPC_STUB IStandardMpegEncoderProfile_GetEncodeMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegEncoderProfile_SetBWVideo_Proxy( 
    IStandardMpegEncoderProfile __RPC_FAR * This,
    /* [in] */ BOOL bVal);


void __RPC_STUB IStandardMpegEncoderProfile_SetBWVideo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegEncoderProfile_SetGOPSize_Proxy( 
    IStandardMpegEncoderProfile __RPC_FAR * This,
    /* [in] */ long nGOPSize);


void __RPC_STUB IStandardMpegEncoderProfile_SetGOPSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegEncoderProfile_GetGOPSize_Proxy( 
    IStandardMpegEncoderProfile __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *nGOPSize);


void __RPC_STUB IStandardMpegEncoderProfile_GetGOPSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegEncoderProfile_SetDetectSceneChange_Proxy( 
    IStandardMpegEncoderProfile __RPC_FAR * This,
    /* [in] */ BOOL bVal);


void __RPC_STUB IStandardMpegEncoderProfile_SetDetectSceneChange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegEncoderProfile_GetDetectSceneChange_Proxy( 
    IStandardMpegEncoderProfile __RPC_FAR * This,
    /* [out] */ BOOL __RPC_FAR *nVal);


void __RPC_STUB IStandardMpegEncoderProfile_GetDetectSceneChange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegEncoderProfile_SetSceneChangeThreshold_Proxy( 
    IStandardMpegEncoderProfile __RPC_FAR * This,
    /* [in] */ float f);


void __RPC_STUB IStandardMpegEncoderProfile_SetSceneChangeThreshold_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegEncoderProfile_SetClosedGOP_Proxy( 
    IStandardMpegEncoderProfile __RPC_FAR * This,
    /* [in] */ BOOL bVal);


void __RPC_STUB IStandardMpegEncoderProfile_SetClosedGOP_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegEncoderProfile_GetClosedGOP_Proxy( 
    IStandardMpegEncoderProfile __RPC_FAR * This,
    /* [out] */ BOOL __RPC_FAR *nVal);


void __RPC_STUB IStandardMpegEncoderProfile_GetClosedGOP_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegEncoderProfile_SetOutputIntervalOfSequenceHeader_Proxy( 
    IStandardMpegEncoderProfile __RPC_FAR * This,
    /* [in] */ long nVal);


void __RPC_STUB IStandardMpegEncoderProfile_SetOutputIntervalOfSequenceHeader_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegEncoderProfile_GetOutputIntervalOfSequenceHeader_Proxy( 
    IStandardMpegEncoderProfile __RPC_FAR * This,
    /* [in] */ long __RPC_FAR *nVal);


void __RPC_STUB IStandardMpegEncoderProfile_GetOutputIntervalOfSequenceHeader_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegEncoderProfile_SetGOPStructure_Proxy( 
    IStandardMpegEncoderProfile __RPC_FAR * This,
    /* [in] */ BSTR strStructure);


void __RPC_STUB IStandardMpegEncoderProfile_SetGOPStructure_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegEncoderProfile_GetGOPStructure_Proxy( 
    IStandardMpegEncoderProfile __RPC_FAR * This,
    /* [out] */ BSTR __RPC_FAR *pstrStructure);


void __RPC_STUB IStandardMpegEncoderProfile_GetGOPStructure_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegEncoderProfile_SetStrictGOP_Proxy( 
    IStandardMpegEncoderProfile __RPC_FAR * This,
    /* [in] */ BOOL bVal);


void __RPC_STUB IStandardMpegEncoderProfile_SetStrictGOP_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegEncoderProfile_SetProfileAndLevel_Proxy( 
    IStandardMpegEncoderProfile __RPC_FAR * This,
    /* [in] */ BSTR strProfileAndLevel);


void __RPC_STUB IStandardMpegEncoderProfile_SetProfileAndLevel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegEncoderProfile_GetProfileAndLevel_Proxy( 
    IStandardMpegEncoderProfile __RPC_FAR * This,
    /* [out] */ BSTR __RPC_FAR *pstrProfileAndLevel);


void __RPC_STUB IStandardMpegEncoderProfile_GetProfileAndLevel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegEncoderProfile_SetMotionSearchPrecision_Proxy( 
    IStandardMpegEncoderProfile __RPC_FAR * This,
    /* [in] */ long nVal);


void __RPC_STUB IStandardMpegEncoderProfile_SetMotionSearchPrecision_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegEncoderProfile_GetMotionSearchPrecision_Proxy( 
    IStandardMpegEncoderProfile __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *nVal);


void __RPC_STUB IStandardMpegEncoderProfile_GetMotionSearchPrecision_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegEncoderProfile_SetQuantBias_Proxy( 
    IStandardMpegEncoderProfile __RPC_FAR * This,
    /* [in] */ long nIntra,
    /* [in] */ long nInter);


void __RPC_STUB IStandardMpegEncoderProfile_SetQuantBias_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegEncoderProfile_SetIDCT_Proxy( 
    IStandardMpegEncoderProfile __RPC_FAR * This,
    /* [in] */ long n);


void __RPC_STUB IStandardMpegEncoderProfile_SetIDCT_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegEncoderProfile_SetQuantFactor_Proxy( 
    IStandardMpegEncoderProfile __RPC_FAR * This,
    /* [in] */ float fQuantFactor);


void __RPC_STUB IStandardMpegEncoderProfile_SetQuantFactor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegEncoderProfile_GetQuantFactor_Proxy( 
    IStandardMpegEncoderProfile __RPC_FAR * This,
    /* [out] */ float __RPC_FAR *pfQuantFactor);


void __RPC_STUB IStandardMpegEncoderProfile_GetQuantFactor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegEncoderProfile_SetInterlaceMode_Proxy( 
    IStandardMpegEncoderProfile __RPC_FAR * This,
    /* [in] */ BOOL bPreProcessDeinterlace,
    /* [in] */ BOOL bInterlacedOutputDCT,
    /* [in] */ BOOL bInterlacedOutputME);


void __RPC_STUB IStandardMpegEncoderProfile_SetInterlaceMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegEncoderProfile_GetInterlaceMode_Proxy( 
    IStandardMpegEncoderProfile __RPC_FAR * This,
    /* [out] */ BOOL __RPC_FAR *bPreProcessDeinterlace,
    /* [out] */ BOOL __RPC_FAR *bInterlacedOutputDCT,
    /* [out] */ BOOL __RPC_FAR *bInterlacedOutputME);


void __RPC_STUB IStandardMpegEncoderProfile_GetInterlaceMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IStandardMpegEncoderProfile_INTERFACE_DEFINED__ */


#ifndef __IStandardMpegEncoderStats_INTERFACE_DEFINED__
#define __IStandardMpegEncoderStats_INTERFACE_DEFINED__

/* interface IStandardMpegEncoderStats */
/* [helpstring][unique][dual][uuid][object] */ 


EXTERN_C const IID IID_IStandardMpegEncoderStats;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C9510218-F457-4d51-8389-7386E6EDD0EF")
    IStandardMpegEncoderStats : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetFramesEncoded( 
            /* [out] */ long __RPC_FAR *lFramesEncoded) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetVideoFramesDropped( 
            /* [out] */ long __RPC_FAR *lFramesDropped) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetAudioTimeCorrected( 
            /* [out] */ double __RPC_FAR *dTimeCorrected) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetWrittenBytes( 
            /* [out] */ long __RPC_FAR *lBytesWritten) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetStatusString( 
            /* [out] */ BSTR __RPC_FAR *strValue) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IStandardMpegEncoderStatsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IStandardMpegEncoderStats __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IStandardMpegEncoderStats __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IStandardMpegEncoderStats __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetFramesEncoded )( 
            IStandardMpegEncoderStats __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *lFramesEncoded);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetVideoFramesDropped )( 
            IStandardMpegEncoderStats __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *lFramesDropped);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAudioTimeCorrected )( 
            IStandardMpegEncoderStats __RPC_FAR * This,
            /* [out] */ double __RPC_FAR *dTimeCorrected);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetWrittenBytes )( 
            IStandardMpegEncoderStats __RPC_FAR * This,
            /* [out] */ long __RPC_FAR *lBytesWritten);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetStatusString )( 
            IStandardMpegEncoderStats __RPC_FAR * This,
            /* [out] */ BSTR __RPC_FAR *strValue);
        
        END_INTERFACE
    } IStandardMpegEncoderStatsVtbl;

    interface IStandardMpegEncoderStats
    {
        CONST_VTBL struct IStandardMpegEncoderStatsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IStandardMpegEncoderStats_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IStandardMpegEncoderStats_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IStandardMpegEncoderStats_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IStandardMpegEncoderStats_GetFramesEncoded(This,lFramesEncoded)	\
    (This)->lpVtbl -> GetFramesEncoded(This,lFramesEncoded)

#define IStandardMpegEncoderStats_GetVideoFramesDropped(This,lFramesDropped)	\
    (This)->lpVtbl -> GetVideoFramesDropped(This,lFramesDropped)

#define IStandardMpegEncoderStats_GetAudioTimeCorrected(This,dTimeCorrected)	\
    (This)->lpVtbl -> GetAudioTimeCorrected(This,dTimeCorrected)

#define IStandardMpegEncoderStats_GetWrittenBytes(This,lBytesWritten)	\
    (This)->lpVtbl -> GetWrittenBytes(This,lBytesWritten)

#define IStandardMpegEncoderStats_GetStatusString(This,strValue)	\
    (This)->lpVtbl -> GetStatusString(This,strValue)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IStandardMpegEncoderStats_GetFramesEncoded_Proxy( 
    IStandardMpegEncoderStats __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *lFramesEncoded);


void __RPC_STUB IStandardMpegEncoderStats_GetFramesEncoded_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegEncoderStats_GetVideoFramesDropped_Proxy( 
    IStandardMpegEncoderStats __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *lFramesDropped);


void __RPC_STUB IStandardMpegEncoderStats_GetVideoFramesDropped_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegEncoderStats_GetAudioTimeCorrected_Proxy( 
    IStandardMpegEncoderStats __RPC_FAR * This,
    /* [out] */ double __RPC_FAR *dTimeCorrected);


void __RPC_STUB IStandardMpegEncoderStats_GetAudioTimeCorrected_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegEncoderStats_GetWrittenBytes_Proxy( 
    IStandardMpegEncoderStats __RPC_FAR * This,
    /* [out] */ long __RPC_FAR *lBytesWritten);


void __RPC_STUB IStandardMpegEncoderStats_GetWrittenBytes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegEncoderStats_GetStatusString_Proxy( 
    IStandardMpegEncoderStats __RPC_FAR * This,
    /* [out] */ BSTR __RPC_FAR *strValue);


void __RPC_STUB IStandardMpegEncoderStats_GetStatusString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IStandardMpegEncoderStats_INTERFACE_DEFINED__ */


#ifndef __IStandardMpegEncoder_INTERFACE_DEFINED__
#define __IStandardMpegEncoder_INTERFACE_DEFINED__

/* interface IStandardMpegEncoder */
/* [helpstring][unique][dual][uuid][object] */ 


EXTERN_C const IID IID_IStandardMpegEncoder;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("91D3D934-6DEE-42c5-A687-6F81E1162559")
    IStandardMpegEncoder : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetProfile( 
            /* [in] */ SystemsOutputFormat systemsFormat,
            /* [in] */ Constraint constraint,
            /* [out] */ IStandardMpegEncoderProfile __RPC_FAR *__RPC_FAR *pProfile) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSelectedProfile( 
            /* [out] */ IStandardMpegEncoderProfile __RPC_FAR *__RPC_FAR *pProfile) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SelectProfile( 
            /* [in] */ IStandardMpegEncoderProfile __RPC_FAR *pProfile) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SelectFormat( 
            /* [in] */ SystemsOutputFormat systemsFormat,
            /* [in] */ Constraint constraint) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetFilterLicenseKey( 
            /* [in] */ BSTR strLicense) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SaveSettings( 
            /* [in] */ BSTR strKey) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE LoadSettings( 
            /* [in] */ BSTR strKey) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PassThruCmd( 
            /* [in] */ BSTR strCmd,
            /* [in] */ long nCmd,
            /* [in] */ double dCmd,
            /* [out] */ BYTE __RPC_FAR *pCmd) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetErrorBoxDisplay( 
            /* [in] */ BOOL bVal) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetPass( 
            /* [in] */ long n) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetSourceFramerate( 
            /* [in] */ double dSourceFramerate,
            /* [out] */ double __RPC_FAR *dRequiredInputFramerate) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ActivateAudioVideoOutputPins( 
            /* [in] */ BOOL bVal) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetAudioVideoOutputPinsActivated( 
            /* [out] */ BOOL __RPC_FAR *bVal) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE EnableFramerateCorrection( 
            /* [in] */ BOOL bCorrectVideo,
            /* [in] */ BOOL bCorrectAudio) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IStandardMpegEncoderVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IStandardMpegEncoder __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IStandardMpegEncoder __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IStandardMpegEncoder __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetProfile )( 
            IStandardMpegEncoder __RPC_FAR * This,
            /* [in] */ SystemsOutputFormat systemsFormat,
            /* [in] */ Constraint constraint,
            /* [out] */ IStandardMpegEncoderProfile __RPC_FAR *__RPC_FAR *pProfile);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSelectedProfile )( 
            IStandardMpegEncoder __RPC_FAR * This,
            /* [out] */ IStandardMpegEncoderProfile __RPC_FAR *__RPC_FAR *pProfile);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SelectProfile )( 
            IStandardMpegEncoder __RPC_FAR * This,
            /* [in] */ IStandardMpegEncoderProfile __RPC_FAR *pProfile);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SelectFormat )( 
            IStandardMpegEncoder __RPC_FAR * This,
            /* [in] */ SystemsOutputFormat systemsFormat,
            /* [in] */ Constraint constraint);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetFilterLicenseKey )( 
            IStandardMpegEncoder __RPC_FAR * This,
            /* [in] */ BSTR strLicense);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SaveSettings )( 
            IStandardMpegEncoder __RPC_FAR * This,
            /* [in] */ BSTR strKey);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *LoadSettings )( 
            IStandardMpegEncoder __RPC_FAR * This,
            /* [in] */ BSTR strKey);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PassThruCmd )( 
            IStandardMpegEncoder __RPC_FAR * This,
            /* [in] */ BSTR strCmd,
            /* [in] */ long nCmd,
            /* [in] */ double dCmd,
            /* [out] */ BYTE __RPC_FAR *pCmd);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetErrorBoxDisplay )( 
            IStandardMpegEncoder __RPC_FAR * This,
            /* [in] */ BOOL bVal);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetPass )( 
            IStandardMpegEncoder __RPC_FAR * This,
            /* [in] */ long n);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetSourceFramerate )( 
            IStandardMpegEncoder __RPC_FAR * This,
            /* [in] */ double dSourceFramerate,
            /* [out] */ double __RPC_FAR *dRequiredInputFramerate);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ActivateAudioVideoOutputPins )( 
            IStandardMpegEncoder __RPC_FAR * This,
            /* [in] */ BOOL bVal);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAudioVideoOutputPinsActivated )( 
            IStandardMpegEncoder __RPC_FAR * This,
            /* [out] */ BOOL __RPC_FAR *bVal);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnableFramerateCorrection )( 
            IStandardMpegEncoder __RPC_FAR * This,
            /* [in] */ BOOL bCorrectVideo,
            /* [in] */ BOOL bCorrectAudio);
        
        END_INTERFACE
    } IStandardMpegEncoderVtbl;

    interface IStandardMpegEncoder
    {
        CONST_VTBL struct IStandardMpegEncoderVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IStandardMpegEncoder_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IStandardMpegEncoder_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IStandardMpegEncoder_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IStandardMpegEncoder_GetProfile(This,systemsFormat,constraint,pProfile)	\
    (This)->lpVtbl -> GetProfile(This,systemsFormat,constraint,pProfile)

#define IStandardMpegEncoder_GetSelectedProfile(This,pProfile)	\
    (This)->lpVtbl -> GetSelectedProfile(This,pProfile)

#define IStandardMpegEncoder_SelectProfile(This,pProfile)	\
    (This)->lpVtbl -> SelectProfile(This,pProfile)

#define IStandardMpegEncoder_SelectFormat(This,systemsFormat,constraint)	\
    (This)->lpVtbl -> SelectFormat(This,systemsFormat,constraint)

#define IStandardMpegEncoder_SetFilterLicenseKey(This,strLicense)	\
    (This)->lpVtbl -> SetFilterLicenseKey(This,strLicense)

#define IStandardMpegEncoder_SaveSettings(This,strKey)	\
    (This)->lpVtbl -> SaveSettings(This,strKey)

#define IStandardMpegEncoder_LoadSettings(This,strKey)	\
    (This)->lpVtbl -> LoadSettings(This,strKey)

#define IStandardMpegEncoder_PassThruCmd(This,strCmd,nCmd,dCmd,pCmd)	\
    (This)->lpVtbl -> PassThruCmd(This,strCmd,nCmd,dCmd,pCmd)

#define IStandardMpegEncoder_SetErrorBoxDisplay(This,bVal)	\
    (This)->lpVtbl -> SetErrorBoxDisplay(This,bVal)

#define IStandardMpegEncoder_SetPass(This,n)	\
    (This)->lpVtbl -> SetPass(This,n)

#define IStandardMpegEncoder_SetSourceFramerate(This,dSourceFramerate,dRequiredInputFramerate)	\
    (This)->lpVtbl -> SetSourceFramerate(This,dSourceFramerate,dRequiredInputFramerate)

#define IStandardMpegEncoder_ActivateAudioVideoOutputPins(This,bVal)	\
    (This)->lpVtbl -> ActivateAudioVideoOutputPins(This,bVal)

#define IStandardMpegEncoder_GetAudioVideoOutputPinsActivated(This,bVal)	\
    (This)->lpVtbl -> GetAudioVideoOutputPinsActivated(This,bVal)

#define IStandardMpegEncoder_EnableFramerateCorrection(This,bCorrectVideo,bCorrectAudio)	\
    (This)->lpVtbl -> EnableFramerateCorrection(This,bCorrectVideo,bCorrectAudio)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IStandardMpegEncoder_GetProfile_Proxy( 
    IStandardMpegEncoder __RPC_FAR * This,
    /* [in] */ SystemsOutputFormat systemsFormat,
    /* [in] */ Constraint constraint,
    /* [out] */ IStandardMpegEncoderProfile __RPC_FAR *__RPC_FAR *pProfile);


void __RPC_STUB IStandardMpegEncoder_GetProfile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegEncoder_GetSelectedProfile_Proxy( 
    IStandardMpegEncoder __RPC_FAR * This,
    /* [out] */ IStandardMpegEncoderProfile __RPC_FAR *__RPC_FAR *pProfile);


void __RPC_STUB IStandardMpegEncoder_GetSelectedProfile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegEncoder_SelectProfile_Proxy( 
    IStandardMpegEncoder __RPC_FAR * This,
    /* [in] */ IStandardMpegEncoderProfile __RPC_FAR *pProfile);


void __RPC_STUB IStandardMpegEncoder_SelectProfile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegEncoder_SelectFormat_Proxy( 
    IStandardMpegEncoder __RPC_FAR * This,
    /* [in] */ SystemsOutputFormat systemsFormat,
    /* [in] */ Constraint constraint);


void __RPC_STUB IStandardMpegEncoder_SelectFormat_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegEncoder_SetFilterLicenseKey_Proxy( 
    IStandardMpegEncoder __RPC_FAR * This,
    /* [in] */ BSTR strLicense);


void __RPC_STUB IStandardMpegEncoder_SetFilterLicenseKey_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegEncoder_SaveSettings_Proxy( 
    IStandardMpegEncoder __RPC_FAR * This,
    /* [in] */ BSTR strKey);


void __RPC_STUB IStandardMpegEncoder_SaveSettings_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegEncoder_LoadSettings_Proxy( 
    IStandardMpegEncoder __RPC_FAR * This,
    /* [in] */ BSTR strKey);


void __RPC_STUB IStandardMpegEncoder_LoadSettings_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegEncoder_PassThruCmd_Proxy( 
    IStandardMpegEncoder __RPC_FAR * This,
    /* [in] */ BSTR strCmd,
    /* [in] */ long nCmd,
    /* [in] */ double dCmd,
    /* [out] */ BYTE __RPC_FAR *pCmd);


void __RPC_STUB IStandardMpegEncoder_PassThruCmd_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegEncoder_SetErrorBoxDisplay_Proxy( 
    IStandardMpegEncoder __RPC_FAR * This,
    /* [in] */ BOOL bVal);


void __RPC_STUB IStandardMpegEncoder_SetErrorBoxDisplay_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegEncoder_SetPass_Proxy( 
    IStandardMpegEncoder __RPC_FAR * This,
    /* [in] */ long n);


void __RPC_STUB IStandardMpegEncoder_SetPass_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegEncoder_SetSourceFramerate_Proxy( 
    IStandardMpegEncoder __RPC_FAR * This,
    /* [in] */ double dSourceFramerate,
    /* [out] */ double __RPC_FAR *dRequiredInputFramerate);


void __RPC_STUB IStandardMpegEncoder_SetSourceFramerate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegEncoder_ActivateAudioVideoOutputPins_Proxy( 
    IStandardMpegEncoder __RPC_FAR * This,
    /* [in] */ BOOL bVal);


void __RPC_STUB IStandardMpegEncoder_ActivateAudioVideoOutputPins_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegEncoder_GetAudioVideoOutputPinsActivated_Proxy( 
    IStandardMpegEncoder __RPC_FAR * This,
    /* [out] */ BOOL __RPC_FAR *bVal);


void __RPC_STUB IStandardMpegEncoder_GetAudioVideoOutputPinsActivated_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IStandardMpegEncoder_EnableFramerateCorrection_Proxy( 
    IStandardMpegEncoder __RPC_FAR * This,
    /* [in] */ BOOL bCorrectVideo,
    /* [in] */ BOOL bCorrectAudio);


void __RPC_STUB IStandardMpegEncoder_EnableFramerateCorrection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IStandardMpegEncoder_INTERFACE_DEFINED__ */



#ifndef __StandardMpegEncoderLib_LIBRARY_DEFINED__
#define __StandardMpegEncoderLib_LIBRARY_DEFINED__

/* library StandardMpegEncoderLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_StandardMpegEncoderLib;

EXTERN_C const CLSID CLSID_StandardMpegEncoder;

#ifdef __cplusplus

class DECLSPEC_UUID("CFD87339-C61F-46ca-B6A1-F87D6B96243E")
StandardMpegEncoder;
#endif

EXTERN_C const CLSID CLSID_StandardMpegEncoderStats;

#ifdef __cplusplus

class DECLSPEC_UUID("1C356305-4D1C-45e1-AA93-1AE16C7DE429")
StandardMpegEncoderStats;
#endif

EXTERN_C const CLSID CLSID_StandardMpegEncoderProfile;

#ifdef __cplusplus

class DECLSPEC_UUID("D4D68F8A-B665-41d4-94D1-E8843001E346")
StandardMpegEncoderProfile;
#endif

EXTERN_C const CLSID CLSID_StandardMpegMultiplexerProfile;

#ifdef __cplusplus

class DECLSPEC_UUID("022A32A5-3689-4d5f-B8CC-C26655C2BA03")
StandardMpegMultiplexerProfile;
#endif

EXTERN_C const CLSID CLSID_StandardMpegEncoderGeneralProps;

#ifdef __cplusplus

class DECLSPEC_UUID("4A6D5C73-270C-4c05-871A-28230F2A8BCC")
StandardMpegEncoderGeneralProps;
#endif

EXTERN_C const CLSID CLSID_StandardMpegEncoderVideoProps;

#ifdef __cplusplus

class DECLSPEC_UUID("DCD4E0B0-FE55-44c6-9B4C-1E78FA2D6D2C")
StandardMpegEncoderVideoProps;
#endif

EXTERN_C const CLSID CLSID_StandardMpegEncoderAudioProps;

#ifdef __cplusplus

class DECLSPEC_UUID("BDB70B23-BAA7-44a5-8CB5-A3F5F34865C8")
StandardMpegEncoderAudioProps;
#endif
#endif /* __StandardMpegEncoderLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long __RPC_FAR *, unsigned long            , BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long __RPC_FAR *, BSTR __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
