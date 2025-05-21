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

void compressStudentGrades(char* inputName, node* inputNode) {
    FILE* f;
    char name[MAX_NAME_LEN];
    const char* subj;
    const char* com;
    char filename[256];

#ifdef _WIN32
    _mkdir("grades_compressed");
#else
    mkdir("grades_compressed", 0777);
#endif
    
    /* prompt student search via name input */
    printf("Enter student name to compress and encrpypt their grade file: ");
    fgets(name, sizeof(name), stdin);
    flush(name, strlen(name));
    
    /* searches student */
    node* found = searchStudent(name, inputNode);
    /* allows retries if user inputted wrong name by accident */
    while (found == NULL) {
        printf("Enter student name to compress and encrpypt their grade file");
        printf("(type 'exit' to return to menu): ");
        fgets(name, sizeof(name), stdin);
        flush(name, strlen(name));

        /* user can enter "exit" to leave the loop */
        if (strcmp(name, "exit") == 0) {
            return;
        }
        found = searchStudent(name, inputNode);
    }

    /* copy name to char pointer after student has been found */
    strcpy(inputName, name);

    /* add file to compressed folder */
    strcpy(filename, "grades_compressed/");
    strcat(filename, inputName);
    strcat(filename, ".txt");

    f = fopen(filename, "w");
    if (!f) {
        printf("Error opening file for student %s.\n", inputName);
        return;
    }
        
    int i;
    fprintf(f, "%s|%d|%d\n", inputName, found->nodeStudent.classNumber, MAX_SUBJECTS);
    for (i = 0; i < MAX_SUBJECTS; i++) {
        subj = compressWithDict(found -> nodeStudent.subjects[i].name, 
            subjectDict, subjectDictLen);
        com = compressWithDict(found -> nodeStudent.subjects[i].comment, 
            commentDict, commentDictLen);
        fprintf(f, "%s,%d,%s\n", subj, found -> nodeStudent.subjects[i].mark, com);
    }

    fclose(f);

    printf("%s's data compressed into 'grades_compressed' folder.\n", inputName);
}

void decompressStudentGrades(char *inputName) {
    FILE* f;
    char line[256];
    char name[MAX_NAME_LEN];
    int classNum, subCount;
    char subjectCode[MAX_SUB_LEN];
    char commentCode[MAX_COM_LEN];
    int mark;
    const char* fullSub;
    const char* fullCom;
    char filename[256];

    strcpy(filename, "grades_compressed/");
    strcat(filename, inputName);
    strcat(filename, ".txt");

    f = fopen(filename, "r");
    if (!f) {
        printf("Compressed file for %s not found.\n", inputName);
        return;
    }
    int i;
    if (fgets(line, sizeof(line), f)) {
        sscanf(line, "%[^|]|%d|%d", name, &classNum, &subCount);
        printf("\nStudent: %s | Class: %d\n", name, classNum);

        printf("%-*s %-6s %s\n", MAX_SUB_LEN, "Subject", "Bands", "Comment");
        printf("------------------------------------------\n");

        for (i = 0; i < subCount; i++) {
            if (!fgets(line, sizeof(line), f)) {
                break;
            }
            int match;
            match = sscanf(line, "%[^,],%d,%[^\n]", subjectCode, &mark, commentCode);
            
            /*checking for any comments; if comment is empty-*/
            if(match==2){
                commentCode[0] = '\0';
            }

            fullSub = decompressWithDict(subjectCode, subjectDict, subjectDictLen);
            fullCom = decompressWithDict(commentCode, commentDict, commentDictLen);
            printf("%-*s %-6d %s\n", MAX_SUB_LEN, fullSub, mark, fullCom);
        }
    }

    fclose(f);
}
