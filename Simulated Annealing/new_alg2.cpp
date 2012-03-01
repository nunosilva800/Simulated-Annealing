
/*
	Room assign problem

*/
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

#include "main.h"
#include <math.h>


// n is the problem size (number of students to match)
void new_alg2(int n)
{

	// the matrix that contains the compatatibilies
	int * D = (int*) malloc( sizeof(int)*n*n );
	// the array that contains a solution
	int * a = (int*) malloc( sizeof(int)*n );
	int * tmp = (int*) malloc( sizeof(int)*n );
	initArray(a, -1, n);

	//initialize the matrix
	genMatrix(D, n);

	// generate a solution
	genSolution(a, n);
	//printArray(a, n);

	// calculate its cost
	int c = cost(D, a, n );
	printf("Initial cost: %d\n", c );

	// attempt to get a better solution
	int tries = MAX_TRIES;
	int it=1;
	double temperature=1.0;
	int aux1, aux2;
	while(tries)
	{
		int new_a = getRand(0,n);
		int new_b = getRand(0,n);

		if( (new_a != new_b) && (a[new_a] != new_b) )
		{
			// back up our current distribution
			copyArray(a, tmp, n);

			// save the matching partners
			aux1 = a[new_a];
			aux2 = a[new_b];

			// swap the room mates
			tmp[new_a] = aux2;
			tmp[new_b] = aux1;
			tmp[aux1] = new_b;
			tmp[aux2] = new_a;

			//d[a,b] has the compatibility number, d[b,a] has -1.
			int oldcost = MAX(D[(new_a*n) + a[new_a]], D[(a[new_a]*n) + new_a]) + MAX (D[(new_b*n) + a[new_b]], D[(a[new_b]*n) + new_b]); 
			int newcost = MAX(D[(new_b*n) + a[new_a]], D[(a[new_a]*n) + new_b]) + MAX (D[(new_a*n) + a[new_b]], D[(a[new_b]*n) + new_a]);
			int delta = newcost-oldcost;

			if (delta < 0 || exp((double) -delta)/temperature < rand()%1)
			{

				tries = MAX_TRIES;
				copyArray(tmp, a, n);

			}
			else
			{
				tries--;
			
			}

			// keep it cool
			temperature*=0.999;
			it++;

		}
	}

	//printMatrix(D, n);
	//printf("\n");
	printArray(a, n);
	c=cost(D, a, n );
	printf("Final cost: %d with %d iterations\n", c, it );

}