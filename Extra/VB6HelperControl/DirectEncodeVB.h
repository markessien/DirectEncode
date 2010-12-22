/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Mon Oct 20 18:01:28 2008
 */
/* Compiler settings for Z:\Development\DirectEncode\DirectEncodeVB\DirectEncodeVB.idl:
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

#ifndef __DirectEncodeVB_h__
#define __DirectEncodeVB_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IStandardMPEGEncoderVB_FWD_DEFINED__
#define __IStandardMPEGEncoderVB_FWD_DEFINED__
typedef interface IStandardMPEGEncoderVB IStandardMPEGEncoderVB;
#endif 	/* __IStandardMPEGEncoderVB_FWD_DEFINED__ */


#ifndef __StandardMPEGEncoderVB_FWD_DEFINED__
#define __StandardMPEGEncoderVB_FWD_DEFINED__

#ifdef __cplusplus
typedef class StandardMPEGEncoderVB StandardMPEGEncoderVB;
#else
typedef struct StandardMPEGEncoderVB StandardMPEGEncoderVB;
#endif /* __cplusplus */

#endif 	/* __StandardMPEGEncoderVB_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 


#ifndef __DIRECTENCODEVBLib_LIBRARY_DEFINED__
#define __DIRECTENCODEVBLib_LIBRARY_DEFINED__

/* library DIRECTENCODEVBLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_DIRECTENCODEVBLib;

#ifndef __IStandardMPEGEncoderVB_INTERFACE_DEFINED__
#define __IStandardMPEGEncoderVB_INTERFACE_DEFINED__

/* interface IStandardMPEGEncoderVB */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IStandardMPEGEncoderVB;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5E4A1AE4-5A1D-4A70-ADB7-53BDD195D962")
    IStandardMPEGEncoderVB : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Test( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CheckObjects( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pb) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetObject( 
            /* [in] */ IUnknown __RPC_FAR *pUnk) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CreateFilter( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetSMPEG( 
            /* [out] */ /* external definition not present */ IStandardMpegEncoder __RPC_FAR *__RPC_FAR *pEncoder) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetOutputFileOnFileWriter( 
            /* [in] */ IUnknown __RPC_FAR *pFileWriter,
            /* [in] */ BSTR FilePath,
            /* [retval][out] */ long __RPC_FAR *pResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE PromptForGraph( 
            /* [in] */ IUnknown __RPC_FAR *pGraph) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IStandardMPEGEncoderVBVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IStandardMPEGEncoderVB __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IStandardMPEGEncoderVB __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IStandardMPEGEncoderVB __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IStandardMPEGEncoderVB __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IStandardMPEGEncoderVB __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IStandardMPEGEncoderVB __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IStandardMPEGEncoderVB __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Test )( 
            IStandardMPEGEncoderVB __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CheckObjects )( 
            IStandardMPEGEncoderVB __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pb);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetObject )( 
            IStandardMPEGEncoderVB __RPC_FAR * This,
            /* [in] */ IUnknown __RPC_FAR *pUnk);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateFilter )( 
            IStandardMPEGEncoderVB __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSMPEG )( 
            IStandardMPEGEncoderVB __RPC_FAR * This,
            /* [out] */ /* external definition not present */ IStandardMpegEncoder __RPC_FAR *__RPC_FAR *pEncoder);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetOutputFileOnFileWriter )( 
            IStandardMPEGEncoderVB __RPC_FAR * This,
            /* [in] */ IUnknown __RPC_FAR *pFileWriter,
            /* [in] */ BSTR FilePath,
            /* [retval][out] */ long __RPC_FAR *pResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PromptForGraph )( 
            IStandardMPEGEncoderVB __RPC_FAR * This,
            /* [in] */ IUnknown __RPC_FAR *pGraph);
        
        END_INTERFACE
    } IStandardMPEGEncoderVBVtbl;

    interface IStandardMPEGEncoderVB
    {
        CONST_VTBL struct IStandardMPEGEncoderVBVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IStandardMPEGEncoderVB_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IStandardMPEGEncoderVB_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IStandardMPEGEncoderVB_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IStandardMPEGEncoderVB_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IStandardMPEGEncoderVB_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IStandardMPEGEncoderVB_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IStandardMPEGEncoderVB_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IStandardMPEGEncoderVB_Test(This)	\
    (This)->lpVtbl -> Test(This)

#define IStandardMPEGEncoderVB_CheckObjects(This,pb)	\
    (This)->lpVtbl -> CheckObjects(This,pb)

#define IStandardMPEGEncoderVB_SetObject(This,pUnk)	\
    (This)->lpVtbl -> SetObject(This,pUnk)

#define IStandardMPEGEncoderVB_CreateFilter(This)	\
    (This)->lpVtbl -> CreateFilter(This)

#define IStandardMPEGEncoderVB_GetSMPEG(This,pEncoder)	\
    (This)->lpVtbl -> GetSMPEG(This,pEncoder)

#define IStandardMPEGEncoderVB_SetOutputFileOnFileWriter(This,pFileWriter,FilePath,pResult)	\
    (This)->lpVtbl -> SetOutputFileOnFileWriter(This,pFileWriter,FilePath,pResult)

#define IStandardMPEGEncoderVB_PromptForGraph(This,pGraph)	\
    (This)->lpVtbl -> PromptForGraph(This,pGraph)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IStandardMPEGEncoderVB_Test_Proxy( 
    IStandardMPEGEncoderVB __RPC_FAR * This);


void __RPC_STUB IStandardMPEGEncoderVB_Test_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IStandardMPEGEncoderVB_CheckObjects_Proxy( 
    IStandardMPEGEncoderVB __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pb);


void __RPC_STUB IStandardMPEGEncoderVB_CheckObjects_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IStandardMPEGEncoderVB_SetObject_Proxy( 
    IStandardMPEGEncoderVB __RPC_FAR * This,
    /* [in] */ IUnknown __RPC_FAR *pUnk);


void __RPC_STUB IStandardMPEGEncoderVB_SetObject_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IStandardMPEGEncoderVB_CreateFilter_Proxy( 
    IStandardMPEGEncoderVB __RPC_FAR * This);


void __RPC_STUB IStandardMPEGEncoderVB_CreateFilter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IStandardMPEGEncoderVB_GetSMPEG_Proxy( 
    IStandardMPEGEncoderVB __RPC_FAR * This,
    /* [out] */ /* external definition not present */ IStandardMpegEncoder __RPC_FAR *__RPC_FAR *pEncoder);


void __RPC_STUB IStandardMPEGEncoderVB_GetSMPEG_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IStandardMPEGEncoderVB_SetOutputFileOnFileWriter_Proxy( 
    IStandardMPEGEncoderVB __RPC_FAR * This,
    /* [in] */ IUnknown __RPC_FAR *pFileWriter,
    /* [in] */ BSTR FilePath,
    /* [retval][out] */ long __RPC_FAR *pResult);


void __RPC_STUB IStandardMPEGEncoderVB_SetOutputFileOnFileWriter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IStandardMPEGEncoderVB_PromptForGraph_Proxy( 
    IStandardMPEGEncoderVB __RPC_FAR * This,
    /* [in] */ IUnknown __RPC_FAR *pGraph);


void __RPC_STUB IStandardMPEGEncoderVB_PromptForGraph_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IStandardMPEGEncoderVB_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_StandardMPEGEncoderVB;

#ifdef __cplusplus

class DECLSPEC_UUID("95D4CFC4-F499-4CB1-8D56-5AE5234DBF90")
StandardMPEGEncoderVB;
#endif
#endif /* __DIRECTENCODEVBLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
