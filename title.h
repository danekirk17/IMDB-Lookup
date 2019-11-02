struct title_basics {
	char *tconst;
	char *primaryTitle;
};

struct title_basics * get_title(char *dir, int *arrSize);
void freeTitleArr(struct title_basics *arr, int size);
