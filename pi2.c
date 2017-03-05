#include <stdio.h>
#include <omp.h>

static void usage() {
  printf("Usage: pi <num_steps>\n");
  printf("Min num_steps is 100,000.\n");
}

int main(int argc, char* argv[]) {

  if (argc != 2) {
    usage();
    return -1;
  }
  
  long long num_steps = 0;
  int thNum = 0;
  int ret = 0;

  ret = sscanf(argv[1], "%lld", &num_steps);
  if (ret != 1 || num_steps < 100000) {
    usage();
    return -1;
  }
 
  printf("num_steps=%lld\n", num_steps);

  long double step = 1.0 / (long double) num_steps;
  // printf("step=%0.50Lf\n",step);

  int i;
  long double sum = 0.0;
  #pragma omp parallel
  {
    long double x = 0.0;

    #pragma omp for reduction(+:sum)
    for (i = 0; i < num_steps; i++) {
      x = (i + 0.5) * step;
      sum += 4.0/(1 + x * x);
    }
  }

  long double pi = step * sum;
  printf("pi=%0.50Lf\n",pi);
}
