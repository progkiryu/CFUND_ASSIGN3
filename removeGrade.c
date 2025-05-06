/*
I will add two global macros, NO_GRADE and NO_COMMENT, at the top of system.h
Define in system.h:
#define NO_GRADE   (-1)   // mark == NO_GRADE       Indicate "no grades"
#define NO_COMMENT ""     // comment == NO_COMMENT  Indicate "no comment"

Please make sure to use these markers 
when writing code to read or display grades or comments. :
if (mark == NO_GRADE)  → Skip this score
if (strlen(comment) == 0)  → Skip this comment
*/
#include <stdio.h>
#include <string.h>
#include "system.h"

/* If the list is empty */
void removeGrades(int studentLen, node* inputNode) {
    if (studentLen <= 0) {
        printf("No students on the list!\n");
        return;
    }

    /*Guide the user to input*/
    char inputName[MAX_NAME_LEN];
    printf("\nEnter student name to clear grades (Type 'exit' to cancel): ");
    fgets(inputName, sizeof(inputName), stdin);
    flush(inputName, MAX_NAME_LEN);

    if (strcmp(inputName, "exit") == 0) {
        return;
    }

    /* Search students */
    node *current = inputNode;
    while (current != NULL && strcmp(current->nodeStudent.name, inputName) != 0) {
        current = current->next;
    }

    /* Student not found */
    if (current == NULL) {
        printf("Could not find student: %s.\n", inputName);
        return;
    }

    /* Clear all grades for the found student */
    int nsub = current->nodeStudent.subjectLen;
    for (int i = 0; i < nsub; i++) {
        current->nodeStudent.subjects[i].mark = NO_GRADE;  // global macros
    }

    printf("Grades removed for student: %s\n", current->nodeStudent.name);
}
