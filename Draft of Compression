/*Im not sure what the file names are so i used placeholders like inputfilename etc*/
/*Also for the main file I think this is gonna be needed to compress the data as its being saved*/
/*case 6:
    getchar();
    saveGradesToFile(head);
    compressWithDictionary("grades.txt", "grades_compressed.txt");
    break; */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DICT_SIZE 5
#define MAX_LINE 256


const char *patterns[DICT_SIZE] = {
    "Name:", "Class:", "Subject:", "Mark:", "Comment:"
};

const char *tokens[DICT_SIZE] = {
    "@N", "@C", "@S", "@M", "@O"
};

void compressWithDictionary(const char* inputFilename, const char* outputFilename) {
    FILE *inFile;
    FILE *outFile;
    char line[MAX_LINE];
    char buffer[MAX_LINE];
    int i;
    char *pos;
    int offset;

    inFile = fopen(inputFilename, "r");
    outFile = fopen(outputFilename, "w");

    if (inFile == NULL || outFile == NULL) {
        printf("Error opening files.\n");
        return;
    }

    while (fgets(line, sizeof(line), inFile) != NULL) {
      
        for (i = 0; i < DICT_SIZE; i++) {
            while ((pos = strstr(line, patterns[i])) != NULL) {
                offset = (int)(pos - line);

               
                strncpy(buffer, line, offset);
                buffer[offset] = '\0';

                strcat(buffer, tokens[i]);

               
                strcat(buffer, pos + strlen(patterns[i]));

                
                strcpy(line, buffer);
            }
        }
        fputs(line, outFile);
    }

    fclose(inFile);
    fclose(outFile);

    printf("Dictionary compression complete. Saved to %s\n", outputFilename);
}
