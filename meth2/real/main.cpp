#include <iostream>
#include <string>
#include <cmath>

#include "functions.h"
#include "point.h"
using namespace std;

int main (void)
{
    int i, j, k;
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
            printf(">>>allocation error\n");
            delete [] n;
            return -3;
        }

        for (j = 0; j < 10000; j++)
        {
            points[i][j].x = 0;
            points[i][j].y = 0;
            points[i][j].z = 0;
        }
    }

    Point* vecs = new Point[10000];
    if (!vecs)
    {
        printf(">>>allocation error --> vecs\n");
        for (j = 0; j < count; j++)
            delete [] points[j];
        delete [] n;
        return -3;
    }

    for (j = 0; j < 10000; j++)
    {
        vecs[j].x = 0;
        vecs[j].y = 0;
        vecs[j].z = 0;
    }

	get_data (points, n, count);

    get_vectors (vecs, n, count);

    // for (i = 0; i < count; i++)
    //     printf("%d: %lf %lf %lf\n", i, vecs[i].x, vecs[i].y, vecs[i].z);

    // k = 0;
    // for (j = 0; j < n[k]; j++)
    //     printf("%lf %lf %lf\n", points[k][j].x, points[k][j].y, points[k][j].z);

    // for (i = 0; i < count; i++)
    //     printf("%d: %lf %lf %lf\n", i, points[i][0].x, points[i][0].y, points[i][0].z);

	solve (points, vecs, n, count);

    for (i = 0; i < count; i++)
        delete [] points[i];
    delete [] n;

    return 0;
}
