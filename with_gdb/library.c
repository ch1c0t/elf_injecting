#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void __attribute__((constructor)) startup();
void __attribute__((destructor)) shutdown();
void* perform_work(void* arg);

void
startup() {
  puts("library loaded");

  pthread_t tid;
  pthread_create(&tid, NULL, perform_work, NULL);
}

void
shutdown() {
  puts("library unloaded");
}

void*
perform_work(void* arg) {
  for(;;) {
    puts("from preloaded");
    sleep(2);
  }
}
