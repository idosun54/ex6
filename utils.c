#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

int getInt(const char* prompt)
{
  printf("%s", prompt);
  int num;
  scanf("%d", &num);
  return num;
}


//Change
char* getString(const char* prompt)
{
  printf("%s", prompt);
   char ch;
   char *temp = malloc(sizeof(char));
   if (!temp) return NULL;
    temp[0] = '\0';
   int currentLen = 0;
   while (scanf("%c", &ch) == 1 && ch != '\n') 
   {
    char *next = realloc(temp, currentLen + 2*sizeof(char));
        if (!next) { 
            free(temp); 
            return NULL; 
        }
        temp = next;
        temp[currentLen++] = ch;
        temp[currentLen] = '\0';
    }
    return temp;
}