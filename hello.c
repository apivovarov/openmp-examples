#include <stdio.h>
#include <omp.h>

int main()
{
  omp_set_num_threads(6);
  int thNum = omp_get_num_threads();
  printf("thNum=%d\n", thNum);

  #pragma omp parallel
  {

    int thNum = omp_get_num_threads();
    printf("thNum=%d\n", thNum);

    int ID = omp_get_thread_num();

    printf("hello(%d) ", ID);
    printf(" world(%d) \n", ID);
  }
}
