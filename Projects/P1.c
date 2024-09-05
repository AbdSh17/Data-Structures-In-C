// StdName: Abdalraheem kifah Shauibi ;
// StdID: 1220148 ;
// Std

/*

Project description:
.This is a university project, data structures and algorithims (COMP2421).
.the projects is an implemantation of linked lists and radix sort algorithim

.so we have a districts and each distrcit contain cities, saved in file named output/Districts.txt which is a psv
.there's multy options you can see and use inside the menu after runing the code

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct node *districts;
typedef struct node1 *town;
//========================Others========================

void sortArray(int[], int);
int getMost(int[], int);
int ConvertString(char *);

//======================District========================

districts findDistrict(char *, districts);
districts makeEmptyDistrict(districts);
void printDistricts(districts);
void deleteTown(char *, char *, districts);
void copyDistrict(districts, districts);
void deleteDistrict(districts);
void insertdistricts(char *, districts);
void deleteDistrictByName(char *c, districts d);
void printDistrictsNoDetails(districts);
void changeTownPopulation(char *, char *, int, districts);
void addNewDistrtictTown(char *, districts, town);
void addToCurrentDistrict(districts, town);
void addNewDistrict(char *, districts);
void printOutput(districts, FILE *);
void sortLinkedListString(districts);
town makeEmptyTown(town);
town findFirstTown(char *, districts);
town minTown(districts);
town maxTown(districts);
town findATown(char *, char *, districts);
int districtSize(districts);
int mostDistrictElement(districts);
int isEmptyDistrict(districts);
int calculatePopulation(districts);
int districtTownsCount(districts);
int mostTownDigits(districts);
void townsSort(districts);
void deleteEntireTown(town);
void deleteCountry(districts);
int calculateDistrictPupulation(districts);
int calculateCountryPopulation(districts);
void printDistrictTowns(districts);

// District Struct ;
struct node
{
    char districtName[50];    // District name ;
    int population;           // Total district population ;
    districts bottom;         // The next District ;
    districts top;            // The previous District ;
    districts distrticstBack; // to keep tracking the las inserted District ;
    town disTownBack;         // to keep tracking the las inserted Town ;
    town nextTown;            // for the next town ;
};

// Town struct ;
struct node1
{
    int population;    // town population ;
    char townName[50]; // town name ;
    town next;         // next town ;
    town previous;     // previous town ;
    town townBack;     // to keep tracking the last inserted town ;
    districts dis;     // to point for which district it belongs to ;
};

int main()
{

    districts district = makeEmptyDistrict(NULL);
    FILE *in;
    in = fopen("output/districts.txt", "r");
    if (in == NULL)
    {
        printf("Fatal: Failed to load the file , please check the file name was: districts.txt ");
        exit(EXIT_FAILURE);
    }

    int operation;

    printf("\nEnter what operation you want based on the index\n1-Load the input file.\n2-Print the loaded information.\n3-Sort the districts alphabetically.\n4-Sort towns based on population.\n5-Print the sorted information.\n6-Add new district.\n7-Add new town to certain district.\n8-Delete a town from a specific district.\n9-Delete a complete district.\n10-Get palestine population , min and max town.\n11-Print the districts and their total population (without towns details).\n12-Change the population of a certen town.\n13-Save to the output file.\n14-Exit.\n\n");
    scanf("%d", &operation);
    getchar(); // Will catch the '\n' that printed by fgets (Could use somtihng like scanf and define a usless variable but that's more cool so don't give me a copy please ) ;
    /*
    char get;
    scanf("%c", &get);
    */

    while (operation != 14)
    {
        char dis[50], tName[50], c[50]; // Didn't handle the length exception cause the project asked me to expect 50 ;
        char c2[50][50];
        FILE *out; // Declared inside loop to allow keep changing ;
        int population, i = 0;
        districts d;
        switch (operation)
        {
        case 1:
            // insert every line using fgets ;
            while (fgets(c, sizeof(c), in) != NULL)
            {
                insertdistricts(c, district);
                strncpy(c2[i], c, sizeof(c2[i])); // Save the loaded information from the PSV file to allow the user to check them (save them while load the file);
                c2[i + 1][0] = '\0';
                i++;
            }
            break;
        case 2:
            while (c2[i][0] != '\0') // Just print the loaded information from the PSV file ( any thing added by the terminal will not be concedard );
            {
                printf("%s", c2[i]);
                i++;
            }
            printf("\n");
            break;
        case 3:
            sortLinkedListString(district); // Radix sort ;
            break;
        case 4:
            townsSort(district); // Radix sort ;
            break;
        case 5:
            sortLinkedListString(district);
            printDistricts(district);
            break;
        case 6:
            printf("\nPlease enter the District name:  ");
            fgets(dis, sizeof(dis), stdin);
            dis[strlen(dis) - 1] = '\0'; // To prevent the '\n' at the end of dis ;
            districts p = findDistrict(dis, district);
            if (p != NULL)
            {
                printf("District with name:  %s already exist\n", dis);
                break;
            }
            addNewDistrict(dis, district);
            sortLinkedListString(district);
            break;
        case 7:
            printf("\nCurrent Districts:\n==============================\n\n");
            printDistrictsNoDetails(district);
            printf("\n==============================\n");
            printf("\nPlease enter the District name:  ");
            fgets(dis, sizeof(dis), stdin);
            dis[strlen(dis) - 1] = '\0';
            d = findDistrict(dis, district);
            if (!d)
            {
                printf("Error occurred: can't find the district: %s, please check the name", dis);
                break;
            }
            printf("Please enter the town name:  ");
            fgets(tName, sizeof(tName), stdin);
            printf("Please enter the population:  ");
            scanf("%d", &population);
            tName[strlen(tName) - 1] = '\0';
            town temp = makeEmptyTown(NULL);
            strncpy(temp->townName, tName, sizeof(temp->townName)); // To make sure that townName[strlen(townName) + k] == '\0' , where k < 50 ;
            temp->population = population;
            addToCurrentDistrict(d, temp);
            break;
        case 8:
            printf("\nCurrent Districts:\n==============================\n\n");
            printDistrictsNoDetails(district);
            printf("\n==============================\n");
            printf("\nPlease enter the District name:  ");
            fgets(dis, sizeof(dis), stdin);
            dis[strlen(dis) - 1] = '\0';
            d = findDistrict(dis, district);
            if (!d)
            {
                printf("Error occurred: can't find the district: %s, please check the name", dis);
                break;
            }
            printf("\nPlease enter the town name:\n\n");
            if (!d->nextTown)
            {
                printf("Empty District\n");
                break;
            }
            printf("\n-%s Current Towns\n==============================\n\n", dis);
            printDistrictTowns(d);
            printf("\n==============================\n");
            printf("\nPlease enter the town name:  ");
            fgets(tName, sizeof(tName), stdin);
            tName[strlen(tName) - 1] = '\0';
            deleteTown(dis, tName, district);
            break;
        case 9:
            printf("\nCurrent Districts:\n==============================\n\n");
            printDistrictsNoDetails(district);
            printf("\n==============================\n");
            printf("\nPlease enter the District name:  ");
            fgets(dis, sizeof(dis), stdin);
            dis[strlen(dis) - 1] = '\0';
            d = findDistrict(dis, district);
            if (!d)
            {
                printf("Error occurred: can't find the district: %s, Please check the name", dis);
                break;
            }
            deleteDistrictByName(dis, district);
            break;
        case 10:
            if (minTown(district) == NULL || maxTown(district) == NULL)
            {
                printf("the total population of palestine is: 0");
                break;
            }
            printf("the total population of palestine is:  %d\nThe min city is: %s\nthe most city is: %s", calculateCountryPopulation(district), minTown(district)->townName, maxTown(district)->townName);
            break;
        case 11:
            printDistrictsNoDetails(district);
            break;
        case 12:
            printf("\nCurrent Districts:\n==============================\n\n");
            printDistrictsNoDetails(district);
            printf("\n==============================\n");
            printf("\nPlease enter the District name:  ");
            fgets(dis, sizeof(dis), stdin);
            dis[strlen(dis) - 1] = '\0';
            d = findDistrict(dis, district);
            if (!d)
            {
                printf("Error occurred: can't find the district: %s, please check the name", dis);
                break;
            }
            if (!d->nextTown)
            {
                printf("Empty District\n");
                break;
            }
            printf("\n-%s Current Towns\n==============================\n\n", dis);
            printDistrictTowns(d);
            printf("\n==============================\n");
            printf("\nPlease enter the town name:  ");
            fgets(tName, sizeof(tName), stdin);
            printf("Please enter the new population:  ");
            scanf("%d", &population);
            tName[strlen(tName) - 1] = '\0';
            changeTownPopulation(dis, tName, population, district);
            break;
        case 13:
            out = fopen("sorted_districts.txt", "w");
            if (out == NULL)
            {
                printf("Fatal: Failed to load the file , please check the file name was: sorted_districts.txt ");
                exit(EXIT_FAILURE);
            }
            printOutput(district, out); // variable -out- is a reference which will make the changes inside the function too ;
            fclose(out);
            break;
        case 14:
            break;
        default:
            printf("Wrong operation , please enter a number that is in the choices\n"); // Just enter the right one smh ):
            break;
        }
        printf("\nEnter what operation you want based on the index\n1-Load the input file.\n2-Print the loaded information.\n3-Sort the districts alphabetically.\n4-Sort towns based on population.\n5-Print the sorted information.\n6-Add new district.\n7-Add new town to certain district.\n8-Delete a town from a specific district.\n9-Delete a complete district.\n10-Get palestine population , min and max town.\n11-Print the districts and their total population (without towns details).\n12-Change the population of a certen town.\n13-Save to the output file.\n14-Exit.\n\n");
        scanf("%d", &operation);
        // scanf("%c", &get);
        getchar();
    }
}

//==================================================================Dstrict================================================================

// Make Empty District Head (Book implemintation) ;
districts makeEmptyDistrict(districts d)
{
    if (d != NULL)
    {
        deleteCountry(d);
    }
    d = (districts)malloc(sizeof(struct node));
    if (d == NULL)
    {
        printf("Fatal: Failed to malloc the district ,   Expecting: Out Of Memory!");
        exit(EXIT_FAILURE);
    }

    d->population = 0;
    d->bottom = NULL;
    d->top = NULL;
    d->distrticstBack = d;
    d->disTownBack = NULL;
    d->nextTown = NULL;
    return d;
}

// To find a district ;
districts findDistrict(char *c, districts d)
{
    if (d == NULL)
    {
        printf("Error occurred: can't find the District: %s,\tExpecting: Empty Head", c);
        return NULL;
    }

    if (d->bottom == NULL)
    {
        return NULL; // Dealing with the buttom so i can handle d == NULL without any crashes ;
    }
    return (strcmp(c, d->bottom->districtName) == 0) ? d->bottom : findDistrict(c, d->bottom); // Ternary comparesion ;
}

// Sort the Districts by their name alphabetically (radix sort implemintation) ;
void sortLinkedListString(districts l)
{
    if (l == NULL || l->bottom == NULL)
    {
        printf("Error occurred during sorting,\tExpecting: empty Head");
        return;
    }
    districts s[28]; // alphabiticilly plus the null charachter (Decided not to handle the upper case cuse it's too stupid to have a town named BeIt ReEmA) ;
    for (int i = 0; i <= 27; i++)
    {
        s[i] = makeEmptyDistrict(NULL);
    }
    int listSize = districtSize(l);    // Get the total list size ;
    int most = mostDistrictElement(l); // Get the most element digits ;

    for (int i = most - 1; i >= 0; i--) // depends on the most digit value O(k) ;
    {
        districts p1 = l->bottom;

        // First loop to list the charachter in its correct location ;
        while (p1 != NULL) // will see all elements O(n) ;
        {
            // Every NULL element will g to the first list (In english grammer the NULL is before any letter fee -> fees) ;
            if (p1->districtName[i] == '\0')
            {
                s[0]->distrticstBack->bottom = p1;
                s[0]->distrticstBack = p1;
                p1 = p1->bottom;
                s[0]->distrticstBack->bottom = NULL;
                continue;
            }
            int val = 0;
            if (p1->districtName[i] >= 97 && p1->districtName[i] <= 122)
            {
                val = (p1->districtName[i] - 96);
            }
            else if (p1->districtName[i] >= 65 && p1->districtName[i] <= 90)
            {
                val = (p1->districtName[i] - 64);
            }
            else
            {
                // Any other special casses will be consedered last (spaces, -, etc...) ;
                s[27]->distrticstBack->bottom = p1;
                s[27]->distrticstBack = p1;
                p1 = p1->bottom;
                s[27]->distrticstBack->bottom = NULL;
                continue;
            }
            s[val]->distrticstBack->bottom = p1;
            s[val]->distrticstBack = p1;
            p1 = p1->bottom;
            s[val]->distrticstBack->bottom = NULL;
        }
        int j = 0, k = 0;
        l->distrticstBack = l;
        districts p3 = s[k]->bottom;

        // Second loop to return the charchters after 'i' sort to the list ;
        while (j < listSize) // will see all elements O(n) ;
        {
            if (p3 != NULL)
            {
                l->distrticstBack->bottom = p3;
                p3->top = l->distrticstBack;
                l->distrticstBack = p3;
                p3 = p3->bottom;
                l->distrticstBack->bottom = NULL;
                j++;
            }
            else if (k < 27)
            {
                p3 = s[++k]->bottom;
            }
        }

        // Third loop to delete the heads and make a new empty ones ;
        for (int i = 0; i <= 27; i++) // constant, O(27) ;
        {
            free(s[i]); // Every node that connected to the head is now connected to L so no need to use delete whole list ;
            s[i] = makeEmptyDistrict(NULL);
        }
    }
}

// Insert the info seperated by '|', usually used while reading a PSV file ;
void insertdistricts(char *info, districts d)
{
    if (d == NULL)
    {
        printf("\nError!: The insertion of: %s, Expecting: Empty District!\n", info);
        return;
    }

    town temp;
    temp = makeEmptyTown(NULL);
    int i = 0;     // will move tell end of info ;
    int count = 0; // will increase every '|' to know it's time for the next step ;
    char districtName[50];
    char townName[50];
    char townPopulation[12]; // Town population over 12 didgits is crazy ;
    int listCount = 0;       // will move tell '|' , then return zero ;

    // I could do it by strtok(), decided to do it manually to check for exceptions ;
    while (info[i] != '\0' && info[i] != '\n')
    {
        if (info[i] == '|')
        {
            if (count == 0)
            {
                districtName[listCount] = '\0'; // To close the String and make sure not to randomily fill the String ;
            }
            else if (count == 1)
            {
                townName[listCount] = '\0';
            }
            count++;
            i++;
            listCount = 0;
            continue;
        }

        if (info[i] == ' ')
        {
            if (info[i - 1] == '|' || info[i + 1] == '|' || info[i + 1] == '\0') // will ignore casses like "| " or " |" ;
            {
                i++;
                continue;
            }
        }
        if (count == 0) // Case 1: District name (first seperated statment );
        {
            districtName[listCount++] = info[i];
        }
        else if (count == 1)
        { // Case 2: Town name (second seperated statment );
            townName[listCount++] = info[i];
        }
        else if (count == 2) // Case 2: Town population (third seperated statment );
        {
            townPopulation[listCount++] = info[i];
        }
        i++;
    }

    if (count != 2)
    {
        printf("\nError Occurred: The insertion of: %s ,\tExpecting: Wrong info insertion\n", info); // if there's less or more | , then wrong insertion ;
        return;
    }
    townPopulation[listCount] = '\0';
    temp->population = ConvertString(townPopulation);
    strncpy(temp->townName, townName, sizeof(temp->townName));
    districts d1 = findDistrict(districtName, d);
    (d1 == NULL) ? (addNewDistrtictTown(districtName, d, temp)) : (addToCurrentDistrict(d1, temp)); // if there isn't District with that name it will add a new one and add its town to it ;
}

// Add a new District then add a new town to it ;
void addNewDistrtictTown(char *disName, districts d, town t)
{
    addNewDistrict(disName, d);                 // Add a new District to the district head ;
    addToCurrentDistrict(d->distrticstBack, t); // Add a town to the Added District ;
}

// Add an existed town to a current district ;
void addToCurrentDistrict(districts d, town t)
{
    d->population += t->population;
    t->previous = d->disTownBack;
    (d->nextTown == NULL) ? (d->nextTown = t) : (d->disTownBack->next = t);

    t->previous = d->disTownBack;
    d->disTownBack = t;
    t->dis = d;
    t->next = NULL;
}

// Add a new District ;
void addNewDistrict(char *disName, districts d)
{
    districts d1;
    d1 = makeEmptyDistrict(NULL);
    strncpy(d1->districtName, disName, sizeof(d1->districtName)); // O(k) ;
    d->distrticstBack->bottom = d1;
    d1->top = d->distrticstBack;
    d->distrticstBack = d1;
    d1->bottom = NULL;
}

// Print a District (one country) with it's informations ;
void printDistricts(districts d)
{
    if (d == NULL)
    {
        printf("Error: Can't Print the District!,\tExpect: Empty District");
        return;
    }
    if (d->bottom == NULL)
    {
        return;
    }
    printf("%s District, Population = %d\n", d->bottom->districtName, d->bottom->population);
    town t1 = d->bottom->nextTown;

    // While loop to print all entered District (which will be recursion tell the end of the list) towns ;
    while (t1 != NULL)
    {
        printf("%s, %d  \n", t1->townName, t1->population);
        t1 = t1->next;
    }
    return (printDistricts(d->bottom)); // Recursion call ;
}

// Print a District (one country) with it's informations to the output file (expected name: sorted_districts);
void printOutput(districts d, FILE *f)
{
    if (d == NULL)
    {
        printf("Error: Can't Print the District!,\tExpect: Empty District");
        return;
    }
    if (d->bottom == NULL)
    {
        return;
    }
    fprintf(f, "%s District, Population = %d\n", d->bottom->districtName, d->bottom->population);
    town t1 = d->bottom->nextTown;

    // While loop to print all entered District (which will be recursion tell the end of the list) towns ;
    while (t1 != NULL)
    {
        fprintf(f, "%s, %d  \n", t1->townName, t1->population);
        t1 = t1->next;
    }
    return (printOutput(d->bottom, f)); // Recursion call ;
}

// Print a District (one country) with no more details ;
void printDistrictsNoDetails(districts d)
{
    if (d == NULL)
    {
        printf("Error: Can't Print the District!,\tExpect: Empty District");
        return;
    }

    if (d->bottom == NULL)
    {
        return;
    }
    printf("Distrtict name: %s , population: %d\n", d->bottom->districtName, d->bottom->population);
    return (printDistrictsNoDetails(d->bottom)); // Recursion call ;
}

// Delete a town from an existed district ;
void deleteTown(char *disName, char *tName, districts d)
{
    if (d == NULL)
    {
        printf("Error occurred: Can't delete the town %s,\tExpecting: Empty Head", tName);
        return;
    }

    districts p = findDistrict(disName, d);
    if (p == NULL)
    {
        printf("Error occurred: Can't delete the town %s,\tExpecting: %s no found", tName, disName);
        return;
    }

    town t1 = findATown(disName, tName, d);
    if (t1 == NULL)
    {
        printf("Error occurred: Can't delete the town %s,\tExpecting: %s no found", tName, tName);
        return;
    }
    p->population -= t1->population;

    if (t1->previous && t1->next)
    {
        t1->previous->next = t1->next;
        t1->next->previous = t1->previous;
        free(t1);
        return;
    }

    if (!t1->previous && !t1->next)
    {
        p->disTownBack = NULL;
        p->nextTown = NULL;
        free(t1);
        return;
    }

    else if (!t1->previous)
    {
        p->nextTown = t1->next;
        t1->next->previous = NULL;
        free(t1);
        return;
    }
    else if (!t1->next)
    {
        p->disTownBack = t1->previous;
        t1->previous->next = NULL;
        free(t1);
        return;
    }
}

// Change a town population from an existed District ;
void changeTownPopulation(char *disName, char *townName, int newPopulation, districts d)
{
    if (d == NULL || d->bottom == NULL)
    {
        printf("Error occurred: Can't change the Town: %s,\tExpecting: Empty Head\n", townName);
        return;
    }

    districts p1 = findDistrict(disName, d);
    if (p1 == NULL)
    {
        printf("Error occurred: Can't change the Town: %s,\tExpecting: No match with the District name\n", townName);
        return;
    }

    town t1 = findATown(disName, townName, d);
    if (t1 == NULL)
    {
        printf("Error occurred: Can't change the Town: %s   ,\tExpecting: No match with the town name\n", townName);
        return;
    }

    p1->population += newPopulation - t1->population;
    t1->population = newPopulation;
}

// Delete a district by entering it's name ;
void deleteDistrictByName(char *c, districts d)
{
    if (d == NULL || d->bottom == NULL)
    {
        printf("Error occurred: Can't delete the District with name: %s,\tExpecting: Empty District or Just head\n", c);
        return;
    }

    districts p = findDistrict(c, d);
    if (p == NULL)
    {
        printf("Error occurred: Can't Delete the Distrtict with name:  %s,\tExpecting: No match with the entered name\n", c);
        return;
    }
    deleteDistrict(p);
}

// Delete a District by it's reference ;
void deleteDistrict(districts d1)
{
    if (d1 == NULL)
    {
        printf("Error occurred: Can't delete the Distrtict,\tExpecting: Empty Distrtict");
        return;
    }
    town p = d1->nextTown;
    if (p != NULL)
    {

        while (p->next != NULL)
        {
            p = p->next;
        }
        while (p != NULL)
        {
            town temp = p->previous;
            free(p);
            p = temp;
        }
    }
    districts p2 = d1;
    while (p2->top != NULL)
    {
        p2 = p2->top;
    }

    if (d1->bottom == NULL)
    {
        p2->distrticstBack = d1->top;
        d1->top->bottom = NULL;
        free(d1);
        return;
    }
    d1->top->bottom = d1->bottom;
    d1->bottom->top = d1->top;
    free(d1);
}

// Delete a whole country with its Districts and Towns from the memory ;
void deleteCountry(districts d)
{
    if (d == NULL)
    {
        return;
    }
    districts p = d;
    deleteDistrict(d);
    return deleteCountry(p->bottom);
}

// Print a one District Towns by the District reference ;
void printDistrictTowns(districts d)
{
    town t1 = d->nextTown;
    if (t1 == NULL)
    {
        printf("\nEmpty District\n");
        return;
    }

    while (t1 != NULL)
    {
        printf("Town name: %s  , Population: %d\n", t1->townName, t1->population);
        t1 = t1->next;
    }
}

// To check if the districts has no towns ;
int isEmptyDistrict(districts d)
{
    return d->nextTown == NULL;
}

// Calculate a one country popualtion ;
int calculatePopulation(districts d)
{
    if (d == NULL)
    {
        printf("Error occurred: Can't calculate the Distrtict,\tExpecting: Empty Distrtict or Just head");
        return -1;
    }

    if (d->bottom == NULL)
    {
        return 0;
    }

    districts p = d->bottom;
    int count = 0;
    while (p != NULL)
    {
        count += p->population;
        p = p->bottom;
    }
    return count;
}

// Calculate a one District population
int calculateDistrictPupulation(districts d)
{
    town t1 = d->nextTown;
    int count = 0;
    while (t1 != NULL)
    {
        count += t1->population;
        t1 = t1->next;
    }
    return count;
}

// Calculate a one country popualtion  ( Another method ) ;
int calculateCountryPopulation(districts d)
{
    return (d == NULL) ? 0 : calculateCountryPopulation(d->bottom) + calculateDistrictPupulation(d); // cool method isn't it ?
}

//===============================================================//DistrictLibrary//=================================================================

//==============================================================//TownsLibrary//===================================================================

// Make empty town ;
town makeEmptyTown(town t)
{
    t = (town)malloc(sizeof(struct node1));
    if (t == NULL)
    {
        printf("\nFatal: Failed to memory allocate new town ,\texpect: Oot Of Memory!\n");
        exit(EXIT_FAILURE);
    }
    t->population = 0;
    t->next = NULL;
    t->previous = NULL;
    t->townBack = t;
    t->dis = NULL;
    t->townName[0] = '\0';
    return t;
}

// The minimum town population in the country ;
town minTown(districts d)
{
    if (d == NULL || d->bottom == NULL)
    {
        printf("Can't find the Distrtict with min population ,\tExpecting: Empty Distrtict or Just head"); // P2 == NULL (true)
        return NULL;
    }
    districts p = d->bottom;
    districts firstTown = p;
    while (firstTown != NULL)
    {
        if (firstTown->nextTown != NULL)
        {
            break;
        }
        firstTown = firstTown->bottom;
    }
    if (firstTown == NULL)
    {
        return NULL;
    }

    town min = firstTown->nextTown;
    while (p != NULL)
    {
        town p1 = p->nextTown;
        while (p1 != NULL)
        {
            if (p1->population < min->population)
            {
                min = p1;
            }
            p1 = p1->next;
        }
        p = p->bottom;
    }
    return min;
}

// The maximum town population in the country ;
town maxTown(districts d)
{
    if (d == NULL || d->bottom == NULL)
    {
        printf("Can't find the Distrtict with max population ,\tExpecting: Empty Distrtict or Just head"); // P2 == NULL (true)
        return NULL;
    }
    districts p = d->bottom;
    districts firstTown = p;
    while (firstTown != NULL)
    {
        if (firstTown->nextTown != NULL)
        {
            break;
        }
        firstTown = firstTown->bottom;
    }

    if (firstTown == NULL)
    {
        return NULL;
    }
    town max = firstTown->nextTown;
    while (p != NULL)
    {
        town p1 = p->nextTown;
        while (p1 != NULL)
        {
            if (p1->population > max->population)
            {
                max = p1;
            }
            p1 = p1->next;
        }
        p = p->bottom;
    }
    return max;
}

// Find a town by the district reference ;
town findATown(char *disName, char *tName, districts d)
{
    if (d == NULL || d->bottom == NULL)
    {
        printf("Can't find the Town %s ,\tExpecting: Empty Distrtict or Just head\n", tName);
        return NULL;
    }
    districts p = findDistrict(disName, d);
    if (p == NULL)
    {
        return NULL;
    }

    town t1 = p->nextTown;
    while (t1 != NULL)
    {
        if (!strcmp(t1->townName, tName))
        {
            return t1;
        }
        t1 = t1->next;
    }
    return NULL;
}

// Find a first town in the country with the entered name ;
town findFirstTown(char *tName, districts d)
{
    if (d == NULL)
    {
        printf("Can't find the Town %s ,\tExpecting: Empty Distrtict \n", tName);
        return NULL;
    }
    if (d->bottom == NULL)
    {
        return NULL;
    }

    town t1 = d->bottom->nextTown;
    while (t1 != NULL)
    {
        if (!strcmp(t1->townName, tName))
        {
            return t1;
        }
        t1 = t1->next;
    }
    return findFirstTown(tName, d->bottom);
}

// Sort the towns by their population ascending order ( Radix sort );
void townsSort(districts l)
{
    if (l == NULL)
    {
        return;
    }

    districts s[10]; // number from 0-9 ;
    for (int i = 0; i <= 9; i++)
    {
        s[i] = makeEmptyDistrict(NULL);
    }
    int listSize = districtTownsCount(l); // Get the total list size ;
    int most = mostTownDigits(l);         // Get the most element digits ;
    int n = 1, m = 10;
    for (int i = 0; i < most; i++) // depends on the most digit value O(k) ;
    {
        town t1 = l->nextTown;
        // First loop to list the charachter in its correct location ;
        while (t1 != NULL) // will see all elements O(n) ;
        {
            int val = (t1->population / n) % m; // Get the value of digit by the current loop ;
            town temp = t1;
            t1 = t1->next;
            temp->previous = s[val]->disTownBack;
            (s[val]->nextTown == NULL) ? (s[val]->nextTown = temp) : (s[val]->disTownBack->next = temp);

            s[val]->disTownBack = temp;
            temp->dis = s[val];
            temp->next = NULL;
        }
        int j = 0, k = 0;
        l->disTownBack = NULL;
        l->nextTown = NULL;
        town t2 = s[k]->nextTown;

        // Second loop to return the charchters after 'i' sort to the list ;
        while (j < listSize) // will see all elements O(n) ;
        {
            if (t2 != NULL)
            {

                town temp = t2;
                t2 = t2->next;
                temp->previous = l->disTownBack;
                (l->nextTown == NULL) ? (l->nextTown = temp) : (l->disTownBack->next = temp);

                l->disTownBack = temp;
                temp->dis = l;
                temp->next = NULL;
                j++;
            }
            else if (k < 9)
            {
                t2 = s[++k]->nextTown;
            }
        }
        n *= 10;
        // Third loop to delete the heads and make a new empty ones ;
        for (int i = 0; i <= 9; i++) // constant, O(10) ;
        {
            free(s[i]); // Every node that connected to the head is now connected to L so no need to use delete whole list ;
            s[i] = makeEmptyDistrict(NULL);
        }
    }
    townsSort(l->bottom); // to sort every district ;
}

//==============================================================//TownsLibrary//===================================================================

//====================================================================Others========================================================================

// Converting a String number into integer (used for insert from PSV file) ;
int ConvertString(char *str)
{
    int result = 0;
    for (int i = 0; str[i] != '\0'; ++i)
    {
        if (str[i] >= '0' && str[i] <= '9')
        {
            result = result * 10 + (str[i] - '0'); // increse 10 for each digit ;
        }
        else
            continue; // just ignore any thing that is not a number ;
    }
    return result;
}

// To get a Districts count in a country (used for radix sort) ;
int districtSize(districts d)
{
    int count = 0;
    districts p = d;
    // loop to check for every element ;
    while (p->bottom != NULL)
    {
        p = p->bottom;
        count++;
    }
    return count;
}

// Most District name length in a country (used for radix sort)
int mostDistrictElement(districts d)
{
    districts p = d->bottom;
    size_t max = strlen(p->districtName); // Unsigned integer ;
    while (p->bottom != NULL)
    {
        max = (max < strlen(p->bottom->districtName)) ? strlen(p->bottom->districtName) : max;
        p = p->bottom;
    }
    return max;
}

// To get a Towns count in a District (used for radix sort) ;
int districtTownsCount(districts d)
{
    town t1 = d->nextTown;
    int count = 0;
    while (t1 != NULL)
    {
        t1 = t1->next;
        count++; // Keep increasing by one tell the end of the list ;
    }
    return count;
}

// Most Town population in the District (used for radix sort) ;
int mostTownDigits(districts d)
{
    town t1 = d->nextTown;
    int max = 0;
    // Get thre max number ;
    while (t1 != NULL)
    {
        max = (max < t1->population) ? t1->population : max;
        t1 = t1->next;
    }
    int didgits = 0;
    // To check max number didgits count ;
    while (max != 0)
    {
        max /= 10;
        didgits++;
    }
    return didgits;
}

//==============================================================//Others//=====================================================================
// A wise man once said: if the code works don't touch it ;