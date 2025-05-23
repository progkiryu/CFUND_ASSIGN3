#ifndef GRADE_H
#define GRADE_H

/*debug mode*/
/*comment line below to exit debug mode, uncomment to enter debug mode*/
/*#define DEBUG*/

#ifdef DEBUG
    #define debug(...) printf(__VA_ARGS__)
#else
    #define debug(...)
#endif

/* define constant numerical boundaries */
#define MAX_STUDENTS 10
#define MAX_SUBJECTS 5
#define MAX_SUB_LEN 20
#define MAX_COM_LEN 50
#define MAX_NAME_LEN 50

struct Subject {
    char name[MAX_SUB_LEN];
    int mark;
    char comment[MAX_COM_LEN];
};
typedef struct Subject subject;

struct Student {
    char name[MAX_NAME_LEN];
    int classNumber;
    
    subject subjects[MAX_SUBJECTS];
    double average;

    int filled;
};
typedef struct Student student;

/* linked list node */
struct Node {
    struct Node* next;
    student nodeStudent;
};
typedef struct Node node;

void inputStudent(node** inputNode, int* studentLen); /* done (denver) */

node* searchStudent(char inputName[MAX_NAME_LEN], node* inputNode); /* done (denver) */

void removeStudent(node** inputNode, int* studentLen); /*done (Andrew)*/

void addGrades(int studentLen, node* inputNode); /* done (denver) */

int calculateGrade(int mark); /* done (denver) */

void displayStudents(node* inputNode, int studentLen); /* done (denver)*/

void displayGrades(); /* done (Andrew) */

void addComment(subject* inputSubject); /* done (denver) */

void saveToFile(node* head);/* Kevin */

void deleteFile(void);/* Kevin */

void flush(char *arr, int lengthofArray); /* done (Andrew) */

/* encryption functions */
void encryptFile(char* name); /* done (Andrew)  */
void decryptFile(char* name, node* inputNode); /* done (Andrew)  */

/* compression and decompression functions */
void compressStudentGrades(char* inputName, node* inputNode);/*Subnoor*/
void decompressStudentGrades(char* inputName);  /*Subnoor*/

#endif
