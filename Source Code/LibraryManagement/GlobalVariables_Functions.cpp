#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>
#include "LibraryObject.h"
#include "GlobalVariables_Functions.h"
//global variable currentUSER
struct USER *currentUSER = new USER;
//clear buffer (temp)
void cleartemp() 
{
    while (getchar() != '\n');
}
//import string that cannot include space
void importStringNotIncludeSpace(char *input, int length, char *displaystring)
{
    while (strstr(input, " ") != NULL)
    {
        printf("Space exists in %s, Please enter again.\n", displaystring);
        printf("Enter again: ");
        gets_s(input, length);
    }
}
//Check if string str exists in string src? don't care about character's case
char *strstri(char *src, char *str)
{
    char *str1 = new char[40];
    char *src1 = new char[40];
    strcpy_s(str1, 40, str);
    strcpy_s(src1, 40, src);
    int i = 0;
    while (str1[i])
    {
        str1[i] = tolower(str1[i]);
        i++;
    }
    i = 0;
    while (src1[i])
    {
        src1[i] = tolower(src1[i]);
        i++;
    }
    char *result = strstr(src1, str1);
    delete[]str1;
    delete[]src1;
    return result;
}