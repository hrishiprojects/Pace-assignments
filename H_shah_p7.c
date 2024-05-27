

/* Define the size of the torus and the partition size H_shah */
ARCHITECTURE TORUS(24);

/* Define constants for matrix size and partition size H_shah */







#define m 24
#define p 2

/* Include necessary header file H_shah */
#include <stdlib.h>

/* Define a 2D array type for a partition H_shah */

typedef float partition[p+1][p+1];
/* Declare matrices A, B, and C as arrays of partitions H_shah */
partition A[m][m], B[m][m], C[m][m];
partition stream Achan[m][m], stream Bchan[m][m];
int i,j;
/* Function to perform matrix multiplication on a given partition H_shah */
void Multiply(int row, int col, value partition myA, value partition myB, partition mainC)
{
  int i,j,k,iter,above,left;
  partition myC = {0};
   /* Determine the neighbors for communication based on torus topology H_shah */

  if (row > 0) above = row-1;
    else above = m-1;
  if (col > 0) left = col-1;
    else left = m-1;
  for (iter = 1; iter <= m; iter++) {
  	/* Send and receive partitions through communication channels H_shah */
    send(Achan[row][left], myA);
	  send(Bchan[above][col], myB);

	  for (i = 1; i <= p; i++)
	   for (j = 1; j <= p; j++)
		  for (k = 1; k <= p; k++)
		    myC[i][j] = myC[i][j] + myA[i][k] * myB[k][j];
		/* Receive updated partitions through communication channels H_shah */
	  recv(Achan[row][col], myA);
	  recv(Bchan[row][col], myB);
  }
  mainC = myC;
}

/* Main function H_shah */

main( ) {

  int k, l;

  /* Initialize matrices A and B with random values H_shah */
  for (i = 0; i < m; i++)
	 for (j = 0; j < m; j++)
	  for (k = 1; k <= p; k++)
	    for (l = 1; l <= p; l++) {
		    A[i][j][k][l] = (rand() % 100)/10.0;
		    B[i][j][k][l] = (rand() % 100)/10.0;
	     }

  for (i = 0; i < m; i++)
	 for (j = 0; j < m; j++)
	  fork (@i * m + j)
      Multiply(i, j, A[i][(j+i)%m], B[(i+j)%m][j], C[i][j]);

  /* Join parallel threads H_shah */
  for (i = 0; i < m; i++)
	 for (j = 0; j < m; j++)
	  join;
cout << "Multicomputer Matrix Multiply" << ENDL;
cout << "Torus size:     " << m <<  ENDL;
cout << "Partition Size: " << p << ENDL;
cout << "Number of Data elements: "<< m*m*p*p << ENDL;
/*
  cout.precision(4);
  for (i = 0; i < m; i++) {
	 for (j = 0; j < m; j++) {
	  cout << "partition[" << i << ", " << j << "]" << endl;
	  for (k = 1; k <= p; k++) {
		 for (l = 1; l <= p; l++)
		  cout << C[i][j][k][l] << ", ";
	    cout << endl;
	  }
	 }
 }*/
}
