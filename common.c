#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "common.h"

void get_column(char *line, char **ptrColumn, int colNum) {
    int tab1, tab2, tabC, i, lenCol;
    char *column = (*ptrColumn);
    tab1 = 0;
    tab2 = 0;
    tabC = 0;
    for (i = 0; i < strlen(line); ++i)
    {
        if (line[i] == '\t' || line[i] == '\n')
        {
            tabC++;
            if (tabC == colNum)
            {
                tab1 = i;
            } else if (tabC == (colNum+1)) {
                tab2 = i;
                break;
            }
        }
    }
    lenCol = tab2-tab1;
    column = malloc(256);
    line += tab1 + 1;
    strncpy(column, line, lenCol-1);
    column[strlen(column)] = '\0';
}
