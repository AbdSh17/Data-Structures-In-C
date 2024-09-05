// INput file name: "input.txt" ;

// StdName: Abd alraheem Shuaibi ;
// StdNum: 1220148 ;
// StdSec: 3 l

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define STRING_SIZE 20    // Define the total Charchters length for each Word ;
#define DELETE_COMPLETE 1 // Delete status: Delete without looking to frequency ;
#define DELEET_FREQ 2     // Delete status: Delete while consedring frequency ;
#define EXIT_FAILURE_NO_COPY 1

//=====================================Project description=====================================
/*
.This is a university project, data structures and algorithims (COMP2421).
.the projects is an implemantation hash tables and avl tree

.this project reads from file named output/input.txt
.you can explor what option you have in the menu

*/

/*
    project idea is to copy the AVL tree in a new tree node and make each element of the hash is a pointer of that tree node
    // t is an array head which poinnt to an array of pointers and t[n] is a pointer ;

t-->| t1- |------------->   TreeNode
    |     |                /        \
    | t2- |------------>TreeNode  TreeNode
    |     |                            ^
    |     |                            |         
    | t3- |-----------------------------
    |     |

*/

typedef struct node *tree; // typedeff to the tree struct pointer ;

int capacity = 0; // The array capacity ;
int CURRENT = 0; // Current location status to decide which prime number from the bellwo

// List of prime numbers where each is new > 2 * old (Its faster that way than doing nested loop each rehashing which might take nearly O(n^2));
int SIZE_LIST[50] = {11, 47, 97, 197, 397, 797, 1597, 3203, 6421, 12853, 25717, 51437, 102877, 205759, 411527, 823117, 1646237, 3292489, 6584983, 13169977, 26339969, 52679969, 105359939, 210719881, 421439783, 842879579};
int PRIME_LIST[50] = {7, 43, 89, 193, 389, 787, 1583, 3191, 6397, 12841, 25703, 51431, 102871, 205753, 411503, 823103, 1646221, 3292463, 6584953, 13169959, 26339929, 52679921, 105359933, 210719863, 421439719, 842879569};

int maxValue(int, int);
void printTree(tree);
tree loadtoAVL(char *, tree);
tree Delete(char *, tree);
void printTreePrefex(tree);
tree deleteAVL(char *, tree);
tree deleteNode(char *, tree, int);
void initializeHash(tree *);
unsigned long stringValue(char *);
tree *insertToHash(tree t, tree *);
void printHash(tree *);
tree *insertTreeIntoHash(tree, tree *);
tree findHash(char *, tree *);
tree copyTree(tree, tree);
tree findTree(char *, tree);
int deleteHash(char *, tree *);
int numberOfUniqueWords(tree *);
tree mostFrequentWord(tree *);
int strcmpCase(char *, char *);
char *toAlpha(char *);
int isAlpha(char);
void printMoreFreqThan(tree *, int);
tree deleteNoFreqAVL(char *, tree);
int deleteHashNoFreq(char *, tree *);


// Tree Struct node ;
struct node
{
    char element[STRING_SIZE];
    tree left;
    tree right;
    int height;
    int frequency;
};

//=====================================================================Hash=====================================================================

// Initialize hash value ( each will take NULL) ;
void initializeHash(tree *hash)
{
    for (int i = 0; i < SIZE_LIST[0]; i++)
    {
        hash[i] = NULL;
    }
}

// Imoplement rehashing function ;
tree *reHash(tree *hash)
{
    int i = 0; 
    tree temp[SIZE_LIST[CURRENT]];
    // Saving old hash memory ;
    while (i < SIZE_LIST[CURRENT])
    {
        temp[i] = hash[i];
        hash[i] = NULL;
        i++;
    }
    // move to the next prime ;
    CURRENT++;
    tree *h2;

    // Point to the new allocated memort ;
    h2 = (tree *)realloc(hash, sizeof(tree) * SIZE_LIST[CURRENT]);
    // initalize the new allocated ;
    while (i < SIZE_LIST[CURRENT])
    {
        h2[i] = NULL;
        i++;
    }

    i = 0;
    printf("\nResized the Hash\n");
    // Re-insert the old memory from zero to the old Size ;
    while (i < SIZE_LIST[CURRENT - 1])
    {
        tree temp1 = temp[i];
        if (temp1 != NULL)
        {
            insertToHash(temp1, h2);
            capacity--;
        }
        i++;
    }
    free(hash); // Free the old allocated ;
    return h2;
}

// Insert new tree pointer to the hash ;
tree *insertToHash(tree t, tree *hash)
{
    // if its 75% complete, Re-Hash then continue the insert ;
    if (capacity > SIZE_LIST[CURRENT] * 0.75)
    {
        hash = reHash(hash);
    }
    int i = 0;
    unsigned long x = stringValue(t->element); // unsugned long is the most bit value the array and modulas can deal with ;
    while (i < SIZE_LIST[CURRENT])
    {
        // h = h1 + i * h2 ;
        unsigned long h2 = PRIME_LIST[CURRENT] - (x % PRIME_LIST[CURRENT]);
        int location = (x % SIZE_LIST[CURRENT] + i * h2) % SIZE_LIST[CURRENT]; 
        // As it is initalized the value is NULL if its empty
        if (hash[location] == NULL)
        {
            capacity++;
            hash[location] = t;
            break;
        }
        // If its deleted before Re-check if the word exist previously, if not just add it ;
        else if (hash[location]->element[0] == '\0')
        {
            tree t1 = findHash(t->element, hash);
            if (t1 == NULL)
            {
                capacity++;
                hash[location] = t;
                break;
            }
            else
            {
                break; // the pointer will increase its frequency ;
            }
        }
        else if (!strcmpCase(hash[location]->element, t->element))
        {
            break; // the pointer will increase its frequency ;
        }
        i++;
    }
    return hash;
}

// find a hash, exactly like insert with few differences ;
// if the function run out with previously deleted word ( '\0' ), it will continue t search ;
tree findHash(char *c, tree *hash)
{
    int i = 0;
    int x = stringValue(c);
    while (i < SIZE_LIST[CURRENT])
    {
        int h2 = PRIME_LIST[CURRENT] - (x % PRIME_LIST[CURRENT]);
        int location = (x % SIZE_LIST[CURRENT] + i * h2) % SIZE_LIST[CURRENT];
        if (hash[location] == NULL)
        {
            printf("\nWord no found in the hash\n");
            return NULL;
        }
        else if (!strcmpCase(hash[location]->element, c))
        {
            return hash[location];
        }
        i++;
    }
    printf("\nWord no found in the hash\n");
    return NULL;
}

// Delete a a word in the hash, then put its status '\0', to know here is deleted ;
int deleteHash(char *c, tree *hash)
{
    int i = 0;
    int x = stringValue(c);
    while (i < SIZE_LIST[CURRENT])
    {
        int h2 = PRIME_LIST[CURRENT] - (x % PRIME_LIST[CURRENT]);
        int location = (x % SIZE_LIST[CURRENT] + i * h2) % SIZE_LIST[CURRENT];
        if (hash[location] == NULL)
        {
            printf("\nWord no found in the hash\n");
            return 0;
        }
        else if (!strcmpCase(hash[location]->element, c))
        {
            if (hash[location]->frequency > 1)
            {
                hash[location]->frequency--;
                return 2;
            }
            tree t = (tree)malloc(sizeof(struct node));
            t->element[0] = '\0';
            t->frequency = 0;
            hash[location] = t;
            return 1;
        }
        i++;
    }
    printf("\nWord no found in the hash\n");
    return 0;
}

// Delete any way without looking to frequency ;
int deleteHashNoFreq(char *c, tree *hash)
{
    int i = 0;
    int x = stringValue(c);
    while (i < SIZE_LIST[CURRENT])
    {
        int h2 = PRIME_LIST[CURRENT] - (x % PRIME_LIST[CURRENT]);
        int location = (x % SIZE_LIST[CURRENT] + i * h2) % SIZE_LIST[CURRENT];
        if (hash[location] == NULL)
        {
            printf("\nWord no found in the hash\n");
            return 0;
        }
        else if (!strcmpCase(hash[location]->element, c))
        {
            tree t = (tree)malloc(sizeof(struct node));
            t->element[0] = '\0'; // Change its status to '\0' ;
            t->frequency = 0;
            hash[location] = t;
            return 1;
        }
        i++;
    }
    printf("\nWord no found in the hash\n");
    return 0;
}

// printing the hash ;
void printHash(tree *hash)
{
    printf("Index   Word    Frequency\n");
    for (int i = 0; i < SIZE_LIST[CURRENT]; i++)
    {
        if (hash[i] != NULL && hash[i]->frequency != 0)
        {
            printf("%-6d %-12s %d\n", i, hash[i]->element, hash[i]->frequency);
        }
        else
        {
            printf("%-6d ---\t    0\n", i);
        }
    }
}

// Return the number that appeared one time ;
int numberOfUniqueWords(tree *hash)
{
    int count = 0;
    int total = 0;
    // Search linearly in the hash ;
    while (count < SIZE_LIST[CURRENT])
    {
        if (hash[count] != NULL && hash[count]->frequency == 1)
        {
            total++;
        }
        count++;
    }
    return total;
}

// Return the most frequant word in the hash ( not the AVL tree ) ;
tree mostFrequentWord(tree *hash)
{
    int count = 0;
    int max = 0;
    int pin;
    // Search linearly ofc ;
    while (count < SIZE_LIST[CURRENT])
    {
        if (hash[count] != NULL)
        {
            if (max < hash[count]->frequency)
            {
                pin = count;
                max = hash[count]->frequency;
            }
        }
        count++;
    }
    return hash[pin]; // pin will return the first occurance ;
}

// Print the most frequant word than specific integer ;
void printMoreFreqThan(tree *hash, int num)
{
    printf("Index   Word    Frequency\n");
    for (int i = 0; i < SIZE_LIST[CURRENT]; i++)
    {
        if (hash[i] != NULL && hash[i]->frequency > num)
        {
            printf("%-6d %-12s %d\n", i, hash[i]->element, hash[i]->frequency);
        }
    }
}

//=====================================================================//Hash=====================================================================

//=====================================================================AVL=====================================================================

// make the tree empty  ;
tree makeEmpty(tree t)
{
    if (t != NULL)
    {
        makeEmpty(t->left);
        makeEmpty(t->right);
        free(t);
    }
    return NULL;
}

// find min value ( go left ) ;
tree findMin(tree t)
{
    if (t == NULL)
        return NULL;
    else if (t->left == NULL)
        return t;
    else
        return findMin(t->left);
}

// find max value ( go right ) ;
tree findMax(tree t)
{
    if (t != NULL)
        while (t->right != NULL)
            t = t->right;

    return t;
}

// go zig-zag until find the node ;
tree findTree(char *c, tree t)
{
    if (t != NULL)
    {
        if (strcmpCase(c, t->element) == 1)
        {
            return findTree(c, t->right);
        }
        else if (strcmpCase(c, t->element) == -1)
        {
            return findTree(c, t->left);
        }
        else if (!strcmpCase(c, t->element))
        {
            return t;
        }
    }
    else
    {
        return NULL;
    }
    return t;
}

// each tree node hieght ;
int height(tree p)
{
    if (p == NULL)
        return -1;
    else
        return p->height;
}

tree singleRotateWithleft(tree t2)
{
    tree t1 = t2->left;
    t2->left = t1->right;
    t1->right = t2;

    t2->height = maxValue(height(t2->left), height(t2->right))  +1;
    t1->height = maxValue(height(t1->left), t2->height) + 1;

    return t1;
}

tree singleRotateWithright(tree t1)
{
    tree t2;

    t2 = t1->right;
    t1->right = t2->left;
    t2->left = t1;

    t1->height = maxValue(height(t1->left), height(t1->right)) + 1;
    t2->height = maxValue(height(t2->right), height(t2->left)) + 1;

    return t2;
}

tree doubleRotateWithleft(tree t3)
{
    t3->left = singleRotateWithright(t3->left);
    return singleRotateWithleft(t3);
}

tree doubleRotateWithright(tree t1)
{
    t1->right = singleRotateWithleft(t1->right);
    return singleRotateWithright(t1);
}

tree insert(char *x, tree t)
{
    if (t == NULL)
    {
        t = (tree)malloc(sizeof(struct node));
        if (t == NULL)
            printf("Out of space!!!");
        else
        {
            strncpy(t->element, x, sizeof(t->element));
            t->height = 0;
            t->frequency = 1;
            t->left = NULL;
            t->right = NULL;
        }
        return t;
    }
    else if (strcmpCase(t->element, x) == 1)
    {
        t->left = insert(x, t->left);
        if (height(t->left) - height(t->right) == 2)
        {
            if (strcmpCase(t->left->element, x) == 1)
                t = singleRotateWithleft(t);
            else
                t = doubleRotateWithleft(t);
        }
    }
    else if (strcmpCase(t->element, x) == -1)
    {
        t->right = insert(x, t->right);
        if (height(t->right) - height(t->left) == 2)
        {
            if (strcmpCase(t->right->element, x) == -1)
            {
                t = singleRotateWithright(t);
            }
            else
            {
                t = doubleRotateWithright(t);
            }
        }
    }
    else if (!strcmpCase(t->element, x))
    {
        t->frequency++;
    }

    t->height = maxValue(height(t->left), height(t->right)) + 1;

    return t;
}

tree Delete(char *x, tree t)
{
    tree tmpCell;

    if (t == NULL)
    {
        printf("There's no such node\n");
        return NULL;
    }
    else if (strcmpCase(t->element, x) == 1)
        t->left = Delete(x, t->left);
    else if (strcmpCase(t->element, x) == -1)
        t->right = Delete(x, t->right);
    else if (t->left && t->right)
    {
        tmpCell = findMax(t->left);
        strncpy(t->element, tmpCell->element, sizeof(t->element));
        t->left = Delete(t->element, t->left);
    }
    else
    {
        tmpCell = t;
        if (t->left == NULL)
            t = t->right;
        else if (t->right == NULL)
            t = t->left;
        free(tmpCell);
    }

    return t;
}

int flag = 0;
tree deleteAVL(char *x, tree t)
{
    if (strcmpCase(t->element, x) == 1)
    {
        t->left = deleteAVL(x, t->left);
        if (flag == 1)
        {
            t = Delete(x, t);
            flag = 0;
        }

        if (height(t->right) - height(t->left) == 2)
        {
            if (t->right->right != NULL)
                t = singleRotateWithright(t);
            else
            {
                t = doubleRotateWithright(t);
            }
        }
    }
    else if (strcmpCase(t->element, x) == -1)
    {
        t->right = deleteAVL(x, t->right);
        if (flag == 1)
        {
            t = Delete(x, t);
            flag = 0;
        }
        if (height(t->left) - height(t->right) == 2)
        {
            if (t->left->left != NULL)
            {
                t = singleRotateWithleft(t);
            }
            else
            {
                t = doubleRotateWithleft(t);
            }
        }
    }
    else if (!strcmpCase(t->element, x))
    {
        if (t->frequency > 1)
        {
            t->frequency--;
            flag = 2;
        }
        else
        {
            flag = 1;
        }
    }

    if (t != NULL)
    {
        t->height = maxValue(height(t->left), height(t->right)) + 1;
    }

    return t;
}

tree deleteNoFreqAVL(char *x, tree t)
{
    if (strcmpCase(t->element, x) == 1)
    {
        t->left = deleteAVL(x, t->left);
        if (flag == 1)
        {
            t = Delete(x, t);
            flag = 0;
        }

        if (height(t->right) - height(t->left) == 2)
        {
            if (t->right->right != NULL)
                t = singleRotateWithright(t);
            else
            {
                t = doubleRotateWithright(t);
            }
        }
    }
    else if (strcmpCase(t->element, x) == -1)
    {
        t->right = deleteAVL(x, t->right);
        if (flag == 1)
        {
            t = Delete(x, t);
            flag = 0;
        }
        if (height(t->left) - height(t->right) == 2)
        {
            if (t->left->left != NULL)
            {
                t = singleRotateWithleft(t);
            }
            else
            {
                t = doubleRotateWithleft(t);
            }
        }
    }
    else if (!strcmpCase(t->element, x))
    {
            flag = 1;
    }

    if (t != NULL)
    {
        t->height = maxValue(height(t->left), height(t->right)) + 1;
    }

    return t;
}

tree deleteNode(char *x, tree t, int status)
{
    if (status == DELETE_COMPLETE)
    {
        t = deleteNoFreqAVL(x, t);
        if (flag == 1)
        {
            t = Delete(x, t);
            flag = 0;
        }
    }
    else if (status == DELEET_FREQ)
    {
        t = deleteAVL(x, t);
        if (flag == 1)
        {
            t = Delete(x, t);
            flag = 0;
        }
    }
    return t;
}

tree loadtoAVL(char *c, tree t)
{
    char *c1[50];
    int i = 0;
    c1[i] = strtok(c, " ");
    while (c1[i] != '\0')
    {
        i++;
        c1[i] = strtok(NULL, " ");
    }
    int count = 0;
    while (count < i)
    {
        toAlpha(c1[count]);
        t = insert(c1[count], t);
        count++;
    }
    return t;
}

// Print the tree infex ;
void printTree(tree t)
{
    if (t != NULL)
    {
        printTree(t->left);
        printf("%s  ", t->element);
        printTree(t->right);
    }
}

// Print tree Prefex ;
void printTreePrefex(tree t)
{
    if (t != NULL)
    {
        printf("%s  ", t->element);
        printTreePrefex(t->left);
        printTreePrefex(t->right);
    }
}

// Max value of two integers ;
int maxValue(int leftHandSide, int rightHandSide)
{
    return leftHandSide > rightHandSide ? leftHandSide : rightHandSide;
}

tree copyTree(tree t1, tree t2)
{
    if (t1 != NULL)
    {
        t2 = copyTree(t1->left, t2);
        t2 = insert(t1->element, t2);
        t2 = copyTree(t1->right, t2);
    }
    return t2;
}

//=====================================================================//AVL=====================================================================

//=====================================================================Main=====================================================================

int main()
{
    // allocate an array of tree ( dynamic ) ;
    tree *hash = (tree *)malloc(sizeof(tree) * SIZE_LIST[CURRENT]);

    FILE *in = NULL;
    in = fopen("output/input.txt", "r");
    if (in == NULL)
    {
        printf("Fatal 02: Failed to load the file, please check the file name was: input.txt ");
        exit(EXIT_FAILURE_NO_COPY); // Defined above ;
    }
    int operation = 0;
    printf("\nEnter what operation you want based on the index\n1-Load the element file.\n2-Create the AVL tree.\n3-Insert a word to the AVL tree.\n4-Delete a word from the AVL tree.\n5-Print the word sorted in the AVL tree.\n6-Create the hash table.\n7-Insert a word to the hash table.\n8-Delete a word from the hash table.\n9-Search for a word and its frequency from the hash table.\n10-Print the words statistics.\n11-Exit.\n");
    scanf("%d", &operation);
    getchar(); // to catch the '\n' that printed by fgets ;

    tree t = makeEmpty(NULL);
    char save[50][500]; // to save to the original avl ;

    tree t2 = makeEmpty(NULL);

    // nedded two cuse the one element will change after inserting ;

    int flag = 0; // to know if it enters specific functions ;
    while (operation != 11)
    {
        char load[500], word[50]; // to be more advanced and specific, the array will pop from the stack that contains while loop after each loop, so no worry sbout the memory
        int i = 0;
        tree t3;
        switch (operation)
        {
        case 1:
            while (fgets(load, sizeof(load), in) != NULL)
            {
                strncpy(save[i], load, strlen(load));
                save[i][strlen(load) - 1] = '\0';
                i++;
            }
            save[i][0] = '\0';

        case 2:
            while (save[i][0] != '\0')
            {
                t = loadtoAVL(save[i], t);
                i++;
            }
            break;
        case 3:
            printf("\nEnter What to insert:  "); 
            fgets(word, sizeof(word), stdin);
            word[strlen(word) - 1] = '\0';
            t = loadtoAVL(word, t); // Function which prepeare the word (makes it alphabatically ) then insert it to the avl tree t ;
            break;
        case 4:
            printf("\nEnter What to delete:  ");
            fgets(word, sizeof(word), stdin);
            word[strlen(word) - 1] = '\0';
            toAlpha(word);
            deleteNode(word, t, DELEET_FREQ);
            break;
        case 5:
            printTree(t);
            break;
        case 6:
            if (flag)
            {
                printf("Already created\n");
                break;
            }
            flag = 1;
            t2 = copyTree(t, t2); // Copy the avl tree to new tree which i will use its node pointers in the hash ( makes the project more flexable and edatable) ;
            initializeHash(hash); // Initalize haah to prebare it ;
            hash = insertTreeIntoHash(t2, hash); // insert the copied tree to the hash ;
            break;
        case 7:
            if (!flag)
            {
                printf("Please create the hash first\n");
                break;
            }

            printf("\nEnter What to insert into the hash:  ");
            fgets(word, sizeof(word), stdin);
            word[strlen(word) - 1] = '\0';
            toAlpha(word); // makes word an alphabatical String ;
            t2 = insert(word, t2); // Insert it to the copied tree first ;
            t3 = findTree(word, t2); // Make a pointer to it ;
            hash = insertToHash(t3, hash); // Insert that pointer to the hash ;
            break;
        case 8:
            if (!flag)
            {
                printf("Please create the hash first\n");
                break;
            }
            printf("\nEnter What to insert into the hash:  ");
            fgets(word, sizeof(word), stdin);
            word[strlen(word) - 1] = '\0';
            printf("\nEnter The deleting method\n1-Delete anyway\n2-Decrease frequency if exist\n");
            scanf("%d", &i);
            // Check if the user wants to handle the freqancy or not ;
            if (i == 1)
            {
                if (deleteHashNoFreq(word, hash) == 1)
                {
                    t2 = deleteNode(word, t2, DELETE_COMPLETE);
                }
            }
            else if (i == 2)
            {
                if (deleteHash(word, hash) == 1)
                {
                    t2 = deleteNode(word, t2, DELEET_FREQ);
                }
            }
            else
            {
                printf("Invalid operation");
            }
            break;
        case 9:
            if (!flag)
            {
                printf("Please create the hash first\n");
                break;
            }
            printf("\nEnter What a word to get its frequency:  ");
            fgets(word, sizeof(word), stdin);
            word[strlen(word) - 1] = '\0';
            t3 = findHash(word, hash);
            if (t3 != NULL)
            {
                printf("\n%s Frequency is:  %d", word, t3->frequency);
            }
            break;
        case 10:
            if (!flag)
            {
                printf("Please create the hash first\n");
                break;
            }
            printHash(hash);
            printf("Number Of unique words:  %d\n", numberOfUniqueWords(hash));
            printf("The word with most occurrance:  %s\n", mostFrequentWord(hash)->element);
            printf("The words with frequency more than 2 are:\n");
            printMoreFreqThan(hash, 2);
            break;
        default:
            printf("Wrong operation , please enter a number that is in the choices\n"); // Just enter the right one please ):
            break;
        }
        printf("\nEnter what operation you want based on the index\n1-Load the element file.\n2-Create the AVL tree.\n3-Insert a word to the AVL tree.\n4-Delete a word from the AVL tree.\n5-Print the word sorted in the AVL tree.\n6-Create the hash table.\n7-Insert a word to the hash table.\n8-Delete a word from the hash table.\n9-Search for a word and its frequency from the hash table.\n10-Print the words statistics.\n11-Exit.\n");
        scanf("%d", &operation);
        getchar();
    }

    return 0;
}

//=====================================================================//Main=====================================================================

//=====================================================================Functions=====================================================================

tree *insertTreeIntoHash(tree t, tree *hash)
{
    if (t != NULL)
    {
        hash = insertTreeIntoHash(t->left, hash);
        if (isAlpha(t->element[0])) // idk what this handle but why not ;
        {
            hash = insertToHash(t, hash);
        }
        hash = insertTreeIntoHash(t->right, hash);
    }
    return hash;
}

unsigned long stringValue(char *key)
{
    // Key[KeySize-i -1]. 32^i
    unsigned long hashValue = 0;
    while (*key != '\0')
    {
        hashValue = (hashValue << 5) + *key++;
    }
    return (hashValue);
}

int strcmpCase(char *c1, char *c2)
{
    int i = 0;
    int j = 0;
    while (c1 || c2)
    {
        int value1 = 0, value2 = 0;
        if (c1[i] == '\0' && c2[j] == '\0')
        {
            return 0;
        }
        if (c1[i] == '\0')
        {
            return -1;
        }

        else if (c2[j] == '\0')
        {
            return 1;
        }

        if (!isAlpha(c1[i]) && !isAlpha(c2[j]))
        {
            j++;
            i++;
            continue;
        }
        else if (!isAlpha(c1[i]))
        {
            i++;
            continue;
        }

        else if (!isAlpha(c2[j]))
        {
            j++;
            continue;
        }

        if (c1[i] >= 65 && c1[i] <= 90)
        {
            value1 = c1[i] - 65;
        }
        else
        {
            value1 = c1[i] - 97;
        }

        if (c2[j] >= 65 && c2[j] <= 90)
        {
            value2 = c2[j] - 65;
        }
        else
        {
            value2 = c2[j] - 97;
        }

        if (value1 > value2)
        {
            return 1;
        }
        else if (value1 < value2)
        {
            return -1;
        }
        i++;
        j++;
    }
    return 0;
}

// Return if the charachter alphabatically ;
int isAlpha(char c)
{
    return (c < 65 || c > 90) && (c < 97 || c > 122) ? 0 : 1;
}

// Concert the String into Alphabatically String ;
char *toAlpha(char *c)
{
    int i = 0;
    int j = 0;
    char c1[strlen(c)];
    while (c[i] != '\0')
    {
        if (isAlpha(c[i]))
        {
            c1[j] = c[i]; // Save each alphabatical charachter ;
            j++;
        }
        i++;
    }
    c1[j] = '\0';
    strncpy(c, c1, strlen(c)); // copy the alphabatical String into the original one ;
    return c;
}
//=====================================================================//Functions=====================================================================
