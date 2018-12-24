#ifndef LIST_H
#define LIST_H

typedef struct List_t *List;

struct List_t
{
	int data;
	List next;
};

List init_list(int x[], int n);
void push_back(List L, int data);
void print_list(List L);
void destory_list(List L);

#endif
