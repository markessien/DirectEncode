
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


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

#ifndef __WMVCreator_h__
#define __WMVCreator_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IWMVCodec_FWD_DEFINED__
#define __IWMVCodec_FWD_DEFINED__
typedef interface IWMVCodec IWMVCodec;
#endif 	/* __IWMVCodec_FWD_DEFINED__ */


#ifndef __IWMVProfile_FWD_DEFINED__
#define __IWMVProfile_FWD_DEFINED__
typedef interface IWMVProfile IWMVProfile;
#endif 	/* __IWMVProfile_FWD_DEFINED__ */


#ifndef __IWMVCreatorObj_FWD_DEFINED__
#define __IWMVCreatorObj_FWD_DEFINED__
typedef interface IWMVCreatorObj IWMVCreatorObj;
#endif 	/* __IWMVCreatorObj_FWD_DEFINED__ */


#ifndef ___IWMVCreatorObjEvents_FWD_DEFINED__
#define ___IWMVCreatorObjEvents_FWD_DEFINED__
typedef interface _IWMVCreatorObjEvents _IWMVCreatorObjEvents;
#endif 	/* ___IWMVCreatorObjEvents_FWD_DEFINED__ */


#ifndef __WMVCreator_FWD_DEFINED__
#define __WMVCreator_FWD_DEFINED__

#ifdef __cplusplus
typedef class WMVCreator WMVCreator;
#else
typedef struct WMVCreator WMVCreator;
#endif /* __cplusplus */

#endif 	/* __WMVCreator_FWD_DEFINED__ */


#ifndef __WMVCodec_FWD_DEFINED__
#define __WMVCodec_FWD_DEFINED__

#ifdef __cplusplus
typedef class WMVCodec WMVCodec;
#else
typedef struct WMVCodec WMVCodec;
#endif /* __cplusplus */

#endif 	/* __WMVCodec_FWD_DEFINED__ */


#ifndef __WMVProfile_FWD_DEFINED__
#define __WMVProfile_FWD_DEFINED__

#ifdef __cplusplus
typedef class WMVProfile WMVProfile;
#else
typedef struct WMVProfile WMVProfile;
#endif /* __cplusplus */

#endif 	/* __WMVProfile_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

#ifndef __IWMVCodec_INTERFACE_DEFINED__
#define __IWMVCodec_INTERFACE_DEFINED__

/* interface IWMVCodec */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IWMVCodec;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("27DCE088-4143-4E1B-8A52-496E963DA094")
    IWMVCodec : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CodecName( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CodecName( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CodecDescription( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CodecDescription( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MajorType( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MaxPasses( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Passes( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Passes( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Quality( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Quality( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Bitrate( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Bitrate( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_VBRMode( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_VBRMode( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_KeyframeFrequency( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_KeyframeFrequency( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Framerate( 
            /* [retval][out] */ DOUBLE *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Framerate( 
            /* [in] */ DOUBLE newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Complexity( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Complexity( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FormatIndex( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_FormatIndex( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CodecGuid( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ComplexityMax( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ComplexityOffline( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ComplexityLive( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IsVBRSupported( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SupportedVBRModes( 
            /* [out] */ VARIANT_BOOL *CBR1Pass,
            /* [out] */ VARIANT_BOOL *CBR2Pass,
            /* [out] */ VARIANT_BOOL *VBR1Pass,
            /* [out] */ VARIANT_BOOL *VBR2Pass,
            /* [out] */ LONG *ConstrainValue) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FormatCount( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE LoadCodecFormats( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FormatName( 
            /* [in] */ LONG Index,
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CodecIndex( 
            /* [retval][out] */ LONG *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWMVCodecVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWMVCodec * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWMVCodec * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWMVCodec * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWMVCodec * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWMVCodec * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWMVCodec * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWMVCodec * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CodecName )( 
            IWMVCodec * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CodecName )( 
            IWMVCodec * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CodecDescription )( 
            IWMVCodec * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CodecDescription )( 
            IWMVCodec * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MajorType )( 
            IWMVCodec * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MaxPasses )( 
            IWMVCodec * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Passes )( 
            IWMVCodec * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Passes )( 
            IWMVCodec * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Quality )( 
            IWMVCodec * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Quality )( 
            IWMVCodec * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Bitrate )( 
            IWMVCodec * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Bitrate )( 
            IWMVCodec * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_VBRMode )( 
            IWMVCodec * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_VBRMode )( 
            IWMVCodec * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_KeyframeFrequency )( 
            IWMVCodec * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_KeyframeFrequency )( 
            IWMVCodec * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Framerate )( 
            IWMVCodec * This,
            /* [retval][out] */ DOUBLE *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Framerate )( 
            IWMVCodec * This,
            /* [in] */ DOUBLE newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Complexity )( 
            IWMVCodec * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Complexity )( 
            IWMVCodec * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FormatIndex )( 
            IWMVCodec * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_FormatIndex )( 
            IWMVCodec * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CodecGuid )( 
            IWMVCodec * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ComplexityMax )( 
            IWMVCodec * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ComplexityOffline )( 
            IWMVCodec * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ComplexityLive )( 
            IWMVCodec * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsVBRSupported )( 
            IWMVCodec * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SupportedVBRModes )( 
            IWMVCodec * This,
            /* [out] */ VARIANT_BOOL *CBR1Pass,
            /* [out] */ VARIANT_BOOL *CBR2Pass,
            /* [out] */ VARIANT_BOOL *VBR1Pass,
            /* [out] */ VARIANT_BOOL *VBR2Pass,
            /* [out] */ LONG *ConstrainValue);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FormatCount )( 
            IWMVCodec * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *LoadCodecFormats )( 
            IWMVCodec * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FormatName )( 
            IWMVCodec * This,
            /* [in] */ LONG Index,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CodecIndex )( 
            IWMVCodec * This,
            /* [retval][out] */ LONG *pVal);
        
        END_INTERFACE
    } IWMVCodecVtbl;

    interface IWMVCodec
    {
        CONST_VTBL struct IWMVCodecVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWMVCodec_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWMVCodec_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWMVCodec_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWMVCodec_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IWMVCodec_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IWMVCodec_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IWMVCodec_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IWMVCodec_get_CodecName(This,pVal)	\
    (This)->lpVtbl -> get_CodecName(This,pVal)

#define IWMVCodec_put_CodecName(This,newVal)	\
    (This)->lpVtbl -> put_CodecName(This,newVal)

#define IWMVCodec_get_CodecDescription(This,pVal)	\
    (This)->lpVtbl -> get_CodecDescription(This,pVal)

#define IWMVCodec_put_CodecDescription(This,newVal)	\
    (This)->lpVtbl -> put_CodecDescription(This,newVal)

#define IWMVCodec_get_MajorType(This,pVal)	\
    (This)->lpVtbl -> get_MajorType(This,pVal)

#define IWMVCodec_get_MaxPasses(This,pVal)	\
    (This)->lpVtbl -> get_MaxPasses(This,pVal)

#define IWMVCodec_get_Passes(This,pVal)	\
    (This)->lpVtbl -> get_Passes(This,pVal)

#define IWMVCodec_put_Passes(This,newVal)	\
    (This)->lpVtbl -> put_Passes(This,newVal)

#define IWMVCodec_get_Quality(This,pVal)	\
    (This)->lpVtbl -> get_Quality(This,pVal)

#define IWMVCodec_put_Quality(This,newVal)	\
    (This)->lpVtbl -> put_Quality(This,newVal)

#define IWMVCodec_get_Bitrate(This,pVal)	\
    (This)->lpVtbl -> get_Bitrate(This,pVal)

#define IWMVCodec_put_Bitrate(This,newVal)	\
    (This)->lpVtbl -> put_Bitrate(This,newVal)

#define IWMVCodec_get_VBRMode(This,pVal)	\
    (This)->lpVtbl -> get_VBRMode(This,pVal)

#define IWMVCodec_put_VBRMode(This,newVal)	\
    (This)->lpVtbl -> put_VBRMode(This,newVal)

#define IWMVCodec_get_KeyframeFrequency(This,pVal)	\
    (This)->lpVtbl -> get_KeyframeFrequency(This,pVal)

#define IWMVCodec_put_KeyframeFrequency(This,newVal)	\
    (This)->lpVtbl -> put_KeyframeFrequency(This,newVal)

#define IWMVCodec_get_Framerate(This,pVal)	\
    (This)->lpVtbl -> get_Framerate(This,pVal)

#define IWMVCodec_put_Framerate(This,newVal)	\
    (This)->lpVtbl -> put_Framerate(This,newVal)

#define IWMVCodec_get_Complexity(This,pVal)	\
    (This)->lpVtbl -> get_Complexity(This,pVal)

#define IWMVCodec_put_Complexity(This,newVal)	\
    (This)->lpVtbl -> put_Complexity(This,newVal)

#define IWMVCodec_get_FormatIndex(This,pVal)	\
    (This)->lpVtbl -> get_FormatIndex(This,pVal)

#define IWMVCodec_put_FormatIndex(This,newVal)	\
    (This)->lpVtbl -> put_FormatIndex(This,newVal)

#define IWMVCodec_get_CodecGuid(This,pVal)	\
    (This)->lpVtbl -> get_CodecGuid(This,pVal)

#define IWMVCodec_get_ComplexityMax(This,pVal)	\
    (This)->lpVtbl -> get_ComplexityMax(This,pVal)

#define IWMVCodec_get_ComplexityOffline(This,pVal)	\
    (This)->lpVtbl -> get_ComplexityOffline(This,pVal)

#define IWMVCodec_get_ComplexityLive(This,pVal)	\
    (This)->lpVtbl -> get_ComplexityLive(This,pVal)

#define IWMVCodec_get_IsVBRSupported(This,pVal)	\
    (This)->lpVtbl -> get_IsVBRSupported(This,pVal)

#define IWMVCodec_SupportedVBRModes(This,CBR1Pass,CBR2Pass,VBR1Pass,VBR2Pass,ConstrainValue)	\
    (This)->lpVtbl -> SupportedVBRModes(This,CBR1Pass,CBR2Pass,VBR1Pass,VBR2Pass,ConstrainValue)

#define IWMVCodec_get_FormatCount(This,pVal)	\
    (This)->lpVtbl -> get_FormatCount(This,pVal)

#define IWMVCodec_LoadCodecFormats(This)	\
    (This)->lpVtbl -> LoadCodecFormats(This)

#define IWMVCodec_get_FormatName(This,Index,pVal)	\
    (This)->lpVtbl -> get_FormatName(This,Index,pVal)

#define IWMVCodec_get_CodecIndex(This,pVal)	\
    (This)->lpVtbl -> get_CodecIndex(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMVCodec_get_CodecName_Proxy( 
    IWMVCodec * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IWMVCodec_get_CodecName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMVCodec_put_CodecName_Proxy( 
    IWMVCodec * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IWMVCodec_put_CodecName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMVCodec_get_CodecDescription_Proxy( 
    IWMVCodec * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IWMVCodec_get_CodecDescription_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMVCodec_put_CodecDescription_Proxy( 
    IWMVCodec * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IWMVCodec_put_CodecDescription_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMVCodec_get_MajorType_Proxy( 
    IWMVCodec * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IWMVCodec_get_MajorType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMVCodec_get_MaxPasses_Proxy( 
    IWMVCodec * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IWMVCodec_get_MaxPasses_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMVCodec_get_Passes_Proxy( 
    IWMVCodec * This,
    /* [retval][out] */ LONG *pVal);


void __RPC_STUB IWMVCodec_get_Passes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMVCodec_put_Passes_Proxy( 
    IWMVCodec * This,
    /* [in] */ LONG newVal);


void __RPC_STUB IWMVCodec_put_Passes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMVCodec_get_Quality_Proxy( 
    IWMVCodec * This,
    /* [retval][out] */ LONG *pVal);


void __RPC_STUB IWMVCodec_get_Quality_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMVCodec_put_Quality_Proxy( 
    IWMVCodec * This,
    /* [in] */ LONG newVal);


void __RPC_STUB IWMVCodec_put_Quality_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMVCodec_get_Bitrate_Proxy( 
    IWMVCodec * This,
    /* [retval][out] */ LONG *pVal);


void __RPC_STUB IWMVCodec_get_Bitrate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMVCodec_put_Bitrate_Proxy( 
    IWMVCodec * This,
    /* [in] */ LONG newVal);


void __RPC_STUB IWMVCodec_put_Bitrate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMVCodec_get_VBRMode_Proxy( 
    IWMVCodec * This,
    /* [retval][out] */ LONG *pVal);


void __RPC_STUB IWMVCodec_get_VBRMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMVCodec_put_VBRMode_Proxy( 
    IWMVCodec * This,
    /* [in] */ LONG newVal);


void __RPC_STUB IWMVCodec_put_VBRMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMVCodec_get_KeyframeFrequency_Proxy( 
    IWMVCodec * This,
    /* [retval][out] */ LONG *pVal);


void __RPC_STUB IWMVCodec_get_KeyframeFrequency_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMVCodec_put_KeyframeFrequency_Proxy( 
    IWMVCodec * This,
    /* [in] */ LONG newVal);


void __RPC_STUB IWMVCodec_put_KeyframeFrequency_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMVCodec_get_Framerate_Proxy( 
    IWMVCodec * This,
    /* [retval][out] */ DOUBLE *pVal);


void __RPC_STUB IWMVCodec_get_Framerate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMVCodec_put_Framerate_Proxy( 
    IWMVCodec * This,
    /* [in] */ DOUBLE newVal);


void __RPC_STUB IWMVCodec_put_Framerate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMVCodec_get_Complexity_Proxy( 
    IWMVCodec * This,
    /* [retval][out] */ LONG *pVal);


void __RPC_STUB IWMVCodec_get_Complexity_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMVCodec_put_Complexity_Proxy( 
    IWMVCodec * This,
    /* [in] */ LONG newVal);


void __RPC_STUB IWMVCodec_put_Complexity_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMVCodec_get_FormatIndex_Proxy( 
    IWMVCodec * This,
    /* [retval][out] */ LONG *pVal);


void __RPC_STUB IWMVCodec_get_FormatIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMVCodec_put_FormatIndex_Proxy( 
    IWMVCodec * This,
    /* [in] */ LONG newVal);


void __RPC_STUB IWMVCodec_put_FormatIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMVCodec_get_CodecGuid_Proxy( 
    IWMVCodec * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IWMVCodec_get_CodecGuid_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMVCodec_get_ComplexityMax_Proxy( 
    IWMVCodec * This,
    /* [retval][out] */ LONG *pVal);


void __RPC_STUB IWMVCodec_get_ComplexityMax_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMVCodec_get_ComplexityOffline_Proxy( 
    IWMVCodec * This,
    /* [retval][out] */ LONG *pVal);


void __RPC_STUB IWMVCodec_get_ComplexityOffline_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMVCodec_get_ComplexityLive_Proxy( 
    IWMVCodec * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IWMVCodec_get_ComplexityLive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMVCodec_get_IsVBRSupported_Proxy( 
    IWMVCodec * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IWMVCodec_get_IsVBRSupported_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMVCodec_SupportedVBRModes_Proxy( 
    IWMVCodec * This,
    /* [out] */ VARIANT_BOOL *CBR1Pass,
    /* [out] */ VARIANT_BOOL *CBR2Pass,
    /* [out] */ VARIANT_BOOL *VBR1Pass,
    /* [out] */ VARIANT_BOOL *VBR2Pass,
    /* [out] */ LONG *ConstrainValue);


void __RPC_STUB IWMVCodec_SupportedVBRModes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMVCodec_get_FormatCount_Proxy( 
    IWMVCodec * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IWMVCodec_get_FormatCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMVCodec_LoadCodecFormats_Proxy( 
    IWMVCodec * This);


void __RPC_STUB IWMVCodec_LoadCodecFormats_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMVCodec_get_FormatName_Proxy( 
    IWMVCodec * This,
    /* [in] */ LONG Index,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IWMVCodec_get_FormatName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMVCodec_get_CodecIndex_Proxy( 
    IWMVCodec * This,
    /* [retval][out] */ LONG *pVal);


void __RPC_STUB IWMVCodec_get_CodecIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWMVCodec_INTERFACE_DEFINED__ */


#ifndef __IWMVProfile_INTERFACE_DEFINED__
#define __IWMVProfile_INTERFACE_DEFINED__

/* interface IWMVProfile */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IWMVProfile;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("DE417BB1-A32F-477F-A73B-AD478C259C57")
    IWMVProfile : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ProfileName( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ProfileName( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ProfileDescription( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ProfileDescription( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_HasVideoStream( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_HasVideoStream( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_HasAudioStream( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_HasAudioStream( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Bitrate( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Bitrate( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_StringEquivalent( 
            /* [in] */ BSTR Param,
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_StringEquivalent( 
            /* [in] */ BSTR Param,
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_VideoWidth( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_VideoWidth( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_VideoHeight( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_VideoHeight( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_VideoCodec( 
            /* [retval][out] */ IWMVCodec **pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_VideoCodec( 
            /* [in] */ IWMVCodec *newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AudioCodec( 
            /* [retval][out] */ IWMVCodec **pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_AudioCodec( 
            /* [in] */ IWMVCodec *newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_KeyFrameSpacing( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_KeyFrameSpacing( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Framerate( 
            /* [retval][out] */ DOUBLE *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Framerate( 
            /* [in] */ DOUBLE newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Quality( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Quality( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_VideoBitrate( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_VideoBitrate( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AudioBitrate( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_AudioBitrate( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CopyProfile( 
            /* [in] */ IWMVProfile *ProfileToCopy) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Seekable( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Seekable( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWMVProfileVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWMVProfile * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWMVProfile * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWMVProfile * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWMVProfile * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWMVProfile * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWMVProfile * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWMVProfile * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ProfileName )( 
            IWMVProfile * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ProfileName )( 
            IWMVProfile * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ProfileDescription )( 
            IWMVProfile * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ProfileDescription )( 
            IWMVProfile * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HasVideoStream )( 
            IWMVProfile * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_HasVideoStream )( 
            IWMVProfile * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HasAudioStream )( 
            IWMVProfile * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_HasAudioStream )( 
            IWMVProfile * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Bitrate )( 
            IWMVProfile * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Bitrate )( 
            IWMVProfile * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StringEquivalent )( 
            IWMVProfile * This,
            /* [in] */ BSTR Param,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_StringEquivalent )( 
            IWMVProfile * This,
            /* [in] */ BSTR Param,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_VideoWidth )( 
            IWMVProfile * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_VideoWidth )( 
            IWMVProfile * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_VideoHeight )( 
            IWMVProfile * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_VideoHeight )( 
            IWMVProfile * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_VideoCodec )( 
            IWMVProfile * This,
            /* [retval][out] */ IWMVCodec **pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_VideoCodec )( 
            IWMVProfile * This,
            /* [in] */ IWMVCodec *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AudioCodec )( 
            IWMVProfile * This,
            /* [retval][out] */ IWMVCodec **pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_AudioCodec )( 
            IWMVProfile * This,
            /* [in] */ IWMVCodec *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_KeyFrameSpacing )( 
            IWMVProfile * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_KeyFrameSpacing )( 
            IWMVProfile * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Framerate )( 
            IWMVProfile * This,
            /* [retval][out] */ DOUBLE *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Framerate )( 
            IWMVProfile * This,
            /* [in] */ DOUBLE newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Quality )( 
            IWMVProfile * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Quality )( 
            IWMVProfile * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_VideoBitrate )( 
            IWMVProfile * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_VideoBitrate )( 
            IWMVProfile * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AudioBitrate )( 
            IWMVProfile * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_AudioBitrate )( 
            IWMVProfile * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CopyProfile )( 
            IWMVProfile * This,
            /* [in] */ IWMVProfile *ProfileToCopy);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Seekable )( 
            IWMVProfile * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Seekable )( 
            IWMVProfile * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        END_INTERFACE
    } IWMVProfileVtbl;

    interface IWMVProfile
    {
        CONST_VTBL struct IWMVProfileVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWMVProfile_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWMVProfile_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWMVProfile_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWMVProfile_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IWMVProfile_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IWMVProfile_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IWMVProfile_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IWMVProfile_get_ProfileName(This,pVal)	\
    (This)->lpVtbl -> get_ProfileName(This,pVal)

#define IWMVProfile_put_ProfileName(This,newVal)	\
    (This)->lpVtbl -> put_ProfileName(This,newVal)

#define IWMVProfile_get_ProfileDescription(This,pVal)	\
    (This)->lpVtbl -> get_ProfileDescription(This,pVal)

#define IWMVProfile_put_ProfileDescription(This,newVal)	\
    (This)->lpVtbl -> put_ProfileDescription(This,newVal)

#define IWMVProfile_get_HasVideoStream(This,pVal)	\
    (This)->lpVtbl -> get_HasVideoStream(This,pVal)

#define IWMVProfile_put_HasVideoStream(This,newVal)	\
    (This)->lpVtbl -> put_HasVideoStream(This,newVal)

#define IWMVProfile_get_HasAudioStream(This,pVal)	\
    (This)->lpVtbl -> get_HasAudioStream(This,pVal)

#define IWMVProfile_put_HasAudioStream(This,newVal)	\
    (This)->lpVtbl -> put_HasAudioStream(This,newVal)

#define IWMVProfile_get_Bitrate(This,pVal)	\
    (This)->lpVtbl -> get_Bitrate(This,pVal)

#define IWMVProfile_put_Bitrate(This,newVal)	\
    (This)->lpVtbl -> put_Bitrate(This,newVal)

#define IWMVProfile_get_StringEquivalent(This,Param,pVal)	\
    (This)->lpVtbl -> get_StringEquivalent(This,Param,pVal)

#define IWMVProfile_put_StringEquivalent(This,Param,newVal)	\
    (This)->lpVtbl -> put_StringEquivalent(This,Param,newVal)

#define IWMVProfile_get_VideoWidth(This,pVal)	\
    (This)->lpVtbl -> get_VideoWidth(This,pVal)

#define IWMVProfile_put_VideoWidth(This,newVal)	\
    (This)->lpVtbl -> put_VideoWidth(This,newVal)

#define IWMVProfile_get_VideoHeight(This,pVal)	\
    (This)->lpVtbl -> get_VideoHeight(This,pVal)

#define IWMVProfile_put_VideoHeight(This,newVal)	\
    (This)->lpVtbl -> put_VideoHeight(This,newVal)

#define IWMVProfile_get_VideoCodec(This,pVal)	\
    (This)->lpVtbl -> get_VideoCodec(This,pVal)

#define IWMVProfile_put_VideoCodec(This,newVal)	\
    (This)->lpVtbl -> put_VideoCodec(This,newVal)

#define IWMVProfile_get_AudioCodec(This,pVal)	\
    (This)->lpVtbl -> get_AudioCodec(This,pVal)

#define IWMVProfile_put_AudioCodec(This,newVal)	\
    (This)->lpVtbl -> put_AudioCodec(This,newVal)

#define IWMVProfile_get_KeyFrameSpacing(This,pVal)	\
    (This)->lpVtbl -> get_KeyFrameSpacing(This,pVal)

#define IWMVProfile_put_KeyFrameSpacing(This,newVal)	\
    (This)->lpVtbl -> put_KeyFrameSpacing(This,newVal)

#define IWMVProfile_get_Framerate(This,pVal)	\
    (This)->lpVtbl -> get_Framerate(This,pVal)

#define IWMVProfile_put_Framerate(This,newVal)	\
    (This)->lpVtbl -> put_Framerate(This,newVal)

#define IWMVProfile_get_Quality(This,pVal)	\
    (This)->lpVtbl -> get_Quality(This,pVal)

#define IWMVProfile_put_Quality(This,newVal)	\
    (This)->lpVtbl -> put_Quality(This,newVal)

#define IWMVProfile_get_VideoBitrate(This,pVal)	\
    (This)->lpVtbl -> get_VideoBitrate(This,pVal)

#define IWMVProfile_put_VideoBitrate(This,newVal)	\
    (This)->lpVtbl -> put_VideoBitrate(This,newVal)

#define IWMVProfile_get_AudioBitrate(This,pVal)	\
    (This)->lpVtbl -> get_AudioBitrate(This,pVal)

#define IWMVProfile_put_AudioBitrate(This,newVal)	\
    (This)->lpVtbl -> put_AudioBitrate(This,newVal)

#define IWMVProfile_CopyProfile(This,ProfileToCopy)	\
    (This)->lpVtbl -> CopyProfile(This,ProfileToCopy)

#define IWMVProfile_get_Seekable(This,pVal)	\
    (This)->lpVtbl -> get_Seekable(This,pVal)

#define IWMVProfile_put_Seekable(This,newVal)	\
    (This)->lpVtbl -> put_Seekable(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMVProfile_get_ProfileName_Proxy( 
    IWMVProfile * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IWMVProfile_get_ProfileName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMVProfile_put_ProfileName_Proxy( 
    IWMVProfile * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IWMVProfile_put_ProfileName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMVProfile_get_ProfileDescription_Proxy( 
    IWMVProfile * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IWMVProfile_get_ProfileDescription_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMVProfile_put_ProfileDescription_Proxy( 
    IWMVProfile * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IWMVProfile_put_ProfileDescription_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMVProfile_get_HasVideoStream_Proxy( 
    IWMVProfile * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IWMVProfile_get_HasVideoStream_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMVProfile_put_HasVideoStream_Proxy( 
    IWMVProfile * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IWMVProfile_put_HasVideoStream_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMVProfile_get_HasAudioStream_Proxy( 
    IWMVProfile * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IWMVProfile_get_HasAudioStream_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMVProfile_put_HasAudioStream_Proxy( 
    IWMVProfile * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IWMVProfile_put_HasAudioStream_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMVProfile_get_Bitrate_Proxy( 
    IWMVProfile * This,
    /* [retval][out] */ LONG *pVal);


void __RPC_STUB IWMVProfile_get_Bitrate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMVProfile_put_Bitrate_Proxy( 
    IWMVProfile * This,
    /* [in] */ LONG newVal);


void __RPC_STUB IWMVProfile_put_Bitrate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMVProfile_get_StringEquivalent_Proxy( 
    IWMVProfile * This,
    /* [in] */ BSTR Param,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IWMVProfile_get_StringEquivalent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMVProfile_put_StringEquivalent_Proxy( 
    IWMVProfile * This,
    /* [in] */ BSTR Param,
    /* [in] */ BSTR newVal);


void __RPC_STUB IWMVProfile_put_StringEquivalent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMVProfile_get_VideoWidth_Proxy( 
    IWMVProfile * This,
    /* [retval][out] */ LONG *pVal);


void __RPC_STUB IWMVProfile_get_VideoWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMVProfile_put_VideoWidth_Proxy( 
    IWMVProfile * This,
    /* [in] */ LONG newVal);


void __RPC_STUB IWMVProfile_put_VideoWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMVProfile_get_VideoHeight_Proxy( 
    IWMVProfile * This,
    /* [retval][out] */ LONG *pVal);


void __RPC_STUB IWMVProfile_get_VideoHeight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMVProfile_put_VideoHeight_Proxy( 
    IWMVProfile * This,
    /* [in] */ LONG newVal);


void __RPC_STUB IWMVProfile_put_VideoHeight_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMVProfile_get_VideoCodec_Proxy( 
    IWMVProfile * This,
    /* [retval][out] */ IWMVCodec **pVal);


void __RPC_STUB IWMVProfile_get_VideoCodec_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMVProfile_put_VideoCodec_Proxy( 
    IWMVProfile * This,
    /* [in] */ IWMVCodec *newVal);


void __RPC_STUB IWMVProfile_put_VideoCodec_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMVProfile_get_AudioCodec_Proxy( 
    IWMVProfile * This,
    /* [retval][out] */ IWMVCodec **pVal);


void __RPC_STUB IWMVProfile_get_AudioCodec_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMVProfile_put_AudioCodec_Proxy( 
    IWMVProfile * This,
    /* [in] */ IWMVCodec *newVal);


void __RPC_STUB IWMVProfile_put_AudioCodec_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMVProfile_get_KeyFrameSpacing_Proxy( 
    IWMVProfile * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IWMVProfile_get_KeyFrameSpacing_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMVProfile_put_KeyFrameSpacing_Proxy( 
    IWMVProfile * This,
    /* [in] */ long newVal);


void __RPC_STUB IWMVProfile_put_KeyFrameSpacing_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMVProfile_get_Framerate_Proxy( 
    IWMVProfile * This,
    /* [retval][out] */ DOUBLE *pVal);


void __RPC_STUB IWMVProfile_get_Framerate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMVProfile_put_Framerate_Proxy( 
    IWMVProfile * This,
    /* [in] */ DOUBLE newVal);


void __RPC_STUB IWMVProfile_put_Framerate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMVProfile_get_Quality_Proxy( 
    IWMVProfile * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IWMVProfile_get_Quality_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMVProfile_put_Quality_Proxy( 
    IWMVProfile * This,
    /* [in] */ long newVal);


void __RPC_STUB IWMVProfile_put_Quality_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMVProfile_get_VideoBitrate_Proxy( 
    IWMVProfile * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IWMVProfile_get_VideoBitrate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMVProfile_put_VideoBitrate_Proxy( 
    IWMVProfile * This,
    /* [in] */ long newVal);


void __RPC_STUB IWMVProfile_put_VideoBitrate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMVProfile_get_AudioBitrate_Proxy( 
    IWMVProfile * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IWMVProfile_get_AudioBitrate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMVProfile_put_AudioBitrate_Proxy( 
    IWMVProfile * This,
    /* [in] */ long newVal);


void __RPC_STUB IWMVProfile_put_AudioBitrate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMVProfile_CopyProfile_Proxy( 
    IWMVProfile * This,
    /* [in] */ IWMVProfile *ProfileToCopy);


void __RPC_STUB IWMVProfile_CopyProfile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMVProfile_get_Seekable_Proxy( 
    IWMVProfile * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IWMVProfile_get_Seekable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMVProfile_put_Seekable_Proxy( 
    IWMVProfile * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IWMVProfile_put_Seekable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWMVProfile_INTERFACE_DEFINED__ */


#ifndef __IWMVCreatorObj_INTERFACE_DEFINED__
#define __IWMVCreatorObj_INTERFACE_DEFINED__

/* interface IWMVCreatorObj */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IWMVCreatorObj;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A4AB6D61-6831-4535-B39C-981630AD3109")
    IWMVCreatorObj : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StartConversion( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StopConversion( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Duration( 
            /* [retval][out] */ DOUBLE *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Progress( 
            /* [retval][out] */ DOUBLE *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Progress( 
            /* [in] */ DOUBLE newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE LoadSystemProfiles( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SystemProfileCount( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SystemProfile( 
            /* [in] */ LONG Index,
            /* [retval][out] */ IWMVProfile **pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE LoadSystemCodecs( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_VideoCodecCount( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_VideoCodec( 
            /* [in] */ LONG Index,
            /* [retval][out] */ IWMVCodec **pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_InputFile( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_InputFile( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_OutputFile( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_OutputFile( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ConversionProfile( 
            /* [retval][out] */ IWMVProfile **pVal) = 0;
        
        virtual /* [helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE putref_ConversionProfile( 
            /* [in] */ IWMVProfile *newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ProfileCount( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Profile( 
            /* [in] */ long Index,
            /* [retval][out] */ IWMVProfile **pVal) = 0;
        
        virtual /* [helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE putref_Profile( 
            /* [in] */ long Index,
            /* [in] */ IWMVProfile *newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AudioCodec( 
            /* [in] */ long Index,
            /* [retval][out] */ IWMVCodec **pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AudioCodecCount( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_EncodeFramerate( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_LicenseKey( 
            /* [in] */ BSTR newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWMVCreatorObjVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWMVCreatorObj * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWMVCreatorObj * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWMVCreatorObj * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWMVCreatorObj * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWMVCreatorObj * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWMVCreatorObj * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWMVCreatorObj * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *StartConversion )( 
            IWMVCreatorObj * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *StopConversion )( 
            IWMVCreatorObj * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Duration )( 
            IWMVCreatorObj * This,
            /* [retval][out] */ DOUBLE *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Progress )( 
            IWMVCreatorObj * This,
            /* [retval][out] */ DOUBLE *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Progress )( 
            IWMVCreatorObj * This,
            /* [in] */ DOUBLE newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *LoadSystemProfiles )( 
            IWMVCreatorObj * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SystemProfileCount )( 
            IWMVCreatorObj * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_SystemProfile )( 
            IWMVCreatorObj * This,
            /* [in] */ LONG Index,
            /* [retval][out] */ IWMVProfile **pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *LoadSystemCodecs )( 
            IWMVCreatorObj * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_VideoCodecCount )( 
            IWMVCreatorObj * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_VideoCodec )( 
            IWMVCreatorObj * This,
            /* [in] */ LONG Index,
            /* [retval][out] */ IWMVCodec **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_InputFile )( 
            IWMVCreatorObj * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_InputFile )( 
            IWMVCreatorObj * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_OutputFile )( 
            IWMVCreatorObj * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_OutputFile )( 
            IWMVCreatorObj * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ConversionProfile )( 
            IWMVCreatorObj * This,
            /* [retval][out] */ IWMVProfile **pVal);
        
        /* [helpstring][id][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_ConversionProfile )( 
            IWMVCreatorObj * This,
            /* [in] */ IWMVProfile *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ProfileCount )( 
            IWMVCreatorObj * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Profile )( 
            IWMVCreatorObj * This,
            /* [in] */ long Index,
            /* [retval][out] */ IWMVProfile **pVal);
        
        /* [helpstring][id][propputref] */ HRESULT ( STDMETHODCALLTYPE *putref_Profile )( 
            IWMVCreatorObj * This,
            /* [in] */ long Index,
            /* [in] */ IWMVProfile *newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AudioCodec )( 
            IWMVCreatorObj * This,
            /* [in] */ long Index,
            /* [retval][out] */ IWMVCodec **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AudioCodecCount )( 
            IWMVCreatorObj * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_EncodeFramerate )( 
            IWMVCreatorObj * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_LicenseKey )( 
            IWMVCreatorObj * This,
            /* [in] */ BSTR newVal);
        
        END_INTERFACE
    } IWMVCreatorObjVtbl;

    interface IWMVCreatorObj
    {
        CONST_VTBL struct IWMVCreatorObjVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWMVCreatorObj_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IWMVCreatorObj_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IWMVCreatorObj_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IWMVCreatorObj_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IWMVCreatorObj_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IWMVCreatorObj_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IWMVCreatorObj_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IWMVCreatorObj_StartConversion(This)	\
    (This)->lpVtbl -> StartConversion(This)

#define IWMVCreatorObj_StopConversion(This)	\
    (This)->lpVtbl -> StopConversion(This)

#define IWMVCreatorObj_get_Duration(This,pVal)	\
    (This)->lpVtbl -> get_Duration(This,pVal)

#define IWMVCreatorObj_get_Progress(This,pVal)	\
    (This)->lpVtbl -> get_Progress(This,pVal)

#define IWMVCreatorObj_put_Progress(This,newVal)	\
    (This)->lpVtbl -> put_Progress(This,newVal)

#define IWMVCreatorObj_LoadSystemProfiles(This)	\
    (This)->lpVtbl -> LoadSystemProfiles(This)

#define IWMVCreatorObj_get_SystemProfileCount(This,pVal)	\
    (This)->lpVtbl -> get_SystemProfileCount(This,pVal)

#define IWMVCreatorObj_get_SystemProfile(This,Index,pVal)	\
    (This)->lpVtbl -> get_SystemProfile(This,Index,pVal)

#define IWMVCreatorObj_LoadSystemCodecs(This)	\
    (This)->lpVtbl -> LoadSystemCodecs(This)

#define IWMVCreatorObj_get_VideoCodecCount(This,pVal)	\
    (This)->lpVtbl -> get_VideoCodecCount(This,pVal)

#define IWMVCreatorObj_get_VideoCodec(This,Index,pVal)	\
    (This)->lpVtbl -> get_VideoCodec(This,Index,pVal)

#define IWMVCreatorObj_get_InputFile(This,pVal)	\
    (This)->lpVtbl -> get_InputFile(This,pVal)

#define IWMVCreatorObj_put_InputFile(This,newVal)	\
    (This)->lpVtbl -> put_InputFile(This,newVal)

#define IWMVCreatorObj_get_OutputFile(This,pVal)	\
    (This)->lpVtbl -> get_OutputFile(This,pVal)

#define IWMVCreatorObj_put_OutputFile(This,newVal)	\
    (This)->lpVtbl -> put_OutputFile(This,newVal)

#define IWMVCreatorObj_get_ConversionProfile(This,pVal)	\
    (This)->lpVtbl -> get_ConversionProfile(This,pVal)

#define IWMVCreatorObj_putref_ConversionProfile(This,newVal)	\
    (This)->lpVtbl -> putref_ConversionProfile(This,newVal)

#define IWMVCreatorObj_get_ProfileCount(This,pVal)	\
    (This)->lpVtbl -> get_ProfileCount(This,pVal)

#define IWMVCreatorObj_get_Profile(This,Index,pVal)	\
    (This)->lpVtbl -> get_Profile(This,Index,pVal)

#define IWMVCreatorObj_putref_Profile(This,Index,newVal)	\
    (This)->lpVtbl -> putref_Profile(This,Index,newVal)

#define IWMVCreatorObj_get_AudioCodec(This,Index,pVal)	\
    (This)->lpVtbl -> get_AudioCodec(This,Index,pVal)

#define IWMVCreatorObj_get_AudioCodecCount(This,pVal)	\
    (This)->lpVtbl -> get_AudioCodecCount(This,pVal)

#define IWMVCreatorObj_get_EncodeFramerate(This,pVal)	\
    (This)->lpVtbl -> get_EncodeFramerate(This,pVal)

#define IWMVCreatorObj_put_LicenseKey(This,newVal)	\
    (This)->lpVtbl -> put_LicenseKey(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMVCreatorObj_StartConversion_Proxy( 
    IWMVCreatorObj * This);


void __RPC_STUB IWMVCreatorObj_StartConversion_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMVCreatorObj_StopConversion_Proxy( 
    IWMVCreatorObj * This);


void __RPC_STUB IWMVCreatorObj_StopConversion_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMVCreatorObj_get_Duration_Proxy( 
    IWMVCreatorObj * This,
    /* [retval][out] */ DOUBLE *pVal);


void __RPC_STUB IWMVCreatorObj_get_Duration_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMVCreatorObj_get_Progress_Proxy( 
    IWMVCreatorObj * This,
    /* [retval][out] */ DOUBLE *pVal);


void __RPC_STUB IWMVCreatorObj_get_Progress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMVCreatorObj_put_Progress_Proxy( 
    IWMVCreatorObj * This,
    /* [in] */ DOUBLE newVal);


void __RPC_STUB IWMVCreatorObj_put_Progress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMVCreatorObj_LoadSystemProfiles_Proxy( 
    IWMVCreatorObj * This);


void __RPC_STUB IWMVCreatorObj_LoadSystemProfiles_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMVCreatorObj_get_SystemProfileCount_Proxy( 
    IWMVCreatorObj * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IWMVCreatorObj_get_SystemProfileCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMVCreatorObj_get_SystemProfile_Proxy( 
    IWMVCreatorObj * This,
    /* [in] */ LONG Index,
    /* [retval][out] */ IWMVProfile **pVal);


void __RPC_STUB IWMVCreatorObj_get_SystemProfile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IWMVCreatorObj_LoadSystemCodecs_Proxy( 
    IWMVCreatorObj * This);


void __RPC_STUB IWMVCreatorObj_LoadSystemCodecs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMVCreatorObj_get_VideoCodecCount_Proxy( 
    IWMVCreatorObj * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IWMVCreatorObj_get_VideoCodecCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMVCreatorObj_get_VideoCodec_Proxy( 
    IWMVCreatorObj * This,
    /* [in] */ LONG Index,
    /* [retval][out] */ IWMVCodec **pVal);


void __RPC_STUB IWMVCreatorObj_get_VideoCodec_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMVCreatorObj_get_InputFile_Proxy( 
    IWMVCreatorObj * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IWMVCreatorObj_get_InputFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMVCreatorObj_put_InputFile_Proxy( 
    IWMVCreatorObj * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IWMVCreatorObj_put_InputFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMVCreatorObj_get_OutputFile_Proxy( 
    IWMVCreatorObj * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IWMVCreatorObj_get_OutputFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMVCreatorObj_put_OutputFile_Proxy( 
    IWMVCreatorObj * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IWMVCreatorObj_put_OutputFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMVCreatorObj_get_ConversionProfile_Proxy( 
    IWMVCreatorObj * This,
    /* [retval][out] */ IWMVProfile **pVal);


void __RPC_STUB IWMVCreatorObj_get_ConversionProfile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE IWMVCreatorObj_putref_ConversionProfile_Proxy( 
    IWMVCreatorObj * This,
    /* [in] */ IWMVProfile *newVal);


void __RPC_STUB IWMVCreatorObj_putref_ConversionProfile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMVCreatorObj_get_ProfileCount_Proxy( 
    IWMVCreatorObj * This,
    /* [retval][out] */ LONG *pVal);


void __RPC_STUB IWMVCreatorObj_get_ProfileCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMVCreatorObj_get_Profile_Proxy( 
    IWMVCreatorObj * This,
    /* [in] */ long Index,
    /* [retval][out] */ IWMVProfile **pVal);


void __RPC_STUB IWMVCreatorObj_get_Profile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propputref] */ HRESULT STDMETHODCALLTYPE IWMVCreatorObj_putref_Profile_Proxy( 
    IWMVCreatorObj * This,
    /* [in] */ long Index,
    /* [in] */ IWMVProfile *newVal);


void __RPC_STUB IWMVCreatorObj_putref_Profile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMVCreatorObj_get_AudioCodec_Proxy( 
    IWMVCreatorObj * This,
    /* [in] */ long Index,
    /* [retval][out] */ IWMVCodec **pVal);


void __RPC_STUB IWMVCreatorObj_get_AudioCodec_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMVCreatorObj_get_AudioCodecCount_Proxy( 
    IWMVCreatorObj * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IWMVCreatorObj_get_AudioCodecCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IWMVCreatorObj_get_EncodeFramerate_Proxy( 
    IWMVCreatorObj * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IWMVCreatorObj_get_EncodeFramerate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IWMVCreatorObj_put_LicenseKey_Proxy( 
    IWMVCreatorObj * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IWMVCreatorObj_put_LicenseKey_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IWMVCreatorObj_INTERFACE_DEFINED__ */



#ifndef __WMVCreatorLib_LIBRARY_DEFINED__
#define __WMVCreatorLib_LIBRARY_DEFINED__

/* library WMVCreatorLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_WMVCreatorLib;

#ifndef ___IWMVCreatorObjEvents_DISPINTERFACE_DEFINED__
#define ___IWMVCreatorObjEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IWMVCreatorObjEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__IWMVCreatorObjEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("7D38D249-06FC-4D98-AF7D-6C649C11F986")
    _IWMVCreatorObjEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IWMVCreatorObjEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IWMVCreatorObjEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IWMVCreatorObjEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IWMVCreatorObjEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IWMVCreatorObjEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IWMVCreatorObjEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IWMVCreatorObjEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IWMVCreatorObjEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _IWMVCreatorObjEventsVtbl;

    interface _IWMVCreatorObjEvents
    {
        CONST_VTBL struct _IWMVCreatorObjEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IWMVCreatorObjEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _IWMVCreatorObjEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _IWMVCreatorObjEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _IWMVCreatorObjEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _IWMVCreatorObjEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _IWMVCreatorObjEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _IWMVCreatorObjEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IWMVCreatorObjEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_WMVCreator;

#ifdef __cplusplus

class DECLSPEC_UUID("B6C1EA13-A642-4078-8E7F-5A9E62F0DBE9")
WMVCreator;
#endif

EXTERN_C const CLSID CLSID_WMVCodec;

#ifdef __cplusplus

class DECLSPEC_UUID("804B1182-1C09-414C-851F-7F4AAA813091")
WMVCodec;
#endif

EXTERN_C const CLSID CLSID_WMVProfile;

#ifdef __cplusplus

class DECLSPEC_UUID("A27BF69D-5ACD-4A01-9913-827BBFE5BC83")
WMVProfile;
#endif
#endif /* __WMVCreatorLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


