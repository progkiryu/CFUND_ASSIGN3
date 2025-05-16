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
    char optionString[3];

    printf("\nEnter:\n");
    printf("'1' to comment\n");
    printf("any to skip: ");
    fgets(optionString, 3, stdin);
    flush(optionString, 3);
    option = atoi(optionString);
    
    if (option == 1) {
        student currentStudent = *inputStudent;
        subject sub = currentStudent.subjects[subjectLen];
        
        printf("Write comment: ");
        fgets(sub.comment, sizeof(sub.comment), stdin);

        flush(sub.comment, MAX_COM_LEN);
    }
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

        int idx, i, ascii, passLoop = 1;
        /*length of 5 just in case input is 4 digit like 1000 + '\0'*/
        char stringinputMark[5];
        int inputMark;

        for (idx = 0; idx < 5; idx++) {
            passLoop = 1;
            while(1){
                if(passLoop == 0){break;}
                passLoop = 0;

                printf("\nEnter mark for %s: ", currentStudent.subjects[idx].name);
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
            
            /*finding address of node to change mark*/
            node* temp;
            temp = inputNode;
            while(temp != NULL){
                if(strcmp( temp -> nodeStudent.name, currentStudent.name) == 0){
                    break;
                }
                else{temp = temp -> next;}
            }
            temp -> nodeStudent.subjects[idx].mark = calculateGrade(inputMark);
            
            addComment(&currentStudent, idx);
        }
        printf("Grades filled in for %s!\n", currentStudent.name);
    }
    else {
        printf("There are no students to grade!\n");
    }
}

void displayGrades(node** inputNode){
    char student_name[MAX_NAME_LEN];
    student currentStudent;
    int found;

    printf("\nPlease input student name: ");
    fgets(student_name, MAX_NAME_LEN, stdin);
    flush(student_name, MAX_NAME_LEN);

    found = searchStudent(student_name, &currentStudent, *inputNode);
    
    if(found != 0){
        /*false*/
        printf("This student does not exist\n");
        return;
    }
    
    else if(found == 0){
        /*true*/
        int idx;
        
        printf("\n%-*s %-14s %s", MAX_SUB_LEN, "Subject", "Bands", "Comments");
        printf("\n--------------------------------------------\n");

        for(idx = 0; idx < 5; idx++){
        
        printf("%-*s", MAX_SUB_LEN, currentStudent.subjects[idx].name);
        printf(" %-14d", currentStudent.subjects[idx].mark);
        printf("%s\n", currentStudent.subjects[idx].comment);
        }        
        return;
    }
}
