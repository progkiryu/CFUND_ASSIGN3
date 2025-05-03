#include <stdio.h>
#include <string.h>
#include "system.h"

void flush(char *arr, int inputLength){
    int character;
    char *p_string = NULL;

    if((p_string = strchr(arr,'\n')) == NULL){ /*exceeding the array limit*/
        while((character = getchar())!= '\n' && character != EOF); /*erase excess string*/
        arr[inputLength-1] = '\0';
    }
    
    else if((p_string = strchr(arr,'\n')) != NULL){ /*within the array limit*/
        *p_string = '\0';
    }
}