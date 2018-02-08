require 'gdb'

pid = ARGV.first
library = "#{__dir__}/library.so"
gdb = GDB::GDB.new "-p #{pid}"

gdb.execute "set $dlopen = (void*(*)(char*, int)) dlopen"
gdb.execute "call $dlopen(\"#{library}\", 1)"
