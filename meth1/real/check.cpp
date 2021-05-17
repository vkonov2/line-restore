#include <iostream>
#include <string>
#include <cmath>

#include "functions.h"
#include "point.h"
using namespace std;

int check (Point** points, Point* vecs, int* n, const int count, int flag)
{
	int i, j, k;

	FILE* f;
    if (flag == 0)
        f = fopen("line_p_data.txt", "r");
    else
        f = fopen("line_m_data.txt", "r");
    if (!f) 
    {
        printf (">>>can't open file -> line_data.txt\n");
        return -2;
    }

    double p, q, r, x0, y0, z0;
    
    if (fscanf (f, "%lf", &p) != 1)
    {
        printf (">>>wrong data in file -> line_data.txt\n");
        fclose (f);
        return -4;
    }
    if (fscanf (f, "%lf", &q) != 1)
    {
        printf (">>>wrong data in file -> line_data.txt\n");
        fclose (f);
        return -4;
    }
    if (fscanf (f, "%lf", &r) != 1)
    {
        printf (">>>wrong data in file -> line_data.txt\n");
        fclose (f);
        return -4;
    }
    if (fscanf (f, "%lf", &x0) != 1)
    {
        printf (">>>wrong data in file -> line_data.txt\n");
        fclose (f);
        return -4;
    }
    if (fscanf (f, "%lf", &y0) != 1)
    {
        printf (">>>wrong data in file -> line_data.txt\n");
        fclose (f);
        return -4;
    }
    if (fscanf (f, "%lf", &z0) != 1)
    {
        printf (">>>wrong data in file -> line_data.txt\n");
        fclose (f);
        return -4;
    }

    fclose (f);

    double* znam = new double[count];
    if (!znam)
    {
        printf(">>>allocation error --> znam\n");
        return -1;
    }

    for (i = 0; i < count; i++)
        znam[i] = 0;

    for (i = 0; i < count; i++)
        znam[i] = sqrt( (-r * vecs[i].y)*(-r * vecs[i].y) + (r * vecs[i].x)*(r * vecs[i].x) + (p * vecs[i].y - q * vecs[i].x)*(p * vecs[i].y - q * vecs[i].x) );

    double* a = new double[count];
    if (!a)
    {
        printf(">>>allocation error --> a\n");
        delete [] znam;
        return -1;
    }

    for (i = 0; i < count; i++)
        a[i] = 0;

    double* b = new double[count];
    if (!b)
    {
        printf(">>>allocation error --> b\n");
        delete [] znam;
        delete [] a;
        return -1;
    }

    for (i = 0; i < count; i++)
        b[i] = 0;

    double* c = new double[count];
    if (!c)
    {
        printf(">>>allocation error --> a\n");
        delete [] znam;
        delete [] a;
        delete [] b;
        return -1;
    }

    for (i = 0; i < count; i++)
        c[i] = 0;

    double* d = new double[count];
    if (!d)
    {
        printf(">>>allocation error --> a\n");
        delete [] znam;
        delete [] a;
        delete [] b;
        delete [] c;
        return -1;
    }

    for (i = 0; i < count; i++)
        d[i] = 0;

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

    for (i = 0; i < count; i++)
    {
        a[i] = (- r * vecs[i].y) / znam[i];
        b[i] = (r * vecs[i].x) / znam[i];
        c[i] = (p * vecs[i].y - q * vecs[i].x) / znam[i];
        d[i] = -( (- r * vecs[i].y) * x0 + (r * vecs[i].x) * y0 + (p * vecs[i].y - q * vecs[i].x) * z0 ) / znam[i];
    }

    // printf("\n");
    // for (i = 0; i < 10; i++)
    //   printf("%d: %lf %lf %lf %lf\n", i, a[i], b[i], c[i], d[i]);
    // printf("\n");

    // k = 0;
    // for (j = 0; j < n[k]; j++)
    //   printf("%lf %lf %lf\n", points[k][j].x, points[k][j].y, points[k][j].z);

    double summ = 0, val;

    double* sum = new double[count];
    if (!sum)
    {
        printf(">>>allocation error --> a\n");
        delete [] znam;
        delete [] a;
        delete [] b;
        delete [] c;
        delete [] d;
        return -1;
    }

    for (i = 0; i < count; i++)
        sum[i] = 0;

    for (i = 0; i < count; i++)
    {
        for (j = 0; j < n[i]; j++)
        {
            val = a[i]*points[i][j].x + b[i]*points[i][j].y + c[i]*points[i][j].z + d[i];
            sum[i] += val * val;
        }
    }

    for (i = 0; i < count; i++)
        summ += sum[i];

    summ /= 180;
    summ /= 100;

    printf("Lambda = %lf\n", summ);
    printf("sqrt(Lambda) = %lf\n", sqrt (summ));

    // znam1 = sqrt( (-r * l1_y)*(-r * l1_y) + (r * l1_x)*(r * l1_x) + (p * l1_y - q * l1_x)*(p * l1_y - q * l1_x) );

    // znam2 = sqrt( (-r * l2_y)*(-r * l2_y) + (r * l2_x)*(r * l2_x) + (p * l2_y - q * l2_x)*(p * l2_y - q * l2_x) );

    // znam3 = sqrt( (-r * l3_y)*(-r * l3_y) + (r * l3_x)*(r * l3_x) + (p * l3_y - q * l3_x)*(p * l3_y - q * l3_x) );

    // a1 = (- r * l1_y) / znam1;
    // b1 = (r * l1_x) / znam1;
    // c1 = (p * l1_y - q * l1_x) / znam1;
    // d1 = -( (- r * l1_y) * x0 + (r * l1_x) * y0 + (p * l1_y - q * l1_x) * z0 ) / znam1;

    // a2 = (- r * l2_y) / znam2;
    // b2 = (r * l2_x) / znam2;
    // c2 = (p * l2_y - q * l2_x) / znam2;
    // d2 = -( (- r * l2_y) * x0 + (r * l2_x) * y0 + (p * l2_y - q * l2_x) * z0 ) / znam2;

    // a3 = (- r * l3_y) / znam3;
    // b3 = (r * l3_x) / znam3;
    // c3 = (p * l3_y - q * l3_x) / znam3;
    // d3 = -( (- r * l3_y) * x0 + (r * l3_x) * y0 + (p * l3_y - q * l3_x) * z0 ) / znam3;

    // printf("\n %.2lf %.2lf %.2lf\n", a1, b1, c1);
    // printf("\n %.2lf %.2lf %.2lf\n", a2, b2, c2);
    // printf("\n %.2lf %.2lf %.2lf\n", a3, b3, c3);

  //   for (i = 0; i < 1000; i++)
  //   {
  //   	points1[i].x = 0;
  //   	points1[i].y = 0;
  //   	points1[i].z = 0;
  //   	points2[i].x = 0;
  //   	points2[i].y = 0;
  //   	points2[i].z = 0;
  //   	points3[i].x = 0;
  //   	points3[i].y = 0;
  //   	points3[i].z = 0;
  //   }

  //   FILE* f1 = fopen("points1.txt", "r");

  //   if (!f1) 
  //   {
  //       printf (">>>can't open file -> points1.txt\n");
  //       delete [] points1;
  //       delete [] points2;
  //       delete [] points3;
  //       return -2;
  //   }

  //   FILE* f2 = fopen("points2.txt", "r");

  //   if (!f2) 
  //   {
  //       printf (">>>can't open file -> points2.txt\n");
  //       delete [] points1;
  //       delete [] points2;
  //       delete [] points3;
  //       return -2;
  //   }

  //   FILE* f3 = fopen("points3.txt", "r");

  //   if (!f3) 
  //   {
  //       printf (">>>can't open file -> points3.txt\n");
  //       delete [] points1;
  //       delete [] points2;
  //       delete [] points3;
  //       return -2;
  //   }

  //   for (i = 0; i < n1; i++)
  //   {
  //   	if (fscanf(f1, "%lf %lf %lf", &val1, &val2, &val3) != 3)
		// 	return -4;
		// else
		// {
		// 	points1[i].x = val1;
		// 	points1[i].y = val2;
		// 	points1[i].z = val3;
		// }
  //   }
  //   for (i = 0; i < n2; i++)
  //   {
  //   	if (fscanf(f2, "%lf %lf %lf", &val1, &val2, &val3) != 3)
		// 	return -4;
		// else
		// {
		// 	points2[i].x = val1;
		// 	points2[i].y = val2;
		// 	points2[i].z = val3;
		// }
  //   }
  //   for (i = 0; i < n3; i++)
  //   {
  //   	if (fscanf(f3, "%lf %lf %lf", &val1, &val2, &val3) != 3)
		// 	return -4;
		// else
		// {
		// 	points3[i].x = val1;
		// 	points3[i].y = val2;
		// 	points3[i].z = val3;
		// }
  //   }

  //   fclose (f1);
  //   fclose (f2);
  //   fclose (f3);

    // double sum = 0, sum1 = 0, sum2 = 0, sum3 = 0;
    // for (i = 0; i < n1; i++)
    // {
    // 	val = a1 * points1[i].x + b1 * points1[i].y + c1 * points1[i].z + d1;
    // 	sum1 += val * val;
    // }
    // for (i = 0; i < n2; i++)
    // {
    // 	val = a2 * points2[i].x + b2 * points2[i].y + c2 * points2[i].z + d2;
    // 	sum2 += val * val;
    // }
    // for (i = 0; i < n3; i++)
    // {
    // 	val = a3 * points3[i].x + b3 * points3[i].y + c3 * points3[i].z + d3;
    // 	sum3 += val * val;
    // }
    // sum = sum1 + sum2 + sum3;

    // printf("Lambda = %lf\n", sum);

	return 1;
}











