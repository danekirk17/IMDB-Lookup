#include <stdlib.h>
#include <stdio.h>
#include "name.h"

int main(int argc, char *argv[]) {
	int paramErr = 0;
	int i;
	if (argc != 2) {fprintf(stderr, "Usage: %s directory\n", argv[0]);}
	struct name_basics *nameArr = get_name(argv[1]);
    return 0;
}
