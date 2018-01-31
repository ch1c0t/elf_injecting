#define _GNU_SOURCE
#include <dlfcn.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

void* perform_work(void*);

typedef int (*LibcStartMainFnType)(int (*main)(int, char **, char **), int argc, char **argv,
                                   int (*init)(void), void (*fini)(void),
                                   void (*ldso_fini)(void), void (*stack_end));

int __libc_start_main(int (*main)(int, char **, char **), int argc, char **argv,
                      int (*init)(void), void (*fini)(void),
                      void (*ldso_fini)(void), void (*stack_end)) {
  LibcStartMainFnType original = (LibcStartMainFnType)dlsym(RTLD_NEXT, "__libc_start_main");
  puts("before original");

  pthread_t tid;
  pthread_create(&tid, NULL, perform_work, NULL);

  int result = original(main, argc, argv, init, fini, ldso_fini, stack_end);
  // puts("after original"); / doesn't work; why?
  return result;
}

void*
perform_work(void* arg) {
  for(;;) {
    puts("from preloaded");
    sleep(2);
  }
}

// gcc -Wall -fPIC -DPIC -c override.c
// ld -shared -o override.so override.o -ldl -lpthread
// LD_PRELOAD=./override.so ruby sleeper.rb
