#include <stdio.h>
int i,j;

typedef struct nodetype
{	int vertex;
    int weight;
	struct nodetype *link;
} node;

node *temp; 
node *list[30];

void createGraph(int vertices, int edges, int w, int d) 
{   int u, v, weight=1;
	node *q;
    for ( i = 1; i <= edges; i++) 
    {   printf("Enter start and end vertex of edge %i : ",i);
        scanf("%d %d", &u, &v);
        if (u<= vertices && v<= vertices && u>0 && v>0)
        {   if(w==1) //for weighted graph
            {   printf("Weight of edge %d : ",i);
                scanf("%d", &weight);
            }
            q=(node *)malloc(sizeof(node));
			q->vertex=v;
    		q->link=list[u];
            q->weight=weight;
		    list[u]=q;
            if(d==0) //for undirected graph
            {   q=(node *)malloc(sizeof(node));
			    q->vertex=u;
    		    q->link=list[v];
                q->weight=weight;
		        list[v]=q;
            }
        }
        else
        {   printf("Wrong input");
            exit(0);
        }
    }
}


void printGraph(int vertices) // to display the list
{	for( i=1;i<=vertices;i++)
	{	temp=list[i];
		printf("|%d|->",i);
		while (temp!=NULL) //checking if end of list is reached
		{		printf ("|%d (%d)|->",temp->vertex, temp->weight); 
				temp=temp->link; //moving to the next node
		}
		printf("NULL\n");
	}
}

void main() 
{   
    int s;
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
    {
        case 1:
            printf("Undirected Unweighted Graph\n");
            createGraph(vertices, edges, 0,0);
            printGraph(vertices);
            break;
        case 2:
            printf("Undirected Weighted Graph\n");
            createGraph(vertices, edges, 1,0);
            printGraph(vertices);
            break;
        case 3:
            printf("Directed Unweighted Graph\n");
            createGraph(vertices, edges, 0,1);
            printGraph(vertices);
            break;

        case 4:
            printf("Directed Weighted Graph\n");
            createGraph(vertices, edges, 1,1);
            printGraph(vertices);
            break;            
    }
}
