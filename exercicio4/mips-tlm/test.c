
#include <stdio.h>

#define ENDERECO_LOCK (100*1024*1024)

volatile int *lock = (int *) ENDERECO_LOCK;

int main(){
  int t;
  while ((t = *lock));
  printf("lock adquirido: %d\n", t >> 24);
  printf("lock realizado: %d\n", (*lock) >> 24);
  *lock = 0;
  printf("lock solto\n");

  return 0;
}
