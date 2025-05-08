#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void removeStudent(node** inputNode, int* studentLen);
//still drafting, W.I.P

void removeStudent(node** inputNode, int* studentLen){

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
        node* temp,* prev_node,* later_node, * removeStudent_node;
        temp = *inputNode;

        while(temp != NULL){
            prev_node = temp;
            removeStudent_node = temp -> next;
            later_node = temp -> next -> next;

            if(strcmp(removeStudent_node -> nodeStudent.name, currentStudent.name) == 0){
                break;
            }

            //else if starting node is the student to be removed
            else if(strcmp(prev_node -> nodeStudent.name, currentStudent.name) == 0){
                removeStudent_node = prev_node;
                later_node = removeStudent_node -> next;
                prev_node = NULL;
                break;
            }
            temp = temp -> next;
        }
        

        if(prev_node != NULL){
            prev_node -> next = later_node;
        }
        //if entry node was to be removed, changes the linked list head
        else if(prev_node == NULL){
            *inputNode = removeStudent_node;
        }
        //free linked list memory
        free(removeStudent_node -> next);
        free(removeStudent_node);

        *studentLen -= 1;
    }
}

        //finding the nodes before and after (done)
        //Remove student from linked list (done)
        //check to see if prevNode or laterNode is NULL (done)
        //join ends of linked list together (done)
