
#include "main.h"

// returns an int between [min, max[
int getRand(int min, int max)
{
	//return (int) min + (rand() % max );
	return (int) min + (rand() / (((double)RAND_MAX + 1)/ max));
}

// returns cost, provided matrix D, solution a, size n
int cost(int * D, int * a, int n)
{
	int sum = 0;
	for( int i=0; i<n; i++)
	{
		if(i < a[i])
			sum += D[ (i*n) + a[i] ];
	}
	return sum;
}

bool contains(int * a, int p, int n)
{
	for(int i = 0; i<n; i++)
	{
		if (a[i] == p) return true;
	}
	return false;
}

// generates a random solution
void genSolution(int * a, int n)
{
	for(int i=0; i<n; i++)
	{
		if(a[i] == -1)
		{

			int p = getRand(0, n);

			if( !contains(a, p, n) && i!=p )
			{
				a[i] = p;
				a[p] = i;
			}
			else i--;
		}
	}
}

void genBestSolution(int * a, int n)
{
	for(int i=0; i<n; i++)
	{
		if ( i%2==0 )
			a[i] = i+1;
		else 
			a[i] = i-1;
	}
}


// 0 -> perfect; 10 -> they will kill each other
void genMatrix(int * D, int n)
{
	for(int i=0; i<n; i++)
		for(int j=0; j<n; j++)
		{
			if(i < j)
			{
				// force a 0 cost solution
				if ( i%2==0 && i==(j-1) ) D[(i*n)+j] = 0;
				else D[(i*n)+j] = getRand(0, 11);
			}
			else
			{	
				// the lower triangle doesnt matter
				D[(i*n)+j] = -1;
			}
		}
}

void printMatrix(int * A, int n)
{
	for(int i = 0; i<n; i++)
	{
		for(int j = 0; j<n; j++)
			printf("%d\t", A[i*n+j]);

		printf("\n");
	}
}

void printArray(int * a, int n)
{
	for(int j = 0; j<n; j++)
		printf("%d\t", a[j]);
	printf("\n");
}

void copyArray(int * src, int *  dst, int n)
{
	for(int j = 0; j<n; j++)
		dst[j] = src[j];
}

void initArray(int * a, int value, int size)
{
	for(int j = 0; j<size; j++)
		a[j] = value;
}


int main()
{
	srand(time(0));

	printf("#Alg\tN\tcost\titerations\n");

	for(int i = 20; i<1000; i+=2)
	{

		// the matrix that contains the compatatibilies
		int * D = (int*) malloc( sizeof(int)*i*i );
		// the array that contains a solution
		int * a = (int*) malloc( sizeof(int)*i );
		initArray(a, -1, i);

		//initialize the matrix
		genMatrix(D, i);

		// generate a solution
		genSolution(a, i);
		
		// calculate its cost
		//printf("Initial cost: %d\n", cost(D, a, i ) );
		
		// run the algorithms
		alg1(i, D, a);
		alg2(i, D, a);

		// free() the malloc()
		free(D);
		free(a);
	}

	return 0;
}