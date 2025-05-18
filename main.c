#include <stdio.h>
#include <stdlib.h>
#include "system.h"
#include "grade.c"
#include "student.c"
#include "flush.c"
#include "Final of Compression and Decompression.c"
#include "file.c"

/* print display menu */
void printMenu();

int main(void) {
    /* initialise linked list */
    node* head = NULL;
    int studentLen = 0;

    printMenu();
    int inputNumber = 0;
    scanf("%d", &inputNumber);

    while (inputNumber != 13) {
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
            case 6:
                getchar();
                displayGrades(head);
                break;
            case 7:
                getchar();
                saveToFile(head);
                break;
            case 11:
                getchar();
                compressStudentGrades(head);
                break;
            case 12:
                getchar();
                decompressStudentGrades();
                break;
            default:
                getchar();
                printf("Please input a number between 1-13!\n");
                break;
        }
        printMenu();
        scanf("%d", &inputNumber);
    }

    return 0;
}

void printMenu() {
    printf("\nWelcome to the Grading System:\n");
    printf("\n");
    printf("1. Add Student\n");
    printf("2: Remove Student\n");
    printf("3. Display Student Database\n");
    printf("4. Add Grades\n");
    printf("5. Remove Grades\n");
    printf("6. Display Grades Database\n");
    printf("7. Save Grade to File\n");
    printf("8. Remove Grade File\n");
    printf("9. Encrypt Grade File\n");
    printf("10. Decrypt Grade File\n");
    printf("11. Compress Grade File\n");
    printf("12. Decompress Grade File\n");
    printf("13. Exit program\n");
    printf("\n");
}
