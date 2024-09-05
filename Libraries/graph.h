#include <stdio.h>
#include <stdlib.h>

typedef struct vertexNode *vertex;
typedef struct edgeNode *edge;

struct vertexNode
{
    int data;
    edge list;
};

struct edgeNode
{
    int weight;
    edge next;
    vertex vertex;
};

vertex makeGraph(int);
edge makeEdgesList();

vertex makeGraph(int x)
{
    vertex v = (vertex)malloc(sizeof(struct vertexNode));
    v->data = x;
    v->list = makeEdgesList();
    return v;
}

edge makeEdgesList()
{
    edge e = (edge)malloc(sizeof(struct edgeNode));
    e->next = NULL;
    e->vertex = NULL;
    e->weight = -1;
    return e;
}

void makeEdge(vertex v1, vertex v2)
{
    edge temp;
    edge e1 = (edge)malloc(sizeof(struct edgeNode));
    temp = v1->list->next;
    v1->list->next = e1;
    e1->next = temp;
    e1->vertex = v2;

    edge e2 = (edge)malloc(sizeof(struct edgeNode));
    temp = v2->list->next;
    v2->list->next = e2;
    e2->next = temp;
    e2->vertex = v1;
}

void makeDirectedEdge(vertex v1, vertex v2)
{
    edge temp;
    edge e1 = (edge)malloc(sizeof(struct edgeNode));
    temp = v1->list->next;
    v1->list->next = e1;
    e1->next = temp;
    e1->vertex = v2;
}

void makeWeightedEdge(vertex v1, vertex v2, int weight)
{
    edge temp;
    edge e1 = (edge)malloc(sizeof(struct edgeNode));
    e1->weight = weight;
    temp = v1->list->next;
    v1->list->next = e1;
    e1->next = temp;
    e1->vertex = v2;

    edge e2 = (edge)malloc(sizeof(struct edgeNode));
    e2->weight = weight;
    temp = v2->list->next;
    v2->list->next = e2;
    e2->next = temp;
    e2->vertex = v1;
}

void makeWeightedDirectedEdge(vertex v1, vertex v2, int weight)
{
    edge temp;
    edge e1 = (edge)malloc(sizeof(struct edgeNode));
    e1->weight = weight;
    temp = v1->list->next;
    v1->list->next = e1;
    e1->next = temp;
    e1->vertex = v2;
}

void printVertexEdges(vertex v)
{
    edge e = v->list->next;
    while (e != NULL)
    {
        printf("%d  ", e->vertex->data);
        e = e->next;
    }
}

/*

int main()
{
    vertex v1 = makeGraph(1);
    vertex v2 = makeGraph(2);
    vertex v3 = makeGraph(3);
    vertex v4 = makeGraph(4);

    makeEdge(v1, v2);
    makeEdge(v2, v4);
    makeEdge(v4, v1);
    makeEdge(v3, v2);
    

    
    return 0;
}

*/
