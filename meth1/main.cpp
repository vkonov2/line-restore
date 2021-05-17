#include <iostream>
#include <string>
#include <cmath>

#include "functions.h"
#include "point.h"
using namespace std;

/*
    MAIN FILE OF THE PROJECT
    contents:
    -- memory allocation for sets of points (points)
    -- memory allocation for the set of normal vectors of the planes to which the points belong (vecs)
    -- checking for errors and freeing memory
*/

int main (void)
{
    int i, j, k, err;
    const int count = 100;

    int* n = new int[count];
    if (!n)
    {
        printf(">>>allocation error --> n\n");
        return -1;
    }

    for (i = 0; i < count; i++)
        n[i] = 0;

    Point* points[count];

    for (i = 0; i < count; i++)
    {
        points[i] = new Point[10000];
        if (!points[i])
        {
            printf(">>>allocation error --> points[%d]\n", i);
            delete [] n;
            return -1;
        }

        for (j = 0; j < 10000; j++)
        {
            points[i][j].x = .0;
            points[i][j].y = .0;
            points[i][j].z = .0;
        }
    }

    Point* vecs = new Point[10000];
    if (!vecs)
    {
        printf(">>>allocation error --> vecs\n");
        for (i = 0; i < count; i++)
            delete [] points[i];
        delete [] n;
        return -1;
    }

    for (i = 0; i < 10000; i++)
    {
        vecs[i].x = 0;
        vecs[i].y = 0;
        vecs[i].z = 0;
    }

	err = get_data (points, vecs, n, count);
    if (err < 0)
    {
        printf(">>>error in func --> get_data\n");
        for (i = 0; i < count; i++)
            delete [] points[i];
        delete [] vecs;
        delete [] n;
        return err;
    }

	err = solve (points, vecs, n, count);
    if (err < 0)
    {
        printf(">>>error in func --> get_data\n");
        for (i = 0; i < count; i++)
            delete [] points[i];
        delete [] vecs;
        delete [] n;
        return err;
    }

    // deleting extra files

    rm (count);

    for (i = 0; i < count; i++)
        delete [] points[i];
    delete [] vecs;
    delete [] n;

    return 0;
}
