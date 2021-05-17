#include <iostream>
#include <string>
#include <cmath>

#include "functions.h"
using namespace std;

/*
    FUNC rm deletes unuseful files
*/

int rm (const int count)
{
	int i, j;
	char pwd1[100], pwd2[100], str1[100], str2[100], num0[10], num1[10];

	for (i = 0; i < count; i++)
    {
        memset (num0, 0, 10);
        memset (num1, 0, 10);
        memset (str1, 0, 100);
        memset (pwd1, 0, 100);
        memset (str2, 0, 100);
        memset (pwd2, 0, 100);

        // linking the names of the files you want

        strcpy (str1, "line_p_data");
        strcpy (str2, "line_m_data");
        strcpy (pwd1, "rm ");
        strcpy (pwd2, "rm ");

        if (i < 10)
        {   
            strcpy (num1, "0");
            sprintf (num0, "%d", i);
            strcat (num1, num0);
        }
        else
            sprintf (num1, "%d", i);

        strcat (str1, num1);
        strcat (str2, num1);

        strcat (str1, ".txt");
        strcat (str2, ".txt");

        strcat (pwd1, str1);
        strcat (pwd2, str2);

        system (pwd1);
        system (pwd2);
    }

    system ("find . -name '*.o' -type f -delete");
    system ("find . -name '*.out' -type f -delete");

	return 1;
}