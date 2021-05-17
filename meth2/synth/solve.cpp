#include <iostream>
#include <string>
#include <cmath>

#include "functions.h"
#include "point.h"
using namespace std;

int solve (Point * points1, Point * points2, Point * points3, int n1, int n2, int n3)
{
	double sqrt2 = 1.414213562373;

	FILE* f1 = fopen("points1.txt", "r");

    if (!f1) 
    {
        printf (">>>can't open file -> points1.txt\n");
        delete [] points1;
        delete [] points2;
        delete [] points3;
        return -2;
    }

    FILE* f2 = fopen("points2.txt", "r");

    if (!f2) 
    {
        printf (">>>can't open file -> points2.txt\n");
        delete [] points1;
        delete [] points2;
        delete [] points3;
        return -2;
    }

    FILE* f3 = fopen("points3.txt", "r");

    if (!f3) 
    {
        printf (">>>can't open file -> points3.txt\n");
        delete [] points1;
        delete [] points2;
        delete [] points3;
        return -2;
    }

    int i, j, k;
    double val, val1, val2, val3;

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

    // for (i = 0; i < n1; i++)
    // 	printf ("%lf %lf %lf\n", points1[i].x, points1[i].y, points1[i].z);
    // printf("\n");
    // for (i = 0; i < n2; i++)
    // 	printf ("%lf %lf %lf\n", points2[i].x, points2[i].y, points2[i].z);
    // printf("\n");
    // for (i = 0; i < n3; i++)
    // 	printf ("%lf %lf %lf\n", points3[i].x, points3[i].y, points3[i].z);
    // printf("\n");

    line_solve (points1, n1, 1);

    line_solve (points2, n2, 2);

    line_solve (points3, n3, 3);

    points1[n1].x = 0.1;
    points1[n1].y = -6;
    points1[n1].z = 1.5;

    points1[n1+1].x = -0.1;
    points1[n1+1].y = -6;
    points1[n1+1].z = 6.5;

    points2[n2].x = -6;
    points2[n2].y = 0;
    points2[n2].z = 1.5;

    points2[n2+1].x = -6;
    points2[n2+1].y = 0;
    points2[n2+1].z = 7.5;

    points3[n3].x = 3*sqrt2-0.1;
    points3[n3].y = 3*sqrt2+0.1;
    points3[n3].z = 6.5;

    points3[n3+1].x = 3*sqrt2;
    points3[n3+1].y = 3*sqrt2;
    points3[n3+1].z = 7.5;

    double x1_min, y1_min, z1_min, x1_max, y1_max, z1_max;
    double x2_min, y2_min, z2_min, x2_max, y2_max, z2_max;
    double x3_min, y3_min, z3_min, x3_max, y3_max, z3_max;

    f1 = fopen ("line1_data.txt", "r");
    if (!f1)
    {
        printf(">>>cant open file --> line1_data.txt\n");
        return -2;
    }

    if (fscanf (f1, "%lf %lf %lf %lf %lf %lf", &x1_min, &y1_min, &z1_min, &x1_max, &y1_max, &z1_max) != 6)
    {
        printf(">>>cant read from file --> line1_data.txt\n");
        return -3;
    }

    fclose (f1);

    f2 = fopen ("line2_data.txt", "r");
    if (!f2)
    {
        printf(">>>cant open file --> line2_data.txt\n");
        return -2;
    }

    if (fscanf (f2, "%lf %lf %lf %lf %lf %lf", &x2_min, &y2_min, &z2_min, &x2_max, &y2_max, &z2_max) != 6)
    {
        printf(">>>cant read from file --> line2_data.txt\n");
        return -3;
    }

    fclose (f2);

    f3 = fopen ("line3_data.txt", "r");
    if (!f3)
    {
        printf(">>>cant open file --> line3_data.txt\n");
        return -2;
    }

    if (fscanf (f3, "%lf %lf %lf %lf %lf %lf", &x3_min, &y3_min, &z3_min, &x3_max, &y3_max, &z3_max) != 6)
    {
        printf(">>>cant read from file --> line3_data.txt\n");
        return -3;
    }

    fclose (f3);

    double m1, q1, p1, m2, q2, p2, m3, q3, p3;
    double t;

    m1 = x1_max - x1_min; 
    m2 = x2_max - x2_min; 
    m3 = x3_max - x3_min; 

    q1 = y1_max - y1_min; 
    q2 = y2_max - y2_min; 
    q3 = y3_max - y3_min;

    p1 = z1_max - z1_min; 
    p2 = z2_max - z2_min; 
    p3 = z3_max - z3_min; 

    t = (points1[n1].z - z1_min) / p1;
    points1[n1].x = x1_min + m1 * t;
    points1[n1].y = y1_min + q1 * t;

    t = (points1[n1+1].z - z1_min) / p1;
    points1[n1+1].x = x1_min + m1 * t;
    points1[n1+1].y = y1_min + q1 * t;

    t = (points2[n2].z - z2_min) / p2;
    points2[n2].x = x2_min + m2 * t;
    points2[n2].y = y2_min + q2 * t;

    t = (points2[n2+1].z - z2_min) / p2;
    points2[n2+1].x = x2_min + m2 * t;
    points2[n2+1].y = y2_min + q2 * t;

    t = (points3[n3].z - z3_min) / p3;
    points3[n3].x = x3_min + m3 * t;
    points3[n3].y = y3_min + q3 * t;

    t = (points3[n3+1].z - z3_min) / p3;
    points3[n3+1].x = x3_min + m3 * t;
    points3[n3+1].y = y3_min + q3 * t;

    n1 += 2;
    n2 += 2;
    n3 += 2;

    int n = n1;

    for (i = 0; i < n1-1; i++)
    {
    	for (j = i+1; j < n1; j++)
    	{
    		if (points1[i].z > points1[j].z)
    		{
    			val = points1[i].z;
    			points1[i].z = points1[j].z;
    			points1[j].z = val;

    			val = points1[i].x;
    			points1[i].x = points1[j].x;
    			points1[j].x = val;

    			val = points1[i].y;
    			points1[i].y = points1[j].y;
    			points1[j].y = val;
    		}
    	}
    }

    for (i = 0; i < n2-1; i++)
    {
    	for (j = i+1; j < n2; j++)
    	{
    		if (points2[i].z > points2[j].z)
    		{
    			val = points2[i].z;
    			points2[i].z = points2[j].z;
    			points2[j].z = val;

    			val = points2[i].x;
    			points2[i].x = points2[j].x;
    			points2[j].x = val;

    			val = points2[i].y;
    			points2[i].y = points2[j].y;
    			points2[j].y = val;
    		}
    	}
    }

    for (i = 0; i < n3-1; i++)
    {
    	for (j = i+1; j < n3; j++)
    	{
    		if (points3[i].z > points3[j].z)
    		{
    			val = points3[i].z;
    			points3[i].z = points3[j].z;
    			points3[j].z = val;

    			val = points3[i].x;
    			points3[i].x = points3[j].x;
    			points3[j].x = val;

    			val = points3[i].y;
    			points3[i].y = points3[j].y;
    			points3[j].y = val;
    		}
    	}
    }

    // for (i = 0; i < n1; i++)
    // 	printf ("(%lf, %lf, %lf)\n", points1[i].x, points1[i].y, points1[i].z);
    // printf("\n");
    // for (i = 0; i < n2; i++)
    // 	printf ("(%lf, %lf, %lf)\n", points2[i].x, points2[i].y, points2[i].z);
    // printf("\n");
    // for (i = 0; i < n3; i++)
    // 	printf ("(%lf, %lf, %lf)\n", points3[i].x, points3[i].y, points3[i].z);
    // printf("\n");

    double z_min = points1[0].z;
    double z_max = points1[n1-1].z;

    // printf("\nz_min = %lf\n", z_min);
    // printf("\nz_max = %lf\n", z_max);

    Point* points = new Point[n+1000];
    if (!points)
    {
        printf(">>>allocation error -> points\n");
        delete [] points1;
        delete [] points2;
        delete [] points3;
        return -3;
    }

    // for (i = 0; i < n; i++)
    //     printf ("%lf %lf %lf\n", points[i].x, points[i].y, points[i].z);
    // printf("\n");

    triangle (points, points1, points2, points3, n);

    delete [] points;

    check (points1, points2, points3, n);

    return 1;
}
