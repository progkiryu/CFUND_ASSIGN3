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
}
typedef struct Subject subject;

struct Student {
    // allocate memory for name
    char name[MAX_NAME_LEN];
    int classNumber;
    
    Subject subjects[MAX_SUBJECTS];
    int subjectLen = 0; // keep track of subjects
    double average;
}
typedef struct Student student;

int calculateGrade(int mark);

void addGrade(int studentLen, Student* students);

char* addComment(Student* student);

void inputStudent(Student* students, int studentLen);

Student searchStudent(char* name, int studentLen, Student* students);

void removeGrade

// encryption functions
// compression functions

#endif
