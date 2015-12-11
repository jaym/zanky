#include <stdio.h>
#include <ruby.h>
#include <windows.h>
#include "win32ole.h"
#include "clrcom/metahost.h"
#include "clrcom/mscoree.h"
#include "clrcom/mscorlib.h"

#define IUnknown_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IUnknown_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


static const GUID CLSID_CorRuntimeHost = {0xcb2f6723,0xab3a,0x11d2,{0x9c,0x40,0x00,0xc0,0x4f,0xa3,0x0a,0x3e}};
static const GUID IID_ICorRuntimeHost = {0xcb2f6722,0xab3a,0x11d2,{0x9c,0x40,0x00,0xc0,0x4f,0xa3,0x0a,0x3e}};
static const GUID CLSID_CLRMetaHost =  {0x9280188d,0x0e8e,0x4867,{0xb3,0x0c,0x7f,0xa8,0x38,0x84,0xe8,0xde}};
static const GUID IID_ICLRMetaHost =  {0xD332DB9E, 0xB9B3, 0x4125, {0x82, 0x07, 0xA1, 0x48, 0x84, 0xF5, 0x32, 0x16}};
static const GUID IID_ICLRRuntimeInfo = {0xBD39D1D2, 0xBA2F, 0x486a, {0x89, 0xB0, 0xB4, 0xB0, 0xCB, 0x46, 0x68, 0x91}};
const GUID IID_IAppDomain = {0x05F696DC, 0x2B29, 0x3663, {0xAD, 0x8B, 0xC4, 0x38, 0x9C, 0xF2, 0xA7, 0x13 }};


typedef HRESULT (*clr_create_instance_t)(const GUID*, const GUID*, void**);

clr_create_instance_t CLRCreateInstance;


VALUE m_zanky = Qnil;
VALUE c_clr_meta_host = Qnil;
VALUE c_cor_runtime_host = Qnil;
VALUE c_app_domain = Qnil;

static void clr_meta_host_free(ICLRMetaHost*);
static void cor_runtime_host_free(ICorRuntimeHost*);
static void app_domain_free(IAppDomain*);

static const rb_data_type_t clr_meta_host_datatype = {
    "clr_meta_host",
    {NULL, clr_meta_host_free, NULL,},
    0, 0, RUBY_TYPED_FREE_IMMEDIATELY
};

static const rb_data_type_t cor_runtime_host_datatype = {
    "cor_runtime_host",
    {NULL, cor_runtime_host_free, NULL,},
    0, 0, RUBY_TYPED_FREE_IMMEDIATELY
};

static const rb_data_type_t app_domain_datatype = {
    "app_domain_datatype",
    {NULL, app_domain_free, NULL,},
    0, 0, RUBY_TYPED_FREE_IMMEDIATELY
};

static void
init_mscoree_functions() {
    HMODULE mscoree_handle;

    if(mscoree_handle = LoadLibrary("mscoree.dll")) {
        CLRCreateInstance = (clr_create_instance_t)GetProcAddress(mscoree_handle, "CLRCreateInstance");

        if(!CLRCreateInstance) {
            rb_fatal("Failed to load CLRCreateInstance from mscoree.dll");
        }
    } else {
        rb_fatal("Failed to load mscoree.dll");
    }
}

static ICLRMetaHost*
init_clr_meta_host() {
    HRESULT hresult;
    ICLRMetaHost* clr_meta_host = NULL;

    hresult = CLRCreateInstance(&CLSID_CLRMetaHost, &IID_ICLRMetaHost, (void**)&clr_meta_host);

    if(hresult) {
        rb_fatal("Could not create CLRMetaHost. Failed with 0x%x", (unsigned int)hresult);
    }

    return clr_meta_host;
}

static VALUE
clr_meta_host_initialize() {
    ICLRMetaHost* clr_meta_host;

    clr_meta_host = init_clr_meta_host();
    return TypedData_Wrap_Struct(c_clr_meta_host, &clr_meta_host_datatype, (void*)clr_meta_host);
}

static void
clr_meta_host_free(ICLRMetaHost* clr_meta_host) {
    ICLRMetaHost_Release(clr_meta_host);
}

static VALUE
clr_meta_host_get_runtime(VALUE self, VALUE str) {
    HRESULT hresult;
    ICLRMetaHost* clr_meta_host;
    ICLRRuntimeInfo* clrinfo;
    ICorRuntimeHost* runtime_host;
    LPWSTR version;

    TypedData_Get_Struct(self, ICLRMetaHost, &clr_meta_host_datatype, clr_meta_host);

    version = ole_vstr2wc(str);
    clrinfo = NULL;
    hresult = ICLRMetaHost_GetRuntime(clr_meta_host, version, &IID_ICLRRuntimeInfo, (void**)&clrinfo);

    SysFreeString(version);

    if(hresult) {
        rb_fatal("Could not instantiate runtime. Failed with 0x%x", (unsigned int)hresult);
    }

    runtime_host = NULL;
    ICLRRuntimeInfo_GetInterface(clrinfo, &CLSID_CorRuntimeHost, &IID_ICorRuntimeHost, (void**)&runtime_host);
    ICLRRuntimeInfo_Release(clrinfo);

    return TypedData_Wrap_Struct(c_cor_runtime_host, &cor_runtime_host_datatype, (void*)runtime_host);
}

static VALUE
cor_runtime_host_start(VALUE self) {
    ICorRuntimeHost* runtime_host;
    HRESULT hresult;

    TypedData_Get_Struct(self, ICorRuntimeHost, &cor_runtime_host_datatype, runtime_host);

    hresult = ICorRuntimeHost_Start(runtime_host);

    if(hresult) {
        rb_fatal("Could not start runtime. Failed with 0x%x", (unsigned int)hresult);
    }

    return self;
}

static VALUE
cor_runtime_host_stop(VALUE self) {
    ICorRuntimeHost* runtime_host;
    HRESULT hresult;

    TypedData_Get_Struct(self, ICorRuntimeHost, &cor_runtime_host_datatype, runtime_host);

    hresult = ICorRuntimeHost_Stop(runtime_host);

    if(hresult) {
        rb_fatal("Could not stop runtime. Failed with 0x%x", (unsigned int)hresult);
    }

    return Qnil;
}

static VALUE
cor_runtime_host_get_default_app_domain(VALUE self) {
    ICorRuntimeHost* runtime_host;
    IUnknown* unk;
    IAppDomain* app_domain;
    HRESULT hresult;

    TypedData_Get_Struct(self, ICorRuntimeHost, &cor_runtime_host_datatype, runtime_host);

    hresult = ICorRuntimeHost_GetDefaultDomain(runtime_host, &unk);

    if(hresult) {
        rb_fatal("Could not get default app domain. Failed with 0x%x", (unsigned int)hresult);
    }

    app_domain = NULL;
    IUnknown_QueryInterface(unk, &IID_IAppDomain, (void**)&app_domain);
    IUnknown_Release(unk);

    return TypedData_Wrap_Struct(c_app_domain, &app_domain_datatype, (void*)app_domain);
}

static void
cor_runtime_host_free(ICorRuntimeHost* cor_runtime_host) {
    ICorRuntimeHost_Release(cor_runtime_host);
}

static
BSTR to_bstr(char* str) {
    DWORD len;
    BSTR  strptr;

    len = MultiByteToWideChar(CP_ACP, 0, str, -1, 0, 0);
    strptr = SysAllocStringLen(0, len);
    MultiByteToWideChar(CP_ACP, 0, str, -1, strptr, len);

    return strptr;
}

static VALUE
app_domain_create_instance(VALUE self, VALUE assembly_name, VALUE type_name) {
    IAppDomain* app_domain;
    IUnknown* inst;
    BSTR bstr_assembly_name;
    BSTR bstr_type_name;
    VARIANT v_inst;
    VALUE ret_val;
    HRESULT hresult;

    TypedData_Get_Struct(self, IAppDomain, &app_domain_datatype, app_domain);
    
    bstr_assembly_name = to_bstr(StringValueCStr(assembly_name));
    bstr_type_name = to_bstr(StringValueCStr(type_name));

    VariantInit(&v_inst);
    
    hresult = IAppDomain_CreateInstance(app_domain, bstr_assembly_name, bstr_type_name, &inst);
    if(hresult) {
        // Leaks memory
        rb_fatal("Could not create instance of %s in %s: Get 0x%x", StringValueCStr(type_name), 
                StringValueCStr(assembly_name), (unsigned int)hresult);
    }

    V_VT(&v_inst) = VT_UNKNOWN;
    V_UNKNOWN(&v_inst) = inst;

    ret_val = ole_variant2val(&v_inst);

    IUnknown_Release(inst);
    SysFreeString(bstr_assembly_name);
    SysFreeString(bstr_type_name);

    return ret_val;
}

static VALUE
app_domain_load(VALUE self, VALUE assembly_string) {
    IAppDomain* app_domain;
    IAssembly* assembly;
    BSTR bstr_assembly_string;
    HRESULT hresult;

    TypedData_Get_Struct(self, IAppDomain, &app_domain_datatype, app_domain);
    
    bstr_assembly_string = to_bstr(StringValueCStr(assembly_string));

    hresult = IAppDomain_Load_2(app_domain, bstr_assembly_string, &assembly);
    if(hresult) {
        // Leaks memory
        rb_fatal("Could not load assembly %s : Got 0x%x", StringValueCStr(assembly_string), 
                  (unsigned int)hresult);
    }
    IUnknown_Release((IUnknown*)assembly);

    return Qnil;
}

static void
app_domain_free(IAppDomain* app_domain) {
    IAppDomain_Release(app_domain);
}

static void
create_clr_meta_host_class() {
    c_clr_meta_host = rb_define_class_under(m_zanky, "CLRMetaHost", rb_cData);
    rb_define_singleton_method(c_clr_meta_host, "create", clr_meta_host_initialize, 0);
    rb_define_method(c_clr_meta_host, "GetRuntime", clr_meta_host_get_runtime, 1);
}

static void
create_cor_runtime_host_class() {
    c_cor_runtime_host = rb_define_class_under(m_zanky, "CorRuntimeInfo", rb_cData);
    rb_define_method(c_cor_runtime_host, "Start", cor_runtime_host_start, 0);
    rb_define_method(c_cor_runtime_host, "Stop", cor_runtime_host_stop, 0);
    rb_define_method(c_cor_runtime_host, "GetDefaultAppDomain", cor_runtime_host_get_default_app_domain, 0);
}

static void
create_app_domain_class() {
    c_app_domain = rb_define_class_under(m_zanky, "AppDomain", rb_cData);
    rb_define_method(c_app_domain, "create_instance", app_domain_create_instance, 2);
    rb_define_method(c_app_domain, "load_assembly", app_domain_load, 1);
}

void 
Init_zanky() {
    Init_win32ole();
    ole_initialize();
    m_zanky = rb_define_module("Zanky");
    init_mscoree_functions();
    create_clr_meta_host_class();
    create_cor_runtime_host_class();
    create_app_domain_class();
}
