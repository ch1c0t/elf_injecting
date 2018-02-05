#include <stdio.h>

void __attribute__((constructor)) startup();
void __attribute__((destructor)) shutdown();

void
startup() {
  puts("library loaded");
}

void
shutdown() {
  puts("library unloaded");
}
