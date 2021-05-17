#include <iostream>
#include <string>
#include <cmath>

#include "functions.h"
#include "point.h"
using namespace std;

int get_data ()
{
	double sqrt2 = 1.414213562373;

	FILE* f1 = fopen("points1.txt", "w");

    if (!f1) 
    {
        printf (">>>can't open file -> points1.txt\n");
        return -1;
    }

    // fprintf(f1, "0 -6 0\n0.2 -6 1\n-0.2 -6 2\n0 -6 3\n0 -6 4\n0.2 -6 5\n-0.2 -6 6\n0 -6 7\n0 -6 7.5\n0 -6 8");

    // fprintf(f1, "2.0000001020102 -4.0000001020102 0\n2.00000020102 -4.00000020102 1\n2.00000010200102 -4.00000010200102 2\n2.000001232021 -4.000001232021 3\n2.00000123012 -4.00012123012 4\n2.000001023012 -4.000001023012 5\n2.00000232122 -4.00000232122 6\n2.0000012322010201 -4.0000012322010201 7\n2.00000023100012 -4.00000023100012 7.5\n2.0000022120001201 -4.0000022120001201 8");

    fprintf(f1, "2.00000201020102 -4.00000201020102 0\n2.10000020102 -4.00000020102 1\n1.90000010200102 -4.00000010200102 2\n2.000001232021 -4.000001232021 3\n2.00000123012 -4.00000123012 4\n2.100000023012 -4.000001023012 5\n1.90000232122 -4.00000232122 6\n2.0000012322010201 -4.0000012322010201 7\n2.00000123100012 -4.00000123100012 7.5\n2.0000022120001201 -4.0000022120001201 8");

    fclose(f1);

    FILE* f2 = fopen("points2.txt", "w");

    if (!f2) 
    {
        printf (">>>can't open file -> points2.txt\n");
        return -1;
    }

    // fprintf(f2, "-6 0 0\n-6 0.2 1\n-6 -0.2 2\n-6 0 3\n-6 0 4\n-6 0.2 5\n-6 -0.2 6\n-6 -0.1 6.5\n-6 0 7\n-6 0 8");

    // fprintf(f2, "-4.00000201020102 2.00000201020102 0\n-4.00000020102 2.00000020102 1\n-4.00000010200102 2.00000010200102 2\n-4.000001232021 2.000001232021 3\n-4.00000123012 2.00000123012 4\n-4.000001023012 2.000001023012 5\n-4.00000232122 2.00000232122 6\n-4.0000012322010201 2.0000012322010201 6.5\n-4.00000123100012 2.00000123100012 7\n-4.0000022120001201 2.0000022120001201 8");

    fprintf(f2, "-4.00000201020102 2.00000201020102 0\n-4.0000020102 2.10000020102 1\n-4.00000010200102 1.90000010200102 2\n-4.000001232021 2.000001232021 3\n-4.00000123012 2.00000123012 4\n-4.000000023012 2.100000023012 5\n-4.00000232122 1.90000232122 6\n-4.0000012322010201 2.0000012322010201 6.5\n-4.00000123100012 2.00000123100012 7\n-4.0000022120001201 2.0000022120001201 8");

    fclose(f2);

    FILE* f3 = fopen("points3.txt", "w");

    if (!f3) 
    {
        printf (">>>can't open file -> points3.txt\n");
        return -1;
    }

    // fprintf(f3, "%lf %lf 0\n%lf %lf 1\n%lf %lf 1.5\n%lf %lf 2\n%lf %lf 3\n%lf %lf 4\n%lf %lf 5\n%lf %lf 6\n%lf %lf 7\n%lf %lf 8", 3*sqrt2, 3*sqrt2, 3*sqrt2+0.2, 3*sqrt2-0.2, 3*sqrt2, 3*sqrt2, 3*sqrt2-0.2, 3*sqrt2+0.2, 3*sqrt2, 3*sqrt2, 3*sqrt2, 3*sqrt2, 3*sqrt2+0.2, 3*sqrt2-0.2, 3*sqrt2-0.2, 3*sqrt2+0.2, 3*sqrt2, 3*sqrt2, 3*sqrt2, 3*sqrt2);

    // fprintf(f3, "%lf %lf 0\n%lf %lf 1\n%lf %lf 1.5\n%lf %lf 2\n%lf %lf 3\n%lf %lf 4\n%lf %lf 5\n%lf %lf 6\n%lf %lf 7\n%lf %lf 8", 3*sqrt2+2.0000012123, 3*sqrt2+2.0000021121, 3*sqrt2+1.99999878669, 3*sqrt2+2.00000212312, 3*sqrt2+2.000001221111, 3*sqrt2+1.999998786978, 3*sqrt2+2.000001111211, 3*sqrt2+2.000001212321, 3*sqrt2+1.999998798, 3*sqrt2+2.000001121221, 3*sqrt2+2.000001112121213, 3*sqrt2+1.9999988898979, 3*sqrt2+2.0000012112112, 3*sqrt2+2.000001112012, 3*sqrt2+1.999999897989, 3*sqrt2+2.0000010101002, 3*sqrt2+2.00000120101010, 3*sqrt2+1.99999987998, 3*sqrt2+2.0000010201021, 3*sqrt2+2.0000020102012011);

    fprintf(f3, "%lf %lf 0\n%lf %lf 1\n%lf %lf 1.5\n%lf %lf 2\n%lf %lf 3\n%lf %lf 4\n%lf %lf 5\n%lf %lf 6\n%lf %lf 7\n%lf %lf 8", 3*sqrt2+2, 3*sqrt2+2, 3*sqrt2+2.1, 3*sqrt2+1.9, 3*sqrt2+2, 3*sqrt2+2, 3*sqrt2+1.9, 3*sqrt2+2.1, 3*sqrt2+2, 3*sqrt2+2, 3*sqrt2+2, 3*sqrt2+2, 3*sqrt2+2.1, 3*sqrt2+1.9, 3*sqrt2+1.9, 3*sqrt2+2.1, 3*sqrt2+2, 3*sqrt2+2, 3*sqrt2+2, 3*sqrt2+2);
    
    fclose(f3);

    return 1;
}