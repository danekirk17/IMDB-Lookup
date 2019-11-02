#include <stdlib.h>
#include <stdio.h>
#include<string.h>
#include "common.h"
#include "name.h"
#include "title.h"
#include "principals.h"

int main(int argc, char *argv[]) {
    int paramErr = 0, i, nameArrSize, titleArrSize, prinArrSize;
    if (argc != 2) {fprintf(stderr, "Usage: %s directory\n", argv[0]);}
/*
    struct name_basics *nameArr = get_name(argv[1], &nameArrSize);
    freeNameArr(nameArr, nameArrSize);

    struct title_basics *titleArr = get_title(argv[1], &titleArrSize);
    freeTitleArr(titleArr, titleArrSize);
*/

    struct title_principals *prinArr = get_principals(argv[1], &prinArrSize);
/*
    freePrinArr(prinArr, prinArrSize);
*/
    for (i=0;i<10;i++)

  {

    printf( "%s %s %s\n", prinArr[i].tconst,

                          prinArr[i].nconst,

                          prinArr[i].characters );

  }

  printf( "\n" );

  for (i=14627307;i<14627317;i++)

  {

    printf( "%s %s %s\n", prinArr[i].tconst,

                          prinArr[i].nconst,

                          prinArr[i].characters );

  }

/*
    printf("%d\n", prinArrSize);
    printf("%s\n", prinArr[0].tconst);
    printf("%s\n", prinArr[0].nconst);
    printf("%s\n", prinArr[0].characters);
/*
    FILE *fp = fopen("files/title.principals.tsv", "r");
    char line[256];
    fgets(line, 256, fp);
    printf("%s\n", line);
*/
    return 0;
}
