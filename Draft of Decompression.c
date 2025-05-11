#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DICT_SIZE 5
#define MAX_LINE 256
#define MAX_NAME_LEN 100

const char *tokens[DICT_SIZE] = {
    "@N", "@C", "@S", "@M", "@O"
};

const char *patterns[DICT_SIZE] = {
    "Name:", "Class:", "Subject:", "Mark:", "Comment:"
};

void decompressAndDisplayStudent(const char* filename) {
    FILE *inFile;
    char line[MAX_LINE];
    char buffer[MAX_LINE];
    char studentName[MAX_NAME_LEN];
    int i, found = 0;
    char *pos;
    int offset;

    printf("Enter student name to view (case-sensitive): ");
    fgets(studentName, sizeof(studentName), stdin);

  
    studentName[strcspn(studentName, "\n")] = '\0';

    inFile = fopen(filename, "r");

    if (inFile == NULL) {
        printf("Error opening file: %s\n", filename);
        return;
    }

    printf("\nSearching for: %s\n\n", studentName);

    while (fgets(line, sizeof(line), inFile) != NULL) {

        if (strncmp(line, "@N", 2) == 0 && strstr(line, studentName) != NULL) {
            found = 1;
        }

        if (found) {

            for (i = 0; i < DICT_SIZE; i++) {
                while ((pos = strstr(line, tokens[i])) != NULL) {
                    offset = (int)(pos - line);
                    strncpy(buffer, line, offset);
                    buffer[offset] = '\0';
                    strcat(buffer, patterns[i]);
                    strcat(buffer, pos + strlen(tokens[i]));
                    strcpy(line, buffer);
                }
            }


            if (strncmp(line, "@N", 2) == 0 && strstr(line, studentName) == NULL && found == 1) {
                break;
            }

            printf("%s", line);
        }
    }

    if (!found) {
        printf("Student not found.\n");
    }

    fclose(inFile);
}
