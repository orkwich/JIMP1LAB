#include "gauss.h"
#include <stdio.h>
#include <string.h>

/*
 * Zwraca 0 - elimnacja zakonczona sukcesem
 * Zwraca 1 - macierz osobliwa - dzielenie przez 0*/

void mtprint(Matrix *mt)
{
    for(int i=0;i<mt->r;i++)
    {
        for(int j=0;j<mt->c;j++) printf("%lf ",mt->data[i][j]);
        printf("\n");
    }
}

void mtfix(Matrix *mt) //naprawia pojawiające się wartości bardzo bliskie zeru na równe 0
{
    double d=-0.00000001;
    char s[256],buf[256];
    snprintf(s,256,"%lf",d);
    for(int i=0;i<mt->r;i++)
    {
        for(int j=0;j<mt->c;j++)
        {
            snprintf(buf,256,"%lf",mt->data[i][j]);
            if(strcmp(s,buf)==0) mt->data[i][j]=0;
        }
    }
}

void vdiff(double *s, double *d, double x, int size)
{
    for(int i=0;i<size;i++) s[i]-=d[i]*x;
}

void clswap(Matrix *mt, int a, int b) //zamiana kolumn macierzy
{
    for(int i=0;i<mt->r;i++)
    {
        double tmp=mt->data[i][a];
        mt->data[i][a]=mt->data[i][b];
        mt->data[i][b]=tmp;
    }
}

void rswap(Matrix *mt, int a, int b) //zamiana wierszy macierzy
{
    for(int i=0;i<mt->c;i++)
    {
        double tmp=mt->data[a][i];
        mt->data[a][i]=mt->data[b][i];
        mt->data[b][i]=tmp;
    }
}

double wb(double n)
{
    if(n<0) return -n;
    return n;
}

void elemgl(Matrix *mt, Matrix *b, int cl) //wybór elementu głównego
{
    int max=0, maxr;
    for(int i=cl;i<mt->r;i++)
    {
        if(max<wb(mt->data[i][cl]))
        {
            max=wb(mt->data[i][cl]);
            maxr=i;
        }
    }
    rswap(mt,cl,maxr);
    rswap(b,cl,maxr);
}

int czywektor0(double *v, int size)
{
    for(int i=0;i<size;i++) if(v[i]!=0) return 0;
    return 1;
}

int eliminate(Matrix *mat, Matrix *b)
{
	for(int i=0;i<mat->r-1;i++)
    {
        elemgl(mat,b,i);
        #ifdef TEST
        printf("macierz po wyborze elementu glownego:\n");
        mtprint(mat);
        printf("\n");
        #endif
        for(int j=i+1;j<mat->r;j++)
        {
			if(mat->data[i][i]==0)
			{
				printf("Dzielenie przez zero!!!\nMacierz osobliwa\n");
				return 1;
			}
            double tmp=mat->data[j][i]/mat->data[i][i];
            b->data[j][0]-=b->data[i][0]*tmp;
            vdiff(mat->data[j],mat->data[i],tmp,mat->c);
            mtfix(mat);
			if(czywektor0(mat->data[j],mat->r))
            {
                printf("Za malo rownan, jeden z wierszy macierzy wyzerowal sie\n");
                return 1;
            }
            #ifdef TEST
            printf("macierz po wykonaniu odejmowania wierszy:\n");
            mtprint(mat);
            printf("\n");
            #endif
        }
    }
    #ifdef TEST
    printf("macierz po wykonaniu odejmowania wierszy:\n");
    mtprint(mat);
    printf("\n");
    #endif
	return 0;
}

