#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "priorityqueue.h"

void print_array(int x[], int n)
{
	for (int i = 0; i < n; i++)
		printf("%d ", x[i]);
	printf("\n");

}

void swap(int &x, int &y)
{
	int t = x;
	x = y;
	y = t;
}

void insert_sort(int x[], int n)
{
	int i, j;
	int temp;
	for (i = 1; i < n; i++)
	{
		temp = x[i];
		for (j = i; j > 0; j--)
		{
			if (temp < x[j - 1])
				x[j] = x[j - 1];
			else
				break;
		}
		x[j] = temp;
		print_array(x, n);
	}
}

void insert_sort_list(List L)
{
	List current, next, p;
	current = L->next;
	L->next = NULL;
	for (; current; current = next)
	{
		for (p = L; p->next; p = p->next)
		{
			if (p->next->data > current->data)
				break;
		}
		next = current->next;
		current->next = p->next;
		p->next = current;
		print_list(L);
	}

}

void select_sort(int x[], int n)
{
	int i, j, min;
	for (i = 0; i < n - 1; i++)
	{
		min = i;
		for (j = i + 1; j < n; j++)
		{
			if (x[j] < x[min])
				min = j;
		}
		swap(x[min], x[i]);
		print_array(x, n);
	}
}


int main()
{
	int x[] = { 12, 5, 6, 18, 18, 13, 56, 34, 30, 49 };
	//insert_sort(x, _countof(x));
	select_sort(x, _countof(x));
	//List L = init_list(x, _countof(x));
	//insert_sort_list(L);
	//print_list(L);
	//destory_list(L);

	//PriorityQueue H = pq_init(_countof(x));
	//for (int i = 0; i < _countof(x); i++)
	//	pq_insert(H, x[i]);
	//while (!pq_empty(H))
	//{
	//	printf("%d ", pq_deletemin(H));
	//}
	//pq_destroy(H);
}