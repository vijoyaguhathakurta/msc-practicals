#include <stdio.h>
#include <stdlib.h>
 int i,j;

 int** createSparse(int r, int c)
{	int **X;
    int n= (r*c)/3;
    X = (int**) malloc(n*sizeof(int*));
	for(i=0;i<n;i++)
		X[i] = (int *) malloc (3*sizeof(int));
    X[0][0] = r;
    X[0][1] = c;
    X[0][2] = n;
	return X;
}

int ** inputSparse(int r, int c)
{	int v,n=0;
	int **X = createSparse (r,c);
    printf("Enter the elements of the matrix:\n");
    for (i=1; i<=r; i++)
       for (j=1; j<=c; j++)
        {   scanf("%d", &v);
            if (v != 0)
            {   n++;
                X[n][0] = i;
                X[n][1] = j;
                X[n][2] = v;
            }
        }
    X[0][2] = n;
    return X;
}

void printSparse( int **X)
{   printf ("\n\t1]\t2]\t3]\n");
    for (i=0; i <= X[0][2]; i++)
    {   printf ("[%d \t",i);
        for (j=0; j <= 2; j++)
            printf("%d\t", X[i][j]);
        printf("\n");
    }   
}

void printMatrix(int **X)
{   int k,f=0;
    printf("\n");
    for (i=1; i <= X[0][0]; i++)
    {   for (j=1; j <= X[0][1]; j++)
        {   f=0;
            for (k=1 ; k <= X[0][2]; k++)
            {   if ( X[k][0] == i && X[k][1] == j)
                {   printf(" %d ",X[k][2]);
                    f=1;
                    break;
                }
            }
            if (f==0)
                printf(" 0 ");
        }
        printf("\n");
    }
}

int ** transpose( int **X)
{   int **T = createSparse ( X[0][1] , X[0][0] );
    T[0][2] = X[0][2];
    for (i=1; i <= X[0][2]; i++)
    {   T[i][0] = X[i][1];
        T[i][1] = X[i][0];
        T[i][2] = X[i][2];   
    }
    return T;
} 

int ** sort( int **X)
{   int x;
	for (i=1; i <= X[0][2]; i++)
		for (j=1; j <= X[0][2]-i; j++)
			if ( X[j][0] > X[j+1][0])
			{	x= X[j][0];
				X[j][0] = X[j+1][0];
                X[j+1][0] = x;
				
                x= X[j][1];
                X[j][1] = X[j+1][1];
                X[j+1][1] = x;
                
                x= X[j][2];
				X[j][2] = X[j+1][2];
				X[j+1][2] = x;
			}
    return X;	
}

void main()
{   int r,c;
	printf("Enter the no. of rows : ");
    scanf ("%d", &r);
    printf("Enter the no. of columns : ");
    scanf ("%d", &c);

    int **X = inputSparse(r,c);
    printf("The Sparse Matrix Representation of the given matrix:");
    printSparse(X);
    printf("The Given matrix:");
    printMatrix(X);

    int **T= sort (transpose(X));
    printf("The Sparse Matrix Representation of the Transpose of the given matrix:");
    printSparse(T);
    printf("The Transpose of the given matrix:");
    printMatrix(T);

}
