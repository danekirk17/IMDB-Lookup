#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "common.h"
#include "title.h"
#include "binary.h"

void add_node(struct node **root, char *string, void *element)
{
    if (*root) /* there's a node here */
    {
        if ( strcmp(string, (*root)->key) < 0 )
        {
            add_node( &((*root)->children[0]), string, element );
        }
        else
        {
            add_node( &((*root)->children[1]), string, element );
        }
    }
    else /* no node here */
    {
        (*root) = malloc( sizeof( struct node ) );
        (*root)->key = string;
        (*root)->data = element;
        (*root)->children[0]=NULL;
        (*root)->children[1]=NULL;
    }
}