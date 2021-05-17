#include <iostream>
#include <string>
#include <cmath>

#include "test_functions.h"
#include "point.h"
using namespace std;

int main (void)
{
    int i, j, k, r;
    int num, len;

    int flag, zero_beg, zero_fin, zero0_beg, zero0_fin, zero1_beg, zero1_fin;

    double m, l, p, t;

    Point* test_points = new Point[100000];
    if (!test_points)
    {
        printf(">>>allocation error --> test_points\n");
        return -1;
    }

    for (r = 0; r < 100000; r++)
    {
        test_points[r].x = 0;
        test_points[r].y = 0;
        test_points[r].z = 0;
    }

    double* arr = new double[100000];
    if (!arr)
    {
        printf(">>>allocation error --> arr\n");
        delete [] test_points;
        return -1;
    }

    for (i = 0; i < 100000; i++)
        arr[i] = 0;

    FILE* f;
    f = fopen ("test_data.txt", "r");
    if (!f)
    {
        printf("cant open file --> test_data.txt\n");
        delete [] test_points;
        delete [] arr;
        return -2;
    }  

    num = 0;
    while (!feof(f))
    {
        if (fscanf (f, "%lf", &arr[num]) != 1)
            break;
        num++;
    }

    len = (int)(num / 3.0);

    for (i = 0; i < len; i++)
    {
        test_points[i].x = arr[3*i];
        test_points[i].y = arr[3*i+1];
        test_points[i].z = arr[3*i+2];
    }

    fclose (f);

    //printf("len = %d\n", len);

    j = 0;
    while (j < len-1)
    {
        //printf("\nbegin of %d step\n", j);

        if ((fabs(test_points[j].x) < 1e-14)&&(fabs(test_points[j].y) < 1e-14))
        {
            zero0_beg = j;

            // printf("step1\n");
            // printf("zero0_beg = %d\n", zero0_beg);

            for (k = j+1; k < len; k++)
            {
                if (!((fabs(test_points[k].x) < 1e-14)&&(fabs(test_points[k].y) < 1e-14)))
                {
                    zero0_fin = k;
                    break;
                }
            }

            // printf("step2\n");
            // printf("zero0_fin = %d\n", zero0_fin);

            zero1_beg = zero0_fin + 1;

            //printf("zero1_beg = %d\n", zero1_beg);

            for (k = zero1_beg; k < len; k++)
            {
                if (!((fabs(test_points[k].x) < 1e-14)&&(fabs(test_points[k].y) < 1e-14)))
                {
                    zero1_fin = k;
                    break;
                }
            }

            // printf("step3\n");
            // printf("zero1_fin = %d\n", zero1_fin);

            //point[i][zero0_fin]
            //point[i][zero1_fin]

            m = test_points[zero1_fin].x - test_points[zero0_fin].x;
            l = test_points[zero1_fin].y - test_points[zero0_fin].y;
            p = test_points[zero1_fin].z - test_points[zero0_fin].z;

            // printf("m = %lf\n", m);
            // printf("l = %lf\n", l);
            // printf("p = %lf\n", p);

            t = (test_points[j].z - test_points[zero0_fin].z) / p;

            //printf("t = %lf\n", t);

            test_points[j].x = m * t + test_points[zero0_fin].x;
            test_points[j].y = l * t + test_points[zero0_fin].y;

            // printf("%lf %lf %lf\n", test_points[j].x, test_points[j].y, test_points[j].z);
        }

        j++;

        //printf("\nend of %d step\n", j);
    }

    for (i = 0; i < 500; i++)
        printf("%lf %lf %lf\n", test_points[i].x, test_points[i].y, test_points[i].z);

    delete [] test_points;
    delete [] arr;

    return 0;
}



