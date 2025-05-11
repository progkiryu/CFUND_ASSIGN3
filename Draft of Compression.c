/*This is very iffy and it might be wrong as even after watching a bunch of videos I wasn't too sure bow to go about this*/
/*Im not sure what the file names are so i used placeholders like inputfilename etc*/
/*case 10:
    getchar();  
    compressStudentByName();
    break; */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DICT_SIZE 5
#define MAX_LINE 256
#define MAX_NAME_LEN 100
#define PATH_LEN 200

const char *patterns[DICT_SIZE] = {
    "Name:", "Class:", "Subject:", "Mark:", "Comment:"
};

const char *tokens[DICT_SIZE] = {
    "@N", "@C", "@S", "@M", "@O"
};

void compressStudentByName() {
    char studentName[MAX_NAME_LEN];
    char inputPath[PATH_LEN];
    char outputPath[PATH_LEN];
    FILE *inFile;
    FILE *outFile;
    char line[MAX_LINE];
    char buffer[MAX_LINE];
    char *pos;
    int offset;
    int i;

    printf("Enter student name (as saved in filename): ");
    fgets(studentName, sizeof(studentName), stdin);
    studentName[strcspn(studentName, "\n")] = '\0'; 


    sprintf(inputPath, "grades/%s.txt", studentName);
    sprintf(outputPath, "grades_compressed/%s.cmp", studentName);

    inFile = fopen(inputPath, "r");
    if (inFile == NULL) {
        printf("Error: Cannot open input file for %s\n", studentName);
        return;
    }

    outFile = fopen(outputPath, "w");
    if (outFile == NULL) {
        printf("Error: Cannot create output file for %s\n", studentName);
        fclose(inFile);
        return;
    }

  
    while (fgets(line, sizeof(line), inFile) != NULL) {
   
        strcpy(buffer, line);

        for (i = 0; i < DICT_SIZE; i++) {
            while ((pos = strstr(buffer, patterns[i])) != NULL) {
                offset = (int)(pos - buffer);
                buffer[offset] = '\0';
                strcat(buffer, tokens[i]);
                strcat(buffer, pos + strlen(patterns[i]));
                strcpy(line, buffer);
            }
        }
        fputs(line, outFile);
    }

    printf("Student '%s' compressed successfully.\n", studentName);

    fclose(inFile);
    fclose(outFile);
}
