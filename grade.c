#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "grade.h" /* include function prototypes */

/* calculate HSC bands via provided numerical mark */
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
    /* sends out error integer if mark exceeds boundaries */
    return -1;
}

int searchStudent(char inputName[MAX_NAME_LEN], student* inputStudent, 
    node* inputNode) {
    student currentStudent;

    while (inputNode != NULL) {
        currentStudent = inputNode->nodeStudent;
        if (strcmp(currentStudent.name, inputName) == 0) {
            *inputStudent = currentStudent;
            return 0;
        }
        inputNode = inputNode->next;
    }
    return -1;
}

void inputStudent(node* inputNode, int* studentLen) {
    if (*studentLen != MAX_STUDENTS) {
        student newStudent;

        printf("Enter student name: ");
        fgets(newStudent.name, sizeof(newStudent.name), stdin);
        sscanf(newStudent.name, "%[^\n]", newStudent.name);
        
        int found;
        found = searchStudent(newStudent.name, &newStudent, inputNode);
        while (found == 0) {
            printf("Student already exists!\n");
            printf("Enter student name (type 'exit' to return to menu): ");
            fgets(newStudent.name, sizeof(newStudent.name), stdin);
            sscanf(newStudent.name, "%[^\n]", newStudent.name);

            flush(newStudent.name, strlen(newStudent.name));
                        
            if (strcmp(newStudent.name, "exit") == 0) {
                return;
            }
            found = searchStudent(newStudent.name, &newStudent, inputNode);
        } 

        flush(newStudent.name, MAX_NAME_LEN);

        printf("Enter class number: ");
        scanf("%d", &newStudent.classNumber);
        getchar();

        int idx;
        /* add student's subject 1 by 1 */
        for (idx = 0; idx < MAX_SUBJECTS; idx++) {
            printf("Enter subject name %d: ", idx + 1);
            fgets(newStudent.subjects[idx].name, 
                sizeof(newStudent.subjects[idx].name), stdin);
            sscanf(newStudent.subjects[idx].name, "%[^\n]", 
                newStudent.subjects[idx].name);

            flush(newStudent.subjects[idx].name, MAX_SUB_LEN);
        }

        inputNode->nodeStudent = newStudent;
        inputNode->next = (node*)malloc(1 * sizeof(node));
        inputNode = inputNode->next;
        *studentLen += 1;
        
        printf("Student put in database!\n");
    }
    else {
        printf("Max number of students reached!\n");
    }
}

void addComment(student* inputStudent, int subjectLen) {
    int option;
    
    printf("Enter:\n");
    printf("'1' to comment\n");
    printf("any to skip: ");
    scanf("%d", &option);

    if (option == 1) {
        student currentStudent = *inputStudent;
        subject sub = currentStudent.subjects[subjectLen];
        
        printf("Write comment: ");
        fgets(sub.comment, sizeof(sub.comment), stdin);
        sscanf(sub.comment, "%[^\n]", sub.comment);
    }
    getchar();

}

void addGrades(int studentLen, node* inputNode) {
    if (studentLen > 0) {
        student currentStudent;
        char inputName[MAX_NAME_LEN];
        
        printf("Enter student name: ");
        fgets(inputName, sizeof(inputName), stdin);
        sscanf(inputName, "%[^\n]", inputName);
        
        flush(inputName, MAX_NAME_LEN);

        /* checks if student is in database via name search */
        int found = searchStudent(inputName, &currentStudent, inputNode);
        while (found == -1) {
                
            /* user can leave if they want to exit */
            /* if student is not found, either user can keep searching or 
            can leave the system */
            printf("Enter student name (type 'exit' to return to menu): ");
            fgets(inputName, sizeof(inputName), stdin);
            sscanf(inputName, "%[^\n]", inputName);

            flush(inputName, MAX_NAME_LEN);
            
            if (strcmp(inputName, "exit") == 0) {
                return;
            }

            found = searchStudent(inputName, &currentStudent, inputNode);
        }

        int idx;
        int inputMark;

        for (idx = 0; idx < 5; idx++) {
            printf("Enter mark for %s: ", currentStudent.subjects[idx].name);
            scanf("%d", &inputMark);
            currentStudent.subjects[idx].mark = calculateGrade(inputMark);

            addComment(&currentStudent, idx);
        }
        printf("Grades filled in for %s!", currentStudent.name);
    }
    else {
        printf("There are no students to grade!\n");
    }
}

void flush(char *arr, int maxLength){
    if(strlen(arr) == maxLength){ /*exceeding the array limit*/
        while(getchar() == '\n'); /*erase excess string*/
    }
}