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

void addComment(subject* inputSubject) {
    int option;
    char optionString[3];

    printf("\nEnter:\n");
    printf("'1' to comment\n");
    printf("any to skip: ");
    fgets(optionString, 3, stdin);
    flush(optionString, 3);
    option = atoi(optionString);
    
    if (option == 1) {

        printf("Write comment: ");
        fgets(inputSubject -> comment, sizeof(inputSubject -> comment), 
        stdin);

        flush(inputSubject -> comment, MAX_COM_LEN);
    }
}

void addGrades(int studentLen, node* inputNode) {
    if (studentLen > 0) {
        char inputName[MAX_NAME_LEN];
        
        printf("\nEnter student name: ");
        fgets(inputName, sizeof(inputName), stdin);
        
        flush(inputName, MAX_NAME_LEN);

        /* checks if student is in database via name search */
        node* found = searchStudent(inputName, inputNode);
        while (found == NULL) {
                
            /* user can leave if they want to exit */
            /* if student is not found, either user can keep searching or 
            can leave the system */
            printf("Enter student name (type 'exit' to return to menu): ");
            fgets(inputName, sizeof(inputName), stdin);

            flush(inputName, MAX_NAME_LEN);
            
            if (strcmp(inputName, "exit") == 0) {
                return;
            }

            found = searchStudent(inputName, inputNode);
        }

        /* If grades have already been filled, inform user for changes */
        if (found -> nodeStudent.filled == 1) {
            printf("Changing marks for %s!\n", found -> nodeStudent.name);
        } 


        int idx, i, ascii, passLoop;
        /*length of 5 just in case input is 4 digit like 1000 + '\0'*/
        char stringinputMark[5];
        int inputMark;

        for (idx = 0; idx < 5; idx++) {
            passLoop = 1;
            while (1) {
                if(passLoop == 0){break;}
                passLoop = 0;

                printf("\nEnter mark for %s: ", found -> nodeStudent.subjects[idx].name);
                fgets(stringinputMark, 5, stdin);
                flush(stringinputMark, 5);
                
                /*Checking ASCII characters, making sure within number char range*/
                for(i=0; stringinputMark[i] != '\0'; i++){
                    ascii = stringinputMark[i];
                    if(ascii < 48 || ascii > 57){
                        passLoop = 1;
                    }
                }
                /*if number outside character range*/
                if(passLoop == 1){
                printf("Please input numbers, try again..\n\n");
                }
                /*convert string to int*/
                inputMark = atoi(stringinputMark);
                
                /*if input is integers & inputmark within 0-100 range*/
                if(passLoop!=1 && (inputMark < 0 || inputMark >100)){
                    printf("Grade needs to be within 0 - 100, try again..\n\n");
                    passLoop = 1;
                }
            }
            
            found->nodeStudent.subjects[idx].mark = calculateGrade(inputMark);
            
            addComment(&found->nodeStudent.subjects[idx]);
        }
        printf("Grades filled in for %s!\n", found->nodeStudent.name);

        /* Assign value to 1 that student's grades are filled */
        found -> nodeStudent.filled = 1;
    }
    else {
        printf("There are no students to grade!\n");
    }
}

void displayGrades(node* inputNode){
    char student_name[MAX_NAME_LEN];
    student currentStudent;
    node* found;

    printf("\nPlease input student name: ");
    fgets(student_name, sizeof(student_name), stdin);
    flush(student_name, strlen(student_name));

    found = searchStudent(student_name, inputNode);
    while (found == NULL) {
        /*false*/
        printf("Please input student name (type 'exit' to return to menu): ");
        fgets(student_name, sizeof(student_name), stdin);
        flush(student_name, strlen(student_name));

        if (strcmp(student_name, "exit") == 0) {
            return;
        }

        found = searchStudent(student_name, inputNode);
    }

    /*true*/
    currentStudent = found -> nodeStudent;
    int idx;
        
    printf("\n%-*s %-5s %-s", MAX_SUB_LEN, "Subject", "Bands", "Comments");
    printf("\n-------------------- ----- ");

    /* Allow space for comment section */
    for (idx = 0; idx < 50; idx++) {
        printf("-");
    }
    printf("\n");

    for (idx = 0; idx < 5; idx++){
        printf("%-*s ", MAX_SUB_LEN, currentStudent.subjects[idx].name);

        /* print grade details */
        printf("%-5d ", currentStudent.subjects[idx].mark);
        printf("%-s", currentStudent.subjects[idx].comment);
        printf("\n");
    }        
    return;
}
