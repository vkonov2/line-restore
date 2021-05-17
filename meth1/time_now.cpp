#include <iostream>
#include <sys/time.h>

#include "functions.h"
using namespace std;

double time_now(void)
{
  struct timeval tv2;
  struct timezone tz;
  gettimeofday(&tv2, &tz);
  return tv2.tv_sec+tv2.tv_usec/1000000.0;
}
