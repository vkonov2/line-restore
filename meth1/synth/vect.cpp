#include <iostream>
#include <string>
#include <cmath>

#include "functions.h"
using namespace std;

int vect (double *eigen_val, double *A, double *coefs, Point* points, int n)
{
	int i;
	double val;
	double coefs1[3], coefs2[3], coefs3[3];
	double L1 = 0, L2 = 0, L3 = 0;

	double a_xy = 0.0, a_xz = 0.0, a_yz = 0.0, b_xy = 0.0, b_xz = 0.0, b_yz = 0.0;

	a_yz = A[0];
    b_xy = -A[1];
    b_xz = -A[2];
    a_xz = A[4];
    b_yz = -A[5];
    a_xy = A[8];

    coefs1[2] = 1.0;
    coefs2[2] = 1.0;
    coefs3[2] = 1.0;

    coefs1[1] = (  (  (b_xy * b_xz) / (a_yz - eigen_val[0])  )  +  b_yz ) / (  (  -(b_xy * b_xy) / (a_yz - eigen_val[0])  )  +  a_xz  -  eigen_val[0]  );
    coefs2[1] = (  (  (b_xy * b_xz) / (a_yz - eigen_val[1])  )  +  b_yz ) / (  (  -(b_xy * b_xy) / (a_yz - eigen_val[1])  )  +  a_xz  -  eigen_val[1]  );
    coefs3[1] = (  (  (b_xy * b_xz) / (a_yz - eigen_val[2])  )  +  b_yz ) / (  (  -(b_xy * b_xy) / (a_yz - eigen_val[2])  )  +  a_xz  -  eigen_val[2]  );

    coefs1[0] = (b_xy * coefs1[1] + b_xz) / (a_yz - eigen_val[0]);
    coefs2[0] = (b_xy * coefs2[1] + b_xz) / (a_yz - eigen_val[1]);
    coefs3[0] = (b_xy * coefs3[1] + b_xz) / (a_yz - eigen_val[2]);

    L1 = a_xz * coefs1[1] * coefs1[1] + a_yz * coefs1[0] * coefs1[0] + a_xy - 2 * b_yz * coefs1[1] - 2 * b_xz * coefs1[0] - 2 * b_xy * coefs1[0] * coefs1[1];

    L2 = a_xz * coefs2[1] * coefs2[1] + a_yz * coefs2[0] * coefs2[0] + a_xy - 2 * b_yz * coefs2[1] - 2 * b_xz * coefs2[0] - 2 * b_xy * coefs2[0] * coefs2[1];

    L3 = a_xz * coefs3[1] * coefs3[1] + a_yz * coefs3[0] * coefs3[0] + a_xy - 2 * b_yz * coefs3[1] - 2 * b_xz * coefs3[0] - 2 * b_xy * coefs3[0] * coefs3[1];

	if ((L1 > L2)&&(L2 > L3))
	{
		coefs[0] = coefs3[0];
		coefs[1] = coefs3[1];
		coefs[2] = coefs3[2];
	}
	else if ((L1 > L2)&&(L2 < L3))
	{
		coefs[0] = coefs2[0];
		coefs[1] = coefs2[1];
		coefs[2] = coefs2[2];
	}
	else if ((L1 < L2)&&(L2 > L3))
	{
		if (L1 > L3)
		{
			coefs[0] = coefs3[0];
			coefs[1] = coefs3[1];
			coefs[2] = coefs3[2];
		}
		else
		{
			coefs[0] = coefs1[0];
			coefs[1] = coefs1[1];
			coefs[2] = coefs1[2];
		}
	}
	else if ((L1 < L2)&&(L2 < L3))
	{
		coefs[0] = coefs1[0];
		coefs[1] = coefs1[1];
		coefs[2] = coefs1[2];
	}
	else if ((L1 > L3)&&(L3 > L2))
	{
		coefs[0] = coefs2[0];
		coefs[1] = coefs2[1];
		coefs[2] = coefs2[2];
	}
	else if ((L1 > L3)&&(L3 < L2))
	{
		coefs[0] = coefs3[0];
		coefs[1] = coefs3[1];
		coefs[2] = coefs3[2];
	}
	else if ((L1 < L3)&&(L3 > L2))
	{
		if (L1 > L2)
		{
			coefs[0] = coefs2[0];
			coefs[1] = coefs2[1];
			coefs[2] = coefs2[2];
		}
		else
		{
			coefs[0] = coefs1[0];
			coefs[1] = coefs1[1];
			coefs[2] = coefs1[2];
		}
	}
	else if ((L1 < L3)&&(L3 < L2))
	{
		coefs[0] = coefs1[0];
		coefs[1] = coefs1[1];
		coefs[2] = coefs1[2];
	}
	else if ((L2 > L3)&&(L3 > L1))
	{
		coefs[0] = coefs1[0];
		coefs[1] = coefs1[1];
		coefs[2] = coefs1[2];
	}
	else if ((L2 > L3)&&(L3 < L1))
	{
		coefs[0] = coefs3[0];
		coefs[1] = coefs3[1];
		coefs[2] = coefs3[2];
	}
	else if ((L2 < L3)&&(L3 > L1))
	{
		if (L2 > L1)
		{
			coefs[0] = coefs1[0];
			coefs[1] = coefs1[1];
			coefs[2] = coefs1[2];
		}
		else
		{
			coefs[0] = coefs2[0];
			coefs[1] = coefs2[1];
			coefs[2] = coefs2[2];
		}
	}
	else if ((L2 < L3)&&(L3 < L1))
	{
		coefs[0] = coefs2[0];
		coefs[1] = coefs2[1];
		coefs[2] = coefs2[2];
	}

	return 1;
}
