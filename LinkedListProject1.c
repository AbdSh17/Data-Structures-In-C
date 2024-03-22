#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct node1 courseNode;
typedef courseNode *courseList;
typedef struct node2 studentNode;
typedef studentNode *studentList;
typedef struct node *list;
struct node1 {
    char courseSymbol[12];
    int year;
    int max;
    char courseName[100];
    courseList next;
    courseList track;
    int count;
};

struct node2 {
    char firstCourseSymbol[12];
    char secondCourseSymbol[12];
    char thirdCourseSymbol[12];
    char fourthCourseSymbol[12];
    char fifthCourseSymbol[12];
    int id ;
    int year;
    char studentName[30];
    studentList next;
    studentList track;
};

struct node {
    int data;
    list track;
    list next;
};


void Delete(int, struct node *);
void insert(int, list);
int isLast(list, list);
void deleteList(list);
void printList(struct node *);
int getMost(int [], int);
void sortArray(int[], int);
int ConvertString(char *);
void insertStudent(char[], studentList);
void insertCourse(char[], courseList);
int isAvailable(char[], courseList);
courseList makeEmptyCourse(courseList);
studentList makeEmptyStudent(studentList);
struct node *makeEmpty(struct node *);
int findCourseIndex(char[], courseList);
void deleteStudentList(studentList);
int isAppropriateYear(char [], studentList, courseList);
int isAllowed(char[], studentList, courseList);
void insertStudentCourse(studentList[], studentList, courseList);
void makeEmptyStudentArray(studentList[], int);
int findCourseLength(courseList);
courseList findCourse(char[], courseList);
void copyStudent(studentList, studentList);
void printCourse(studentList);
void printStudent(studentList);
courseList findID(int, studentList);
void sortCourse(studentList);
int Studentsize(studentList);
// Node to make an emoty course ;
courseList makeEmptyCourse(courseList l){
if(l != NULL){
   deleteList(l);
   }
l = (courseList)malloc(sizeof(courseNode)) ;
if(l == NULL)
    printf("No space in the memory");
    l->next = NULL ;
    l->track = l;
    l->count = 0;
    return l ;
}
// Node to make an emoty student ;
studentList makeEmptyStudent(studentList l){
    if(l != NULL){
        deleteStudentList(l);
   }
   l = (studentList)malloc(sizeof(studentNode));
   if (l == NULL)
       printf("No space in the memory wtf");
   l->next = NULL;
   l->track = l;
   return l;
}
// Node to make an emoty normal List ;
struct node *makeEmpty(struct node *l){
    if(l != NULL){
        deleteList(l);
   }
l = (list)malloc(sizeof(struct node)) ;
    if(l == NULL)
        printf("No space in the memory");
    l->next = NULL ;
    l->track = l;
    return l ;
}

//===================================================Main===================================================

int main() {
    int operation = 0;
    courseList course = makeEmptyCourse(NULL);
    studentList student = makeEmptyStudent(NULL);

    
    /*
abd alraheem shuaibi#1220148#math331#comp133#encs130#comp333#comp242 ;
saleh Shawer#1230128#comp242#comp133#encs130#comp333#math331
Abd awalmeh#1221199#comp243#comp133#encs130#comp333#math331
Nabeel swafteh#1220003#math331#comp333#encs130#comp133#comp242


data structer,comp242,122,55 ;
c-programin,comp133,122,55
digital,encs130,122,55
data base,comp333,122,55
differential equation,math331,122,55
*/

    insertCourse("data structer,comp242,122,55", course);
    insertCourse("c-programin,comp133,122,55", course);
    insertCourse("digital,encs130,122,55", course);
    insertCourse("data base,comp333,121,55", course);
    insertCourse("differential equation,math331,122,2", course);

    insertStudent("abd alraheem shuaibi#1210148#math331#comp133#encs130#comp333#comp242", student);
    insertStudent("saleh Shawer#1220128#comp242#comp133#encs130#comp333#math331", student);
    insertStudent("Abd sawalmeh#1221199#comp243#comp133#encs130#comp333#math331", student);
    insertStudent("Nabeel swafteh#1210003#math331#comp333#encs130#comp133#comp242", student);
    

    //     printf("Enter an operation:\n1-Add course\n2-Add a Student\n3-Exit\n");
    //     scanf("%d", &operation);
    //     getchar();
    // while (operation != 3)
    // {
    //     char courseInfo[100];
    //     char studentInfo[100];
    //     switch (operation) {
    //         case 1:
    //             printf("Enter full Course info:\n");
    //             fgets(courseInfo, sizeof(courseInfo), stdin);
    //             insertCourse(courseInfo, course);
    //             break;
    //         case 2:
    //             printf("Enter full Student info:\n");
    //             fgets(studentInfo, sizeof(studentInfo), stdin);
    //             insertStudent(studentInfo, student);
    //             break;
    //         case 3:
    //             printf("Invalid operation!\n");
    //             break;
    //     }
    //     printf("Enter an operation:\n1-Add course\n2-Add a Student\n3-Exit\n");
    //     scanf("%d", &operation);
    //     getchar();
    // }

    studentList studentArray[10];
    makeEmptyStudentArray(studentArray, ((sizeof(studentArray)/sizeof(studentArray[0]))));

    insertStudentCourse(studentArray, student, course);
    printf("Diff\n");
    printCourse(studentArray[0]);
    printf("\n");
    printCourse(studentArray[1]);
    printf("\n");
    printCourse(studentArray[2]);
    printf("\n");
    printCourse(studentArray[3]);
    printf("\n");
    printCourse(studentArray[4]);
    return 0;

    /*
abd alraheem shuaibi#1220148#math331#comp133#encs130#comp333#comp242 ;
saleh Shawer#1230128#comp242#comp133#encs130#comp333#math331
Abd awalmeh#1221199#comp243#comp133#encs130#comp333#math331
Nabeel swafteh#1220003#math331#comp333#encs130#comp133#comp242


data structer,comp242,122,55 ;
c-programin,comp133,122,55
digital,encs130,122,55
data base,comp333,122,55
differential equation,math331,122,55
*/
}

//===================================================Main===================================================

// Print course student particibater ;
void printCourse(studentList s){
    sortCourse(s);
    studentList s1 = s->next;
    if(s1 == NULL)
        printf("empty Course , no students has applied yet!");
    while (s1 != NULL)
    {
        printStudent(s1);
        printf("\n");
        s1 = s1->next;
    }
}

// sort normal list ;
void sortArray(int values[] , int size){
    list s[10] ;
    list p[10] ;
    for(int i=0 ; i<=9 ; i++){
        s[i] = makeEmpty(NULL);
        p[i] = NULL ;
    }
    int n=1 , m=10 ;
    for(int i=0 ; i<getMost(values , size) ; i++){
        for(int i=0 ; i<size ; i++){
            int val = (values[i]/n) % m;
           insert(values[i], s[val]);
            p[val] = s[val]->next ;
        }
            int i=0 , k=0;
            while(i < size && k<=9) {
                    if(p[k] != NULL){
                         values[i] = p[k]->data;
                            i++;
                    if(p[k]->next != NULL){
                        p[k] = p[k]->next ;
                        k-- ;
                     }
                    }
                    k++ ;
            }
            n*=10  ;
            for(int i=0 ; i<=9 ; i++){
                s[i] = makeEmpty(NULL);
                p[i] = NULL;
            }
        }
}

void sortCourse(studentList l){
    int size = Studentsize(l);
    int *values = (int*)malloc(size * sizeof(int));
    if(values == NULL){
        printf("Array allocation failed!");
    }
    studentList p = l->next;
    for (int i = 0; i < size; i++ , p = p->next)
    {
        values[i] = p->id;
    }
    sortArray(values, size);
    studentList l1 = makeEmptyStudent(NULL);
    studentList p1 = l1;
    studentList p2 = l;
    //printf("\n\n================================================\n\n");
    //l = makeEmptyStudent(l);
    for (int i = 0; i < size; i++, p1 = p1->next)
    {
        studentList temp = makeEmptyStudent(NULL);
        copyStudent(temp, findID(values[i], l));
        p1->next = temp;
    }
    //studentList p2 = l; 
    //printf("\n\n================================================\n\n");
    l->next = l1->next;
    l->track = l1->track;
    free(values);
    //deleteStudentList(p2->next);
}

// insert normal list ;
void insert(int x, list l) {
    list temp;
    list track = l;
    temp = (list)malloc(sizeof(struct node));
    
    while (track->next != NULL) {
        track = track->next;
    }
    temp->next = NULL;
    track->next = temp;
    temp->data = x;
}

void insertStudentCourse(studentList l [] , studentList s , courseList c){
    studentList s1 = s->next;
    studentList l1[10];
    makeEmptyStudentArray(l1, ((sizeof(l1)/sizeof(l1[0]))));
    for (int i = 0; i < 10; i++)
    {
        l1[i] = l[i];
    }
    while (s1 != NULL)
    {
        if(isAllowed(s1->firstCourseSymbol,s1,c->next) && findCourse(s1->firstCourseSymbol, c->next)->count < findCourse(s1->firstCourseSymbol, c->next)->max){
            studentList temp = makeEmptyStudent(NULL);
            copyStudent(temp, s1);
            l1[findCourseIndex(s1->firstCourseSymbol,c->next)]->next = temp;
            l1[findCourseIndex(s1->firstCourseSymbol, c->next)] = l1[findCourseIndex(s1->firstCourseSymbol, c->next)]->next;
            findCourse(s1->firstCourseSymbol, c->next)->count++;
        }
        else{
            printf("studetn with id: %d can't join the course with sympol %s  ", s1->id, s1->firstCourseSymbol);
        }
            
        if(isAllowed(s1->secondCourseSymbol,s1,c->next) && findCourse(s1->secondCourseSymbol, c->next)->count < findCourse(s1->secondCourseSymbol, c->next)->max){
            studentList temp = makeEmptyStudent(NULL);
            copyStudent(temp, s1);
            l1[findCourseIndex(s1->secondCourseSymbol,c->next)]->next = temp;
            l1[findCourseIndex(s1->secondCourseSymbol, c->next)] = l1[findCourseIndex(s1->secondCourseSymbol, c->next)]->next;
            findCourse(s1->secondCourseSymbol, c->next)->count++;
        }
        else{
            printf("studetn with id: %d can't join the course with sympol %s  ", s1->id, s1->secondCourseSymbol);
        }
            
        if(isAllowed(s1->thirdCourseSymbol,s1,c->next) && findCourse(s1->thirdCourseSymbol, c->next)->count < findCourse(s1->thirdCourseSymbol, c->next)->max){
            studentList temp = makeEmptyStudent(NULL);
            copyStudent(temp, s1);
            l1[findCourseIndex(s1->thirdCourseSymbol,c->next)]->next = temp;
            l1[findCourseIndex(s1->thirdCourseSymbol, c->next)] = l1[findCourseIndex(s1->thirdCourseSymbol, c->next)]->next;
            findCourse(s1->thirdCourseSymbol, c->next)->count++;
        }
        else{
            printf("studetn with id: %d can't join the course with sympol %s  ", s1->id, s1->thirdCourseSymbol);
        }
        
        if(isAllowed(s1->fourthCourseSymbol,s1,c->next) && findCourse(s1->fourthCourseSymbol, c->next)->count < findCourse(s1->fourthCourseSymbol, c->next)->max){
            studentList temp = makeEmptyStudent(NULL);
            copyStudent(temp, s1);
            l1[findCourseIndex(s1->fourthCourseSymbol,c->next)]->next = temp;
            l1[findCourseIndex(s1->fourthCourseSymbol, c->next)] = l1[findCourseIndex(s1->fourthCourseSymbol, c->next)]->next;
            findCourse(s1->fourthCourseSymbol, c->next)->count++;
        }
        else{
            printf("studetn with id: %d can't join the course with sympol %s  ", s1->id, s1->fourthCourseSymbol);
        }
        if(isAllowed(s1->fifthCourseSymbol, s1, c->next) && findCourse(s1->fifthCourseSymbol, c->next)->count < findCourse(s1->fifthCourseSymbol, c->next)->max){
            studentList temp = makeEmptyStudent(NULL);
            copyStudent(temp, s1);
            l1[findCourseIndex(s1->fifthCourseSymbol,c->next)]->next = temp;
            l1[findCourseIndex(s1->fifthCourseSymbol, c->next)] = l1[findCourseIndex(s1->fifthCourseSymbol, c->next)]->next;
            findCourse(s1->fifthCourseSymbol, c->next)->count++;
        }
        else{
            printf("studetn with id: %d can't join the course with sympol %s  ", s1->id, s1->fifthCourseSymbol);
        }
        s1 = s1->next;
    }
}

// insert studetn to his linked list ;
void insertStudent(char c [] , studentList l){
    studentList temp;
    studentList track = l;
    temp = (studentList)malloc(sizeof(studentNode));
    while (track->next != NULL) {
        track = track->next;
    }
    int i = 0;
    int count = 0;
    int listCount = 0;
    char idString[12];
    while (c[i] != '\0' && c[i] != '\n'){
        if (count == 0){
            if(c[i] == '#'){
                count++;
                temp->studentName[listCount] = '\0';
                i++;
                listCount = 0;
                continue;
            }
            else
            temp->studentName[listCount++] = c[i];
        }
        else if(count == 1){
            if(c[i] == '#'){
                count++;
                idString[listCount] = '\0';
                i++;
                listCount = 0;
                continue;
            }
            else
            idString[listCount++] = c[i];
        }
        else if(count == 2){
                if(c[i] == '#'){
                count++;
                temp->firstCourseSymbol[listCount] = '\0';
                i++;
                listCount = 0;
                continue;
            }
            else
            temp->firstCourseSymbol[listCount++] = c[i];
        }
        else if(count == 3){
            if(c[i] == '#'){
                count++;
                temp->secondCourseSymbol[listCount] = '\0';
                i++;
                listCount = 0;
                continue;
            }
            temp->secondCourseSymbol[listCount++] = c[i];
        }
        else if(count == 4){
            if(c[i] == '#'){
                count++;
                temp->thirdCourseSymbol[listCount] = '\0';
                i++;
                listCount = 0;
                continue;
            }
            temp->thirdCourseSymbol[listCount++] = c[i];
        }
        else if(count == 5){
            if(c[i] == '#'){
                count++;
                temp->fourthCourseSymbol[listCount] = '\0';
                i++;
                listCount = 0;
                continue;
            }
            temp->fourthCourseSymbol[listCount++] = c[i];
        }
        else if(count == 6){
            temp->fifthCourseSymbol[listCount++] = c[i];
        }
        i++;
    }
    temp->fifthCourseSymbol[listCount] = '\0';
    temp->id = ConvertString(idString);
    temp->year = temp->id / 10000;
    temp->next = NULL;
    track->next = temp;
}

// copy student info to temp ;
void copyStudent(studentList temp , studentList s){
    strcpy(temp->firstCourseSymbol, s->firstCourseSymbol);
    strcpy(temp->secondCourseSymbol, s->secondCourseSymbol);
    strcpy(temp->thirdCourseSymbol, s->thirdCourseSymbol);
    strcpy(temp->fourthCourseSymbol, s->fourthCourseSymbol);
    strcpy(temp->fifthCourseSymbol, s->fifthCourseSymbol);
    strcpy(temp->studentName, s->studentName);
    temp->id = s->id;
    temp->year = s->year;
}

// insert course to it's linked list ;
void insertCourse(char c [] , courseList l){
    courseList temp;
    courseList track = l;
    temp = (courseList)malloc(sizeof(courseNode));

    while (track->next != NULL) {
        track = track->next;
    }
    int i = 0;
    int count = 0;
    char yearString[6];
    char maxString[6];
    int listCount = 0;

    while (c[i] != '\0' && c[i] != '\n'){
        if (count == 0){
            if(c[i] == ','){
                count++;
                temp->courseName[listCount] = '\0';
                i++;
                listCount = 0;
                continue;
            }
            else
            temp->courseName[listCount++] = c[i];
        }
        else if(count == 1){
            if(c[i] == ','){
                count++;
                temp->courseSymbol[listCount] = '\0';
                i++;
                listCount = 0;
                continue;
            }
            else
            temp->courseSymbol[listCount++] = c[i];
        }
        else if(count == 2){
                if(c[i] == ','){
                count++;
                yearString[listCount]= '\0';
                i++;
                listCount = 0;
                continue;
            }
            else
            yearString[listCount++] = c[i];
        }
        else if(count == 3){
            maxString[listCount++] = c[i];
        }
        i++;
    }
    maxString[listCount] = '\0';
    temp->year = ConvertString(yearString);
    temp->max = ConvertString(maxString);
    temp->next = NULL;
    temp->count = 0;
    track->next = temp;
    
}

// converting string to an integer ;
int ConvertString(char *str) {
    int result = 0;
    for (int i = 0; str[i] != '\0'; ++i) {
        if (str[i] >= '0' && str[i] <= '9') {
            result = result * 10 + (str[i] - '0');
        } else {
            break;
        }
    }
    return result;
}

// find if the course is Available ;
int isAvailable(char c [] , courseList l){
    courseList p = l;
    while (p != NULL)
    {
        if(strcmp(p->courseSymbol, c) == 0)
            return 1;
        p = p->next;
    }
    return 0;
}

// find if the course and return it ;
courseList findCourse(char c [] , courseList l){
    courseList p = l;
    while (p != NULL){
        if(strcmp(p->courseSymbol, c) == 0)
            return p;
        p = p->next;
    }
    return NULL;
}

courseList findID(int id , studentList l){
    studentList p = l->next;
    while (p != NULL)
    {
        if(p->id == id)
            return p;
        p = p->next;
    }
    printf("There's no such student with this id");
    return p;
}

// find if this student year is appropriat ;
int isAppropriateYear(char c [] , studentList s , courseList l){
    return s->year <= findCourse(c,l)->year;
}

// merge functions to see if student can join this course ;
int isAllowed(char c [] , studentList s , courseList l){
    return (isAvailable(c, l) && isAppropriateYear(c , s, l));
}

// find the course index ;
int findCourseIndex(char c [] , courseList l){
    courseList p = l;
    int count = 0;
    while (p != NULL)
    {
        if(strcmp(p->courseSymbol, c) == 0)
            return count;
        count++;
        p = p->next;
    }
    return -1;
}

// find course list length ;
int findCourseLength(courseList l){
    courseList p = l->next;
    int count = 0;
    while (p != NULL){
        count++;
        p = p->next;
    }
    return count;
}

// make for each index empty student head ;
void makeEmptyStudentArray(studentList l [] , int size){
        for (int i = 0; i < 10; i++)
        {
            l[i] = makeEmptyStudent(NULL);
        }
}

    // function for sort ;
int getMost(int array[], int size){
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

int getMostStudent(studentList s){
    int max = s->next->id ;
    studentList s1 = s->next;
    while (s1 != NULL)
    {
        if (max < s1->id)
            max = s1->id;
        s1 = s1->next;
    }
        int count = 0;
        while(max != 0 ){
            max /= 10 ;
            count++ ;
        }
        return count ;
}

// is empty for normal list ;
int isEmpty(struct node *l){
return l->next == NULL ;
}

// is empty for course list ;
int isEmptyCourse(courseList l){
return l->next == NULL ;
}

// is empty for student list ;
int isEmptyStudent(studentList l){
return l->next == NULL ;
}

// is last for normal list ;
int isLast(struct node *p , struct node *l){
return p->next == NULL ;
}

// is last for course list ;
int isLastCourse(courseList p , courseList l){
return p->next == NULL ;
}

// Print student info ;
void printStudent(studentList s){
    printf("Student Name: %s  ", s->studentName);
    printf("Student ID: %d  ", s->id);
}

// is empty for student list ;
int isLastStudent(studentList p , studentList l){
return p->next == NULL ;
}

struct node *find(int x , struct node *l){

struct node *p = l->next;

while(p != NULL && p->data != x)
    p = p->next ;
return p ;

};

struct node *findPrevious(int x , struct node *l){

struct node *p = l;

while(p->next != NULL && p->next->data != x)
    p = p->next ;
return p ;
}

void Delete(int x , struct node *l){

struct node *p;
struct node *temp ;

p = findPrevious(x , l) ;
if(! isLast(p , l)){
    temp = p->next ;
    p->next = temp->next;
    free(temp) ;
}
}

void deleteList(struct node *l){
struct node *p ;
while(! isLast(p,l))
{
    struct node *temp = p ;
    p = temp->next ;
    free(temp) ;
}
}

void deleteStudentList(studentList l){
studentList p = l->next;
l->next = NULL;
while(p->next != NULL)
{
    studentList temp = p ;
    p = temp->next ;
    free(temp) ;
}
}

void printList(struct node *l){
struct node *p = l->next ;

if(l == NULL)
    printf("there's no list") ;
if(p == NULL)
    printf("the list is empty") ;
while(p != NULL){
    printf("%d  " , p->data) ;
    p = p->next ;
}
}

int size(struct node *l){
struct node *p = l->next ;
int count = 0 ;

while(p != NULL){
  count++;
  p = p->next ;
}
return count ;
}

int Studentsize(studentList l){
studentList p = l->next ;
int count = 0 ;

while(p != NULL){
  count++;
  p = p->next ;
}
return count ;
}