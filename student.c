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
        printf("\nThere are no students on file!\n");
    }
}

void inputStudent(node** inputNode, int* studentLen) {
    if (*studentLen != MAX_STUDENTS) {
        student newStudent;

        printf("\nEnter student name: ");
        fgets(newStudent.name, sizeof(newStudent.name), stdin);
        flush(newStudent.name, MAX_NAME_LEN);

        int found;
        found = searchStudent(newStudent.name, &newStudent, *inputNode);
        while (found == 0) {
            printf("Student already exists!\n");
            printf("Enter student name (type 'exit' to return to menu): ");
            fgets(newStudent.name, sizeof(newStudent.name), stdin);

            flush(newStudent.name, MAX_NAME_LEN);
                        
            if (strcmp(newStudent.name, "exit") == 0) {
                return;
            }
            found = searchStudent(newStudent.name, &newStudent, *inputNode);
        } 


        printf("Enter class number: ");
        scanf("%d", &newStudent.classNumber);
        while (getchar() != '\n') {}

        int idx;
        /* add student's subject 1 by 1 */
        for (idx = 0; idx < MAX_SUBJECTS; idx++) {
            printf("Enter subject name %d: ", idx + 1);
            fgets(newStudent.subjects[idx].name, 
                sizeof(newStudent.subjects[idx].name), stdin);

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

void removeStudent(node** inputNode, int* studentLen) {
    int found;
    student currentStudent;
    char student_name[MAX_NAME_LEN];
    
    if(*studentLen == 0){
        printf("\nNo students to remove\n");
    }
        
    else{
        printf("\nPlease input name of student to remove: ");
        fgets(student_name, sizeof(student_name), stdin);
        flush(student_name, MAX_NAME_LEN);
    
        found = searchStudent(student_name, &currentStudent, *inputNode);
        if(found != 0){
            /*false*/
            printf("This student does not exist\n");
        }
    
        else if(found == 0){
            /*true*/
            
            /*if linkedlist only contains entry node*/
            if(*studentLen == 1){
                free(*inputNode);
                *inputNode = NULL;
            }
            
            else{
                node* temp,* prev_node,* later_node, * removeStudent_node;
                temp = *inputNode;
                
                while(temp != NULL){
    
                    prev_node = temp;
                    removeStudent_node = temp -> next;
                    later_node = temp -> next -> next;
    
                    /*if student name lines up with node in linked list */
                    if(strcmp(removeStudent_node -> nodeStudent.name, currentStudent.name) == 0){
                        break;
                    }
    
                    /*considering condition: entry node is the student to be removed*/
                    else if(strcmp(prev_node -> nodeStudent.name, currentStudent.name) == 0){
                        removeStudent_node = prev_node;
                        later_node = removeStudent_node -> next;
                        prev_node = NULL;
                        break;
                    }
                    temp = temp -> next;
                }
                
                /*mending the linked list, removing student from list*/
                if(prev_node != NULL){
                    prev_node -> next = later_node;
                }
                /*if entry node was to be removed, changes the linked list head*/
                else if(prev_node == NULL){
                    *inputNode = later_node;
                }
                /*free linked list memory*/
                free(removeStudent_node);
    
            }
            *studentLen -= 1;
            printf("Student successfully removed.\n");
        }
    }
}

