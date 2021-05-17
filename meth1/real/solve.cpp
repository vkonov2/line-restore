#include <iostream>
#include <string>
#include <cmath>

#include "functions.h"
#include "point.h"
using namespace std;

int solve (Point** points, Point* vecs, int* n, const int count)
{
    int i, j, k, flag;
    int nump, numm;

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

    for (i = 0; i < count; i++)
    {
        for (j = 1; j < n_plus[i]; j++)
        {
            ppoints[i][j-1].x = ppoints[i][j].x;
            ppoints[i][j-1].y = ppoints[i][j].y;
            ppoints[i][j-1].z = ppoints[i][j].z;
        }
    }

    for (j = 0; j < n_plus[0]; j++)
    {
        if (j%2 == 0)
            ppoints[0][j].x = 0.00000011212;
        else
            ppoints[0][j].x = 0.0001000021212;
    }

    for (j = 0; j < n_minus[0]; j++)
    {
        if (j%2 == 0)
            mpoints[0][j].x = 0.0000020011212;
        else
            mpoints[0][j].x = 0.00000010021212;
    }

    // k = 0;
    // for (j = 0; j < n_plus[k]; j++)
    //     printf("(%lf, %lf, %lf)\n", ppoints[k][j].x, ppoints[k][j].y, ppoints[k][j].z);

    // FILE* f = fopen ("ppoint_test.txt", "w");
    // if (!f)
    // {
    //     printf(">>>cant open file --> ppoint_test.txt\n");
    //     return -1;
    // }  

    // k = 0;
    // for (j = 0; j < n_plus[k]; j++)
    //     fprintf(f, "%lf %lf %lf\n", ppoints[k][j].x, ppoints[k][j].y, ppoints[k][j].z);

    // k = 20;
    // for (j = 0; j < n_plus[k]; j++)
    //     fprintf(f, "%lf %lf %lf\n", ppoints[k][j].x, ppoints[k][j].y, ppoints[k][j].z);

    // k = 40;
    // for (j = 0; j < n_plus[k]; j++)
    //     fprintf(f, "%lf %lf %lf\n", ppoints[k][j].x, ppoints[k][j].y, ppoints[k][j].z);

    // k = 60;
    // for (j = 0; j < n_plus[k]; j++)
    //     fprintf(f, "%lf %lf %lf\n", ppoints[k][j].x, ppoints[k][j].y, ppoints[k][j].z);

    // k = 80;
    // for (j = 0; j < n_plus[k]; j++)
    //     fprintf(f, "%lf %lf %lf\n", ppoints[k][j].x, ppoints[k][j].y, ppoints[k][j].z);

    // k = 99;
    // for (j = 0; j < n_plus[k]; j++)
    //     fprintf(f, "%lf %lf %lf\n", ppoints[k][j].x, ppoints[k][j].y, ppoints[k][j].z);

    // fclose (f);

    // splot '../meth1/real/ppoint_test.txt' with lines

    // printf("\n");

    // k = 0;
    // for (j = 0; j < n_minus[k]; j++)
    //     printf("%lf %lf %lf\n", mpoints[k][j].x, mpoints[k][j].y, mpoints[k][j].z);
    // printf("\n");

    char pwd[100];
    char str[100];
    char num0[10];
    char num[10];

    for (i = 0; i < count; i++)
    {
        memset (num, 0, 10);
        memset (num0, 0, 10);
        memset (str, 0, 100);
        memset (pwd, 0, 100);

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

        // printf("%d:\n", i);
        
        line_solve (ppoints[i], n_plus[i], str);

        strcpy (pwd, "cat ");

        strcat (pwd, str);

        // system (pwd);

        // if (i == 0)
        // {
        //     printf("%d:\n", i);
        //     system (pwd);
        // }
    }

    //printf("\n");

    for (i = 0; i < count; i++)
    {
        memset (num, 0, 10);
        memset (num0, 0, 10);
        memset (str, 0, 100);
        memset (pwd, 0, 100);

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

        line_solve (mpoints[i], n_minus[i], str);

        strcpy (pwd, "cat ");

        strcat (pwd, str);

        // printf("%d:\n", i);
        // system (pwd);

        // if (i == 0)
        // {
        //     printf("%d:\n", i);
        //     system (pwd);
        // }
    }

    //printf("\n");

    FILE* f1;
    FILE* f2;
    FILE* f3;

    double m1, n1, p1, x1, y1, z1;
    double m2, n2, p2, x2, y2, z2;
    double m3, n3, p3, x3, y3, z3;
    double val1, val2, val3, val4, val5, val6;

    f1 = fopen ("line_p_data66.txt", "r");
    if (!f1)
    {
        printf(">>>cant open file --> line_p_data66\n");
        for (i = 0; i < count; i++)
        {
            delete [] ppoints[i];
            delete [] mpoints[i];
        }
        delete [] n_plus;
        delete [] n_minus;
        return -2;
    }

    if (fscanf (f1, "%lf %lf %lf %lf %lf %lf", &val1, &val2, &val3, &val4, &val5, &val6) != 6)
    {
        printf(">>>cant read file --> line_p_data66\n");
        for (i = 0; i < count; i++)
        {
            delete [] ppoints[i];
            delete [] mpoints[i];
        }
        delete [] n_plus;
        delete [] n_minus;
        return -1;
    }

    m1 = val1; n1 = val2; p1 = val3;
    x1 = val4; y1 = val5; z1 = val6;

    fclose (f1);
    
    f3 = fopen ("line_p_data68.txt", "r");
    if (!f3)
    {
        printf(">>>cant open file --> line_p_data66\n");
        for (i = 0; i < count; i++)
        {
            delete [] ppoints[i];
            delete [] mpoints[i];
        }
        delete [] n_plus;
        delete [] n_minus;
        return -2;
    }

    if (fscanf (f3, "%lf %lf %lf %lf %lf %lf", &val1, &val2, &val3, &val4, &val5, &val6) != 6)
    {
        printf(">>>cant read file --> line_p_data68\n");
        for (i = 0; i < count; i++)
        {
            delete [] ppoints[i];
            delete [] mpoints[i];
        }
        delete [] n_plus;
        delete [] n_minus;
        return -1;
    }

    m3 = val1; n3 = val2; p3 = val3;
    x3 = val4; y3 = val5; z3 = val6;

    fclose (f3);

    f2 = fopen ("line_p_data67.txt", "w");
    if (!f2)
    {
        printf(">>>cant open file --> line_p_data66\n");
        for (i = 0; i < count; i++)
        {
            delete [] ppoints[i];
            delete [] mpoints[i];
        }
        delete [] n_plus;
        delete [] n_minus;
        return -2;
    }

    //fprintf(f2, "# X Y Z\n");

    m2 = (m1+m3)/2; n2 = (n1+n3)/2; p2 = (p1+p3)/2;
    x2 = (x1+x3)/2; y2 = (y1+y3)/2; z2 = (z1+z3)/2;

    fprintf(f2, "%lf %lf %lf\n%lf %lf %lf\n", m2, n2, p2, x2, y2, z2);

    fclose (f2);

    f1 = fopen ("line_p_data82.txt", "r");
    if (!f1)
    {
        printf(">>>cant open file --> line_p_data82\n");
        for (i = 0; i < count; i++)
        {
            delete [] ppoints[i];
            delete [] mpoints[i];
        }
        delete [] n_plus;
        delete [] n_minus;
        return -2;
    }

    if (fscanf (f1, "%lf %lf %lf %lf %lf %lf", &val1, &val2, &val3, &val4, &val5, &val6) != 6)
    {
        printf(">>>cant read file --> line_p_data82\n");
        for (i = 0; i < count; i++)
        {
            delete [] ppoints[i];
            delete [] mpoints[i];
        }
        delete [] n_plus;
        delete [] n_minus;
        return -1;
    }

    m1 = val1; n1 = val2; p1 = val3;
    x1 = val4; y1 = val5; z1 = val6;

    fclose (f1);
    
    f3 = fopen ("line_p_data84.txt", "r");
    if (!f3)
    {
        printf(">>>cant open file --> line_p_data84\n");
        for (i = 0; i < count; i++)
        {
            delete [] ppoints[i];
            delete [] mpoints[i];
        }
        delete [] n_plus;
        delete [] n_minus;
        return -2;
    }

    if (fscanf (f3, "%lf %lf %lf %lf %lf %lf", &val1, &val2, &val3, &val4, &val5, &val6) != 6)
    {
        printf(">>>cant read file --> line_p_data84\n");
        for (i = 0; i < count; i++)
        {
            delete [] ppoints[i];
            delete [] mpoints[i];
        }
        delete [] n_plus;
        delete [] n_minus;
        return -1;
    }

    m3 = val1; n3 = val2; p3 = val3;
    x3 = val4; y3 = val5; z3 = val6;

    fclose (f3);

    f2 = fopen ("line_p_data83.txt", "w");
    if (!f2)
    {
        printf(">>>cant open file --> line_p_data83\n");
        for (i = 0; i < count; i++)
        {
            delete [] ppoints[i];
            delete [] mpoints[i];
        }
        delete [] n_plus;
        delete [] n_minus;
        return -2;
    }

    //fprintf(f2, "# X Y Z\n");

    m2 = (m1+m3)/2; n2 = (n1+n3)/2; p2 = (p1+p3)/2;
    x2 = (x1+x3)/2; y2 = (y1+y3)/2; z2 = (z1+z3)/2;

    fprintf(f2, "%lf %lf %lf\n%lf %lf %lf\n", m2, n2, p2, x2, y2, z2);

    fclose (f2);

    // for (i = 0; i < count; i++)
    // {
    //     memset (num, 0, 10);
    //     memset (num0, 0, 10);
    //     memset (str, 0, 100);
    //     memset (pwd, 0, 100);

    //     strcpy (str, "line_p_data");

    //     if (i < 10)
    //     {   
    //         strcpy (num, "0");
    //         sprintf (num0, "%d", i);
    //         strcat (num, num0);
    //     }
    //     else
    //         sprintf (num, "%d", i);

    //     strcat (str, num);

    //     // printf("%s\n", str);

    //     strcat (str, ".txt");

    //     strcpy (pwd, "cat ");

    //     strcat (pwd, str);

    //     printf("%d:\n", i);
    //     system (pwd);
    // }

    // printf("\n");

    // for (i = 0; i < count; i++)
    // {
    //     memset (num, 0, 10);
    //     memset (num0, 0, 10);
    //     memset (str, 0, 100);
    //     memset (pwd, 0, 100);

    //     strcpy (str, "line_m_data");

    //     if (i < 10)
    //     {   
    //         strcpy (num, "0");
    //         sprintf (num0, "%d", i);
    //         strcat (num, num0);
    //     }
    //     else
    //         sprintf (num, "%d", i);

    //     strcat (str, num);

    //     // printf("%s\n", str);

    //     strcat (str, ".txt");

    //     strcpy (pwd, "cat ");

    //     strcat (pwd, str);
    //     printf("%d:\n", i);
    //     system (pwd);
    // }

    // printf("\n");

    // splot '../meth1/real/line_p_data00.txt' with lines, '../meth1/real/line_p_data10.txt' with lines, '../meth1/real/line_p_data20.txt' with lines, '../meth1/real/line_p_data30.txt' with lines, '../meth1/real/line_p_data40.txt' with lines, '../meth1/real/line_p_data50.txt' with lines, '../meth1/real/line_p_data60.txt' with lines, '../meth1/real/line_p_data70.txt' with lines, '../meth1/real/line_p_data80.txt' with lines, '../meth1/real/line_p_data90.txt' with lines, '../meth1/real/line_p_data.txt' with lines lt 7 lw 5

    // splot '../meth1/real/line_m_data00.txt' with lines, '../meth1/real/line_m_data10.txt' with lines, '../meth1/real/line_m_data20.txt' with lines, '../meth1/real/line_m_data30.txt' with lines, '../meth1/real/line_m_data40.txt' with lines, '../meth1/real/line_m_data50.txt' with lines, '../meth1/real/line_m_data60.txt' with lines, '../meth1/real/line_m_data70.txt' with lines, '../meth1/real/line_m_data80.txt' with lines, '../meth1/real/line_m_data90.txt' with lines, '../meth1/real/line_m_data.txt' with lines lt 7 lw 5

    // splot [-5:5][-5:5][-8:-3] '../meth1/real/line_p_data00.txt' with lines, '../meth1/real/line_p_data10.txt' with lines, '../meth1/real/line_p_data20.txt' with lines, '../meth1/real/line_p_data30.txt' with lines, '../meth1/real/line_p_data40.txt' with lines, '../meth1/real/line_p_data50.txt' with lines, '../meth1/real/line_p_data60.txt' with lines, '../meth1/real/line_p_data70.txt' with lines, '../meth1/real/line_p_data80.txt' with lines, '../meth1/real/line_p_data90.txt' with lines, '../meth1/real/line_m_data00.txt' with lines, '../meth1/real/line_m_data10.txt' with lines, '../meth1/real/line_m_data20.txt' with lines, '../meth1/real/line_m_data30.txt' with lines, '../meth1/real/line_m_data40.txt' with lines, '../meth1/real/line_m_data50.txt' with lines, '../meth1/real/line_m_data60.txt' with lines, '../meth1/real/line_m_data70.txt' with lines, '../meth1/real/line_m_data80.txt' with lines, '../meth1/real/line_m_data90.txt' with lines, '../meth1/real/line_p_data.txt' with lines lt 7 lw 5, '../meth1/real/line_m_data.txt' with lines lt 7 lw 5

    // splot [-5:5][-5:5][-8:-3] '../meth1/real/line_p_data00.txt' with lines lw 5, '../meth1/real/line_p_data10.txt' with lines lw 5, '../meth1/real/line_p_data20.txt' with lines lw 5, '../meth1/real/line_p_data30.txt' with lines lw 5, '../meth1/real/line_p_data40.txt' with lines lw 5, '../meth1/real/line_p_data50.txt' with lines lw 5, '../meth1/real/line_p_data60.txt' with lines lw 5, '../meth1/real/line_p_data70.txt' with lines lw 5, '../meth1/real/line_p_data80.txt' with lines lw 5, '../meth1/real/line_p_data90.txt' with lines lw 5, '../meth1/real/line_m_data00.txt' with lines lw 5, '../meth1/real/line_m_data10.txt' with lines lw 5, '../meth1/real/line_m_data20.txt' with lines lw 5, '../meth1/real/line_m_data30.txt' with lines lw 5, '../meth1/real/line_m_data40.txt' with lines lw 5, '../meth1/real/line_m_data50.txt' with lines lw 5, '../meth1/real/line_m_data60.txt' with lines lw 5, '../meth1/real/line_m_data70.txt' with lines lw 5, '../meth1/real/line_m_data80.txt' with lines lw 5, '../meth1/real/line_m_data90.txt' with lines lw 5, 'merged-cont000' with lines, 'merged-cont010' with lines, 'merged-cont020' with lines, 'merged-cont030' with lines, 'merged-cont040' with lines, 'merged-cont050' with lines, 'merged-cont060' with lines, 'merged-cont070' with lines, 'merged-cont080' with lines, 'merged-cont090' with lines

    // splot [-5:5][-5:5][-8:-3] '../meth1/real/line_p_data00.txt' lw 5, '../meth1/real/line_m_data00.txt' lw 5

    // splot [-5:5][-5:5][-8:-3] '../meth1/real/line_p_data00.txt' lw 5, '../meth1/real/line_p_data10.txt' lw 5, '../meth1/real/line_p_data20.txt' lw 5, '../meth1/real/line_p_data30.txt' lw 5, '../meth1/real/line_p_data40.txt' lw 5, '../meth1/real/line_p_data50.txt' lw 5, '../meth1/real/line_p_data60.txt' lw 5, '../meth1/real/line_p_data70.txt' lw 5, '../meth1/real/line_p_data80.txt' lw 5, '../meth1/real/line_p_data90.txt' lw 5, '../meth1/real/line_m_data00.txt' lw 5, '../meth1/real/line_m_data10.txt' lw 5, '../meth1/real/line_m_data20.txt' lw 5, '../meth1/real/line_m_data30.txt' lw 5, '../meth1/real/line_m_data40.txt' lw 5, '../meth1/real/line_m_data50.txt' lw 5, '../meth1/real/line_m_data60.txt' lw 5, '../meth1/real/line_m_data70.txt' lw 5, '../meth1/real/line_m_data80.txt' lw 5, '../meth1/real/line_m_data90.txt' lw 5

    // splot 'AllPolygonizedContours', 'merged-cont000' with lines lw 5, 'merged-cont010' with lines lw 5, 'merged-cont020' with lines lw 5, 'merged-cont030' with lines lw 5, 'merged-cont040' with lines lw 5, 'merged-cont050' with lines lw 5, 'merged-cont060' with lines lw 5, 'merged-cont070' with lines lw 5, 'merged-cont080' with lines lw 5, 'merged-cont090' with lines lw 5

    // splot 'poly0-000' with lines, '../shadow/merged-cont000' with lines , '../shadow/merged-cont010' with lines , '../shadow/merged-cont020' with lines , '../shadow/merged-cont030' with lines , '../shadow/merged-cont040' with lines , '../shadow/merged-cont050' with lines , '../shadow/merged-cont060' with lines , '../shadow/merged-cont070' with lines , '../shadow/merged-cont080' with lines , '../shadow/merged-cont090' with lines, '../meth1/real/line_p_data00.txt' lw 5 with lines, '../meth1/real/line_p_data10.txt' lw 5 with lines, '../meth1/real/line_p_data20.txt' lw 5 with lines, '../meth1/real/line_p_data30.txt' lw 5 with lines, '../meth1/real/line_p_data40.txt' lw 5 with lines, '../meth1/real/line_p_data50.txt' lw 5 with lines, '../meth1/real/line_p_data60.txt' lw 5 with lines, '../meth1/real/line_p_data70.txt' lw 5 with lines, '../meth1/real/line_p_data80.txt' lw 5 with lines, '../meth1/real/line_p_data90.txt' lw 5 with lines, '../meth1/real/line_m_data00.txt' lw 5 with lines, '../meth1/real/line_m_data10.txt' lw 5 with lines, '../meth1/real/line_m_data20.txt' lw 5 with lines, '../meth1/real/line_m_data30.txt' lw 5 with lines, '../meth1/real/line_m_data40.txt' lw 5 with lines, '../meth1/real/line_m_data50.txt' lw 5 with lines, '../meth1/real/line_m_data60.txt' lw 5 with lines, '../meth1/real/line_m_data70.txt' lw 5 with lines, '../meth1/real/line_m_data80.txt' lw 5 with lines, '../meth1/real/line_m_data90.txt' lw 5 with lines

    // splot 'poly0-000' with lines, '../shadow/merged-cont000' with lines , '../shadow/merged-cont010' with lines , '../shadow/merged-cont020' with lines , '../shadow/merged-cont030' with lines , '../shadow/merged-cont040' with lines , '../shadow/merged-cont050' with lines , '../shadow/merged-cont060' with lines , '../shadow/merged-cont070' with lines , '../shadow/merged-cont080' with lines , '../shadow/merged-cont090' with lines, '../meth1/real/line2_p_data.txt' lt 7 lw 5 with lines, '../meth1/real/line2_m_data.txt' lt 7 lw 5 with lines

    // printf("Data for positive set:\n");

    // printf("Data for negative set:\n");

    line_res (vecs, count);

    check (ppoints, vecs, n_plus, count, 0);

    check (mpoints, vecs, n_minus, count, 1);

    for (i = 0; i < count; i++)
    {
        delete [] ppoints[i];
        delete [] mpoints[i];
    }
    delete [] n_plus;
    delete [] n_minus;

    return 1;
}
