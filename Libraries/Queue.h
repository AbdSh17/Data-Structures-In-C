#include <stdio.h>
#include <stdlib.h>

typedef struct QueueNode *queue;

struct QueueNode
{
    int data;
    queue back;
    queue next;
};

queue makeEmptyQueue(queue q)
{
    q = (queue)malloc(sizeof(struct QueueNode));
    q->next = NULL;
    q->back = q;
    q->data = -1;
    return q;
}

int isEmptyQueue(queue q)
{
    return q->next == NULL;
}

void enqueue(int x, queue q)
{
    if (!q)
    {
        return;
    }

    queue q1 = makeEmptyQueue(NULL);
    q1->data = x;
    q1->back = q;

    q->back->next = q1;
    q->back = q1;
    q1->next = NULL;
}

void dequeue(queue q)
{
    if (!q || isEmptyQueue(q))
    {
        return;
    }

    queue temp = q->next;
    q->next = q->next->next;
    free(temp);
    if (isEmptyQueue(q))
    {
        q->back = q;
    }
}

queue getFront(queue q)
{
    if (!q)
    {
        return NULL;
    }

    return q->next;
}

void printQueue(queue q)
{
    queue save = makeEmptyQueue(NULL);
    while (!isEmptyQueue(q))
    {
        enqueue(getFront(q)->data, save);
        printf("%d  ", getFront(q)->data);
        dequeue(q);
    }
    while (!isEmptyQueue(save))
    {
        enqueue(getFront(save)->data, q);
        dequeue(save);
    }
    free(save);
}