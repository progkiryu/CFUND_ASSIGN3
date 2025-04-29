#ifndef GRADE_H // establish header file
#define GRADE_H

// define constant numerical boundaries
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
    // allocate memory for name
    char name[MAX_NAME_LEN];
    int classNumber;
    
    subject subjects[MAX_SUBJECTS];
    int subjectLen; // keep track of subjects
    double average;
};
typedef struct Student student;

int calculateGrade(int mark); // done (denver)

void addGrades(int studentLen, student* students); // done (denver)

void removeGrades(int studentLen, student* students);

char* addComment(student* student); // done (denver)

void removeComment(student* student);

void inputStudent(student* students, int studentLen);

void removeStudent(int studentLen);

int searchStudent(char* name, int studentLen, student* students); // done (denver)

// encryption functions
// compression functions

#endif
