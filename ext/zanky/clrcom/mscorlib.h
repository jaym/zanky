/*
 * Shamelessy stolen from from the php peoples:
 * https://github.com/php/php-src/blob/250938e2d35fc54161a18167b7901c5e3b574371/ext/com_dotnet/com_dotnet.c
 *
 * It seems System._AppDomain does not support IDispatch
 * even though it implements all the functions required.
 */
typedef struct _Imscorlib_System_AppDomain IAppDomain;
typedef struct IAssembly IAssembly;

typedef struct _Imscorlib_System_Type IType;

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

#define IAppDomain_CreateInstance(This,AssemblyName,TypeName,pRetVal)	\
    ( (This)->lpVtbl -> CreateInstance(This,AssemblyName,TypeName,pRetVal) ) 

#define IAppDomain_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 

#define IAppDomain_Load_2(This, AssemblyString, pRetVal) \
    ( (This)->lpVtbl -> Load_2(This,AssemblyString,pRetVal) ) 

struct _Imscorlib_System_TypeVtbl {
    BEGIN_INTERFACE

    HRESULT ( STDMETHODCALLTYPE *QueryInterface )(
            IAppDomain * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);

    ULONG ( STDMETHODCALLTYPE *AddRef )(
            IAppDomain * This);

    ULONG ( STDMETHODCALLTYPE *Release )(
            IAppDomain * This);

#undef  DUMMY_METHOD
#define DUMMY_METHOD(x)		HRESULT ( STDMETHODCALLTYPE *dummy_##x )(IType *This)

    DUMMY_METHOD(GetTypeInfoCount);
    DUMMY_METHOD(GetTypeInfo);
    DUMMY_METHOD(GetIDsOfNames);
    DUMMY_METHOD(Invoke);
    DUMMY_METHOD(ToString);
    DUMMY_METHOD(Equals);
    DUMMY_METHOD(GetHashCode);
    DUMMY_METHOD(GetType);
    DUMMY_METHOD(MemberType);
    DUMMY_METHOD(name);
    DUMMY_METHOD(DeclaringType);
    DUMMY_METHOD(ReflectedType);
    DUMMY_METHOD(GetCustomAttributes);
    DUMMY_METHOD(GetCustomAttributes_2);
    DUMMY_METHOD(IsDefined);
    DUMMY_METHOD(Guid);
    DUMMY_METHOD(Module);
    DUMMY_METHOD(Assembly);
    DUMMY_METHOD(TypeHandle);
    DUMMY_METHOD(FullName);
    DUMMY_METHOD(Namespace);
    DUMMY_METHOD(AssemblyQualifiedName);
    DUMMY_METHOD(GetArrayRank);
    DUMMY_METHOD(BaseType);
    DUMMY_METHOD(GetConstructors);
    DUMMY_METHOD(GetInterface);
    DUMMY_METHOD(GetInterfaces);
    DUMMY_METHOD(FindInterfaces);
    DUMMY_METHOD(GetEvent);
    DUMMY_METHOD(GetEvents);
    DUMMY_METHOD(GetEvents_2);
    DUMMY_METHOD(GetNestedTypes);
    DUMMY_METHOD(GetNestedType);
    DUMMY_METHOD(GetMember);
    DUMMY_METHOD(GetDefaultMembers);
    DUMMY_METHOD(FindMembers);
    DUMMY_METHOD(GetElementType);
    DUMMY_METHOD(IsSubclassOf);
    DUMMY_METHOD(IsInstanceOfType);
    DUMMY_METHOD(IsAssignableFrom);
    DUMMY_METHOD(GetInterfaceMap);
    DUMMY_METHOD(GetMethod);
    DUMMY_METHOD(GetMethod_2);
    DUMMY_METHOD(GetMethods);
    DUMMY_METHOD(GetField);
    DUMMY_METHOD(GetFields);
    DUMMY_METHOD(GetProperty);
    DUMMY_METHOD(GetProperty_2);
    DUMMY_METHOD(GetProperties);
    DUMMY_METHOD(GetMember_2);
    DUMMY_METHOD(GetMembers);
    DUMMY_METHOD(InvokeMember);
    DUMMY_METHOD(UnderlyingSystemType);
    DUMMY_METHOD(InvokeMember_2);
    DUMMY_METHOD(InvokeMember_3);
    DUMMY_METHOD(GetConstructor);
    DUMMY_METHOD(GetConstructor_2);
    DUMMY_METHOD(GetConstructor_3);
    DUMMY_METHOD(GetConstructors_2);
    DUMMY_METHOD(TypeInitializer);
    DUMMY_METHOD(GetMethod_3);
    DUMMY_METHOD(GetMethod_4);
    DUMMY_METHOD(GetMethod_5);
    DUMMY_METHOD(GetMethod_6);
    DUMMY_METHOD(GetMethods_2);
    DUMMY_METHOD(GetField_2);
    DUMMY_METHOD(GetFields_2);
    DUMMY_METHOD(GetInterface_2);
    DUMMY_METHOD(GetEvent_2);
    DUMMY_METHOD(GetProperty_3);
    DUMMY_METHOD(GetProperty_4);
    DUMMY_METHOD(GetProperty_5);
    DUMMY_METHOD(GetProperty_6);
    DUMMY_METHOD(GetProperty_7);
    DUMMY_METHOD(GetProperties_2);
    DUMMY_METHOD(GetNestedTypes_2);
    DUMMY_METHOD(GetNestedType_2);
    DUMMY_METHOD(GetMember_3);
    DUMMY_METHOD(GetMembers_2);
    DUMMY_METHOD(Attributes);
    DUMMY_METHOD(IsNotPublic);
    DUMMY_METHOD(IsPublic);
    DUMMY_METHOD(IsNestedPublic);
    DUMMY_METHOD(IsNestedPrivate);
    DUMMY_METHOD(IsNestedFamily);
    DUMMY_METHOD(IsNestedAssembly);
    DUMMY_METHOD(IsNestedFamAndAssem);
    DUMMY_METHOD(IsNestedFamOrAssem);
    DUMMY_METHOD(IsAutoLayout);
    DUMMY_METHOD(IsLayoutSequential);
    DUMMY_METHOD(IsExplicitLayout);
    DUMMY_METHOD(IsClass);
    DUMMY_METHOD(IsInterface);
    DUMMY_METHOD(IsValueType);
    DUMMY_METHOD(IsAbstract);
    DUMMY_METHOD(IsSealed);
    DUMMY_METHOD(IsEnum);
    DUMMY_METHOD(IsSpecialName);
    DUMMY_METHOD(IsImport);
    DUMMY_METHOD(IsSerializable);
    DUMMY_METHOD(IsAnsiClass);
    DUMMY_METHOD(IsUnicodeClass);
    DUMMY_METHOD(IsAutoClass);
    DUMMY_METHOD(IsArray);
    DUMMY_METHOD(IsByRef);
    DUMMY_METHOD(IsPointer);
    DUMMY_METHOD(IsPrimitive);
    DUMMY_METHOD(IsCOMObject);
    DUMMY_METHOD(HasElementType);
    DUMMY_METHOD(IsContextful);
    DUMMY_METHOD(IsMarshalByRef);
    
    END_INTERFACE
};

struct _Imscorlib_System_Type {
    struct _Imscorlib_System_TypeVtbl *lpVtbl;
};
