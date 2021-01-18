#ifndef _GAUSS_H
#define _GAUSS_H

#include "mat_io.h"

/**
 * Zwraca 0 - elimnacja zakonczona sukcesem
 * Zwraca 1 - macierz osobliwa - dzielenie przez 0*/
void mtfix(Matrix *mt);
void vdiff(double *s, double *d, double x, int size);
void clswap(Matrix *mt, int a, int b);
void zerus(Matrix *mt);
int czywektor0(double *v, int size);
int eliminate(Matrix *mat, Matrix *b);

#endif
