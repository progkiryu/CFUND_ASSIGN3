/*saveToFile.c
Function: 
Save the specified student's score information to a text file named after this student,
and prompts a warning before overwriting existing files.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "system.h"

void saveToFile(node* head) {
    if (head == NULL) {
        printf("Error: The student list is empty!\n");
        return;
    }

    /* Get the target student's name */
    char targetName[MAX_NAME_LEN];
    printf("Enter the name of the student to save: ");
    fgets(targetName, sizeof(targetName), stdin);
    targetName[strcspn(targetName, "\n")] = '\0';

    /* Search the student */
    node* currentNode = head;
    while (currentNode && strcmp(currentNode->nodeStudent.name, targetName) != 0) {
        currentNode = currentNode->next;
    }
    if (!currentNode) {
        printf("Error: Student %s not found\n", targetName);
        return;
    }

    char filename[MAX_NAME_LEN + 10];
    strcpy(filename, "files/");
    strcat(filename, targetName);
    strcat(filename, ".txt");

    /* Check if the file already exists */
    FILE* f = fopen(filename, "r");
    if (f) {
        fclose(f);
        /* Remind the user: Files with the same name will be overwritten */
        printf("Warning:File already exists. Overwrite? (Y/N): ");
        char c;
        if (scanf(" %c", &c) != 1) {
            while (getchar() != '\n');
            printf("Input error. Operation cancelled\n");
            return;
        }
        while (getchar() != '\n');  
        if (c != 'Y' && c != 'y') {   
            printf("Operation cancelled\n");
            return;
        }
    }

    FILE* studentFile = fopen(filename, "w");
    if (!studentFile) {
        printf("Failed to create file\n");
        return;
    }

    /* Write student data to file */
    fprintf(studentFile, "Student Name: %s\n", targetName);
    fprintf(studentFile, "Student Class Number: %d\n\n",
    currentNode->nodeStudent.classNumber);

    fprintf(studentFile, "Subject Scores:\n");
    int i;
    for (i = 0; i < MAX_SUBJECTS; i++) {
        subject sub = currentNode->nodeStudent.subjects[i];

        fprintf(studentFile, "- %s: ", sub.name);
        if (sub.mark >= 0) fprintf(studentFile, "Band %d | ", sub.mark);
        else fprintf(studentFile, "No score available | ");

        if (sub.mark < 0 || strlen(sub.comment) == 0) {
            fprintf(studentFile, "No comment\n");
        } else {
            fprintf(studentFile, "Comment: ");
            int j;
            for (j = 0; sub.comment[j] && j < MAX_COM_LEN; j++) {
                putc(sub.comment[j] == '\n' ? ' ' : sub.comment[j], studentFile);
            }
            putc('\n', studentFile);
        }
    }

    fclose(studentFile);
    printf("Successfully saved to %s\n", filename);
}
