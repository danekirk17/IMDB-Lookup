/* Dane Kirkpatrick
 * 1004843
 * dkirkpat@uoguelph.ca
 */

#ifndef PRINCIPALS
#define PRINCIPALS
struct principal_data
{
	int size;
	struct title_principals * array;
	struct node *tconst_root;
	struct node *nconst_root;
};

struct title_principals
{
	char *nconst;
	char *tconst;
	char *characters;
};

struct principal_data * get_principals(char *dir);
void freePrinArr(struct title_principals *arr, int size);
void build_nindex_tp(struct principal_data *arr);
void build_tindex_tp(struct principal_data *arr);
struct node * find_nconst_tp(struct principal_data *data, char *nconst);
struct node * find_tconst_tp(struct principal_data *data, char *tconst);
#endif