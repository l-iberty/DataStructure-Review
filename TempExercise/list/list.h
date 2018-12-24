#ifndef LIST_H
#define LIST_H

typedef struct ListEntry *List;
typedef struct ListEntry *Position;

struct ListEntry
{
	int data;
	List next;
};

List create_list();
void push_back(List L, int x);
List init_list(int *x, int len);
List find_prev(List L, int data);
void print_list(List L);

#endif
