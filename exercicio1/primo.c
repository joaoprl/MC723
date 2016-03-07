#include <stdio.h>
#include <omp.h>

int primo(int n)
{
  int i;

  if(n == 2)
    return 1;
  if(n % 2 == 0 || n == 1)
    return 0;
  for(i = 3; i < n; i += 2)
    if (n % i == 0)
      return 0;

  return 1; 
}

int main(int argc, char **argv) {
  if(argc != 2) return 1; 
  int n = atoi(argv[1]), primos = 0, i;

  #pragma omp parallel for reduction(+ : primos)
    for(i = 0; i <= n; i++)
      primos += primo(i); // true is 1, false is 0
  printf("%d\n", primos);

  return 0;
}
