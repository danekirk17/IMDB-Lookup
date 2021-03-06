/* Dane Kirkpatrick
 * 1004843
 * dkirkpat@uoguelph.ca
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "name.h"
#include "common.h"
#include "binary.h"

struct name_basics * find_nconst(struct name_data *data, char *nconst)
{
    struct node *found_node;

    found_node = find(data->nconst_root, nconst);

    if (found_node == NULL)
    {
        return NULL;
    }
    else
    {
        return ((struct name_basics *)(found_node->data));
    }
    
}

void build_nindex(struct name_data *arr)
{
    int i;
    for (i = 0; i < arr->size; i++)
    {
        add_node(&(arr->nconst_root), (arr->array[i]).nconst, &((arr->array)[i]));
    }
}

struct name_basics * find_primary_name(struct name_data *data, char *title)
{
    struct node *found_node;

    found_node = find(data->primaryName_root, title);

    if (found_node == NULL)
    {
        return NULL;
    }
    else
    {
        return ((struct name_basics *)(found_node->data));
    }
}

void build_pnindex(struct name_data *arr)
{
    int i;
    for (i = 0; i < arr->size; i++)
    {
        add_node(&(arr->primaryName_root), (arr->array[i]).primaryName, &((arr->array)[i]));
    }
}

struct name_data * get_name(char *dir)
{
    struct name_basics *arr;
    struct name_data *arr_struct = malloc(sizeof(struct name_data));
    FILE *fp;
    int cActors;
    char line[256];
    char col[256];
    /*open data file*/
    char *fileDir = "/name.basics.tsv";
    char *fullDir = calloc(strlen(dir) + strlen(fileDir)+1, sizeof(char));
    strcat(fullDir, dir);
    strcat(fullDir, fileDir);
    fp = fopen(fullDir, "r");
    if (fp == NULL) {
        printf("FOPEN FAILED\n");
        return NULL;
    }
    /*find all the actors in the file*/
    cActors = 0;
    while (fgets(line, 256, fp) != NULL) {
        get_column(line, col, 4);
        if (strstr(col, "actor") != NULL || strstr(col, "actress") != NULL)
        {
            cActors++;
        }
    }
    /*create array of actors to be returned*/
    arr = malloc(sizeof(struct name_basics) * cActors);
    arr_struct->size = cActors;
    /*read whole file again and save actors data in the array*/
    fseek(fp, 0, SEEK_SET);
    cActors = 0;
    while (fgets(line, 256, fp) != NULL) {
        get_column(line, col, 4);   /*get the occupation column*/
        if (strstr(col, "actor") != NULL || strstr(col, "actress") != NULL) /*if they are an actor or actress*/
        {
            get_column(line, col, 0);                            /*get their nconst*/
            arr[cActors].nconst = malloc(strlen(col) + 1);      /*malloc space for their nconst in the array*/
            strrev(col);                                        /*reverse nconst before entering it into table*/
            strcpy(arr[cActors].nconst, col);                   /*copy nconst into the array*/
            get_column(line, col, 1);                           /*repeat for their names*/
            arr[cActors].primaryName = malloc(strlen(col) + 1);
            strcpy(arr[cActors].primaryName, col);
            cActors++;
        }
    }

    fclose(fp);

    arr_struct->array = arr;	/*add the name array to the struct to be returned.*/
    arr_struct->nconst_root = 0;	/*set tree roots to zero*/
    arr_struct->primaryName_root = 0;
    return arr_struct;
}

void freeNameArr(struct name_basics *arr, int size)
{
    int i;
    for (i = 0; i < size; ++i)
    {
        free(arr[i].nconst);
        free(arr[i].primaryName);
    }
    free(arr);
}
