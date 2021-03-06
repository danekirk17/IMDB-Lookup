/* Dane Kirkpatrick
 * 1004843
 * dkirkpat@uoguelph.ca
 */

#ifndef COMMON
#define COMMON
struct node
{
	char *key;
	void *data;
	struct node *children[2];
};

void get_column(char *line, char *column, int colNum);
struct node *find( struct node *root, char *value );
void strrev(char *string);
#endif