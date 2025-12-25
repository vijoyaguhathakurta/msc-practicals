#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int i, int j)  
{   int t = a[i];
    a[i] = a[j]; 
    a[j] = t;
}

void printList( int *a, int n)
{   int i;
    for (i = 0; i < n; i++ )
    {   printf("%d\t ", a[i]);
    }
    printf("\n");
}


void shellSort(int *ar, int n, int a, int b)
{   int i,k,x,y;
    for (k=a; k>=1; k-=b)
    {   printf("INCREMENT %d: ARRAY =  ",k);   
        printList(ar,n);
        for (i=0; i<k; i++)
        {   for (x=i; x<n; x+=k)
               for (y=i; y<n-k; y+=k)
                    if (ar[y] > ar[y+k])
                        swap( ar, y, y+k);
            printf("STEP %d: ",i+1);
            printList(ar,n);  
        }
    }    
}

void main()
{   int v[] = {13,3,4,12,14,10,5,1,8,2,7,9,11,6};
    int v1[] = {4,2,1,4,3,5,4,3,1};
    printf("\nUNSORTED LIST:\t");
    printList(v,14);    
    
    shellSort(v,14,7,2);

    printf("\nSORTED LIST:\t");
    printList(v,14);
}
