struct principal_data
{
	int size;
	struct title_principals * array;
	struct node *tconst_root;
	struct node *nconst_root;
	struct node *characters_root;
};

struct title_principals
{
	char *nconst;
	char *tconst;
	char *characters;
};

struct principal_data * get_principals(char *dir);
void freePrinArr(struct title_principals *arr, int size);
