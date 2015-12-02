#include <windows.h>
#include <ole2.h>
#include <rpcndr.h>

typedef struct ICLRMetaHost ICLRMetaHost;
typedef struct ICLRRuntimeInfo ICLRRuntimeInfo;

typedef HRESULT ( __stdcall *CallbackThreadSetFnPtr )( void);
typedef HRESULT ( __stdcall *CallbackThreadUnsetFnPtr )( void);
typedef void ( __stdcall *RuntimeLoadedCallbackFnPtr )( 
        ICLRRuntimeInfo *pRuntimeInfo,
        CallbackThreadSetFnPtr pfnCallbackThreadSet,
        CallbackThreadUnsetFnPtr pfnCallbackThreadUnset);

typedef struct ICLRMetaHostVtbl
{
    BEGIN_INTERFACE

        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
                ICLRMetaHost * This,
                /* [in] */ REFIID riid,
                /* [annotation][iid_is][out] */ 
                void **ppvObject);

    ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICLRMetaHost * This);

    ULONG ( STDMETHODCALLTYPE *Release )( 
            ICLRMetaHost * This);

    HRESULT ( STDMETHODCALLTYPE *GetRuntime )( 
            ICLRMetaHost * This,
            /* [in] */ LPCWSTR pwzVersion,
            /* [in] */ REFIID riid,
            /* [retval][iid_is][out] */ LPVOID *ppRuntime);

    HRESULT ( STDMETHODCALLTYPE *GetVersionFromFile )( 
            ICLRMetaHost * This,
            /* [in] */ LPCWSTR pwzFilePath,
            /* [annotation][size_is][out] */ 
            LPWSTR pwzBuffer,
            /* [out][in] */ DWORD *pcchBuffer);

    HRESULT ( STDMETHODCALLTYPE *EnumerateInstalledRuntimes )( 
            ICLRMetaHost * This,
            /* [retval][out] */ IEnumUnknown **ppEnumerator);

    HRESULT ( STDMETHODCALLTYPE *EnumerateLoadedRuntimes )( 
            ICLRMetaHost * This,
            /* [in] */ HANDLE hndProcess,
            /* [retval][out] */ IEnumUnknown **ppEnumerator);

    HRESULT ( STDMETHODCALLTYPE *RequestRuntimeLoadedNotification )( 
            ICLRMetaHost * This,
            /* [in] */ RuntimeLoadedCallbackFnPtr pCallbackFunction);

    HRESULT ( STDMETHODCALLTYPE *QueryLegacyV2RuntimeBinding )( 
            ICLRMetaHost * This,
            /* [in] */ REFIID riid,
            /* [retval][iid_is][out] */ LPVOID *ppUnk);

    HRESULT ( STDMETHODCALLTYPE *ExitProcess )( 
            ICLRMetaHost * This,
            /* [in] */ INT32 iExitCode);

    END_INTERFACE
} ICLRMetaHostVtbl;

struct ICLRMetaHost
{
    const struct ICLRMetaHostVtbl *lpVtbl;
};

#define ICLRMetaHost_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ICLRMetaHost_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ICLRMetaHost_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ICLRMetaHost_GetRuntime(This,pwzVersion,riid,ppRuntime)	\
    ( (This)->lpVtbl -> GetRuntime(This,pwzVersion,riid,ppRuntime) ) 

#define ICLRMetaHost_GetVersionFromFile(This,pwzFilePath,pwzBuffer,pcchBuffer)	\
    ( (This)->lpVtbl -> GetVersionFromFile(This,pwzFilePath,pwzBuffer,pcchBuffer) ) 

#define ICLRMetaHost_EnumerateInstalledRuntimes(This,ppEnumerator)	\
    ( (This)->lpVtbl -> EnumerateInstalledRuntimes(This,ppEnumerator) ) 

#define ICLRMetaHost_EnumerateLoadedRuntimes(This,hndProcess,ppEnumerator)	\
    ( (This)->lpVtbl -> EnumerateLoadedRuntimes(This,hndProcess,ppEnumerator) ) 

#define ICLRMetaHost_RequestRuntimeLoadedNotification(This,pCallbackFunction)	\
    ( (This)->lpVtbl -> RequestRuntimeLoadedNotification(This,pCallbackFunction) ) 

#define ICLRMetaHost_QueryLegacyV2RuntimeBinding(This,riid,ppUnk)	\
    ( (This)->lpVtbl -> QueryLegacyV2RuntimeBinding(This,riid,ppUnk) ) 

#define ICLRMetaHost_ExitProcess(This,iExitCode)	\
    ( (This)->lpVtbl -> ExitProcess(This,iExitCode) ) 


typedef struct ICLRRuntimeInfoVtbl
{
    BEGIN_INTERFACE

        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
                ICLRRuntimeInfo * This,
                /* [in] */ REFIID riid,
                /* [annotation][iid_is][out] */ 
                void **ppvObject);

    ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICLRRuntimeInfo * This);

    ULONG ( STDMETHODCALLTYPE *Release )( 
            ICLRRuntimeInfo * This);

    HRESULT ( STDMETHODCALLTYPE *GetVersionString )( 
            ICLRRuntimeInfo * This,
            /* [annotation][size_is][out] */ 
            LPWSTR pwzBuffer,
            /* [out][in] */ DWORD *pcchBuffer);

    HRESULT ( STDMETHODCALLTYPE *GetRuntimeDirectory )( 
            ICLRRuntimeInfo * This,
            /* [annotation][size_is][out] */ 
            LPWSTR pwzBuffer,
            /* [out][in] */ DWORD *pcchBuffer);

    HRESULT ( STDMETHODCALLTYPE *IsLoaded )( 
            ICLRRuntimeInfo * This,
            /* [in] */ HANDLE hndProcess,
            /* [retval][out] */ BOOL *pbLoaded);

    HRESULT ( STDMETHODCALLTYPE *LoadErrorString )( 
            ICLRRuntimeInfo * This,
            /* [in] */ UINT iResourceID,
            /* [annotation][size_is][out] */ 
            LPWSTR pwzBuffer,
            /* [out][in] */ DWORD *pcchBuffer,
            /* [lcid][in] */ LONG iLocaleID);

    HRESULT ( STDMETHODCALLTYPE *LoadLibrary )( 
            ICLRRuntimeInfo * This,
            /* [in] */ LPCWSTR pwzDllName,
            /* [retval][out] */ HMODULE *phndModule);

    HRESULT ( STDMETHODCALLTYPE *GetProcAddress )( 
            ICLRRuntimeInfo * This,
            /* [in] */ LPCSTR pszProcName,
            /* [retval][out] */ LPVOID *ppProc);

    HRESULT ( STDMETHODCALLTYPE *GetInterface )( 
            ICLRRuntimeInfo * This,
            /* [in] */ REFCLSID rclsid,
            /* [in] */ REFIID riid,
            /* [retval][iid_is][out] */ LPVOID *ppUnk);

    HRESULT ( STDMETHODCALLTYPE *IsLoadable )( 
            ICLRRuntimeInfo * This,
            /* [retval][out] */ BOOL *pbLoadable);

    HRESULT ( STDMETHODCALLTYPE *SetDefaultStartupFlags )( 
            ICLRRuntimeInfo * This,
            /* [in] */ DWORD dwStartupFlags,
            /* [in] */ LPCWSTR pwzHostConfigFile);

    HRESULT ( STDMETHODCALLTYPE *GetDefaultStartupFlags )( 
            ICLRRuntimeInfo * This,
            /* [out] */ DWORD *pdwStartupFlags,
            /* [annotation][size_is][out] */ 
            LPWSTR pwzHostConfigFile,
            /* [out][in] */ DWORD *pcchHostConfigFile);

    HRESULT ( STDMETHODCALLTYPE *BindAsLegacyV2Runtime )( 
            ICLRRuntimeInfo * This);

    HRESULT ( STDMETHODCALLTYPE *IsStarted )( 
            ICLRRuntimeInfo * This,
            /* [out] */ BOOL *pbStarted,
            /* [out] */ DWORD *pdwStartupFlags);

    END_INTERFACE
} ICLRRuntimeInfoVtbl;

struct ICLRRuntimeInfo
{
    const struct ICLRRuntimeInfoVtbl *lpVtbl;
};

#define ICLRRuntimeInfo_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ICLRRuntimeInfo_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ICLRRuntimeInfo_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ICLRRuntimeInfo_GetVersionString(This,pwzBuffer,pcchBuffer)	\
    ( (This)->lpVtbl -> GetVersionString(This,pwzBuffer,pcchBuffer) ) 

#define ICLRRuntimeInfo_GetRuntimeDirectory(This,pwzBuffer,pcchBuffer)	\
    ( (This)->lpVtbl -> GetRuntimeDirectory(This,pwzBuffer,pcchBuffer) ) 

#define ICLRRuntimeInfo_IsLoaded(This,hndProcess,pbLoaded)	\
    ( (This)->lpVtbl -> IsLoaded(This,hndProcess,pbLoaded) ) 

#define ICLRRuntimeInfo_LoadErrorString(This,iResourceID,pwzBuffer,pcchBuffer,iLocaleID)	\
    ( (This)->lpVtbl -> LoadErrorString(This,iResourceID,pwzBuffer,pcchBuffer,iLocaleID) ) 

#define ICLRRuntimeInfo_LoadLibrary(This,pwzDllName,phndModule)	\
    ( (This)->lpVtbl -> LoadLibrary(This,pwzDllName,phndModule) ) 

#define ICLRRuntimeInfo_GetProcAddress(This,pszProcName,ppProc)	\
    ( (This)->lpVtbl -> GetProcAddress(This,pszProcName,ppProc) ) 

#define ICLRRuntimeInfo_GetInterface(This,rclsid,riid,ppUnk)	\
    ( (This)->lpVtbl -> GetInterface(This,rclsid,riid,ppUnk) ) 

#define ICLRRuntimeInfo_IsLoadable(This,pbLoadable)	\
    ( (This)->lpVtbl -> IsLoadable(This,pbLoadable) ) 

#define ICLRRuntimeInfo_SetDefaultStartupFlags(This,dwStartupFlags,pwzHostConfigFile)	\
    ( (This)->lpVtbl -> SetDefaultStartupFlags(This,dwStartupFlags,pwzHostConfigFile) ) 

#define ICLRRuntimeInfo_GetDefaultStartupFlags(This,pdwStartupFlags,pwzHostConfigFile,pcchHostConfigFile)	\
    ( (This)->lpVtbl -> GetDefaultStartupFlags(This,pdwStartupFlags,pwzHostConfigFile,pcchHostConfigFile) ) 

#define ICLRRuntimeInfo_BindAsLegacyV2Runtime(This)	\
    ( (This)->lpVtbl -> BindAsLegacyV2Runtime(This) ) 

#define ICLRRuntimeInfo_IsStarted(This,pbStarted,pdwStartupFlags)	\
    ( (This)->lpVtbl -> IsStarted(This,pbStarted,pdwStartupFlags) ) 


