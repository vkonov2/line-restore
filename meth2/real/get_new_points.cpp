#include <iostream>
#include <string>
#include <cmath>

#include "functions.h"
#include "point.h"
using namespace std;

int get_new_points (Point** points, int* n, const int count, int flag)
{
	int i, j, k, r;
	int n_new;
	int flagg, zero_beg, zero_fin, zero0_beg, zero0_fin, zero1_beg, zero1_fin;

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

        for (j = 1; j < n[i]; j++)
        {
            mem_points[i][j-1].x = points[i][j].x;
            mem_points[i][j-1].y = points[i][j].y;
            mem_points[i][j-1].z = points[i][j].z;
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
        n_mem[i] = n[i]-1;

    if (flag == 2)
    {
    	for (j = 0; j < n_mem[0]; j++)
	    {
	    	if (j % 2 == 0)
	    		mem_points[0][j].x = 0.000001212;
	    	else 
	    		mem_points[0][j].x = 0.000010102;
	    }

	    for (j = 0; j < n_mem[18]; j++)
	    {
	    	if (j % 2 == 0)
	    		mem_points[18][j].x += 0.000001210101;
	    	else 
	    		mem_points[18][j].x -= 0.000010001201;
	    }
    }
    if (flag == 3)
    {
    	for (j = 0; j < n_mem[0]; j++)
	    {
	    	if (j % 2 == 0)
	    		mem_points[0][j].x = 0.0001000011212;
	    	else 
	    		mem_points[0][j].x = 0.00001000011212;
	    }
    }

    // k = 0;
    // for (j = 0; j < n_mem[k]; j++)
    // 	printf("%lf %lf %lf\n", mem_points[k][j].x, mem_points[k][j].y, mem_points[k][j].z);

    // char strr[] = "line_p_data18.txt";
    // line_solve (mem_points[k], n_mem[k], 1, strr);
    // system ("cat line_p_data18.txt");
    // exit (1);

    char pwd[100];
    char str[100];
    char num0[10];
    char num[10];

    FILE* f;
    double x_minn, y_minn, z_minn, x_maxx, y_maxx, z_maxx;
    double mm, nn, pp, x0, y0, z0, tt, znam;

	for (i = 0; i < count; i++)
	{
		memset (num, 0, 10);
        memset (num0, 0, 10);
        memset (str, 0, 100);
        memset (pwd, 0, 100);

        if (flag == 2)
        	strcpy (str, "line_p_data");
        else if (flag == 3)
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

        // printf("%d:\n", i);

		line_solve (mem_points[i], n_mem[i], 1, str);

		f = fopen (str, "r");
		if (!f)
		{
			printf(">>>cant open file --> %s\n", str);
			for (i = 0; i < count; i++)
        		delete [] mem_points[i];
        	delete [] n_mem;
			return -2;
		}

		if (fscanf (f, "%lf %lf %lf %lf %lf %lf", &x_minn, &y_minn, &z_minn, &x_maxx, &y_maxx, &z_maxx) != 6)
		{
			printf(">>>cant read file --> %s\n", str);
			for (i = 0; i < count; i++)
        		delete [] mem_points[i];
        	delete [] n_mem;
        	fclose (f);
			return -3;
		}

		fclose (f);

		mm = x_maxx - x_minn;
		nn = y_maxx - y_minn;
		pp = z_maxx - z_minn;

		znam = sqrt (mm*mm + nn*nn + pp*pp);

		mm /= znam;
		nn /= znam;
		pp /= znam;

		for (j = 0; j < i; j++)
		{
			n_new = n[i];
			for (k = 0; k < n_mem[j]; k++)
			{
				points[i][n_new].z = mem_points[j][k].z;

				tt = (points[i][n_new].z - z_minn) / pp;
				points[i][n_new].x = mm * tt + x_minn;
				points[i][n_new].y = nn * tt + y_minn;
				
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

				tt = (points[i][n_new].z - z_minn) / pp;
				points[i][n_new].x = mm * tt + x_minn;
				points[i][n_new].y = nn * tt + y_minn;

				n_new++;
			}
			n[i] = n_new;
		}
	}

	// for (i = 0; i < count; i++)
	// {
	// 	memset (num, 0, 10);
 //        memset (num0, 0, 10);
 //        memset (str, 0, 100);
 //        memset (pwd, 0, 100);

 //        if (flag == 2)
 //        	strcpy (str, "line_p_data");
 //        else if (flag == 3)
 //        	strcpy (str, "line_m_data");

 //        if (i < 10)
 //        {   
 //            strcpy (num, "0");
 //            sprintf (num0, "%d", i);
 //            strcat (num, num0);
 //        }
 //        else
 //            sprintf (num, "%d", i);

 //        strcat (str, num);

 //        strcat (str, ".txt");

 //        strcpy (pwd, "cat ");

 //        strcat (pwd, str);

 //        printf("%d: \n", i);
 //        system (pwd);

 //        // if (i == 0)
 //        // {
 //        // 	printf("%d: \n", i);
 //        // 	system (pwd);
 //        // }
 //    }

	// printf("\n\n");

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

	// for (i = 0; i < count; i++)
	// {
	// 	j = 0;
	// 	while (j < n[i]-1)
	// 	{
	// 		// printf("\nbegin of %d step\n", j);

	// 		if ((fabs(points[i][j].x) < 1e-14)&&(fabs(points[i][j].y) < 1e-14))
	// 		{
	// 			zero0_beg = j;

	// 			// printf("step1\n");
 //            	// printf("zero0_beg = %d\n", zero0_beg);

	// 			for (k = j+1; k < n[i]; k++)
	// 			{
	// 				if (!((fabs(points[i][k].x) < 1e-14)&&(fabs(points[i][k].y) < 1e-14)))
	// 				{
	// 					zero0_fin = k;
	// 					break;
	// 				}
	// 			}

	// 			// printf("step2\n");
 //            	// printf("zero0_fin = %d\n", zero0_fin);

	// 			zero1_beg = zero0_fin + 1;

	// 			// printf("zero1_beg = %d\n", zero1_beg);

	// 			for (k = zero1_beg; k < n[i]; k++)
	// 			{
	// 				if (!((fabs(points[i][k].x) < 1e-14)&&(fabs(points[i][k].y) < 1e-14)))
	// 				{
	// 					zero1_fin = k;
	// 					break;
	// 				}
	// 			}

	// 			// printf("step3\n");
 //            	// printf("zero1_fin = %d\n", zero1_fin);

	// 			//point[i][zero0_fin]
	// 			//point[i][zero1_fin]

	// 			m = points[i][zero1_fin].x - points[i][zero0_fin].x;
	// 			l = points[i][zero1_fin].y - points[i][zero0_fin].y;
	// 			p = points[i][zero1_fin].z - points[i][zero0_fin].z;

	// 			// printf("m = %lf\n", m);
	//    			// printf("l = %lf\n", l);
	//    			// printf("p = %lf\n", p);

	// 			t = (points[i][j].z - points[i][zero0_fin].z) / p;

	// 			// printf("t = %lf\n", t);

	// 			points[i][j].x = m * t + points[i][zero0_fin].x;
	// 			points[i][j].y = l * t + points[i][zero0_fin].y;

	// 			// printf("%lf %lf %lf\n", points[i][j].x, points[i][j].y, points[i][j].z);
	// 		}

	// 		j++;
	// 	}
	// }

	// k = 0;
	// for (j = 0; j < 300; j++)
	// 	printf("%lf %lf %lf\n", points[k][j].x, points[k][j].y, points[k][j].z);

	// printf("\n\n");

	for (int i = 0; i < count; ++i)
		delete [] mem_points[i];

	delete [] n_mem;

	return n[0];
}