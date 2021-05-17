#ifndef FUNCTIONS_H 
#define FUNCTIONS_H

#include "point.h"

int solve (Point** points, Point* vecs, int* n, const int count);

int get_data (Point** points, int* n, const int count);

int get_vectors (Point* vecs, int* n, const int count);

int get_new_points (Point** points, int* n, const int count, int flag);

int triangle (Point* mid_points, Point** points, Point* vecs, int num, const int count, int flag);

int line_solve (Point * points, int n, int flag, char* str);

int eigen (int n, int m, double eps, double *A);

int yakobi (double *A, int n, int i, int j);

int vect (double *eigen_val, double *A, double *coefs, Point* points, int n);

int check (Point** points, Point* vecs, int* n, const int count, int flag);

int fprint (Point** points, int* n, const int count, int flag);

double time_now(void);

#endif
