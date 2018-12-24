#include <stdio.h>
#include <stdlib.h>
#include "list.h"

List create_list()
{
	List L = (List)malloc(sizeof(struct ListEntry));
	L->next = NULL;
	return L;
}

void push_back(List L, int x)
{
	List Cell;
	Position p;

	Cell = (List)malloc(sizeof(struct ListEntry));
	Cell->data = x;
	Cell->next = NULL;

	for (p = L; p->next; p = p->next);
	p->next = Cell;
}

List init_list(int *x, int len)
{
	List L;

	L = create_list();
	for (int i = 0; i < len; i++)
		push_back(L, x[i]);

	return L;
}

List find_prev(List L, int data)
{
	List p = L;
	while (p->next && p->next->data != data)
		p = p->next;
	return p;
}

void print_list(List L)
{
	Position p;
	for (p = L->next; p; p = p->next)
		printf("%d ", p->data);
	printf("\n");
}