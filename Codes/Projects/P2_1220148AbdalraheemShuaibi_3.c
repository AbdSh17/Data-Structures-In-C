// Input File: input.txt ;
// output File: output.txt ;

// StdName: Abdlaraheen Shuaibi ;
// StdNum: 1220148 ;
// SectionNum: 3 ;

// you can find project Error codes below you can take a look ;

//=====================================Project description=====================================
/*
.This is a university project, data structures and algorithims (COMP2421).
.the projects is an implemantation of stack and queue

.this is a simple simulation of undo (cntrl-z) and redo (cntrl-y) using consol
.this project reads from file named output/input.txt

*/

//=====================================Project guideline=====================================
/*

1- When the user INSERT the program will give the user 4 option either insert before or after a word (which will search for its first occurance),
INSERT based on index or insert last as an individual word, However in the first two casses if the user entered a word that dose not exist or
Enter it will automatically INSERT it at the last individually ;

2- if you undo anything then INSERT/REMOVE it will automatically emptying Redo stack ( you can try it by yourself on any text editor :) ) ;

3- the project support multiple line on the text field so feel free to write anything (: ;

4- when inserting more than one word then undo each word will go with its previous space ;

5- Can't INSERT a word like '_word' || 'word_', and the first word will always

6- the most number of charachters for one word is 50, the most number for one line on the file is 50 and the most number for the whole file is 500 ;

*/
//=====================================/Project guideline=====================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REMOVE 2
#define INSERT 1

typedef struct node1 *queue; // Queue typedef ;
typedef struct node2 *stack; // Stack typedef ;
typedef queue ptrToQueue;    // Queue typedef
typedef stack ptrToStack;    // Stack typedef ;

// Queue struct ;
struct node1
{
    queue next;      // Next node ;
    queue back;      // To keep tracking last added node ;
    char qToken[50]; // The name that stored inside the node ;
};

// Stack node
struct node2
{
    stack next;          // Next node ;
    char stackToken[50]; // The name that stored inside the node ;
    int index;           // Index of the first string charchter in the array, from 1 - strlen(array) ;
    int type;            // Type of the pushed word (Remove and Insert) ;
};

//====================================Queuee====================================

queue makeEmptyQueue(queue);
int isEmptyQueue(queue);
void enqueue(char *, queue);
void dequeue(queue);
ptrToQueue getFront(queue);
void disposeQueue(queue);

//====================================/Queue====================================

//====================================Stack====================================

stack makeEmptyStack(stack);
int isEmptyStack(stack);
void push(char *, stack, int, int);
void pop(stack);
ptrToStack getTop(stack);
ptrToStack popwithValue(stack);
ptrToStack copySatck(ptrToStack);
void pushWithValue(stack, ptrToStack);
void emptyingStack(stack);
void printS(stack);

//====================================/Stack====================================

//====================================Functions====================================

void inserQText(queue, char *, int);
void insertToQ(char *, queue, int);
void insertQ_Stack(queue, stack, int, int);
void printToFile(FILE *, char *);
int deleteWord(char *, char *);
void deleteWordIndex(char *, char *, int);
void insertWord(char *, char *, int);

//====================================/Functions====================================

//==============================================================================Main==============================================================================

int main()
{

    int *x = (int *)malloc(sizeof(int) * 5);
    int y[] = {1,3,4,5,6};

    free(x);
    free(y);

    FILE *in = NULL;
    in = fopen("output/input.txt", "r");
    if (in == NULL)
    {
        printf("Fatal 02: Failed to load the file, please check the file name was: input.txt ");
        exit(EXIT_FAILURE);
        exit(0);
    }

    stack undo = makeEmptyStack(NULL);
    stack redo = makeEmptyStack(NULL);
    int operation = 0;
    FILE *out = NULL;
    printf("\nEnter what operation you want based on the index\n1-Load the input file.\n2-Print the loaded text.\n3-Insert a word to the text.\n4-Remove a word from the text.\n5-Perform Undo operation.\n6-Perform Redo operation.\n7-Print the Undo Stack and the Redo stack.\n8-Save to the output file.\n9-Exit.\n");
    scanf("%d", &operation);
    getchar(); // To catch the '\n' that printed by fgets ;

    // File line, Loaded Text,          Latest text ;
    char c[50], orignalText[500] = "", text[500];
    while (operation != 9)
    {
        char insert[50], word[50], *search;
        queue q = makeEmptyQueue(NULL);
        int i = 0, index = 0, op = 0, flag = 1;
        switch (operation)
        {
        case 1:
            while (fgets(c, sizeof(c), in) != NULL)
            {
                strcat(orignalText, c); // Save the loaded information from file allowing the user to check them (save them while load the file);
            }
            strncpy(text, orignalText, sizeof(text));
            break;
        case 2:
            printf("%s", orignalText); // Just print the loaded information from the file ( any thing added by the terminal will not be concedard );
            break;
        case 3:
            printf("\nEnter a sentence:  ");
            fgets(insert, sizeof(insert), stdin);
            insert[strlen(insert) - 1] = '\0';
            if (insert[0] == '\0')
            {
                break;
            }
            printf("\nEnter the operation\n1-Insert before\n2-Insert after\n3-Insert based on index\n4-Insert last as individual word\n");
            scanf("%d", &op);
            getchar();
            switch (op)
            {
            case 1:
                printf("\nEnter What to insert before, if you wnat to insert last just skip by pressing enter:  ");
                fgets(word, sizeof(word), stdin);
                word[strlen(word) - 1] = '\0';
                search = strstr(text, word);           // function inside String.h library that returns (char *) to the entered word ;
                if (search == NULL || word[i] == '\0') // Three cases for inserting last ;
                {
                    index = -1; // if inserted last let the index be -1 ;
                }

                else
                {
                    index = strlen(text) - strlen(search) + 1; // the length from 1 - strlen(text) ;
                }
                break;
            case 2:
                printf("\nEnter What to insert after, if you wnat to insert last just skip by pressing enter:  ");
                fgets(word, sizeof(word), stdin);
                word[strlen(word) - 1] = '\0';
                search = strstr(text, word); // function inside String.h library that returns (char *) to the entered word ;
                /*
                search for ructur ;
                Welcome to Data Structures\n and algorithms'\0' ;
                ^                 ^
                |                 |
               text             search
                */
                if (search == NULL || word[i] == '\0') // Three cases for inserting last ;
                {
                    index = -1; // if inserted last let the index be -1 ;
                }

                else
                {
                    index = strlen(text) - strlen(search) + 1 + strlen(word); // the length from 1 - strlen(text) ;
                }
                break;
            case 3:
                printf("\nEnter the index you want:  ");
                scanf("%d", &index);
                if (index < 1)
                {
                    index = 1;
                }
                else if ((size_t)index > strlen(text))
                {
                    index = -1;
                }
                break;
            case 4:
                index = -1;
                break;
            default:
                printf("\nPlease just enter an existed operation -_-\n");
                flag = 0;
                break;
            }
            if (!flag)
            {
                break;
            }

            insertToQ(insert, q, index);           // Insert the entered words to queue ;
            insertQ_Stack(q, undo, INSERT, index); // Push queue nodes to stack ;
            inserQText(q, text, index);            // Insert queue nodes ;
            disposeQueue(q);                       // Free the q (Expect to send just the head but to make very sure there's no reamin nodes idk) ;
            emptyingStack(redo);                   // Make the redo stack empty after any insert operation as cleared above;
            break;
        case 4:
            printf("\nEnter the word:\n");
            fgets(word, sizeof(word), stdin);
            word[strlen(word) - 1] = '\0';
            if (word[0] == '\0')
            {
                break; // Handle pressing enter by the user case ;
            }

            index = deleteWord(text, word) + 1; // the length from 1 - strlen(text) ;
            if (index == -1)
            {
                break; // if Delete word return -2 (which is handeled case inside delteword) ;
            }
            push(word, undo, REMOVE, index);
            emptyingStack(redo); // Make the redo stack empty after any rempve operation as cleared above ;

            break;
        case 5:
            if (isEmptyStack(undo))
            {
                break;
            }
            // INSERT then remove it, REMOVE then insert it ;
            if (getTop(undo)->type == INSERT)
            {
                deleteWordIndex(text, getTop(undo)->stackToken, getTop(undo)->index); // Delete the word by index (no first occurance cuse we have specfied word) ;
            }
            else if (getTop(undo)->type == REMOVE)
            {
                insertWord(text, getTop(undo)->stackToken, getTop(undo)->index); // Insert the word to it's previous index ;
            }
            pushWithValue(redo, popwithValue(undo)); // Push the top of undo to redo ;
            break;
        case 6:
            if (isEmptyStack(redo))
            {
                break;
            }
            // INSERT then insert it, REMOVE then remove it ;
            if (getTop(redo)->type == INSERT)
            {
                insertWord(text, getTop(redo)->stackToken, getTop(redo)->index);
            }
            else if (getTop(redo)->type == REMOVE)
            {
                deleteWord(text, getTop(redo)->stackToken);
            }
            pushWithValue(undo, popwithValue(redo)); // Push the top of redo to undo ;
            break;
        case 7:
            printf("\n==================Undo===================\n\n");
            printS(undo);
            printf("\n==================Redo===================\n\n");
            printS(redo);
            break;
        case 8:
            printToFile(out, text);
            emptyingStack(undo);
            emptyingStack(redo);
            break;
        case 9:
            break;
        case 11:
            printf("%s", text);
            break;
        default:
            printf("Wrong operation , please enter a number that is in the choices\n"); // Just enter the right one please ):
            break;
        }
        printf("\nEnter what operation you want based on the index\n1-Load the input file.\n2-Print the loaded text.\n3-Insert a word to the text.\n4-Remove a word from the text.\n5-Perform Undo operation.\n6-Perform Redo operation.\n7-Print the Undo Stack and the Redo stack.\n8-Save to the output file.\n9-Exit.\n");
        scanf("%d", &operation);
        getchar();
    }
    fclose(in);
    return 0;
}

//==============================================================================/Main==============================================================================

//==============================================================================Functions==============================================================================

// Insert the queue to the text (will break the queue) ;
void inserQText(queue q, char *text, int index)
{

    if (q == NULL || text[0] == '\0')
    {
        printf("Error 01:  Can't insert to the text,\tExpected: Null head");
        return;
    }

    else if (getFront(q) == NULL)
    {
        printf("Error 02:  Can't insert to the text,\tExpected: Empty queue");
        return;
    }

    char *c = getFront(q)->qToken;
    dequeue(q);
    // Save each node in the queue in c ;
    while (!isEmptyQueue(q))
    {
        strcat(c, getFront(q)->qToken);
        dequeue(q);
    }
    // insert c (which expected to be combained queue nodes) to the text ;
    insertWord(text, c, index);
}

// Push the queue to the stack (will Keep queue safe) ;
void insertQ_Stack(queue q, stack s, int type, int index)
{
    if (q == NULL || s == NULL)
    {
        printf("Error 01:  Can't insert to the stack,\tExpected: Null head");
        return;
    }

    else if (getFront(q) == NULL)
    {
        printf("Error 02:  Can't insert to the stack,\tExpected: Empty queue");
        return;
    }

    queue save = makeEmptyQueue(NULL); // Save queue to try not losing its data ;

    // Index for each will be -1 ;
    if (index == -1)
    {
        while (!isEmptyQueue(q))
        {
            push(getFront(q)->qToken, s, type, index);
            enqueue(getFront(q)->qToken, save);
            dequeue(q);
        }
        // Return the info to the queue
        while (!isEmptyQueue(save))
        {
            enqueue(getFront(save)->qToken, q);
            dequeue(save);
        }
    }

    // Index will keep changing ;
    else
    {
        while (!isEmptyQueue(q))
        {
            push(getFront(q)->qToken, s, type, index);
            enqueue(getFront(q)->qToken, save);
            dequeue(q);
            index += strlen(getTop(s)->stackToken); // increase index for the next word ;
        }
        // Return the info to the queue
        while (!isEmptyQueue(save))
        {
            enqueue(getFront(save)->qToken, q);
            dequeue(save);
        }
    }
}

// To insert the text to the queue according to project requirements ;
void insertToQ(char *token, queue q, int index)
{
    if (q == NULL)
    {
        printf("Error 01:  Can't insert to the stack,\tExpected: Null head");
        return;
    }
    char space = token[strlen(token) - 1];
    char *c[50], tokenArr[50];
    int i = 0, count = 0;
    strncpy(tokenArr, token, sizeof(tokenArr));

    c[0] = strtok(tokenArr, " "); // function inside String.h library that returns (char *) before the first occured charachter then and replace it with null then point to that null ;

    /*

    After first strtok

    Welcome'\0'to Data Structures and Algorithms'\0'
    ^        ^
    |        |
    c[0]   strtok

    */
    while (c[i] != '\0') // loop until c[i] point to '\0' ;
    {
        i++;
        c[i] = strtok(NULL, " ");
    }
    if (space == ' ')
    {
        insertWord(c[i - 1], " ", strlen(c[i - 1]) + 1);
    }

    // hello i am abd shuaibi
    //  Enqueue each woed in a new node ;
    while (count < i)
    {
        ptrToQueue p = (ptrToQueue)malloc(sizeof(struct node1));
        if (count != 0 || index == -1 || token[0] == ' ')
        {
            p->qToken[0] = ' ';                                  // Make sure to return the space with each word (expect first one) ( it's tokened based on ' ' so i can guarantee it has space before it );
            strncpy(&p->qToken[1], c[count], sizeof(p->qToken)); // First char is ' ' so pointed to the next char ;
        }
        else
        {
            strncpy(p->qToken, c[count], sizeof(p->qToken));
        }
        q->back->next = p;
        q->back = p;
        p->next = NULL;
        count++;
    }
}

// Print to output file (FILE Name: Output.txt) ;
void printToFile(FILE *out, char *c)
{
    out = fopen("output.txt", "w");
    if (out == NULL)
    {
        printf("Fatal 02: Failed to load the file , please check the file name was: output.txt ");
        exit(EXIT_FAILURE);
    }
    fprintf(out, "%s", c);
    fclose(out);
}

// Delete the first occurance word ;
int deleteWord(char *c, char *ch)
{
    char *c1, *c2;
    c1 = strstr(c, ch);
    if (c1 == NULL)
    {
        return -2;
    }
    int x = strlen(c) - strlen(c1);
    int y = strlen(ch);
    int count = 0;
    for (int i = 0; i < y; i++, count++)
    {
        c1[i] = '\0'; // Replace each charachter with null ;
    }

    c2 = &c1[count]; // point to the first next char ;
    /*
    delete ruc
    Welcome to Data St'\0''\0''\0'tures'\n'and Algorithms
                                  ^
                                  |
                                  c2
    */
    char c3[50], c4[50];
    strncpy(c3, c2, sizeof(c3));
    strncpy(c4, c, sizeof(c4));
    strcat(c4, c3);
    strncpy(c, c4, 500);

    return x;
}

// Exactly same as above put c1 point based on index not first occurance ;
void deleteWordIndex(char *c, char *ch, int index)
{
    char *c1, *c2;
    if (index == -1)
    {
        index = strlen(c) - strlen(ch) + 1;
    }
    index--;
    c1 = &c[index];
    int y = strlen(ch);
    int count = 0;
    for (int i = 0; i < y; i++, count++)
    {
        c1[i] = '\0';
    }

    c2 = &c1[count];
    char c3[50], c4[500];
    strncpy(c3, c2, sizeof(c3));
    strncpy(c4, c, sizeof(c4));
    strcat(c4, c3);
    strncpy(c, c4, 500);
}

// Insert a word based on index ;
void insertWord(char *c, char *ch, int index)
{

    if (index == -1)
    {
        strcat(c, ch);
        return;
    }
    index--; // To make index appropriate with charchters which start 0 - (strlen(text) - 1) while index is from 1 - strlen(text) ;
    int len = strlen(c);
    int amount = strlen(ch);
    int count = 0, count2 = 0;
    // Shifting each charachter based on the inserted word length
    for (int i = len - 1; i >= index; i--)
    {
        c[i + amount] = c[i];
        count++;
    }
    // So now after emptying some space (exactly like the inserted word length in the wanted index), we can replace the index with the inserted word ;
    for (int i = 0; i < amount; i++, index++)
    {
        c[index] = ch[i];
        count2++;
    }
}

//==============================================================================/Functions==============================================================================

//==============================================================================Queue==============================================================================

// Make empty queue head ;
queue makeEmptyQueue(queue q)
{
    if (q != NULL)
    {
        disposeQueue(q);
    }
    q = (queue)malloc(sizeof(struct node1));
    if (q == NULL)
    {
        printf("Fatal 01: Failed to add Queue,\tExpecting: Out Of Memory !");
        exit(EXIT_FAILURE);
    }
    q->back = q;
    q->next = NULL;
    return q;
}

// Dispose the queue
void disposeQueue(queue q)
{
    if (q == NULL)
    {
        printf("Error 01:  Can't Dispose queue,\tExpected: Null head");
        return;
    }

    while (!isEmptyQueue(q))
    {
        queue temp = q->next;
        q->next = q->next->next;
        free(temp);
    }
}

// Insert last to the queue
void enqueue(char *token, queue q)
{
    if (q == NULL)
    {
        printf("Error 01:  Can't insert to the queue,\tExpected: Null head");
        return;
    }

    ptrToQueue p = (ptrToQueue)malloc(sizeof(struct node1));
    if (p == NULL)
    {
        printf("Fatal 01: Failed to add Queue,\tExpecting: Out Of Memory !");
        exit(EXIT_FAILURE);
    }
    strncpy(p->qToken, token, sizeof(p->qToken));
    q->back->next = p;
    q->back = p;
    p->next = NULL;
}

// Remove the first inserted node ;
void dequeue(queue q)
{
    if (q == NULL)
    {
        printf("Error 01:  Can't delete from the queue,\tExpected: Null head");
        return;
    }

    if (isEmptyQueue(q))
    {
        printf("Error 02: Failed to delete from the queue,\tExpecting: Empty Queue");
        return;
    }
    ptrToQueue p = q->next;
    q->next = q->next->next;
    if (q->back == p)
    {
        q->back = q;
        q->next = NULL;
    }
    free(p);
}

// Boolean function to return if the queue is empty ;
int isEmptyQueue(queue q)
{
    if (q == NULL)
    {
        printf("Error 01:  Can't insert to the stack,\tExpected: Null head");
        return 0;
    }

    return q->next == NULL;
}

// Return pointer to queue front ;
ptrToQueue getFront(queue q)
{
    if (q == NULL)
    {
        printf("Error 01:  Can't get the front of the queue,\tExpected: Null queue");
        return NULL;
    }

    if (isEmptyQueue(q))
    {
        printf("Error 02: Failed to get front from the queue,\tExpecting: Empty Queue");
        return NULL;
    }
    return q->next;
}

//==============================================================================/Queue==============================================================================

//==============================================================================Stack==============================================================================

// Make empty stack head and return a pointer point to the head ;
stack makeEmptyStack(stack s)
{
    if (s->next != NULL)
    {
        // disposeQueue(q) ;
    }
    s = (stack)malloc(sizeof(struct node2));
    if (s == NULL)
    {
        printf("Fatal: Failed to add Stack,\tExpecting: Out Of Memory !");
        exit(EXIT_FAILURE);
    }
    s->next = NULL;
    return s;
}

// Boolean function to return if the stack is empty ;
int isEmptyStack(stack s)
{
    if (s == NULL)
    {
        printf("Error 01:  Can't return boolean function is empty,\tExpected: Null head");
        return 0;
    }

    return s->next == NULL;
}

// Insert fist to the stack
void push(char *token, stack s, int type, int index)
{
    if (s == NULL)
    {
        printf("Error 01: Failed to push %s to the Stack,\tExpecting: Null head", token);
        return;
    }
    ptrToStack p;
    p = (ptrToStack)malloc(sizeof(struct node2));
    if (p == NULL)
    {
        printf("Fatal 01: Failed to add to the Stack,\tExpecting: Out Of Memory !");
        exit(EXIT_FAILURE);
    }
    p->next = s->next;
    s->next = p;
    strncpy(p->stackToken, token, sizeof(p->stackToken));
    p->type = type;
    p->index = index;
}

// Insert first to the stack for a existed node ;
void pushWithValue(stack s, ptrToStack p)
{
    if (s == NULL)
    {
        printf("Error 01:  Can't push to the stack,\tExpected: Null head");
        return;
    }
    if (p == NULL)
    {
        printf("Error 03:  Can't return boolean function is empty,\tExpected: Null pointer");
        return;
    }
    p->next = getTop(s);
    s->next = p;
}

// Remove first from the stack ;
void pop(stack s)
{
    if (s == NULL)
    {
        printf("Error 01: Failed to pop the Stack,\tExpecting: Null head");
        return;
    }
    if (isEmptyStack(s))
    {
        printf("Error 02: Failed to pop the stack,\tExpecting: Empty Stack");
        return;
    }
    ptrToStack p = getTop(s);
    s->next = s->next->next;
    free(p);
}

// Remove first to the stack for a existed node ;
ptrToStack popwithValue(stack s)
{
    if (s == NULL)
    {
        printf("Error 01: Failed to pop the Stack,\tExpecting: Null head");
        return NULL;
    }
    if (isEmptyStack(s))
    {
        printf("Error 02: Failed to pop the stack,\tExpecting: Empty Stack");
        return NULL;
    }
    ptrToStack p = getTop(s);
    s->next = s->next->next;
    ptrToStack p1 = copySatck(p);
    free(p);
    return p1;
}

// Copy a node to new one ;
ptrToStack copySatck(ptrToStack p)
{
    if (p == NULL)
    {
        printf("Error 01:  Can't copy the stack,\tExpected: Null head");
        return NULL;
    }

    ptrToStack p1 = makeEmptyStack(NULL);
    p1->index = p->index;
    p1->type = p->type;
    strncpy(p1->stackToken, p->stackToken, sizeof(p->stackToken));
    return p1;
}

// Get the top of the stack ;
ptrToStack getTop(stack s)
{
    if (s == NULL)
    {
        printf("Error 01: Failed to get the top of the Stack,\tExpecting: Null head");
        return NULL;
    }

    return s->next;
}

// Make all stack node empty (exclude the head) ;
void emptyingStack(stack s)
{
    while (!isEmptyStack(s))
    {
        pop(s);
    }
}

// To print the stack ;
void printS(stack s)
{
    if (s == NULL)
    {
        printf("Error 01:  Can't print the stack,\tExpected: Null head");
        return;
    }
    stack s1 = makeEmptyStack(NULL);
    while (!isEmptyStack(s))
    {
        if (getTop(s)->type == INSERT)
        {
            printf("%-7s | Insert | %-3d\n", getTop(s)->stackToken, getTop(s)->index);
        }
        else if (getTop(s)->type == REMOVE)
        {
            printf("%-7s | Remove | %-3d\n", getTop(s)->stackToken, getTop(s)->index);
        }
        pushWithValue(s1, popwithValue(s));
    }
    while (!isEmptyStack(s1))
    {
        pushWithValue(s, popwithValue(s1));
    }
    free(s1);
}

//==============================================================================/Stack==============================================================================

//================================================Errors Codes================================================
/*
    Error 01: Usually happens when sending a null head to a function ;
    Error 02: Usually happens when sending a empty head ;
    Error 03: Usually happens when sending a pointer point to NULL to a function ;
*/

/*
    Fatal 01: Usually happens when failing to store a memory during infinite loop or full memory ;
    Fatal 02: Usually happens when failing to reach the File ;
*/