/* Dane Kirkpatrick
 * 1004843
 * dkirkpat@uoguelph.ca
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "title.h"
#include "common.h"
#include "binary.h"

struct title_basics * find_tconst(struct title_data *data, char *tconst)
{
    struct node *found_node;

    found_node = find(data->tconst_root, tconst);

    if (found_node == NULL)
    {
        return NULL;
    }
    else
    {
        return ((struct title_basics *)(found_node->data));
    }
}

struct title_basics * find_primary_title(struct title_data *data, char *title)
{
    struct node *found_node;

    found_node = find(data->primaryTitle_root, title);

    if (found_node == NULL)
    {
        return NULL;
    }
    else
    {
        return ((struct title_basics *)(found_node->data));
    }
}
/*function builds tree: key = tconst, value = primaryTitle*/
void build_tindex(struct title_data *arr)
{
    int i;
    for (i = 0; i < arr->size; i++)
    {
        add_node(&(arr->tconst_root), (arr->array[i]).tconst, &((arr->array)[i]));
    }
}
/*function builds tree: key = primaryTitle, value = tconst*/
void build_ptindex(struct title_data *arr)
{
    int i;
    for (i = 0; i < arr->size; i++)
    {
        add_node(&(arr->primaryTitle_root), (arr->array[i]).primaryTitle, &((arr->array)[i]));
    }
}

struct title_data * get_title(char *dir)
{
    struct title_basics *arr;
    struct title_data *arr_struct = malloc(sizeof(struct title_data));
    FILE *fp;
    int cTitles;
    char line[1024];
    char col1[512];
    char col2[512];
    /*open data file*/
    char *fileDir = "/title.basics.tsv";
    char *fullDir = calloc(strlen(dir) + strlen(fileDir)+1, sizeof(char));
    strcat(fullDir, dir);
    strcat(fullDir, fileDir);
    fp = fopen(fullDir, "r");
    if (fp == NULL) {
        printf("FOPEN FAILED\n");
        return NULL;
    }
    /*find all the actors in the file*/
    cTitles = 0;
    while (fgets(line, 1024, fp) != NULL) {
        get_column(line, col1, 1);
        get_column(line, col2, 4);
        if (strstr(col1, "movie") != NULL && strstr(col2, "0") != NULL)
        {
            cTitles++;
        }
    }
    /*create array of actors to be returned*/
    arr = malloc(sizeof(struct title_basics) * cTitles);
    arr_struct->size = cTitles;
    /*read whole file again and save actors data in the array*/
    fseek(fp, 0, SEEK_SET);
    cTitles = 0;
    while (fgets(line, 1024, fp) != NULL) {
        get_column(line, col1, 1);   /*get the titleType column*/
        get_column(line, col2, 4);   /*get the isAdult column*/
        if (strstr(col1, "movie") != NULL && strstr(col2, "0") != NULL) /*if it is a movie and is not porn*/
        {
            get_column(line, col1, 0);                            /*get their tconst*/
            arr[cTitles].tconst = malloc(strlen(col1) + 1);      /*malloc space for their tconst in the array*/
            strrev(col1);                                        /*reverse the tconst value before storing it in table*/
            strcpy(arr[cTitles].tconst, col1);                   /*copy tconst into the array*/
            get_column(line, col2, 2);                           /*repeat for their titles*/
            arr[cTitles].primaryTitle = malloc(strlen(col2) + 1);
            strcpy(arr[cTitles].primaryTitle, col2);
            cTitles++;
        }
    }

    fclose(fp);

    arr_struct->array = arr;    /*add the title array to the struct to be returned.*/
    arr_struct->tconst_root = 0;    /*set tree roots to zero*/
    arr_struct->primaryTitle_root = 0;
    return arr_struct;
}

void freeTitleArr(struct title_basics *arr, int size)
{
    int i;
    for (i = 0; i < size; ++i)
    {
        free(arr[i].tconst);
        free(arr[i].primaryTitle);
    }
    free(arr);
}
