#include <stdio.h>
#include "grade.h"
#include "grade.c"

// print display menu
void printMenu();

int main(void) {
    student students[MAX_STUDENTS];
    int studentLen = 0;

    printMenu();
    int inputNumber;
    scanf("%d", &inputNumber);

    while (inputNumber != 7) {
        switch (inputNumber) {
            case 1:
                addGrade(studentLen, students);
                break;
            default:
                printf("Please input a number between 1-6!\n");
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
    printf("1. Add Grade\n");
    printf("2. Remove Grade\n");
    printf("3. Save Grade to File\n");
    printf("4. Remove Grade File\n");
    printf("5. Encrypt Grade File\n");
    printf("6. Decrypt Grade File\n");
    printf("7. Exit program\n");
    printf("\n");
}
