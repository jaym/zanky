#include <stdio.h>
#include <ruby.h>

VALUE m_zanky = Qnil;

void 
Init_zanky() {
    m_zanky = rb_define_module("Zanky");
}
