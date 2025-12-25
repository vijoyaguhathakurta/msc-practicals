#ifndef ADJACENCYLIST_H
#define ADJACENCYLIST_H

/*
    createVertex() : creates a vertex
    createGraph() : creates an empty graph
    displayGraph() : displays the graph
    addEdge() : adds an edge to the graph
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int findIndex(char *arr[], int size, char *target) {
	int i;
    for (i = 1; i <= size; i++) 
        if (strcmp(arr[i], target) == 0) 
            return i; // Return the index if the string is found
    return -1; // Return -1 if the string is not found
}

typedef struct n{
    int position; // position of the vertex i.e. no associated with a vertex
    int weight; // weight of the edge
    struct n *link; //pointer to next node
 } vertex;

typedef struct g{
    vertex ** adj_list; //adjaceny list
    int vertices;   //no. of vertices
    int edges;  // no. of edges
    char **Vname; //name of each vertex
    int directed; // 1 for directed graph
    int weighted; // 1 for weighted graph
    int self_loop; // 1 if there are self loops
}graph;

vertex * createVertex(int v, int wt){
    vertex *q = (vertex *) malloc ( sizeof (vertex) );
    q->position = v;
    q->weight = wt;
    q->link = NULL;
}

graph * createGraph(int v, char **Vname, int directed , int self_loop, int weighted){
    int i;
    graph *g = (graph *) malloc ( sizeof (graph));

    g->adj_list = (vertex **) malloc ( (v + 1) * sizeof(vertex*) );
    for(i=1; i<=v; i++)
        g->adj_list[i]= NULL;

    g->edges = 0;
    g->directed = directed ;
    g->weighted = weighted ;
    g->self_loop = self_loop;
    g->vertices = v;

    g->Vname = (char **) malloc ( (v + 1) * sizeof(char *) );
    for (i=1; i<=v; i++)
        g->Vname[i] = strdup(Vname[i]);

    return g;
}

void displayGraph( graph *g){
    int i;
    vertex *t;
    printf("THE GRAPH IS :\nNo. of vertices = %d\nNo. of edges = %d\nAdjacency List:\n", g->vertices, g->edges);
    for (i=1; i<= g->vertices; i++)
    {   t = g->adj_list[i];
        printf("[%s]", g->Vname[i] );
        while ( t != NULL ){
            printf(" -> [%s", g->Vname[t->position]);
            if (g->weighted == 1)
                printf("|%d", t->weight );
            printf("]");
            t = t->link;
        }
        printf("\n");
    }
}

void insert(graph *g, int u, int v, int wt)
{   vertex *k = createVertex(v,wt);
    k->link = g->adj_list[u];
    g->adj_list[u] = k;
}

void addEdge(graph *g, char *v1, char *v2, int weight){
    int u = findIndex( g->Vname, g->vertices, v1);
    int v = findIndex( g->Vname, g->vertices, v2);
     
    // vertex not present 
    if(u==-1 || v==-1)
    {	printf("The vertex not present."); 
		return;
	}

    //self loop
    if (!g->self_loop && u==v)
    {	printf("Self loop not allowed.\n"); 
		return;
	}

    // same edge check
    vertex *t = g->adj_list[u];
    while (t!=NULL)
    {   if (t->position == v)
        {	printf("The edge already exists.\n"); 
			return;
		}   
        t = t->link;
    }

    g->edges ++;
    if (g->weighted == 1)
    {   insert(g,u,v,weight);
        if (g->directed == 0 && u!=v)
            insert(g,v,u,weight);
    }
    else{
        insert(g,u,v,0);
        if (g->directed == 0 && u!=v)
            insert(g,v,u,0);
    }    
}


/*void graphInput(){
    int n,i,d,s,wt;
    char ch[30];
    char ch1[30];

    printf("Enter the no. of vertices : ");
    scanf("%d",&n);

    printf("\nEnter the vertices: \n");
    char **name = (char **) malloc ( (n + 1) * sizeof(char *) );
    for (i=1; i<=n ; i++)
    {   scanf("%s",&ch);
        name[i] = strdup(ch);
    }

    printf("\nEnter the type of graph (1 for directed or 0 for undirected): ");
    scanf("%d",d);

    graph *g = createGraph(n,name,ch,0);

    printf("\nEnter the edges of the graph (enter 0 when done):\n ");
    while (ch[0] != 0)
    {   printf("Edge %d\nV1: ", g->edges+1);
        scanf("%s",&ch);
        printf("V2: ");
        scanf("%s",&ch1);
        printf("Weight: ");
        scanf("%d",&wt);
        addEdge(g,ch,ch1,wt);
    }    
    displayGraph(g);
}*/

/*void main()
{   char **name = (char **) malloc ( (5 + 1) * sizeof(char *) );
    name[1] = strdup("Kol");
    name[2] = strdup("Ban");
    name[3] = strdup("Che");
    name[4] = strdup("Mum");
    name[5] = strdup("Del");

    graph *g = createGraph(5,name,0,1,1);

    addEdge(g,"Kol","Del",29);
    addEdge(g,"Che","Mum",89);
    addEdge(g,"Kol","Mum",79);
    addEdge(g,"Del","Ban",49);
    addEdge(g,"Del","Del",0);
    addEdge(g,"Del","Ban",49);

    addEdge(g,"Del","Bag",-9);

    displayGraph(g);

    //graphInput();
}*/

#endif
