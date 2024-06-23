#include <stdio.h>
#include <stdlib.h>

typedef struct stackNode *stack;

struct stackNode
{
    int data;
    stack next;
};

stack makeEmptyStack(stack s)
{
    s = (stack)malloc(sizeof(struct stackNode));
    s->next = NULL;
    s->data = -1;
    return s;
}

int isEmptyStack(stack s)
{
    return s->next == NULL;
}

void push(int x, stack s)
{
    if (!s)
    {
        return;
    }

    stack s1 = makeEmptyStack(NULL);
    s1->data = x;

    stack temp = s->next;
    s1->next = temp;
    s->next = s1;
}

void pop(stack s)
{
    if (!s || isEmptyStack(s))
    {
        return;
    }

    stack temp = s->next;
    s->next = s->next->next;
    free(temp);
}

stack getTop(stack s)
{
    if (!s)
    {
        return NULL;
    }

    return s->next;
}

void printStack(stack s)
{
    stack save = makeEmptyStack(NULL);

    while (!isEmptyStack(s))
    {
        push(getTop(s)->data, save);
        printf("%d  ", getTop(s)->data);
        pop(s);
    }

    while (!isEmptyStack(save))
    {
        push(getTop(save)->data, s);
        pop(save);
    }
    free(save);
}
