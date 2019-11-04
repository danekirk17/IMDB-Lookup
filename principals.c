#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "principals.h"
#include "common.h"
#include "binary.h"

struct node * find_tconst_tp(struct principal_data *data, char *tconst)
{
    struct node *found_node;

    found_node = find(data->tconst_root, tconst);

    if (found_node == NULL)
    {
        return NULL;
    }
    else
    {
        return found_node;
    }
}

void build_tindex_tp(struct principal_data *arr)
{
    int i;
    for (i = 0; i < arr->size; i++)
    {
        add_node(&(arr->tconst_root), (arr->array[i]).tconst, &((arr->array)[i]));
    }
}

struct node * find_nconst_tp(struct principal_data *data, char *nconst)
{
    struct node *found_node;

    found_node = find(data->nconst_root, nconst);

    if (found_node == NULL)
    {
        return NULL;
    }
    else
    {
        return found_node;
    }
}

void build_nindex_tp(struct principal_data *arr)
{
    int i;
    for (i = 0; i < arr->size; i++)
    {
        add_node(&(arr->nconst_root), (arr->array[i]).nconst, &((arr->array)[i]));
    }
}

struct principal_data * get_principals(char *dir)
{
    struct title_principals *arr;
    struct principal_data *arr_struct = malloc(sizeof(struct principal_data));
    FILE *fp;
    int cActors;
    char line[1024];
    char col[512];
    /*open data file*/
    char *fileDir = "/title.principals.tsv";
    char *fullDir = calloc(strlen(dir) + strlen(fileDir)+1, sizeof(char));
    strcat(fullDir, dir);
    strcat(fullDir, fileDir);
    fp = fopen(fullDir, "r");
    if (fp == NULL) {
        printf("FOPEN FAILED\n");
        return NULL;
    }
    /*find all the relevant lines in the file*/
    cActors = 0;
    while (fgets(line, 1024, fp) != NULL) {
        get_column(line, col, 3);   /*get the category column*/
        if (strstr(col, "actor") != NULL || strstr(col, "actress") != NULL)
        {
            cActors++;
        }
    }
    /*create array to be returned*/
    arr = malloc(sizeof(struct title_principals) * cActors);
    arr_struct->size = cActors;
    /*read whole file again and save data in the array*/
    fseek(fp, 0, SEEK_SET);
    cActors = 0;
    while (fgets(line, 1024, fp) != NULL) {
        get_column(line, col, 3);   /*get the category column*/
        if (strstr(col, "actor") != NULL || strstr(col, "actress") != NULL) /*if they are an actor or actress*/
        {
            get_column(line, col, 0);                            /*get their tconst*/
            arr[cActors].tconst = malloc(strlen(col) + 1);      /*malloc space for their tconst in the array*/
            strrev(col);                                        /*reverse tconst*/
            strcpy(arr[cActors].tconst, col);                   /*copy tconst into the array*/
            get_column(line, col, 2);                           /*repeat for their nconst*/
            arr[cActors].nconst = malloc(strlen(col) + 1);
            strrev(col);                                        /*reverse nconst*/
            strcpy(arr[cActors].nconst, col);
            get_column(line, col, 5);                           /*repeat for their characters*/
            arr[cActors].characters = malloc(strlen(col) + 1);
            strcpy(arr[cActors].characters, col);
            cActors++;
        }
    }

    fclose(fp);

    arr_struct->array = arr;    /*add the title array to the struct to be returned.*/
    arr_struct->nconst_root = 0;    /*set tree roots to zero*/
    arr_struct->tconst_root = 0;
    return arr_struct;
}

void freePrinArr(struct title_principals *arr, int size)
{
    int i;
    for (i = 0; i < size; ++i)
    {
        free(arr[i].tconst);
        free(arr[i].nconst);
        free(arr[i].characters);
    }
    free(arr);
}
