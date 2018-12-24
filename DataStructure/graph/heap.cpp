#include "graph.h"
#include <stdio.h>
#include <stdlib.h>


PriorityQueue init_heap(int nr_elem)
{
	PriorityQueue H;
	H = (PriorityQueue)malloc(sizeof(struct HeapEntry));
	H->elements = (TableEntry*)malloc((nr_elem + 1) * sizeof(TableEntry));
	H->elements[0] = make_table_entry(0, 0, MIN_DATA, 0);
	H->capacity = nr_elem;
	H->size = 0;
	return H;
}

void insert(PriorityQueue H, TableEntry elem)
{
	int i;

	if (full_heap(H))
	{
		fprintf(stderr, "PriorityQueue is full");
		return;
	}

	for (i = ++H->size; i >= 0; i /= 2)
	{
		if (elem->dist < H->elements[i / 2]->dist)
			H->elements[i] = H->elements[i / 2];
		else
			break;
	}
	H->elements[i] = elem;
}

TableEntry delete_min(PriorityQueue H)
{
	int i, child;
	TableEntry min_elem, last_elem;

	if (empty_heap(H))
	{
		fprintf(stderr, "PriorityQueue is empty");
		return NULL;
	}

	min_elem = H->elements[1];
	last_elem = H->elements[H->size--];

	for (i = 1; i * 2 <= H->size; i = child)
	{
		child = i * 2;
		if (child < H->size &&
			H->elements[child + 1]->dist < H->elements[child]->dist)
			child++;

		if (last_elem->dist > H->elements[child]->dist)
			H->elements[i] = H->elements[child];
		else
			break;
	}
	H->elements[i] = last_elem;
	return min_elem;
}

int empty_heap(PriorityQueue H)
{
	return (H->size == 0);
}

int full_heap(PriorityQueue H)
{
	return (H->capacity == H->size);
}

void percolate_up(PriorityQueue H, int idx)
{
	int i;
	TableEntry temp;

	temp = H->elements[idx];
	for (i = idx; i > 0; i /= 2)
	{
		if (temp->dist < H->elements[i / 2]->dist)
			H->elements[i] = H->elements[i / 2];
		else
			break;
	}
	H->elements[i] = temp;
}

void percolate_down(PriorityQueue H, int idx)
{
	int i, child;
	TableEntry temp;

	temp = H->elements[idx];
	for (i = idx; i * 2 <= H->size; i = child)
	{
		child = i * 2;
		if (child < H->size &&
			H->elements[child + 1]->dist < H->elements[child]->dist)
			child++;

		if (temp->dist > H->elements[child]->dist)
			H->elements[i] = H->elements[child];
		else
			break;
	}
	H->elements[i] = temp;
}

void destroy_heap(PriorityQueue H)
{
	for (int i = 0; i <= H->size; i++)
		free(H->elements[i]);

	free(H->elements);
	free(H);
}
