#include <stdio.h>
#include <stdlib.h>
#include "priorityqueue.h"

PriorityQueue pq_init(int max_elements)
{
	PriorityQueue H;
	H = (PriorityQueue)malloc(sizeof(struct HeapStruct));
	H->elements = (int*)malloc(sizeof(int) * (max_elements + 1));
	H->elements[0] = MIN_DATA;
	H->capacity = max_elements;
	H->size = 0;
	return H;
}

void pq_insert(PriorityQueue H, int data)
{
	int i;

	if (pq_full(H))
	{
		printf("Error: Full");
		return;
	}

	for (i = ++H->size; i > 0; i /= 2)
	{
		if (data < H->elements[i / 2])
			H->elements[i] = H->elements[i / 2];
		else
			break;
	}
	H->elements[i] = data;
}

int pq_deletemin(PriorityQueue H)
{
	int i, child;
	int min, last;

	if (pq_empty(H))
	{
		printf("Error: Empty");
		return MIN_DATA;
	}

	min = H->elements[1];
	last = H->elements[H->size--];
	for (i = 1; i * 2 <= H->size; i = child)
	{
		child = i * 2;
		if (i * 2 < H->size &&
			H->elements[child + 1] < H->elements[child])
			child++;

		if (last > H->elements[child])
			H->elements[i] = H->elements[child];
		else
			break;
	}
	H->elements[i] = last;
	return min;
}

bool pq_empty(PriorityQueue H)
{
	return H->size == 0;
}

bool pq_full(PriorityQueue H)
{
	return H->size == H->capacity;
}

void pq_destroy(PriorityQueue H)
{
	free(H->elements);
	free(H);
}
