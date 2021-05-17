#include <iostream>
#include <string>
#include <cmath>

#include "functions.h"
#include "point.h"
using namespace std;

int check (Point * points1, Point * points2, Point * points3, int n, double z_min, double z_max)
{
	int i, j, k;
	double l1_x, l1_y, l1_d, l2_x, l2_y, l2_d, l3_x, l3_y, l3_d;
	double znam1, znam2, znam3;
	double a1, b1, c1, d1, a2, b2, c2, d2, a3, b3, c3, d3;
	double sqrt2 = 1.414213562373;
	double val, val1, val2, val3;
	int n1 = 10, n2 = 10, n3 = 10;
    FILE* f1;
    FILE* f2;
    FILE* f3;

	FILE* f = fopen("line_data.txt", "r");
    if (!f) 
    {
        printf (">>>can't open file -> line_data.txt\n");
        delete [] points1;
        delete [] points2;
        delete [] points3;
        return -2;
    }

    double p, q, r, x0, y0, z0;
    
    if (fscanf (f, "%lf", &p) != 1)
    {
        printf (">>>wrong data in file -> line_data.txt\n");
        delete [] points1;
        delete [] points2;
        delete [] points3;
        return -4;
    }
    if (fscanf (f, "%lf", &q) != 1)
    {
        printf (">>>wrong data in file -> line_data.txt\n");
        delete [] points1;
        delete [] points2;
        delete [] points3;
        return -4;
    }
    if (fscanf (f, "%lf", &r) != 1)
    {
        printf (">>>wrong data in file -> line_data.txt\n");
        delete [] points1;
        delete [] points2;
        delete [] points3;
        return -4;
    }
    if (fscanf (f, "%lf", &x0) != 1)
    {
        printf (">>>wrong data in file -> line_data.txt\n");
        delete [] points1;
        delete [] points2;
        delete [] points3;
        return -4;
    }
    if (fscanf (f, "%lf", &y0) != 1)
    {
        printf (">>>wrong data in file -> line_data.txt\n");
        delete [] points1;
        delete [] points2;
        delete [] points3;
        return -4;
    }
    if (fscanf (f, "%lf", &z0) != 1)
    {
        printf (">>>wrong data in file -> line_data.txt\n");
        delete [] points1;
        delete [] points2;
        delete [] points3;
        return -4;
    }

    fclose (f);

    l1_x = 0;
    l1_y = 1;
    l1_d = 4;

    l2_x = 1;
    l2_y = 0;
    l2_d = 4;

    l3_x = -1/sqrt2;
    l3_y = l3_x;
    l3_d = 6+2*sqrt2;

    // m >> p
    // n >> q
    // p >> r
    // r_1^1 >> l1_x
    // r_2^1 >> l1_y
    // r_3^1 >> 0
    // r_1^2 >> l2_x
    // r_2^2 >> l2_y
    // r_3^2 >> 0
    // r_1^3 >> l3_x
    // r_2^3 >> l3_y
    // r_3^3 >> 0

    znam1 = sqrt( (-r * l1_y)*(-r * l1_y) + (r * l1_x)*(r * l1_x) + (p * l1_y - q * l1_x)*(p * l1_y - q * l1_x) );

    znam2 = sqrt( (-r * l2_y)*(-r * l2_y) + (r * l2_x)*(r * l2_x) + (p * l2_y - q * l2_x)*(p * l2_y - q * l2_x) );

    znam3 = sqrt( (-r * l3_y)*(-r * l3_y) + (r * l3_x)*(r * l3_x) + (p * l3_y - q * l3_x)*(p * l3_y - q * l3_x) );

    a1 = (- r * l1_y) / znam1;
    b1 = (r * l1_x) / znam1;
    c1 = (p * l1_y - q * l1_x) / znam1;
    d1 = -( (- r * l1_y) * x0 + (r * l1_x) * y0 + (p * l1_y - q * l1_x) * z0 ) / znam1;

    a2 = (- r * l2_y) / znam2;
    b2 = (r * l2_x) / znam2;
    c2 = (p * l2_y - q * l2_x) / znam2;
    d2 = -( (- r * l2_y) * x0 + (r * l2_x) * y0 + (p * l2_y - q * l2_x) * z0 ) / znam2;

    a3 = (- r * l3_y) / znam3;
    b3 = (r * l3_x) / znam3;
    c3 = (p * l3_y - q * l3_x) / znam3;
    d3 = -( (- r * l3_y) * x0 + (r * l3_x) * y0 + (p * l3_y - q * l3_x) * z0 ) / znam3;

    // printf("\n %lf %lf %lf %lf\n", a1, b1, c1, d1);
    // printf("\n %lf %lf %lf %lf\n", a2, b2, c2, d2);
    // printf("\n %lf %lf %lf %lf\n", a3, b3, c3, d3);

    double x1_min, y1_min, x1_max, y1_max;
    double x2_min, y2_min, x2_max, y2_max;
    double x3_min, y3_min, x3_max, y3_max;

    x1_min = (l1_y * (c1 * z_min + d1) - b1 * l1_d) / (l1_x * b1 - a1 * l1_y);
    y1_min = (l1_x * (c1 * z_min + d1) - a1 * l1_d) / (a1 * l1_y - l1_x * b1);
    x1_max = (l1_y * (c1 * z_max + d1) - b1 * l1_d) / (l1_x * b1 - a1 * l1_y);
    y1_max = (l1_x * (c1 * z_max + d1) - a1 * l1_d) / (a1 * l1_y - l1_x * b1);

    x2_min = (l2_y * (c2 * z_min + d2) - b2 * l2_d) / (l2_x * b2 - a2 * l2_y);
    y2_min = (l2_x * (c2 * z_min + d2) - a2 * l2_d) / (a2 * l2_y - l2_x * b2);
    x2_max = (l2_y * (c2 * z_max + d2) - b2 * l2_d) / (l2_x * b2 - a2 * l2_y);
    y2_max = (l2_x * (c2 * z_max + d2) - a2 * l2_d) / (a2 * l2_y - l2_x * b2);

    x3_min = (l3_y * (c3 * z_min + d3) - b3 * l3_d) / (l3_x * b3 - a3 * l3_y);
    y3_min = (l3_x * (c3 * z_min + d3) - a3 * l3_d) / (a3 * l3_y - l3_x * b3);
    x3_max = (l3_y * (c3 * z_max + d3) - b3 * l3_d) / (l3_x * b3 - a3 * l3_y);
    y3_max = (l3_x * (c3 * z_max + d3) - a3 * l3_d) / (a3 * l3_y - l3_x * b3);

    f1 = fopen ("proecline1.txt", "w");
    if (!f1)
    {
        printf (">>>cant open file -> proecline1.txt\n");
        delete [] points1;
        delete [] points2;
        delete [] points3;
        return -4;
    }

    fprintf(f1, "%lf %lf %lf\n %lf %lf %lf\n", x1_min, y1_min, z_min, x1_max, y1_max, z_max);

    fclose (f1);

    f2 = fopen ("proecline2.txt", "w");
    if (!f2)
    {
        printf (">>>cant open file -> proecline2.txt\n");
        delete [] points1;
        delete [] points2;
        delete [] points3;
        return -4;
    }

    fprintf(f2, "%lf %lf %lf\n %lf %lf %lf\n", x2_min, y2_min, z_min, x2_max, y2_max, z_max);

    fclose (f2);

    f3 = fopen ("proecline3.txt", "w");
    if (!f3)
    {
        printf (">>>cant open file -> proecline3.txt\n");
        delete [] points1;
        delete [] points2;
        delete [] points3;
        return -4;
    }

    fprintf(f3, "%lf %lf %lf\n %lf %lf %lf\n", x3_min, y3_min, z_min, x3_max, y3_max, z_max);

    fclose (f3);

    for (i = 0; i < 1000; i++)
    {
    	points1[i].x = 0;
    	points1[i].y = 0;
    	points1[i].z = 0;
    	points2[i].x = 0;
    	points2[i].y = 0;
    	points2[i].z = 0;
    	points3[i].x = 0;
    	points3[i].y = 0;
    	points3[i].z = 0;
    }

    f1 = fopen("points1.txt", "r");

    if (!f1) 
    {
        printf (">>>can't open file -> points1.txt\n");
        delete [] points1;
        delete [] points2;
        delete [] points3;
        return -2;
    }

    f2 = fopen("points2.txt", "r");

    if (!f2) 
    {
        printf (">>>can't open file -> points2.txt\n");
        delete [] points1;
        delete [] points2;
        delete [] points3;
        return -2;
    }

    f3 = fopen("points3.txt", "r");

    if (!f3) 
    {
        printf (">>>can't open file -> points3.txt\n");
        delete [] points1;
        delete [] points2;
        delete [] points3;
        return -2;
    }

    for (i = 0; i < n1; i++)
    {
    	if (fscanf(f1, "%lf %lf %lf", &val1, &val2, &val3) != 3)
			return -4;
		else
		{
			points1[i].x = val1;
			points1[i].y = val2;
			points1[i].z = val3;
		}
    }
    for (i = 0; i < n2; i++)
    {
    	if (fscanf(f2, "%lf %lf %lf", &val1, &val2, &val3) != 3)
			return -4;
		else
		{
			points2[i].x = val1;
			points2[i].y = val2;
			points2[i].z = val3;
		}
    }
    for (i = 0; i < n3; i++)
    {
    	if (fscanf(f3, "%lf %lf %lf", &val1, &val2, &val3) != 3)
			return -4;
		else
		{
			points3[i].x = val1;
			points3[i].y = val2;
			points3[i].z = val3;
		}
    }

    fclose (f1);
    fclose (f2);
    fclose (f3);

    double sum = 0, sum1 = 0, sum2 = 0, sum3 = 0;
    for (i = 0; i < n1; i++)
    {
    	val = a1 * points1[i].x + b1 * points1[i].y + c1 * points1[i].z + d1;
    	sum1 += val * val;
    }
    for (i = 0; i < n2; i++)
    {
    	val = a2 * points2[i].x + b2 * points2[i].y + c2 * points2[i].z + d2;
    	sum2 += val * val;
    }
    for (i = 0; i < n3; i++)
    {
    	val = a3 * points3[i].x + b3 * points3[i].y + c3 * points3[i].z + d3;
    	sum3 += val * val;
    }
    sum = sum1 + sum2 + sum3;
    sum /= 3;
    sum /= 10;

    printf("Lambda = %lf\n", sum);

	return 1;
}











