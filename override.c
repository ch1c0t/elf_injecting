#define _GNU_SOURCE
#include <dlfcn.h>
#include <unistd.h>
#include <stdio.h>

typedef int (*LibcStartMainFnType)(int (*main)(int, char **, char **), int argc, char **argv,
                                   int (*init)(void), void (*fini)(void),
                                   void (*ldso_fini)(void), void (*stack_end));

int __libc_start_main(int (*main)(int, char **, char **), int argc, char **argv,
                      int (*init)(void), void (*fini)(void),
                      void (*ldso_fini)(void), void (*stack_end)) {
  LibcStartMainFnType original = (LibcStartMainFnType)dlsym(RTLD_NEXT, "__libc_start_main");
  puts("before original");
  int result = original(main, argc, argv, init, fini, ldso_fini, stack_end);
  // puts("after original"); / doesn't work; why?
  return result;
}

// gcc -Wall -fPIC -DPIC -c override.c
// ld -shared -o override.so override.o -ldl
// LD_PRELOAD=./override.so cat override.c
