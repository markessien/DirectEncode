

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


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


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __VideoEdit_h__
#define __VideoEdit_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IVideoRect_FWD_DEFINED__
#define __IVideoRect_FWD_DEFINED__
typedef interface IVideoRect IVideoRect;
#endif 	/* __IVideoRect_FWD_DEFINED__ */


#ifndef ___IVideoEditObjEvents_FWD_DEFINED__
#define ___IVideoEditObjEvents_FWD_DEFINED__
typedef interface _IVideoEditObjEvents _IVideoEditObjEvents;
#endif 	/* ___IVideoEditObjEvents_FWD_DEFINED__ */


#ifndef __IMediaFile_FWD_DEFINED__
#define __IMediaFile_FWD_DEFINED__
typedef interface IMediaFile IMediaFile;
#endif 	/* __IMediaFile_FWD_DEFINED__ */


#ifndef __IVideoClip_FWD_DEFINED__
#define __IVideoClip_FWD_DEFINED__
typedef interface IVideoClip IVideoClip;
#endif 	/* __IVideoClip_FWD_DEFINED__ */


#ifndef __IVideoEditObj_FWD_DEFINED__
#define __IVideoEditObj_FWD_DEFINED__
typedef interface IVideoEditObj IVideoEditObj;
#endif 	/* __IVideoEditObj_FWD_DEFINED__ */


#ifndef __VideoEdit_FWD_DEFINED__
#define __VideoEdit_FWD_DEFINED__

#ifdef __cplusplus
typedef class VideoEdit VideoEdit;
#else
typedef struct VideoEdit VideoEdit;
#endif /* __cplusplus */

#endif 	/* __VideoEdit_FWD_DEFINED__ */


#ifndef __MediaFile_FWD_DEFINED__
#define __MediaFile_FWD_DEFINED__

#ifdef __cplusplus
typedef class MediaFile MediaFile;
#else
typedef struct MediaFile MediaFile;
#endif /* __cplusplus */

#endif 	/* __MediaFile_FWD_DEFINED__ */


#ifndef __VideoClip_FWD_DEFINED__
#define __VideoClip_FWD_DEFINED__

#ifdef __cplusplus
typedef class VideoClip VideoClip;
#else
typedef struct VideoClip VideoClip;
#endif /* __cplusplus */

#endif 	/* __VideoClip_FWD_DEFINED__ */


#ifndef __VideoRect_FWD_DEFINED__
#define __VideoRect_FWD_DEFINED__

#ifdef __cplusplus
typedef class VideoRect VideoRect;
#else
typedef struct VideoRect VideoRect;
#endif /* __cplusplus */

#endif 	/* __VideoRect_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 


#ifndef __VIDEOEDITLib_LIBRARY_DEFINED__
#define __VIDEOEDITLib_LIBRARY_DEFINED__

/* library VIDEOEDITLib */
/* [helpstring][version][uuid] */ 

typedef 
enum EnumMediaFormat
    {	formatVideo	= 0,
	formatAudio	= formatVideo + 1
    } 	MediaFormat;


EXTERN_C const IID LIBID_VIDEOEDITLib;

#ifndef __IVideoRect_INTERFACE_DEFINED__
#define __IVideoRect_INTERFACE_DEFINED__

/* interface IVideoRect */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IVideoRect;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7D8E84A6-81B2-4912-891C-91470360A414")
    IVideoRect : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Right( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Right( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Top( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Top( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Left( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Left( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Bottom( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Bottom( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Width( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Width( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Height( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Height( 
            /* [in] */ long newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IVideoRectVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IVideoRect * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IVideoRect * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IVideoRect * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IVideoRect * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IVideoRect * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IVideoRect * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IVideoRect * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Right )( 
            IVideoRect * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Right )( 
            IVideoRect * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Top )( 
            IVideoRect * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Top )( 
            IVideoRect * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Left )( 
            IVideoRect * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Left )( 
            IVideoRect * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Bottom )( 
            IVideoRect * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Bottom )( 
            IVideoRect * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Width )( 
            IVideoRect * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Width )( 
            IVideoRect * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Height )( 
            IVideoRect * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Height )( 
            IVideoRect * This,
            /* [in] */ long newVal);
        
        END_INTERFACE
    } IVideoRectVtbl;

    interface IVideoRect
    {
        CONST_VTBL struct IVideoRectVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVideoRect_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IVideoRect_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IVideoRect_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IVideoRect_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IVideoRect_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IVideoRect_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IVideoRect_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IVideoRect_get_Right(This,pVal)	\
    (This)->lpVtbl -> get_Right(This,pVal)

#define IVideoRect_put_Right(This,newVal)	\
    (This)->lpVtbl -> put_Right(This,newVal)

#define IVideoRect_get_Top(This,pVal)	\
    (This)->lpVtbl -> get_Top(This,pVal)

#define IVideoRect_put_Top(This,newVal)	\
    (This)->lpVtbl -> put_Top(This,newVal)

#define IVideoRect_get_Left(This,pVal)	\
    (This)->lpVtbl -> get_Left(This,pVal)

#define IVideoRect_put_Left(This,newVal)	\
    (This)->lpVtbl -> put_Left(This,newVal)

#define IVideoRect_get_Bottom(This,pVal)	\
    (This)->lpVtbl -> get_Bottom(This,pVal)

#define IVideoRect_put_Bottom(This,newVal)	\
    (This)->lpVtbl -> put_Bottom(This,newVal)

#define IVideoRect_get_Width(This,pVal)	\
    (This)->lpVtbl -> get_Width(This,pVal)

#define IVideoRect_put_Width(This,newVal)	\
    (This)->lpVtbl -> put_Width(This,newVal)

#define IVideoRect_get_Height(This,pVal)	\
    (This)->lpVtbl -> get_Height(This,pVal)

#define IVideoRect_put_Height(This,newVal)	\
    (This)->lpVtbl -> put_Height(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVideoRect_get_Right_Proxy( 
    IVideoRect * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IVideoRect_get_Right_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVideoRect_put_Right_Proxy( 
    IVideoRect * This,
    /* [in] */ long newVal);


void __RPC_STUB IVideoRect_put_Right_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVideoRect_get_Top_Proxy( 
    IVideoRect * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IVideoRect_get_Top_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVideoRect_put_Top_Proxy( 
    IVideoRect * This,
    /* [in] */ long newVal);


void __RPC_STUB IVideoRect_put_Top_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVideoRect_get_Left_Proxy( 
    IVideoRect * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IVideoRect_get_Left_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVideoRect_put_Left_Proxy( 
    IVideoRect * This,
    /* [in] */ long newVal);


void __RPC_STUB IVideoRect_put_Left_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVideoRect_get_Bottom_Proxy( 
    IVideoRect * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IVideoRect_get_Bottom_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVideoRect_put_Bottom_Proxy( 
    IVideoRect * This,
    /* [in] */ long newVal);


void __RPC_STUB IVideoRect_put_Bottom_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVideoRect_get_Width_Proxy( 
    IVideoRect * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IVideoRect_get_Width_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVideoRect_put_Width_Proxy( 
    IVideoRect * This,
    /* [in] */ long newVal);


void __RPC_STUB IVideoRect_put_Width_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVideoRect_get_Height_Proxy( 
    IVideoRect * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IVideoRect_get_Height_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVideoRect_put_Height_Proxy( 
    IVideoRect * This,
    /* [in] */ long newVal);


void __RPC_STUB IVideoRect_put_Height_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IVideoRect_INTERFACE_DEFINED__ */


#ifndef ___IVideoEditObjEvents_DISPINTERFACE_DEFINED__
#define ___IVideoEditObjEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IVideoEditObjEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__IVideoEditObjEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("AE6F165D-9469-41D5-9FDA-CCF8642E4747")
    _IVideoEditObjEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IVideoEditObjEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IVideoEditObjEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IVideoEditObjEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IVideoEditObjEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IVideoEditObjEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IVideoEditObjEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IVideoEditObjEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IVideoEditObjEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _IVideoEditObjEventsVtbl;

    interface _IVideoEditObjEvents
    {
        CONST_VTBL struct _IVideoEditObjEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IVideoEditObjEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _IVideoEditObjEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _IVideoEditObjEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _IVideoEditObjEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _IVideoEditObjEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _IVideoEditObjEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _IVideoEditObjEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IVideoEditObjEvents_DISPINTERFACE_DEFINED__ */


#ifndef __IMediaFile_INTERFACE_DEFINED__
#define __IMediaFile_INTERFACE_DEFINED__

/* interface IMediaFile */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IMediaFile;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4E224C6B-E3B5-4C86-BFF5-1518CE9773E4")
    IMediaFile : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PosterFrame( 
            /* [retval][out] */ IPictureDisp **pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Duration( 
            /* [retval][out] */ double *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Duration( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Transition( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Transition( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_StartOffset( 
            /* [retval][out] */ double *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_StartOffset( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FilePath( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_FilePath( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FileTitle( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_FileTitle( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_PosterFramePath( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_IsImage( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_IsImage( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TransitionLength( 
            /* [retval][out] */ double *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_TransitionLength( 
            /* [in] */ double newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OverlayText( 
            /* [in] */ BSTR Text,
            /* [in] */ long xPos,
            /* [in] */ long yPos,
            /* [in] */ long Width,
            /* [in] */ long Height,
            /* [in] */ BSTR FontFace,
            /* [in] */ long FontHeight) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DoTextOverlay( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DoTextOverlay( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetZoomOutRect( 
            /* [in] */ IVideoRect **rcSource,
            /* [in] */ IVideoRect **rcZoomIn,
            /* [in] */ IVideoRect **ppResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ApplyMotionEffect( 
            /* [in] */ long hwnd,
            /* [in] */ IVideoRect **rcReferenceRect,
            /* [in] */ IVideoRect **rcStart,
            /* [in] */ IVideoRect **rcEnd,
            /* [in] */ long fps,
            /* [in] */ long duration) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMediaFileVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMediaFile * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMediaFile * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMediaFile * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IMediaFile * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IMediaFile * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IMediaFile * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IMediaFile * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PosterFrame )( 
            IMediaFile * This,
            /* [retval][out] */ IPictureDisp **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Duration )( 
            IMediaFile * This,
            /* [retval][out] */ double *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Duration )( 
            IMediaFile * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Transition )( 
            IMediaFile * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Transition )( 
            IMediaFile * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_StartOffset )( 
            IMediaFile * This,
            /* [retval][out] */ double *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_StartOffset )( 
            IMediaFile * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FilePath )( 
            IMediaFile * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_FilePath )( 
            IMediaFile * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_FileTitle )( 
            IMediaFile * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_FileTitle )( 
            IMediaFile * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_PosterFramePath )( 
            IMediaFile * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_IsImage )( 
            IMediaFile * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_IsImage )( 
            IMediaFile * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TransitionLength )( 
            IMediaFile * This,
            /* [retval][out] */ double *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_TransitionLength )( 
            IMediaFile * This,
            /* [in] */ double newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *OverlayText )( 
            IMediaFile * This,
            /* [in] */ BSTR Text,
            /* [in] */ long xPos,
            /* [in] */ long yPos,
            /* [in] */ long Width,
            /* [in] */ long Height,
            /* [in] */ BSTR FontFace,
            /* [in] */ long FontHeight);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DoTextOverlay )( 
            IMediaFile * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DoTextOverlay )( 
            IMediaFile * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetZoomOutRect )( 
            IMediaFile * This,
            /* [in] */ IVideoRect **rcSource,
            /* [in] */ IVideoRect **rcZoomIn,
            /* [in] */ IVideoRect **ppResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ApplyMotionEffect )( 
            IMediaFile * This,
            /* [in] */ long hwnd,
            /* [in] */ IVideoRect **rcReferenceRect,
            /* [in] */ IVideoRect **rcStart,
            /* [in] */ IVideoRect **rcEnd,
            /* [in] */ long fps,
            /* [in] */ long duration);
        
        END_INTERFACE
    } IMediaFileVtbl;

    interface IMediaFile
    {
        CONST_VTBL struct IMediaFileVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMediaFile_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMediaFile_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMediaFile_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMediaFile_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IMediaFile_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IMediaFile_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IMediaFile_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IMediaFile_get_PosterFrame(This,pVal)	\
    (This)->lpVtbl -> get_PosterFrame(This,pVal)

#define IMediaFile_get_Duration(This,pVal)	\
    (This)->lpVtbl -> get_Duration(This,pVal)

#define IMediaFile_put_Duration(This,newVal)	\
    (This)->lpVtbl -> put_Duration(This,newVal)

#define IMediaFile_get_Transition(This,pVal)	\
    (This)->lpVtbl -> get_Transition(This,pVal)

#define IMediaFile_put_Transition(This,newVal)	\
    (This)->lpVtbl -> put_Transition(This,newVal)

#define IMediaFile_get_StartOffset(This,pVal)	\
    (This)->lpVtbl -> get_StartOffset(This,pVal)

#define IMediaFile_put_StartOffset(This,newVal)	\
    (This)->lpVtbl -> put_StartOffset(This,newVal)

#define IMediaFile_get_FilePath(This,pVal)	\
    (This)->lpVtbl -> get_FilePath(This,pVal)

#define IMediaFile_put_FilePath(This,newVal)	\
    (This)->lpVtbl -> put_FilePath(This,newVal)

#define IMediaFile_get_FileTitle(This,pVal)	\
    (This)->lpVtbl -> get_FileTitle(This,pVal)

#define IMediaFile_put_FileTitle(This,newVal)	\
    (This)->lpVtbl -> put_FileTitle(This,newVal)

#define IMediaFile_put_PosterFramePath(This,newVal)	\
    (This)->lpVtbl -> put_PosterFramePath(This,newVal)

#define IMediaFile_get_IsImage(This,pVal)	\
    (This)->lpVtbl -> get_IsImage(This,pVal)

#define IMediaFile_put_IsImage(This,newVal)	\
    (This)->lpVtbl -> put_IsImage(This,newVal)

#define IMediaFile_get_TransitionLength(This,pVal)	\
    (This)->lpVtbl -> get_TransitionLength(This,pVal)

#define IMediaFile_put_TransitionLength(This,newVal)	\
    (This)->lpVtbl -> put_TransitionLength(This,newVal)

#define IMediaFile_OverlayText(This,Text,xPos,yPos,Width,Height,FontFace,FontHeight)	\
    (This)->lpVtbl -> OverlayText(This,Text,xPos,yPos,Width,Height,FontFace,FontHeight)

#define IMediaFile_get_DoTextOverlay(This,pVal)	\
    (This)->lpVtbl -> get_DoTextOverlay(This,pVal)

#define IMediaFile_put_DoTextOverlay(This,newVal)	\
    (This)->lpVtbl -> put_DoTextOverlay(This,newVal)

#define IMediaFile_GetZoomOutRect(This,rcSource,rcZoomIn,ppResult)	\
    (This)->lpVtbl -> GetZoomOutRect(This,rcSource,rcZoomIn,ppResult)

#define IMediaFile_ApplyMotionEffect(This,hwnd,rcReferenceRect,rcStart,rcEnd,fps,duration)	\
    (This)->lpVtbl -> ApplyMotionEffect(This,hwnd,rcReferenceRect,rcStart,rcEnd,fps,duration)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMediaFile_get_PosterFrame_Proxy( 
    IMediaFile * This,
    /* [retval][out] */ IPictureDisp **pVal);


void __RPC_STUB IMediaFile_get_PosterFrame_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMediaFile_get_Duration_Proxy( 
    IMediaFile * This,
    /* [retval][out] */ double *pVal);


void __RPC_STUB IMediaFile_get_Duration_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMediaFile_put_Duration_Proxy( 
    IMediaFile * This,
    /* [in] */ double newVal);


void __RPC_STUB IMediaFile_put_Duration_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMediaFile_get_Transition_Proxy( 
    IMediaFile * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IMediaFile_get_Transition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMediaFile_put_Transition_Proxy( 
    IMediaFile * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IMediaFile_put_Transition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMediaFile_get_StartOffset_Proxy( 
    IMediaFile * This,
    /* [retval][out] */ double *pVal);


void __RPC_STUB IMediaFile_get_StartOffset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMediaFile_put_StartOffset_Proxy( 
    IMediaFile * This,
    /* [in] */ double newVal);


void __RPC_STUB IMediaFile_put_StartOffset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMediaFile_get_FilePath_Proxy( 
    IMediaFile * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IMediaFile_get_FilePath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMediaFile_put_FilePath_Proxy( 
    IMediaFile * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IMediaFile_put_FilePath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMediaFile_get_FileTitle_Proxy( 
    IMediaFile * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IMediaFile_get_FileTitle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMediaFile_put_FileTitle_Proxy( 
    IMediaFile * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IMediaFile_put_FileTitle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMediaFile_put_PosterFramePath_Proxy( 
    IMediaFile * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IMediaFile_put_PosterFramePath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMediaFile_get_IsImage_Proxy( 
    IMediaFile * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IMediaFile_get_IsImage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMediaFile_put_IsImage_Proxy( 
    IMediaFile * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IMediaFile_put_IsImage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMediaFile_get_TransitionLength_Proxy( 
    IMediaFile * This,
    /* [retval][out] */ double *pVal);


void __RPC_STUB IMediaFile_get_TransitionLength_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMediaFile_put_TransitionLength_Proxy( 
    IMediaFile * This,
    /* [in] */ double newVal);


void __RPC_STUB IMediaFile_put_TransitionLength_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMediaFile_OverlayText_Proxy( 
    IMediaFile * This,
    /* [in] */ BSTR Text,
    /* [in] */ long xPos,
    /* [in] */ long yPos,
    /* [in] */ long Width,
    /* [in] */ long Height,
    /* [in] */ BSTR FontFace,
    /* [in] */ long FontHeight);


void __RPC_STUB IMediaFile_OverlayText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMediaFile_get_DoTextOverlay_Proxy( 
    IMediaFile * This,
    /* [retval][out] */ VARIANT_BOOL *pVal);


void __RPC_STUB IMediaFile_get_DoTextOverlay_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IMediaFile_put_DoTextOverlay_Proxy( 
    IMediaFile * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IMediaFile_put_DoTextOverlay_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMediaFile_GetZoomOutRect_Proxy( 
    IMediaFile * This,
    /* [in] */ IVideoRect **rcSource,
    /* [in] */ IVideoRect **rcZoomIn,
    /* [in] */ IVideoRect **ppResult);


void __RPC_STUB IMediaFile_GetZoomOutRect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IMediaFile_ApplyMotionEffect_Proxy( 
    IMediaFile * This,
    /* [in] */ long hwnd,
    /* [in] */ IVideoRect **rcReferenceRect,
    /* [in] */ IVideoRect **rcStart,
    /* [in] */ IVideoRect **rcEnd,
    /* [in] */ long fps,
    /* [in] */ long duration);


void __RPC_STUB IMediaFile_ApplyMotionEffect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMediaFile_INTERFACE_DEFINED__ */


#ifndef __IVideoClip_INTERFACE_DEFINED__
#define __IVideoClip_INTERFACE_DEFINED__

/* interface IVideoClip */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IVideoClip;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("423C8CAA-D940-4958-9603-EB07B9F8BD36")
    IVideoClip : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddAudio( 
            /* [in] */ long Index,
            /* [in] */ BSTR Path,
            /* [retval][out] */ IMediaFile **ppResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddVideo( 
            /* [in] */ long Index,
            /* [in] */ BSTR Path,
            /* [retval][out] */ IMediaFile **ppResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveVideo( 
            /* [in] */ long Index) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveAudio( 
            /* [in] */ long Index) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SaveClip( 
            /* [in] */ BSTR Path) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE LoadClip( 
            /* [in] */ BSTR Path) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ForcePhotoDurations( 
            /* [in] */ double NewDuration) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SpacePhotosToAudio( 
            /* [in] */ int iStartAudioItem,
            /* [in] */ int iEndAudioItem) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AudioCount( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_VideoCount( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_AudioLength( 
            /* [retval][out] */ double *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_VideoLength( 
            /* [retval][out] */ double *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MediaFile( 
            /* [in] */ MediaFormat format,
            /* [in] */ long ItemIndex,
            /* [retval][out] */ IMediaFile **pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IVideoClipVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IVideoClip * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IVideoClip * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IVideoClip * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IVideoClip * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IVideoClip * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IVideoClip * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IVideoClip * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AddAudio )( 
            IVideoClip * This,
            /* [in] */ long Index,
            /* [in] */ BSTR Path,
            /* [retval][out] */ IMediaFile **ppResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AddVideo )( 
            IVideoClip * This,
            /* [in] */ long Index,
            /* [in] */ BSTR Path,
            /* [retval][out] */ IMediaFile **ppResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RemoveVideo )( 
            IVideoClip * This,
            /* [in] */ long Index);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RemoveAudio )( 
            IVideoClip * This,
            /* [in] */ long Index);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SaveClip )( 
            IVideoClip * This,
            /* [in] */ BSTR Path);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *LoadClip )( 
            IVideoClip * This,
            /* [in] */ BSTR Path);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ForcePhotoDurations )( 
            IVideoClip * This,
            /* [in] */ double NewDuration);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SpacePhotosToAudio )( 
            IVideoClip * This,
            /* [in] */ int iStartAudioItem,
            /* [in] */ int iEndAudioItem);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AudioCount )( 
            IVideoClip * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_VideoCount )( 
            IVideoClip * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_AudioLength )( 
            IVideoClip * This,
            /* [retval][out] */ double *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_VideoLength )( 
            IVideoClip * This,
            /* [retval][out] */ double *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_MediaFile )( 
            IVideoClip * This,
            /* [in] */ MediaFormat format,
            /* [in] */ long ItemIndex,
            /* [retval][out] */ IMediaFile **pVal);
        
        END_INTERFACE
    } IVideoClipVtbl;

    interface IVideoClip
    {
        CONST_VTBL struct IVideoClipVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVideoClip_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IVideoClip_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IVideoClip_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IVideoClip_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IVideoClip_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IVideoClip_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IVideoClip_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IVideoClip_AddAudio(This,Index,Path,ppResult)	\
    (This)->lpVtbl -> AddAudio(This,Index,Path,ppResult)

#define IVideoClip_AddVideo(This,Index,Path,ppResult)	\
    (This)->lpVtbl -> AddVideo(This,Index,Path,ppResult)

#define IVideoClip_RemoveVideo(This,Index)	\
    (This)->lpVtbl -> RemoveVideo(This,Index)

#define IVideoClip_RemoveAudio(This,Index)	\
    (This)->lpVtbl -> RemoveAudio(This,Index)

#define IVideoClip_SaveClip(This,Path)	\
    (This)->lpVtbl -> SaveClip(This,Path)

#define IVideoClip_LoadClip(This,Path)	\
    (This)->lpVtbl -> LoadClip(This,Path)

#define IVideoClip_ForcePhotoDurations(This,NewDuration)	\
    (This)->lpVtbl -> ForcePhotoDurations(This,NewDuration)

#define IVideoClip_SpacePhotosToAudio(This,iStartAudioItem,iEndAudioItem)	\
    (This)->lpVtbl -> SpacePhotosToAudio(This,iStartAudioItem,iEndAudioItem)

#define IVideoClip_get_AudioCount(This,pVal)	\
    (This)->lpVtbl -> get_AudioCount(This,pVal)

#define IVideoClip_get_VideoCount(This,pVal)	\
    (This)->lpVtbl -> get_VideoCount(This,pVal)

#define IVideoClip_get_AudioLength(This,pVal)	\
    (This)->lpVtbl -> get_AudioLength(This,pVal)

#define IVideoClip_get_VideoLength(This,pVal)	\
    (This)->lpVtbl -> get_VideoLength(This,pVal)

#define IVideoClip_get_MediaFile(This,format,ItemIndex,pVal)	\
    (This)->lpVtbl -> get_MediaFile(This,format,ItemIndex,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoClip_AddAudio_Proxy( 
    IVideoClip * This,
    /* [in] */ long Index,
    /* [in] */ BSTR Path,
    /* [retval][out] */ IMediaFile **ppResult);


void __RPC_STUB IVideoClip_AddAudio_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoClip_AddVideo_Proxy( 
    IVideoClip * This,
    /* [in] */ long Index,
    /* [in] */ BSTR Path,
    /* [retval][out] */ IMediaFile **ppResult);


void __RPC_STUB IVideoClip_AddVideo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoClip_RemoveVideo_Proxy( 
    IVideoClip * This,
    /* [in] */ long Index);


void __RPC_STUB IVideoClip_RemoveVideo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoClip_RemoveAudio_Proxy( 
    IVideoClip * This,
    /* [in] */ long Index);


void __RPC_STUB IVideoClip_RemoveAudio_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoClip_SaveClip_Proxy( 
    IVideoClip * This,
    /* [in] */ BSTR Path);


void __RPC_STUB IVideoClip_SaveClip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoClip_LoadClip_Proxy( 
    IVideoClip * This,
    /* [in] */ BSTR Path);


void __RPC_STUB IVideoClip_LoadClip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoClip_ForcePhotoDurations_Proxy( 
    IVideoClip * This,
    /* [in] */ double NewDuration);


void __RPC_STUB IVideoClip_ForcePhotoDurations_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoClip_SpacePhotosToAudio_Proxy( 
    IVideoClip * This,
    /* [in] */ int iStartAudioItem,
    /* [in] */ int iEndAudioItem);


void __RPC_STUB IVideoClip_SpacePhotosToAudio_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVideoClip_get_AudioCount_Proxy( 
    IVideoClip * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IVideoClip_get_AudioCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVideoClip_get_VideoCount_Proxy( 
    IVideoClip * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IVideoClip_get_VideoCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVideoClip_get_AudioLength_Proxy( 
    IVideoClip * This,
    /* [retval][out] */ double *pVal);


void __RPC_STUB IVideoClip_get_AudioLength_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVideoClip_get_VideoLength_Proxy( 
    IVideoClip * This,
    /* [retval][out] */ double *pVal);


void __RPC_STUB IVideoClip_get_VideoLength_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVideoClip_get_MediaFile_Proxy( 
    IVideoClip * This,
    /* [in] */ MediaFormat format,
    /* [in] */ long ItemIndex,
    /* [retval][out] */ IMediaFile **pVal);


void __RPC_STUB IVideoClip_get_MediaFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IVideoClip_INTERFACE_DEFINED__ */


#ifndef __IVideoEditObj_INTERFACE_DEFINED__
#define __IVideoEditObj_INTERFACE_DEFINED__

/* interface IVideoEditObj */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IVideoEditObj;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CC95A0DF-4F4A-44BE-9BFA-02A8BAB63A27")
    IVideoEditObj : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE StartPreview( 
            /* [in] */ long ParentHwnd,
            /* [in] */ long x,
            /* [in] */ long y,
            /* [in] */ long width,
            /* [in] */ long height,
            /* [retval][out] */ VARIANT_BOOL *pResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Stop( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CompileToFile( 
            /* [in] */ BSTR OutputPath,
            /* [in] */ long Format,
            /* [retval][out] */ VARIANT_BOOL *pResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE EnumerateTransitions( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Progress( 
            /* [retval][out] */ double *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Duration( 
            /* [retval][out] */ double *pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_CurrentClip( 
            /* [retval][out] */ IVideoClip **pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_CurrentClip( 
            /* [in] */ IVideoClip **newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE InsertTemplate( 
            /* [in] */ IVideoClip **pVideoClip) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IVideoEditObjVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IVideoEditObj * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IVideoEditObj * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IVideoEditObj * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IVideoEditObj * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IVideoEditObj * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IVideoEditObj * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IVideoEditObj * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *StartPreview )( 
            IVideoEditObj * This,
            /* [in] */ long ParentHwnd,
            /* [in] */ long x,
            /* [in] */ long y,
            /* [in] */ long width,
            /* [in] */ long height,
            /* [retval][out] */ VARIANT_BOOL *pResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Stop )( 
            IVideoEditObj * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CompileToFile )( 
            IVideoEditObj * This,
            /* [in] */ BSTR OutputPath,
            /* [in] */ long Format,
            /* [retval][out] */ VARIANT_BOOL *pResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *EnumerateTransitions )( 
            IVideoEditObj * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Progress )( 
            IVideoEditObj * This,
            /* [retval][out] */ double *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Duration )( 
            IVideoEditObj * This,
            /* [retval][out] */ double *pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CurrentClip )( 
            IVideoEditObj * This,
            /* [retval][out] */ IVideoClip **pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_CurrentClip )( 
            IVideoEditObj * This,
            /* [in] */ IVideoClip **newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *InsertTemplate )( 
            IVideoEditObj * This,
            /* [in] */ IVideoClip **pVideoClip);
        
        END_INTERFACE
    } IVideoEditObjVtbl;

    interface IVideoEditObj
    {
        CONST_VTBL struct IVideoEditObjVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVideoEditObj_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IVideoEditObj_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IVideoEditObj_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IVideoEditObj_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IVideoEditObj_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IVideoEditObj_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IVideoEditObj_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IVideoEditObj_StartPreview(This,ParentHwnd,x,y,width,height,pResult)	\
    (This)->lpVtbl -> StartPreview(This,ParentHwnd,x,y,width,height,pResult)

#define IVideoEditObj_Stop(This)	\
    (This)->lpVtbl -> Stop(This)

#define IVideoEditObj_CompileToFile(This,OutputPath,Format,pResult)	\
    (This)->lpVtbl -> CompileToFile(This,OutputPath,Format,pResult)

#define IVideoEditObj_EnumerateTransitions(This)	\
    (This)->lpVtbl -> EnumerateTransitions(This)

#define IVideoEditObj_get_Progress(This,pVal)	\
    (This)->lpVtbl -> get_Progress(This,pVal)

#define IVideoEditObj_get_Duration(This,pVal)	\
    (This)->lpVtbl -> get_Duration(This,pVal)

#define IVideoEditObj_get_CurrentClip(This,pVal)	\
    (This)->lpVtbl -> get_CurrentClip(This,pVal)

#define IVideoEditObj_put_CurrentClip(This,newVal)	\
    (This)->lpVtbl -> put_CurrentClip(This,newVal)

#define IVideoEditObj_InsertTemplate(This,pVideoClip)	\
    (This)->lpVtbl -> InsertTemplate(This,pVideoClip)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoEditObj_StartPreview_Proxy( 
    IVideoEditObj * This,
    /* [in] */ long ParentHwnd,
    /* [in] */ long x,
    /* [in] */ long y,
    /* [in] */ long width,
    /* [in] */ long height,
    /* [retval][out] */ VARIANT_BOOL *pResult);


void __RPC_STUB IVideoEditObj_StartPreview_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoEditObj_Stop_Proxy( 
    IVideoEditObj * This);


void __RPC_STUB IVideoEditObj_Stop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoEditObj_CompileToFile_Proxy( 
    IVideoEditObj * This,
    /* [in] */ BSTR OutputPath,
    /* [in] */ long Format,
    /* [retval][out] */ VARIANT_BOOL *pResult);


void __RPC_STUB IVideoEditObj_CompileToFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoEditObj_EnumerateTransitions_Proxy( 
    IVideoEditObj * This);


void __RPC_STUB IVideoEditObj_EnumerateTransitions_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVideoEditObj_get_Progress_Proxy( 
    IVideoEditObj * This,
    /* [retval][out] */ double *pVal);


void __RPC_STUB IVideoEditObj_get_Progress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVideoEditObj_get_Duration_Proxy( 
    IVideoEditObj * This,
    /* [retval][out] */ double *pVal);


void __RPC_STUB IVideoEditObj_get_Duration_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IVideoEditObj_get_CurrentClip_Proxy( 
    IVideoEditObj * This,
    /* [retval][out] */ IVideoClip **pVal);


void __RPC_STUB IVideoEditObj_get_CurrentClip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IVideoEditObj_put_CurrentClip_Proxy( 
    IVideoEditObj * This,
    /* [in] */ IVideoClip **newVal);


void __RPC_STUB IVideoEditObj_put_CurrentClip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IVideoEditObj_InsertTemplate_Proxy( 
    IVideoEditObj * This,
    /* [in] */ IVideoClip **pVideoClip);


void __RPC_STUB IVideoEditObj_InsertTemplate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IVideoEditObj_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_VideoEdit;

#ifdef __cplusplus

class DECLSPEC_UUID("665A4D7D-91A5-4EA4-999A-4FAA4E5A8C50")
VideoEdit;
#endif

EXTERN_C const CLSID CLSID_MediaFile;

#ifdef __cplusplus

class DECLSPEC_UUID("CF561283-7544-4B90-9C68-49D690746B3E")
MediaFile;
#endif

EXTERN_C const CLSID CLSID_VideoClip;

#ifdef __cplusplus

class DECLSPEC_UUID("0527F33C-C731-4AC4-B7AD-6072958B1179")
VideoClip;
#endif

EXTERN_C const CLSID CLSID_VideoRect;

#ifdef __cplusplus

class DECLSPEC_UUID("95D60350-D4BF-48A4-81C6-3D25954847A3")
VideoRect;
#endif
#endif /* __VIDEOEDITLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


