#include <stdio.h>
int graph[30][30] = {0};
int i,j;

void createGraph(int vertices, int edges, int w, int d) 
{   int u, v, weight=1;
    for ( i = 1; i <= edges; i++) 
    {   printf("Enter start and end vertex of edge %i : ",i);
        scanf("%d %d", &u, &v);
        if (u<= vertices && v<= vertices && u>0 && v>0) 
        {   if(w==1) // for weighted graph
            {   printf("Weight of edge %d : ",i);
                scanf("%d", &weight);
            }
            graph[u][i] = weight; // Mark vertex u as connected to edge i
            if(d==1)    //for directed graph
                graph[v][i] = -weight; // Mark vertex v as connected to edge i
            else if(d==0) //for undirected graph
                graph[v][i] = weight;
        }
        else
        {   printf("Wrong input");
            exit(0);
        }
    }
}

void printGraph(int vertices, int edges) 
{   printf("Incidence Matrix:\n");
    for ( i = 1; i <= vertices; i++) 
    {   for ( j = 1; j <= edges; j++) 
            printf("%d ", graph[i][j]);
        printf("\n");
    }
}

void main() 
{   int s;
    printf("1 :: Undirected Unweighted Graph\n");
    printf("2 :: Undirected Weighted Graph\n");
    printf("3 :: Directed Unweighted Graph\n");
    printf("4 :: Directed Weighted Graph\n");
    printf("Enter type of graph:");
    scanf("%d", &s);

    int vertices, edges;
    printf("Enter number of vertices : ");
    scanf("%d", &vertices);
    printf("Enter number of edges: ");
    scanf("%d", &edges);

    switch(s)
    {   case 1:
            printf("Undirected Unweighted Graph\n");
            createGraph(vertices, edges, 0,0);
            printGraph(vertices, edges);
            break;
        case 2:
            printf("Undirected Weighted Graph\n");
            createGraph(vertices, edges, 1,0);
            printGraph(vertices, edges);
            break;
        case 3:
            printf("Directed Unweighted Graph\n");
            createGraph(vertices, edges, 0,1);
            printGraph(vertices, edges);
            break;

        case 4:
            printf("Directed Weighted Graph\n");
            createGraph(vertices, edges, 1,1);
            printGraph(vertices, edges);
            break;            
    }
}
