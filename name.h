struct name_data
{
	int size;
	struct name_basics * array;
	struct node *nconst_root;
	struct node *primaryName_root;
};

struct name_basics
{
	char *nconst;
	char *primaryName;
};

struct name_data * get_name(char *dir);
void freeNameArr(struct name_basics * arr, int size);
void build_tindex(struct name_data *arr);
struct name_basics * find_primary_name(struct name_data *data, char *title);
