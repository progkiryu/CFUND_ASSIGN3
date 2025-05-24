#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "system.h"

node* searchStudent(char inputName[MAX_NAME_LEN], 
    node* inputNode) {

    /* iterates through each student until name matches*/
    while (inputNode != NULL) {
        if (strcmp(inputNode->nodeStudent.name, inputName) == 0) {
            return inputNode;
        }
        /* copies node */
        inputNode = inputNode->next;
    }
    return NULL;
}

void displayStudents(node* inputNode, int studentLen) {
    if (studentLen > 0) {

        /* display format of students */
        printf("\nName                 Class\n");
        printf("-------------------- -----\n");

        /* store students in array */
        node* temp = inputNode;
        student sorted[studentLen];
        int idx = 0;
        while (temp != NULL && idx < studentLen) {
            sorted[idx] = temp -> nodeStudent;
            temp = temp -> next;
            idx++;
        }

        /* implement selection sort to display students in 
        alphabetical order */
        int sidx, tidx, minIdx;
        student tempStu;
        for (sidx = 0; sidx < studentLen; sidx++) {
            minIdx = sidx;
            for (tidx = sidx + 1; tidx < studentLen; tidx++) {
                if (strcmp(sorted[tidx].name, sorted[minIdx].name) < 0) {
                    minIdx = tidx;
                }
            }

            if (minIdx != sidx) {
                tempStu = sorted[sidx];
                sorted[sidx] = sorted[minIdx];
                sorted[minIdx] = tempStu;   
            }
        }
        
        student currStudent;
        int arrIdx;
        for (arrIdx = 0; arrIdx < studentLen; arrIdx++) {
            currStudent = sorted[arrIdx];
            printf("%-20.20s %-5d\n", currStudent.name, 
                currStudent.classNumber);
        }
    }
    else {
        printf("\nThere are no students on file!\n");
    }
}

void inputStudent(node** inputNode, int* studentLen) {
    /* check if linked list is full */
    if (*studentLen != MAX_STUDENTS) {
        /* initialise relevant variables*/
        student newStudent;
        node* found;

        /* enter new name */
        printf("\nEnter student name: ");
        fgets(newStudent.name, sizeof(newStudent.name), stdin);
        flush(newStudent.name, MAX_NAME_LEN);

        /* search for an existing student */
        found = searchStudent(newStudent.name, *inputNode);
        while (found != NULL) {
            /* user can leave if they do not want to add students */
            printf("Student already exists!\n");
            printf("Enter student name (type 'exit' to return to menu): ");
            fgets(newStudent.name, sizeof(newStudent.name), stdin);

            flush(newStudent.name, MAX_NAME_LEN);
                  
            if (strcmp(newStudent.name, "exit") == 0) {
                return;
            }
            found = searchStudent(newStudent.name, *inputNode);
        } 

        /* enter class number */
        printf("Enter class number: ");
        scanf("%d", &newStudent.classNumber);
        /* account for extra numbers */
        while (getchar() != '\n') {}

        int idx;
        /* add student's subject 1 by 1 */
        for (idx = 0; idx < MAX_SUBJECTS; idx++) {
            printf("Enter subject name %d: ", idx + 1);
            fgets(newStudent.subjects[idx].name, 
                sizeof(newStudent.subjects[idx].name), stdin);

            flush(newStudent.subjects[idx].name, MAX_SUB_LEN);
            newStudent.subjects[idx].mark = 0;
            newStudent.subjects[idx].comment[0] = '\0';
        }

        /* Initialise value to 0 since subjects are not filled */
        newStudent.filled = 0;

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
    /* initialise relevant variables */
    node* found;
    char student_name[MAX_NAME_LEN];
    
    /* if there are no students, return to menu */
    if(*studentLen == 0){
        printf("\nNo students to remove!\n");
    }
        
    else{
        /* search student via name */
        printf("\nPlease input name of student to remove: ");
        fgets(student_name, sizeof(student_name), stdin);
        flush(student_name, strlen(student_name));
    
        found = searchStudent(student_name, *inputNode);
        while (found == NULL){
            /*false*/
            printf("\nPlease input name of student to remove ");
            printf("(type 'exit' to return to menu): ");
            fgets(student_name, sizeof(student_name), stdin);
            flush(student_name, strlen(student_name));

            /* user can leave if they enter 'exit' */
            if (strcmp(student_name, "exit") == 0) {
                return;
            }
    
            found = searchStudent(student_name, *inputNode);
        }
    
        /*true*/
        node* temp = *inputNode;
        node* after = temp -> next;
        /*if linkedlist only contains entry node*/
        if(*studentLen == 1){
            free(*inputNode);
            *inputNode = NULL;
        }
        /* if the student is at the 1st node, change the head node
        by swapping to the next */
        else if (strcmp(found -> nodeStudent.name, 
            temp -> nodeStudent.name) == 0) {
            *inputNode = temp -> next;
        }
        else{
            /* if the student is found past the 1st node, search
            throughout the list */
            while (after == NULL) {
                if (strcmp(after -> nodeStudent.name, 
                    found -> nodeStudent.name) == 0) {
                    return;
                }
                temp = temp -> next;
                after = after -> next;
            }
            
            if (after -> next != NULL) {
                temp -> next = after -> next;
            }
            /* if student was at the last node, make the previous node's 
            neighbour null */
            else {
                temp -> next = NULL;
            }
                
            /*free linked list memory*/
            free(after);
    
        }
        *studentLen -= 1;
        printf("Student successfully removed.\n");
    }
}

