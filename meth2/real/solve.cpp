#include <iostream>
#include <string>
#include <cmath>

#include "functions.h"
#include "point.h"
using namespace std;

int solve (Point** points, Point* vecs, int* n, const int count)
{
    int i, j, k, flag;
    int nump, numm, nummp, nummm;

	int* n_plus = new int[count];
    if (!n_plus)
    {
        printf(">>>allocation error --> n\n");
        return -1;
    }

    for (i = 0; i < count; i++)
        n_plus[i] = 0;

    int* n_minus = new int[count];
    if (!n_minus)
    {
        printf(">>>allocation error --> n\n");
        return -1;
    }

    for (i = 0; i < count; i++)
        n_minus[i] = 0;

    for (i = 0; i < count; i++)
    {
        for (j = 0; j < n[i]; j++)
        {
            if (points[i][j].y > 0)
                n_plus[i]++;
        }
    }

    for (i = 0; i < count; i++)
        n_minus[i] = n[i] - n_plus[i];

    // for (i = 0; i < count; i++)
    //     printf("%d\n", n_plus[i]);

    Point* ppoints[count];
    Point* mpoints[count];

    for (i = 0; i < count; i++)
    {
        ppoints[i] = new Point[100000];

        if (!ppoints[i])
        {
            printf(">>>allocation error\n");
            delete [] n_plus;
            delete [] n_minus;
            return -3;
        }

        for (j = 0; j < 100000; ++j)
        {
            ppoints[i][j].x = 0;
            ppoints[i][j].y = 0;
            ppoints[i][j].z = 0;
        }

        for (j = 1; j < n_plus[i]; j++)
        {
            ppoints[i][j].x = points[i][j].x;
            ppoints[i][j].y = points[i][j].y;
            ppoints[i][j].z = points[i][j].z;
        }
    }

    for (i = 0; i < count; i++)
    {
        mpoints[i] = new Point[100000];
        if (!mpoints[i])
        {
            printf(">>>allocation error\n");
            delete [] n_plus;
            delete [] n_minus;
            for (j = 0; j < count; j++)
                delete [] ppoints[j];
            return -3;
        }

        for (j = 0; j < 100000; ++j)
        {
            mpoints[i][j].x = 0;
            mpoints[i][j].y = 0;
            mpoints[i][j].z = 0;
        }

        for (j = n_plus[i]; j < n[i]; j++)
        {
            mpoints[i][j-n_plus[i]].x = points[i][j].x;
            mpoints[i][j-n_plus[i]].y = points[i][j].y;
            mpoints[i][j-n_plus[i]].z = points[i][j].z;
        }
    }

    Point* mem_ppoints[count];

    for (i = 0; i < count; i++)
    {
        mem_ppoints[i] = new Point[20000];
        if (!mem_ppoints[i])
        {
            printf(">>>allocation error\n");
            delete [] n_plus;
            delete [] n_minus;
            for (j = 0; j < count; j++)
                delete [] ppoints[j];
            for (j = 0; j < count; j++)
                delete [] mpoints[j];
            return -3;
        }

        for (j = 0; j < n_plus[i]; j++)
        {
            mem_ppoints[i][j].x = ppoints[i][j].x;
            mem_ppoints[i][j].y = ppoints[i][j].y;
            mem_ppoints[i][j].z = ppoints[i][j].z;
        }
    }

    int* n_plus_mem = new int[count];
    if (!n_plus_mem)
    {
        printf(">>>allocation error --> n\n");
        delete [] n_plus;
        delete [] n_minus;
        for (j = 0; j < count; j++)
            delete [] ppoints[j];
        for (j = 0; j < count; j++)
            delete [] mpoints[j];
        for (j = 0; j < count; j++)
            delete [] mem_ppoints[j];
        return -1;
    }

    for (i = 0; i < count; i++)
        n_plus_mem[i] = n_plus[i];

    Point* mem_mpoints[count];

    for (i = 0; i < count; i++)
    {
        mem_mpoints[i] = new Point[20000];
        if (!mem_mpoints[i])
        {
            printf(">>>allocation error\n");
            delete [] n_plus;
            delete [] n_minus;
            for (j = 0; j < count; j++)
                delete [] ppoints[j];
            for (j = 0; j < count; j++)
                delete [] mpoints[j];
            for (j = 0; j < count; j++)
                delete [] mem_ppoints[j];
            delete [] n_plus_mem;
            return -3;
        }

        for (j = 0; j < n_minus[i]; j++)
        {
            mem_mpoints[i][j].x = mpoints[i][j].x;
            mem_mpoints[i][j].y = mpoints[i][j].y;
            mem_mpoints[i][j].z = mpoints[i][j].z;
        }
    }

    int* n_minus_mem = new int[count];
    if (!n_minus_mem)
    {
        printf(">>>allocation error --> n\n");
        delete [] n_plus;
        delete [] n_minus;
        for (j = 0; j < count; j++)
            delete [] ppoints[j];
        for (j = 0; j < count; j++)
            delete [] mpoints[j];
        for (j = 0; j < count; j++)
            delete [] mem_ppoints[j];
        for (j = 0; j < count; j++)
            delete [] mem_mpoints[j];
        delete [] n_plus_mem;
        return -1;
    }

    for (i = 0; i < count; i++)
        n_minus_mem[i] = n_minus[i];

    // for (i = 0; i < count; i++)
    //     printf("%d\n", n_plus_mem[i]);
    // printf("\n");
    // for (i = 0; i < count; i++)
    //     printf("%d\n", n_minus_mem[i]);

    // k = 0;
    // for (j = 0; j < 100; j++)
    //     printf("%lf %lf %lf\n", ppoints[k][j].x, ppoints[k][j].y, ppoints[k][j].z);

    nump = get_new_points (ppoints, n_plus, count, 2);

    numm = get_new_points (mpoints, n_minus, count, 3);

    for (i = 0; i < count; i++)
        n_plus[i]--;

    // k = 0;
    // for (i = 0; i < n[k]; i++)
    //     printf("%lf\n", points[k][i].z);

    k = 50;
    for (j = 0; j < n_plus[k]; j++)
        printf("%lf %lf %lf\n", ppoints[k][j].x, ppoints[k][j].y, ppoints[k][j].z);

    // printf("\n\n");

    // k = 0;
    // for (j = 0; j < n_plus[k]; j++)
    //     printf("%lf %lf %lf\n", ppoints[k][j].x, ppoints[k][j].y, ppoints[k][j].z);

    // printf("\n\n");

    // k = 0;
    // for (j = 0; j < n_minus[k]; j++)
    //     printf("%lf %lf %lf\n", mpoints[k][j].x, mpoints[k][j].y, mpoints[k][j].z);

    // printf("nump = %d\n", nump);
    // printf("numm = %d\n", numm);

    Point* midp_points = new Point[nump];
    if (!midp_points)
    {
        printf(">>>allocation error\n");
        delete [] n_plus;
        delete [] n_minus;
        for (j = 0; j < count; j++)
            delete [] ppoints[j];
        for (j = 0; j < count; j++)
            delete [] mpoints[j];
        for (j = 0; j < count; j++)
            delete [] mem_ppoints[j];
        for (j = 0; j < count; j++)
            delete [] mem_mpoints[j];
        delete [] n_plus_mem;
        delete [] n_minus_mem;
        return -3;
    }

    for (j = 0; j < nump; j++)
    {
        midp_points[j].x = 0;
        midp_points[j].y = 0;
        midp_points[j].z = 0;
    }

    Point* midm_points = new Point[numm];
    if (!midm_points)
    {
        printf(">>>allocation error\n");
        delete [] midp_points;
        delete [] n_plus;
        delete [] n_minus;
        for (j = 0; j < count; j++)
            delete [] ppoints[j];
        for (j = 0; j < count; j++)
            delete [] mpoints[j];
        for (j = 0; j < count; j++)
            delete [] mem_ppoints[j];
        for (j = 0; j < count; j++)
            delete [] mem_mpoints[j];
        delete [] n_plus_mem;
        delete [] n_minus_mem;
        return -3;
    }

    for (j = 0; j < numm; j++)
    {
        midm_points[j].x = 0;
        midm_points[j].y = 0;
        midm_points[j].z = 0;
    }

    // printf("\n%lf\n\n", ppoints[0][18000].x);

    // for (i = 0; i < count; i++)
    // {
    //     // printf("step %d:\n", i);
    //     flag = 0;
    //     for (j = 0; j < nump; j++)
    //     {   
    //         // printf("\t%d\n", j);
    //         if (isnan (ppoints[i][j].x) != 0)
    //         {
    //             nummp = j;
    //             flag = 1;
    //             break;
    //         }
    //     }
    //     if (flag == 1)
    //         break;
    // }

    // for (i = 0; i < count; i++)
    // {
    //     flag = 0;
    //     for (j = 0; j < numm; j++)
    //     {   
    //         if (isnan (mpoints[i][j].x) != 0)
    //         {
    //             nummm = j;
    //             flag = 1;
    //             break;
    //         }
    //     }
    //     if (flag == 1)
    //         break;
    // }

    // for (i = 0; i < count; i++)
    // {
    //     // printf("step %d:\n", i);
    //     flag = 0;
    //     for (j = 0; j < nump; j++)
    //     {   
    //         // printf("\t%d\n", j);
    //         if ((fabs (ppoints[i][j].x) < 1e-14)&&(fabs (ppoints[i][j].y) < 1e-14))
    //         {
    //             nummp = j;
    //             flag = 1;
    //             break;
    //         }
    //     }
    //     if (flag == 1)
    //         break;
    // }

    // for (i = 0; i < count; i++)
    // {
    //     // printf("step %d:\n", i);
    //     flag = 0;
    //     for (j = 0; j < numm; j++)
    //     {   
    //         // printf("\t%d\n", j);
    //         if ((fabs (mpoints[i][j].x) < 1e-14)&&(fabs (mpoints[i][j].y) < 1e-14))
    //         {
    //             nummm = j;
    //             flag = 1;
    //             break;
    //         }
    //     }
    //     if (flag == 1)
    //         break;
    // }

    // printf("\n%lf %lf %lf\n", ppoints[0][18123].x, ppoints[0][18123].y, ppoints[0][18123].z);
    // printf("\n%lf %lf %lf\n", ppoints[0][18124].x, ppoints[0][18124].y, ppoints[0][18124].z);

    // printf("\n%lf %lf %lf\n", mpoints[0][17995].x, mpoints[0][17995].y, mpoints[0][17995].z);
    // printf("\n%lf %lf %lf\n", mpoints[0][17996].x, mpoints[0][17996].y, mpoints[0][17996].z);

    // printf("nump = %d\n", nump);
    // printf("nummp = %d\n", nummp);
    // printf("numm = %d\n", numm);
    // printf("nummm = %d\n", nummm);

    printf("Data for positive set:\n");

    triangle (midp_points, ppoints, vecs, nump, count, 0);

    check (mem_ppoints, vecs, n_plus_mem, count, 0);

    printf("Data for negative set:\n");

    triangle (midm_points, mpoints, vecs, numm, count, -2);

    check (mem_mpoints, vecs, n_minus_mem, count, 1);

    // fprint (mem_ppoints, n_plus_mem, count, 0);

    // fprint (mem_mpoints, n_minus_mem, count, 1);

    // splot 'poly0-000' with lines, '../meth2/real/line2_p_data.txt' with lines lw 5 lt 7, '../shadow/merged-cont000' with lines, '../shadow/merged-cont010' with lines, '../shadow/merged-cont020' with lines, '../shadow/merged-cont030' with lines, '../shadow/merged-cont040' with lines, '../shadow/merged-cont050' with lines, '../shadow/merged-cont060' with lines, '../shadow/merged-cont070' with lines, '../shadow/merged-cont080' with lines, '../shadow/merged-cont090' with lines 

    for (i = 0; i < count; i++)
    {
        delete [] ppoints[i];
        delete [] mpoints[i];
    }
    delete [] n_plus;
    delete [] n_minus;

    for (j = 0; j < count; j++)
        delete [] mem_ppoints[j];
    for (j = 0; j < count; j++)
        delete [] mem_mpoints[j];
    
    delete [] n_plus_mem;
    delete [] n_minus_mem;

    delete [] midp_points;
    delete [] midm_points;

    return 1;
}
