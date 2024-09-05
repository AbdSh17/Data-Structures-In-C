#include <stdio.h>
#include <stdlib.h>

typedef struct minHeapNode *minHeap;

#define HEAPSIZE 100

struct minHeapNode
{
    int current;
    int *array;
};

void initializeMinHeap(minHeap h)
{
    for (int i = 0; i < HEAPSIZE; i++)
    {
        h->array[i] = 0;
    }
}

minHeap makeEmptyMinHeap()
{
    minHeap h = (minHeap)malloc(sizeof(struct minHeapNode));
    h->current = 1;
    h->array = (int *)malloc(sizeof(int) * HEAPSIZE);
    initializeMinHeap(h);
    return h;
}

void insertMinHeap(int x, minHeap h)
{
    int current = h->current;
    if (h->current == 1)
    {
        h->array[current] = x;
        h->current++;
        return;
    }

    while (h->array[current / 2] > x && current != 1)
    {
        h->array[current] = h->array[current / 2];
        current /= 2;
    }

    h->array[current] = x;
    h->current++;
}

void deleteMinHeap(minHeap h)
{
    if (h->current == 1)
    {
        return;
    }

    int current = h->current;
    h->array[1] = h->array[current - 1];
    h->array[current - 1] = 0;
    h->current--;

    int i = 1;
    while (i < h->current / 2 && (h->array[i] > h->array[i * 2] || h->array[i] > h->array[i * 2 + 1]))
    {
        if (h->array[i * 2 + 1] > h->array[i * 2])
        {
            int temp = h->array[i];
            h->array[i] = h->array[i * 2];
            h->array[i * 2] = temp;

            i *= 2;
        }
        else
        {
            int temp = h->array[i];
            h->array[i] = h->array[i * 2 + 1];
            h->array[i * 2 + 1] = temp;

            i = i * 2 + 1;
        }
    }
}

void printMinHeap(minHeap h)
{
    printf("Index:  Value\n");
    for (int i = 1; i < h->current; i++)
    {
        printf("%-5d:  %-5d\n", i, h->array[i]);
    }
}
