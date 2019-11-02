#ifndef COMMON
#define COMMON
struct node
{
	char *key;
	void *data;
	struct node *children[2];
};

void get_column(char *line, char *column, int colNum);
#endif