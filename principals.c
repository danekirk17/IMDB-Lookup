#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "principals.h"
#include "common.h"

struct title_principals * get_principals(char *dir, int *arrSize) {
    struct title_principals *arr;
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
        return -1;
    }
    printf("Opening: %s\n", fullDir);
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
    (*arrSize) = cActors;
    /*read whole file again and save data in the array*/
    fseek(fp, 0, SEEK_SET);
    cActors = 0;
    while (fgets(line, 1024, fp) != NULL) {
        get_column(line, col, 3);   /*get the category column*/
        if (strstr(col, "actor") != NULL || strstr(col, "actress") != NULL) /*if they are an actor or actress*/
        {
            get_column(line, col, 0);                            /*get their tconst*/
            arr[cActors].tconst = malloc(strlen(col) + 1);      /*malloc space for their tconst in the array*/
            strcpy(arr[cActors].tconst, col);                   /*copy tconst into the array*/
            get_column(line, col, 2);                           /*repeat for their nconst*/
            arr[cActors].nconst = malloc(strlen(col) + 1);
            strcpy(arr[cActors].nconst, col);
            get_column(line, col, 5);                           /*repeat for their characters*/
            arr[cActors].characters = malloc(strlen(col) + 1);
            strcpy(arr[cActors].characters, col);
            cActors++;
        }
    }

    fclose(fp);
    return arr;
}

void freePrinArr(struct title_principals *arr, int size) {
    int i;
    for (i = 0; i < size; ++i)
    {
        free(arr[i].tconst);
        free(arr[i].nconst);
        free(arr[i].characters);
    }
    free(arr);
}
