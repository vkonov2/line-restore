#include <iostream>
#include <string>
#include <cmath>

#include "functions.h"
#include "point.h"
using namespace std;

int line_solve (Point * points, int n, int flag, char* str)
{
	FILE* f;
    int i, j, err;
    double eigen_val[3];
    double coefs[3];
    double x[3];

    for (i = 0; i < 3; i++)
        coefs[i] = 0.0;

    double sum_x, sum_y, sum_z;

    for (i = 0; i < 3; i++)
        x[i] = 0.0;

    for (i = 0; i < n; i++)
    {
        x[0] += points[i].x;
        x[1] += points[i].y;
        x[2] += points[i].z;
    }

    for (i = 0; i < 3; i++)
        x[i] /= ((double)(n));

    double *A;
    double a11, a12, a13, a21, a22, a23, a31, a32, a33;
    double eps = 1e-2;
    double m, nn, p;

    double val1, val2, val3;

    double a_xy = 0.0, a_xz = 0.0, a_yz = 0.0, b_xy = 0.0, b_xz = 0.0, b_yz = 0.0;

    for (i = 0; i < n; i++)
    {
        val1 = points[i].x - x[0];
        val2 = points[i].y - x[1];
        val3 = points[i].z - x[2];

        a_xz += val1 * val1 + val3 * val3;
        a_yz += val2 * val2 + val3 * val3;
        a_xy += val1 * val1 + val2 * val2;
        b_yz += val2 * val3;
        b_xz += val1 * val3;
        b_xy += val1 * val2;
    }

    A = (double *)malloc(9 * sizeof (double));
    if (!A)
    {
        printf(">>>allocation error -> A\n");
        return -1;
    }

    a11 = a_yz;
    a12 = -b_xy;
    a13 = -b_xz;
    a21 = -b_xy;
    a22 = a_xz;
    a23 = -b_yz;
    a31 = -b_xz;
    a32 = -b_yz;
    a33 = a_xy;

    A[0] = a11;
    A[1] = a12;
    A[2] = a13;
    A[3] = a21;
    A[4] = a22;
    A[5] = a23;
    A[6] = a31;
    A[7] = a32;
    A[8] = a33;

    // for (i = 0; i < 9; i++)
    //     printf("A[%d] = %.2lf\n", i, A[i]);

    err = eigen (3, 3, eps, A);
    if (err < 0)
    {
        printf("\n>>>error in func -> eigen\n");
        free (A);
        return err;
    }

    eigen_val[0] = A[0];
    eigen_val[1] = A[4];
    eigen_val[2] = A[8];

    // for (i = 0; i < 3; i++)
    //     printf("eigen_val[%d] = %.2lf\n", i, eigen_val[i]);

    A[0] = a11;
    A[1] = a12;
    A[2] = a13;
    A[3] = a21;
    A[4] = a22;
    A[5] = a23;
    A[6] = a31;
    A[7] = a32;
    A[8] = a33;

    // for (i = 0; i < 9; i++)
    //     printf("A[%d] = %.2lf\n", i, A[i]);

    err = vect (eigen_val, A, coefs, points, n);
    if (err < 0)
    {
        printf("\n>>>error in func -> vect\n");
        free (A);
        return err;
    }

    free (A);

    m = coefs[0];
    nn = coefs[1];
    p = coefs[2];

	// if (flag == 0)
 //    {
 //        printf ("vector of line:\n");
 //        printf ("(%lf, %lf, %lf)\n\n", m, nn, p);

 //        printf ("point of line:\n");
 //        printf ("(%lf, %lf, %lf)\n\n", x[0], x[1], x[2]);
 //    }

    double x_min, y_min, z_min, x_max, y_max, z_max, t;

    z_min = -6.08332812434530;
    z_max = -4.57712089734895;

    t = (z_min - x[2]) / p;
    x_min = t * m + x[0];
    y_min = t * nn + x[1];

    t = (z_max - x[2]) / p;
    x_max = t * m + x[0];
    y_max = t * nn + x[1];

    f = fopen (str, "w");
    if (!f)
    {
        printf(">>>can't open file -> line_coefs.txt\n");
        return -1;
    }
	if (flag == 1)
        fprintf(f, "%lf %lf %lf\n %lf %lf %lf\n", x_min, y_min, z_min, x_max, y_max, z_max);
    // else if (flag == 0)
    //     fprintf(f, "%lf %lf %lf\n %lf %lf %lf\n", x_min, y_min, z_min, x_max, y_max, z_max);
    else
        fprintf(f, "%lf %lf %lf\n %lf %lf %lf\n", m, nn, p, x[0], x[1], x[2]);
	fclose (f);

    if (flag == 0)
    {
        printf("TWO POINTS OF POSITIVE LINE:\n");
        printf("(%lf, %lf, %lf)\n", x_min, y_min, z_min);
        printf("(%lf, %lf, %lf)\n", x_max, y_max, z_max);
    }

    if (flag == -2)
    {
        printf("TWO POINTS OF NEGATIVE LINE:\n");
        printf("(%lf, %lf, %lf)\n", x_min, y_min, z_min);
        printf("(%lf, %lf, %lf)\n", x_max, y_max, z_max);
    }

    if (flag == 0)
    {
        f = fopen ("line2_p_data.txt", "w");
        if (!f)
        {
            printf(">>>can't open file -> line_coefs.txt\n");
            return -1;
        }
        fprintf(f, "%lf %lf %lf\n %lf %lf %lf\n", x_min, y_min, z_min, x_max, y_max, z_max);
        
        fclose (f);
    }

    if (flag == -2)
    {
        f = fopen ("line2_m_data.txt", "w");
        if (!f)
        {
            printf(">>>can't open file -> line_coefs.txt\n");
            return -1;
        }
        fprintf(f, "%lf %lf %lf\n %lf %lf %lf\n", x_min, y_min, z_min, x_max, y_max, z_max);
        
        fclose (f);
    }

    return 1;
}
