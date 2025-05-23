/*This function stores students' grades and comments in files named by the user (default is .txt),
and prompts a warning before overwriting existing files.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "system.h"  

/*Check the contents of the list*/
void saveToFile(node* head) {

    /* if there are no students, exit function */
    if (head == NULL) {
        printf("The list is empty!\n"); 
        return;
    }

    /*Guide the user to set the file name*/
    char inputName[MAX_NAME_LEN];
    printf("Enter student's name to save their grades to file: ");
    fgets(inputName, sizeof(inputName), stdin);
    flush(inputName, strlen(inputName));

    /* checks if student exists via name */
    node* found = searchStudent(inputName, head);
    while (found == NULL) {
        /* if student is not found, prompt a search loop until student is found 
        or not */
        printf("Enter student's name to save their grades to file ");
        printf("(type 'exit' to return to menu): ");
        fgets(inputName, sizeof(inputName), stdin);
        flush(inputName, strlen(inputName));

        /* user can type 'exit' to escape loop and return to menu */
        if (strcmp(inputName, "exit") == 0) {
            return;
        }

        node* found = searchStudent(inputName, head);
    }

    /* if student's grades are not filled, exit function */
    if (found -> nodeStudent.filled == 0) {
        printf("Student's grades not filled yet!\n");
        return;
    }

    /* prepares filename with student's name */
    char filename[MAX_NAME_LEN + 10];
    strcat(filename, "files/");
    strcat(filename, found -> nodeStudent.name);
    strcat(filename, ".txt");

    /*Overwrite reminder for the saem name file */
    FILE* check = fopen(filename, "r");
    if (check != NULL) {
        fclose(check);
        printf("Warning: file \"%s\" already exists. ", filename);
        printf("Overwrite? (Y/N): ");
    }

    /* prompts confirmation to create file */
    char choice[3];
    printf("Are you sure? (type 'yes' to create, type 'no' to exit): ");
    fgets(choice, sizeof(choice), stdin);
    flush(choice, strlen(choice)); 

    if (strcmp(choice, "yes") == 0) {
        printf("Operation cancelled.\n");
        return;
    }
    
    /* accounts for abnormal errors */
    FILE* fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error: Cannot open file for writing.\n");
        return;
    }

    /*Store the student information*/
    fprintf(fp, "Student: %s\n", found -> nodeStudent.name);
    fprintf(fp, "Grades:\n");
    int idx;
    for (idx = 0; idx < MAX_SUB_LEN; idx++) {
        fprintf(fp, "- %s: Band %d | %s\n",
        found -> nodeStudent.subjects[idx].name,
        found -> nodeStudent.subjects[idx].mark,
        found -> nodeStudent.subjects[idx].comment);
    }

    fclose(fp);
    printf("Successfully saved to: %s\n", filename);
} 

