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

void compressStudentGrades(node* head) {
    FILE* f;
    node* curr;
    student s;
    const char* subj;
    const char* com;
    char filename[256];

#ifdef _WIN32
    _mkdir("grades_compressed");
#else
    mkdir("grades_compressed", 0777);
#endif

    curr = head;
    while (curr) {
        s = curr->nodeStudent;

        strcpy(filename, "grades_compressed/");
        strcat(filename, s.name);
        strcat(filename, ".txt");

        f = fopen(filename, "w");
        if (!f) {
            printf("Error opening file for student %s.\n", s.name);
            curr = curr->next;
            continue;
        }
        int i;
        fprintf(f, "%s|%d|%d\n", s.name, s.classNumber, MAX_SUBJECTS);
        for (i = 0; i < MAX_SUBJECTS; i++) {
            subj = compressWithDict(s.subjects[i].name, subjectDict, subjectDictLen);
            com = compressWithDict(s.subjects[i].comment, commentDict, commentDictLen);
            fprintf(f, "%s,%d,%s\n", subj, s.subjects[i].mark, com);
        }

        fclose(f);
        curr = curr->next;
    }

    printf("All student data compressed into 'grades_compressed' folder.\n");
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

        printf("%-*s %-6s %s\n", MAX_SUB_LEN, "Subject", "Mark", "Comment");
        printf("------------------------------------------\n");

        for (i = 0; i < subCount; i++) {
            if (!fgets(line, sizeof(line), f)) {
                break;
            }
            sscanf(line, "%[^,],%d,%[^\n]", subjectCode, &mark, commentCode);
            fullSub = decompressWithDict(subjectCode, subjectDict, subjectDictLen);
            fullCom = decompressWithDict(commentCode, commentDict, commentDictLen);
            printf("%-*s %-6d %s\n", MAX_SUB_LEN, fullSub, mark, fullCom);
        }
    }

    fclose(f);
}
