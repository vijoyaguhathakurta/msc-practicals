#include <stdio.h>
#include <stdlib.h>
#define MIN(a,b) (((a)<(b))?(a):(b))

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
    int *low_pt;
    int *articulation_pt;
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
    
    g->visited = (int *)malloc((v + 1) * sizeof(int) );
    for(i=1; i<=v; i++)
        g->visited[i]= 0;
    
    g->low_pt = (int *)malloc((v + 1) * sizeof(int) );
    for(i=1; i<=v; i++)
        g->low_pt[i]= 0;

    g->articulation_pt = (int *)malloc((v + 1) * sizeof(int) );
    for(i=1; i<=v; i++)
        g->articulation_pt[i]= 0;
        
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

void update_lowpt( Graph *g, int u, int v)
{   node *t = g->adj_list[v];
    while (t!=NULL)
    {   int w = t->vertex;
        if (w != u) // not parent
        {   if (g->visited[w] == -1) // if w is visited
                g->low_pt[v] = MIN (g->dfs_no[w] , g->low_pt[v]);
            else    //if w is processed or unvisited
                g->low_pt[v] = MIN (g->low_pt[w] , g->low_pt[v]);
        }        
        t = t->link;
    }
}

void pop( int u, int **stack, int *top, int *c) // prints a bcc
{   int f = 0;
    if (*top == -1)
        return;
    printf("\nBCC %d : ",++(*c));
    while (1)
    {   if (*top == -1 || f == 1)
            break;
        if (stack[*top][0] == u)
            f = 1;
        printEdge( stack[(*top)--][0], stack[*top][1], 0);  
    }
}

void dfs(Graph *g, int u, int *dfs_n, int **stack, int *top, int *c)
{   g->dfs_no[u] = ++(*dfs_n);
    g->visited[u] = -1;
    g->low_pt[u] = *dfs_n;

    node *t = g->adj_list[u];
    while (t!=NULL)
    {   int v = t->vertex;
        if( g->visited[v] == 0)
        {   g->parent[v] = u;
            stack[++(*top)][0] = u;
            stack[*top][1] = v;
            dfs(g, v, dfs_n, stack, top, c);
            update_lowpt(g, u, v);
            if ( g->low_pt[v] >= g->dfs_no[u] && u != 1 )
            {   g->articulation_pt[u] = 1;
                pop( u, stack, top, c);
            }
        }
        t = t->link;
    }
    g->visited[u] = 1;
}

void find_bcc(Graph *g)
{   int i;
    int top = -1;
    int **stack = (int**) malloc(  g->vertices * sizeof(int*));
    for(i = 0; i < g->vertices   ; i++)
    {   stack[i] = (int*) malloc (2 * sizeof(int));
        stack[i][0] = 0;
        stack[i][1] = 0;
    }
    int dfs_n = 0;
    int dfs_c = 0;
    int root = 1;
    int c=0;

    dfs (g, root, &dfs_n, stack, &top, &c );//perform dfs and print the bcc acc.

    // check if root is articulation point
    node *t = g->adj_list[root];
    // root is articulation point if it has more than 1 child and its lowpt is not equal to any one of its children
    while (t!=NULL)
    {   int v = t->vertex;
        if (g->low_pt[root] != g->low_pt[v])
        {   g->articulation_pt[root] = 1;
            pop( root, stack, &top, &c);
        }
        t = t->link;
    }

    // if stack not empty then pop all elements as they form a bcc
    pop(0, stack, &top, &c);

    //articulation points
    printf("\n\nThe articulation points are : ");
    for (i=1 ; i <= g->vertices; i++ )
        if (g->articulation_pt[i] == 1)
            printf("%d, ",i);
}

void main() 
{   /*Graph *G = create_graph(7,11);
    addEdge(G,0,1,6);
    addEdge(G,0,1,5);
    addEdge(G,0,1,3);
    addEdge(G,0,2,3);
    addEdge(G,0,2,7);
    addEdge(G,0,3,4);
    addEdge(G,0,3,2);
    addEdge(G,0,4,6);
    addEdge(G,0,5,4);
    addEdge(G,0,5,7);
    addEdge(G,0,6,5);
    */

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
    addEdge(G1,1,7,5);*/

    Graph *G = create_graph(10,13);
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

    /*Graph *G = create_graph(4,3);
    addEdge(G,0,1,2);
    addEdge(G,0,1,3);
    addEdge(G,0,1,4);*/
    
    printGraph(G);
    find_bcc(G);
}

/*Algorithm FindBCCs(Graph G):
    Input: A graph G with vertices V and edges E
    Output: List of all biconnected components (BCCs)

    Initialize:
        disc[] ← -1  // Discovery time for each vertex (initially unvisited)
        low[] ← -1   // Lowest discovery time reachable from each vertex
        parent[] ← -1 // Parent of each vertex in DFS tree
        visited[] ← false // To track visited vertices
        stack[] ← empty stack // Stack to hold edges during DFS
        time ← 0 // To track the discovery time
        BCCs ← empty list // List to store BCCs

    For each vertex u in G:
        If u is not visited:
            DFS(u)

    // Function to perform DFS and find BCCs
    Function DFS(u):
        // Initialize discovery time and low time
        disc[u] ← low[u] ← ++time
        visited[u] ← true
        children ← 0 // Count the number of children in DFS tree

        // For each adjacent vertex v of u
        For each vertex v adjacent to u:
            If v is not visited:
                // Push the edge (u, v) onto the stack
                stack.push((u, v))
                parent[v] ← u
                children ← children + 1

                // Recur for DFS
                DFS(v)

                // After recursion, update the low value of u
                low[u] ← min(low[u], low[v])

                // Check if u is an articulation point
                If (parent[u] == -1 and children > 1) or (parent[u] != -1 and low[v] >= disc[u]):
                    // u is an articulation point, pop edges from the stack to form a BCC
                    BCC ← empty list
                    While stack is not empty:
                        edge ← stack.pop()
                        BCC.push(edge)
                        If edge == (u, v):
                            Break
                    BCCs.push(BCC)

            Else If v is not parent[u] and disc[v] < disc[u]:
                // Update low[u] for back edges
                low[u] ← min(low[u], disc[v])
                stack.push((u, v)) // Push back edge onto the stack

        // If the DFS finishes and there are still edges in the stack, pop them to form a BCC
        If stack is not empty:
            BCC ← empty list
            While stack is not empty:
                edge ← stack.pop()
                BCC.push(edge)
            BCCs.push(BCC)
*/