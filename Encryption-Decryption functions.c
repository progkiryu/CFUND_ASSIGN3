
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*Work in progress*/

void encryptFile(){
    
    int i;
    char key[10], ciphertext[len+1];
    char filename[256], student_name[MAX_NAME_LEN];
    char plainstring[MAX_NAME_LEN+(MAX_SUBJECTS*(MAX_SUB_LEN+MAX_COM_LEN+10))+1];

    strcpy(filename, "grades_compressed/");
    
    
    printf("Enter student name to encrypt: ");
    fgets(student_name, MAX_NAME_LEN, stdin);
    flush(student_name, MAX_NAME_LEN);

    strcat(filename, student_name);
    strcat(filename, ".txt");

    printf("Please input a password and safely remember it: ");
    fgets(key, 10, stdin);
    flush(key, 10);

    /*open file to check if it exists*/
    FILE *dataFile = fopen("dataFile.txt", "r");
    
    /*stops function if non-existent*/
    if(dataFile == NULL){
        printf("File does not exist\n");
        fclose(dataFile);
        return;
    }

    else{
        fgets(plainstring, strlen(plainstring), dataFile)
        
        fclose(dataFile);
    }
    
    FILE *dataFile = fopen(, "w");

    
    /*encrypting data*/
    for(i=0; i < strlen(plainstring); i++){
        ciphertext[i] = plainstring[i] ^ key[i % strlen(key)];
    }
    ciphertext[len] = '\0';


    /*open file to edit*/
    FILE *dataFile = fopen("dataFile.txt", "w");

    for(i=0; i < len; i++){
    printf("%02X ", (unsigned char)ciphertext[i]);
    fprintf(dataFile, "%02X ", (unsigned char)ciphertext[i]);
    }
    fprintf(dataFile, "%\n");
    fclose(dataFile);
}
