#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "name.h"
#include "common.h"

struct name_basics * get_name(char *dir) {
    struct name_basics arr[1];
    FILE *fp;
    int bytes, cActors;
    char *line = malloc(sizeof(char) * 256);
    char *col;
    /*open data file*/
    char *fileDir = "/name.basics.tsv";
    char *fullDir = malloc(strlen(dir) + strlen(fileDir)+1);
    strcat(fullDir, dir);
    strcat(fullDir, fileDir);
    fp = fopen(fullDir, "r");
    if (fp == NULL) {
        printf("FOPEN FAILED\n");
        return -1;
    }
    printf("Opening: %s\n", fullDir);
    /*count total amount of bytes in file before reading*/
    fseek(fp, 0, SEEK_END);
    bytes = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    /*begin reading*/
    cActors = 0;
    while (fgets(line, 256, fp) != NULL) {
        col = get_column(line, col, 4);
        printf("%s\n", col);
        if (strstr(col, "actor") != NULL || strstr(col, "actress") != NULL)
        {
            printf("FOUND ACTOR/ACTRESS\n");
            cActors++;
        }
    }
    printf("NUM Actors: %d\n", cActors);

    fclose(fp);
    return arr;
}
