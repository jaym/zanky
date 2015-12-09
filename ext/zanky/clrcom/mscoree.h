#include <windows.h>
#include <ole2.h>
#include <rpcndr.h>

typedef struct ICorRuntimeHost ICorRuntimeHost;
typedef struct ICorConfiguration ICorConfiguration;
typedef void* HDOMAINENUM;

typedef struct ICorRuntimeHostVtbl
{
    BEGIN_INTERFACE

    HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICorRuntimeHost * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            void **ppvObject);

    ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICorRuntimeHost * This);

    ULONG ( STDMETHODCALLTYPE *Release )( 
            ICorRuntimeHost * This);

    HRESULT ( STDMETHODCALLTYPE *CreateLogicalThreadState )( 
            ICorRuntimeHost * This);

    HRESULT ( STDMETHODCALLTYPE *DeleteLogicalThreadState )( 
            ICorRuntimeHost * This);

    HRESULT ( STDMETHODCALLTYPE *SwitchInLogicalThreadState )( 
            ICorRuntimeHost * This,
            /* [in] */ DWORD *pFiberCookie);

    HRESULT ( STDMETHODCALLTYPE *SwitchOutLogicalThreadState )( 
            ICorRuntimeHost * This,
            /* [out] */ DWORD **pFiberCookie);

    HRESULT ( STDMETHODCALLTYPE *LocksHeldByLogicalThread )( 
            ICorRuntimeHost * This,
            /* [out] */ DWORD *pCount);

    HRESULT ( STDMETHODCALLTYPE *MapFile )( 
            ICorRuntimeHost * This,
            /* [in] */ HANDLE hFile,
            /* [out] */ HMODULE *hMapAddress);

    HRESULT ( STDMETHODCALLTYPE *GetConfiguration )( 
            ICorRuntimeHost * This,
            /* [out] */ ICorConfiguration **pConfiguration);

    HRESULT ( STDMETHODCALLTYPE *Start )( 
            ICorRuntimeHost * This);

    HRESULT ( STDMETHODCALLTYPE *Stop )( 
            ICorRuntimeHost * This);

    HRESULT ( STDMETHODCALLTYPE *CreateDomain )( 
            ICorRuntimeHost * This,
            /* [in] */ LPCWSTR pwzFriendlyName,
            /* [in] */ IUnknown *pIdentityArray,
            /* [out] */ IUnknown **pAppDomain);

    HRESULT ( STDMETHODCALLTYPE *GetDefaultDomain )( 
            ICorRuntimeHost * This,
            /* [out] */ IUnknown **pAppDomain);

    HRESULT ( STDMETHODCALLTYPE *EnumDomains )( 
            ICorRuntimeHost * This,
            /* [out] */ HDOMAINENUM *hEnum);

    HRESULT ( STDMETHODCALLTYPE *NextDomain )( 
            ICorRuntimeHost * This,
            /* [in] */ HDOMAINENUM hEnum,
            /* [out] */ IUnknown **pAppDomain);

    HRESULT ( STDMETHODCALLTYPE *CloseEnum )( 
            ICorRuntimeHost * This,
            /* [in] */ HDOMAINENUM hEnum);

    HRESULT ( STDMETHODCALLTYPE *CreateDomainEx )( 
            ICorRuntimeHost * This,
            /* [in] */ LPCWSTR pwzFriendlyName,
            /* [in] */ IUnknown *pSetup,
            /* [in] */ IUnknown *pEvidence,
            /* [out] */ IUnknown **pAppDomain);

    HRESULT ( STDMETHODCALLTYPE *CreateDomainSetup )( 
            ICorRuntimeHost * This,
            /* [out] */ IUnknown **pAppDomainSetup);

    HRESULT ( STDMETHODCALLTYPE *CreateEvidence )( 
            ICorRuntimeHost * This,
            /* [out] */ IUnknown **pEvidence);

    HRESULT ( STDMETHODCALLTYPE *UnloadDomain )( 
            ICorRuntimeHost * This,
            /* [in] */ IUnknown *pAppDomain);

    HRESULT ( STDMETHODCALLTYPE *CurrentDomain )( 
            ICorRuntimeHost * This,
            /* [out] */ IUnknown **pAppDomain);

    END_INTERFACE
} ICorRuntimeHostVtbl;

struct ICorRuntimeHost
{
    const struct ICorRuntimeHostVtbl *lpVtbl;
};

#define ICorRuntimeHost_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ICorRuntimeHost_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ICorRuntimeHost_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ICorRuntimeHost_CreateLogicalThreadState(This)	\
    ( (This)->lpVtbl -> CreateLogicalThreadState(This) ) 

#define ICorRuntimeHost_DeleteLogicalThreadState(This)	\
    ( (This)->lpVtbl -> DeleteLogicalThreadState(This) ) 

#define ICorRuntimeHost_SwitchInLogicalThreadState(This,pFiberCookie)	\
    ( (This)->lpVtbl -> SwitchInLogicalThreadState(This,pFiberCookie) ) 

#define ICorRuntimeHost_SwitchOutLogicalThreadState(This,pFiberCookie)	\
    ( (This)->lpVtbl -> SwitchOutLogicalThreadState(This,pFiberCookie) ) 

#define ICorRuntimeHost_LocksHeldByLogicalThread(This,pCount)	\
    ( (This)->lpVtbl -> LocksHeldByLogicalThread(This,pCount) ) 

#define ICorRuntimeHost_MapFile(This,hFile,hMapAddress)	\
    ( (This)->lpVtbl -> MapFile(This,hFile,hMapAddress) ) 

#define ICorRuntimeHost_GetConfiguration(This,pConfiguration)	\
    ( (This)->lpVtbl -> GetConfiguration(This,pConfiguration) ) 

#define ICorRuntimeHost_Start(This)	\
    ( (This)->lpVtbl -> Start(This) ) 

#define ICorRuntimeHost_Stop(This)	\
    ( (This)->lpVtbl -> Stop(This) ) 

#define ICorRuntimeHost_CreateDomain(This,pwzFriendlyName,pIdentityArray,pAppDomain)	\
    ( (This)->lpVtbl -> CreateDomain(This,pwzFriendlyName,pIdentityArray,pAppDomain) ) 

#define ICorRuntimeHost_GetDefaultDomain(This,pAppDomain)	\
    ( (This)->lpVtbl -> GetDefaultDomain(This,pAppDomain) ) 

#define ICorRuntimeHost_EnumDomains(This,hEnum)	\
    ( (This)->lpVtbl -> EnumDomains(This,hEnum) ) 

#define ICorRuntimeHost_NextDomain(This,hEnum,pAppDomain)	\
    ( (This)->lpVtbl -> NextDomain(This,hEnum,pAppDomain) ) 

#define ICorRuntimeHost_CloseEnum(This,hEnum)	\
    ( (This)->lpVtbl -> CloseEnum(This,hEnum) ) 

#define ICorRuntimeHost_CreateDomainEx(This,pwzFriendlyName,pSetup,pEvidence,pAppDomain)	\
    ( (This)->lpVtbl -> CreateDomainEx(This,pwzFriendlyName,pSetup,pEvidence,pAppDomain) ) 

#define ICorRuntimeHost_CreateDomainSetup(This,pAppDomainSetup)	\
    ( (This)->lpVtbl -> CreateDomainSetup(This,pAppDomainSetup) ) 

#define ICorRuntimeHost_CreateEvidence(This,pEvidence)	\
    ( (This)->lpVtbl -> CreateEvidence(This,pEvidence) ) 

#define ICorRuntimeHost_UnloadDomain(This,pAppDomain)	\
    ( (This)->lpVtbl -> UnloadDomain(This,pAppDomain) ) 

#define ICorRuntimeHost_CurrentDomain(This,pAppDomain)	\
    ( (This)->lpVtbl -> CurrentDomain(This,pAppDomain) ) 
