
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

int contains(int * a, int p, int n)
{
	for(int i = 0; i<n; i++)
	{
		if (a[i] == p) return 1;
	}
	return 0;
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

int getMin(int * a, int size)
{
	int min = a[0];
	for(int j = 0; j<size; j++)
		if(a[j] < min) min = a[j];
		
	return min;
}

int main(int argc, char * argv[])
{
	int rank, np;
	int * D;
	int * a;
	int i;
	
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &np);

	int res=-1;
	int * results;
	
	srand(rank + time(0));

	for(i = 20; i<100; i+=2)
	{
	
		// the matrix that contains the compatatibilies
		D = (int*) malloc( sizeof(int)*i*i );
		// the array that contains a solution
		a = (int*) malloc( sizeof(int)*i );
		
		initArray(a, -1, i);
		
		if(rank==0)
		{
			//initialize the matrix
			genMatrix(D, i);
			
			// allocate the array to receive the gold
			results = (int*) malloc( sizeof(int)*np );
		}
		
		// generate a solution
		genSolution(a, i);
		
		//send compatibily matrix and initial solution to other processes
	    MPI_Bcast(D, sizeof(int)*i*i, MPI_BYTE, 0, MPI_COMM_WORLD);
	    //MPI_Bcast(a, sizeof(int)*i, MPI_BYTE, 0, MPI_COMM_WORLD);
		
		res = alg2(i, D, a, rank);
		
		//MPI_Barrier(MPI_COMM_WORLD);
		
		MPI_Gather(&res, 1, MPI_INT, results, 1, MPI_INT, 0, MPI_COMM_WORLD);
		
		if(rank==0)
		{
			printf("%d\t%d\n", i, getMin(results, np) );
			
			// clean
			free(results);
		}
			
		free(D);
		free(a);
		
	}
	
	MPI_Finalize();
	
	return 0;
}
