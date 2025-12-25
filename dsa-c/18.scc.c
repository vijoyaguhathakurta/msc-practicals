#include <stdio.h>
#include <stdlib.h>

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
{   int i;
    Graph *g = (Graph *) malloc (sizeof(Graph));
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
{	int i;
    node *temp;
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


void dfs(Graph *g, int u, int *dfs_n, int *dfs_c, int *stack, int *top)
{   g->dfs_no[u] = ++(*dfs_n);
    g->visited[u] = -1;
    node *t = g->adj_list[u];
    while (t!=NULL)
    {   int v = t->vertex;
        if( g->visited[v] == 0)
        {   g->parent[v] = u;
            dfs(g, v, dfs_n, dfs_c, stack, top);
        }
        t = t->link;
    }
    g->visited[u] = 1;
    g->dfs_comp[u] = ++(*dfs_c);
    // push vertex in stack if dfs is completed on that vertex
    stack[++(*top)] = u;
}

Graph *transpose (Graph *g)
{   int u;
    Graph *g1 = create_graph(g->vertices, g->edges);
    for ( u = 1; u <= g->vertices; u++)
    {   node *t = g->adj_list[u];
        while(t!=NULL)
        {   addEdge(g1, 1, t->vertex, u);
            t = t->link;
        }          
    }
    return g1;
}

void find_scc(Graph *g)
{   int i;
    int *stack = (int *)malloc(g->vertices * sizeof(int) );
    int top = -1;
    int dfs_n = 0;
    int dfs_c = 0;

    //Perform a DFS on the Original Graph
    dfs(g, 1, &dfs_n, &dfs_c, stack, &top);

    //Create the Transpose Graph
    Graph *g1 = transpose(g);

    int *stack1 = (int *)malloc(g1->vertices * sizeof(int) );
    int top1 = -1;
    int dfs_n1 = 0;
    int dfs_c1 = 0;
    int c = 0; // no. of sccs

    // Perform DFS on the Transposed Graph
    while (top>=0)
    {   int v = stack[top--];
        if (g1->visited[v] == 0)
        {   dfs(g1, v, &dfs_n1, &dfs_c1, stack1, &top1);
            printf("\nSCC %d: ",++c);
            int f = 0;
            for (i=1; i<=g1->vertices; i++)
            {   int p = g1->parent[i];
                if( p != 0)
                {   // tree edges in the scc
                    printEdge(i, p, 1);
                    node *t = g1->adj_list[i];
                    while (t!=NULL)
                    {   // finding the backward edges in the scc 
                        if (g1->dfs_no[i] > g1->dfs_no[t->vertex] && g1->dfs_comp[i] < g1->dfs_comp[t->vertex])
                            printEdge(t->vertex, i, 1);
                        t = t->link;
                    }
                    g1->parent[i] = 0;
                    g1->dfs_comp[i] = 0;
                    g1->dfs_no[i] = 0;
                    f = 1;
                } 
            }
            if (f==0)
                printf("%d",v);         
        }       
    }
}


void main() 
{   Graph *G = create_graph(7,11);
    addEdge(G,1,1,6);
    addEdge(G,1,1,5);
    addEdge(G,1,1,3);
    addEdge(G,1,2,3);
    addEdge(G,1,2,7);
    addEdge(G,1,3,4);
    addEdge(G,1,3,2);
    addEdge(G,1,4,6);
    addEdge(G,1,5,4);
    addEdge(G,1,5,7);
    addEdge(G,1,6,5);
    //printf("Example 1: \n");
    printGraph(G);
    find_scc(G);

    /*Graph *G1 = create_graph(7,10);
    addEdge(G1,1,1,2);
    addEdge(G1,1,2,3);
    addEdge(G1,1,2,4);
    addEdge(G1,1,3,4);
    addEdge(G1,1,3,6);
    addEdge(G1,1,4,5);
    addEdge(G1,1,4,1);
    addEdge(G1,1,5,6);
    addEdge(G1,1,6,7);
    addEdge(G1,1,7,5);
    printf("\n\n\nExample 2: \n");
    printGraph(G1);
    find_scc(G1);*/
}
