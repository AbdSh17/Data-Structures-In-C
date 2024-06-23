#include <stdio.h>
#include <stdlib.h>

typedef struct BSTNode *bst;

struct BSTNode
{
    int data;
    bst left;
    bst right;
    int count;
};

bst insertTree(int x, bst t)
{
    if (t == NULL)
    {
        bst t = (bst)malloc(sizeof(struct BSTNode));
        t->data = x;
        t->left = NULL;
        t->right = NULL;
        t->count = 1;
        return t;
    }

    else if (x > t->data)
    {
        t->right = insertTree(x, t->right);
    }

    else if (x < t->data)
    {
        t->left = insertTree(x, t->left);
    }

    else
    {
        t->count++;
        return t;
    }

    return t;
}

bst findTree(int x, bst t)
{
    if (!t)
    {
        return NULL;
    }

    bst t1 = t;
    while (t1 != NULL && t1->data != x)
    {
        if (x > t1->data)
        {
            t1 = t1->right;
        }

        else if (x < t->data)
        {
            t1 = t1->left;
        }
    }

    return t1;
}

bst findParentTree(int x, bst t)
{
    if (!t)
    {
        return NULL;
    }

    bst t1 = t;
    while (t1 != NULL)
    {
        if ((t1->left != NULL && t1->left->data == x) || (t1->right != NULL && t1->right->data == x))
        {
            break;
        }

        if (x > t1->data)
        {
            t1 = t1->right;
        }

        else if (x < t->data)
        {
            t1 = t1->left;
        }
    }

    return t1;
}

bst findMin(bst t)
{
    bst t1 = t;
    while (t1->left != NULL)
    {
        t1 = t1->left;
    }
    return t1;
}

bst findMax(bst t)
{
    bst t1 = t;
    while (t1->right != NULL)
    {
        t1 = t1->right;
    }
    return t1;
}

void deleteTree(int x, bst t)
{
    if (!t)
    {
        return;
    }

    bst t1 = findTree(x, t);
    if (!t1)
    {
        return;
    }

    if (t1->left && t1->right)
    {
        bst t2 = findMin(t1->right);
        int temp = t2->data;
        deleteTree(t2->data, t);
        t1->data = temp;
        return;
    }

    bst p = findParentTree(x, t);

    if (!t1->left && !t1->right)
    {
        if (p->left == t1)
        {
            p->left = NULL;
        }

        else if (p->right == t1)
        {
            p->right = NULL;
        }

        free(t1);
    }

    else if (!t1->right || !t1->left)
    {
        if (p->left == t1)
        {
            if (t1->left)
            {
                p->left = t1->left;
            }
            else
            {
                p->left = t1->right;
            }
        }

        else if (p->right == t1)
        {
            if (t1->left)
            {
                p->right = t1->left;
            }
            else
            {
                p->right = t1->right;
            }
        }
        free(t1);
    }
}

void printTreeInOrder(bst t)
{
    if (t != NULL)
    {
        printTreeInOrder(t->left);
        printf("%d  ", t->data);
        printTreeInOrder(t->right);
    }
}

void printTreePostOrder(bst t)
{
    if (t != NULL)
    {
        printTreePostOrder(t->left);
        printTreePostOrder(t->right);
        printf("%d  ", t->data);
    }
}

void printTreePreOrder(bst t)
{
    if (t != NULL)
    {
        printf("%d  ", t->data);
        printTreePreOrder(t->left);
        printTreePreOrder(t->right);
    }
}

/*
int main()
{
    bst t = insertTree(5, NULL);
    insertTree(6, t);
    insertTree(3, t);
    // Use the remain functions ;
    return 0;
}
*/
