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
    int *degree;
    int *parent;
    int *rank;
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

    g->degree = (int *)malloc( (v + 1) * sizeof(int) );
    for(i=1; i<=v; i++)
        g->degree[i]= 0;

    g->parent = (int *)malloc( (v + 1) * sizeof(int) );
    for(i=1; i<=v; i++)
        g->parent[i]= 0;

    g->rank = (int *)malloc( (v + 1) * sizeof(int) );
    for(i=1; i<=v; i++)
        g->rank[i]= 0;
    
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

void make_set(int x, Graph *g)
{   g->parent[x] = x;
    g->rank[x] = 0;    
}

int find_set(int x, Graph *g)
{   if (x != g->parent[x])
        g->parent[x] = find_set(g->parent[x], g);
    return g->parent[x];
}

void link(int x, int y, Graph * g)
{   if (g->rank[x] > g->rank[y])
        g->parent[y] = x;
    else 
        g->parent[x] = y;
    if (g->rank[x] == g->rank[y])
        g->rank[y] ++;
}

void Union(int x, int y, Graph *g)
{    link( find_set(x , g) , find_set(y , g) , g);
}

void connected_components(Graph *G)
{   int u;
    for (u=1; u <= G->vertices; u++) 
        make_set(u,G);
    for (u=1; u <= G->vertices; u++) 
    {   node *v = G->adj_list[u];
        while (v!=NULL)
        {    if ( find_set(u,G) != find_set(v->vertex,G))
                Union(u,v->vertex,G);
            v = v->link;
            G->degree[u] ++ ;
        }
    }
}

node ** find_components(Graph *g)
{   int i;
    connected_components(g);

    node **c = (node**) malloc ( (g->vertices + 1) * sizeof(node*) );
    for(i=0; i<= g->vertices; i++)
        c[i]= NULL;

    for(i=1; i<= g->vertices; i++)
       insertSorted( g->parent[i] , i, c);
    return c;
}

void print_components(Graph *g)
{   node ** c = find_components(g);

    int i, n=0;
    node *temp;

    printf("\nThe connected components are: \n");
    for( i=0; i <= g->vertices ; i++)
	{	temp = c[i];
        if (temp == NULL)
            continue;
        printf("Component %d : { ", ++n);
		while (temp!=NULL) 
		{		printf ("%d , ",temp->vertex); 
				temp=temp->link; 
		}
        printf("}\n");
	}
}

void print_degree(Graph *g)
{   int i;
    printf("\nThe degree of the vertices:\nVertex\tDegree\n");
    for( i=1; i <= g->vertices ; i++)
	{   printf(" %d\t%d \t", i, g->degree[i]);
        // pendent vetices have degree = 1
        if(g->degree[i] == 1)
            printf("Pendent Vertex");
        // isolated vertices have degree = 0
        if(g->degree[i] == 0)
            printf("Isolated Vertex");
        printf("\n");

    }	
}

void find_clique(Graph *G)
{   int u,v;
    printf("\nThe maximal cliques are : \n");
    for (v=1; v <= G->vertices; v++)
    {   node *ad = G->adj_list[v];
        while (ad != NULL)
        {   // set of vertices in clique
            node *set = NULL;
            int sn = 0; // no. of vertices in clique
            
            // insert an edge in set
            set = create_node(v);
            printf("{ %d, ",set->vertex);
            sn++;
        
            node *q = create_node(ad->vertex);
            q->link = set;
            set = q;
            printf(" %d, ",set->vertex);
            sn ++;
                        
            for( u=1; u <= G->vertices; u++)
            {   // elements in set
                node *t = set;
                int f = 0;
                if (u == v || u == ad->vertex)
                    continue;

                while (t != NULL)
                {   // adjacent vertices of u
                    // edges between u and a->vertex
                    node *a = G->adj_list[u];
                    while(a!=NULL)
                    {   if ( t->vertex == a->vertex)
                        {   f++;
                            break;
                        }
                        a = a->link;
                    }
                    t = t->link;
                }
                // if u has edge to all vertices in set then insert u
                if (f == sn)
                {   node *q = create_node(u);
                    q->link = set;
                    set = q;
                    printf(" %d, ",set->vertex);
                    sn ++;
                }
            }
            printf("}\n");
            ad = ad->link;
        }
    }
}

void main()
{   /*Graph *G = create_graph(10,7);
    addEdge(G,0,1,2);
    addEdge(G,0,2,3);
    addEdge(G,0,2,4);
    addEdge(G,0,1,3);
    addEdge(G,0,5,6);
    addEdge(G,0,5,7);
    addEdge(G,0,8,9);*/
    
    /*Graph *G = create_graph(5,8);
    addEdge(G,0,1,2);
    addEdge(G,0,1,3);
    addEdge(G,0,1,4);
    addEdge(G,0,2,3);
    addEdge(G,0,2,4);
    addEdge(G,0,3,4);
    addEdge(G,0,4,5);
    addEdge(G,0,3,5);*/
    
    Graph *G = create_graph(12,14);
    addEdge(G,0,1,2);
    addEdge(G,0,1,7);
    addEdge(G,0,2,6);
    addEdge(G,0,2,3);
    addEdge(G,0,2,4);
    addEdge(G,0,3,4);
    addEdge(G,0,3,5);
    addEdge(G,0,4,5);
    addEdge(G,0,6,8);
    addEdge(G,0,6,7);
    addEdge(G,0,6,9);
    addEdge(G,0,8,9);
    addEdge(G,0,9,10);
    addEdge(G,0,11,12);
    
    printGraph(G);
    print_components(G);
    print_degree(G);
    find_clique(G);

}