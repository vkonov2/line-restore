#include <iostream>
#include <string>
#include <cmath>
#include <cstring>
#include "functions.h"
#include "point.h"
using namespace std;

/*
    FUNC get_data: reading data from files to our structures
    contents
*/

int get_data (Point** points, Point* vecs, int* n, const int count)
{
    FILE* f;
	int i, j, k, len, num;
    char* full_file;
    char* file;
    char pwd[100], str[100], num0[10], num1[10];
    double z_min, z_max;
    double val1, val2, val3;

    z_min = -6.08332812434530;
    z_max = -4.57712089734895;

    // an array for intermediate reading of file elements

    double* arr = new double[10000];
    if (!arr)
    {
        printf(">>>allocation error --> arr\n");
        return -1;
    }
    for (i = 0; i < 10000; i++)
        arr[i] = 0;

    for (i = 0; i < count; i++)
    {
        memset (num0, 0, 10);
        memset (num1, 0, 10);
        memset (str, 0, 100);
        memset (pwd, 0, 100);

        // linking the names of the files you want

        strcpy (str, "merged-cont0");
        strcpy (pwd, "../shadow/");

        if (i < 10)
        {   
            strcpy (num1, "0");
            sprintf (num0, "%d", i);
            strcat (num1, num0);
        }
        else
            sprintf (num1, "%d", i);

        strcat (str, num1);
        strcat (pwd, str);

        f = fopen (pwd, "r");
        if (!f)
        {
            printf(">>>cant open file --> %s\n", pwd);
            delete [] arr;
            return -2;
        }
        fseek(f, 0, SEEK_END);
        len = (int)ftell(f); // the length of the file being read
        fclose(f);

        // an array with all file data

        full_file = (char*)malloc((len+1)*sizeof(char));
        if(!full_file)
        {
            printf(">>>allocation error --> full_file\n");
            delete [] arr;
            return -1;
        } 
            
        f = fopen(pwd, "r");
        if (fread (full_file, sizeof(char), len, f) != (unsigned)len) 
        {
            printf(">>>cant open file --> %s\n", pwd);
            delete [] arr;
            free (full_file);
            return -2;
        }
        fclose(f);

        full_file[len] = '\0';

        // an array with just the data you need

        file = (char*)malloc((len+1)*sizeof(char));
        if (!file)
        {
            printf(">>>allocation error --> file\n");
            delete [] arr;
            free (full_file);
            return -1;
        }
        for (j = 0; j < len; j++)
            file[j] = '0';

        for (j = 48; j < 81; j++)
            file[j-48] = full_file[j];
        for (j = 105; j < len; j++)
            file[j + 34 - 105] = full_file[j];
        int fin = len-48+105-81+1-48;
        file[fin] = '\0';

        // writing the necessary data to a separate file

        strcat (pwd, ".txt");
        f = fopen(pwd, "w");
        if (!f)
        {
            printf(">>>cant open file --> %s\n", pwd);
            delete [] arr;
            free (full_file);
            free (file);
            return -2;
        }
        for (j = 0; j < fin; j++)
            fprintf(f, "%c", file[j]);
        fclose(f);

        // reading the required elements from the received files into one array

        f = fopen(pwd, "r");
        if (!f)
        {
            printf(">>>cant open file --> %s\n", pwd);
            delete [] arr;
            free (full_file);
            free (file);
            return -2;
        }

        if (fscanf (f, "%lf %lf %lf", &val1, &val2, &val3) != 3)
        {
            printf(">>>cant read from file --> %s\n", pwd);
            delete [] arr;
            free (full_file);
            free (file);
            return -3;
        }
        vecs[i].x = val1;
        vecs[i].y = val2;
        vecs[i].z = val3;

        num = 0;
        while (!feof(f))
        {
            if (fscanf (f, "%lf", &arr[num]) != 1)
                break;
            num++;
        }
        n[i] = (int)(num/3.0);
        for (j = 0; j < n[i]; j++)
        {
            points[i][j].x = arr[3*j];
            points[i][j].y = arr[3*j+1];
            points[i][j].z = arr[3*j+2];
        }
        fclose(f);

        free (full_file);
        free (file);
    }

    delete [] arr;

    return 1;
}
