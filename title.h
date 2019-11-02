#ifndef TITLE
#define TITLE
struct title_data
{
	int size;
	struct title_basics * array;
	struct node *tconst_root;
	struct node *primaryTitle_root;
};

struct title_basics {
	char *tconst;
	char *primaryTitle;
};

struct title_data * get_title(char *dir);
void build_tindex(struct title_data *arr);
struct title_basics * find_primary_title(struct title_data *data, char *title);
void freeTitleArr(struct title_basics *arr, int size);
#endif