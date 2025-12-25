#include <stdio.h>
#include <stdlib.h>

#define EMPTY -2147483648

int i, j, n; 
typedef struct poly{
	int** P;
	int degree;
	int n; 
 }Polynomial;

Polynomial* createPoly(int n)
{	Polynomial *X = (Polynomial*) malloc(sizeof(Polynomial)); 
	
	X->P = (int**) malloc(n*sizeof(int*));
	for(i=0;i<n;i++){
		X->P[i]= (int *) malloc (2*sizeof(int));
		X->P[i][0] = EMPTY;
		X->P[i][1] = EMPTY;
	}
	X->n = n;
	X->degree = -1;
	return X;
}

void sort(Polynomial *X)
{	int p,c;
 	// Bubble sort
	for (i=0; i<(X->n) - 1; i++)
		for (j=0; j<(X->n)-i-1; j++)
			if ( X->P[j][0] < X->P[j+1][0])
			{	p= X->P[j][0];
				c= X->P[j][1];
				X->P[j][0] = X->P[j+1][0];
				X->P[j][1] = X->P[j+1][1];
				X->P[j+1][0] = p;
				X->P[j+1][1] = c;
			}	
	X->degree= X->P [0][0];
}

void insert(int c, int p, Polynomial *X)
{	int f=0,x;
	for( x=0; x<X->n; x++)
		if (X->P[x][0] == p){
			X->P[x][1] += c;
			f=1;
			break;
		} 
	if (f==0)
	{	X->P[n][1] = c;
		X->P[n][0] = p;
		n++;
	}	
}

/* Modified
void insert(int c, int p, Polynomial *X)
{	int x;
	for( x=0; x<X->n; x++)
		if (X->P[x][0] == p){
			X->P[x][1] += c;
			return;
		} 

	X->P[n][1] = c;
	X->P[n][0] = p;
	n++;
	
}*/

void printPoly(Polynomial* X)
{	for(i=0; i< X->n; i++)
	{	if (X->P[i][1] < 0)
			printf(" - ");
		else if (X->P[i][1] > 0 && i>0 && X->P[i-1][1] != 0 )
			printf(" + ");
		else if (X->P[i][1] == 0)
			continue;

		if (X->P[i][0] == 0)
			printf ("%d" , abs(X->P[i][1]));
		else if (X->P[i][0] == 1)
			printf ("%dx" , abs(X->P[i][1]));
		else
			printf ("%dx^%d" , abs(X->P[i][1]) , X->P[i][0] );
	}
}

void inputPoly(Polynomial *X)
{	int c,p;
	n=0;
	printf("Enter the polynomial : \n");
	for (i=0 ; i< X->n ;i++)
	{	printf ("Cofficient: ");
	 	scanf ("%d", &c );
		printf ("Power: ");
	 	scanf ("%d", &p );
		insert(c, p, X);
	}
	sort(X);
	X->n= n;
}



Polynomial* add(Polynomial *A, Polynomial *B){	

	Polynomial *C= createPoly (A->n + B->n); // 6
	n=0;
	for (i=0; i<A->n; i++)
		insert ( A->P[i][1], A->P[i][0], C );
	
	for (i=0; i<B->n; i++)
		insert ( B->P[i][1], B->P[i][0], C );
	sort(C);
	C->n= n;
	return C;
}
 
Polynomial* subtract(Polynomial *A, Polynomial *B)
{	Polynomial *C= createPoly (A->n + B->n);
	n=0;
	for (i=0; i<A->n; i++)
		insert ( A->P[i][1], A->P[i][0], C );
	for (i=0; i<B->n; i++)
		insert ( (-1)*(B->P[i][1]), B->P[i][0], C );
	sort(C);
	C->n= n;
	return C;	
}

Polynomial* multiply(Polynomial *A, Polynomial *B)
{   Polynomial *C = createPoly(2* A->n * B->n);  
    n = 0;  
    for (i = 0; i < A->n; i++)
    	for (j = 0; j < B->n; j++)
           insert((A->P[i][1] * B->P[j][1]), (A->P[i][0] + B->P[j][0]), C);
    sort(C);
    C->n = n;  
	return C;
}
 
Polynomial* diff(Polynomial *A)
{	Polynomial *C = createPoly(A->n);  
    n = 0;  
    for (i = 0; i < A->n; i++)
       insert( (A->P[i][1] * A->P[i][0]), (A->P[i][0] - 1), C);
	sort(C);
    C->n = n;  
	return C;
}
  
void main()
{	int n;
	Polynomial	*A, *B, *C;
 	
	printf("Enter no. of terms in the polynomial A: ");
	scanf("%d",&n);
	A= createPoly(n);
	inputPoly(A);
		
	printf("Enter no. of terms in the polynomial B: ");
	scanf("%d",&n);
	B= createPoly(n);
	inputPoly(B);

	printf("\nPolynomial A: ");
    printPoly(A);
    
    printf("\nPolynomial B: ");
    printPoly(B);
    
	C=add(A,B);
	printf("\n\nPolynomial C = A + B : ");
    printPoly(C);
    
	C=subtract(A,B);
	printf("\n\nPolynomial C = A - B : ");
    printPoly(C);
    
	C=multiply(A,B);
	printf("\n\nPolynomial C = A.B : ");
    printPoly(C);
    
	C=diff(A);
	printf("\n\nPolynomial C = dA/dx : ");
    printPoly(C);
    
}
