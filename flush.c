#include <stdio.h>
#include <string.h>
#include "system.h"

void flush(char *arr, int maxLength){
    if(strlen(arr) == maxLength){ /*exceeding the array limit*/
        while(getchar() == '\n'); /*erase excess string*/
    }
}