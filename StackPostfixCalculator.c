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
int isOperationInfex(char);
void printArray(char[]);
int power(char);
int priority(char, char);
void postFixConverter(char[], int);
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
    char c1[30] = "(a+(b*c))+(((d*e)+f)*g)" ;
    int size = sizeof(c1) / sizeof(c1[0]);
    postFixConverter(c1 , size);
    printf("\n%d  ", postFix(c));
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

void postFixConverter(char c1 [] , int size){
    stack s = creatStack();
    char c2[size];
    int i = 0;
    int j = 0;
    while (c1[i] != '\0')
    {
        // if it's not an operation drop it directly ;
        if(!isOperationInfex(c1[i])){
            c2[j] = c1[i];
            j++;
        }
        // if it was a close Parentheses drop and pop it till the open Parentheses ;
        else if(c1[i] == ')'){
            while (getTop(s) != '(')
            {
                c2[j] = getTop(s);
                pop(s);
                j++;
            }
            pop(s);
        }
        // if it has the priority push it into the stack ;
        else if(priority(c1[i] , getTop(s))){
            push(c1[i], s);
        }
        // if it doesn't has a priority drop the previous operation and push it into the stack
        else{
            c2[j] = getTop(s);
            pop(s);
            push(c1[i], s);
            j++;
        }
        i++;
    }
    //to close the String
    c2[j] = '\0';
    i = 0;
    //Drop the remain in the stack
    while (!isEmpty(s))
    {
        c2[j] = getTop(s);
        pop(s);
        j++;
    }
    c2[j] = '\0';
    printArray(c2);
}

int isOperationInfex(char c1){
    return (c1 == '+' || c1 == '-' || c1 == '*' || c1 == '/' || c1 == '^' || c1 == '(' || c1 == ')') ? 1 : 0;
}

void printArray(char c [] ){
    int i = 0;
    while (c[i] != '\0')
    {
        printf("%c  ", c[i]);
        i++;
    }
}
int priority(char c1 ,char c2){
    //if it was on the top don't give it priority
    if(c2 == '(')
        return 1;
    //decide if the power has a priority or not
    if(power(c1) <= power(c2))
    return 0;
    return 1;
}
int power(char c) {
    int operation = 0;
    switch (c) {
        case '(':
            operation = 4;
            break;
        case '^':
            operation = 3;
            break;
        case '*':
        case '/':
            operation = 2;
            break;
        case '+':
        case '-':
            operation = 1;
            break;
        default:
            operation = 0;
    }
    return operation;
}

