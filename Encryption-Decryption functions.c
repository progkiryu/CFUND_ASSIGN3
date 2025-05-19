
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*Work in progress*/
/*Need to make sure in encryption function that the compressed file gets overwritten to blank*/

void encryptFile(){
    
    int i;
    char key[10];
    char filename[256], student_name[MAX_NAME_LEN];
    char ch;

    strcpy(filename, "grades_compressed/");
    
    
    printf("Enter student name to encrypt: ");
    fgets(student_name, MAX_NAME_LEN, stdin);
    flush(student_name, MAX_NAME_LEN);

    strcat(filename, student_name);
    strcat(filename, ".txt");

    printf("Please input a password and safely remember it: ");
    fgets(key, 10, stdin);
    key[strcspn(key, "\n")] = '\0';

    /*open file to check if it exists*/
    FILE *dataFile = fopen(filename, "r");
    
    /*stops function if non-existent*/
    if(dataFile == NULL){
        printf("File does not exist\n");
        return;
    }

    else{
        /*naming encryptedfile to be made*/
        char encryptedfilename[256];
        strcpy(encryptedfilename, "encrypted");
        strcat(encryptedfilename, student_name);
        strcat(encryptedfilename, ".bin");
        
        /*opening file for encryption*/
        FILE *encryptFile = fopen(encryptedfilename, "wb");


        /*encrypting and printing hexadecimal character by character*/        
        for (i=0; (ch = fgetc(dataFile)) != EOF; i++) {
                char encrypted = ch ^ key[i % strlen(key)];
                fprintf(encryptFile, "%02X ", (unsigned char)encrypted);
            }

        fclose(dataFile);
        fclose(encryptFile);
    }
}


void decryptFile(){
    int i;
    char key[10];
    char encryptedfilename[256];
    char filename[256], student_name[MAX_NAME_LEN];
    
    printf("Enter student name to decrypt: ");
    fgets(student_name, MAX_NAME_LEN, stdin);
    flush(student_name, MAX_NAME_LEN);

    strcpy(encryptedfilename, "encrypted");
    strcat(encryptedfilename, student_name);
    strcat(encryptedfilename, ".bin");

    /*open file to check if it exists*/
    FILE *encryptedFile = fopen(encryptedfilename, "r");
    
    /*stops function if non-existent*/
    if(encryptedFile == NULL){
        printf("File does not exist\n");
        return;
    }

    printf("Please enter the password: ");
    fgets(key, 10, stdin);
    flush(key, 10);
    
    /*naming compressed student file*/
    strcpy(filename, "grades_compressed/");
    strcat(filename, "test");
    strcat(filename, student_name);
    strcat(filename, ".txt");

    FILE *dataFile = fopen(filename, "w");
    unsigned char byte;
    
    /*decrypting each character*/
    for(i=0; fscanf(encryptedFile, "%2hhX", &byte) == 1; i++){
            char decrypted = byte ^ key[i % strlen(key)];
            fprintf(dataFile, "%c", decrypted);
    }

    fclose(encryptedFile);
    fclose(dataFile);
}
