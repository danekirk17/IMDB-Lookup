#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "title.h"
#include "common.h"

struct title_basics * get_title(char *dir, int *arrSize) {
    struct title_basics *arr;
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
        return -1;
    }
    printf("Opening: %s\n", fullDir);
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
    (*arrSize) = cTitles;
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
            strcpy(arr[cTitles].tconst, col1);                   /*copy tconst into the array*/
            get_column(line, col2, 2);                           /*repeat for their titles*/
            arr[cTitles].primaryTitle = malloc(strlen(col2) + 1);
            strcpy(arr[cTitles].primaryTitle, col2);
            cTitles++;
        }
    }

    fclose(fp);
    return arr;
}

void freeTitleArr(struct title_basics *arr, int size) {
    int i;
    for (i = 0; i < size; ++i)
    {
        free(arr[i].tconst);
        free(arr[i].primaryTitle);
    }
    free(arr);
}
