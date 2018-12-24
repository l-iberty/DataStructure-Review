#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

Table init_table(int nr_ent, int start_vertex)
{
	Table T;

	T = (Table)malloc(sizeof(struct _Table));
	T->nr_ent = nr_ent;
	T->entries = (TableEntry*)malloc((nr_ent + 1) * sizeof(TableEntry));
	
	for (int i = 1; i <= nr_ent; i++)
	{
		T->entries[i] = (TableEntry)malloc(sizeof(struct _TableEntry));
		T->entries[i]->vertex = i;
		T->entries[i]->known = FALSE;
		T->entries[i]->dist = INFINITY;
		T->entries[i]->path = 0;
	}
	T->entries[start_vertex]->dist = 0;
	return T;
}

void print_table(Table T)
{
	printf("------------------------------------\n");
	printf("|   v  |  known  |  dist  |  path  |\n");
	printf("------------------------------------\n");
	for (int i = 1; i <= T->nr_ent; i++)
	{
		printf("|  %2d  |    %2d   |   %2d   |   %2d   |\n",
			T->entries[i]->vertex, T->entries[i]->known,
			T->entries[i]->dist, T->entries[i]->path);
	}
	printf("------------------------------------\n");
}

/* 打印从起点到 vertex 的路径. 起点的 Table:->dist 域为 0. */
void print_path(Table T, int vertex)
{
	if (T->entries[vertex]->dist == 0)
	{
		printf("%d", vertex);
	}
	else
	{
		print_path(T, T->entries[vertex]->path);
		printf(" -> %d", vertex);
	}
}

TableEntry make_table_entry(int vertex, int known, int dist, int path)
{
	TableEntry entry;
	entry = (TableEntry)malloc(sizeof(struct _TableEntry));
	entry->vertex = vertex;
	entry->known = known;
	entry->dist = dist;
	entry->path = path;
	return entry;
}

void destroy_table(Table T)
{
	//for (int i = 1; i <= T->nr_ent; i++)
		//free(T->entries[i]);

	free(T->entries);
	free(T);
}

int find_smallest_unknown_dist(Table T)
{
	int v, min;
	v = -1;
	min = INFINITY;

	for (int i = 1; i <= T->nr_ent; i++)
	{
		if (T->entries[i]->known == FALSE && T->entries[i]->dist < min)
		{
			min = T->entries[i]->dist;
			v = T->entries[i]->vertex;
		}
	}
	return v;
}

