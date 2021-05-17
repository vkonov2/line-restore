#include <iostream>
#include <string>
#include <cmath>

#include "functions.h"
#include "point.h"
using namespace std;

int main (void)
{
	FILE* f;
	f = fopen ("line_m_data.txt", "w");
	fprintf(f, "%lf %lf %lf\n%lf %lf %lf\n", -3.370184, -2.216509, -6.083328, -1.980432, -2.290605, -4.577121);
	fclose(f);

	return 0;
}