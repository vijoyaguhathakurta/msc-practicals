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

node ** insert(int u, int v, node **list) 
{	node *curr;
    node *q =create_node(v);

    if (list[u] == NULL) 
		list[u] = q;
    else
    {   curr = list[u];
        while (curr->link != NULL)
                curr = curr->link;
        curr->link = q;
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
        {   graph = insert(u,v,graph);
			if(d==0) //for undirected graph
            	graph= insert(v,u,graph);
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
        printf("{ %d , %d }\n", v1, v2);
    else if (d==1)
        printf("( %d , %d )\n", v1, v2);
}

int ** bfs (node **graph, int src)
{   int v,u,s=src,f=0;
    node *cur;
    int ** b = (int**) malloc(  ( 2 * graph[0]->vertex + 1 ) * sizeof(int*));
    int bf = 0, bc = 0;
    // b is a matrix containing all information
    // b[0][0] -> no. of traversal tree edges
    // b[0][1] -> no. of components of undirected graph
    // b[i][0] for all 1 <= i <= vertices(n) -> BFS no.
    // b[i][1] for all 1 <= i <= vertices(n) -> BFS completion no.
    // b[j][0] for all n+1 <= j < 2n -> Parent of each vertex 
    
    int *queue = (int *) malloc (graph[0]->vertex * sizeof(int));
    int front = 0, rear = 0;

    for(i = 0; i <= graph[0]->vertex  ; i++)
    {   b[i] = (int*) malloc (2 * sizeof(int));
        b[i][0] = 0;
        b[i][1] = 0;
    }

    for(i = graph[0]->vertex + 1; i <= 2 * graph[0]->vertex + 1 ; i++)
    {   b[i] = (int*) malloc (sizeof(int));
        b[i][0] = 0;
    }

    while(1)
    {   f=0;
        if (s==src && b[s][0] == 0)
            f=1;
        else
        {   for (i=1; i<= graph[0]->vertex; i++)
               if ( b[i][0] == 0 )
                {   s = i;
                    f = 1;
                    break;     }    
        }
        if (f==0)
            break;
    
        b[s][0] = ++bf;
        b[s][1] = ++bc;
        queue[rear] = s;
        while (front <= rear)
        {   u = queue[front++];
            cur = graph[u];
            while (cur!=NULL)
            {   v = cur->vertex;
                if (b[v][0] == 0)
                {   b[v][0] = ++bf;
                    b[v][1] = b[u][1] + 1;
                    b[graph[0]->vertex + 1 + v][0] = u;
                    queue[++rear] = v;
                }
                cur = cur->link;
            }
        } 
    }
    return b;    
}

void shortest_path(node **graph, int s, int g)
{   int ** b = bfs( graph , s);
    int ** p = &b[graph[0]->vertex+1];
    int i;
    int d = 0;
    int u = g;
    
    printf("The shortest path: %d ",g);
    while(1)
    {   if (g == s)
        {   printf(" : Goal same as Source");
            break;
        }
        if(p[u][0] == 0)
        {   printf(" : No path exists.");
            break;
        } 
        printf("<- %d ", p[u][0]);
        d++;   
        if (p[u][0] == s)
            break;
        u = p[u][0]; 
    }
    printf("\nDistance= %d",d);

}

void main() 
{   int s,u;
    int **b;
    int ** p;
    int vertices, edges;
    node **graph ;
    int src, goal;
    
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
    
    printf("\n\tBFS:\nEnter the starting vertex  : ");
    scanf("%d", &u);
    
    b= bfs(graph,u);
    p = &b[graph[0]->vertex+1];
    
    printf ("\nBFS TRAVERSAL OF THE GIVEN GRAPH:\n"); 
    printf ("Vertex\tBFS No.\tBFS Completion No.\n");
    for ( i=1; i<= graph[0]->vertex; i++)
        printf("%d\t%d\t%d \n",i,b[i][0],b[i][1]);
    
    printf("TREE EDGES:\n");
    for(i = 1; i <= graph[0]->vertex ; i++)
    {   if (i != u)
            printEdge(p[i][0],i,s);
    }        

    printf("\nFinding the shortest path between 2 vertices:\nSource: ");
    scanf("%d",&src);
    printf("Goal: ");
    scanf("%d",&goal);
    shortest_path(graph,src,goal);    
}

