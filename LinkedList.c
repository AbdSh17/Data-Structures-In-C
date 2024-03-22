#include <stdio.h>
#include <stdlib.h>
typedef struct node* list;
struct node {

    int data;
    list next;
    list previous;
    list track;
};

void reverseLinkedList(struct node *);
void Delete(int, struct node *);
void insert(int, list);
int recursionDisjoint(list, list);
int isLast(list);
void deleteList(list);
void concat(list , list );
void printList(struct node *) ;
void removeDuplicated(struct node *);
int iterationDisjoint(list, list);
list find(int, list);
void sortArray(int[], int);
int getMost(int[], int);
void sortList(list);
int size(list);
void deleteNoData(list);
list getCommon(list, list);
list makeEmpty(list l) {
    if (l != NULL) {
        deleteList(l);
    }
    l = (list)malloc(sizeof(struct node));
    if (l == NULL)
        printf("No space in the memory");
    l->next = NULL;
    l->previous = NULL;
    l->track = l;
    return l;
}
//==================================================================main================================================================
int main() {
    int array []= {40, 756, 2, 10, 9, 409, 33};
    int size = sizeof(array) / sizeof(array[0]);
    sortArray(array, size);
    printf("The sorted array is:  ");
    for (int i = 0; i < size; i++)
    {
        printf("%d  ", array[i]);
    }
    printf("\n");

    list s1 = makeEmpty(NULL);
    list s2 = makeEmpty(NULL);

    insert(40, s1);
    insert(10, s1);
    insert(20, s1);
    insert(10, s1);
    insert(30, s1);
    insert(30, s1);
    insert(40, s1);
    insert(40, s1);
    insert(45, s1);
    insert(20, s1);
    insert(40, s1);
    sortList(s1);

    insert(15, s2);
    insert(25, s2);
    insert(25, s2);
    insert(45, s2);
    insert(35, s2);
    insert(35, s2);
    insert(35, s2);
    insert(45, s2);
    insert(45, s2);
    insert(45, s2);
    insert(45, s2);

    removeDuplicated(s1);
    printf("S1 after sorting and removing duplicated  ");
    printList(s1);
    printf("\n");
    removeDuplicated(s2);
    printf("S2 after sorting and removing duplicated  ");
    printList(s2);
    printf("\n%d\n", iterationDisjoint(s2, s1));
    printf("%d\n", recursionDisjoint(s1, s2));
    reverseLinkedList(s1);
    printf("S1 reversed  ");
    printList(s1);
    printf("\n");
    reverseLinkedList(s2);
    printf("S2 reversed  ");
    printList(s2);

    list l1 = makeEmpty(NULL);
    list l2 = makeEmpty(NULL);
    printf("\n=========================================\n");
    insert(1, l1);
    insert(2, l1);
    insert(3, l1);
    insert(4, l1);
    insert(5, l1);
    insert(6, l1);
    insert(7, l1);
    insert(8, l1);

    insert(10, l2);
    insert(20, l2);
    insert(30, l2);
    insert(40, l2);
    insert(50, l2);
    insert(60, l2);
    insert(70, l2);
    insert(5, l2);
    insert(6, l2);
    insert(7, l2);
    insert(8, l2);

    printf("the first common digit is : %d  \n", getCommon(l1,l2)->data);
    concat(s2, s1);
    printList(s2);

    return 0;
}
//=================================================================main===============================================================

//===============================================================functions==============================================================
void sortArray(int values[] , int size){
    struct node *s[10] ;
    struct node *p[10] ;
    for(int i=0 ; i<=9 ; i++){
        s[i] = makeEmpty(NULL);
        p[i] = NULL ;
    }
    int n=1 , m=10 , most = getMost(values , size);
    for(int i=0 ; i<most ; i++){
        for(int i=0 ; i<size ; i++){
            int val = (values[i]/n) % m;
           insert(values[i], s[val]);
            p[val] = s[val]->next ;
        }
            int i=0 , k=0;
            while(i < size) {
                    if(p[k] != NULL){
                         values[i] = p[k]->data;
                            i++;
                    if(p[k]->next != NULL){
                        p[k] = p[k]->next ;
                        continue;
                     }
                    }
                    k++ ;
            }
            n*=10  ;

            for(int i=0 ; i<=9 ; i++){
                deleteList(s[i]); // as long as the loop is constant so it will take O(9n) which is O(n) ;
                s[i] = makeEmpty(NULL);
                p[i] = NULL;
            }
        }
}

void sortList(list l){
    int listSize = size(l);
    int *values = (int*)malloc(listSize * sizeof(int));
    if(values == NULL){
        printf("Array allocation failed!");
    }
    list p1 = l->next;
    for (int i = 0; i < listSize && p1 != NULL; i++ , p1 = p1->next){
        values[i] = p1->data;
    }
    list p2 = l->next;
    sortArray(values, listSize);
    for (int i = 0; i < listSize && p2 !=NULL; i++ , p2 = p2->next)
    {
        p2->data = values[i];
    }
}
/*
Example:
          1 2 3 4 5 6 7 8 9
            |
10 20 30 40 |
Example:
1 2 3 4 5 6 7 8 9
          |
 10 20 30 |
Example::
    1 2 3 4 5 6 7 8 9
            |
10 20 30 40 |
*/
list getCommon(list l1 , list l2){ 
    if( l1 == NULL || l2 == NULL || isEmpty(l1)  || isEmpty(l2) ){
        printf("funny ?");
        return NULL;
    }
    int size1 = size(l1);
    int totalSize = size(l1) - size(l2);
        list p1 = l1->next;
        list p2 = l2->next;
        if (totalSize > 0)
        {
            for (int i = 0; i < totalSize; i++)
            {
                p1 = p1->next;
            }
    }
    else if(totalSize < 0){
        for (int i = 0; i < totalSize * -1; i++)
        {
            p2 = p2->next;
        }
    }
    
    for (int i = 0; i < size1; i++)
    {
        if(p2->data == p1->data)
            return p2;
        p1 = p1->next;
        p2 = p2->next;
    }
    printf("no match");
    return NULL;
}

void reverseLinkedList(struct node *s){
    if(s == NULL){
        printf("funny ?");
        close(0);
    }
    list p1 = s->next;
    if(p1 == NULL)
        printf("Empty List");
    s->next = s->track;
    p1 = s->track;
    list p2 = s;
    while(p1->previous != s){
        p1->next = p1->previous;
        p1->previous = p2;
        p1 = p1->next;
        p2 = p2->next;
    }
    p1->next = NULL ;
    p1->previous = p2;
}

void removeDuplicated(list s1) {
    if(s1 == NULL || isEmpty(s1)){
        printf("funny ?");
        close(0);
    }
      list p = s1->next;
    while (p != NULL && p->next != NULL)
    {
        list p1 = p->next;
        if(p->data == p->next->data){
            deleteNoData(p);
        }
        p = p1;
    }
}

int iterationDisjoint(list s1, list s2){
    if (s1 == NULL || s2 == NULL)
        return 1;

    list s3 = s1;
    list s4 = s2;
    while (s3->next != NULL && s4->next != NULL)
    {
       if (s3->next->data == s4->next->data)
        return 0;
        if(s3->next->data < s4->next->data){
            s3 = s3->next;
            continue;
        }
            s4 = s4->next;
    }
    return 1;
}

int recursionDisjoint(list s1, list s2) {
    if (s1 == NULL || s2 == NULL)
        return 1;

    if (s1->next == NULL || s2->next == NULL)
        return 1;

    if (s1->next->data == s2->next->data)
        return 0;

    if(s1->next->data < s2->next->data)
        return recursionDisjoint(s1->next, s2);

    if (s1->next->data > s2->next->data)
        return recursionDisjoint(s1, s2->next);
    else
        return recursionDisjoint(s1->next , s2->next);
}


void concat(list s1, list s2) {
    if(s1 == NULL || s2 == NULL || isEmpty(s1) || isEmpty(s2) ){
        printf("funny ?");
        close(0);
    }
    list tape = s1;
    while (tape->next != NULL) {
        tape = tape->next;
    }
    tape->next = s2->next;
    free(s2);
}

list merge(list s1 , list s2){
    list p1 
}

int getMost(int array[] , int size){
    int max = array[0] ;
        for(int i=1 ; i<size ; i++){
            if(max < array[i])
                max = array[i] ;
        }
        int count = 0;
        while(max != 0 ){
            max /= 10 ;
            count++ ;
        }
        return count ;
}
//===============================================================functions==============================================================

//===============================================================LS library==============================================================
void insert(int x, list l) {
    list temp;
    temp = (list)malloc(sizeof(struct node));
    l->track->next = temp;
    temp->previous = l->track;
    l->track = temp;
    temp->next = NULL;
    temp->data = x;
};

void deleteByIndex(list l , int index){
    list p = l->next;
    for (int i = 0; i < index - 1; i++)
    {
        p = p->next;
    }
    Delete(p);
}

int isEmpty(list l) {
    return l->next == NULL;
}

int isLast(list p) {
    return p->next == NULL;
}


list find(int x, list l) {

    list p = l->next;

    while (p != NULL && p->data != x)
        p = p->next;
    return p;

};

list findPrevious(int x, list l) {
    return find(x, l)->previous;
}

void Delete(int x, list l) {
    list p;
    list temp;

    p = findPrevious(x, l);
    if (!isLast(p)) {
        temp = p->next;
        p->next = temp->next;
        if(!isLast(temp)){
            temp->next->previous = temp->previous;
        }
        else if(isLast(temp)){
            l->track = temp->previous;
        }
        free(temp);
    }
        
}

void deleteNoData(list l) {
    list p;
    list temp;

    p = l->previous;
    if (!isLast(p)) {
        temp = p->next;
        p->next = temp->next;
        if(!isLast(temp)){
            temp->next->previous = temp->previous;
        }
        else if(isLast(temp)){
            l->track = temp->previous;
        }
        free(temp);
    }
        
}

void deleteList(list l) {
    list p = l;
    while (!isLast(p))
    {
        list temp = p;
        p = temp->next;
        free(temp);
    }
}

void printList(list l) {
    list p = l->next;

    if (l == NULL)
        printf("there's no list");
    if (p == NULL)
        printf("the list is empty");
    while (p != NULL) {
        printf("%d  ", p->data);
        p = p->next;
    }
}

int size(list l) {
    list p = l->next;
    int count = 0;

    while (p != NULL) {
        count++;
        p = p->next;
    }
    return count;
}
//===============================================================LS library==============================================================
// 
