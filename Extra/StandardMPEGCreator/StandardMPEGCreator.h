/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue Sep 09 11:04:08 2008
 */
/* Compiler settings for Z:\Development\DirectEncode\StandardMPEGCreator\StandardMPEGCreator.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __StandardMPEGCreator_h__
#define __StandardMPEGCreator_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef ___IMPEGConverterEvents_FWD_DEFINED__
#define ___IMPEGConverterEvents_FWD_DEFINED__
typedef interface _IMPEGConverterEvents _IMPEGConverterEvents;
#endif 	/* ___IMPEGConverterEvents_FWD_DEFINED__ */


#ifndef __IStatistics_FWD_DEFINED__
#define __IStatistics_FWD_DEFINED__
typedef interface IStatistics IStatistics;
#endif 	/* __IStatistics_FWD_DEFINED__ */


#ifndef __ISettings_FWD_DEFINED__
#define __ISettings_FWD_DEFINED__
typedef interface ISettings ISettings;
#endif 	/* __ISettings_FWD_DEFINED__ */


#ifndef __IMPEGConverter_FWD_DEFINED__
#define __IMPEGConverter_FWD_DEFINED__
typedef interface IMPEGConverter IMPEGConverter;
#endif 	/* __IMPEGConverter_FWD_DEFINED__ */


#ifndef __MPEGConverter_FWD_DEFINED__
#define __MPEGConverter_FWD_DEFINED__

#ifdef __cplusplus
typedef class MPEGConverter MPEGConverter;
#else
typedef struct MPEGConverter MPEGConverter;
#endif /* __cplusplus */

#endif 	/* __MPEGConverter_FWD_DEFINED__ */


#ifndef __Statistics_FWD_DEFINED__
#define __Statistics_FWD_DEFINED__

#ifdef __cplusplus
typedef class Statistics Statistics;
#else
typedef struct Statistics Statistics;
#endif /* __cplusplus */

#endif 	/* __Statistics_FWD_DEFINED__ */


#ifndef __Settings_FWD_DEFINED__
#define __Settings_FWD_DEFINED__

#ifdef __cplusplus
typedef class Settings Settings;
#else
typedef struct Settings Settings;
#endif /* __cplusplus */

#endif 	/* __Settings_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_StandardMPEGCreator_0000 */
/* [local] */ 

typedef /* [public] */ 
enum _VideoOutputFormat
    {	VIDEOFORMAT_NONE	= 0,
	VIDEOFORMAT_MPEG1	= VIDEOFORMAT_NONE + 1,
	VIDEOFORMAT_MPEG2	= VIDEOFORMAT_MPEG1 + 1,
	VIDEOFORMAT_MPEG4	= VIDEOFORMAT_MPEG2 + 1,
	VIDEOFORMAT_H263	= VIDEOFORMAT_MPEG4 + 1,
	VIDEOFORMAT_H264	= VIDEOFORMAT_H263 + 1,
	VIDEOFORMAT_FLV	= VIDEOFORMAT_H264 + 1
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
	SYSTEMSFORMAT_KVCD	= SYSTEMSFORMAT_RM + 1,
	SYSTEMSFORMAT_FLV	= SYSTEMSFORMAT_KVCD + 1,
	SYSTEMSFORMAT_DVB	= SYSTEMSFORMAT_FLV + 1
    }	SystemsOutputFormat;

typedef /* [public] */ 
enum _Constraint
    {	CONSTRAINT_NONE	= 0,
	CONSTRAINT_NTSC	= CONSTRAINT_NONE + 1,
	CONSTRAINT_FILM	= CONSTRAINT_NTSC + 1,
	CONSTRAINT_PAL	= CONSTRAINT_FILM + 1,
	CONSTRAINT_IPOD	= CONSTRAINT_PAL + 1,
	CONSTRAINT_IPOD_NANO	= CONSTRAINT_IPOD + 1,
	CONSTRAINT_IPHONE	= CONSTRAINT_IPOD_NANO + 1,
	CONSTRAINT_HD	= CONSTRAINT_IPHONE + 1,
	CONSTRAINT_H264	= CONSTRAINT_HD + 1
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



extern RPC_IF_HANDLE __MIDL_itf_StandardMPEGCreator_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_StandardMPEGCreator_0000_v0_0_s_ifspec;


#ifndef __STANDARDMPEGCREATORLib_LIBRARY_DEFINED__
#define __STANDARDMPEGCREATORLib_LIBRARY_DEFINED__

/* library STANDARDMPEGCREATORLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_STANDARDMPEGCREATORLib;

#ifndef ___IMPEGConverterEvents_DISPINTERFACE_DEFINED__
#define ___IMPEGConverterEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IMPEGConverterEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__IMPEGConverterEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("42F0250E-09C9-4DFF-89B5-908269D5D389")
    _IMPEGConverterEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IMPEGConverterEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            _IMPEGConverterEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            _IMPEGConverterEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            _IMPEGConverterEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            _IMPEGConverterEvents __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            _IMPEGConverterEvents __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            _IMPEGConverterEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            _IMPEGConverterEvents __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } _IMPEGConverterEventsVtbl;

    interface _IMPEGConverterEvents
    {
        CONST_VTBL struct _IMPEGConverterEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IMPEGConverterEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _IMPEGConverterEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _IMPEGConverterEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _IMPEGConverterEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _IMPEGConverterEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _IMPEGConverterEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _IMPEGConverterEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IMPEGConverterEvents_DISPINTERFACE_DEFINED__ */


#ifndef __IStatistics_INTERFACE_DEFINED__
#define __IStatistics_INTERFACE_DEFINED__

/* interface IStatistics */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IStatistics;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("ECA2893E-47C9-47FE-AFBF-6C29A8B235E3")
    IStatistics : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Progress( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Duration( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetInstance( 
            /* [in] */ long Ptr) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FramesEncoded( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_EncodeFramerate( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TimeElapsed( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IStatisticsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IStatistics __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IStatistics __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IStatistics __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IStatistics __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IStatistics __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IStatistics __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IStatistics __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Progress )( 
            IStatistics __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Duration )( 
            IStatistics __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetInstance )( 
            IStatistics __RPC_FAR * This,
            /* [in] */ long Ptr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FramesEncoded )( 
            IStatistics __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_EncodeFramerate )( 
            IStatistics __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TimeElapsed )( 
            IStatistics __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        END_INTERFACE
    } IStatisticsVtbl;

    interface IStatistics
    {
        CONST_VTBL struct IStatisticsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IStatistics_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IStatistics_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IStatistics_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IStatistics_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IStatistics_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IStatistics_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IStatistics_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IStatistics_get_Progress(This,pVal)	\
    (This)->lpVtbl -> get_Progress(This,pVal)

#define IStatistics_get_Duration(This,pVal)	\
    (This)->lpVtbl -> get_Duration(This,pVal)

#define IStatistics_SetInstance(This,Ptr)	\
    (This)->lpVtbl -> SetInstance(This,Ptr)

#define IStatistics_get_FramesEncoded(This,pVal)	\
    (This)->lpVtbl -> get_FramesEncoded(This,pVal)

#define IStatistics_get_EncodeFramerate(This,pVal)	\
    (This)->lpVtbl -> get_EncodeFramerate(This,pVal)

#define IStatistics_get_TimeElapsed(This,pVal)	\
    (This)->lpVtbl -> get_TimeElapsed(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IStatistics_get_Progress_Proxy( 
    IStatistics __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IStatistics_get_Progress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IStatistics_get_Duration_Proxy( 
    IStatistics __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IStatistics_get_Duration_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IStatistics_SetInstance_Proxy( 
    IStatistics __RPC_FAR * This,
    /* [in] */ long Ptr);


void __RPC_STUB IStatistics_SetInstance_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IStatistics_get_FramesEncoded_Proxy( 
    IStatistics __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IStatistics_get_FramesEncoded_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IStatistics_get_EncodeFramerate_Proxy( 
    IStatistics __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IStatistics_get_EncodeFramerate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IStatistics_get_TimeElapsed_Proxy( 
    IStatistics __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IStatistics_get_TimeElapsed_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IStatistics_INTERFACE_DEFINED__ */


#ifndef __ISettings_INTERFACE_DEFINED__
#define __ISettings_INTERFACE_DEFINED__

/* interface ISettings */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ISettings;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7EC4D5A8-7E6A-4DCF-81F4-D464885428EE")
    ISettings : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct ISettingsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ISettings __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ISettings __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ISettings __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ISettings __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ISettings __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ISettings __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ISettings __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } ISettingsVtbl;

    interface ISettings
    {
        CONST_VTBL struct ISettingsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISettings_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISettings_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISettings_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISettings_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ISettings_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ISettings_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ISettings_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISettings_INTERFACE_DEFINED__ */


#ifndef __IMPEGConverter_INTERFACE_DEFINED__
#define __IMPEGConverter_INTERFACE_DEFINED__

/* interface IMPEGConverter */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IMPEGConverter;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A70F42FA-B3CF-4FCF-82FC-2E9E26CB419A")
    IMPEGConverter : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE PassThruCmd( 
            /* [in] */ BSTR Param1) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SourceFile( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SourceFile( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TargetFile( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_TargetFile( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StartConversion( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StopConversion( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE LoadPreset( 
            /* [in] */ BSTR PresetName) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Statistics( 
            /* [retval][out] */ IStatistics __RPC_FAR *__RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMPEGConverterVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMPEGConverter __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMPEGConverter __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMPEGConverter __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IMPEGConverter __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IMPEGConverter __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IMPEGConverter __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IMPEGConverter __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PassThruCmd )( 
            IMPEGConverter __RPC_FAR * This,
            /* [in] */ BSTR Param1);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SourceFile )( 
            IMPEGConverter __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SourceFile )( 
            IMPEGConverter __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TargetFile )( 
            IMPEGConverter __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_TargetFile )( 
            IMPEGConverter __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *StartConversion )( 
            IMPEGConverter __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *StopConversion )( 
            IMPEGConverter __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *LoadPreset )( 
            IMPEGConverter __RPC_FAR * This,
            /* [in] */ BSTR PresetName);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Statistics )( 
            IMPEGConverter __RPC_FAR * This,
            /* [retval][out] */ IStatistics __RPC_FAR *__RPC_FAR *pVal);
        
        END_INTERFACE
    } IMPEGConverterVtbl;

    interface IMPEGConverter
    {
        CONST_VTBL struct IMPEGConverterVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMPEGConverter_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMPEGConverter_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMPEGConverter_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMPEGConverter_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IMPEGConverter_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IMPEGConverter_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IMPEGConverter_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IMPEGConverter_PassThruCmd(This,Param1)	\
    (This)->lpVtbl -> PassThruCmd(This,Param1)

#define IMPEGConverter_get_SourceFile(This,pVal)	\
    (This)->lpVtbl -> get_SourceFile(This,pVal)

#define IMPEGConverter_put_SourceFile(This,newVal)	\
    (This)->lpVtbl -> put_SourceFile(This,newVal)

#define IMPEGConverter_get_TargetFile(This,pVal)	\
    (This)->lpVtbl -> get_TargetFile(This,pVal)

#define IMPEGConverter_put_TargetFile(This,newVal)	\
    (This)->lpVtbl -> put_TargetFile(This,newVal)

#define IMPEGConverter_StartConversion(This)	\
    (This)->lpVtbl -> StartConversion(This)

#define IMPEGConverter_StopConversion(This)	\
    (This)->lpVtbl -> StopConversion(This)

#define IMPEGConverter_LoadPreset(This,PresetName)	\
    (This)->lpVtbl -> LoadPreset(This,PresetName)

#define IMPEGConverter_get_Statistics(This,pVal)	\
    (This)->lpVtbl -> get_Statistics(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMPEGConverter_PassThruCmd_Proxy( 
    IMPEGConverter __RPC_FAR * This,
    /* [in] */ BSTR Param1);


void __RPC_STUB IMPEGConverter_PassThruCmd_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMPEGConverter_get_SourceFile_Proxy( 
    IMPEGConverter __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IMPEGConverter_get_SourceFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMPEGConverter_put_SourceFile_Proxy( 
    IMPEGConverter __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IMPEGConverter_put_SourceFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMPEGConverter_get_TargetFile_Proxy( 
    IMPEGConverter __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IMPEGConverter_get_TargetFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMPEGConverter_put_TargetFile_Proxy( 
    IMPEGConverter __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IMPEGConverter_put_TargetFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMPEGConverter_StartConversion_Proxy( 
    IMPEGConverter __RPC_FAR * This);


void __RPC_STUB IMPEGConverter_StartConversion_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMPEGConverter_StopConversion_Proxy( 
    IMPEGConverter __RPC_FAR * This);


void __RPC_STUB IMPEGConverter_StopConversion_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMPEGConverter_LoadPreset_Proxy( 
    IMPEGConverter __RPC_FAR * This,
    /* [in] */ BSTR PresetName);


void __RPC_STUB IMPEGConverter_LoadPreset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMPEGConverter_get_Statistics_Proxy( 
    IMPEGConverter __RPC_FAR * This,
    /* [retval][out] */ IStatistics __RPC_FAR *__RPC_FAR *pVal);


void __RPC_STUB IMPEGConverter_get_Statistics_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMPEGConverter_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_MPEGConverter;

#ifdef __cplusplus

class DECLSPEC_UUID("AEF8D647-4BD1-4922-8E81-324897B1BFB1")
MPEGConverter;
#endif

EXTERN_C const CLSID CLSID_Statistics;

#ifdef __cplusplus

class DECLSPEC_UUID("39A2FEEE-E83A-41BD-BA48-575B7D09AF10")
Statistics;
#endif

EXTERN_C const CLSID CLSID_Settings;

#ifdef __cplusplus

class DECLSPEC_UUID("21E055F2-DB1B-43F6-948E-1B655FE3E08F")
Settings;
#endif
#endif /* __STANDARDMPEGCREATORLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
