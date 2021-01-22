#include "backsubst.h"
#include <stdio.h>
/**
 * Zwraca 0 - wsteczne podstawienie zakonczone sukcesem
 * Zwraca 1 - błąd dzielenia przez 0 (element na diagonali = 0)
 * Zwraca 2 - błąd nieprawidłowych rozmiarów macierzy*/
int  backsubst(Matrix *x, Matrix *mat, Matrix *b)
{
	if(mat->r!=mat->c || mat->r!=x->r || mat->r!=b->r) return 2;
    for(int i=mat->r-1;i>=0;i--)
    {
        double sum=0;
		if(mat->data[i][i]==0) return 1;
        for(int j=mat->c-1;j>=0;j--)
        {
            if(i==j)
            {
                x->data[i][0]=((b->data[i][0]-sum)/mat->data[i][j]);
                break;
            } else sum+=(mat->data[i][j]*x->data[j][0]);
        }
    }
	return 0;
}


