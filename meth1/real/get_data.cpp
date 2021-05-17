#include <iostream>
#include <string>
#include <cmath>
#include <cstring>
#include "functions.h"
#include "point.h"
using namespace std;

int get_data (Point** points, int* n, const int count)
{
	int i, j, k;
    int len, numm;
    char* s;
    char* file;

    char pwd[100];
    char str[100];
    char num0[10];
    char num[10];

    double z_min, z_max;
    z_min = -6.08332812434530;
    z_max = -4.57712089734895;

    // n0 = 175;

    Point* allpoints[count];

    int* m = new int[count];
    if (!m)
    {
        printf(">>>allocation error --> m\n");
        return -1;
    }

    for (i = 0; i < count; i++)
        m[i] = 0;

    double* arr = new double[10000];
    if (!arr)
    {
        printf(">>>allocation error --> arr\n");
        delete [] arr;
        return -1;
    }

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

        allpoints[i] = new Point[10000];
        if (!allpoints[i])
        {
            printf(">>>allocation error\n");
            for (int k = 0; k < i; k++)
                delete [] allpoints[k];
            return -3;
        }

        for (j = 0; j < 10000; j++)
        {
            allpoints[i][j].x = 0;
            allpoints[i][j].y = 0;
            allpoints[i][j].z = 0;
        }

        FILE* f;
        f = fopen (pwd, "r");
        if (!f)
        {
            printf(">>>cant open file --> %s\n", pwd);
            for (int k = 0; k < i + 1; k++)
                delete [] allpoints[k];
            return -2;
        }

        fseek(f, 0, SEEK_END);
        len = (int)ftell(f);

        fclose(f);

        s = (char*) malloc((len+1)*sizeof(char));
        if(!s)
        {
            printf(">>>allocation error --> s\n");
            for (int k = 0; k < i + 1; k++)
                delete [] allpoints[k];
            delete [] m;
            delete [] arr;
            return -1;
        } 
            

        f = fopen(pwd, "r");
        
        if (fread(s, sizeof(char), len, f)!=(unsigned)len) 
        {
            printf(">>>cant open file --> %s\n", pwd);
            for (int k = 0; k < i + 1; k++)
                delete [] allpoints[k];
            delete [] m;
            delete [] arr;
            free (s);
            return -2;
        }

        fclose(f);
       
        s[len] = '\0';

        file = (char*)malloc((len+1)*sizeof(char));
        if (!file)
        {
            printf(">>>allocation error --> file\n");
            for (int k = 0; k < i + 1; k++)
                delete [] allpoints[k];
            delete [] m;
            delete [] arr;
            free (s);
            return -1;
        }

        for (j = 0; j < len; j++)
            file[j] = '0';

        for (j = 48; j < 81; j++)
            file[j-48] = s[j];
        for (j = 105; j < len; j++)
            file[j + 34 - 105] = s[j];
        int fin = len-48+105-81+1-48;
        file[fin] = '\0';

        // for (i = 0; i < fin; i++)
        //     printf("%c", file[i]);

        strcat (pwd, ".txt");

        f = fopen(pwd, "w");
        if (!f)
        {
            printf(">>>cant open file --> %s\n", pwd);
            for (int k = 0; k < i + 1; k++)
                delete [] allpoints[k];
            delete [] m;
            delete [] arr;
            free (s);
            free (file);
            return -2;
        }
        for (j = 0; j < fin; j++)
            fprintf(f, "%c", file[j]);

        fclose(f);

        f = fopen(pwd, "r");
        if (!f)
        {
            printf(">>>cant open file --> %s\n", pwd);
            for (int k = 0; k < i + 1; k++)
                delete [] allpoints[k];
            delete [] m;
            delete [] arr;
            free (s);
            free (file);
            return -2;
        }

        numm = 0;

        for (j = 0; j < 10000; j++)
            arr[j] = 0;

        while (!feof(f))
        {
            if (fscanf (f, "%lf", &arr[numm]) != 1)
                break;
            numm++;
        }

        // for (i = 0; i < 3*3; i+=3)
        //     printf("%lf %lf %lf\n", arr[i], arr[i+1], arr[i+2]);

        m[i] = (int)(numm/3.0);

        for (j = 0; j < m[i]; j++)
        {
            allpoints[i][j].x = arr[3*j];
            allpoints[i][j].y = arr[3*j+1];
            allpoints[i][j].z = arr[3*j+2];
        }

        fclose(f);

        free (s);
        free (file);
    }

    // for (i = 0; i < count; i++)
    //     printf("%d\n", m[i]);

    // k = 0;
    // for (j = 0; j < m[k]; j++)
    //     printf("%lf %lf %lf\n", allpoints[k][j].x, allpoints[k][j].y, allpoints[k][j].z);

    // for (i = 0; i < count; i++)
    //     printf("%d: %lf %lf %lf\n", i, points[i][0].x, points[i][0].y, points[i][0].z);

    for (i = 0; i < count; i++)
    {
        numm = 0;
        for (j = 0; j < m[i]; j++)
        {
            if ((allpoints[i][j].z < z_max)&&(allpoints[i][j].z > z_min))
            {
                points[i][numm].x = allpoints[i][j].x;
                points[i][numm].y = allpoints[i][j].y;
                points[i][numm].z = allpoints[i][j].z;

                numm++;
            }
        }
        n[i] = numm;
    }

    // k = 0;
    // for (j = 0; j < n[k]; j++)
    //     printf("%lf %lf %lf\n", points[k][j].x, points[k][j].y, points[k][j].z);

    for (i = 0; i < count; i++)
        delete [] allpoints[i];
    delete [] m;
    delete [] arr;

    return 1;
}
