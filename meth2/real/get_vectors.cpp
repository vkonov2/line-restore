#include <iostream>
#include <string>
#include <cmath>
#include <cstring>
#include "functions.h"
#include "point.h"
using namespace std;

int get_vectors (Point* vecs, int* n, const int count)
{
	int i, j, k;
	int len;
	double val1, val2, val3;

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

        strcpy (str, "merged-cont0");
        strcpy (pwd, "../../shadow/");

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

        strcat (pwd, str);

        // printf("%s\n", pwd);

        strcat (pwd, ".txt");

        // printf("%s\n", pwd);

        FILE* f;
        f = fopen (pwd, "r");
        if (!f)
        {
            printf(">>>cant open file --> %s\n", pwd);
            return -2;
        }

        if (fscanf (f, "%lf %lf %lf", &val1, &val2, &val3) != 3)
        {
        	printf(">>>cant read from file --> %s\n", pwd);
            return -2;
        }

    	vecs[i].x = val1;
    	vecs[i].y = val2;
    	vecs[i].z = val3;

    	// for (i = 0; i < count; i++)
        //    	printf("%d: %lf %lf %lf\n", i, vecs[i].x, vecs[i].y, vecs[i].z);

        fclose (f);
    }

	return 1;
}