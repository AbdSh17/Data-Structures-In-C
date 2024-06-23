#include <stdio.h>
#include <stdlib.h>

typedef struct hashNode *hash;
// typedef int *hash;

int SIZE_LIST[50] = {11, 47, 97, 197, 397, 797, 1597, 3203, 6421, 12853, 25717, 51437, 102877, 205759, 411527, 823117, 1646237, 3292489, 6584983, 13169977, 26339969, 52679969, 105359939, 210719881, 421439783, 842879579};
int PRIME_LIST[50] = {7, 43, 89, 193, 389, 787, 1583, 3191, 6397, 12841, 25703, 51431, 102871, 205753, 411503, 823103, 1646221, 3292463, 6584953, 13169959, 26339929, 52679921, 105359933, 210719863, 421439719, 842879569};

#define EMPTY 0
#define DELETED -1

struct hashNode
{
    int *array;
    int currentSize;
    int currentRehash;
};

void insertToHash(int, hash);

void initializeHash(hash h)
{
    for (int i = 0; i < SIZE_LIST[h->currentRehash]; i++)
    {
        h->array[i] = EMPTY;
    }
}

hash MakeEmptyHash()
{
    hash h = (hash)malloc(sizeof(struct hashNode));
    h->currentSize = 0;
    h->currentRehash = 0;

    h->array = (int *)malloc(sizeof(int) * SIZE_LIST[h->currentRehash]);
    initializeHash(h);
    return h;
}

void reHash(hash h)
{
    hash save = (hash)malloc(sizeof(struct hashNode));
    save->currentSize = 0;
    save->currentRehash = h->currentRehash;

    save->array = (int *)malloc(sizeof(int) * SIZE_LIST[save->currentRehash]);
    initializeHash(save);

    for (int i = 0; i < SIZE_LIST[h->currentRehash]; i++)
    {
        save->array[i] = h->array[i];
    }
    free(h->array);
    h->currentRehash++;
    h->currentSize = 0;
    h->array = (int *)malloc(sizeof(int) * SIZE_LIST[h->currentRehash]);
    initializeHash(h);
    for (int i = 0; i < SIZE_LIST[save->currentRehash]; i++)
    {
        insertToHash(save->array[i], h);
    }
}

void insertToHash(int x, hash h)
{
    if (h->currentSize > SIZE_LIST[h->currentRehash] * 0.70)
    {
        reHash(h);
    }

    int i = 0;
    while (i < SIZE_LIST[h->currentRehash])
    {
        unsigned long h2 = PRIME_LIST[h->currentRehash] - (x % PRIME_LIST[h->currentRehash]);
        int location = (x % SIZE_LIST[h->currentRehash] + i * h2) % SIZE_LIST[h->currentRehash];

        if (h->array[location] == EMPTY || h->array[location] == DELETED)
        {
            h->array[location] = x;
            h->currentSize++;
            break;
        }
        i++;
    }
}

void deleteHashValue(int x, hash h)
{
    int i = 0;
    while (i < SIZE_LIST[h->currentRehash])
    {
        unsigned long h2 = PRIME_LIST[h->currentRehash] - (x % PRIME_LIST[h->currentRehash]);
        int location = (x % SIZE_LIST[h->currentRehash] + i * h2) % SIZE_LIST[h->currentRehash];

        if (h->array[location] == EMPTY)
        {
            break;
        }

        else if (h->array[location] == x)
        {
            h->array[location] = DELETED;
        }

        i++;
    }
}

void printHash(hash h)
{
    printf("Index   Value\n");
    for (int i = 0; i < SIZE_LIST[h->currentRehash]; i++)
    {
        if (h->array[i] == DELETED)
        {
            printf("%-5d:  0\n", i);
            continue;
        }

        printf("%-5d:  %-5d\n", i, h->array[i]);
    }
}
