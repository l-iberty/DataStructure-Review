#include <stdio.h>
#include <stdlib.h>
#include "avltree.h"

void print_tree(AvlTree T)
{
	printf("pre:\t");
	pre_order(T);
	printf("\n");
	printf("in:\t");
	in_order(T);
	printf("\n");
}

int main()
{
	AvlTree T = NULL;
	int data[] = { 3, 2, 1, 4, 5, 6, 7, 16, 15, 14, 13, 12, 11, 10, 8, 9 };

	for (int i = 0; i < _countof(data); i++)
		T = avl_insert(T, data[i]);

	print_tree(T);
	printf("max=%d, min=%d\n", avl_find_max(T)->data, avl_find_min(T)->data);

	destroy(T);
}