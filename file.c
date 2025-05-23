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


/*deleteFile.c
Function: 
Delete a student’s report file named after this student*/

void deleteFile(node* head) {
    //Check if there are any students in the list
    if (head == NULL) {
        printf("Error: The student list is empty!\n");
        return;
    }

    //Prompt for the student name whose file to delete
    char studentName[MAX_NAME_LEN];
    printf("Enter the name of the student to delete: ");
    if (fgets(studentName, sizeof(studentName), stdin) == NULL) {
        printf("Error: Failed to read input!\n");
        return;
    }
    // Remove trailing newline
    for (int i = 0; studentName[i]; i++) {
        if (studentName[i] == '\n') {
            studentName[i] = '\0';
            break;
        }
    }

    //Search for the student in the linked list
    node* current = head;
    int found = 0;
    while (current != NULL) {
        if (strcmp(current->nodeStudent.name, studentName) == 0) {
            found = 1;
            break;
        }
        current = current->next;
    }
    if (!found) {
        printf("Error: Student \"%s\" not found\n", studentName);
        return;
    }

    //Build the filename
    char filename[MAX_NAME_LEN + 12];
    snprintf(filename, sizeof(filename), "%s_report.txt", studentName);

    //Check if the file exists
    FILE* fileTest = fopen(filename, "r");
    if (fileTest == NULL) {
        printf("Notice: Report file \"%s\" does not exist\n", filename);
        return;
    }
    fclose(fileTest);

    //Confirm deletion
    printf("WARNING: This will delete \"%s\". Continue? (Y/N): ", filename);
    char confirm;
    if (scanf(" %c", &confirm) != 1) {
        while (getchar() != '\n') {}
        printf("Error: Invalid input. Operation cancelled.\n");
        return;
    }
    while (getchar() != '\n') {}
    if (confirm != 'Y') {
        printf("Operation cancelled\n");
        return;
    }

    //Perform deletion
    if (remove(filename) == 0) {
        printf("Successfully deleted \"%s\"\n", filename);
    } else {
        printf("Error: Failed to delete \"%s\"\n", filename);
    }
}
