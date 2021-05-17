#include <iostream>
#include <string>
#include <cmath>

#include "functions.h"
#include "point.h"
using namespace std;

int line_res (double z_min, double z_max)
{
	double lx1, ly1, lz1, lx2, ly2, lz2, lx3, ly3, lz3;
	double x1, y1, z1, x2, y2, z2, x3, y3, z3;
	double rx1, ry1, rz1, rx2, ry2, rz2, rx3, ry3, rz3;

	double val1, val2, val3, val4, val5, val6;

	double sqrt2 = 1.414213562373;

	FILE* f1 = fopen("line1_data.txt", "r");

    if (!f1) 
    {
        printf (">>>can't open file -> line1_data.txt\n");
        return -2;
    }

    if (fscanf (f1, "%lf %lf %lf %lf %lf %lf", &val1, &val2, &val3, &val4, &val5, &val6) != 6)
    {
    	printf (">>>can't open file -> line1_data.txt\n");
    	fclose(f1);
    	return -1;
    }

    lx1 = val1;
    ly1 = val2;
    lz1 = val3;
    x1 = val4;
    y1 = val5;
    z1 = val6;

    fclose (f1);

    // printf("coefs1: %lf %lf %lf %lf %lf %lf\n", lx1, ly1, lz1, x1, y1, z1);

    FILE* f2 = fopen("line2_data.txt", "r");

    if (!f2) 
    {
        printf (">>>can't open file -> line2_data.txt\n");
        return -2;
    }

    if (fscanf (f2, "%lf %lf %lf %lf %lf %lf", &val1, &val2, &val3, &val4, &val5, &val6) != 6)
    {
    	printf (">>>can't open file -> line2_data.txt\n");
    	fclose(f2);
    	return -1;
    }

    lx2 = val1;
    ly2 = val2;
    lz2 = val3;
    x2 = val4;
    y2 = val5;
    z2 = val6;

    fclose (f2);

    // printf("coefs2: %lf %lf %lf %lf %lf %lf\n", lx2, ly2, lz2, x2, y2, z2);

    FILE* f3 = fopen("line3_data.txt", "r");

    if (!f3) 
    {
        printf (">>>can't open file -> line3_data.txt\n");
        return -2;
    }

    if (fscanf (f3, "%lf %lf %lf %lf %lf %lf", &val1, &val2, &val3, &val4, &val5, &val6) != 6)
    {
    	printf (">>>can't open file -> line3_data.txt\n");
    	fclose(f3);
    	return -1;
    }

    lx3 = val1;
    ly3 = val2;
    lz3 = val3;
    x3 = val4;
    y3 = val5;
    z3 = val6;

    fclose (f3);

    // printf("coefs3: %lf %lf %lf %lf %lf %lf\n\n", lx3, ly3, lz3, x3, y3, z3);

    rx1 = 0;
    ry1 = 1;
    rz1 = 0;

    rx2 = 1;
    ry2 = 0;
    rz2 = 0;

    rx3 = -1/sqrt2;
    ry3 = -1/sqrt2;
    rz3 = 0;

    //m --> lx1, lx2, lx3
    //n --> ly1, ly2, ly3
    //p --> lz1, lz2, lz3
    //r_1^1 --> rx1, r_2^1 --> ry1, r_3^1 --> rz1
    //r_1^2 --> rx2, r_2^2 --> ry2, r_3^2 --> rz2
    //r_1^3 --> rx3, r_2^3 --> ry3, r_3^3 --> rz3

    double znam1, znam2, znam3;

    znam1 = sqrt ((ly1 * rz1 - lz1 * ry1)*(ly1 * rz1 - lz1 * ry1) + (lz1 * rx1 - lx1 * rz1)*(lz1 * rx1 - lx1 * rz1) + (lx1 * ry1 - ly1 * lx1)*(lx1 * ry1 - ly1 * lx1));

    znam2 = sqrt ((ly2 * rz2 - lz2 * ry2)*(ly2 * rz2 - lz2 * ry2) + (lz2 * rx2 - lx2 * rz2)*(lz2 * rx2 - lx2 * rz2) + (lx2 * ry2 - ly2 * lx2)*(lx2 * ry2 - ly2 * lx2));

    znam3 = sqrt ((ly3 * rz3 - lz3 * ry3)*(ly3 * rz3 - lz3 * ry3) + (lz3 * rx3 - lx3 * rz3)*(lz3 * rx3 - lx3 * rz3) + (lx3 * ry3 - ly3 * lx3)*(lx3 * ry3 - ly3 * lx3));

    double A1, B1, C1, D1, A2, B2, C2, D2, A3, B3, C3, D3;

    A1 = (ly1 * rz1 - lz1 * ry1) / znam1;
    B1 = (lz1 * rx1 - lx1 * rz1) / znam1;
    C1 = (lx1 * ry1 - ly1 * lx1) / znam1;
    D1 = - ((ly1 * rz1 - lz1 * ry1) * x1 + (lz1 * rx1 - lx1 * rz1) * y1 + (lx1 * ry1 - ly1 * lx1) * z1) / znam1;

    // printf("pi1: %lf %lf %lf %lf\n", A1, B1, C1, D1);

    A2 = (ly2 * rz2 - lz2 * ry2) / znam2;
    B2 = (lz2 * rx2 - lx2 * rz2) / znam2;
    C2 = (lx2 * ry2 - ly2 * lx2) / znam2;
    D2 = - ((ly2 * rz2 - lz2 * ry2) * x2 + (lz2 * rx2 - lx2 * rz2) * y2 + (lx2 * ry2 - ly2 * lx2) * z2) / znam2;

    // printf("pi2: %lf %lf %lf %lf\n", A2, B2, C2, D2);

    A3 = (ly3 * rz3 - lz3 * ry3) / znam3;
    B3 = (lz3 * rx3 - lx3 * rz3) / znam3;
    C3 = (lx3 * ry3 - ly3 * lx3) / znam3;
    D3 = - ((ly3 * rz3 - lz3 * ry3) * x3 + (lz3 * rx3 - lx3 * rz3) * y3 + (lx3 * ry3 - ly3 * lx3) * z3) / znam3;

    // printf("pi3: %lf %lf %lf %lf\n", A3, B3, C3, D3);

    double a11, a12, a22, b1_min, b1_max, b2_min, b2_max;

    a11 = A1*A1 + A2*A2 + A3*A3;
    a12 = A1*B1 + A2*B2 + A3*B3;
    a22 = B1*B1 + B2*B2 + B3*B3;
    b1_min = A1*(C1*z_min+D1) + A2*(C2*z_min+D2) + A3*(C3*z_min+D3);
    b1_max = A1*(C1*z_max+D1) + A2*(C2*z_max+D2) + A3*(C3*z_max+D3);
    b2_min = B1*(C1*z_min+D1) + B2*(C2*z_min+D2) + B3*(C3*z_min+D3);
    b2_max = B1*(C1*z_max+D1) + B2*(C2*z_max+D2) + B3*(C3*z_max+D3);

    double x_min, y_min, x_max, y_max;

    x_min = (a22*b1_min - a12*b2_min) / (a12*a12 - a11*a22);
    y_min = (a11*b2_min - a12*b1_min) / (a12*a12 - a11*a22);

    x_max = (a22*b1_max - a12*b2_max) / (a12*a12 - a11*a22);
    y_max = (a11*b2_max - a12*b1_max) / (a12*a12 - a11*a22);

    FILE* f;
    f = fopen ("line_data.txt", "w");
    if (!f)
    {
        printf(">>>cant open file --> line_data.txt\n");
        return -2;
    }

    //printf("%lf %lf %lf\n%lf %lf %lf\n", x_min, y_min, z_min, x_max, y_max, z_max);

    double p, q, r, zn;
    p = x_max - x_min;
    q = y_max - y_min;
    r = z_max - z_min;
    zn = sqrt (p*p + q*q + r*r);
    p /= zn;
    q /= zn;
    r /= zn;
    fprintf(f, "%lf %lf %lf\n%lf %lf %lf\n", p, q, r, x_min, y_min, z_min);

    fclose (f);

    printf("TWO POINTS OF RESULT LINE:\n");
    system ("cat line_data.txt");
    // printf("%lf %lf %lf\n", x_max, y_max, z_max);
    printf("\n");

	return 1;
}