#include <stdlib.h>
#include <stdio.h>
#include<string.h>
#include "common.h"
#include "name.h"
#include "title.h"
#include "principals.h"
#include "binary.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {fprintf(stderr, "Usage: %s directory\n", argv[0]);}	/*command line input error checking*/

	struct name_data *nameArr;
	struct title_data *titleArr;
	struct principal_data *prinArr;
	struct name_basics *foundName;
	struct title_basics *foundTitle;
	struct title_principals *foundPrin;

	printf("BUILDING TITLES\n");
	titleArr = get_title(argv[1]);
	build_ptindex(titleArr);
	build_tindex(titleArr);

	printf("BUILDING NAMES\n");
	nameArr = get_name(argv[1]);
	build_pnindex(nameArr);
	build_nindex(nameArr);

	printf("BUILDING PRINCIPALS\n");
	prinArr = get_principals(argv[1]);
	build_tindex_tp(prinArr);
	build_nindex_tp(prinArr);

	printf("READY\n");
	foundName = find_primary_name(nameArr, "Bruce Lee");
	foundPrin = find_nconst_tp(prinArr, foundName->nconst);
	foundTitle = find_tconst(titleArr, foundPrin->tconst);

	printf("%s\n", foundTitle->primaryTitle);

    return 0;
}
