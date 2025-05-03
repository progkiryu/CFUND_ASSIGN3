#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "system.h" /* include function prototypes */


/* calculate HSC bands via provided numerical mark */
int calculateGrade(int mark) {
    if (mark >= 0 && mark <= 100) {
        if (mark >= 90) {
            return 6;
        }
        else if (mark >= 80) {
            return 5;
        }
        else if (mark >= 70) {
            return 4;
        }
        else if (mark >= 60) {
            return 3;
        }
        else if (mark >= 50) {
            return 2;
        }
        return 1;
    }
    /* sends out error integer if mark exceeds boundaries */
    return -1;
}

void addComment(student* inputStudent, int subjectLen) {
    int option;
    
    printf("\nEnter:\n");
    printf("'1' to comment\n");
    printf("any to skip: ");
    scanf("%d", &option);

    if (option == 1) {
        student currentStudent = *inputStudent;
        subject sub = currentStudent.subjects[subjectLen];
        
        printf("Write comment: ");
        fgets(sub.comment, sizeof(sub.comment), stdin);

        flush(sub.comment, strlen(sub.comment));
    }
    getchar();

}

void addGrades(int studentLen, node* inputNode) {
    if (studentLen > 0) {
        student currentStudent;
        char inputName[MAX_NAME_LEN];
        
        printf("\nEnter student name: ");
        fgets(inputName, sizeof(inputName), stdin);
        
        flush(inputName, MAX_NAME_LEN);

        /* checks if student is in database via name search */
        int found = searchStudent(inputName, &currentStudent, inputNode);
        while (found == -1) {
                
            /* user can leave if they want to exit */
            /* if student is not found, either user can keep searching or 
            can leave the system */
            printf("Enter student name (type 'exit' to return to menu): ");
            fgets(inputName, sizeof(inputName), stdin);

            flush(inputName, MAX_NAME_LEN);
            
            if (strcmp(inputName, "exit") == 0) {
                return;
            }

            found = searchStudent(inputName, &currentStudent, inputNode);
        }

        int idx;
        int inputMark;

        for (idx = 0; idx < 5; idx++) {
            printf("Enter mark for %s: ", currentStudent.subjects[idx].name);
            scanf("%d", &inputMark);
            currentStudent.subjects[idx].mark = calculateGrade(inputMark);

            addComment(&currentStudent, idx);
        }
        printf("Grades filled in for %s!\n", currentStudent.name);
    }
    else {
        printf("There are no students to grade!\n");
    }
}