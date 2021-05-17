#ifndef FUNCTIONS_H 
#define FUNCTIONS_H

#include "point.h"

int solve (Point * points1, Point * points2, Point * points3, int n1, int n2, int n3);

int get_data ();

int triangle (Point * points, Point * points1, Point * points2, Point * points3, int n);

int line_solve (Point * points, int n, int flag);

int eigen (int n, int m, double eps, double *A);

int yakobi (double *A, int n, int i, int j);

int vect (double *eigen_val, double *A, double *coefs, Point* points, int n);

int check (Point * points1, Point * points2, Point * points3, int n);

double time_now(void);

#endif
