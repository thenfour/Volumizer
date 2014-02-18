
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0347 */
/* at Sat May 31 22:09:04 2003
 */
/* Compiler settings for MixerLib.idl:
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

#ifndef __MixerLib_h__
#define __MixerLib_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IMixerLibrary_FWD_DEFINED__
#define __IMixerLibrary_FWD_DEFINED__
typedef interface IMixerLibrary IMixerLibrary;
#endif 	/* __IMixerLibrary_FWD_DEFINED__ */


#ifndef __IMixers_FWD_DEFINED__
#define __IMixers_FWD_DEFINED__
typedef interface IMixers IMixers;
#endif 	/* __IMixers_FWD_DEFINED__ */


#ifndef __IMixer_FWD_DEFINED__
#define __IMixer_FWD_DEFINED__
typedef interface IMixer IMixer;
#endif 	/* __IMixer_FWD_DEFINED__ */


#ifndef __IMixerDestinations_FWD_DEFINED__
#define __IMixerDestinations_FWD_DEFINED__
typedef interface IMixerDestinations IMixerDestinations;
#endif 	/* __IMixerDestinations_FWD_DEFINED__ */


#ifndef __IMixerDestination_FWD_DEFINED__
#define __IMixerDestination_FWD_DEFINED__
typedef interface IMixerDestination IMixerDestination;
#endif 	/* __IMixerDestination_FWD_DEFINED__ */


#ifndef __IMixerLines_FWD_DEFINED__
#define __IMixerLines_FWD_DEFINED__
typedef interface IMixerLines IMixerLines;
#endif 	/* __IMixerLines_FWD_DEFINED__ */


#ifndef __IMixerLine_FWD_DEFINED__
#define __IMixerLine_FWD_DEFINED__
typedef interface IMixerLine IMixerLine;
#endif 	/* __IMixerLine_FWD_DEFINED__ */


#ifndef __IMixerControls_FWD_DEFINED__
#define __IMixerControls_FWD_DEFINED__
typedef interface IMixerControls IMixerControls;
#endif 	/* __IMixerControls_FWD_DEFINED__ */


#ifndef __IMixerControl_FWD_DEFINED__
#define __IMixerControl_FWD_DEFINED__
typedef interface IMixerControl IMixerControl;
#endif 	/* __IMixerControl_FWD_DEFINED__ */


#ifndef __IEnumMixers_FWD_DEFINED__
#define __IEnumMixers_FWD_DEFINED__
typedef interface IEnumMixers IEnumMixers;
#endif 	/* __IEnumMixers_FWD_DEFINED__ */


#ifndef __IEnumMixerDestinations_FWD_DEFINED__
#define __IEnumMixerDestinations_FWD_DEFINED__
typedef interface IEnumMixerDestinations IEnumMixerDestinations;
#endif 	/* __IEnumMixerDestinations_FWD_DEFINED__ */


#ifndef __IEnumMixerLines_FWD_DEFINED__
#define __IEnumMixerLines_FWD_DEFINED__
typedef interface IEnumMixerLines IEnumMixerLines;
#endif 	/* __IEnumMixerLines_FWD_DEFINED__ */


#ifndef __IEnumMixerControls_FWD_DEFINED__
#define __IEnumMixerControls_FWD_DEFINED__
typedef interface IEnumMixerControls IEnumMixerControls;
#endif 	/* __IEnumMixerControls_FWD_DEFINED__ */


#ifndef ___IMixerEvents_FWD_DEFINED__
#define ___IMixerEvents_FWD_DEFINED__
typedef interface _IMixerEvents _IMixerEvents;
#endif 	/* ___IMixerEvents_FWD_DEFINED__ */


#ifndef __IMixerControl2_FWD_DEFINED__
#define __IMixerControl2_FWD_DEFINED__
typedef interface IMixerControl2 IMixerControl2;
#endif 	/* __IMixerControl2_FWD_DEFINED__ */


#ifndef __IMixerLine2_FWD_DEFINED__
#define __IMixerLine2_FWD_DEFINED__
typedef interface IMixerLine2 IMixerLine2;
#endif 	/* __IMixerLine2_FWD_DEFINED__ */


#ifndef __MixerLibrary_FWD_DEFINED__
#define __MixerLibrary_FWD_DEFINED__

#ifdef __cplusplus
typedef class MixerLibrary MixerLibrary;
#else
typedef struct MixerLibrary MixerLibrary;
#endif /* __cplusplus */

#endif 	/* __MixerLibrary_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 


#ifndef __MIXERLIBLib_LIBRARY_DEFINED__
#define __MIXERLIBLib_LIBRARY_DEFINED__

/* library MIXERLIBLib */
/* [helpstring][version][uuid] */ 














typedef 
enum _MixDestination
    {	MIXD_INVALID	= 0,
	MIXD_HEADPHONES	= 1,
	MIXD_LINE	= 2,
	MIXD_MONITOR	= 3,
	MIXD_SPEAKERS	= 4,
	MIXD_TELEPHONE	= 5,
	MIXD_UNDEFINED	= 6,
	MIXD_VOICEIN	= 7,
	MIXD_WAVEIN	= 8,
	MIXD_DIGITAL	= 9
    } 	MIX_DESTINATION;

typedef 
enum _MixLine
    {	MIXL_INVALID	= 0,
	MIXL_AUXILIARY	= 1,
	MIXL_COMPACTDISC	= 2,
	MIXL_DIGITAL	= 3,
	MIXL_LINE	= 4,
	MIXL_MICROPHONE	= 5,
	MIXL_PCSPEAKER	= 6,
	MIXL_SYNTHESIZER	= 7,
	MIXL_TELEPHONE	= 8,
	MIXL_UNDEFINED	= 9,
	MIXL_WAVEOUT	= 10,
	MIXL_SELF	= 11,
	MIXL_ANALOG	= 12
    } 	MIX_LINE;

typedef 
enum _MixControl
    {	MIXC_INVALID	= 0,
	MIXC_BASS	= 1,
	MIXC_EQUALIZER	= 2,
	MIXC_FADER	= 3,
	MIXC_TREBLE	= 4,
	MIXC_VOLUME	= 5,
	MIXC_MIXER	= 20,
	MIXC_MULTIPLESELECT	= 21,
	MIXC_MUX	= 22,
	MIXC_SINGLESELECT	= 23,
	MIXC_BOOLEANMETER	= 40,
	MIXC_PEAKMETER	= 41,
	MIXC_SIGNEDMETER	= 42,
	MIXC_UNSIGNEDMETER	= 43,
	MIXC_DECIBELS	= 60,
	MIXC_PERCENT	= 61,
	MIXC_SIGNED	= 62,
	MIXC_UNSIGNED	= 63,
	MIXC_PAN	= 80,
	MIXC_QSOUNDPAN	= 81,
	MIXC_SLIDER	= 82,
	MIXC_BOOLEAN	= 100,
	MIXC_BUTTON	= 101,
	MIXC_LOUDNESS	= 102,
	MIXC_MONO	= 103,
	MIXC_MUTE	= 104,
	MIXC_ONOFF	= 105,
	MIXC_STEREOENH	= 106,
	MIXC_BASS_BOOST	= 107,
	MIXC_MICROTIME	= 120,
	MIXC_MILLITIME	= 121,
	MIXC_CUSTOM	= 140,
	MIXC_UNDEFINED	= 141
    } 	MIX_CONTROL;

typedef 
enum _MixDataType
    {	MIXDT_INVALID	= 0,
	MIXDT_CUSTOM	= 1,
	MIXDT_BOOLEAN	= 2,
	MIXDT_SIGNED	= 3,
	MIXDT_UNSIGNED	= 4,
	MIXDT_STRING	= 5,
	MIXDT_UNDEFINED	= 6
    } 	MIX_DATATYPE;


EXTERN_C const IID LIBID_MIXERLIBLib;

#ifndef __IMixerLibrary_INTERFACE_DEFINED__
#define __IMixerLibrary_INTERFACE_DEFINED__

/* interface IMixerLibrary */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IMixerLibrary;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F3C28A5C-EB2D-4ECB-B2DB-E23F917CD266")
    IMixerLibrary : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Load( 
            /* [in] */ VARIANT v) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_mixers( 
            /* [retval][out] */ IMixers **pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Save( 
            /* [in] */ VARIANT v) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE EnumMixers( 
            /* [retval][out] */ IEnumMixers **ppVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_mixer_count( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetMixer( 
            /* [in] */ long id,
            /* [retval][out] */ IMixer **pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetDestination( 
            /* [in] */ long idMixer,
            /* [in] */ MIX_DESTINATION Dest,
            /* [retval][out] */ IMixerDestination **pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetControl( 
            /* [in] */ long idMixer,
            /* [in] */ MIX_DESTINATION dest,
            /* [in] */ MIX_LINE line,
            /* [in] */ MIX_CONTROL control,
            /* [retval][out] */ IMixerControl **pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetLine( 
            /* [in] */ long idMixer,
            /* [in] */ MIX_DESTINATION dest,
            /* [in] */ MIX_LINE line,
            /* [retval][out] */ IMixerLine **pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Refresh( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMixerLibraryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMixerLibrary * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMixerLibrary * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMixerLibrary * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Load )( 
            IMixerLibrary * This,
            /* [in] */ VARIANT v);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_mixers )( 
            IMixerLibrary * This,
            /* [retval][out] */ IMixers **pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Save )( 
            IMixerLibrary * This,
            /* [in] */ VARIANT v);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *EnumMixers )( 
            IMixerLibrary * This,
            /* [retval][out] */ IEnumMixers **ppVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_mixer_count )( 
            IMixerLibrary * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetMixer )( 
            IMixerLibrary * This,
            /* [in] */ long id,
            /* [retval][out] */ IMixer **pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetDestination )( 
            IMixerLibrary * This,
            /* [in] */ long idMixer,
            /* [in] */ MIX_DESTINATION Dest,
            /* [retval][out] */ IMixerDestination **pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetControl )( 
            IMixerLibrary * This,
            /* [in] */ long idMixer,
            /* [in] */ MIX_DESTINATION dest,
            /* [in] */ MIX_LINE line,
            /* [in] */ MIX_CONTROL control,
            /* [retval][out] */ IMixerControl **pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetLine )( 
            IMixerLibrary * This,
            /* [in] */ long idMixer,
            /* [in] */ MIX_DESTINATION dest,
            /* [in] */ MIX_LINE line,
            /* [retval][out] */ IMixerLine **pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Refresh )( 
            IMixerLibrary * This);
        
        END_INTERFACE
    } IMixerLibraryVtbl;

    interface IMixerLibrary
    {
        CONST_VTBL struct IMixerLibraryVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMixerLibrary_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMixerLibrary_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMixerLibrary_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMixerLibrary_Load(This,v)	\
    (This)->lpVtbl -> Load(This,v)

#define IMixerLibrary_get_mixers(This,pVal)	\
    (This)->lpVtbl -> get_mixers(This,pVal)

#define IMixerLibrary_Save(This,v)	\
    (This)->lpVtbl -> Save(This,v)

#define IMixerLibrary_EnumMixers(This,ppVal)	\
    (This)->lpVtbl -> EnumMixers(This,ppVal)

#define IMixerLibrary_get_mixer_count(This,pVal)	\
    (This)->lpVtbl -> get_mixer_count(This,pVal)

#define IMixerLibrary_GetMixer(This,id,pVal)	\
    (This)->lpVtbl -> GetMixer(This,id,pVal)

#define IMixerLibrary_GetDestination(This,idMixer,Dest,pVal)	\
    (This)->lpVtbl -> GetDestination(This,idMixer,Dest,pVal)

#define IMixerLibrary_GetControl(This,idMixer,dest,line,control,pVal)	\
    (This)->lpVtbl -> GetControl(This,idMixer,dest,line,control,pVal)

#define IMixerLibrary_GetLine(This,idMixer,dest,line,pVal)	\
    (This)->lpVtbl -> GetLine(This,idMixer,dest,line,pVal)

#define IMixerLibrary_Refresh(This)	\
    (This)->lpVtbl -> Refresh(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMixerLibrary_Load_Proxy( 
    IMixerLibrary * This,
    /* [in] */ VARIANT v);


void __RPC_STUB IMixerLibrary_Load_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IMixerLibrary_get_mixers_Proxy( 
    IMixerLibrary * This,
    /* [retval][out] */ IMixers **pVal);


void __RPC_STUB IMixerLibrary_get_mixers_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMixerLibrary_Save_Proxy( 
    IMixerLibrary * This,
    /* [in] */ VARIANT v);


void __RPC_STUB IMixerLibrary_Save_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMixerLibrary_EnumMixers_Proxy( 
    IMixerLibrary * This,
    /* [retval][out] */ IEnumMixers **ppVal);


void __RPC_STUB IMixerLibrary_EnumMixers_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IMixerLibrary_get_mixer_count_Proxy( 
    IMixerLibrary * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IMixerLibrary_get_mixer_count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMixerLibrary_GetMixer_Proxy( 
    IMixerLibrary * This,
    /* [in] */ long id,
    /* [retval][out] */ IMixer **pVal);


void __RPC_STUB IMixerLibrary_GetMixer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMixerLibrary_GetDestination_Proxy( 
    IMixerLibrary * This,
    /* [in] */ long idMixer,
    /* [in] */ MIX_DESTINATION Dest,
    /* [retval][out] */ IMixerDestination **pVal);


void __RPC_STUB IMixerLibrary_GetDestination_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMixerLibrary_GetControl_Proxy( 
    IMixerLibrary * This,
    /* [in] */ long idMixer,
    /* [in] */ MIX_DESTINATION dest,
    /* [in] */ MIX_LINE line,
    /* [in] */ MIX_CONTROL control,
    /* [retval][out] */ IMixerControl **pVal);


void __RPC_STUB IMixerLibrary_GetControl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMixerLibrary_GetLine_Proxy( 
    IMixerLibrary * This,
    /* [in] */ long idMixer,
    /* [in] */ MIX_DESTINATION dest,
    /* [in] */ MIX_LINE line,
    /* [retval][out] */ IMixerLine **pVal);


void __RPC_STUB IMixerLibrary_GetLine_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMixerLibrary_Refresh_Proxy( 
    IMixerLibrary * This);


void __RPC_STUB IMixerLibrary_Refresh_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMixerLibrary_INTERFACE_DEFINED__ */


#ifndef __IMixers_INTERFACE_DEFINED__
#define __IMixers_INTERFACE_DEFINED__

/* interface IMixers */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IMixers;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("22E07A74-2409-4AAF-BE7E-66F6F0B10A3E")
    IMixers : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ VARIANT i,
            /* [retval][out] */ IMixer **pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMixersVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMixers * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMixers * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMixers * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IMixers * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IMixers * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IMixers * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IMixers * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IMixers * This,
            /* [in] */ VARIANT i,
            /* [retval][out] */ IMixer **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IMixers * This,
            /* [retval][out] */ IUnknown **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IMixers * This,
            /* [retval][out] */ long *pVal);
        
        END_INTERFACE
    } IMixersVtbl;

    interface IMixers
    {
        CONST_VTBL struct IMixersVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMixers_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMixers_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMixers_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMixers_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IMixers_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IMixers_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IMixers_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IMixers_get_Item(This,i,pVal)	\
    (This)->lpVtbl -> get_Item(This,i,pVal)

#define IMixers_get__NewEnum(This,pVal)	\
    (This)->lpVtbl -> get__NewEnum(This,pVal)

#define IMixers_get_Count(This,pVal)	\
    (This)->lpVtbl -> get_Count(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMixers_get_Item_Proxy( 
    IMixers * This,
    /* [in] */ VARIANT i,
    /* [retval][out] */ IMixer **pVal);


void __RPC_STUB IMixers_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMixers_get__NewEnum_Proxy( 
    IMixers * This,
    /* [retval][out] */ IUnknown **pVal);


void __RPC_STUB IMixers_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMixers_get_Count_Proxy( 
    IMixers * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IMixers_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMixers_INTERFACE_DEFINED__ */


#ifndef __IMixer_INTERFACE_DEFINED__
#define __IMixer_INTERFACE_DEFINED__

/* interface IMixer */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IMixer;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("44F401CA-0CB5-4956-A5CE-F0D37F68A9C8")
    IMixer : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_name( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_destinations( 
            /* [retval][out] */ IMixerDestinations **pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE EnumDestinations( 
            /* [retval][out] */ IEnumMixerDestinations **ppVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_destination_count( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetDestination( 
            /* [in] */ MIX_DESTINATION dest,
            /* [retval][out] */ IMixerDestination **pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetLine( 
            /* [in] */ MIX_DESTINATION dest,
            /* [in] */ MIX_LINE line,
            /* [retval][out] */ IMixerLine **pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetControl( 
            /* [in] */ MIX_DESTINATION dest,
            /* [in] */ MIX_LINE line,
            /* [in] */ MIX_CONTROL control,
            /* [retval][out] */ IMixerControl **pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Load( 
            /* [in] */ VARIANT v) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Save( 
            /* [in] */ VARIANT v) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_manufacturer( 
            /* [retval][out] */ short *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_product( 
            /* [retval][out] */ short *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_version_major( 
            /* [retval][out] */ short *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_version_minor( 
            /* [retval][out] */ short *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_owner( 
            /* [retval][out] */ IMixerLibrary **pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Refresh( void) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_mixerid( 
            /* [retval][out] */ DWORD *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetDestinationByID( 
            /* [in] */ unsigned long ulId,
            /* [out] */ IMixerDestination **pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetLineByID( 
            /* [in] */ unsigned long ulId,
            /* [out] */ IMixerLine **pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetControlByID( 
            /* [in] */ unsigned long ulId,
            /* [out] */ IMixerControl **pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMixerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMixer * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMixer * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMixer * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_name )( 
            IMixer * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_destinations )( 
            IMixer * This,
            /* [retval][out] */ IMixerDestinations **pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *EnumDestinations )( 
            IMixer * This,
            /* [retval][out] */ IEnumMixerDestinations **ppVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_destination_count )( 
            IMixer * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetDestination )( 
            IMixer * This,
            /* [in] */ MIX_DESTINATION dest,
            /* [retval][out] */ IMixerDestination **pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetLine )( 
            IMixer * This,
            /* [in] */ MIX_DESTINATION dest,
            /* [in] */ MIX_LINE line,
            /* [retval][out] */ IMixerLine **pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetControl )( 
            IMixer * This,
            /* [in] */ MIX_DESTINATION dest,
            /* [in] */ MIX_LINE line,
            /* [in] */ MIX_CONTROL control,
            /* [retval][out] */ IMixerControl **pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Load )( 
            IMixer * This,
            /* [in] */ VARIANT v);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Save )( 
            IMixer * This,
            /* [in] */ VARIANT v);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_manufacturer )( 
            IMixer * This,
            /* [retval][out] */ short *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_product )( 
            IMixer * This,
            /* [retval][out] */ short *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_version_major )( 
            IMixer * This,
            /* [retval][out] */ short *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_version_minor )( 
            IMixer * This,
            /* [retval][out] */ short *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_owner )( 
            IMixer * This,
            /* [retval][out] */ IMixerLibrary **pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Refresh )( 
            IMixer * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_mixerid )( 
            IMixer * This,
            /* [retval][out] */ DWORD *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetDestinationByID )( 
            IMixer * This,
            /* [in] */ unsigned long ulId,
            /* [out] */ IMixerDestination **pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetLineByID )( 
            IMixer * This,
            /* [in] */ unsigned long ulId,
            /* [out] */ IMixerLine **pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetControlByID )( 
            IMixer * This,
            /* [in] */ unsigned long ulId,
            /* [out] */ IMixerControl **pVal);
        
        END_INTERFACE
    } IMixerVtbl;

    interface IMixer
    {
        CONST_VTBL struct IMixerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMixer_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMixer_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMixer_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMixer_get_name(This,pVal)	\
    (This)->lpVtbl -> get_name(This,pVal)

#define IMixer_get_destinations(This,pVal)	\
    (This)->lpVtbl -> get_destinations(This,pVal)

#define IMixer_EnumDestinations(This,ppVal)	\
    (This)->lpVtbl -> EnumDestinations(This,ppVal)

#define IMixer_get_destination_count(This,pVal)	\
    (This)->lpVtbl -> get_destination_count(This,pVal)

#define IMixer_GetDestination(This,dest,pVal)	\
    (This)->lpVtbl -> GetDestination(This,dest,pVal)

#define IMixer_GetLine(This,dest,line,pVal)	\
    (This)->lpVtbl -> GetLine(This,dest,line,pVal)

#define IMixer_GetControl(This,dest,line,control,pVal)	\
    (This)->lpVtbl -> GetControl(This,dest,line,control,pVal)

#define IMixer_Load(This,v)	\
    (This)->lpVtbl -> Load(This,v)

#define IMixer_Save(This,v)	\
    (This)->lpVtbl -> Save(This,v)

#define IMixer_get_manufacturer(This,pVal)	\
    (This)->lpVtbl -> get_manufacturer(This,pVal)

#define IMixer_get_product(This,pVal)	\
    (This)->lpVtbl -> get_product(This,pVal)

#define IMixer_get_version_major(This,pVal)	\
    (This)->lpVtbl -> get_version_major(This,pVal)

#define IMixer_get_version_minor(This,pVal)	\
    (This)->lpVtbl -> get_version_minor(This,pVal)

#define IMixer_get_owner(This,pVal)	\
    (This)->lpVtbl -> get_owner(This,pVal)

#define IMixer_Refresh(This)	\
    (This)->lpVtbl -> Refresh(This)

#define IMixer_get_mixerid(This,pVal)	\
    (This)->lpVtbl -> get_mixerid(This,pVal)

#define IMixer_GetDestinationByID(This,ulId,pVal)	\
    (This)->lpVtbl -> GetDestinationByID(This,ulId,pVal)

#define IMixer_GetLineByID(This,ulId,pVal)	\
    (This)->lpVtbl -> GetLineByID(This,ulId,pVal)

#define IMixer_GetControlByID(This,ulId,pVal)	\
    (This)->lpVtbl -> GetControlByID(This,ulId,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IMixer_get_name_Proxy( 
    IMixer * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IMixer_get_name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IMixer_get_destinations_Proxy( 
    IMixer * This,
    /* [retval][out] */ IMixerDestinations **pVal);


void __RPC_STUB IMixer_get_destinations_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMixer_EnumDestinations_Proxy( 
    IMixer * This,
    /* [retval][out] */ IEnumMixerDestinations **ppVal);


void __RPC_STUB IMixer_EnumDestinations_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IMixer_get_destination_count_Proxy( 
    IMixer * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IMixer_get_destination_count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMixer_GetDestination_Proxy( 
    IMixer * This,
    /* [in] */ MIX_DESTINATION dest,
    /* [retval][out] */ IMixerDestination **pVal);


void __RPC_STUB IMixer_GetDestination_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMixer_GetLine_Proxy( 
    IMixer * This,
    /* [in] */ MIX_DESTINATION dest,
    /* [in] */ MIX_LINE line,
    /* [retval][out] */ IMixerLine **pVal);


void __RPC_STUB IMixer_GetLine_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMixer_GetControl_Proxy( 
    IMixer * This,
    /* [in] */ MIX_DESTINATION dest,
    /* [in] */ MIX_LINE line,
    /* [in] */ MIX_CONTROL control,
    /* [retval][out] */ IMixerControl **pVal);


void __RPC_STUB IMixer_GetControl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMixer_Load_Proxy( 
    IMixer * This,
    /* [in] */ VARIANT v);


void __RPC_STUB IMixer_Load_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMixer_Save_Proxy( 
    IMixer * This,
    /* [in] */ VARIANT v);


void __RPC_STUB IMixer_Save_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IMixer_get_manufacturer_Proxy( 
    IMixer * This,
    /* [retval][out] */ short *pVal);


void __RPC_STUB IMixer_get_manufacturer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IMixer_get_product_Proxy( 
    IMixer * This,
    /* [retval][out] */ short *pVal);


void __RPC_STUB IMixer_get_product_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IMixer_get_version_major_Proxy( 
    IMixer * This,
    /* [retval][out] */ short *pVal);


void __RPC_STUB IMixer_get_version_major_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IMixer_get_version_minor_Proxy( 
    IMixer * This,
    /* [retval][out] */ short *pVal);


void __RPC_STUB IMixer_get_version_minor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IMixer_get_owner_Proxy( 
    IMixer * This,
    /* [retval][out] */ IMixerLibrary **pVal);


void __RPC_STUB IMixer_get_owner_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMixer_Refresh_Proxy( 
    IMixer * This);


void __RPC_STUB IMixer_Refresh_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IMixer_get_mixerid_Proxy( 
    IMixer * This,
    /* [retval][out] */ DWORD *pVal);


void __RPC_STUB IMixer_get_mixerid_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMixer_GetDestinationByID_Proxy( 
    IMixer * This,
    /* [in] */ unsigned long ulId,
    /* [out] */ IMixerDestination **pVal);


void __RPC_STUB IMixer_GetDestinationByID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMixer_GetLineByID_Proxy( 
    IMixer * This,
    /* [in] */ unsigned long ulId,
    /* [out] */ IMixerLine **pVal);


void __RPC_STUB IMixer_GetLineByID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMixer_GetControlByID_Proxy( 
    IMixer * This,
    /* [in] */ unsigned long ulId,
    /* [out] */ IMixerControl **pVal);


void __RPC_STUB IMixer_GetControlByID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMixer_INTERFACE_DEFINED__ */


#ifndef __IMixerDestinations_INTERFACE_DEFINED__
#define __IMixerDestinations_INTERFACE_DEFINED__

/* interface IMixerDestinations */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IMixerDestinations;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6908530F-B57A-4BDE-B9A2-0F39D27EE500")
    IMixerDestinations : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ VARIANT i,
            /* [retval][out] */ IMixerDestination **pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMixerDestinationsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMixerDestinations * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMixerDestinations * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMixerDestinations * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IMixerDestinations * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IMixerDestinations * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IMixerDestinations * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IMixerDestinations * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IMixerDestinations * This,
            /* [in] */ VARIANT i,
            /* [retval][out] */ IMixerDestination **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IMixerDestinations * This,
            /* [retval][out] */ IUnknown **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IMixerDestinations * This,
            /* [retval][out] */ long *pVal);
        
        END_INTERFACE
    } IMixerDestinationsVtbl;

    interface IMixerDestinations
    {
        CONST_VTBL struct IMixerDestinationsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMixerDestinations_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMixerDestinations_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMixerDestinations_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMixerDestinations_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IMixerDestinations_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IMixerDestinations_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IMixerDestinations_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IMixerDestinations_get_Item(This,i,pVal)	\
    (This)->lpVtbl -> get_Item(This,i,pVal)

#define IMixerDestinations_get__NewEnum(This,pVal)	\
    (This)->lpVtbl -> get__NewEnum(This,pVal)

#define IMixerDestinations_get_Count(This,pVal)	\
    (This)->lpVtbl -> get_Count(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMixerDestinations_get_Item_Proxy( 
    IMixerDestinations * This,
    /* [in] */ VARIANT i,
    /* [retval][out] */ IMixerDestination **pVal);


void __RPC_STUB IMixerDestinations_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMixerDestinations_get__NewEnum_Proxy( 
    IMixerDestinations * This,
    /* [retval][out] */ IUnknown **pVal);


void __RPC_STUB IMixerDestinations_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMixerDestinations_get_Count_Proxy( 
    IMixerDestinations * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IMixerDestinations_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMixerDestinations_INTERFACE_DEFINED__ */


#ifndef __IMixerDestination_INTERFACE_DEFINED__
#define __IMixerDestination_INTERFACE_DEFINED__

/* interface IMixerDestination */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IMixerDestination;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("FCD62288-AE72-4297-BF05-40EE82233D48")
    IMixerDestination : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_lines( 
            /* [retval][out] */ IMixerLines **pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE EnumLines( 
            /* [retval][out] */ IEnumMixerLines **ppVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_line_count( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetLine( 
            /* [in] */ MIX_LINE line,
            /* [retval][out] */ IMixerLine **pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetLineControl( 
            /* [in] */ MIX_LINE line,
            /* [in] */ MIX_CONTROL control,
            /* [retval][out] */ IMixerControl **pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_type_destination( 
            /* [retval][out] */ MIX_DESTINATION *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_owner( 
            /* [retval][out] */ IMixer **pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Refresh( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetLineByID( 
            /* [in] */ unsigned long ulId,
            /* [out] */ IMixerLine **pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetLineControlByID( 
            /* [in] */ unsigned long ulId,
            /* [out] */ IMixerControl **pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SaveDestination( 
            /* [in] */ VARIANT v) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE LoadDestination( 
            /* [in] */ VARIANT v) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMixerDestinationVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMixerDestination * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMixerDestination * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMixerDestination * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_lines )( 
            IMixerDestination * This,
            /* [retval][out] */ IMixerLines **pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *EnumLines )( 
            IMixerDestination * This,
            /* [retval][out] */ IEnumMixerLines **ppVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_line_count )( 
            IMixerDestination * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetLine )( 
            IMixerDestination * This,
            /* [in] */ MIX_LINE line,
            /* [retval][out] */ IMixerLine **pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetLineControl )( 
            IMixerDestination * This,
            /* [in] */ MIX_LINE line,
            /* [in] */ MIX_CONTROL control,
            /* [retval][out] */ IMixerControl **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_type_destination )( 
            IMixerDestination * This,
            /* [retval][out] */ MIX_DESTINATION *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_owner )( 
            IMixerDestination * This,
            /* [retval][out] */ IMixer **pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Refresh )( 
            IMixerDestination * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetLineByID )( 
            IMixerDestination * This,
            /* [in] */ unsigned long ulId,
            /* [out] */ IMixerLine **pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetLineControlByID )( 
            IMixerDestination * This,
            /* [in] */ unsigned long ulId,
            /* [out] */ IMixerControl **pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SaveDestination )( 
            IMixerDestination * This,
            /* [in] */ VARIANT v);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *LoadDestination )( 
            IMixerDestination * This,
            /* [in] */ VARIANT v);
        
        END_INTERFACE
    } IMixerDestinationVtbl;

    interface IMixerDestination
    {
        CONST_VTBL struct IMixerDestinationVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMixerDestination_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMixerDestination_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMixerDestination_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMixerDestination_get_lines(This,pVal)	\
    (This)->lpVtbl -> get_lines(This,pVal)

#define IMixerDestination_EnumLines(This,ppVal)	\
    (This)->lpVtbl -> EnumLines(This,ppVal)

#define IMixerDestination_get_line_count(This,pVal)	\
    (This)->lpVtbl -> get_line_count(This,pVal)

#define IMixerDestination_GetLine(This,line,pVal)	\
    (This)->lpVtbl -> GetLine(This,line,pVal)

#define IMixerDestination_GetLineControl(This,line,control,pVal)	\
    (This)->lpVtbl -> GetLineControl(This,line,control,pVal)

#define IMixerDestination_get_type_destination(This,pVal)	\
    (This)->lpVtbl -> get_type_destination(This,pVal)

#define IMixerDestination_get_owner(This,pVal)	\
    (This)->lpVtbl -> get_owner(This,pVal)

#define IMixerDestination_Refresh(This)	\
    (This)->lpVtbl -> Refresh(This)

#define IMixerDestination_GetLineByID(This,ulId,pVal)	\
    (This)->lpVtbl -> GetLineByID(This,ulId,pVal)

#define IMixerDestination_GetLineControlByID(This,ulId,pVal)	\
    (This)->lpVtbl -> GetLineControlByID(This,ulId,pVal)

#define IMixerDestination_SaveDestination(This,v)	\
    (This)->lpVtbl -> SaveDestination(This,v)

#define IMixerDestination_LoadDestination(This,v)	\
    (This)->lpVtbl -> LoadDestination(This,v)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IMixerDestination_get_lines_Proxy( 
    IMixerDestination * This,
    /* [retval][out] */ IMixerLines **pVal);


void __RPC_STUB IMixerDestination_get_lines_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMixerDestination_EnumLines_Proxy( 
    IMixerDestination * This,
    /* [retval][out] */ IEnumMixerLines **ppVal);


void __RPC_STUB IMixerDestination_EnumLines_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IMixerDestination_get_line_count_Proxy( 
    IMixerDestination * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IMixerDestination_get_line_count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMixerDestination_GetLine_Proxy( 
    IMixerDestination * This,
    /* [in] */ MIX_LINE line,
    /* [retval][out] */ IMixerLine **pVal);


void __RPC_STUB IMixerDestination_GetLine_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMixerDestination_GetLineControl_Proxy( 
    IMixerDestination * This,
    /* [in] */ MIX_LINE line,
    /* [in] */ MIX_CONTROL control,
    /* [retval][out] */ IMixerControl **pVal);


void __RPC_STUB IMixerDestination_GetLineControl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IMixerDestination_get_type_destination_Proxy( 
    IMixerDestination * This,
    /* [retval][out] */ MIX_DESTINATION *pVal);


void __RPC_STUB IMixerDestination_get_type_destination_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IMixerDestination_get_owner_Proxy( 
    IMixerDestination * This,
    /* [retval][out] */ IMixer **pVal);


void __RPC_STUB IMixerDestination_get_owner_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMixerDestination_Refresh_Proxy( 
    IMixerDestination * This);


void __RPC_STUB IMixerDestination_Refresh_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMixerDestination_GetLineByID_Proxy( 
    IMixerDestination * This,
    /* [in] */ unsigned long ulId,
    /* [out] */ IMixerLine **pVal);


void __RPC_STUB IMixerDestination_GetLineByID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMixerDestination_GetLineControlByID_Proxy( 
    IMixerDestination * This,
    /* [in] */ unsigned long ulId,
    /* [out] */ IMixerControl **pVal);


void __RPC_STUB IMixerDestination_GetLineControlByID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMixerDestination_SaveDestination_Proxy( 
    IMixerDestination * This,
    /* [in] */ VARIANT v);


void __RPC_STUB IMixerDestination_SaveDestination_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMixerDestination_LoadDestination_Proxy( 
    IMixerDestination * This,
    /* [in] */ VARIANT v);


void __RPC_STUB IMixerDestination_LoadDestination_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMixerDestination_INTERFACE_DEFINED__ */


#ifndef __IMixerLines_INTERFACE_DEFINED__
#define __IMixerLines_INTERFACE_DEFINED__

/* interface IMixerLines */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IMixerLines;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("85E9D4CE-B77D-4261-A093-4A1ECA0AA52B")
    IMixerLines : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ VARIANT i,
            /* [retval][out] */ IMixerLine **pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMixerLinesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMixerLines * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMixerLines * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMixerLines * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IMixerLines * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IMixerLines * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IMixerLines * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IMixerLines * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IMixerLines * This,
            /* [in] */ VARIANT i,
            /* [retval][out] */ IMixerLine **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IMixerLines * This,
            /* [retval][out] */ IUnknown **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IMixerLines * This,
            /* [retval][out] */ long *pVal);
        
        END_INTERFACE
    } IMixerLinesVtbl;

    interface IMixerLines
    {
        CONST_VTBL struct IMixerLinesVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMixerLines_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMixerLines_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMixerLines_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMixerLines_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IMixerLines_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IMixerLines_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IMixerLines_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IMixerLines_get_Item(This,i,pVal)	\
    (This)->lpVtbl -> get_Item(This,i,pVal)

#define IMixerLines_get__NewEnum(This,pVal)	\
    (This)->lpVtbl -> get__NewEnum(This,pVal)

#define IMixerLines_get_Count(This,pVal)	\
    (This)->lpVtbl -> get_Count(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMixerLines_get_Item_Proxy( 
    IMixerLines * This,
    /* [in] */ VARIANT i,
    /* [retval][out] */ IMixerLine **pVal);


void __RPC_STUB IMixerLines_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMixerLines_get__NewEnum_Proxy( 
    IMixerLines * This,
    /* [retval][out] */ IUnknown **pVal);


void __RPC_STUB IMixerLines_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMixerLines_get_Count_Proxy( 
    IMixerLines * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IMixerLines_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMixerLines_INTERFACE_DEFINED__ */


#ifndef __IMixerLine_INTERFACE_DEFINED__
#define __IMixerLine_INTERFACE_DEFINED__

/* interface IMixerLine */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IMixerLine;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4570A7A2-7213-4BD7-A93D-E5BD4717A66A")
    IMixerLine : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_name( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_controls( 
            /* [retval][out] */ IMixerControls **pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE EnumControls( 
            /* [retval][out] */ IEnumMixerControls **ppVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_control_count( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetControl( 
            /* [in] */ MIX_CONTROL control,
            /* [retval][out] */ IMixerControl **pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Load( 
            /* [in] */ VARIANT v) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Save( 
            /* [in] */ VARIANT v) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_type( 
            /* [retval][out] */ MIX_LINE *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_owner( 
            /* [retval][out] */ IMixerDestination **pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_channels( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_lineid( 
            /* [retval][out] */ unsigned long *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_short_name( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE RefreshLine( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetControlByID( 
            /* [in] */ unsigned long ulId,
            /* [out] */ IMixerControl **pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMixerLineVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMixerLine * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMixerLine * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMixerLine * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_name )( 
            IMixerLine * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_controls )( 
            IMixerLine * This,
            /* [retval][out] */ IMixerControls **pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *EnumControls )( 
            IMixerLine * This,
            /* [retval][out] */ IEnumMixerControls **ppVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_control_count )( 
            IMixerLine * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetControl )( 
            IMixerLine * This,
            /* [in] */ MIX_CONTROL control,
            /* [retval][out] */ IMixerControl **pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Load )( 
            IMixerLine * This,
            /* [in] */ VARIANT v);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Save )( 
            IMixerLine * This,
            /* [in] */ VARIANT v);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_type )( 
            IMixerLine * This,
            /* [retval][out] */ MIX_LINE *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_owner )( 
            IMixerLine * This,
            /* [retval][out] */ IMixerDestination **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_channels )( 
            IMixerLine * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_lineid )( 
            IMixerLine * This,
            /* [retval][out] */ unsigned long *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_short_name )( 
            IMixerLine * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *RefreshLine )( 
            IMixerLine * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetControlByID )( 
            IMixerLine * This,
            /* [in] */ unsigned long ulId,
            /* [out] */ IMixerControl **pVal);
        
        END_INTERFACE
    } IMixerLineVtbl;

    interface IMixerLine
    {
        CONST_VTBL struct IMixerLineVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMixerLine_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMixerLine_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMixerLine_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMixerLine_get_name(This,pVal)	\
    (This)->lpVtbl -> get_name(This,pVal)

#define IMixerLine_get_controls(This,pVal)	\
    (This)->lpVtbl -> get_controls(This,pVal)

#define IMixerLine_EnumControls(This,ppVal)	\
    (This)->lpVtbl -> EnumControls(This,ppVal)

#define IMixerLine_get_control_count(This,pVal)	\
    (This)->lpVtbl -> get_control_count(This,pVal)

#define IMixerLine_GetControl(This,control,pVal)	\
    (This)->lpVtbl -> GetControl(This,control,pVal)

#define IMixerLine_Load(This,v)	\
    (This)->lpVtbl -> Load(This,v)

#define IMixerLine_Save(This,v)	\
    (This)->lpVtbl -> Save(This,v)

#define IMixerLine_get_type(This,pVal)	\
    (This)->lpVtbl -> get_type(This,pVal)

#define IMixerLine_get_owner(This,pVal)	\
    (This)->lpVtbl -> get_owner(This,pVal)

#define IMixerLine_get_channels(This,pVal)	\
    (This)->lpVtbl -> get_channels(This,pVal)

#define IMixerLine_get_lineid(This,pVal)	\
    (This)->lpVtbl -> get_lineid(This,pVal)

#define IMixerLine_get_short_name(This,pVal)	\
    (This)->lpVtbl -> get_short_name(This,pVal)

#define IMixerLine_RefreshLine(This)	\
    (This)->lpVtbl -> RefreshLine(This)

#define IMixerLine_GetControlByID(This,ulId,pVal)	\
    (This)->lpVtbl -> GetControlByID(This,ulId,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IMixerLine_get_name_Proxy( 
    IMixerLine * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IMixerLine_get_name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IMixerLine_get_controls_Proxy( 
    IMixerLine * This,
    /* [retval][out] */ IMixerControls **pVal);


void __RPC_STUB IMixerLine_get_controls_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMixerLine_EnumControls_Proxy( 
    IMixerLine * This,
    /* [retval][out] */ IEnumMixerControls **ppVal);


void __RPC_STUB IMixerLine_EnumControls_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IMixerLine_get_control_count_Proxy( 
    IMixerLine * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IMixerLine_get_control_count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMixerLine_GetControl_Proxy( 
    IMixerLine * This,
    /* [in] */ MIX_CONTROL control,
    /* [retval][out] */ IMixerControl **pVal);


void __RPC_STUB IMixerLine_GetControl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMixerLine_Load_Proxy( 
    IMixerLine * This,
    /* [in] */ VARIANT v);


void __RPC_STUB IMixerLine_Load_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMixerLine_Save_Proxy( 
    IMixerLine * This,
    /* [in] */ VARIANT v);


void __RPC_STUB IMixerLine_Save_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IMixerLine_get_type_Proxy( 
    IMixerLine * This,
    /* [retval][out] */ MIX_LINE *pVal);


void __RPC_STUB IMixerLine_get_type_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IMixerLine_get_owner_Proxy( 
    IMixerLine * This,
    /* [retval][out] */ IMixerDestination **pVal);


void __RPC_STUB IMixerLine_get_owner_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IMixerLine_get_channels_Proxy( 
    IMixerLine * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IMixerLine_get_channels_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IMixerLine_get_lineid_Proxy( 
    IMixerLine * This,
    /* [retval][out] */ unsigned long *pVal);


void __RPC_STUB IMixerLine_get_lineid_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IMixerLine_get_short_name_Proxy( 
    IMixerLine * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IMixerLine_get_short_name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMixerLine_RefreshLine_Proxy( 
    IMixerLine * This);


void __RPC_STUB IMixerLine_RefreshLine_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMixerLine_GetControlByID_Proxy( 
    IMixerLine * This,
    /* [in] */ unsigned long ulId,
    /* [out] */ IMixerControl **pVal);


void __RPC_STUB IMixerLine_GetControlByID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMixerLine_INTERFACE_DEFINED__ */


#ifndef __IMixerControls_INTERFACE_DEFINED__
#define __IMixerControls_INTERFACE_DEFINED__

/* interface IMixerControls */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IMixerControls;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("EDABF35F-EDDE-4BF8-BCB4-251019669D6D")
    IMixerControls : public IDispatch
    {
    public:
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            /* [in] */ VARIANT i,
            /* [retval][out] */ IMixerControl **pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ IUnknown **pVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMixerControlsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMixerControls * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMixerControls * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMixerControls * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IMixerControls * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IMixerControls * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IMixerControls * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IMixerControls * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Item )( 
            IMixerControls * This,
            /* [in] */ VARIANT i,
            /* [retval][out] */ IMixerControl **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get__NewEnum )( 
            IMixerControls * This,
            /* [retval][out] */ IUnknown **pVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IMixerControls * This,
            /* [retval][out] */ long *pVal);
        
        END_INTERFACE
    } IMixerControlsVtbl;

    interface IMixerControls
    {
        CONST_VTBL struct IMixerControlsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMixerControls_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMixerControls_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMixerControls_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMixerControls_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IMixerControls_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IMixerControls_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IMixerControls_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IMixerControls_get_Item(This,i,pVal)	\
    (This)->lpVtbl -> get_Item(This,i,pVal)

#define IMixerControls_get__NewEnum(This,pVal)	\
    (This)->lpVtbl -> get__NewEnum(This,pVal)

#define IMixerControls_get_Count(This,pVal)	\
    (This)->lpVtbl -> get_Count(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMixerControls_get_Item_Proxy( 
    IMixerControls * This,
    /* [in] */ VARIANT i,
    /* [retval][out] */ IMixerControl **pVal);


void __RPC_STUB IMixerControls_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMixerControls_get__NewEnum_Proxy( 
    IMixerControls * This,
    /* [retval][out] */ IUnknown **pVal);


void __RPC_STUB IMixerControls_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IMixerControls_get_Count_Proxy( 
    IMixerControls * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IMixerControls_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMixerControls_INTERFACE_DEFINED__ */


#ifndef __IMixerControl_INTERFACE_DEFINED__
#define __IMixerControl_INTERFACE_DEFINED__

/* interface IMixerControl */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IMixerControl;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6B20150C-1051-4792-9325-97BD34C9072B")
    IMixerControl : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_name( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Load( 
            /* [in] */ VARIANT v) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Save( 
            /* [in] */ VARIANT v) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_type( 
            /* [retval][out] */ MIX_CONTROL *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_uniform( 
            /* [retval][out] */ BOOL *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_multiple( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_channels( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_datatype( 
            /* [retval][out] */ MIX_DATATYPE *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_custom_size( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_min( 
            /* [retval][out] */ VARIANT *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_max( 
            /* [retval][out] */ VARIANT *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_steps( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Refresh( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetCustomBuffer( 
            /* [out] */ BYTE **pVal,
            /* [out] */ long *pcb) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CommitCustomBuffer( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetValuesBuffer( 
            /* [out] */ VARIANT **__MIDL_0011,
            /* [out] */ long *pc) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CommitValuesBuffer( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetText( 
            /* [in] */ long id,
            /* [out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_supports_text( 
            /* [retval][out] */ BOOL *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetMuxLine( 
            /* [in] */ long id,
            /* [retval][out] */ IMixerLine **pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetValuesUniformly( 
            /* [in] */ VARIANT v) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_owner( 
            /* [retval][out] */ IMixerLine **pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_controlid( 
            /* [retval][out] */ unsigned long *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_short_name( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMixerControlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMixerControl * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMixerControl * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMixerControl * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_name )( 
            IMixerControl * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Load )( 
            IMixerControl * This,
            /* [in] */ VARIANT v);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Save )( 
            IMixerControl * This,
            /* [in] */ VARIANT v);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_type )( 
            IMixerControl * This,
            /* [retval][out] */ MIX_CONTROL *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_uniform )( 
            IMixerControl * This,
            /* [retval][out] */ BOOL *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_multiple )( 
            IMixerControl * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_channels )( 
            IMixerControl * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_datatype )( 
            IMixerControl * This,
            /* [retval][out] */ MIX_DATATYPE *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_custom_size )( 
            IMixerControl * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_min )( 
            IMixerControl * This,
            /* [retval][out] */ VARIANT *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_max )( 
            IMixerControl * This,
            /* [retval][out] */ VARIANT *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_steps )( 
            IMixerControl * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Refresh )( 
            IMixerControl * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetCustomBuffer )( 
            IMixerControl * This,
            /* [out] */ BYTE **pVal,
            /* [out] */ long *pcb);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *CommitCustomBuffer )( 
            IMixerControl * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetValuesBuffer )( 
            IMixerControl * This,
            /* [out] */ VARIANT **__MIDL_0011,
            /* [out] */ long *pc);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *CommitValuesBuffer )( 
            IMixerControl * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetText )( 
            IMixerControl * This,
            /* [in] */ long id,
            /* [out] */ BSTR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_supports_text )( 
            IMixerControl * This,
            /* [retval][out] */ BOOL *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetMuxLine )( 
            IMixerControl * This,
            /* [in] */ long id,
            /* [retval][out] */ IMixerLine **pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetValuesUniformly )( 
            IMixerControl * This,
            /* [in] */ VARIANT v);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_owner )( 
            IMixerControl * This,
            /* [retval][out] */ IMixerLine **pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_controlid )( 
            IMixerControl * This,
            /* [retval][out] */ unsigned long *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_short_name )( 
            IMixerControl * This,
            /* [retval][out] */ BSTR *pVal);
        
        END_INTERFACE
    } IMixerControlVtbl;

    interface IMixerControl
    {
        CONST_VTBL struct IMixerControlVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMixerControl_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMixerControl_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMixerControl_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMixerControl_get_name(This,pVal)	\
    (This)->lpVtbl -> get_name(This,pVal)

#define IMixerControl_Load(This,v)	\
    (This)->lpVtbl -> Load(This,v)

#define IMixerControl_Save(This,v)	\
    (This)->lpVtbl -> Save(This,v)

#define IMixerControl_get_type(This,pVal)	\
    (This)->lpVtbl -> get_type(This,pVal)

#define IMixerControl_get_uniform(This,pVal)	\
    (This)->lpVtbl -> get_uniform(This,pVal)

#define IMixerControl_get_multiple(This,pVal)	\
    (This)->lpVtbl -> get_multiple(This,pVal)

#define IMixerControl_get_channels(This,pVal)	\
    (This)->lpVtbl -> get_channels(This,pVal)

#define IMixerControl_get_datatype(This,pVal)	\
    (This)->lpVtbl -> get_datatype(This,pVal)

#define IMixerControl_get_custom_size(This,pVal)	\
    (This)->lpVtbl -> get_custom_size(This,pVal)

#define IMixerControl_get_min(This,pVal)	\
    (This)->lpVtbl -> get_min(This,pVal)

#define IMixerControl_get_max(This,pVal)	\
    (This)->lpVtbl -> get_max(This,pVal)

#define IMixerControl_get_steps(This,pVal)	\
    (This)->lpVtbl -> get_steps(This,pVal)

#define IMixerControl_Refresh(This)	\
    (This)->lpVtbl -> Refresh(This)

#define IMixerControl_GetCustomBuffer(This,pVal,pcb)	\
    (This)->lpVtbl -> GetCustomBuffer(This,pVal,pcb)

#define IMixerControl_CommitCustomBuffer(This)	\
    (This)->lpVtbl -> CommitCustomBuffer(This)

#define IMixerControl_GetValuesBuffer(This,__MIDL_0011,pc)	\
    (This)->lpVtbl -> GetValuesBuffer(This,__MIDL_0011,pc)

#define IMixerControl_CommitValuesBuffer(This)	\
    (This)->lpVtbl -> CommitValuesBuffer(This)

#define IMixerControl_GetText(This,id,pVal)	\
    (This)->lpVtbl -> GetText(This,id,pVal)

#define IMixerControl_get_supports_text(This,pVal)	\
    (This)->lpVtbl -> get_supports_text(This,pVal)

#define IMixerControl_GetMuxLine(This,id,pVal)	\
    (This)->lpVtbl -> GetMuxLine(This,id,pVal)

#define IMixerControl_SetValuesUniformly(This,v)	\
    (This)->lpVtbl -> SetValuesUniformly(This,v)

#define IMixerControl_get_owner(This,pVal)	\
    (This)->lpVtbl -> get_owner(This,pVal)

#define IMixerControl_get_controlid(This,pVal)	\
    (This)->lpVtbl -> get_controlid(This,pVal)

#define IMixerControl_get_short_name(This,pVal)	\
    (This)->lpVtbl -> get_short_name(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IMixerControl_get_name_Proxy( 
    IMixerControl * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IMixerControl_get_name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMixerControl_Load_Proxy( 
    IMixerControl * This,
    /* [in] */ VARIANT v);


void __RPC_STUB IMixerControl_Load_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMixerControl_Save_Proxy( 
    IMixerControl * This,
    /* [in] */ VARIANT v);


void __RPC_STUB IMixerControl_Save_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IMixerControl_get_type_Proxy( 
    IMixerControl * This,
    /* [retval][out] */ MIX_CONTROL *pVal);


void __RPC_STUB IMixerControl_get_type_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IMixerControl_get_uniform_Proxy( 
    IMixerControl * This,
    /* [retval][out] */ BOOL *pVal);


void __RPC_STUB IMixerControl_get_uniform_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IMixerControl_get_multiple_Proxy( 
    IMixerControl * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IMixerControl_get_multiple_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IMixerControl_get_channels_Proxy( 
    IMixerControl * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IMixerControl_get_channels_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IMixerControl_get_datatype_Proxy( 
    IMixerControl * This,
    /* [retval][out] */ MIX_DATATYPE *pVal);


void __RPC_STUB IMixerControl_get_datatype_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IMixerControl_get_custom_size_Proxy( 
    IMixerControl * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IMixerControl_get_custom_size_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IMixerControl_get_min_Proxy( 
    IMixerControl * This,
    /* [retval][out] */ VARIANT *pVal);


void __RPC_STUB IMixerControl_get_min_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IMixerControl_get_max_Proxy( 
    IMixerControl * This,
    /* [retval][out] */ VARIANT *pVal);


void __RPC_STUB IMixerControl_get_max_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IMixerControl_get_steps_Proxy( 
    IMixerControl * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IMixerControl_get_steps_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMixerControl_Refresh_Proxy( 
    IMixerControl * This);


void __RPC_STUB IMixerControl_Refresh_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMixerControl_GetCustomBuffer_Proxy( 
    IMixerControl * This,
    /* [out] */ BYTE **pVal,
    /* [out] */ long *pcb);


void __RPC_STUB IMixerControl_GetCustomBuffer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMixerControl_CommitCustomBuffer_Proxy( 
    IMixerControl * This);


void __RPC_STUB IMixerControl_CommitCustomBuffer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMixerControl_GetValuesBuffer_Proxy( 
    IMixerControl * This,
    /* [out] */ VARIANT **__MIDL_0011,
    /* [out] */ long *pc);


void __RPC_STUB IMixerControl_GetValuesBuffer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMixerControl_CommitValuesBuffer_Proxy( 
    IMixerControl * This);


void __RPC_STUB IMixerControl_CommitValuesBuffer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMixerControl_GetText_Proxy( 
    IMixerControl * This,
    /* [in] */ long id,
    /* [out] */ BSTR *pVal);


void __RPC_STUB IMixerControl_GetText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IMixerControl_get_supports_text_Proxy( 
    IMixerControl * This,
    /* [retval][out] */ BOOL *pVal);


void __RPC_STUB IMixerControl_get_supports_text_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMixerControl_GetMuxLine_Proxy( 
    IMixerControl * This,
    /* [in] */ long id,
    /* [retval][out] */ IMixerLine **pVal);


void __RPC_STUB IMixerControl_GetMuxLine_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMixerControl_SetValuesUniformly_Proxy( 
    IMixerControl * This,
    /* [in] */ VARIANT v);


void __RPC_STUB IMixerControl_SetValuesUniformly_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IMixerControl_get_owner_Proxy( 
    IMixerControl * This,
    /* [retval][out] */ IMixerLine **pVal);


void __RPC_STUB IMixerControl_get_owner_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IMixerControl_get_controlid_Proxy( 
    IMixerControl * This,
    /* [retval][out] */ unsigned long *pVal);


void __RPC_STUB IMixerControl_get_controlid_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IMixerControl_get_short_name_Proxy( 
    IMixerControl * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IMixerControl_get_short_name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMixerControl_INTERFACE_DEFINED__ */


#ifndef __IEnumMixers_INTERFACE_DEFINED__
#define __IEnumMixers_INTERFACE_DEFINED__

/* interface IEnumMixers */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEnumMixers;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9D60B0F4-9C46-4230-9FEF-DB4B167DA0DF")
    IEnumMixers : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG c,
            /* [length_is][size_is][out] */ IMixer **ppVal,
            /* [out] */ ULONG *pFetched) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG c) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumMixers **ppEnum) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEnumMixersVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumMixers * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumMixers * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumMixers * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumMixers * This,
            /* [in] */ ULONG c,
            /* [length_is][size_is][out] */ IMixer **ppVal,
            /* [out] */ ULONG *pFetched);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumMixers * This,
            /* [in] */ ULONG c);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumMixers * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumMixers * This,
            /* [out] */ IEnumMixers **ppEnum);
        
        END_INTERFACE
    } IEnumMixersVtbl;

    interface IEnumMixers
    {
        CONST_VTBL struct IEnumMixersVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumMixers_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEnumMixers_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEnumMixers_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEnumMixers_Next(This,c,ppVal,pFetched)	\
    (This)->lpVtbl -> Next(This,c,ppVal,pFetched)

#define IEnumMixers_Skip(This,c)	\
    (This)->lpVtbl -> Skip(This,c)

#define IEnumMixers_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#define IEnumMixers_Clone(This,ppEnum)	\
    (This)->lpVtbl -> Clone(This,ppEnum)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IEnumMixers_Next_Proxy( 
    IEnumMixers * This,
    /* [in] */ ULONG c,
    /* [length_is][size_is][out] */ IMixer **ppVal,
    /* [out] */ ULONG *pFetched);


void __RPC_STUB IEnumMixers_Next_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IEnumMixers_Skip_Proxy( 
    IEnumMixers * This,
    /* [in] */ ULONG c);


void __RPC_STUB IEnumMixers_Skip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IEnumMixers_Reset_Proxy( 
    IEnumMixers * This);


void __RPC_STUB IEnumMixers_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IEnumMixers_Clone_Proxy( 
    IEnumMixers * This,
    /* [out] */ IEnumMixers **ppEnum);


void __RPC_STUB IEnumMixers_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEnumMixers_INTERFACE_DEFINED__ */


#ifndef __IEnumMixerDestinations_INTERFACE_DEFINED__
#define __IEnumMixerDestinations_INTERFACE_DEFINED__

/* interface IEnumMixerDestinations */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEnumMixerDestinations;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("221FD072-E504-49A7-B7B0-8CC54F8FDCAE")
    IEnumMixerDestinations : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG c,
            /* [length_is][size_is][out] */ IMixerDestination **ppVal,
            /* [out] */ ULONG *pFetched) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG c) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumMixerDestinations **ppEnum) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEnumMixerDestinationsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumMixerDestinations * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumMixerDestinations * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumMixerDestinations * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumMixerDestinations * This,
            /* [in] */ ULONG c,
            /* [length_is][size_is][out] */ IMixerDestination **ppVal,
            /* [out] */ ULONG *pFetched);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumMixerDestinations * This,
            /* [in] */ ULONG c);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumMixerDestinations * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumMixerDestinations * This,
            /* [out] */ IEnumMixerDestinations **ppEnum);
        
        END_INTERFACE
    } IEnumMixerDestinationsVtbl;

    interface IEnumMixerDestinations
    {
        CONST_VTBL struct IEnumMixerDestinationsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumMixerDestinations_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEnumMixerDestinations_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEnumMixerDestinations_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEnumMixerDestinations_Next(This,c,ppVal,pFetched)	\
    (This)->lpVtbl -> Next(This,c,ppVal,pFetched)

#define IEnumMixerDestinations_Skip(This,c)	\
    (This)->lpVtbl -> Skip(This,c)

#define IEnumMixerDestinations_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#define IEnumMixerDestinations_Clone(This,ppEnum)	\
    (This)->lpVtbl -> Clone(This,ppEnum)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IEnumMixerDestinations_Next_Proxy( 
    IEnumMixerDestinations * This,
    /* [in] */ ULONG c,
    /* [length_is][size_is][out] */ IMixerDestination **ppVal,
    /* [out] */ ULONG *pFetched);


void __RPC_STUB IEnumMixerDestinations_Next_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IEnumMixerDestinations_Skip_Proxy( 
    IEnumMixerDestinations * This,
    /* [in] */ ULONG c);


void __RPC_STUB IEnumMixerDestinations_Skip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IEnumMixerDestinations_Reset_Proxy( 
    IEnumMixerDestinations * This);


void __RPC_STUB IEnumMixerDestinations_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IEnumMixerDestinations_Clone_Proxy( 
    IEnumMixerDestinations * This,
    /* [out] */ IEnumMixerDestinations **ppEnum);


void __RPC_STUB IEnumMixerDestinations_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEnumMixerDestinations_INTERFACE_DEFINED__ */


#ifndef __IEnumMixerLines_INTERFACE_DEFINED__
#define __IEnumMixerLines_INTERFACE_DEFINED__

/* interface IEnumMixerLines */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEnumMixerLines;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E7E51097-9DD7-4D8C-999A-7ACE8FAB2394")
    IEnumMixerLines : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG c,
            /* [length_is][size_is][out] */ IMixerLine **ppVal,
            /* [out] */ ULONG *pFetched) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG c) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumMixerLines **ppEnum) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEnumMixerLinesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumMixerLines * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumMixerLines * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumMixerLines * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumMixerLines * This,
            /* [in] */ ULONG c,
            /* [length_is][size_is][out] */ IMixerLine **ppVal,
            /* [out] */ ULONG *pFetched);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumMixerLines * This,
            /* [in] */ ULONG c);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumMixerLines * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumMixerLines * This,
            /* [out] */ IEnumMixerLines **ppEnum);
        
        END_INTERFACE
    } IEnumMixerLinesVtbl;

    interface IEnumMixerLines
    {
        CONST_VTBL struct IEnumMixerLinesVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumMixerLines_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEnumMixerLines_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEnumMixerLines_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEnumMixerLines_Next(This,c,ppVal,pFetched)	\
    (This)->lpVtbl -> Next(This,c,ppVal,pFetched)

#define IEnumMixerLines_Skip(This,c)	\
    (This)->lpVtbl -> Skip(This,c)

#define IEnumMixerLines_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#define IEnumMixerLines_Clone(This,ppEnum)	\
    (This)->lpVtbl -> Clone(This,ppEnum)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IEnumMixerLines_Next_Proxy( 
    IEnumMixerLines * This,
    /* [in] */ ULONG c,
    /* [length_is][size_is][out] */ IMixerLine **ppVal,
    /* [out] */ ULONG *pFetched);


void __RPC_STUB IEnumMixerLines_Next_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IEnumMixerLines_Skip_Proxy( 
    IEnumMixerLines * This,
    /* [in] */ ULONG c);


void __RPC_STUB IEnumMixerLines_Skip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IEnumMixerLines_Reset_Proxy( 
    IEnumMixerLines * This);


void __RPC_STUB IEnumMixerLines_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IEnumMixerLines_Clone_Proxy( 
    IEnumMixerLines * This,
    /* [out] */ IEnumMixerLines **ppEnum);


void __RPC_STUB IEnumMixerLines_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEnumMixerLines_INTERFACE_DEFINED__ */


#ifndef __IEnumMixerControls_INTERFACE_DEFINED__
#define __IEnumMixerControls_INTERFACE_DEFINED__

/* interface IEnumMixerControls */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEnumMixerControls;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2A23E48A-F952-44E8-B45C-177A26F1032B")
    IEnumMixerControls : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG c,
            /* [length_is][size_is][out] */ IMixerControl **ppVal,
            /* [out] */ ULONG *pFetched) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG c) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumMixerControls **ppEnum) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEnumMixerControlsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumMixerControls * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumMixerControls * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumMixerControls * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumMixerControls * This,
            /* [in] */ ULONG c,
            /* [length_is][size_is][out] */ IMixerControl **ppVal,
            /* [out] */ ULONG *pFetched);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumMixerControls * This,
            /* [in] */ ULONG c);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumMixerControls * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumMixerControls * This,
            /* [out] */ IEnumMixerControls **ppEnum);
        
        END_INTERFACE
    } IEnumMixerControlsVtbl;

    interface IEnumMixerControls
    {
        CONST_VTBL struct IEnumMixerControlsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumMixerControls_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEnumMixerControls_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEnumMixerControls_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEnumMixerControls_Next(This,c,ppVal,pFetched)	\
    (This)->lpVtbl -> Next(This,c,ppVal,pFetched)

#define IEnumMixerControls_Skip(This,c)	\
    (This)->lpVtbl -> Skip(This,c)

#define IEnumMixerControls_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#define IEnumMixerControls_Clone(This,ppEnum)	\
    (This)->lpVtbl -> Clone(This,ppEnum)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IEnumMixerControls_Next_Proxy( 
    IEnumMixerControls * This,
    /* [in] */ ULONG c,
    /* [length_is][size_is][out] */ IMixerControl **ppVal,
    /* [out] */ ULONG *pFetched);


void __RPC_STUB IEnumMixerControls_Next_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IEnumMixerControls_Skip_Proxy( 
    IEnumMixerControls * This,
    /* [in] */ ULONG c);


void __RPC_STUB IEnumMixerControls_Skip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IEnumMixerControls_Reset_Proxy( 
    IEnumMixerControls * This);


void __RPC_STUB IEnumMixerControls_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IEnumMixerControls_Clone_Proxy( 
    IEnumMixerControls * This,
    /* [out] */ IEnumMixerControls **ppEnum);


void __RPC_STUB IEnumMixerControls_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEnumMixerControls_INTERFACE_DEFINED__ */


#ifndef ___IMixerEvents_DISPINTERFACE_DEFINED__
#define ___IMixerEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IMixerEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__IMixerEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("9f05af25-61d8-4427-953b-1243d58df616")
    _IMixerEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IMixerEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IMixerEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IMixerEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IMixerEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IMixerEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IMixerEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IMixerEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IMixerEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _IMixerEventsVtbl;

    interface _IMixerEvents
    {
        CONST_VTBL struct _IMixerEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IMixerEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _IMixerEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _IMixerEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _IMixerEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _IMixerEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _IMixerEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _IMixerEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IMixerEvents_DISPINTERFACE_DEFINED__ */


#ifndef __IMixerControl2_INTERFACE_DEFINED__
#define __IMixerControl2_INTERFACE_DEFINED__

/* interface IMixerControl2 */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IMixerControl2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7d122821-73c7-4eac-a54f-ea34ed49551a")
    IMixerControl2 : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_volume( 
            /* [retval][out] */ unsigned long *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_volume( 
            /* [in] */ unsigned long newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_balance( 
            /* [retval][out] */ unsigned long *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_balance( 
            /* [in] */ unsigned long newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_mute( 
            /* [retval][out] */ BOOL *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_mute( 
            /* [in] */ BOOL newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_mux_source( 
            /* [retval][out] */ IMixerLine **pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_mux_source( 
            /* [in] */ IMixerLine *newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_mux_type( 
            /* [retval][out] */ MIX_LINE *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_mux_type( 
            /* [in] */ MIX_LINE newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_fade( 
            /* [retval][out] */ unsigned long *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_fade( 
            /* [in] */ unsigned long newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMixerControl2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMixerControl2 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMixerControl2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMixerControl2 * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_volume )( 
            IMixerControl2 * This,
            /* [retval][out] */ unsigned long *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_volume )( 
            IMixerControl2 * This,
            /* [in] */ unsigned long newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_balance )( 
            IMixerControl2 * This,
            /* [retval][out] */ unsigned long *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_balance )( 
            IMixerControl2 * This,
            /* [in] */ unsigned long newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_mute )( 
            IMixerControl2 * This,
            /* [retval][out] */ BOOL *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_mute )( 
            IMixerControl2 * This,
            /* [in] */ BOOL newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_mux_source )( 
            IMixerControl2 * This,
            /* [retval][out] */ IMixerLine **pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_mux_source )( 
            IMixerControl2 * This,
            /* [in] */ IMixerLine *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_mux_type )( 
            IMixerControl2 * This,
            /* [retval][out] */ MIX_LINE *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_mux_type )( 
            IMixerControl2 * This,
            /* [in] */ MIX_LINE newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_fade )( 
            IMixerControl2 * This,
            /* [retval][out] */ unsigned long *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_fade )( 
            IMixerControl2 * This,
            /* [in] */ unsigned long newVal);
        
        END_INTERFACE
    } IMixerControl2Vtbl;

    interface IMixerControl2
    {
        CONST_VTBL struct IMixerControl2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMixerControl2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMixerControl2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMixerControl2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMixerControl2_get_volume(This,pVal)	\
    (This)->lpVtbl -> get_volume(This,pVal)

#define IMixerControl2_put_volume(This,newVal)	\
    (This)->lpVtbl -> put_volume(This,newVal)

#define IMixerControl2_get_balance(This,pVal)	\
    (This)->lpVtbl -> get_balance(This,pVal)

#define IMixerControl2_put_balance(This,newVal)	\
    (This)->lpVtbl -> put_balance(This,newVal)

#define IMixerControl2_get_mute(This,pVal)	\
    (This)->lpVtbl -> get_mute(This,pVal)

#define IMixerControl2_put_mute(This,newVal)	\
    (This)->lpVtbl -> put_mute(This,newVal)

#define IMixerControl2_get_mux_source(This,pVal)	\
    (This)->lpVtbl -> get_mux_source(This,pVal)

#define IMixerControl2_put_mux_source(This,newVal)	\
    (This)->lpVtbl -> put_mux_source(This,newVal)

#define IMixerControl2_get_mux_type(This,pVal)	\
    (This)->lpVtbl -> get_mux_type(This,pVal)

#define IMixerControl2_put_mux_type(This,newVal)	\
    (This)->lpVtbl -> put_mux_type(This,newVal)

#define IMixerControl2_get_fade(This,pVal)	\
    (This)->lpVtbl -> get_fade(This,pVal)

#define IMixerControl2_put_fade(This,newVal)	\
    (This)->lpVtbl -> put_fade(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IMixerControl2_get_volume_Proxy( 
    IMixerControl2 * This,
    /* [retval][out] */ unsigned long *pVal);


void __RPC_STUB IMixerControl2_get_volume_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IMixerControl2_put_volume_Proxy( 
    IMixerControl2 * This,
    /* [in] */ unsigned long newVal);


void __RPC_STUB IMixerControl2_put_volume_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IMixerControl2_get_balance_Proxy( 
    IMixerControl2 * This,
    /* [retval][out] */ unsigned long *pVal);


void __RPC_STUB IMixerControl2_get_balance_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IMixerControl2_put_balance_Proxy( 
    IMixerControl2 * This,
    /* [in] */ unsigned long newVal);


void __RPC_STUB IMixerControl2_put_balance_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IMixerControl2_get_mute_Proxy( 
    IMixerControl2 * This,
    /* [retval][out] */ BOOL *pVal);


void __RPC_STUB IMixerControl2_get_mute_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IMixerControl2_put_mute_Proxy( 
    IMixerControl2 * This,
    /* [in] */ BOOL newVal);


void __RPC_STUB IMixerControl2_put_mute_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IMixerControl2_get_mux_source_Proxy( 
    IMixerControl2 * This,
    /* [retval][out] */ IMixerLine **pVal);


void __RPC_STUB IMixerControl2_get_mux_source_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IMixerControl2_put_mux_source_Proxy( 
    IMixerControl2 * This,
    /* [in] */ IMixerLine *newVal);


void __RPC_STUB IMixerControl2_put_mux_source_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IMixerControl2_get_mux_type_Proxy( 
    IMixerControl2 * This,
    /* [retval][out] */ MIX_LINE *pVal);


void __RPC_STUB IMixerControl2_get_mux_type_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IMixerControl2_put_mux_type_Proxy( 
    IMixerControl2 * This,
    /* [in] */ MIX_LINE newVal);


void __RPC_STUB IMixerControl2_put_mux_type_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IMixerControl2_get_fade_Proxy( 
    IMixerControl2 * This,
    /* [retval][out] */ unsigned long *pVal);


void __RPC_STUB IMixerControl2_get_fade_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IMixerControl2_put_fade_Proxy( 
    IMixerControl2 * This,
    /* [in] */ unsigned long newVal);


void __RPC_STUB IMixerControl2_put_fade_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMixerControl2_INTERFACE_DEFINED__ */


#ifndef __IMixerLine2_INTERFACE_DEFINED__
#define __IMixerLine2_INTERFACE_DEFINED__

/* interface IMixerLine2 */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IMixerLine2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7deeadce-2cec-4703-9ba6-2f469bcb7c98")
    IMixerLine2 : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_volume( 
            /* [retval][out] */ unsigned long *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_volume( 
            /* [in] */ unsigned long newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_balance( 
            /* [retval][out] */ unsigned long *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_balance( 
            /* [in] */ unsigned long newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_mute( 
            /* [retval][out] */ BOOL *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_mute( 
            /* [in] */ BOOL newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_mux_source( 
            /* [retval][out] */ IMixerLine **pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_mux_source( 
            /* [in] */ IMixerLine *newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_mux_type( 
            /* [retval][out] */ MIX_LINE *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_mux_type( 
            /* [in] */ MIX_LINE newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_fade( 
            /* [retval][out] */ unsigned long *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_fade( 
            /* [in] */ unsigned long newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMixerLine2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMixerLine2 * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMixerLine2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMixerLine2 * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_volume )( 
            IMixerLine2 * This,
            /* [retval][out] */ unsigned long *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_volume )( 
            IMixerLine2 * This,
            /* [in] */ unsigned long newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_balance )( 
            IMixerLine2 * This,
            /* [retval][out] */ unsigned long *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_balance )( 
            IMixerLine2 * This,
            /* [in] */ unsigned long newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_mute )( 
            IMixerLine2 * This,
            /* [retval][out] */ BOOL *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_mute )( 
            IMixerLine2 * This,
            /* [in] */ BOOL newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_mux_source )( 
            IMixerLine2 * This,
            /* [retval][out] */ IMixerLine **pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_mux_source )( 
            IMixerLine2 * This,
            /* [in] */ IMixerLine *newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_mux_type )( 
            IMixerLine2 * This,
            /* [retval][out] */ MIX_LINE *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_mux_type )( 
            IMixerLine2 * This,
            /* [in] */ MIX_LINE newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_fade )( 
            IMixerLine2 * This,
            /* [retval][out] */ unsigned long *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_fade )( 
            IMixerLine2 * This,
            /* [in] */ unsigned long newVal);
        
        END_INTERFACE
    } IMixerLine2Vtbl;

    interface IMixerLine2
    {
        CONST_VTBL struct IMixerLine2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMixerLine2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMixerLine2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMixerLine2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMixerLine2_get_volume(This,pVal)	\
    (This)->lpVtbl -> get_volume(This,pVal)

#define IMixerLine2_put_volume(This,newVal)	\
    (This)->lpVtbl -> put_volume(This,newVal)

#define IMixerLine2_get_balance(This,pVal)	\
    (This)->lpVtbl -> get_balance(This,pVal)

#define IMixerLine2_put_balance(This,newVal)	\
    (This)->lpVtbl -> put_balance(This,newVal)

#define IMixerLine2_get_mute(This,pVal)	\
    (This)->lpVtbl -> get_mute(This,pVal)

#define IMixerLine2_put_mute(This,newVal)	\
    (This)->lpVtbl -> put_mute(This,newVal)

#define IMixerLine2_get_mux_source(This,pVal)	\
    (This)->lpVtbl -> get_mux_source(This,pVal)

#define IMixerLine2_put_mux_source(This,newVal)	\
    (This)->lpVtbl -> put_mux_source(This,newVal)

#define IMixerLine2_get_mux_type(This,pVal)	\
    (This)->lpVtbl -> get_mux_type(This,pVal)

#define IMixerLine2_put_mux_type(This,newVal)	\
    (This)->lpVtbl -> put_mux_type(This,newVal)

#define IMixerLine2_get_fade(This,pVal)	\
    (This)->lpVtbl -> get_fade(This,pVal)

#define IMixerLine2_put_fade(This,newVal)	\
    (This)->lpVtbl -> put_fade(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IMixerLine2_get_volume_Proxy( 
    IMixerLine2 * This,
    /* [retval][out] */ unsigned long *pVal);


void __RPC_STUB IMixerLine2_get_volume_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IMixerLine2_put_volume_Proxy( 
    IMixerLine2 * This,
    /* [in] */ unsigned long newVal);


void __RPC_STUB IMixerLine2_put_volume_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IMixerLine2_get_balance_Proxy( 
    IMixerLine2 * This,
    /* [retval][out] */ unsigned long *pVal);


void __RPC_STUB IMixerLine2_get_balance_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IMixerLine2_put_balance_Proxy( 
    IMixerLine2 * This,
    /* [in] */ unsigned long newVal);


void __RPC_STUB IMixerLine2_put_balance_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IMixerLine2_get_mute_Proxy( 
    IMixerLine2 * This,
    /* [retval][out] */ BOOL *pVal);


void __RPC_STUB IMixerLine2_get_mute_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IMixerLine2_put_mute_Proxy( 
    IMixerLine2 * This,
    /* [in] */ BOOL newVal);


void __RPC_STUB IMixerLine2_put_mute_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IMixerLine2_get_mux_source_Proxy( 
    IMixerLine2 * This,
    /* [retval][out] */ IMixerLine **pVal);


void __RPC_STUB IMixerLine2_get_mux_source_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IMixerLine2_put_mux_source_Proxy( 
    IMixerLine2 * This,
    /* [in] */ IMixerLine *newVal);


void __RPC_STUB IMixerLine2_put_mux_source_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IMixerLine2_get_mux_type_Proxy( 
    IMixerLine2 * This,
    /* [retval][out] */ MIX_LINE *pVal);


void __RPC_STUB IMixerLine2_get_mux_type_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IMixerLine2_put_mux_type_Proxy( 
    IMixerLine2 * This,
    /* [in] */ MIX_LINE newVal);


void __RPC_STUB IMixerLine2_put_mux_type_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IMixerLine2_get_fade_Proxy( 
    IMixerLine2 * This,
    /* [retval][out] */ unsigned long *pVal);


void __RPC_STUB IMixerLine2_get_fade_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IMixerLine2_put_fade_Proxy( 
    IMixerLine2 * This,
    /* [in] */ unsigned long newVal);


void __RPC_STUB IMixerLine2_put_fade_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMixerLine2_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_MixerLibrary;

#ifdef __cplusplus

class DECLSPEC_UUID("CD871F9D-4BCD-49B7-B3AD-977C93982AF1")
MixerLibrary;
#endif
#endif /* __MIXERLIBLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


