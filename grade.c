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

int searchStudent(char inputName, student* inputStudent, int studentLen, student* students) {
    student currentStudent;
    int idx;

    for (idx = 0; idx < studentLen; idx++) {
        currentStudent = students[idx];
        if (strcmp(currentStudent.name, inputName)) {
            *(inputStudent)->name = inputName;
            return 0;
        }
    }
    return -1;
}

void inputStudent(student* students, int studentLen) {
    if (studentLen != MAX_STUDENTS){
        student newStudent;

        printf("Enter student name: ");
        fgets(newStudent.name, sizeof(newStudent.name), stdin);
        sscanf(newStudent.name, "%[^\n]", newStudent.name);

        printf("Enter class number: ");
        scanf("%d", &newStudent.classNumber);

        // add student's subject 1 by 1
        for (newStudent.subjectLen = 0; newStudent.subjectLen < MAX_SUBJECTS; 
            newStudent.subjectLen++) {
            char subjectName = newStudent.subjects[newStudent.subjectLen].name;
            printf("Enter subject name %d: ", newStudent.subjectLen + 1);
            fgets(subjectName, sizeof(subjectName), stdin);
            sscanf(subjectName, "%[^\n]", subjectName);
        }

        students[studentLen] = newStudent;
        studentLen++;
        
        printf("Student put in database!\n");
    }
    else {
        printf("Max number of students reached!\n");
    }
}

void addGrade(int studentLen, student* students) {
    if (studentLen > 0) {
        student currentStudent;
        char inputName[MAX_NAME_LEN];
        
        printf("Enter student name: ");
        fgets(inputName, sizeof(inputName), stdin);
        sscanf(inputName, "%[^\n]", inputName);

        // checks if student is in database via name search
        int found = searchStudent(inputName, &currentStudent, studentLen, 
            students);
        while (found == -1) {
            
            // user can leave if they want to exit
            if (strcmp(inputName, "exit")) {
                return;
            }
            /* if student is not found, either user can keep searching or 
            can leave the system */
            printf("Enter student name (type 'exit' to return to menu): ");
            fgets(inputName, sizeof(inputName), stdin);
            sscanf(inputName, "%[^\n]", inputName);


            found = searchStudent(inputName, &currentStudent, studentLen, 
                students);
        }

        int subLen = currentStudent.subjectLen;
        subject* subs = currentStudent.subjects;

        int idx;
        int inputMark;
        char option[3];

        for (idx = 0; idx < subLen; idx++) {
            printf("Enter mark for %s", subs[idx]);
            scanf("%d", &inputMark);
            subs[idx].mark = calculateGrade(inputMark);

            printf("Enter:\n");
            printf("'yes' to comment\n");
            printf("'no' to skip: ");
            scanf("%s", &option);
            if (strcmp(option, "yes")) {
                addComment(&currentStudent);
            }
        }
    }
    else {
        printf("There are no students to grade!\n");
    }
}

