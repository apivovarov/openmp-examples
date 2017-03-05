#include <stdio.h>
#include <omp.h>

static void usage() {
  printf("Usage: fib n\n");
  printf("Max n is 100\n");
}

int fib(int n) {
  if (n < 2) return n;
  int a,b;
  #pragma omp task shared(a)
  a = fib(n - 1);
  #pragma omp task shared(b)
  b = fib(n - 2);
  #pragma omp taskwait
  return a + b;
}

int main(int argc, char* argv[]) {

  if (argc != 2) {
    usage();
    return -1;
  }

  int n = 0;
  int ret = 0;

  ret = sscanf(argv[1], "%d", &n);
  if (ret != 1 || n > 100) {
    usage();
    return -1;
  }

  printf("n=%d\n", n);

  int res;

  #pragma omp parallel shared(res)
  {
    #pragma omp single
    res = fib(n);
  }

  printf("fib=%d\n", res);
}
