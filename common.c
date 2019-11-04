/* Dane Kirkpatrick
 * 1004843
 * dkirkpat@uoguelph.ca
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "common.h"

void strrev(char *string)
{
    int ind1;
    int ind2;
    char temp;
    ind1 = 0;
    ind2 = strlen(string) - 1;
    while (ind1 < ind2)
    {
        temp = string[ind1];
        string[ind1] = string[ind2];
        string[ind2] = temp;
        ind1++;
        ind2--;
    }
}

struct node *find( struct node *root, char *value )
{
    if (root)
    {
        if ( strcmp( value, root->key ) == 0)
        {
            return root;
        }
        else
        {
            if ( strcmp(value, (root)->key) < 0 )
            {
                return find( root->children[0], value );
            }
            else /* value>=(root)->number */
            {
                return find( root->children[1], value );
            }
        }
    }
    else 
    {
        return NULL;
    }
}

void get_column(char *line, char *column, int colNum)
{
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
