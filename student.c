#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "system.h"

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

void displayStudents(node* inputNode, int studentLen) {
    if (studentLen > 0) {
        student currentStudent;

        printf("\nName                 Class\n");
        printf("-------------------- -----\n");

        while (inputNode != NULL) {
            currentStudent = inputNode->nodeStudent;
            printf("%-20.20s %-5d\n", currentStudent.name, 
                currentStudent.classNumber);

            inputNode = inputNode->next;
        }
    }
    else {
        printf("There are no students on file!\n");
    }
}

void inputStudent(node** inputNode, int* studentLen) {
    if (*studentLen != MAX_STUDENTS) {
        student newStudent;

        printf("\nEnter student name: ");
        fgets(newStudent.name, sizeof(newStudent.name), stdin);
        sscanf(newStudent.name, "%[^\n]", newStudent.name);
        
        int found;
        found = searchStudent(newStudent.name, &newStudent, *inputNode);
        while (found == 0) {
            printf("Student already exists!\n");
            printf("Enter student name (type 'exit' to return to menu): ");
            fgets(newStudent.name, sizeof(newStudent.name), stdin);
            sscanf(newStudent.name, "%[^\n]", newStudent.name);

            flush(newStudent.name, MAX_NAME_LEN);
                        
            if (strcmp(newStudent.name, "exit") == 0) {
                return;
            }
            found = searchStudent(newStudent.name, &newStudent, *inputNode);
        } 

        flush(newStudent.name, MAX_NAME_LEN);

        printf("Enter class number: ");
        scanf("%d", &newStudent.classNumber);
        while (getchar() != '\n') {}

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

        node* currentNode = *inputNode;
        /* allocate space for next node */
        node* newNode = (node*)malloc(sizeof(node));
        /* save student data to node */
        newNode->nodeStudent = newStudent;
        /* initialise next node */
        newNode->next = NULL;

        /* if there are no students, initialise the first node */
        if (*inputNode == NULL) {
            *inputNode = newNode;
        }
        else { 
            /* finds the next node to assign the student data without
            directly affecting the head node */
            while (currentNode->next != NULL) {
                currentNode = currentNode->next;
            }
            currentNode->next = newNode;
        }
        
        *studentLen += 1;
        
        printf("Student put in database!\n");
    }
    else {
        printf("Max number of students reached!\n");
    }
}