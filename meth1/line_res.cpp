#include <iostream>
#include <string>
#include <cmath>

#include "functions.h"
#include "point.h"
using namespace std;

int line_res (Point* vecs, const int count)
{
	int i, j, k;

	FILE* f;

	char num[10];
	char num0[10];
	char str[100];

	double val1, val2, val3, val4, val5, val6;

	Point* ppoints[count];

	for (i = 0; i < count; i++)
    {
        ppoints[i] = new Point[10];
        if (!ppoints[i])
        {
            printf(">>>allocation error --> points\n");
            return -3;
        }

        for (j = 0; j < 10; j++)
        {
            ppoints[i][j].x = 0;
            ppoints[i][j].y = 0;
            ppoints[i][j].z = 0;
        }
    }

    Point* mpoints[count];

	for (i = 0; i < count; i++)
    {
        mpoints[i] = new Point[10];
        if (!mpoints[i])
        {
            printf(">>>allocation error --> points\n");
            for (j = 0; j < count; j++)
            	delete [] ppoints[j];
            return -3;
        }

        for (j = 0; j < 10; j++)
        {
            mpoints[i][j].x = 0;
            mpoints[i][j].y = 0;
            mpoints[i][j].z = 0;
        }
    }

	for (i = 0; i < count; i++)
	{
	    memset (num, 0, 10);
	    memset (num0, 0, 10);
	    memset (str, 0, 100);

	    strcpy (str, "line_p_data");

	    if (i < 10)
	    {   
	        strcpy (num, "0");
	        sprintf (num0, "%d", i);
	        strcat (num, num0);
	    }
	    else
	        sprintf (num, "%d", i);

	    strcat (str, num);

	    // printf("%s\n", str);

	    strcat (str, ".txt");

	    f = fopen (str, "r");
	    if (!f)
	    {
	    	printf(">>>cant open file --> %s\n", str);
	    	for (j = 0; j < count; j++)
	    	{
				delete [] ppoints[j];
				delete [] mpoints[j];
	    	}   
			return -1;
	    }

	    if (fscanf (f, "%lf %lf %lf %lf %lf %lf", &val1, &val2, &val3, &val4, &val5, &val6) != 6)
	    {
	        printf(">>>cant read file --> %s\n", str);
	        for (j = 0; j < count; j++)
	    	{
				delete [] ppoints[j];
				delete [] mpoints[j];
	    	}
	        return -1;
	    }

	    ppoints[i][0].x = val1;
	    ppoints[i][0].y = val2;
	    ppoints[i][0].z = val3;
	    ppoints[i][1].x = val4;
	    ppoints[i][1].y = val5;
	    ppoints[i][1].z = val6;

	    fclose (f);
	}

	//printf("\n");

	for (i = 0; i < count; i++)
	{
	    memset (num, 0, 10);
	    memset (num0, 0, 10);
	    memset (str, 0, 100);

	    strcpy (str, "line_m_data");

	    if (i < 10)
	    {   
	        strcpy (num, "0");
	        sprintf (num0, "%d", i);
	        strcat (num, num0);
	    }
	    else
	        sprintf (num, "%d", i);

	    strcat (str, num);

	    // printf("%s\n", str);

	    strcat (str, ".txt");

	    f = fopen (str, "r");
	    if (!f)
	    {
	    	printf(">>>cant open file --> %s\n", str);
	    	for (j = 0; j < count; j++)
	    	{
				delete [] ppoints[j];
				delete [] mpoints[j];
	    	}
			return -1;
	    }

	    if (fscanf (f, "%lf %lf %lf %lf %lf %lf", &val1, &val2, &val3, &val4, &val5, &val6) != 6)
	    {
	        printf(">>>cant read file --> %s\n", str);
	        for (j = 0; j < count; j++)
	    	{
				delete [] ppoints[j];
				delete [] mpoints[j];
	    	}
	        return -1;
	    }

	    mpoints[i][0].x = val1;
	    mpoints[i][0].y = val2;
	    mpoints[i][0].z = val3;
	    mpoints[i][1].x = val4;
	    mpoints[i][1].y = val5;
	    mpoints[i][1].z = val6;

	    fclose (f);
	}

	// k = 0;
	// for (j = 0; j < 2; j++)
	// 	printf("%lf %lf %lf\n", ppoints[k][j].x, ppoints[k][j].y, ppoints[k][j].z);

	double* A = new double[count];
	if (!A)
	{
		printf(">>>allocation error --> A\n");
		for (j = 0; j < count; j++)
    	{
			delete [] ppoints[j];
			delete [] mpoints[j];
    	}
		return -2;
	}

	double* B = new double[count];
	if (!B)
	{
		printf(">>>allocation error --> B\n");
		for (j = 0; j < count; j++)
    	{
			delete [] ppoints[j];
			delete [] mpoints[j];
    	}
    	delete [] A;
		return -2;
	}

	double* C = new double[count];
	if (!C)
	{
		printf(">>>allocation error --> C\n");
		for (j = 0; j < count; j++)
    	{
			delete [] ppoints[j];
			delete [] mpoints[j];
    	}
    	delete [] A;
		delete [] B;
		return -2;
	}

	double* D = new double[count];
	if (!D)
	{
		printf(">>>allocation error --> D\n");
		for (j = 0; j < count; j++)
    	{
			delete [] ppoints[j];
			delete [] mpoints[j];
    	}
    	delete [] A;
		delete [] B;
		delete [] C;
		return -2;
	}

	double* znam = new double[count];
	if (!znam)
	{
		printf(">>>allocation error --> znam\n");
		for (j = 0; j < count; j++)
    	{
			delete [] ppoints[j];
			delete [] mpoints[j];
    	}
    	delete [] A;
		delete [] B;
		delete [] C;
		delete [] D;
		return -2;
	}

	for (i = 0; i < count; i++)
	{
		A[i] = 0;
		B[i] = 0;
		C[i] = 0;
		D[i] = 0;
		znam[i] = 0;
	}

	double lx, ly, lz, rx, ry, rz, x, y, z;

	double x_min, y_min, x_max, y_max, z_min, z_max;

	z_min = -6.08332812434530;
    z_max = -4.57712089734895;

	double a11, a12, a22, b1_min, b1_max, b2_min, b2_max;

	for (i = 0; i < count; i++)
	{
		lx = ppoints[i][0].x;
		ly = ppoints[i][0].y;
		lz = ppoints[i][0].z;
		rx = vecs[i].x;
		ry = vecs[i].y;
		rz = vecs[i].z;
		x = ppoints[i][1].x;
		y = ppoints[i][1].y;
		z = ppoints[i][1].z;

		znam[i] = sqrt ((ly * rz - lz * ry)*(ly * rz - lz * ry) + (lz * rx - lx * rz)*(lz * rx - lx * rz) + (lx * ry - ly * rx)*(lx * ry - ly * rx));

		A[i] = (ly * rz - lz * ry) / znam[i];
	    B[i] = (lz * rx - lx * rz) / znam[i];
	    C[i] = (lx * ry - ly * rx) / znam[i];
	    D[i] = - ((ly * rz - lz * ry) * x + (lz * rx - lx * rz) * y + (lx * ry - ly * rx) * z) / znam[i];
	}

	// for (i = 0; i < count; i++)
	// 	printf("znam[%d] = %lf\n", i, znam[i]);

	// for (i = 0; i < count; i++)
	// 	printf("A[%d] = %lf\n", i, A[i]);

	// for (i = 0; i < count; i++)
	// 	printf("B[%d] = %lf\n", i, B[i]);

	// for (i = 0; i < count; i++)
	// 	printf("C[%d] = %lf\n", i, C[i]);

	// for (i = 0; i < count; i++)
	// 	printf("D[%d] = %lf\n", i, D[i]);

	// k = 1;
	// for (i = 0; i < k; i++)
	// 	printf("%d: %lf %lf %lf %lf\n", i, A[i], B[i], C[i], D[i]);

	// printf("\n\n");

	a11 = 0; a12 = 0; a22 = 0; b1_min = 0; b1_max = 0; b2_min = 0; b2_max = 0;

	// printf("a11 = %lf\n", a11);
	// printf("a12 = %lf\n", a12);
	// printf("a22 = %lf\n", a22);

	for (i = 0; i < count; i++)
	{
		a11 += A[i]*A[i];
		a12 += A[i]*B[i];
		a22 += B[i]*B[i];
		b1_min += A[i]*(C[i]*z_min+D[i]);
	    b1_max += A[i]*(C[i]*z_max+D[i]);
	    b2_min += B[i]*(C[i]*z_min+D[i]);
	    b2_max += B[i]*(C[i]*z_max+D[i]);
	}

	// printf("a11 = %lf\n", a11);
	// printf("a12 = %lf\n", a12);
	// printf("a22 = %lf\n", a22);

	x_min = (a22*b1_min - a12*b2_min) / (a12*a12 - a11*a22);
    y_min = (a11*b2_min - a12*b1_min) / (a12*a12 - a11*a22);

    x_max = (a22*b1_max - a12*b2_max) / (a12*a12 - a11*a22);
    y_max = (a11*b2_max - a12*b1_max) / (a12*a12 - a11*a22);

    double znam_line, x_line, y_line, z_line;

    znam_line = sqrt ((x_max - x_min)*(x_max - x_min) + (y_max - y_min)*(y_max - y_min) + (z_max - z_min)*(z_max - z_min) );
    x_line = (x_max - x_min) / znam_line;
    y_line = (y_max - y_min) / znam_line;
    z_line = (z_max - z_min) / znam_line;

    f = fopen ("line_p_data.txt", "w");
    if (!f)
    {
        printf(">>>cant open file --> line_p_data.txt\n");
        return -2;
    }

    fprintf(f, "%lf %lf %lf\n%lf %lf %lf\n", x_line, y_line, z_line, x_max, y_max, z_max);

    // fprintf(f, "%lf %lf %lf\n%lf %lf %lf\n", x_min, y_min, z_min, x_max, y_max, z_max);

    // double p, q, r, zn;
    // p = x_max - x_min;
    // q = y_max - y_min;
    // r = z_max - z_min;
    // zn = sqrt (p*p + q*q + r*r);
    // p /= zn;
    // q /= zn;
    // r /= zn;
    // fprintf(f, "%lf %lf %lf\n%lf %lf %lf\n", p, q, r, x_min, y_min, z_min);

    fclose (f);

    f = fopen ("line2_p_data.txt", "w");
    if (!f)
    {
        printf(">>>cant open file --> line_m_data.txt\n");
        return -2;
    }

    fprintf(f, "%lf %lf %lf\n%lf %lf %lf\n", x_min, y_min, z_min, x_max, y_max, z_max);

    fclose (f);

    printf("TWO POINTS OF RESULT LINE:\n");
    system ("cat line2_p_data.txt");
    printf("\n");

    for (i = 0; i < count; i++)
	{
		lx = mpoints[i][0].x;
		ly = mpoints[i][0].y;
		lz = mpoints[i][0].z;
		rx = vecs[i].x;
		ry = vecs[i].y;
		rz = vecs[i].z;
		x = mpoints[i][1].x;
		y = mpoints[i][1].y;
		z = mpoints[i][1].z;

		znam[i] = sqrt ((ly * rz - lz * ry)*(ly * rz - lz * ry) + (lz * rx - lx * rz)*(lz * rx - lx * rz) + (lx * ry - ly * rx)*(lx * ry - ly * rx));

		A[i] = (ly * rz - lz * ry) / znam[i];
	    B[i] = (lz * rx - lx * rz) / znam[i];
	    C[i] = (lx * ry - ly * rx) / znam[i];
	    D[i] = - ((ly * rz - lz * ry) * x + (lz * rx - lx * rz) * y + (lx * ry - ly * rx) * z) / znam[i];
	}

	// for (i = 0; i < count; i++)
	// 	printf("znam[%d] = %lf\n", i, znam[i]);

	// for (i = 0; i < count; i++)
	// 	printf("A[%d] = %lf\n", i, A[i]);

	// for (i = 0; i < count; i++)
	// 	printf("B[%d] = %lf\n", i, B[i]);

	// for (i = 0; i < count; i++)
	// 	printf("C[%d] = %lf\n", i, C[i]);

	// for (i = 0; i < count; i++)
	// 	printf("D[%d] = %lf\n", i, D[i]);

	// for (i = 0; i < k; i++)
	// 	printf("%d: %lf %lf %lf %lf\n", i, A[i], B[i], C[i], D[i]);

	a11 = 0; a12 = 0; a22 = 0; b1_min = 0; b1_max = 0; b2_min = 0; b2_max = 0;

	for (i = 0; i < count; i++)
	{
		a11 += A[i]*A[i];
		a12 += A[i]*B[i];
		a22 += B[i]*B[i];
		b1_min += A[i]*(C[i]*z_min+D[i]);
	    b1_max += A[i]*(C[i]*z_max+D[i]);
	    b2_min += B[i]*(C[i]*z_min+D[i]);
	    b2_max += B[i]*(C[i]*z_max+D[i]);
	}

	x_min = (a22*b1_min - a12*b2_min) / (a12*a12 - a11*a22);
    y_min = (a11*b2_min - a12*b1_min) / (a12*a12 - a11*a22);

    x_max = (a22*b1_max - a12*b2_max) / (a12*a12 - a11*a22);
    y_max = (a11*b2_max - a12*b1_max) / (a12*a12 - a11*a22);

    znam_line = sqrt ((x_max - x_min)*(x_max - x_min) + (y_max - y_min)*(y_max - y_min) + (z_max - z_min)*(z_max - z_min) );
    x_line = (x_max - x_min) / znam_line;
    y_line = (y_max - y_min) / znam_line;
    z_line = (z_max - z_min) / znam_line;

    f = fopen ("line_m_data.txt", "w");
    if (!f)
    {
        printf(">>>cant open file --> line_m_data.txt\n");
        return -2;
    }

    fprintf(f, "%lf %lf %lf\n%lf %lf %lf\n", x_line, y_line, z_line, x_max, y_max, z_max);

    // fprintf(f, "%lf %lf %lf\n%lf %lf %lf\n", x_min, y_min, z_min, x_max, y_max, z_max);

    // double p, q, r, zn;
    // p = x_max - x_min;
    // q = y_max - y_min;
    // r = z_max - z_min;
    // zn = sqrt (p*p + q*q + r*r);
    // p /= zn;
    // q /= zn;
    // r /= zn;
    // fprintf(f, "%lf %lf %lf\n%lf %lf %lf\n", p, q, r, x_min, y_min, z_min);

    fclose (f);

    f = fopen ("line2_m_data.txt", "w");
    if (!f)
    {
        printf(">>>cant open file --> line_m_data.txt\n");
        return -2;
    }

    fprintf(f, "%lf %lf %lf\n%lf %lf %lf\n", x_min, y_min, z_min, x_max, y_max, z_max);

    fclose (f);

    printf("\nTWO POINTS OF RESULT LINE:\n");
    system ("cat line2_m_data.txt");
    printf("\n");

    // splot [-5:5][-5:5][-8:-3] 'merged-cont000' with lines, 'merged-cont010' with lines, 'merged-cont020' with lines, 'merged-cont030' with lines, 'merged-cont040' with lines, 'merged-cont050' with lines, 'merged-cont060' with lines, 'merged-cont070' with lines, 'merged-cont080' with lines, 'merged-cont090' with lines, '../meth1/real/line_p_data.txt' with lines, '../meth1/real/line_m_data.txt' with lines  

    // splot [-5:5][-5:5][-8:-3] 'merged-plus-cont000.txt' with lines, 'merged-plus-cont010.txt' with lines, 'merged-plus-cont020.txt' with lines, 'merged-plus-cont030.txt' with lines, 'merged-plus-cont040.txt' with lines, 'merged-plus-cont050.txt' with lines, 'merged-plus-cont060.txt' with lines, 'merged-plus-cont070.txt' with lines, 'merged-plus-cont080.txt' with lines, 'merged-plus-cont090.txt' with lines, '../meth1/real/line_p_data.txt' with lines lt 8 lw 5

    // splot 'merged-minus-cont000.txt' with lines, 'merged-minus-cont010.txt' with lines, 'merged-minus-cont020.txt' with lines, 'merged-minus-cont030.txt' with lines, 'merged-minus-cont040.txt' with lines, 'merged-minus-cont050.txt' with lines, 'merged-minus-cont060.txt' with lines, 'merged-minus-cont070.txt' with lines, 'merged-minus-cont080.txt' with lines, 'merged-minus-cont090.txt' with lines, '../meth1/real/line_m_data.txt' with lines

    // splot 'merged-cont000' with lines, 'merged-cont010' with lines, 'merged-cont020' with lines, 'merged-cont030' with lines, 'merged-cont040' with lines, 'merged-cont050' with lines, 'merged-cont060' with lines, 'merged-cont070' with lines, 'merged-cont080' with lines, 'merged-cont090' with lines, '../meth1/real/line_p_data.txt' with lines lt 8 lw 5, '../meth1/real/line_m_data.txt' with lines lt 8 lw 5

	for (j = 0; j < count; j++)
	{
		delete [] ppoints[j];
		delete [] mpoints[j];
	}
	delete [] A;
	delete [] B;
	delete [] C;
	delete [] D;
	delete [] znam;

	return 1;
}