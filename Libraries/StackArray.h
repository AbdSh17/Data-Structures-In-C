#include <stdio.h>
#include <stdlib.h>

typedef struct StackArrayNode *stackArray;

struct StackArrayNode
{
    int top;
    int *array;
    int maxSize;
};

stackArray makeEmptyStackArray(int size)
{
    stackArray s = (stackArray)malloc(sizeof(struct StackArrayNode));
    s->maxSize = size;
    s->array = (int *)malloc(sizeof(int) * size);
    s->top = 0;
    return s;
}

int isEmptyStackArray(stackArray s)
{
    return s->top == 0;
}

void pushStackArray(int x, stackArray s)
{
    if (s->top >= s->maxSize)
    {
        return;
    }

    s->array[s->top] = x;
    s->top++;
}

void popStackArray(stackArray s)
{
    if (!s->top)
    {
        return;
    }

    s->top--;
}

int getTopStackArray(stackArray s)
{
    return s->array[s->top - 1];
}

void printStackArray(stackArray s)
{
    if (!s->top)
    {
        return;
    }
    
    for (int i = s->top - 1; i >= 0; i--)
    {
        printf("%d  ", s->array[i]);
    }
}