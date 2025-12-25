#include <stdio.h>
#include <stdlib.h>
 int i,j;

typedef struct n{
    int coeff;
    int power;
    struct n *link;
} Polynomial;

Polynomial* create_term ( int c, int p )
{	Polynomial* q = (Polynomial*) malloc ( sizeof (Polynomial));
	q->coeff = c;
	q->power = p;
	q->link = NULL;
	return q;
}

void printPoly(Polynomial *X)
{	Polynomial *temp = X;
	int f=0;
	while (temp!=NULL) 
	{	if (temp->coeff < 0)
		{	printf(" - ");
			f = 0;
		}	
		else if (temp->coeff > 0 && temp != X && f==0)
		{	printf(" + ");
			f= 0;
		}	
		else if (temp->coeff == 0)
		{	temp=temp->link;
			f=1;
			continue;
		}	

		if (temp->power == 0)
			printf ("%d" , abs(temp->coeff));
		else if (temp->power == 1)
			printf ("%dx" , abs(temp->coeff));
		else
			printf ("%dx^%d" , abs(temp->coeff) , temp->power );
		temp=temp->link;
	}
}

Polynomial * insert_sorted(int c, int p, Polynomial *head)
{	Polynomial *curr;
	Polynomial *q = (Polynomial *) malloc ( sizeof (Polynomial));
	q->coeff = c;
	q->power = p;
	q->link = NULL;
	
	if (head == NULL)
		head = q;
	else
	{	curr = head;
		if ( p > curr->power )
		{   q->link = curr;
			head = q;
		}
		else
		{	while (curr->link != NULL && curr->link->power >= p)
			curr = curr->link;
			if ( curr != NULL && curr->power == p )
				curr->coeff += c;
			else
			{	q->link = curr->link;
				curr->link = q;
			}
		}
	}
	return head;
}

Polynomial * inputPoly(Polynomial *X)
{	int c,p;
	printf("Enter the polynomial : \n");
	while(1)
	{	printf ("Cofficient: ");
	 	scanf ("%d", &c );
		if (c==0)
			break;
		printf ("Power: ");
	 	scanf ("%d", &p );
		X = insert_sorted(c, p, X);
	}
	return X;
}

Polynomial* add(Polynomial *A, Polynomial *B)
{	Polynomial *C = NULL;
	Polynomial *curr = A;
	while (curr != NULL)
	{	C = insert_sorted (curr->coeff , curr->power, C);
		curr = curr->link;
	}
	curr = B;
	while (curr != NULL)
	{	C = insert_sorted (curr->coeff , curr->power, C);
		curr = curr->link;
	}
	return C;
}

Polynomial* subtract(Polynomial *A, Polynomial *B)
{	Polynomial *C = NULL;
	Polynomial *curr = A;
	while (curr != NULL)
	{	C = insert_sorted (curr->coeff , curr->power, C);
		curr = curr->link;
	}
	curr = B;
	while (curr != NULL)
	{	C = insert_sorted ( (-1)*curr->coeff , curr->power, C);
		curr = curr->link;
	}
	return C;
}

Polynomial* multiply(Polynomial *A, Polynomial *B)
{   Polynomial *C = NULL;  
    Polynomial *a = A;
	Polynomial *b = B;
	while ( a != NULL )
	{	b = B;
		while (b != NULL)
		{	C = insert_sorted ( (a->coeff * b->coeff), (a->power + b->power), C);
			b = b->link;
		}
		a = a->link;
	}
	return C;
}

Polynomial* diff(Polynomial *A)
{	Polynomial *C = NULL; 
	Polynomial *curr = A;
	while (curr != NULL)
	{	C = insert_sorted (curr->coeff * curr->power, curr->power - 1, C);
		curr = curr->link;
	}
    return C;
}


void main()
{	Polynomial	*A= NULL;
 	printf("Enter the terms in the polynomial A: ");
	A= inputPoly(A);
		
	Polynomial	*B= NULL;
 	printf("Enter the terms in the polynomial B: ");
	B= inputPoly(B);
	
	printf("\nPolynomial A: ");
    printPoly(A);
    
    printf("\nPolynomial B: ");
    printPoly(B);
    
	Polynomial *C;
	
	C = add(A,B);
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
