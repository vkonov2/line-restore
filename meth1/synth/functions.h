#ifndef FUNCTIONS_H 
#define FUNCTIONS_H

#include "point.h"

int solve (Point * points1, Point * points2, Point * points3, int n1, int n2, int n3);

int check (Point * points1, Point * points2, Point * points3, int n, double z_min, double z_max);

int get_data ();

int line_solve (Point * points, int n, int num);

int line_res (double z_min, double z_max);

int eigen (int n, int m, double eps, double *A);

int vect (double *eigen_val, double *A, double *coefs, Point* points, int n);

int yakobi (double *A, int n, int i, int j);

double time_now(void);

#endif
