



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"  

//Check the contents of the list
void saveToFile(node* head) {
    if (head == NULL) {
        printf("The list is empty!\n"); 
        return;
    }

    //Guide the user to set the file name
char filename[50];
    printf("Enter your custom file name (without suffix): ");
    scanf("%s", filename); 

    strcat(filename, ".txt");

    //Overwrite reminder for the saem name file 
FILE* check = fopen(filename, "r");
    if (check != NULL) {
        fclose(check);
        printf("Warning: file \"%s\" already exists. Overwrite? (Y/N): ", filename);

    while (getchar() != '\n'); 

    char choice;
    scanf("%c", &choice);  

    if (choice != 'Y' && choice != 'y') {
        printf("Operation cancelled.\n");
    return;
    }
}
    
FILE* fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error: Cannot open file for writing.\n");
        return;
    }

//Store the student information
node* curr = head;
    while (curr != NULL) {
        fprintf(fp, "Student: %s\n", curr->nodeStudent.name);

for (int i = 0; i < 5; i++) {
    fprintf(fp, "- %s: %d marks | ", 
            curr->nodeStudent.subjects[i].name, 
            curr->nodeStudent.subjects[i].mark);

    if (strlen(curr->nodeStudent.subjects[i].comment) == 0) {
        fprintf(fp, "No comment");
    } else {
        char buf[100];
        strncpy(buf, curr->nodeStudent.subjects[i].comment, 99);
        buf[99] = '\0';
        for (int j = 0; buf[j]; j++) {
            if (buf[j] == '\n') buf[j] = ' ';
        }
        fprintf(fp, "Comment: %s", buf);
    }
    fprintf(fp, "\n");
}

    fprintf(fp, "\n");
    curr = curr->next;
    }

    fclose(fp);
    printf("Successfully saved to: %s\n", filename);
} 
