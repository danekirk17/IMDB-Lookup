#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "name.h"
#include "common.h"

struct name_basics * get_name(char *dir, int *arrSize) {
    struct name_basics *arr;
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
        return -1;
    }
    printf("Opening: %s\n", fullDir);
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
    (*arrSize) = cActors;
    /*read whole file again and save actors data in the array*/
    fseek(fp, 0, SEEK_SET);
    cActors = 0;
    while (fgets(line, 256, fp) != NULL) {
        get_column(line, col, 4);   /*get the occupation column*/
        if (strstr(col, "actor") != NULL || strstr(col, "actress") != NULL) /*if they are an actor or actress*/
        {
            get_column(line, col, 0);                            /*get their nconst*/
            arr[cActors].nconst = malloc(strlen(col) + 1);      /*malloc space for their nconst in the array*/
            strcpy(arr[cActors].nconst, col);                   /*copy nconst into the array*/
            get_column(line, col, 1);                           /*repeat for their names*/
            arr[cActors].primaryName = malloc(strlen(col) + 1);
            strcpy(arr[cActors].primaryName, col);
            cActors++;
        }
    }

    fclose(fp);
    return arr;
}

void freeNameArr(struct name_basics *arr, int size) {
    int i;
    for (i = 0; i < size; ++i)
    {
        free(arr[i].nconst);
        free(arr[i].primaryName);
    }
    free(arr);
}
