#include <iostream>
#include <string>
#include <cmath>

#include "functions.h"
#include "point.h"
using namespace std;

int eigen (int n, int m, double eps, double *A)
{
   	int i, j;
   	double val = A[1];
   	int cur_i = 0, cur_j = 1;

      //print (A, n, n, m);

   	yakobi (A, n, cur_i, cur_j);

      val = A[2];
      cur_i = 0;
      cur_j = 2;

      yakobi (A, n, cur_i, cur_j);

      val = A[5];
      cur_i = 1;
      cur_j = 2;

      yakobi (A, n, cur_i, cur_j);

      //print (A, n, n, m);

   	// printf("\n");
   	// for (i = 0; i < m; i++)
   	// 	printf("eigen_val[%d] = %10.3e\n", i, A[i*n+i]);

    return 1;
}
