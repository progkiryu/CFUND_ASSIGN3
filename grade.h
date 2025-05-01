#ifndef GRADE_H
#define GRADE_H

/* define constant numerical boundaries */
#define MAX_SUBJECTS 5
#define MAX_SUB_LEN 20
#define MAX_COM_LEN 50
#define MAX_STUDENTS 10
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
    int subjectLen; /* keep track of subjects */
    double average;
};
typedef struct Student student;

int calculateGrade(int mark); /* done (denver) */

void addGrades(int studentLen, student* students); /* in progress (denver) */

/*void removeGrades(int studentLen, student* students);  Kevin */

void addComment(student* inputStudent, int subjectLen); /* in progress (denver) */

/*void removeComment(student* inputStudent);  Kevin */

void inputStudent(student* students, int* studentLen);

/*void removeStudent(int studentLen);*/

int searchStudent(char inputName[MAX_NAME_LEN], student* inputStudent, int studentLen, student* students); /* done (denver) */

void flush(char *arr, int lengthofArray); /* done (Andrew) */

/* encryption functions */
void encryptFile(); /* (Andrew) work in progress */
void decryptFile(); /* (Andrew) work in progress */

/* compression functions */

#endif
