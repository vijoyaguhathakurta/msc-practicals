#ifndef DFS_H
#define DFS_H

#include <stdio.h>
#include <stdlib.h>
int i,j;

typedef struct nodetype
{	int vertex;
    struct nodetype *link;
} node;

typedef struct g
{   node ** adj_list;
    int vertices;
    int edges;
    int *parent;
    int *visited; // 0-> unvisited, 1->processed, -1->visited  
    int *dfs_no;
    int *dfs_comp;
}Graph;

node * create_node (int v)
{   node *q=(node *)malloc(sizeof(node));
	q->vertex=v;
    q->link= NULL;
    return q;
}

void insertSorted(int u, int v, node **list) 
{	node *curr;
    node *q =create_node(v);

    if (list[u] == NULL) 
		list[u] = q;
    else
    {   curr = list[u];
        if ( v < curr->vertex )
        {   q->link = curr;
            list[u] = q;
        }
        else
        {   while (curr->link != NULL && curr->link->vertex < v)
                curr = curr->link;
            q->link = curr->link;
            curr->link = q;
        }
    }    
}

Graph * create_graph(int v, int e) 
{   Graph *g = (Graph *) malloc (sizeof(Graph));
    g->adj_list = (node**) malloc ( (v + 1) * sizeof(node*) );
    for(i=1; i<=v; i++)
        g->adj_list[i]= NULL;
    
    g->vertices = v;
    g->edges = e;

    g->parent = (int *)malloc( (v + 1) * sizeof(int) );
    for(i=1; i<=v; i++)
        g->parent[i]= 0;
    
    g->dfs_no = (int *)malloc((v + 1) * sizeof(int) );
    for(i=1; i<=v; i++)
        g->dfs_no[i]= 0;
    
    g->dfs_comp = (int *)malloc((v + 1) * sizeof(int) );
    for(i=1; i<=v; i++)
        g->dfs_comp[i]= 0;

    g->visited = (int *)malloc((v + 1) * sizeof(int) );
    for(i=1; i<=v; i++)
        g->visited[i]= 0;
    
    return g;
}

void addEdge (Graph * g, int d, int u, int v)
{   if (u<= g->vertices && v<= g->vertices && u>0 && v>0)
    {   insertSorted( u, v, g->adj_list);
			if(d==0) //for undirected graph
            	insertSorted(v, u, g->adj_list);
    }
    else
    {   printf("Wrong input");
            exit(0);      
    }
}

void printGraph(Graph *g) 
{	node *temp;
    for( i=1; i <= g->vertices ; i++)
	{	temp = g->adj_list[i];
		printf("(%d) ->",i);
		while (temp!=NULL) //checking if end of list is reached
		{		printf ("|%d|->",temp->vertex); 
				temp=temp->link; //moving to the next node
		}
		printf("NULL\n");
	}
}

void printEdge (int v1, int v2, int d)
{   if (d==0)
        printf("{ %d , %d }", v1, v2);
    else if (d==1)
        printf("( %d , %d )", v1, v2);
}


void dfs(Graph *g, int u, int *dfs_n, int *dfs_c)
{   g->dfs_no[u] = ++(*dfs_n);
    g->visited[u] = -1;
    node *t = g->adj_list[u];
    while (t!=NULL)
    {   int v = t->vertex;
        if( g->visited[v] == 0)
        {   g->parent[v] = u;
            dfs(g, v, dfs_n, dfs_c);
        }
        t = t->link;
    }
    g->visited[u] = 1;
    g->dfs_comp[u] = ++(*dfs_c);
}


/*void main() 
{   int s,u;
    int **d;
    int vertices, edges;
    Graph *graph ;
    
    printf("0 :: Undirected Graph\n");
    printf("1 :: Directed Graph\n");
    printf("Enter type of graph:");
    scanf("%d", &s);

    printf("Enter number of vertices : ");
    scanf("%d", &vertices);
    printf("Enter number of edges: ");
    scanf("%d", &edges);
    
    switch(s)
    {   case 0:
            printf("Undirected Graph\n");
            graph = create_graph(vertices, edges);
            inputGraph (graph , 0);
            break;
        case 1:
            printf("Directed Graph\n");
            graph = create_graph (vertices, edges);
            inputGraph (graph, 1);
            break;
        default:
            exit(0);
    }
    printf("\nNo. of vertices : %d\nNo. of edges : %d\n", graph->vertices, graph->edges);
    printGraph (graph);
    
    printf("\n\tDFS:\nEnter the starting vertex  : ");
    scanf("%d", &u);
    
    int dfs_n = 0;
    int dfs_c = 0;
    dfs(graph,u,&dfs_n,&dfs_c);

    printf ("\nDFS TRAVERSAL OF THE GIVEN GRAPH:\n"); 
    printf ("Vertex\tDFS No.\tDFS Completion No.\tParent\n");
    for ( i=1; i<= graph->vertices; i++)
        printf("%d\t%d\t%d\t%d \n",i, graph->dfs_no[i], graph->dfs_comp[i], graph->parent[i]);
}*/

#endif


