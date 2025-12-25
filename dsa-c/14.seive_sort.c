#include <stdio.h>
#include <stdlib.h>

typedef struct n{
    int data;
    struct n *link;
}node;

node * createNode(int v){
    node *q = (node *)malloc(sizeof(node));
    q->data = v;
    q->link = NULL;
}

void display( node **list, int n){
    int i;
    node *t;
    printf("\nThe sublists are:\n");
    for (i=0; i< n; i++)
    {   t = list[i];
        printf("[S%d]->", i);
        while ( t != NULL ){
            printf(" %d , ", t->data);
            t = t->link;
        }
        printf("\n");
    }
}

void printArray(int *a, int n){
    int i;
    for(i=0; i<n; i++)
        printf("%d ",a[i]);
    printf("\n");
}

//adds a node to linked list 
node * addNode(node *head, int v){
    node *q = createNode(v);
    
    if (head == NULL)
    {   head = q;
        return head;
    }
    node *t = head;
    while (t->link!=NULL)
        t = t->link;
    t->link = q;

    return head;    
}

//creates an empty header list
node** makeHeaderList(int n){
    node **list = (node **) malloc ( n * sizeof(node*) );
    return list;
}

// adds a node to the header list H
int addToHeader(node **H, int *a, int n){
    int i,j=0,sc=0,f=0;
    // sc = no. of sublists
    //reset H before dividing the current array
    for(i=0; i<n; i++)
        H[i]= NULL;
    
    for(i = 0; i<n; i++){
        int v = a[i];
        f = 0;   
        for (j=0; j<sc; j++){
            // if v is smaller than the first element in H[j]
            //then add v to H[j]
            if(H[j]!=NULL && H[j]->data > v){
                H[j] = addNode(H[j],v);
                f = 1;
                break;
            }
        }
        //else create a new sublist with v as first element
        if(f==0){
            H[sc] = addNode(H[j],v);
            sc++;
        }
    }
    return sc;
}

// reverse the sublists and puts it back in the array
void reverseSublist(node **H, int *a, int n, int sc){
    int i,k=n ;
    for(i=sc-1; i>=0; i--){
        node *t = H[i];
        while(t!=NULL){
            a[--k] = t->data;
            t = t->link;
        }
    }
    printf("Sublists in reverse order: ");
    printArray(a,n);
}

// checks if the array is sorted
/*int isSorted(int *a, int n){
    int i;
    for (i = 0; i < n - 1; i++) 
        if (a[i] > a[i + 1])
                return 0;  // not sorted
    return 1;  // Sorted
    
}*/

void seiveSort(int *a, int n){
    int sc,i=0;
    node **h = makeHeaderList(n);
        
    while(sc!=n){
        //if(isSorted(a,n))
          //  break;
        printf("\nSTEP %d:",++i);
        sc = addToHeader(h,a,n);
        display(h,sc);
        reverseSublist(h,a,n,sc);
    }  
    printf("\nThe Sorted Array: ");
    printArray(a,n);  
    printf("\n");
}


void main()
{
    int i,j;
    //int v[6][3]={{1,5,9},{1,9,5},{5,1,9},{5,9,1},{9,1,5},{9,5,1}};
    //int v[]={1,3,5,7,13,15,17,19,10,8,6,4,20,18,16,14,12,9,11,2};
    //int v[]={6,4,1,9,5,8,3,7,2};
    //int v[]={12,10,8,6,4,2,1,3,5,7,9,11};
    int v[] = {6,4,1,9,3,5,8,7,2};
    seiveSort(v,9);
    //int v[]={6,4,2,1,3,5};
    //display(h,9);
    //h= sort(v,9);
    //printf("\n THE SORTED LIST:\n");
    //print(h);
}