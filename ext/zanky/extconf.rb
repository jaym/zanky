require 'mkmf'

def crash(str)
  puts "extconf failure: #{str}"
  exit 1
end

def create_zanky_makefile
  if have_library("ole32") and
     have_library("oleaut32") and
     have_library("uuid", "&CLSID_CMultiLanguage", "mlang.h") and
     have_library("user32") and
     have_library("kernel32") and
     have_library("advapi32") and
     have_header("windows.h") and
     have_func("rb_sym2str", "ruby.h") and
     have_func("rb_check_symbol", "ruby.h")

    unless have_type("IMultiLanguage2", "mlang.h")
      have_type("IMultiLanguage", "mlang.h")
    end
    spec = nil
    checking_for('thread_specific', '%s') do
      spec = %w[__declspec(thread) __thread].find {|th|
        try_compile("#{th} int foo;", "", :werror => true)
      }
      spec or 'no'
    end
    $defs << "-DRB_THREAD_SPECIFIC=#{spec}" if spec
    create_makefile("zanky")
  end
end


case RUBY_PLATFORM
when /mswin/
  $CFLAGS.sub!(/((?:\A|\s)[-\/])W\d(?=\z|\s)/, '\1W3') or
    $CFLAGS += ' -W3'
end
create_zanky_makefile
