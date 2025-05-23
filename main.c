#include <stdio.h>
#include <stdlib.h>
#include "system.h"
#include "grade.c"
#include "student.c"
#include "flush.c"
#include "compression.c"
#include "file.c"
#include "encryption.c"

/* print prototypes */
void printTeacherMenu();
void printStudentMenu();

int main(int argc, char* argv[]) {

/* create folders if they do not exist */
#ifdef _WIN32
    _mkdir("secured_files");
    _mkdir("files");
#else
    mkdir("secured_files", 0777);
    mkdir("files", 0777);
#endif

    int mode;
    /* if number is not entered in the command line, print error and exit */
    if (argc != 2) {
        printf("Pick mode in command line:\n");
        printf("1 for Teachers\n");
        printf("2 for Students\n");
        exit(1);
    }
    mode = atoi(argv[1]);

    if (mode == 1) {
        /* initialise linked list */
        node* head = NULL;
        int studentLen = 0;
        char studentName[MAX_NAME_LEN];

        /* print display menu and take number input */
        printTeacherMenu();
        int inputNumber = 0;
        scanf("%d", &inputNumber);

        /* input dictates what function of the menu is used */
        while (inputNumber != 10) {
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
                    deleteFile(head);
                    break；
                case 8:
                    getchar();
                    compressStudentGrades(studentName);
                    encryptFile(studentName);
                    break;
                case 9:
                    getchar();
                    decryptFile(studentName);
                    decompressStudentGrades(studentName);
                    break;
                /* if number is outside 1-9, loop again*/
                default:
                    while (getchar() != '\n') {};
                    printf("Please input a number between 1-10!\n");
                    break;
            }
            printTeacherMenu();
            scanf("%d", &inputNumber);
        }
    }
    else if (mode == 2) {
        /* print display menu for students and take number input */
        char studentName[MAX_NAME_LEN];
        
        printStudentMenu();
        int inputNumber = 0;
        scanf("%d", &inputNumber);

        while (inputNumber != 2) {
            switch (inputNumber) {
                case 1:
                    getchar();
                    decryptFile(studentName);
                    decompressStudentGrades(studentName);
                    break;
                default:
                    while (getchar() != '\n') {};
                    printf("Please input a number between 1-2!\n");
                    break;
            }
            printStudentMenu();
            scanf("%d", &inputNumber);
        }
    }

    return 0;
}

/* print display menu with the relevant choices */
void printTeacherMenu() {
    printf("\nTeacher Grading System:\n");
    printf("\n");
    printf("1. Add Student\n");
    printf("2: Remove Student\n");
    printf("3. Display Student Database\n");
    printf("4. Add Grades\n");
    printf("5. Display Grades Database\n");
    printf("6. Save Grade to File\n");
    printf("7. Remove Grade File\n");
    printf("8. Compress & Encrypt Grade File\n");
    printf("9. Decrypt & Decompress Grade File\n");
    printf("10. Exit program\n");
    printf("\n");
}

/* print student menu to view grade files */
void printStudentMenu() {
    printf("\nStudent Grades System:\n");
    printf("\n");
    printf("1. Decrypt & Decompress Grade File\n");
    printf("2. Exit program\n");
    printf("\n");
}
