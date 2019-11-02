struct name_basics
{
	char *nconst;
	char *primaryName;
};

struct name_basics * get_name(char *dir, int *arrSize);
void freeNameArr(struct name_basics * arr, int size);