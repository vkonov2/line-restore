#include <iostream>
#include <string>
#include <cmath>

#include "functions.h"
#include "point.h"
using namespace std;

int get_new_points (Point** points, int* n, const int count)
{
	int i, j, k, r;
	int n_new;
	int flag, zero_beg, zero_fin, zero0_beg, zero0_fin, zero1_beg, zero1_fin;

	double m, l, p, t;

	double z_min, z_max, cur, val;
    
    z_min = -6.08332812434530;
    z_max = -4.57712089734895;

    Point* mem_points[count];

    for (i = 0; i < count; i++)
    {
        mem_points[i] = new Point[20000];
        if (!mem_points[i])
        {
            printf(">>>allocation error\n");
            return -3;
        }

        for (j = 0; j < n[i]; j++)
        {
            mem_points[i][j].x = points[i][j].x;
            mem_points[i][j].y = points[i][j].y;
            mem_points[i][j].z = points[i][j].z;
        }
    }

    int* n_mem = new int[count];
    if (!n_mem)
    {
        printf(">>>allocation error --> n\n");
        for (i = 0; i < count; i++)
        	delete [] mem_points[i];
        return -1;
    }

    for (i = 0; i < count; i++)
        n_mem[i] = n[i];

	for (i = 0; i < count; i++)
	{
		for (j = 0; j < i; j++)
		{
			n_new = n[i];
			for (k = 0; k < n_mem[j]; k++)
			{
				points[i][n_new].z = mem_points[j][k].z;
				n_new++;
			}
			n[i] = n_new;
		}

		for (j = i+1; j < count; j++)
		{
			n_new = n[i];
			for (k = 0; k < n_mem[j]; k++)
			{
				points[i][n_new].z = mem_points[j][k].z;
				n_new++;
			}
			n[i] = n_new;
		}
	}

	// for (i = 0; i < count; i++)
	// 	printf("%d\n", n_mem[i]);

	// for (i = 0; i < count; i++)
	// 	printf("%d\n", n[i]);

	// k = 0;
	// for (j = 0; j < n[k]; j++)
	// 	printf("%lf %lf %lf\n", points[k][j].x, points[k][j].y, points[k][j].z);

	for (i = 0; i < count; i++)
	{
		for (j = 0; j < n[i]-1; j++)
		{
			for (k = j+1; k < n[i]; k++)
			{
				if (points[i][j].z > points[i][k].z)
				{
					val = points[i][j].x;
					points[i][j].x = points[i][k].x;
					points[i][k].x = val;

					val = points[i][j].y;
					points[i][j].y = points[i][k].y;
					points[i][k].y = val;

					val = points[i][j].z;
					points[i][j].z = points[i][k].z;
					points[i][k].z = val;
				}
			}
		}
	}

	// k = 0;
	// for (j = 0; j < n[k]; j++)
	// 	printf("%lf %lf %lf\n", points[k][j].x, points[k][j].y, points[k][j].z);

	//beg_nonzero = 73;
	// for (i = 0; i < count; i++)
	// {
	// 	printf("%d: %lf %lf %lf\n", i, points[i][0].x, points[i][0].y, points[i][0].z);
	// }

	// FILE* f;
	//    f = fopen ("test_data.txt", "w");
	//    if (!f)
	//    {
	//        printf(">>>cant open file --> test_data.txt\n");
	//        for (i = 0; i < count; i++)
	//        	delete [] mem_points[i];
	//        delete [] n_mem;
	//        return -2;
	//    }

	//    k=0;
	//    for (j = 0; j < n[k]; j++)
	//    	fprintf(f, "%lf %lf %lf\n", points[k][j].x, points[k][j].y, points[k][j].z);

	//    fclose(f);

	// k = 0;
	// for (j = 0; j < 170; j++)
	// 	printf("%lf %lf %lf\n", points[k][j].x, points[k][j].y, points[k][j].z);

	for (i = 0; i < count; i++)
	{
		j = 0;
		while (j < n[i]-1)
		{
			// printf("\nbegin of %d step\n", j);

			if ((fabs(points[i][j].x) < 1e-14)&&(fabs(points[i][j].y) < 1e-14))
			{
				zero0_beg = j;

				// printf("step1\n");
            	// printf("zero0_beg = %d\n", zero0_beg);

				for (k = j+1; k < n[i]; k++)
				{
					if (!((fabs(points[i][k].x) < 1e-14)&&(fabs(points[i][k].y) < 1e-14)))
					{
						zero0_fin = k;
						break;
					}
				}

				// printf("step2\n");
            	// printf("zero0_fin = %d\n", zero0_fin);

				zero1_beg = zero0_fin + 1;

				// printf("zero1_beg = %d\n", zero1_beg);

				for (k = zero1_beg; k < n[i]; k++)
				{
					if (!((fabs(points[i][k].x) < 1e-14)&&(fabs(points[i][k].y) < 1e-14)))
					{
						zero1_fin = k;
						break;
					}
				}

				// printf("step3\n");
            	// printf("zero1_fin = %d\n", zero1_fin);

				//point[i][zero0_fin]
				//point[i][zero1_fin]

				m = points[i][zero1_fin].x - points[i][zero0_fin].x;
				l = points[i][zero1_fin].y - points[i][zero0_fin].y;
				p = points[i][zero1_fin].z - points[i][zero0_fin].z;

				// printf("m = %lf\n", m);
	   			// printf("l = %lf\n", l);
	   			// printf("p = %lf\n", p);

				t = (points[i][j].z - points[i][zero0_fin].z) / p;

				// printf("t = %lf\n", t);

				points[i][j].x = m * t + points[i][zero0_fin].x;
				points[i][j].y = l * t + points[i][zero0_fin].y;

				// printf("%lf %lf %lf\n", points[i][j].x, points[i][j].y, points[i][j].z);
			}

			j++;
		}
	}

	// k = 0;
	// for (j = 0; j < 300; j++)
	// 	printf("%lf %lf %lf\n", points[k][j].x, points[k][j].y, points[k][j].z);

	// printf("\n\n");

	for (int i = 0; i < count; ++i)
		delete [] mem_points[i];

	delete [] n_mem;

	return n[0];
}