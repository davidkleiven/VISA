#include <omp.h>
#include <iostream>

using namespace std;
int main()
{
  int numThreads = omp_get_num_threads();
  clog << "Number of available threads\n";
  #pragma omp parallel
  {
    clog << "Thread " << omp_get_thread_num() << " says hello\n";
  }
  return 0;
}
