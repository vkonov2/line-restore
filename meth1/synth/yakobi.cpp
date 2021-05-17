#include <iostream>
#include <string>
#include <cmath>

#include "functions.h"
using namespace std;

int yakobi (double *A, int n, int i, int j)
{
	const double cos_pi4 = 0.7071067811865475;
	int min, max, k, sgn;
	double val00, val01, val10, val11;
	double val_ik, val_jk, val_ki, val_kj;
	double tg, c2, s, c;

	min = (i > j ? j : i);
	max = (i > j ? i : j);
	val00 = A[min*n+min];
	val01 = A[min*n+max];
	val10 = A[max*n+min];
	val11 = A[max*n+max];

	if (fabs(val00 - val11) < 1e-16)
	{
		c = cos_pi4;
		s = c;
	}
	else
	{
		tg = 2 * val01 / (val00 - val11);
		sgn = tg / fabs(tg);

		c2 = 1 / sqrt (1 + tg * tg);

		c = sqrt ((1 + c2) / 2);

		s = sgn * sqrt ((1 - c2) / 2);
	}

	for (k = 0; k < n; k++)
	{
		val_ki = A[k*n+min];
		val_kj = A[k*n+max];

		A[k*n+min] = val_ki * c + val_kj * s;
		A[k*n+max] = -val_ki * s + val_kj * c;
	}

	for (k = 0; k < n; k++)
	{
		val_ik = A[min*n+k];
		val_jk = A[max*n+k];

		A[min*n+k] = val_ik * c + val_jk * s;
		A[max*n+k] = -val_ik * s + val_jk * c;
	}

	return 1;
}
