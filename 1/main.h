#ifndef __SOMECODE__
#define __SOMECODE__
#include<stdio.h>
#include<stdlib.h>
typedef struct Line{
        int size;
        double* data;
}Line;
typedef struct Matrix{
        int size;
        Line* data;
}Matrix;
int getInt(int* a);
int getDouble(double* a);
int input(Matrix *rm);
void deletemtr(Matrix *m);
void printmtr(Matrix* m);
int countK(Matrix* m,int i);
int countL(Matrix* m, int i, int k);
void indtask(Matrix* m);
#endif
