#include <iostream>
#include <string>
#include <cmath>

#include "functions.h"
#include "point.h"
using namespace std;

int main (void)
{
	int n1, n2, n3;
    
	n1 = 10;
	n2 = 10;
	n3 = 10;

	Point* points1 = new Point[n1+1000];
    if (!points1)
    {
        printf(">>>allocation error -> points1\n");
        return -3;
    }
    Point* points2 = new Point[n2+1000];
    if (!points2)
    {
        printf(">>>allocation error -> points2\n");
        delete [] points1;
        return -3;
    }
    Point* points3 = new Point[n3+1000];
    if (!points3)
    {
        printf(">>>allocation error -> points3\n");
        delete [] points1;
        delete [] points2;
        return -3;
    }

	get_data ();

	solve (points1, points2, points3, n1, n2, n3);

	delete [] points1;
    delete [] points2;
    delete [] points3;

    return 0;
}
