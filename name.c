#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "name.h"

struct name_basics * get_name(char *dir) {
    struct name_basics arr[1];
    FILE *fp;
    int bytes;
    char *line = malloc(sizeof(char) * 256);
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
    /*count total amount of bytes in file before reading*/
    fseek(fp, 0, SEEK_END);
    bytes = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    /*begin reading*/
    while (fgets(line, 256, fp) != NULL) {
        printf("%s\n", line);

    }

    fclose(fp);
    return arr;
}
