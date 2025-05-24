/*saveToFile.c
Function: 
Save the specified student's score information to a text file named after this student,
and prompts a warning before overwriting existing files.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "system.h"

void saveToFile(node* head) {
    /* if there are no students, do not bother searching */
    if (head == NULL) {
        printf("Error: The student list is empty!\n");
        return;
    }

    /* Get the target student's name */
    char targetName[MAX_NAME_LEN];
    printf("Enter the name of the student to save: ");
    fgets(targetName, sizeof(targetName), stdin);
    flush(targetName, strlen(targetName));

    /* search for student in linked list */
    node* found = searchStudent(targetName, head);
    while (found == NULL) {
        /* user can type exit if student does not exist */
        printf("Enter the name of the student to save ");
        printf("(type 'exit' to return to menu): ");
        fgets(targetName, sizeof(targetName), stdin);
        flush(targetName, strlen(targetName));

        if (strcmp(targetName, "exit") == 0) {
            return;
        }

        found = searchStudent(targetName, head);
    }
    
    /* if student's grades are not filled, return to menu */
    if (found -> nodeStudent.filled == 0) {
        printf("Student's grades are not filled!\n");
        return;
    }

    /* create file to write the student's grades in */
    char filename[MAX_NAME_LEN + 10];
    strcpy(filename, "files/");
    strcat(filename, targetName);
    strcat(filename, ".txt");

    /* Check if the file already exists */
    FILE* f = fopen(filename, "r");
    if (f) {
        fclose(f);
        /* Remind the user: Files with the same name will be overwritten */
        printf("Warning: File already exists. Overwrite? (Y/N): ");
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

    /* open file for writing */
    FILE* studentFile = fopen(filename, "w");
    if (!studentFile) {
        printf("Failed to create file\n");
        return;
    }

    /* Write student data to file */
    fprintf(studentFile, "Student Name: %s\n", targetName);
    fprintf(studentFile, "Student Class Number: %d\n\n",
    found->nodeStudent.classNumber);

    fprintf(studentFile, "Subject Scores:\n");
    int i;
    for (i = 0; i < MAX_SUBJECTS; i++) {
        subject sub = found->nodeStudent.subjects[i];

        fprintf(studentFile, "- %s: ", sub.name);
        if (sub.mark >= 0) fprintf(studentFile, "Band %d | ", sub.mark);
        else fprintf(studentFile, "No score available | ");

        fprintf(studentFile, "Comment: %s\n", sub.comment);
    }

    /* close file and print success message */
    fclose(studentFile);
    printf("Successfully saved to %s\n", filename);
}


/*deleteFile.c
Function: 
Delete a student’s report file named after this student*/

void deleteFile(node* head) {

    /* if there are no students, assume there are no files */
    if (head == NULL) {
        return;
    }

    /*Prompt for the student name whose file to delete*/
    char studentName[MAX_NAME_LEN];
    printf("Enter the name of the student to delete: ");
    if (fgets(studentName, sizeof(studentName), stdin) == NULL) {
        printf("Error: Failed to read input!\n");
        return;
    }
    /* clear extra input */
    flush(studentName, strlen(studentName));

    /*Build the filename*/
    char filename[MAX_NAME_LEN + 10];
    strcpy(filename, "files/");
    strcat(filename, studentName);
    strcat(filename, ".txt");

    /* also remove encrypted file name */
    char encryptFile[MAX_NAME_LEN + 17];
    strcpy(encryptFile, "secured_files/");
    strcat(encryptFile, studentName);
    strcat(encryptFile, ".bin");

    /*Check if either file exists */
    FILE* fileTest = fopen(filename, "r");
    FILE* fileTest2 = fopen(encryptFile, "rb");
    if (fileTest == NULL && fileTest2 == NULL) {
        printf("Notice: Report file \"%s\" do not exist\n", filename);
        return;
    }
    fclose(fileTest);
    fclose(fileTest2);

    printf("bruh");

    /*Confirm deletion*/
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

    /*Perform deletion*/
    if (fileTest != NULL) {
        if (remove(filename) == 0) {
            printf("Successfully deleted \"%s\"\n", filename);
        } else {
            printf("Error: Failed to delete \"%s\"\n", filename);
        }
    }
    if (fileTest2 != NULL) {
        if (remove(encryptFile) == 0) {
            printf("Successfully deleted \"%s\"\n", encryptFile);
        } else {
            printf("Error: Failed to delete \"%s\"\n", encryptFile);
        }
    }
}
