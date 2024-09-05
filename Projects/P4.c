// Bellow ( Last line in the project ) you can find a filled files sample for HSV files ;

// StdName: Abd alraheem Shuaibi ;
// StdNum: 1220148
// SecNum: 3

/*
    Hash-Separated Values (HSV) Input Files Names
    Course: input_courses.txt ;
    Buildings: input_Buildings.txt ;
*/

//=====================================Project description=====================================
/*
    The project main idea is to take a HSV files data by the user first one for the courses which the user can be able to sort
     the courses using Topological-sort afte link them together in graphs, the second one for the biuldings and be able to
     return the shortest route and its distance after link them in un-directed weighted graphs in the link i will provide a photos if this helps ;
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node1 *Vertex;      // Pointer to the Vertices ;
typedef struct node2 *Edge;        // Pointer to the Edgeas ;
typedef struct queueG *queueGraph; // Pointer to queue of graphs ;
typedef struct node1 *heap;        // Pointer to heap of Verteces Pointer;

#define LINE_LENGTH 500
#define WORD_LENGTH 50
#define HEAP_SIZE 100

int current = 1; // Current heap status (Empty place );

struct node1
{
    char word[WORD_LENGTH];
    Edge edges; // Vertex Edges set ;
    int count;  // Count for in edges ;
    int isVisited; // Flag to see if the edge visited ;
    int searchValue; // For saving the shotest path status ( i could use isVisited to save memory and make the flag -1,1 but that is more readable for u) ;
};

struct node2
{
    Edge next;
    Edge back; // The last node
    Vertex edge;
    int weight;
};

struct queueG
{
    queueGraph next;
    queueGraph back; // Last node ;
    Vertex graphPtr;
};

//=============================Graph=============================

Vertex makeVertex(Vertex, char *);
Edge makeEmptyEdge(Edge);
void makeDirectedEdge(Vertex, Vertex);
void insertEdge(Edge, Vertex);
queueGraph makeEmptyqueueGraph(queueGraph);
void enqueueQG(Vertex, queueGraph q);
void dequeueQG(queueGraph);
int isEmptyqueueGraph(queueGraph);
Vertex BFS(Vertex, char *);
Edge topoligicalSort(Vertex);
Vertex BFSCount(Vertex);
int dijkstra(Vertex, Vertex);
void makeWeightedEdge(Vertex, Vertex, int);
int shortestRoute(Vertex, Vertex);
Edge copyGrapghList(Edge, Edge);

//=============================//Graph=============================

//=============================Heap=============================

void insertIntoHeap(Vertex, heap *);
void printHeap(heap *);
void deleteMinHeap(heap *);

//=============================//Heap=============================

//=============================Functions=============================

void loadCourses(char *, Vertex);
void loadBuildings(char *, Vertex);
int ConvertString(char *);

//=============================//Functions=============================

//=========================================================================GraphLibrary=========================================================================

Vertex makeVertex(Vertex g, char *str)
{
    g = (Vertex)malloc(sizeof(struct node1));
    strncpy(g->word, str, sizeof(g->word));
    g->edges = makeEmptyEdge(NULL);
    g->count = 0;
    g->isVisited = 0;
    g->searchValue = -1;
    return g;
}

Edge makeEmptyEdge(Edge l)
{
    l = (Edge)malloc(sizeof(struct node2));
    l->back = l;
    l->edge = NULL;
    l->next = NULL;
    return l;
}

void makeDirectedEdge(Vertex g1, Vertex g2)
{
    Edge l1 = (Edge)malloc(sizeof(struct node2));
    g1->edges->back->next = l1;
    g1->edges->back = l1;
    l1->edge = g2;
    l1->next = NULL;
    // insert a pointer to g2 in g1 edges set ;

    g2->count++;
}

void makeWeightedDirectedEdge(Vertex g1, Vertex g2, int weight)
{
    Edge l1 = (Edge)malloc(sizeof(struct node2));
    l1->weight = weight;
    g1->edges->back->next = l1;
    g1->edges->back = l1;
    l1->edge = g2;
    l1->next = NULL;

    g2->count++;
}

void makeWeightedEdge(Vertex g1, Vertex g2, int weight)
{
    Edge l1 = (Edge)malloc(sizeof(struct node2));
    l1->weight = weight; // set the weight ;
    g1->edges->back->next = l1;
    g1->edges->back = l1;
    l1->edge = g2;
    l1->next = NULL;
    // insert a pointer to g2 in g1 edges set ;

    Edge l2 = (Edge)malloc(sizeof(struct node2));
    l2->weight = weight; // set the weight ;
    g2->edges->back->next = l2;
    g2->edges->back = l2;
    l2->edge = g1;
    l2->next = NULL;
    // insert a pointer to g1 in g2 edges set ;

    g2->count++;
    g1->count++;
}

void insertEdge(Edge l, Vertex g)
{
    Edge l1 = (Edge)malloc(sizeof(struct node2));
    l->back->next = l1;
    l->back = l1;
    l1->edge = g;
    l1->next = NULL;
}

Vertex BFS(Vertex g, char *c)
{
    if (g == NULL)
    {
        return NULL;
    }

    if (!strcmp(g->word, c))
    {
        return g;
    }

    queueGraph q = makeEmptyqueueGraph(NULL);
    queueGraph q1 = makeEmptyqueueGraph(NULL); // Queue to return the needed data to defult ;
    enqueueQG(g, q);
    enqueueQG(g, q1); 
    g->isVisited = 1;
    Edge l1 = g->edges->next;
    if (l1 != NULL && !strcmp(l1->edge->word, c))
    {
        while (!isEmptyqueueGraph(q1))
        {
            q1->next->graphPtr->isVisited = 0;
            dequeueQG(q1);
        }
        return l1->edge;
    }
    while (!isEmptyqueueGraph(q))
    {
        // Insert all pointers to lall graphs that the edge point to to the queue of graphs pointers (is its not visited) ;
        while (l1 != NULL)
        {
            if (l1->edge->isVisited == 0)
            {
                enqueueQG(l1->edge, q);
                enqueueQG(l1->edge, q1);
                l1->edge->isVisited = 1;
            }
            l1 = l1->next;
            // if we find it stop, no? insert the next edge ;
            if (l1 != NULL && !strcmp(l1->edge->word, c))
            {
                while (!isEmptyqueueGraph(q1))
                {
                    q1->next->graphPtr->isVisited = 0;
                    dequeueQG(q1);
                }
                return l1->edge;
            }
        }
        Vertex g4 = q->next->graphPtr;
        enqueueQG(g4, q1);
        dequeueQG(q);

        if (!isEmptyqueueGraph(q))
        {
            // Move to the next graph edges set ;
            l1 = q->next->graphPtr->edges->next;
            if (l1 != NULL && !strcmp(l1->edge->word, c))
            {
                while (!isEmptyqueueGraph(q1))
                {
                    q1->next->graphPtr->isVisited = 0;
                    dequeueQG(q1);
                }
                return l1->edge;
            }
        }
    }
    while (!isEmptyqueueGraph(q1))
    {
        q1->next->graphPtr->isVisited = 0;
        dequeueQG(q1);
    }
    return NULL;
}

// To find a graph which its count is 0 ;
Vertex BFSCount(Vertex g)
{
    queueGraph q = makeEmptyqueueGraph(NULL);
    enqueueQG(g, q);
    g->isVisited = 1;
    Edge l1 = g->edges->next;
    if (l1 != NULL && l1->edge->count == 0)
    {
        return l1->edge;
    }
    while (!isEmptyqueueGraph(q))
    {
        while (l1 != NULL)
        {
            if (!l1->edge->isVisited)
            {
                enqueueQG(l1->edge, q);
                l1->edge->isVisited = 1;
            }
            l1 = l1->next;
            if (l1 != NULL && l1->edge->count == 0)
            {
                while (!isEmptyqueueGraph(q))
                {
                    q->next->graphPtr->isVisited = 0;
                    dequeueQG(q);
                }
                return l1->edge;
            }
        }
        q->next->graphPtr->isVisited = 0;
        dequeueQG(q);
        if (!isEmptyqueueGraph(q))
        {
            l1 = q->next->graphPtr->edges->next;
            if (l1 != NULL && l1->edge->count == 0)
            {
                while (!isEmptyqueueGraph(q))
                {
                    q->next->graphPtr->isVisited = 0;
                    dequeueQG(q);
                }
                return l1->edge;
            }
        }
    }
    return NULL;
}

Edge topoligicalSort(Vertex g)
{
    Edge l1 = makeEmptyEdge(NULL);
    Vertex g1 = g;
    while (g1 != NULL)
    {
        Vertex g1 = BFSCount((g)); // find one with zero count ;
        if (g1 == NULL)
        {
            break;
        }

        // if it has edges re-Arrange the count ;
        if (g1->edges != NULL)
        {
            Edge l = g1->edges->next;
            while (l != NULL)
            {
                Vertex g2 = l->edge;
                g2->count--;
                l = l->next;
            }
        }
        g1->count = -1;
        insertEdge(l1, g1);
    }
    return l1;
}

int dijkstra(Vertex g, Vertex g1)
{
    heap *h = (heap *)malloc(sizeof(heap) * HEAP_SIZE);
    int pin = 0;
    g->searchValue = 0;
    insertIntoHeap(g, h);
    queueGraph q = makeEmptyqueueGraph(NULL);
    while (current != 1)
    {
        Edge l1 = h[1]->edges->next;
        while (l1 != NULL)
        {
            Vertex g2 = l1->edge;
            if (l1->weight < 0)
            {
                l1 = l1->next;
                continue;
            }
            if (g2->searchValue == -1)
            {
                g2->searchValue = l1->weight + h[1]->searchValue;
                insertIntoHeap(g2, h);
            }
            else if (h[1]->searchValue + l1->weight < g2->searchValue)
            {
                g2->searchValue = h[1]->searchValue + l1->weight;
            }
            l1 = l1->next;
        }
        if (h[1] == g1)
        {
            pin = g1->searchValue;
        }
        enqueueQG(h[1], q);
        deleteMinHeap(h);
    }

    while (!isEmptyqueueGraph(q))
    {
        q->next->graphPtr->searchValue = -1;
        dequeueQG(q);
    }

    return pin;
}

int shortestRoute(Vertex g, Vertex g1)
{
    heap *h = (heap *)malloc(sizeof(heap) * HEAP_SIZE);
    int pin = 0;
    g->searchValue = 0;
    insertIntoHeap(g, h);
    queueGraph q = makeEmptyqueueGraph(NULL);
    int i = 1;
    Edge l[50];
    l[0] = makeEmptyEdge(NULL);
    insertEdge(l[0], g);

    while (current != 1)
    {
        Edge l1 = h[1]->edges->next;
        while (l1 != NULL)
        {
            Vertex g2 = l1->edge;
            if (l1->weight < 0)
            {
                l1 = l1->next;
                continue;
            }
            if (g2->searchValue == -1)
            {
                l[i] = makeEmptyEdge(NULL);
                int j = 0;
                while (l[j]->back->edge != h[1])
                {
                    j++;
                }

                l[i] = copyGrapghList(l[j], l[i]);
                insertEdge(l[i], g2);
                i++;
                g2->searchValue = l1->weight + h[1]->searchValue;
                insertIntoHeap(g2, h);
            }
            else if (h[1]->searchValue + l1->weight < g2->searchValue)
            {
                int j = 0;
                int k = 0;
                while (l[j]->back->edge != g2)
                {
                    j++;
                }
                while (l[k]->back->edge != h[1])
                {
                    k++;
                }

                l[j] = copyGrapghList(l[k], l[j]);
                insertEdge(l[j], g2);
                g2->searchValue = h[1]->searchValue + l1->weight;
            }

            l1 = l1->next;
        }
        if (h[1] == g1)
        {
            pin = g1->searchValue;
        }
        enqueueQG(h[1], q);
        deleteMinHeap(h);
    }

    while (!isEmptyqueueGraph(q))
    {
        q->next->graphPtr->searchValue = -1;
        dequeueQG(q);
    }
    int j = 0;
    while (l[j]->back->edge != g1)
    {
        j++;
    }

    Edge l4 = l[j]->next;
    printf("\nThe Shortest route to go between %s and %s is: \n", g->word, g1->word);
    while (l4 != NULL)
    {
        l4->next == NULL ? printf("%s", l4->edge->word) : printf("%s --> ", l4->edge->word);
        l4 = l4->next;
    }

    j = 0;
    while (j < i)
    {
        Edge l3 = l[j]->next;
        while (l3 != NULL)
        {
            Edge temp = l3;
            l3 = temp->next;
            free(temp);
        }
        j++;
    }

    return pin;
}

Edge copyGrapghList(Edge l1, Edge l2)
{

    Edge l3 = l2->next;
    while (l3 != NULL)
    {
        Edge temp = l3;
        l3 = temp->next;
        free(temp);
    }
    Edge l4 = makeEmptyEdge(NULL);
    l3 = l1->next;
    while (l3 != NULL)
    {
        insertEdge(l4, l3->edge);
        l3 = l3->next;
    }

    l3 = l4->next;
    return l4;
}

//=========================================================================//GraphLibrary=========================================================================

//==========================================================================QueueLibrary=========================================================================

queueGraph makeEmptyqueueGraph(queueGraph q)
{
    q = (queueGraph)malloc(sizeof(struct queueG));
    q->back = q;
    q->next = NULL;
    return q;
}

void enqueueQG(Vertex x, queueGraph q)
{
    queueGraph q1 = (queueGraph)malloc(sizeof(struct queueG));
    q->back->next = q1;
    q->back = q1;
    q1->next = NULL;
    q1->graphPtr = x;
}

void dequeueQG(queueGraph q)
{
    if (q->next == NULL)
    {
        return;
    }
    queueGraph q1 = q->next;
    q->next = q->next->next;
    if (q->back == q1)
    {
        q->back = q;
        q->next = NULL;
    }
    free(q1);
}

int isEmptyqueueGraph(queueGraph q)
{
    return q->next == NULL;
}

//=========================================================================//QueueLibrary=========================================================================

//==========================================================================HeapLibrary==========================================================================

void insertIntoHeap(Vertex g, heap *h)
{
    int location = current;
    int x = g->searchValue;
    while (x < h[location / 2]->searchValue && current != 1 && location != 0)
    {
        h[location] = h[location / 2];
        location /= 2;
    }
    location = (location == 0) ? 1 : location;

    h[location] = g;
    current++;
}

void deleteMinHeap(heap *h)
{
    int location = 1;

    while (location <= current / 2)
    {
        if (location * 2 == current)
        {
            break;
        }

        if (location * 2 + 1 == current || h[location * 2]->searchValue <= h[(location * 2) + 1]->searchValue)
        {
            h[location] = h[location * 2];
            location *= 2;
        }
        else
        {
            h[location] = h[(location * 2) + 1];
            location = (location * 2) + 1;
        }
    }
    int shift = location;
    while (shift < current)
    {
        h[shift] = h[shift + 1];
        shift++;
    }
    current--;
}

void printHeap(heap *h)
{
    int i = 1;
    while (i < current)
    {
        printf("%d:  %s   %d\n", i, h[i]->word, h[i]->searchValue);
        i++;
    }
}

//=========================================================================//HeapLibrary==========================================================================

//==============================================================================Main==============================================================================


int main(int argc, char *argv[])
{
    FILE *inputBuildings = NULL;
    inputBuildings = fopen("output/input_buildings.txt", "r");
    if (inputBuildings == NULL)
    {
        printf("\nFailed to load the file, please check file name was: input_buildings.txt ");
    }

    FILE *inputcourses = NULL;
    inputcourses = fopen("output/input_courses.txt", "r");
    if (inputcourses == NULL)
    {
        printf("\nFailed to load the file, please check file name was: input_courses.txt ");
    }

    Vertex gCourse = makeVertex(NULL, "\0");
    Vertex gBuild = makeVertex(NULL, "\0");

    int operation = 0;
    printf("Enter what operation you want based on the index:\n1-Load the input files.\n2-Calculate the shortest distance between two buildings.\n3-Print the shortest route between two buildings and the total distance.\n4-Sort the Courses.\n5-Print the sorted courses.\n6-Exit.\n");
    scanf("%d", &operation);
    getchar(); // Will catch the '\n' that printed by fgets (Could use somtihng like scanf and define a usless variable but that's more cool so don't give me a copy please ) ;

    Edge l1 = NULL;
    while (operation != 6)
    {
        switch (operation)
        {
            char buldings[LINE_LENGTH];
            char courses[LINE_LENGTH];
            char word1[WORD_LENGTH];
            char word2[WORD_LENGTH];

            Vertex g2, g3;
            Edge l2;
        case 1:
            while (fgets(buldings, sizeof(buldings), inputBuildings) != NULL)
            {
                if (buldings[strlen(buldings) - 1] == '\n')
                {
                    buldings[strlen(buldings) - 1] = '\0';
                }

                loadBuildings(buldings, gBuild);
            }
            while (fgets(courses, sizeof(courses), inputcourses) != NULL)
            {
                if (courses[strlen(courses) - 1] == '\n')
                {
                    courses[strlen(courses) - 1] = '\0';
                }

                loadCourses(courses, gCourse);
            }

            break;
        case 2:
            if (gBuild->edges->next == NULL)
            {
                printf("\nPlease Fill the Data first by pressing on option number: 1\n");
                break;
            }
            printf("\nPlease Enter the first Building name:   ");
            fgets(word1, sizeof(word1), stdin);
            word1[strlen(word1) - 1] = '\0';
            g2 = BFS(gBuild, word1);

            if (g2 == NULL)
            {
                printf("\nThe building %s does not exist, please check the name and try again (:\n", word1);
                break;
            }

            printf("\nPlease Enter the Second Building name:   ");
            fgets(word2, sizeof(word2), stdin);
            word2[strlen(word2) - 1] = '\0';
            g3 = BFS(gBuild, word2);
            if (g3 == NULL)
            {
                printf("\nThe building %s does not exist, please check the name and try again (:\n", word2);
                break;
            }

            printf("\nThe shortest Path between %s and %s is:  %d  ", word1, word2, dijkstra(g2, g3));

            break;
        case 3:
            if (gBuild->edges->next == NULL)
            {
                printf("\nPlease Fill the Data first by pressing on option number: 1\n");
                break;
            }

            printf("\nPlease Enter the first Building name:   ");
            fgets(word1, sizeof(word1), stdin);
            word1[strlen(word1) - 1] = '\0';
            g2 = BFS(gBuild, word1);

            if (g2 == NULL)
            {
                printf("\nThe building %s does not exist, please check the name and try again (:\n", word1);
                break;
            }

            printf("\nPlease Enter the Second Building name:   ");
            fgets(word2, sizeof(word2), stdin);
            word2[strlen(word2) - 1] = '\0';
            g3 = BFS(gBuild, word2);
            if (g3 == NULL)
            {
                printf("\nThe building %s does not exist, please check the name and try again (:\n", word2);
                break;
            }

            printf("\nThe distance beteen them is:  %d\n\n", shortestRoute(g2, g3));
            break;
        case 4:
            if (gCourse->edges->next == NULL)
            {
                printf("\nPlease Fill the Data first by pressing on option number: 1\n");
                break;
            }
            if (l1 != NULL)
            {
                break;
            }
            
            l1 = topoligicalSort(gCourse)->next;
            break;
        case 5:
            if (gCourse->edges->next == NULL)
            {
                printf("\nPlease Fill the Data first by pressing on option number: 1\n");
                break;
            }
            if (l1 == NULL)
            {
                printf("\nPlease sort the courses first.\n");
                break;
            }
            printf("\nThe Sorted courses are:\n");
            l2 = l1;
            while (l2 != NULL)
            {
                printf("%s  ", l2->edge->word);
                l2 = l2->next;
            }
            break;
        case 6:
            printf("\nExit Success (exit(0))\n");
            break;

        default:
            printf("Please Enter a valid key");
            break;
        }
        printf("\nEnter what operation you want based on the index:\n1-Load the input files.\n2-Calculate the shortest distance between two buildings.\n3-Print the shortest route between two buildings and the total distance.\n4-Sort the Courses.\n5-Print the sorted courses.\n6-Exit.\n");
        scanf("%d", &operation);
        getchar(); // Will catch the '\n' that printed by fgets (Could use somtihng like scanf and define a usless variable but that's more cool so don't give me a copy please ) ;
    }
}

//==============================================================================Main==============================================================================

//=============================================================================Functions==========================================================================

// Load the data from the HSV courses file ;
void loadCourses(char *HSV, Vertex g)
{
    char *c[WORD_LENGTH];
    if (!strcmp(HSV, "\0"))
    {
        return;
    }

    c[0] = strtok(HSV, "#");
    int i = 0;

    while (c[i] != '\0')
    {
        i++;
        c[i] = strtok(NULL, "#"); // Keep saving data tell the end of the line ;
    }
    /*
    // strtok function inside String.h library that returns (char *) before the first occured charachter then and replace it with null then point to that null ;
    After first strtok

    Welcome'\0'to Data Structures and Algorithms'\0'
    ^        ^
    |        |
    c[0]   strtok

    */
    Vertex g1 = makeVertex(NULL, c[0]);
    if (i == 1)
    {
        makeDirectedEdge(g, g1);
        g1->count--; // Root does not conseder as count ;
        return;
    }

    for (int count = 1; count < i; count++)
    {
        Vertex g2 = BFS(g, c[count]);
        if (g2 == NULL)
        {
            g2 = makeVertex(NULL, c[count]);
            makeDirectedEdge(g, g2);
            g2->count--; // Root does not conseder as count ;
        }
        makeDirectedEdge(g2, g1);
    }
}

// Load the data from the HSV Buildings file ;
void loadBuildings(char *HSV, Vertex g)
{
    if (!strcmp(HSV, "\0"))
    {
        return;
    }
    char *c1 = NULL, *c2 = NULL, *c3 = NULL;

    // Exception handling inserting invalid data ;
    c1 = strtok(HSV, "#");
    if (c1 == NULL)
    {
        printf("\nInvalid input: %s  \n", HSV);
        return;
    }
    
    c2 = strtok(NULL, "#");
    if (c2 == NULL)
    {
        printf("\nInvalid input: %s  \n", HSV);
        return;
    }
    
    c3 = strtok(NULL, "#");
    if (c3 == NULL)
    {
        printf("\nInvalid input: %s  \n", HSV);
        return;
    }

    // Handling extra data ;
    if (strtok(NULL, "#") != NULL)
    {
        printf("\nInvalid input: %s  \n", HSV);
        return;
    }

    int weight = ConvertString(c3);
    
    Vertex g1 = BFS(g, c1);
    Vertex g2 = BFS(g, c2);

    if (!g1 && !g2)
    {
        g1 = makeVertex(NULL, c1);
        makeWeightedEdge(g, g1, -1); // Connect them to the root ( to avoid losing track of data ( both has no exist previously so need to connect them into somthing )) ;
    }

    else if (g1 == NULL)
    {
        g1 = makeVertex(NULL, c1);
    }
    if (g2 == NULL)
    {
        g2 = makeVertex(NULL, c2);
    }

    makeWeightedEdge(g1, g2, weight);
}

// Converting a String number into integer (used for insert from HSV file) ;
int ConvertString(char *str)
{
    int result = 0;
    for (int i = 0; str[i] != '\0'; ++i)
    {
        if (str[i] >= '0' && str[i] <= '9')
        {
            result = result * 10 + (str[i] - '0'); // increse 10 for each digit ;
        }
        else
            continue; // just ignore any thing that is not a number ;
    }
    return result;
}

//=========================================================================//Functions=========================================================================

/*

Input_Buildings.txt


Masri#A.Shaheen#70
Masri#Bamieh#39
Masri#KNH#155
Masri#Sh.Shaheen#78
Aggad#AL.Juraysi#71
Aggad#Alsadik#52
Aggad#KNH#43
A.Shaheen#Aggad#60
A.Shaheen#AL.Juraysi#89
A.Shaheen#Sh.Shaheen#40
Bamieh#Aggad#139
Bamieh#Sh.Shaheen#33
Bamieh#KNH#77
Alsadik#AL.Juraysi#57
KNH#AL.Juraysi#67
Sh.Shaheen#KNH#104
Sh.Shaheen#Alsadik#140
Sh.Shaheen#AL.Juraysi#120
Sh.Shaheen#Aggad#90

*/

/*

Input_Courses.txt


COMP133
COMP233
COMP2310#COMP133
COMP2421#COMP133
COMP333#COMP2421
COMP433#COMP333
ENCS2340#COMP133
ENCS2380#ENCS2340
ENCS3130#COMP133
ENCS3310#ENCS2380
ENCS3340#COMP233#COMP133
ENCS4320#COMP233#COMP133

*/