#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PARENT(i) floor(i/2)
#define LEFT(i) 2*i
#define RIGHT(i) 2*i+1

int *swap(int *a, int i, int j)  
{   int t = a[i];
    a[i] = a[j]; 
    a[j] = t;
    return a;
}

typedef struct h
{   int *H; // the heap
    int heap_size; // current size of heap
    int length; // max no. of elements heap can hold
}Heap;

Heap *createHeap(int n)
{	Heap *A = (Heap*) malloc(sizeof(Heap)); 
	A->H = (int*) malloc(n*sizeof(int));
	A->heap_size = 0;
    A->length = n;
    return A;
}

void printList( int *a, int s, int n)
{   int i;
    for (i = s; i <= n; i++ )
    {   printf("%d\t", a[i]);
    }
    printf("\n");
}



void heapify(Heap *A, int i)
{   int largest = i;
    int l = LEFT(i);
    int r = RIGHT(i);
    if (i == 0)
        return;
    if (l <= A->heap_size && A->H[l] > A->H[largest])
        largest = l;
    if (r <= A->heap_size && A->H[r] > A->H[largest])
        largest = r;
    if (largest != i)
       A->H = swap( A->H, i, largest);
    heapify ( A, --i);    
}

void insert(Heap *A, int v)
{   int i;
    A->H [ ++ A->heap_size ] = v;
    // considering the parent of last element
    heapify( A, PARENT(A->heap_size));
}

int delete( Heap *A)
{   int i;
    int v = A->H[1];
    // delete the root 
    A->H[1] = A->H [A->heap_size];
    // decrease the heap size by 1
    A->heap_size--;
    // heapify the remaining heap
    for (i = A->heap_size/2; i >=1 ; i-- )
        heapify( A, PARENT(A->heap_size));
    return v;

}

/*void heapSort(int *a, int n)
{   int i;
    Heap *X = createHeap(n);
    
    printf("1. INSERTION INTO HEAP:\n");
    for (i=0;i<n;i++)
    {   printf("%d : ", a[i]);
        insert( X, a[i]);
        printList(X->H , 1 , X->heap_size);
    }

    printf("\n2. DELETION FROM HEAP:\n");
    for (i=0;i<n;i++)
    {   a[i] = delete( X);
        printf("%d : ", a[i]);
        printList(X->H , 1 , X->heap_size);
    }
    
}*/

void max_heapify(int *A, int i, int heap_size){
    int largest;
    int l = LEFT(i);
    int r = RIGHT(i);
    if (l <= heap_size && A[l] > A[i])
        largest = l;
    else 
        largest = i;
    if (r <= heap_size && A[r] > A[largest])
        largest = r;
    if (largest != i)
    {   A = swap( A, i, largest);
        max_heapify ( A, largest, heap_size);
    }
}

void build_heap(int *A, int n){
    for(int i= PARENT(n); i>=1; i--)
        max_heapify(A,i,n);
}

void heapSort(int *A, int n){

    build_heap(A,n);
    for(int i= n; i>=2; i--){
        printList(A,1,n);
        swap(A,1,i);
        max_heapify(A,1,--n);        
    }

}

void main()
{   int val[] = {0,42,23,74,11,65,58,94,36,99,87};
    
    printf("\nUNSORTED LIST:\t");
    printList(val,1,9);    
    
    heapSort(val,9);

    printf("\nSORTED LIST:\t");
    printList(val,1,9);
}