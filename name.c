#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "name.h"
#include "common.h"

struct name_basics * get_name(char *dir) {
    struct name_basics arr[1];
    FILE *fp;
    int bytes;
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
    while (fgets(line, 256, fp) != NULL) {
        get_column(line, &col, 0);
        printf("%s\n", col);
    }

    fclose(fp);
    return arr;
}
