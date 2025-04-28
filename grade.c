#include <stdio.h>
#include <string.h>
#include "grade.h" // include function prototypes

// calculate HSC bands via provided numerical mark
int calculateGrade(int mark) {
    if (mark >= 0 && mark <= 100) {
        if (mark >= 90) {
            return 6;
        }
        else if (mark >= 80) {
            return 5;
        }
        else if (mark >= 70) {
            return 4;
        }
        else if (mark >= 60) {
            return 3;
        }
        else if (mark >= 50) {
            return 2;
        }
        return 1;
    }
    // sends out error integer if mark exceeds boundaries
    return -1;
}

Student searchStudent(char* name, int studentLen, Student* students) {
    student currentStudent;
    int idx;

    for (idx = 0; idx < studentLen; idx++) {
        currentStudent = *(students[idx]);
        if (strcmp(student->name, name)) {
            return student;
        }
    }

    return NULL;
}

void inputStudent(Student* students, int studentLen) {
    if (studentLen != MAX_STUDENTS){
        student newStudent;

        printf("Enter student name: ");
        fgets(newStudent.name, sizeof(newStudent.name), stdin);
        sscanf(newStudent.name, "%[^\n]", newStudent.name);

        printf("Enter class number: ");
        scanf("%d", &newStudent.classNumber);

        *(students[studentLen]) = newStudent;
        studentLen++;
        
        printf("Student put in database!\n");
    }
    else {
        printf("Max number of students reached!\n");
    }
}

void addGrade(int studentLen, Student* students) {
    if (studentLen > 0) {
        char inputNam
    }
    else {
        printf("There are no students to grade!\n");
    }
}

