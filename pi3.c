#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <stdlib.h>

static void usage() {
  printf("Usage: pi3 <num_steps>\n");
  printf("Min num_steps is 100,000.\n");
}

int main(int argc, char* argv[]) {

  if (argc != 2) {
    usage();
    return -1;
  }
 
  long long num_steps = 0;
  int ret = 0;

  ret = sscanf(argv[1], "%lld", &num_steps);
  if (ret != 1 || num_steps < 100000) {
    usage();
    return -1;
  }

  num_steps *= 4L; 
  printf("num_steps=%lld\n", num_steps);

  long long sum = 0L;
  long long R = (long long) RAND_MAX * RAND_MAX;

 // long long i = 0L;
  //time_t t;
  //srand((unsigned) time(&t));
  // srand((unsigned int)(time(NULL)));

  printf("RAND_MAX=%d\n", RAND_MAX);
 
  #pragma omp parallel default(none) shared(R, num_steps, sum)
  {
    unsigned int rs = (unsigned int)(time(NULL) + omp_get_thread_num());
    
    printf("rs=%u\n", rs);
    rand_r(&rs);
    rs = rand_r(&rs);

    unsigned int rs2 = rand_r(&rs);
    printf("rnd0=%u\n",rs2);
    rand_r(&rs2);
    rs2 = rand_r(&rs2);
    rand_r(&rs2);
    
    #pragma omp for reduction(+:sum)
    for (long long  i = 0; i < num_steps; i++) {
      long double x = rand_r(&rs);
      long double y = rand_r(&rs2);
      long double d = x*x + y*y;
      if (d <= R) sum++;
    }
  }
  printf("sum=%lld\n", sum);

  long double pi = ((long double) sum) / (num_steps / 4L);
  printf("pi=%0.50Lf\n",pi);
}
