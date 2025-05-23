/*deleteFile.c
Delete a student’s report file named after this student*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "system.h"  

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
