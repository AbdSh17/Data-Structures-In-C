#include <stdio.h>
#include <stdlib.h>

typedef struct node *tree;
typedef struct node1 *stack;
struct node
{
    int data;
    tree left;
    tree right;
};

struct node1
{
    int data;
    stack next;
};

tree insert(int, tree);
tree findTree(int, tree);
tree makeEmpty(tree);
tree findMin(tree);
tree findMax(tree);
tree findParentTree(int, tree);
void delete(int, tree);
void printTree(tree);
tree findTreeIteration(int, tree);
int isEmptyStack(stack);
void pop(stack);
void makeEmptyStack(stack);
void push(int, stack);
int getTop(stack);
stack creatStack();
tree zig(tree, tree, tree);
tree zag(tree, tree, tree);
//=============================================================================Main=============================================================================    

int main()
{
    tree t;
    t = insert(7, NULL);
    insert(6, t);
    insert(5, t);
    insert(4, t);
    insert(3, t);
    insert(2, t);
    insert(1, t);

       t = findTreeIteration(1, t);
       printf("\n\n");
       t = findTreeIteration(5, t);
       printf("%d  ", t->data);

       return 0;
}

//=============================================================================Main=============================================================================


//=============================================================================Tree=============================================================================

tree findTreeIteration(int x, tree t)
{

    stack s = creatStack();
    tree t1 = t;
    // tree t2 = t;
    while (t1 != NULL)
    {
        if (x > t1->data)
        {
            push(1, s);
            t1 = t1->right;
        }
        else if (x < t1->data)
        {
            push(2, s);
            t1 = t1->left;
        }
        else
            break;
    }
    while (!isEmptyStack(s))
    {
    
        tree t2 = findParentTree(t1->data, t);
        tree t3 = findParentTree(t2->data, t);
        if (getTop(s) == 1)
        {
            zig(t1, t2, t3);
        }
        else if (getTop(s) == 2)
        {
            zag(t1, t2, t3);
        }

        pop(s);
    }
    return t1;
}

tree zig(tree t1, tree parent, tree grand)
{
    parent->right = t1->left;
    t1->left = parent;
    if (grand != NULL)
    {
      if (grand->right->data == parent->data)
    {
        grand->right = t1;
    }
    else if (grand->left->data == parent->data)
    {
        grand->left = t1;
    }
    }
    return t1;
}

tree zag(tree t1, tree parent, tree grand)
{
    parent->left = t1->right;
    t1->right = parent;
    if (grand != NULL)
    {
      if ( (grand->right != NULL) && (grand->right->data == parent->data))
    {
        grand->right = t1;
    }
    else if ((grand->left != NULL) && (grand->left->data == parent->data))
    {
        grand->left = t1;
    }
    }
    return t1;
}

tree makeEmpty(tree t)
{
    if (t != NULL)
    {
        makeEmpty(t->right);
        makeEmpty(t->left);
        free(t);
    }
    return NULL;
}

tree insert(int x, tree t)
{
    if (t == NULL)
    {
        t = (tree)malloc(sizeof(struct node));
        if (t == NULL)
        {
            printf("Out of memory!");
        }
        else
        {
            t->data = x;
            t->left = t->right = NULL;
            return t;
        }
    } 
        else if (x > t->data)
        {
            t->right = insert(x, t->right);
        }
        else if (x < t->data)
        {
            t->left = insert(x, t->left);
        }
        return t;
    }

tree findTree(int x, tree t)
{
    if (t == NULL)
    {
        return NULL;
    }

    else if (x > t->data)
    {
        return findTree(x, t->right);
    }

    else if (x < t->data)
    {
        return findTree(x, t->left);
    }
    return t;
}

tree findParentTree(int x, tree t)
{
    if (t == NULL)
    {
        return NULL;
    }
    // if left or roigh is null will crash beacuse (t->null->data) is a null pointer ;
    else if( (t->left != NULL && t->left->data == x) || (t->right != NULL && t->right->data == x))
    {
        return t;
    }
    
    else if (x > t->data)
    {
        return findParentTree(x, t->right);
    }

    else if (x < t->data)
    {
        return findParentTree(x, t->left);
    }
    return NULL;
}

tree findMin(tree t)
{
    return (t->left == NULL) ? t : findMin(t->left);
}

tree findMax(tree t)
{
    return (t->right == NULL) ? t : findMax(t->right);
}

void delete(int x , tree t)
{
    tree t1 = findTree(x, t);
    if (!t1->left && !t1->right)
    {
        free(t1);
        return;
    }
    else if (!t1->left || !t1->right)
    {
        
        tree t2 = findParentTree(x, t);
        if (x > t2->data)
        {
            if (t1->right)
            {
                printf("%d  ", t2->data);
                t2->right = t1->right;
            }
            else
            {
                t2->right = t1->left;
                
            }
        }
        else if(x < t2->data)
        {
            if (t1->right)
            {
                t2->left = t1->right;
            }
            else
            {
                t2->left = t1->left;
            }
        }
        free(t1);
    }
    else
    {
        tree t2 = findMin(t1->right);
        t1->data = t2->data;
        free(t2);
    }
}

void printTree(tree t)
{
    if (t != NULL)
    {
        printTree(t->left);
        printf("%d  ", t->data);
        printTree(t->right);
    }
}
//=============================================================================Tree=============================================================================

//=============================================================================Stack=============================================================================

stack creatStack()
{
    stack s;
    s = (stack)malloc(sizeof(struct node));
    if(s == NULL)
        printf("The memory is Full");
    else
    {
        s->next = NULL;
        makeEmptyStack(s);
    }
    return s;
}

void makeEmptyStack(stack s){

    if(s == NULL)
        printf("The memory is Full");
    else{
        while(!isEmptyStack(s)){
            pop(s);
        }
    }
}

void pop(stack s)
{
    stack p = s->next;
    if (isEmptyStack(s))
    {
        return;
    }
    s->next = s->next->next;
    free(p);
  }

  int isEmptyStack(stack s)
  {
      return s->next == NULL;
  }

void push(int x, stack s)
  {
      stack p;
      p = (stack)malloc(sizeof(struct node1));
      if (p == NULL)
      {
          printf("Out of memory !");
          exit(EXIT_FAILURE);
      }
      p->next = s->next;
      s->next = p;
      p->data = x;
  }

  int getTop(stack s)
  {
    if (isEmptyStack(s))
    {
        printf("Can't get the top empty list ");
        return 0;
    }
    
      return s->next->data;
  }