
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "system.h"

void encryptFile(char* name){
    
    int i;
    char key[25];
    char filename[256];
    char ch;

    /* if compression failed, do not run function */
    if (strlen(name) == 0) {
        return;
    }
    
    printf("\nEncrypting files..\n");
    printf("Please input a password and safely remember it: ");
    fgets(key, 25, stdin);
    flush(key, 25);

    strcpy(filename, "secured_files/");
    strcat(filename, name);
    strcat(filename, ".txt");

    /*open file to check if it exists*/
    FILE* dataFile = fopen(filename, "r");
        
    /*stops function if non-existent*/
    if(dataFile == NULL){
        printf("File does not exist\n");
        return;
    }

    char encryptedfilename[256];
    strcpy(encryptedfilename, "secured_files/");
    strcat(encryptedfilename, name);
    strcat(encryptedfilename, ".bin");
            
    /*opening file for encryption*/
    FILE* encryptFile = fopen(encryptedfilename, "wb");


    /*encrypting and printing hexadecimal character by character*/        
    for (i=0; (ch = fgetc(dataFile)) != EOF; i++) {
        char encrypted = ch ^ key[i % strlen(key)];
        fprintf(encryptFile, "%02X ", (unsigned char)encrypted);
    }

    fclose(dataFile);
    fclose(encryptFile);

    /*erasing data from compression to make it unreadable*/
    dataFile = fopen(filename, "w");
    fclose(dataFile);

    /* remove compressed grade file */
    remove(filename);

    printf("%s's grade file encrypted.\n", name);
}


void decryptFile(char* name){
    /* intialise relevant variables */
    int i;
    char key[25];
    char encryptedfilename[256];
    char filename[256], student_name[MAX_NAME_LEN];
    
    /* search for student via name */
    printf("\nEnter student name to decrypt & decompress: ");
    fgets(student_name, sizeof(student_name), stdin);
    flush(student_name, MAX_NAME_LEN);

    /*setting up given name argument for compression file*/
    strcpy(name, student_name);

    /* open encryption file */
    strcpy(encryptedfilename, "secured_files/");
    strcat(encryptedfilename, name);
    strcat(encryptedfilename, ".bin");

    /*open file to check if it exists*/
    FILE* encryptedFile = fopen(encryptedfilename, "r");
    
    /*stops function if non-existent*/
    if(encryptedFile == NULL){
        printf("File does not exist\n");
        name[0] = '\0';
        return;
    }

    /* check if encryption key is correct */
    printf("Please enter the password: ");
    fgets(key, sizeof(key), stdin);
    flush(key, strlen(key));
    
    /*naming compressed student file*/
    strcpy(filename, "secured_files/");
    strcat(filename, name);
    strcat(filename, ".txt");

    /* open compression file to write */
    FILE* dataFile = fopen(filename, "w");
    unsigned char byte;
    
    /*decrypting each character*/
    for(i=0; fscanf(encryptedFile, "%2hhX", &byte) == 1; i++){
        char decrypted = byte ^ key[i % strlen(key)];
        fprintf(dataFile, "%c", decrypted);
    }

    /* remove encrypted grade file */
    remove(encryptedfilename);

    /* close files */
    fclose(encryptedFile);
    fclose(dataFile);
}
