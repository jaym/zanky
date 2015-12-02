#include <stdio.h>
#include <ruby.h>
#include <windows.h>
#include "win32ole.h"
#include "clrcom/metahost.h"

VALUE m_zanky = Qnil;
VALUE c_clr_meta_host;

static void clr_meta_host_free();
static const rb_data_type_t clr_meta_host_datatype = {
    "clr_meta_host",
    {NULL, clr_meta_host_free, NULL,},
    0, 0, RUBY_TYPED_FREE_IMMEDIATELY
};

static const GUID CLSID_CorRuntimeHost = {0xcb2f6723,0xab3a,0x11d2,{0x9c,0x40,0x00,0xc0,0x4f,0xa3,0x0a,0x3e}};
static const GUID IID_ICorRuntimeHost = {0xcb2f6722,0xab3a,0x11d2,{0x9c,0x40,0x00,0xc0,0x4f,0xa3,0x0a,0x3e}};
static const GUID CLSID_CLRMetaHost =  {0x9280188d,0x0e8e,0x4867,{0xb3,0x0c,0x7f,0xa8,0x38,0x84,0xe8,0xde}};
static const GUID IID_ICLRMetaHost =  {0xD332DB9E, 0xB9B3, 0x4125, {0x82, 0x07, 0xA1, 0x48, 0x84, 0xF5, 0x32, 0x16}};

typedef HRESULT (*clr_create_instance_t)(const GUID*, const GUID*, void**);

clr_create_instance_t CLRCreateInstance;

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
clr_meta_host_free() {
}

static void
create_clr_meta_host_class() {
    c_clr_meta_host = rb_define_class_under(m_zanky, "CLRMetaHost", rb_cData);
    rb_define_singleton_method(c_clr_meta_host, "create", clr_meta_host_initialize, 0);
}

void 
Init_zanky() {
    Init_win32ole();
    ole_initialize();
    m_zanky = rb_define_module("Zanky");
    init_mscoree_functions();
    create_clr_meta_host_class();
}
