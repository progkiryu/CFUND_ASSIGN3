#include <stdio.h>
#include <stdlib.h>
#include "system.h"
#include "grade.c"
#include "student.c"
#include "flush.c"
#include "compression.c"
#include "file.c"
#include "encryption.c"

/* print display menu */
void printMenu();

int main(void) {

/* create folders if they do not exist */
#ifdef _WIN32
    _mkdir("secured_files");
    _mkdir("files");
#else
    mkdir("secured_files", 0777);
    mkdir("files", 0777);
#endif

    /* initialise linked list */
    node* head = NULL;
    int studentLen = 0;
    char studentName[MAX_NAME_LEN];

    /* print display menu and take number input */
    printMenu();
    int inputNumber = 0;
    scanf("%d", &inputNumber);

    /* input dictates what function of the menu is used */
    while (inputNumber != 9) {
        switch (inputNumber) {
            case 1:
                getchar();
                inputStudent(&head, &studentLen);
                break;
            case 2:
                getchar();
                removeStudent(&head, &studentLen);
                break;
            case 3:
                getchar();
                displayStudents(head, studentLen);
                break;
            case 4:
                getchar();
                addGrades(studentLen, head);
                break;
            case 5:
                getchar();
                displayGrades(head);
                break;
            case 6:
                getchar();
                saveToFile(head);
                break;
            case 7:
                getchar();
                compressStudentGrades(studentName, head);
                encryptFile(studentName);
                break;
            case 8:
                getchar();
                decryptFile(studentName, head);
                decompressStudentGrades(studentName);
                break;
            /* if number is outside 1-9, loop again*/
            default:
                while (getchar() != '\n') {};
                printf("Please input a number between 1-10!\n");
                break;
        }
        printMenu();
        scanf("%d", &inputNumber);
    }

    return 0;
}

/* print display menu with the relevant choices */
void printMenu() {
    printf("\nWelcome to the Grading System:\n");
    printf("\n");
    printf("1. Add Student\n");
    printf("2: Remove Student\n");
    printf("3. Display Student Database\n");
    printf("4. Add Grades\n");
    printf("5. Display Grades Database\n");
    printf("6. Save Grade to File\n");
    printf("7. Compress & Encrypt Grade File\n");
    printf("8. Decrypt & Decompress Grade File\n");
    printf("9. Exit program\n");
    printf("\n");
}
