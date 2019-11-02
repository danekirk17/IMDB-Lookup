#include <stdlib.h>
#include <stdio.h>
#include<string.h>
#include "common.h"
#include "name.h"
#include "title.h"
#include "principals.h"
#include "binary.h"

void testTitle(struct title_data *arr)
{
	int i;
	for (i=0;i<10;i++)

  {

    printf( "%s %s\n", (arr->array)[i].tconst, (arr->array)[i].primaryTitle );

  }

  printf( "\n" );

  for (i=524619;i<524629;i++)

  {

    printf( "%s %s\n", (arr->array)[i].tconst, (arr->array)[i].primaryTitle );

  }
}

void testPrin(struct principal_data *arr)
{
	int i;
	for (i=0;i<10;i++)

  {

    printf( "%s %s %s\n", (arr->array)[i].tconst,

                          (arr->array)[i].nconst,

                          (arr->array)[i].characters );

  }

  printf( "\n" );

  for (i=14627307;i<14627317;i++)

  {

    printf( "%s %s %s\n", (arr->array)[i].tconst,

                          (arr->array)[i].nconst,

                          (arr->array)[i].characters );

  }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {fprintf(stderr, "Usage: %s directory\n", argv[0]);}	/*command line input error checking*/

	struct name_data *nameArr;
	struct title_data *titleArr;
	struct principal_data *prinArr;
	struct name_basics *foundName;
	struct title_basics *foundTitle;
	struct principal_basics *foundPrin;


    nameArr = get_name(argv[1]);
    printf("%d\n", nameArr->size);

    build_nindex(nameArr);

    foundName = find_primary_name(nameArr, "Anthony Daniels");

/*
    titleArr = get_title(argv[1]);
    printf("lines: %d\n", titleArr->size);

    build_tindex(titleArr);

    foundTitle = find_primary_title(titleArr, "Star Wars: Episode V - The Empire Strikes Back");
*/
    if (foundName == NULL)
    {
    	printf("NAME NOT FOUND\n");
    }
    else
    {
    	printf("%s\n", foundName->nconst);
    	printf("%s\n", foundName->primaryName);
	}

/*
    prinArr = get_principals(argv[1]);
    printf("%d\n", prinArr->size);

/*
    freeNameArr(nameArr);
    freeTitleArr(titleArr);
    freePrinArr(prinArr);
*/
    return 0;
}
