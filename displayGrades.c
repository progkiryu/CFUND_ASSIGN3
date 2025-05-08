#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//Work in progress

void displayGrades(node** inputNode){
    char student_name[MAX_NAME_LEN];
    student current_student;
    int found;

    printf("Please input student name: ");
    fgets(student_name, sizeof(student_name), stdin);
    flush(student_name, MAX_NAME_LEN);

    found = searchStudent(student_name, &current_student, *inputNode);
    
    if(found != 0){
        //false
        printf("This student does not exist");
    }
    
    else if(found == 0){
        //true
        int idx, grade;
        int subjectLen = student_name.subjectLen;
        char subject[MAX_SUB_LEN];
        
        printf("%-*s %s\n", MAX_SUB_LEN, Subject, Grades);
        printf("----------------------------------\n");

        for(idx = 0; idx < subjectLen; idx++){
        grade = current_student.subjects[idx].mark;
        subject = current_student.subjects[idx].name;
        
        printf("%-*s", MAX_SUB_LEN, subject);
        printf(" %.2d\n", grade);
        }
    }
}
