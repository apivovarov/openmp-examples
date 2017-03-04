#include <stdio.h>
#include <omp.h>

static void usage() {
  printf("Usage: pi <num_steps> <num_threads>\n");
  printf("Min num_steps is 100,000. Max num_threads is 1,000\n");
}

int main(int argc, char* argv[]) {
  
  long long num_steps = 0;
  int thNum = 0;
  int ret = 0;

  ret = sscanf(argv[1], "%lld", &num_steps);
  if (ret != 1 || num_steps < 100000) {
    usage();
    return -1;
  }
 
  ret = sscanf(argv[2], "%d", &thNum);
  if (ret != 1 || thNum < 1 || thNum > 1000) {
    usage();
    return -1;
  }

  printf("num_steps=%lld\n", num_steps);

  omp_set_num_threads(thNum);
  printf("thNum=%d\n", thNum);

  long double ss[thNum];

  long long stPerTh = num_steps / thNum;
  // printf("stPerTh=%lld\n",stPerTh);

  long double step = 1.0 / (long double) num_steps;
  // printf("step=%0.50Lf\n",step);

  #pragma omp parallel
  {
    int ID = omp_get_thread_num();
    long double sum2 = 0.0;
    long double x = 0.0;

    long long i1 = ID * stPerTh;
    long long i2 = i1 + stPerTh;
    if (ID + 1 == thNum) {
      i2 = num_steps;
    }

    // printf("ID=%d,i1=%lld,i2=%lld\n",ID,i1,i2);
    long long i;
    for (i = i1; i < i2; i++) {
      x = (i + 0.5)*step;
      sum2 += 4.0/(1 + x*x);
    }

    ss[ID] = sum2;
  }

  long double sum = 0.0;
  int i;
  for (i=0;i<thNum;i++) {
    sum += ss[i];
  }

  long double pi = step * sum;
  printf("pi=%0.50Lf\n",pi);
}
