#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int main (void)
{
	int i;
    int len;

	FILE* f;
    f = fopen ("merged-cont000", "r");
    if (!f)
    {
        printf(">>>cant open file --> merged-cont000\n");
        return -2;
    }

    fseek(f, 0, SEEK_END);
    len = (int)ftell(f);
    fclose(f);

    char* s;
    s = (char*) malloc((len+1)*sizeof(char));
        if(!s) 
            return -3;

    f = fopen("merged-cont000", "r");
        if(fread(s, sizeof(char), len, f)!=(unsigned)len) 
        {
            printf("ERROR!\n");
            exit(1);
        }
    fclose(f);
   
    s[len] = '\0';

    //int cut0 = 0; --> 0
    //int cut1 = 48; --> 1
    //int cut2 = 81; --> 2
    //int cut3 = 105; --> 3

    // for (i = 81; i < 105; i++)
    //     printf("%c", s[i]);
    // printf("\n");

    char* file;
    file = (char*)malloc((len+1)*sizeof(char));
    if (!file) 
        return -3;

    for (i = 0; i < len; i++)
        file[i] = '0';

    for (i = 48; i < 81; i++)
        file[i-48] = s[i];
    for (i = 105; i < len; i++)
        file[i + 34 - 105] = s[i];
    int fin = len-48+105-81+1-48;
    file[fin] = '\0';

    // for (i = 0; i < fin; i++)
    //     printf("%c", file[i]);

    f = fopen("merged-cont000.txt", "w");
    if (!f)
        return -2;
    for (i = 0; i < fin; i++)
        fprintf(f, "%c", file[i]);

    fclose(f);


    f = fopen("merged-cont000.txt", "r");
    if (!f)
        return -2;

    double* arr = new double[10000];
    if (!arr)
        return -3;

    int num = 0;
    while (!feof(f))
    {
        if (fscanf (f, "%lf", &arr[num]) != 1)
            break;
        num++;
    }

    for (i = 0; i < 3000; i+=3)
        printf("%lf %lf %lf\n", arr[i], arr[i+1], arr[i+2]);

    fclose(f);

	return 0;
}






