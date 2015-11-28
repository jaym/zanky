require 'mkmf'

extension_name = 'zanky'

def crash(str)
  puts "extconf failure: #{str}"
  exit 1
end

create_makefile(extension_name)
