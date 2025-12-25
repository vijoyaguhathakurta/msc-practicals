#include <stdio.h>
#include <stdlib.h>
int i,j;

typedef struct nodetype
{	int vertex;
    struct nodetype *link;
} node;

node * create_node (int v)
{   node *q=(node *)malloc(sizeof(node));
	q->vertex=v;
    q->link= NULL;
    return q;
}

node ** insertSorted(int u, int v, node **list) 
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
    return list;    
}

node ** create_list(int v, int e) 
{   node **list= (node**) malloc ( (v+1) * sizeof(node*) );
    node *q;
    for(i=0; i<=v; i++)
		list[i]= NULL;
    q= create_node(v);
    list[0] = q;
    q = create_node (e);
    list[0]->link = q;
    return list;
}

node ** inputGraph (node **graph, int d)
{   int u, v;
    for ( i = 1; i <= graph[0]->link->vertex; i++) 
    {   printf("Enter start and end vertex of edge %i : ",i);
        scanf("%d %d", &u, &v);
        if (u<= graph[0]->vertex && v<= graph[0]->vertex && u>0 && v>0)
        {   graph= insertSorted(u,v,graph);
			if(d==0) //for undirected graph
            	graph= insertSorted(v,u,graph);
        }
        else
        {   printf("Wrong input");
            exit(0);      }
    }
    return graph;
}

void printGraph(node **list) 
{	node *temp;
    for( i=1; i <= list[0]->vertex ; i++)
	{	temp=list[i];
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

int ** dfs (node **graph, int s)
{   int k,l, f=0 ;
    int u=s;
    node *curr;
    int p=0;
    int ** d;
    node **stack = create_list( graph[0]->vertex , 0);
    int top=0, df=0, dc=0;

    d = (int**) malloc(  ( 2 * graph[0]->vertex ) * sizeof(int*)); 
    // d is a matrix containing all information
    // d[0][0] -> no. of traversal tree edges
    // d[0][1] -> no. of components of undirected graph
    // d[i][0] for all 1 <= i <= vertices(n) -> DFS no.
    // d[i][1] for all 1 <= i <= vertices(n) -> DFS completion no.
    // d[j][0] for all n+1 <= j < 2n -> Parent of each vertex 
    
    for(i = 0; i <= graph[0]->vertex  ; i++)
    {   d[i] = (int*) malloc (2 * sizeof(int));
        d[i][0] = 0;
        d[i][1] = 0;
    }

    for(i = graph[0]->vertex + 1; i <= 2 * graph[0]->vertex + 1 ; i++)
    {   d[i] = (int*) malloc (sizeof(int));
        d[i][0] = 0;
    }
    
    while(1)
    {   f=0;
        if (u==s && d[s][0] == 0)
            f=1;
        else
        {   for (i=1; i<= graph[0]->vertex; i++)
               if ( d[i][0] == 0 )
                {   u = i;
                    f = 1;
                    break;     }    
        }
        if (f==0)
            break;
        d[0][1]++; // contains the no. of components of undirected graph
        top = 0;
        stack[++top] = create_node(u);
        stack[top]->link = graph[u];
        d[u][0] = ++df;

        while ( top > 0)
        {   curr = stack[top]->link;
            p = stack[top]->vertex;

            while (curr!=NULL)
            {   u = curr->vertex;
                stack[top]->link = curr->link;
                if (d[u][0] == 0)
                {   stack[++top] = create_node(u);
                    stack[top]->link = graph[u]; 
                    d[u][0] = ++df;
                    d[graph[0]->vertex + 1 + u][0] = p;
                    break; 
                }
                curr = curr->link;
            }
            if (curr == NULL)
            {   u = stack[top--]->vertex;
                d[u][1] = ++dc;
            }     
        }
    }
    return d;    
}

void diff_edges (int ** d, node **graph , int dr)
{   node *temp;
    int ** p = &d[graph[0]->vertex+1];
    int u,v;
    printf("\nTHE TYPE OF EACH EDGE OF THE TREE: \n");
    for( u=1; u <= graph[0]->vertex ; u++)
	{	temp=graph[u];
		while (temp!=NULL) 
        {	v = temp->vertex;
            if ( p[v][0] == u)
            {   printEdge( u, v, dr);
                printf(" : TREE EDGE\n");
            }
            else
            {   if ( d[u][0] < d[v][0] && d[u][1] > d[v][1])
                {   printEdge( u, v, dr);
                    printf(" : FORWARD EDGE\n");
                }
                else if ( d[u][0] > d[v][0] && d[u][1] < d[v][1])
                {   printEdge( u, v, dr);
                    printf(" : BACKWARD EDGE\n");
                }
                else if ( d[u][0] > d[v][0] && d[u][1] > d[v][1])
                {   printEdge( u, v, dr);
                    printf(" : CROSS EDGE\n");
                }
            }
        temp=temp->link; 
		}
    }
}

void main() 
{   int s,u;
    int **d;
    int vertices, edges;
    node **graph ;
    
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
            graph = create_list (vertices, edges);
            graph = inputGraph (graph , 0);
            break;
        case 1:
            printf("Directed Graph\n");
            graph = create_list (vertices, edges);
            graph = inputGraph (graph, 1);
            break;
        default:
            exit(0);
    }
    printf("\nNo. of vertices : %d\nNo. of edges : %d\n", graph[0]->vertex, graph[0]->link->vertex);
    printGraph (graph);
    
    printf("\n\tDFS:\nEnter the starting vertex  : ");
    scanf("%d", &u);
    
    d= dfs(graph,u);

    printf ("\nDFS TRAVERSAL OF THE GIVEN GRAPH:\n"); 
    printf ("Vertex\tDFS No.\tDFS Completion No.\n");
    for ( i=0; i<= graph[0]->vertex; i++)
        printf("%d\t%d\t%d \n",i,d[i][0],d[i][1]);
    
    if (s==0)
       printf("No. of components of the graph: %d ", d[0][1]);
    
    diff_edges(d,graph,s);
}

