#include <stdio.h>
#include <stdlib.h>

typedef struct node *ptrToNode;
typedef ptrToNode stack;
struct node
{
    int element;
    ptrToNode next;
};

int isEmpty(stack);
stack creatStack();
void printStack(stack);
void makeEmpty(stack);
void pop(stack);
char getTop(stack);
void push(int, stack);
void DisposeStack(stack);
int isOperation(char);
int getRseult(int, int, char);
int postFix(char *);
int isEmpty(stack s){
    return s->next == NULL;
}

stack creatStack(){
    stack s;
    s = (ptrToNode)malloc(sizeof(struct node));
    if(s == NULL)
        printf("The memory is Full");
    else{
        s->next = NULL;
        makeEmpty(s);
    }
    return s;
}

void makeEmpty(stack s){

    if(s == NULL)
        printf("The memory is Full");
    else{
        while(!isEmpty(s)){
            pop(s);
        }
    }
}

void pop(stack s){
    ptrToNode p = s->next;
    if(isEmpty(s))
     printf("Empty stack");
    else{
        s->next = s->next->next;
        free(p);
    }
}

/*
    if(!isEmpty(s))
        return s->next->element;
        return 0;
*/
char getTop(stack s){
    return (!isEmpty(s)) ? s->next->element : 0;
}

void push(int x , stack s){
    ptrToNode p;
    p =  (ptrToNode)malloc(sizeof(struct node));
    if(p == NULL)
    printf("The memory is full");
    else{
         p->next = s->next;
        s->next = p;
        p->element = x;
    }
}

void DisposeStack( stack s ){
makeEmpty( s );
free( s );
}

void printStack(stack s){
    ptrToNode p = s->next;
    if (s->next == NULL || s == NULL)
    {
        printf("The list is empty");
    }
    else{
         while(p != NULL){
        printf("%c  ", p->element);
        p = p->next;
    }
    }
}
//=========================================main===========================================================
int main(){
    char c[30] = "1234+*+" ;

    printf("%d  ", postFix(c));
}
//=========================================main===========================================================

int postFix(char *c){
    stack s = creatStack();
    
    int i = 0;
    while (c[i] != '\0')
    {
        int x, y;
        if(isOperation(c[i])){
             x = getTop(s) ;
            pop(s);
             y = getTop(s);
            pop(s);
            push(getRseult(x, y, c[i]),s);
        }
       else if(c[i] >= '0' && c[i] <= '9')
            push(c[i]-'0', s);
        i++;
    }
    return getTop(s);
}

int getRseult(int c1 ,int c2 , char c3){
    switch (c3)
    {
    case '+':
        return c1 + c2 ;
    case '-':
        return c1 - c2 ;
    case '*':
        return c2 *  c1 ;
    case '/':
        return c1 / c2 ;
    default:
        printf("Wrong operation");
        break;
    }
    return 0;
}

int isOperation(char c){
    return (c == '+' || c == '-' || c == '*' || c == '/') ? 1 : 0;
}

/*
int getRseult(char c1 ,char c2 , char c3){
    switch (c3)
    {
    case '+':
        return c1 + c2 - 2 * '0';
    case '-':
        return c1 - c2 ;
    case '*':
        return ( (c2 - '0') *  (c1 - '0') );
    case '/':
        return ( (c1 - '0')  / (c2 - '0') );
    default:
        printf("Wrong operation");
        break;
    }
    return 0;
}

*/

