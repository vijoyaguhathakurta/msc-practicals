#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0


typedef struct nodetype
{	int vertex;
    struct nodetype *link;
} node;

typedef struct gr
{   node **list;  
    int *type; 
}G;


node * create_node (int v)
{   node *q=(node *)malloc(sizeof(node));
	q->vertex=v;
    q->link= NULL;
    return q;
}

G* allocate_graph(int n) 
{   int i;
    G *g = (G * ) malloc (sizeof(n));
    g->list= (node**) malloc ( (n) * sizeof(node*) );
    g->type= (int*) malloc ( (n) * sizeof(int) );
    for(i=0; i<=n; i++)
    {   g->list[i]= NULL;
        g->type[i] = 0;
    }		
    return g;
}

void printGraph(int *a,G *g,int n) 
{	int i;
    node *temp;
    for( i=0; i < n ; i++)
	{	temp = g->list[i];
        if (g->type[i] != -1)
        {
            printf("[%d (%d)] ->",a[i],i);
            while (temp!=NULL) //checking if end of list is reached
            {		printf ("|%d (%d)|->",a[temp->vertex],temp->vertex); 
                    temp=temp->link; //moving to the next node
            }
            printf("NULL\n");
        }
	}
}

G *create_graph(int *a, int n)
{   int i,j;
    node *cur;
    G *graph = allocate_graph(n);
    
    for (i=0 ; i < n ; i++)
    {   //graph->list[i] = create_node(i);
        //cur = graph->list[i];
        for (j=i+1 ; j<n ; j++)
        {   if(a[i] <= a[j])
            {   //cur = graph->list[i];
                cur = create_node(j);
                cur->link = graph->list[i];
                graph->list[i] = cur;
                graph->type[j]++;
                //cur = cur->link; 
                //printGraph(graph->list);
            }    
        }   
    }
    return graph;  
}

void printList( int *a, int s, int n)
{   int i;
    for (i = s; i <= n; i++ )
    {   printf("%d\t", a[i]);
    }
    printf("\n");
}

/*int isSourceVertex( node **g , int v, int n)
{   int i;
    node *cur;
    for (i=0 ; i<n ; i++ )
    {   // if the vertex is same as the vertex to be checked skip the iteration
        if (g[i]->vertex == v)
            continue;
        // else for all other vertices u check if adjacent vertex of u is v
        // if condition true then not a source vertex     
        cur = g[i]->link;
        while (cur!=NULL)
        {   if ( cur->vertex == v)
                return FALSE;
            cur = cur->link;
        }
    }
    return TRUE;
}*/

int extract(G *g, int n)
{   int i,j;
    node *e;
    // finding the source vertex with the highest position
    for ( i = n-1; i>=0; i--)
        if (g->type[i] == 0)
            break;
    g->type[i]= -1;
    e = g->list[i];
    while(e!=NULL)
    {   g->type[e->vertex]--;
        e= e->link;
    }
    g->list[i]=NULL;
    return i; 
}

int * graphSort(int *a, int n)
{   int i,n1=n;
    int *ar = (int *)malloc(n * sizeof(int)); 
    G *graph = create_graph(a,n);
    printf("\nINITIAL STEP: \n");
    for (i=0; i<n ; i++)
    {   printGraph(a,graph,n);
        ar[i] = a[extract(graph,n)];
        printf("\nSTEP %d: \n",i+1);
        printf("Extract %d\nThe new altered graph:\n",ar[i]);
    }
    return ar;
}

void main()
{   int v[] = {6,4,1,9,5,8,3,7,2};
    //int v[] = {6,4,1,6};
    int v1[] = {4,2,1,4,3,5,4,3,1};
    printf("\nUNSORTED LIST:\t");
    printList(v1,0,8);    
    
    int *ar = graphSort(v1,9);

    printf("\nSORTED LIST:\t");
    printList(ar,0,8);
}
