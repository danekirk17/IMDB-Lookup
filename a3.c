#include <stdlib.h>
#include <stdio.h>
#include<string.h>
#include "common.h"
#include "name.h"
#include "title.h"
#include "principals.h"
#include "binary.h"

int main(int argc, char *argv[])
{
	/*command line input error checking*/
    if (argc != 2) {fprintf(stderr, "Usage: %s directory\n", argv[0]);}

	struct name_data *nameArr;
	struct title_data *titleArr;
	struct principal_data *prinArr;
	struct name_basics *foundName;
	struct title_basics *foundTitle;
	struct node *foundPrin;
	/*read data from files and build trees*/
	titleArr = get_title(argv[1]);
	build_ptindex(titleArr);
	build_tindex(titleArr);

	nameArr = get_name(argv[1]);
	build_pnindex(nameArr);
	build_nindex(nameArr);

	prinArr = get_principals(argv[1]);
	build_tindex_tp(prinArr);
	build_nindex_tp(prinArr);

	/*get input from user*/
	while (1) {
		int i;
		char readLine[1024];
		char command[6], key[1024], *whiteRemove;
		do {	/*loop until user enters a valid command*/
			printf("> ");
			fgets(readLine, 1000, stdin);
			char *input = readLine;
			/*remove leading whitespace*/
			whiteRemove = &input[0];
			while (input[0] == ' ') {input++;}
			/*remove trailing whitespace*/
			whiteRemove = &input[strlen(input)-1];
			while (whiteRemove[0] == ' ' || whiteRemove[0] == '\n') {whiteRemove--;}
			whiteRemove[1] = '\0';
			/*separate command*/
			i = 0;
			whiteRemove = &input[0];
			while (whiteRemove[0] != ' ') {whiteRemove++; i++;}
			strncpy(command, input, i);
			command[i] = '\0';
			/*separate key*/
			input += i;
			while (input[0] == ' ') {input++;}
			strcpy(key, input);
		} while (strcmp(command, "name") != 0 && strcmp(command, "title") != 0);
		/*execute search*/
		if (strcmp(command, "name") == 0)
		{
			/*search by name*/
			foundName = find_primary_name(nameArr, key);
			if (foundName == NULL) {printf("NAME NOT FOUND\n"); return -1;}
			foundPrin = find_nconst_tp(prinArr, foundName->nconst);
			if (foundPrin == NULL) {printf("PRIN NOT FOUND\n"); return -1;}

			char nconst[15];
			strcpy(nconst, foundPrin->key);

			while (foundPrin)
			{
				if ( strcmp( nconst, foundPrin->key ) == 0)
		        {
		            foundTitle = find_tconst(titleArr, ((struct title_principals *)(foundPrin->data))->tconst);
					if (foundTitle != NULL)
					{
						printf("%s: %s\n", foundTitle->primaryTitle, ((struct title_principals *)(foundPrin->data))->characters);
					}
		        }
				foundPrin = find(foundPrin->children[1], nconst);
			}
		}
		else if (strcmp(command, "title") == 0)
		{
			/*search by title*/
			foundTitle = find_primary_title(titleArr, key);
			if (foundTitle == NULL) {printf("TITLE NOT FOUND\n"); return -1;}
			foundPrin = find_tconst_tp(prinArr, foundTitle->tconst);
			if (foundPrin == NULL) {printf("PRIN NOT FOUND\n"); return -1;}
			char tconst[15];
			strcpy(tconst, foundPrin->key);

			while (foundPrin)
			{
				if ( strcmp( tconst, foundPrin->key ) == 0)
		        {
		            foundName = find_nconst(nameArr, ((struct title_principals *)(foundPrin->data))->nconst);
					if (foundTitle != NULL)
					{
						printf("%s\n", foundName->primaryName);
					}
		        }
				foundPrin = find(foundPrin->children[1], tconst);
			}
		}
	}

	free(titleArr);
	free(nameArr);
	free(prinArr);

    return 0;
}
