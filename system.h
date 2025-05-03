#ifndef GRADE_H
#define GRADE_H

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
    int subjectLen;
    double average;
};
typedef struct Student student;

/* linked list node */
struct Node {
    struct Node* next;
    student nodeStudent;
};
typedef struct Node node;

void inputStudent(node** inputNode, int* studentLen); /* done (denver) */

int searchStudent(char inputName[MAX_NAME_LEN], student* inputStudent, node* inputNode); /* done (denver) */

/* void removeStudent(node** inputNode, int* studentLen); (Andrew)*/

void addGrades(int studentLen, node* inputNode); /* done (denver) */

int calculateGrade(int mark); /* done (denver) */

void displayStudents(node* inputNode, int studentLen); /* done (denver)*/

/* void displayGrades(); (Andrew)*/

void addComment(student* inputStudent, int subjectLen); /* done (denver) */

/*void removeGrades(int studentLen, student* students);  Kevin */

/*void removeComment(student* inputStudent);  Kevin */

/*void removeStudent(int studentLen);*/

void flush(char *arr, int lengthofArray); /* done (Andrew) */

/* encryption functions */
void encryptFile(); /* (Andrew) work in progress */
void decryptFile(); /* (Andrew) work in progress */

/* compression functions */

#endif
