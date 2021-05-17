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
	
	for (i = 0; i < num; i++)
	{
		aa = 0;
		bb = 0;
		ab = 0;
		ac = 0;
		bc = 0;
		for (j = 0; j < count; j++)
		{
			a[j] = vecs[j].x;
			b[j] = vecs[j].y;
			val = vecs[j].x * points[j][i].y - vecs[j].y * points[j][i].x;
			if (val < 0)
			{
				val = -val;
				a[j] = -a[j];
				b[j] = -b[j];
			}
			c[j] = val;

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

		//printf("%lf %lf %lf\n", mid_points[i].x, mid_points[i].y, mid_points[i].z);
	}

	int numm;
	int flagg = 0;
	for (i = 10000; i < num; i++)
    {
        if ((isnan (mid_points[i].x) != 0)||(isnan (mid_points[i].y) != 0))
        {
            numm = i;
            flagg = 1;
            break;
        }
        if (flagg == 1)
            break;
    }

	// for (i = 0; i < numm; i++)
	// 	printf("%lf %lf %lf\n", mid_points[i].x, mid_points[i].y, mid_points[i].z);

	delete [] a;
	delete [] b;
	delete [] c;

	line_solve (mid_points, numm, flag);

	return 1;
}