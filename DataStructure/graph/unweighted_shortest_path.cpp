#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

Table unweighted_shortest_path(Graph G, int start_vertex)
{
	Table T;
	Queue Q;
	GraphVertex vertex;
	Position p;

	T = init_table(G->nr_vertex, start_vertex);
	Q = create_queue();

	vertex = G->adj_list[start_vertex]->data;
	enqueue(Q, vertex);
	while (!empty_queue(Q))
	{
		GraphVertex v = dequeue(Q);
		T->entries[v->value]->known = TRUE;

		for (p = G->adj_list[v->value]->next; p; p = p->next)
		{
			GraphVertex w = p->data;
			if (T->entries[w->value]->dist == INFINITY)
			{
				T->entries[w->value]->dist = T->entries[v->value]->dist + 1;
				T->entries[w->value]->path = v->value;
				enqueue(Q, w);
			}
		}
	}
	destroy_queue(Q);
	return T;
}
