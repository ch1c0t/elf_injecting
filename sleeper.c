#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void*
fun(void* vargp) {
  for(;;) {
    sleep(1);
    puts("fun from new thread");
  }
}

int
main() {
  pthread_t tid;

  pthread_create(&tid, NULL, fun, NULL);

  puts("Something");
  sleep(30);
}

// gcc sleeper.c -lpthread
// ./a.out
