#include <iostream>
#include <string>
#include <cmath>

#include "functions.h"
#include "point.h"
using namespace std;

int fprint (Point** points, int* n, const int count, int flag)
{
	int i, j, k;

    char str[100];
    char num0[10];
    char num[10];

    FILE* f;

    for (i = 0; i < count; i++)
    {
        memset (num, 0, 10);
        memset (num0, 0, 10);
        memset (str, 0, 100);

        if (flag == 0)
        	strcpy (str, "../../shadow/merged-plus-cont0");
        else
        	strcpy (str, "../../shadow/merged-minus-cont0");

        if (i < 10)
        {   
            strcpy (num, "0");
            sprintf (num0, "%d", i);
            strcat (num, num0);
        }
        else
            sprintf (num, "%d", i);

        strcat (str, num);
        strcat (str, ".txt");

        f = fopen(str, "w");
        if (!f)
        {
        	printf(">>>cant open file --> %s\n", str);
            return -2;
        }
        
        for (j = 0; j < n[i]; j++)
        	fprintf(f, "%lf %lf %lf\n", points[i][j].x, points[i][j].y, points[i][j].z);

        fclose(f);
    }

    double z_min, z_max;
    z_min = -6.08332812434530;
    z_max = -4.57712089734895;

    if (flag == 0)
        f = fopen ("line_p_data.txt", "r");
    else
        f = fopen ("line_m_data.txt", "r");
    if (!f)
    {
        printf(">>>cant open file --> line_data\n");
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

    if (flag == 0)
        f = fopen ("line_p_points_data.txt", "w");
    else
        f = fopen ("line_m_points_data.txt", "w");
    if (!f)
    {
        printf(">>>cant open file --> line_points_data\n");
        return -2;
    }

    double t_0, t_1, x_0, x_1, y_0, y_1;

    t_0 = (z_min - z0)/r;
    t_1 = (z_max - z0)/r;

    x_0 = p * t_0 + x0;
    x_1 = p * t_1 + x0;

    y_0 = q * t_0 + y0;
    y_1 = q * t_1 + y0;

    fprintf(f, "%lf %lf %lf\n %lf %lf %lf", x_0, y_0, z_min, x_1, y_1, z_max);

    // splot [-5:5][-5:5][-8:-3] 'merged-cont000' with lines, 'merged-cont010' with lines, 'merged-cont020' with lines, 'merged-cont030' with lines, 'merged-cont040' with lines, 'merged-cont050' with lines, 'merged-cont060' with lines, 'merged-cont070' with lines, 'merged-cont080' with lines, 'merged-cont090' with lines, '../meth2/real/line_p_points_data.txt' with lines, '../meth2/real/line_m_points_data.txt' with lines  

    fclose (f);

	return 1;
}