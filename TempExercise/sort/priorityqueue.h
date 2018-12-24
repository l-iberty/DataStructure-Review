#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#define MIN_DATA (-1)

typedef struct HeapStruct *PriorityQueue;

struct HeapStruct
{
	int *elements;
	int capacity;
	int size;
};

PriorityQueue pq_init(int max_elements);
void pq_insert(PriorityQueue H, int data);
int pq_deletemin(PriorityQueue H);
bool pq_empty(PriorityQueue H);
bool pq_full(PriorityQueue H);
void pq_destroy(PriorityQueue H);

#endif
