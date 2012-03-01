

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include <mpi.h>

#define MAX_TRIES 100;

#define MAX(a, b) (((a) > (b)) ? (a) : (b))


int getRand(int min, int max);
int cost(int * D, int * a, int n);
int contains(int * a, int p, int n);
void genSolution(int * a, int n);
void genBestSolution(int * a, int n);
void genMatrix(int * D, int n);

void printMatrix(int * A, int n);
void printArray(int * a, int n);
void copyArray(int * src, int *  dst, int n);
void initArray(int * a, int value, int size);

void alg1(int n, int * D, int * a);
int alg2(int n, int * D, int * a, int process_rank);


