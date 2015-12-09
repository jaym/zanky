/*
 * Shamelessy stolen from from the php peoples:
 * https://github.com/php/php-src/blob/250938e2d35fc54161a18167b7901c5e3b574371/ext/com_dotnet/com_dotnet.c
 *
 * It seems System._AppDomain does not support IDispatch
 * even though it implements all the functions required.
 */
typedef struct _Imscorlib_System_AppDomain IAppDomain;
typedef struct IAssembly IAssembly;

struct _Imscorlib_System_AppDomainVtbl {
    BEGIN_INTERFACE

    HRESULT ( STDMETHODCALLTYPE *QueryInterface )(
            IAppDomain * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);

    ULONG ( STDMETHODCALLTYPE *AddRef )(
            IAppDomain * This);

    ULONG ( STDMETHODCALLTYPE *Release )(
            IAppDomain * This);

    /* this is padding to get CreateInstance into the correct position */
#define DUMMY_METHOD(x)		HRESULT ( STDMETHODCALLTYPE *dummy_##x )(IAppDomain *This)

    DUMMY_METHOD(GetTypeInfoCount);
    DUMMY_METHOD(GetTypeInfo);
    DUMMY_METHOD(GetIDsOfNames);
    DUMMY_METHOD(Invoke);
    DUMMY_METHOD(ToString);
    DUMMY_METHOD(Equals);
    DUMMY_METHOD(GetHashCode);
    DUMMY_METHOD(GetType);
    DUMMY_METHOD(InitializeLifetimeService);
    DUMMY_METHOD(GetLifetimeService);
    DUMMY_METHOD(Evidence);
    DUMMY_METHOD(add_DomainUnload);
    DUMMY_METHOD(remove_DomainUnload);
    DUMMY_METHOD(add_AssemblyLoad);
    DUMMY_METHOD(remove_AssemblyLoad);
    DUMMY_METHOD(add_ProcessExit);
    DUMMY_METHOD(remove_ProcessExit);
    DUMMY_METHOD(add_TypeResolve);
    DUMMY_METHOD(remove_TypeResolve);
    DUMMY_METHOD(add_ResourceResolve);
    DUMMY_METHOD(remove_ResourceResolve);
    DUMMY_METHOD(add_AssemblyResolve);
    DUMMY_METHOD(remove_AssemblyResolve);
    DUMMY_METHOD(add_UnhandledException);
    DUMMY_METHOD(remove_UnhandledException);
    DUMMY_METHOD(DefineDynamicAssembly);
    DUMMY_METHOD(DefineDynamicAssembly_2);
    DUMMY_METHOD(DefineDynamicAssembly_3);
    DUMMY_METHOD(DefineDynamicAssembly_4);
    DUMMY_METHOD(DefineDynamicAssembly_5);
    DUMMY_METHOD(DefineDynamicAssembly_6);
    DUMMY_METHOD(DefineDynamicAssembly_7);
    DUMMY_METHOD(DefineDynamicAssembly_8);
    DUMMY_METHOD(DefineDynamicAssembly_9);

    HRESULT ( STDMETHODCALLTYPE *CreateInstance )(IAppDomain * This, BSTR AssemblyName, BSTR typeName, IUnknown **pRetVal);
    HRESULT ( STDMETHODCALLTYPE *CreateInstanceFrom )(IAppDomain * This, BSTR AssemblyFile, BSTR typeName, IUnknown **pRetVal);

    DUMMY_METHOD(CreateInstance_2);
    DUMMY_METHOD(CreateInstanceFrom_2);
    DUMMY_METHOD(CreateInstance_3);
    DUMMY_METHOD(CreateInstanceFrom_3);

    DUMMY_METHOD(Load);
    HRESULT ( STDMETHODCALLTYPE *Load_2)(IAppDomain * This, BSTR AssemblyString, IAssembly** pRetVal);
    DUMMY_METHOD(Load_3);
    DUMMY_METHOD(Load_4);
    DUMMY_METHOD(Load_5);
    DUMMY_METHOD(Load_6);
    DUMMY_METHOD(Load_7);
    DUMMY_METHOD(ExecuteAssembly);
    DUMMY_METHOD(ExecuteAssembly_2);
    DUMMY_METHOD(ExecuteAssembly_3);
    HRESULT ( STDMETHODCALLTYPE *FriendlyName)(IAppDomain * This, BSTR* pRetVal);
    HRESULT ( STDMETHODCALLTYPE *BaseDirectory)(IAppDomain * This, BSTR* pRetVal);
    HRESULT ( STDMETHODCALLTYPE *RelativeSearchPath)(IAppDomain * This, BSTR* pRetVal);
    /* more methods live here */

    END_INTERFACE
};

struct _Imscorlib_System_AppDomain {
    struct _Imscorlib_System_AppDomainVtbl *lpVtbl;
};

#define IAppDomain_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


