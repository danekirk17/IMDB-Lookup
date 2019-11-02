struct title_principals
{
	char *tconst;
	char *nconst;
	char *characters;
};

struct title_principals * get_principals(char *dir, int *arrSize);
void freePrinArr(struct title_principals *arr, int size);
