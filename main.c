#include <stdio.h>
#include <stdlib.h>
#include "grade.h"
#include "grade.c"

/* print display menu */
void printMenu();

int main(void) {
    node* head = (node*)malloc(1 * sizeof(node));
    int studentLen = 0;

    printMenu();
    int inputNumber = 0;
    scanf("%d", &inputNumber);

    while (inputNumber != 11) {
        switch (inputNumber) {
            case 1:
                getchar();
                inputStudent(head, &studentLen);
                break;
            case 4:
                getchar();
                addGrades(studentLen, head);
                break;
            case 12:
                getchar();
                break;
            default:
                getchar();
                printf("Please input a number between 1-12!\n");
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
    printf("6. Save Grade to File\n");
    printf("7. Remove Grade File\n");
    printf("8. Encrypt Grade File\n");
    printf("9. Decrypt Grade File\n");
    printf("10. Compress Grade File\n");
    printf("11. Decompress Grade File\n");
    printf("12. Exit program\n");
    printf("\n");
}
