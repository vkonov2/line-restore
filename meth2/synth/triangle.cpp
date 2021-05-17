#include <iostream>
#include <string>
#include <cmath>

#include "functions.h"
#include "point.h"
using namespace std;

int triangle (Point * points, Point * points1, Point * points2, Point * points3, int n)
{
	int i, j, k;
	double l1_x, l1_y, l2_x, l2_y, l3_x, l3_y;
	double val, znam;
	double a1, b1, c1, a2, b2, c2, a3, b3, c3;
	double aa, bb, ab, ac, bc;

	double sqrt2 = 1.414213562373;
    
    l1_x = 0;
    l1_y = 1;

    l2_x = 1;
    l2_y = 0;

    l3_x = -1/sqrt2;
    l3_y = l3_x;

	for (i = 0; i < n; i++)
	{
		znam = sqrt (l1_x*l1_x + l1_y*l1_y);
		a1 = l1_y / znam;
		b1 = - l1_x / znam;
		c1 = - (a1 * points1[i].x + b1 * points1[i].y);

		// printf("1: %lf %lf %lf\n", a1, b1, c1);

		znam = sqrt (l2_x*l2_x + l2_y*l2_y);
		a2 = l2_y / znam;
		b2 = - l2_x / znam;
		c2 = - (a2 * points2[i].x + b2 * points2[i].y);

		// printf("2: %lf %lf %lf\n", a2, b2, c2);

		znam = sqrt (l3_x*l3_x + l3_y*l3_y);
		a3 = l3_y / znam;
		b3 = - l3_x / znam;
		c3 = - (a3 * points3[i].x + b3 * points3[i].y);

		// printf("3: %lf %lf %lf\n", a3, b3, c3);	

		aa = a1*a1 + a2*a2 + a3*a3;
		bb = b1*b1 + b2*b2 + b3*b3;
		ab = a1*b1 + a2*b2 + a3*b3;
		ac = a1*c1 + a2*c2 + a3*c3;
		bc = b1*c1 + b2*c2 + b3*c3;

		points[i].x = (bb * ac - ab * bc) / (ab * ab - aa * bb);
		points[i].y = (aa * bc - ab * ac) / (ab * ab - aa * bb);
		points[i].z = points1[i].z;
	}

	// for (i = 0; i < n; i++)
	// 	printf("(%lf, %lf, %lf)\n", points[i].x, points[i].y, points[i].z);

	FILE* f;
	f = fopen ("midpoints.txt", "w");
	if (!f)
	{
		printf(">>>cant open file --> midpoints.txt\n");
		return -1;
	}

	for (i = 0; i < n; i++)
		fprintf(f, "%lf %lf %lf\n", points[i].x, points[i].y, points[i].z);

	fclose (f);

	// splot '../meth2/synth/points1.txt', '../meth2/synth/points2.txt', '../meth2/synth/points3.txt', '../meth2/synth/midpoints.txt'

	line_solve (points, n, 0);

	return 1;
}