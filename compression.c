#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "system.h"

#define COMPRESSED_FILE "compressed_data.txt"

/* Define dictionary mappings */
const char* subjectDict[][2] = {
    {"Mathematics", "MATH"},
    {"English", "ENG"},
    {"Science", "SCI"},
    {"History", "HIST"},
    {"Geography", "GEO"}
};
const int subjectDictLen = 5;

const char* commentDict[][2] = {
    {"Excellent", "EXC"},
    {"Very Good", "VG"},
    {"Good", "GD"},
    {"Average", "AVG"},
    {"Needs Improvement", "NI"}
};
const int commentDictLen = 5;

/* Helper to replace full string with dictionary code */
const char* compressWithDict(const char* input, const char* dict[][2], int dictLen) {
    int i;
    for (i = 0; i < dictLen; i++) {
        if (strcmp(input, dict[i][0]) == 0) {
            return dict[i][1];
        }
    }
    return input; /* No match found */
}

/* Helper to decompress code to full string */
const char* decompressWithDict(const char* code, const char* dict[][2], int dictLen) {
    int i;
    for (i = 0; i < dictLen; i++) {
        if (strcmp(code, dict[i][1]) == 0) {
            return dict[i][0];
        }
    }
    return code; /* No match found */
}

void compressStudentGrades(node* head, char* inputName) {
    /* initialise relevant variables */
    FILE* f1;
    FILE* f2;
    char name[MAX_NAME_LEN];
    const char* subj;
    const char* com;
    char filename[256];
    char removeFile[MAX_NAME_LEN + 10];

    /* if there are no students, do not bother searching */
    if (head == NULL) {
        printf("\nNo students in database!\n");
        return;
    }
    
    /* prompt student search via name input */
    printf("\nEnter student name to compress and encrypt their grade file: ");
    fgets(name, sizeof(name), stdin);
    flush(name, strlen(name));
    
    strcpy(removeFile, "files/");
    strcat(removeFile, name);
    strcat(removeFile, ".txt");

    /* searches student's grade file */
    f2 = fopen(removeFile, "r");
    if (!f2) {
        printf("Student file does not exist!\n");
        inputName[0] = '\0';
        return;
    }

    /* copy name to char pointer after student has been found */
    strcpy(inputName, name);

    /* add file to compressed folder */
    strcpy(filename, "secured_files/");
    strcat(filename, inputName);
    strcat(filename, ".txt");

    /* open file to write */
    f1 = fopen(filename, "w");
    if (!f1) {
        printf("Error opening file for student %s.\n", inputName);
        inputName[0] = '\0';
        return;
    }
        
    /* read each line from normal grade file and input details 
    into the student struct */
    student temp;
    char message[256];
    
    fgets(message, sizeof(message), f2);
    sscanf(message, "Student Name: %s", temp.name);

    fgets(message, sizeof(message), f2);
    sscanf(message, "Student Class Number: %d", &temp.classNumber);

    fgets(message, sizeof(message), f2);
    fgets(message, sizeof(message), f2);

    int idx;
    for (idx = 0; idx < MAX_SUBJECTS; idx++) {
        fgets(message, sizeof(message), f2);
        sscanf(message, "- %[^:]: Band %d | %[^\n]",
        temp.subjects[idx].name, &temp.subjects[idx].mark,
        temp.subjects[idx].comment);
    }

    /* read each attribute from the student and output the compressed 
    details to the new file*/
    int i;
    fprintf(f1, "%s|%d|%d\n", inputName, temp.classNumber, MAX_SUBJECTS);
    for (i = 0; i < MAX_SUBJECTS; i++) {
        subj = compressWithDict(temp.subjects[i].name, 
            subjectDict, subjectDictLen);
        com = compressWithDict(temp.subjects[i].comment, 
            commentDict, commentDictLen);
        fprintf(f1, "%s,%d,%s\n", subj, temp.subjects[i].mark, com);
    }

    fclose(f1);
    fclose(f2);

    /* remove original grade file */
    remove(removeFile);

    printf("%s's data compressed into 'grades_compressed' folder.\n", 
        inputName);
}

void decompressStudentGrades(char *inputName) {
    /* initialise relevant variables */
    FILE* f1;
    FILE* f2;
    char line[256];
    char name[MAX_NAME_LEN];
    int classNum, subCount;
    char subjectCode[MAX_SUB_LEN];
    char commentCode[MAX_COM_LEN];
    int mark;
    const char* fullSub;
    const char* fullCom;
    char filename[256];
    char orgFile[MAX_NAME_LEN + 10];

    /* if decryption did not work, return to menu */
    if (strlen(inputName) == 0) {
        return;
    }

    /* create filename for compressed file */
    strcpy(filename, "secured_files/");
    strcat(filename, inputName);
    strcat(filename, ".txt");

    /* create filename for normal grade file */
    strcpy(orgFile, "files/");
    strcat(orgFile, inputName);
    strcat(orgFile, ".txt");

    /* open compression file to read */
    f1 = fopen(filename, "r");
    if (!f1) {
        printf("Compressed file for %s not found.\n", inputName);
        return;
    }

    /* open normal grade file to write */
    f2 = fopen(orgFile, "w");
    if (!f2) {
        printf("Error opening file to write!\n");
        return;
    }

    /* in each line from the compression file, write into the normal grade 
    file */
    int i;
    if (fgets(line, sizeof(line), f1)) {
        sscanf(line, "%[^|]|%d|%d", name, &classNum, &subCount);
        fprintf(f2, "Student Name: %s\n", name);
        fprintf(f2, "Student Class Number: %d\n\n", classNum);        
        fprintf(f2, "Subject Grades:\n");

        for (i = 0; i < subCount; i++) {
            if (!fgets(line, sizeof(line), f1)) {
                break;
            }
            int match;
            match = sscanf(line, "%[^,],%d,%[^\n]", subjectCode, &mark, 
            commentCode);
            
            /*checking for any comments; if comment is empty-*/
            if(match==2){
                commentCode[0] = '\0';
            }

            fullSub = decompressWithDict(subjectCode, subjectDict, 
            subjectDictLen);
            fullCom = decompressWithDict(commentCode, commentDict, 
            commentDictLen);

            fprintf(f2, "- %s: Band %d | %s\n", fullSub, mark, fullCom);
        }
    }
    /* close file pointers */
    fclose(f1);
    fclose(f2);

    /* remove compression file */
    remove(filename);
}