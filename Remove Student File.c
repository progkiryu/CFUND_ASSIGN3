#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void removeStudent(node** inputNode, int* studentLen);
//still drafting, W.I.P

/* void removeStudent(node** inputNode, int* studentLen){

    int found;
    student currentStudent;
    char student_name[MAX_NAME_LEN];

    printf("Please input name of student to remove: ");
    fgets(student_name, sizeof(student_name), stdin);
    flush(student_name, MAX_NAME_LEN);

    found = searchStudent(student_name, &currentStudent, *inputNode);
    if(found != 0){
        //false
        printf("This student does not exist");
    }

    else if(found == 0){
        //true
        &currentStudent

        node* temp,* prev_node,* later_node;
        node* removeStudent_node;
        int i, j;

        while(temp != NULL){
            prev_node = temp -> next;
            removeStudent_node = temp -> next;
            later_node = removeStudent_node -> next;
            
            if(strcmp(removeStudent_node -> nodeStudent.name, currentStudent.name) == 0){
                break;
            }
        }
        //temp->next
        //temp->next->next

        //finding the nodes before and after
        //Remove student from linked list
        //check to see if prevNode or laterNode is NULL, this will mean 
        //join ends of linked list together
    

    }

*/
