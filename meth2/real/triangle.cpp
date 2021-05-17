#include <iostream>
#include <string>
#include <cmath>

#include "functions.h"
#include "point.h"
using namespace std;

int triangle (Point* mid_points, Point** points, Point* vecs, int num, const int count, int flag)
{
	int i, j, k;

	double val;
	double aa, bb, ab, ac, bc;

	double* a = new double[count];
    if (!a)
    {
        printf(">>>allocation error --> a\n");
        return -1;
    }

    for (i = 0; i < count; i++)
        a[i] = 0;

    double* b = new double[count];
    if (!b)
    {
        printf(">>>allocation error --> b\n");
        delete [] a;
        return -1;
    }

    for (i = 0; i < count; i++)
        b[i] = 0;

    double* c = new double[count];
    if (!c)
    {
        printf(">>>allocation error --> a\n");
        delete [] a;
        delete [] b;
        return -1;
    }

    for (i = 0; i < count; i++)
        c[i] = 0;

    //printf("num = %d\n", num);

    double znam;
	
	for (i = 0; i < num-1; i++)
	{
		aa = 0;
		bb = 0;
		ab = 0;
		ac = 0;
		bc = 0;
		for (j = 0; j < count; j++)
		{
			znam = sqrt (vecs[j].x*vecs[j].x + vecs[j].y*vecs[j].y + vecs[j].z*vecs[j].z);
			a[j] = vecs[j].y / znam;
			b[j] = - vecs[j].x / znam;
			c[j] = - (a[j] * points[j][i].x + b[j] * points[j][i].y);

			aa += a[j]*a[j];
			bb += b[j]*b[j];
			ab += a[j]*b[j];
			ac += a[j]*c[j];
			bc += b[j]*c[j];
		}

		// printf("level: %d\n", i);

		mid_points[i].x = (bb * ac - ab * bc) / (ab * ab - aa * bb);
		mid_points[i].y = (aa * bc - ab * ac) / (ab * ab - aa * bb);
		mid_points[i].z = points[0][i].z;

		// printf("%lf %lf %lf\n", mid_points[i].x, mid_points[i].y, mid_points[i].z);
	}

	// int numm;
	// int flagg = 0;
	// for (i = 10000; i < num; i++)
 //    {
 //        if ((isnan (mid_points[i].x) != 0)||(isnan (mid_points[i].y) != 0))
 //        {
 //            numm = i;
 //            flagg = 1;
 //            break;
 //        }
 //        if (flagg == 1)
 //            break;
 //    }

	// for (i = 0; i < numm; i++)
	// 	printf("%lf %lf %lf\n", mid_points[i].x, mid_points[i].y, mid_points[i].z);

	delete [] a;
	delete [] b;
	delete [] c;

	char str [100];

	if (flag == 0)
		strcpy (str, "line_p_data.txt");
	else if (flag == -2)
		strcpy (str, "line_m_data.txt");

	line_solve (mid_points, num-1, flag, str);

	return 1;
}