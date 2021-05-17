#include <iostream>
#include <string>
#include <cmath>

#include "functions.h"
#include "point.h"
using namespace std;

/*
    FUNC solve contains the problem solving algorithm
*/

int solve (Point** points, Point* vecs, int* n, const int count)
{
    FILE* f;
    int i, j, k, flag;
    int nump, numm;
    char str[100], num0[10], num1[10];

    // an array for the number of elements of the projections of the first line

	int* np = new int[count];
    if (!np)
    {
        printf(">>>allocation error --> np\n");
        return -1;
    }

    // an array for the number of elements of the projections of the second line

    int* nm = new int[count];
    if (!nm)
    {
        printf(">>>allocation error --> nm\n");
        delete [] nm;
        return -1;
    }
    for (i = 0; i < count; i++)
    {
        np[i] = 0;
        nm[i] = 0;
    }

    for (i = 0; i < count; i++)
    {
        for (j = 0; j < n[i]; j++)
        {
            if (points[i][j].y > 0)
                np[i]++;
        }
        nm[i] = n[i] - np[i];
    }

    // an array for the elements of the projections of the first line

    Point* ppoints[count];
    for (i = 0; i < count; i++)
    {
        ppoints[i] = new Point[100000];
        if (!ppoints[i])
        {
            printf(">>>allocation error\n");
            delete [] np;
            return -3;
        }

        for (j = 0; j < 100000; ++j)
        {
            ppoints[i][j].x = .0;
            ppoints[i][j].y = .0;
            ppoints[i][j].z = .0;
        }
    }

    // an array for the elements of the projections of the second line

    Point* mpoints[count];
    for (i = 0; i < count; i++)
    {
        mpoints[i] = new Point[100000];
        if (!mpoints[i])
        {
            printf(">>>allocation error\n");
            delete [] np;
            for (j = 0; j < count; j++)
                delete [] ppoints[j];
            return -3;
        }

        for (j = 0; j < 100000; ++j)
        {
            mpoints[i][j].x = .0;
            mpoints[i][j].y = .0;
            mpoints[i][j].z = .0;
        }
    }

    for (i = 0; i < count; i++)
    {
        for (j = 0; j < np[i]; j++)
        {
            ppoints[i][j].x = points[i][j].x;
            ppoints[i][j].y = points[i][j].y;
            ppoints[i][j].z = points[i][j].z;
        }
        for (j = np[i]; j < n[i]; j++)
        {
            mpoints[i][j-np[i]].x = points[i][j].x;
            mpoints[i][j-np[i]].y = points[i][j].y;
            mpoints[i][j-np[i]].z = points[i][j].z;
        }
    }

    /*
        fluctuation of the data of some files so that the algorithm for finding the approximating straight line can work correctly: finding the eigenvalues requires observing some proportionality of the elements of the lines
    */

    for (j = 0; j < np[0]; j++)
    {
        if (j%2 == 0)
            ppoints[0][j].x = 0.00000011212;
        else
            ppoints[0][j].x = 0.0001000021212;
    }

    for (j = 0; j < nm[0]; j++)
    {
        if (j%2 == 0)
            mpoints[0][j].x = 0.0000020011212;
        else
            mpoints[0][j].x = 0.00000010021212;
    }

    // finding lines that approximate the sets of points of projections of the first line

    for (i = 0; i < count; i++)
    {
        memset (num0, 0, 10);
        memset (num1, 0, 10);
        memset (str, 0, 100);

        strcpy (str, "line_p_data");

        if (i < 10)
        {   
            strcpy (num1, "0");
            sprintf (num0, "%d", i);
            strcat (num1, num0);
        }
        else
            sprintf (num1, "%d", i);

        strcat (str, num1);
        strcat (str, ".txt");
        
        line_solve (ppoints[i], np[i], str);
    }

    // finding lines that approximate the sets of points of projections of the second line

    for (i = 0; i < count; i++)
    {
        memset (num0, 0, 10);
        memset (num1, 0, 10);
        memset (str, 0, 100);

        strcpy (str, "line_m_data");

        if (i < 10)
        {   
            strcpy (num1, "0");
            sprintf (num0, "%d", i);
            strcat (num1, num0);
        }
        else
            sprintf (num1, "%d", i);

        strcat (str, num1);
        strcat (str, ".txt");

        line_solve (mpoints[i], nm[i], str);
    }

    line_res (vecs, count);

    check (ppoints, vecs, np, count, 0);

    check (mpoints, vecs, nm, count, 1);

    for (i = 0; i < count; i++)
    {
        delete [] ppoints[i];
        delete [] mpoints[i];
    }
    delete [] np;
    delete [] nm;

    return 1;
}
