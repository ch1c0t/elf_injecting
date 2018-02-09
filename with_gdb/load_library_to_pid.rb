require 'gdb'

pid = ARGV[0]
library = ARGV[1] || "#{__dir__}/library.so"

gdb = GDB::GDB.new "-p #{pid}"
gdb.execute "set $dlopen = (void*(*)(char*, int)) dlopen"
gdb.execute "call $dlopen(\"#{library}\", 1)"