#include <iostream>
#include <string>
#include <cmath>

#include "functions.h"
#include "point.h"
using namespace std;

int solve (Point * points1, Point * points2, Point * points3, int n1, int n2, int n3)
{
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

    for (i = 0; i < n1; i++)
    	printf ("%lf %lf %lf\n", points1[i].x, points1[i].y, points1[i].z);
    printf("\n");
    for (i = 0; i < n2; i++)
    	printf ("%lf %lf %lf\n", points2[i].x, points2[i].y, points2[i].z);
    printf("\n");
    for (i = 0; i < n3; i++)
    	printf ("%lf %lf %lf\n", points3[i].x, points3[i].y, points3[i].z);
    printf("\n");

    double z_min = points1[0].z;
    double z_max = points1[n1-1].z;

    // printf("\nz_min = %lf\n", z_min);
    // printf("\nz_max = %lf\n", z_max);

    line_solve (points1, n1, 1);

    line_solve (points2, n2, 2);

    line_solve (points3, n3, 3);

    line_res (z_min, z_max);

    check (points1, points2, points3, n1, z_min, z_max);

    return 1;
}
