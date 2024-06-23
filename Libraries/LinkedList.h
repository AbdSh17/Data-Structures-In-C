#include <stdio.h>
#include <stdlib.h>

typedef struct LinkedList *list;

struct LinkedList
{
    list next ;
    list previous;
    list back;
    int data;
};

list makeEmptyList(list);
void insertLast(int, list);
void insertFirst(int, list);
void printList(list);
list findList(int, list);
void deleteList(int, list);

list makeEmptyList(list l)
{
    l = (list)malloc(sizeof(struct LinkedList));
    l->back = l ;
    l->next = NULL ;
    l->previous = NULL;
    l->data = 0 ;
}

void insertLast(int x, list l)
{
    list l1 = makeEmptyList(NULL);
    l1->data = x ;

    l->back->next = l1;
    l1->previous = l->back;
    l->back = l1;
    l1->back = l;
}

void insertFirst(int x, list l)
{
    if (l->next == NULL)
    {
        insertLast(x, l);
        return ;
    }

    list l1 = makeEmptyList(NULL);
    l1->data = x ;

    l1->previous = l ;
    l1->next = l->next;
    l1->next->previous = l1;
    l->next = l1;
    l1->back = l ;
}

void printList(list l)
{
    list p = l->next ;
    while (p != NULL)
    {
        printf("%d  ", p->data);
        p = p->next ;
    }
    
}

list findList(int x, list l)
{
    list p = l->next ;
    while (p != NULL && p->data != x)
    {
        p = p->next ;
    }

    return p ;
    
}

void deleteList(int x, list l)
{
    list d = findList(x, l);

    if(d->next != NULL)
        d->next->previous = d->previous ;
    d->previous->next = d->next ;
    free(d);
}
