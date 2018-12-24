#include <stdio.h>
#include <stdlib.h>
#include "list.h"

List init_list(int x[], int n)
{
	List L;
	int i;
	L = (List)malloc(sizeof(struct List_t));
	L->data = 0;
	L->next = NULL;
	for (i = 0; i < n; i++)
		push_back(L, x[i]);
	return L;
}

void push_back(List L, int data)
{
	List t, p;
	t = (List)malloc(sizeof(struct List_t));
	t->data = data;
	t->next = NULL;

	for (p = L; p->next; p = p->next);
	p->next = t;
}

void print_list(List L)
{
	List p;
	for (p = L->next; p; p = p->next)
		printf("%d ", p->data);
	printf("\n");
}

void destory_list(List L)
{
	List p, t;
	for (p = L; p; p = t)
	{
		t = p->next;
		free(p);
	}
}
