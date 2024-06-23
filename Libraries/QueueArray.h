#include <stdio.h>
#include <stdlib.h>

typedef struct QueueArrayNode *queueArray;


struct QueueArrayNode
{
    int rear;
    int front;
    int capacity;
    int size;
    int *array;
};

queueArray makeEmptyQueueArray(int capacity)
{
    queueArray q = (queueArray)malloc(sizeof(struct QueueArrayNode));
    q->rear = 0;
    q->front = 1;
    q->size = 0;
    q->capacity = capacity;
    q->array = (int *)malloc(sizeof(int) * q->capacity);
    return q;
}

int isFull(queueArray q)
{
    return q->capacity == q->size;
}

int isEmpty(queueArray q)
{
    return q->size == 0;
}

int succ(int value, queueArray q)
{
   return (++value == q->capacity) ? 0 : value;
}

void enqueueArray(int x, queueArray q)
{
    if (isFull(q))
    {
        printf("Queue is Full\n");
        return;
    }

    q->size++;
    q->rear = succ(q->rear, q);
    q->array[q->rear] = x;
}

void dequeueArray(queueArray q)
{
    if (isEmpty(q))
    {
        printf("Empty Queue");
        return;
    }

    q->size--;
    q->front = succ(q->front, q);
}

int getFront(queueArray q)
{
    if (isEmpty(q))
    {
        printf("Empty Queue");
        return -1;
    }
    
    return q->array[q->front];
}