require 'gdb'

pid = ARGV[0]
library = File.expand_path (ARGV[1] || "#{__dir__}/library.so")

gdb = GDB::GDB.new "-p #{pid} -q"
gdb.execute "set $dlopen = (void*(*)(char*, int)) dlopen"
gdb.execute "call $dlopen(\"#{library}\", 1)"
