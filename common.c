#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "common.h"

void get_column(char *line, char *column, int colNum) {
    int tab1, tab2, tabC, i, lenCol;
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
            } else if (tabC == (colNum+1))
            {
                tab2 = i;
                break;
            }
        }
    }
    
    if (colNum != 0)
    {
        tab1++;
    }
    lenCol = tab2-tab1;
    line += tab1;
    /*
    if (column == NULL)
    {
        column = malloc(lenCol+1);
    }
    */
    strncpy(column, line, lenCol);
    column[lenCol] = '\0';
}
