#include "graph.h"

void bfs(Graph G, int v)
{
	Queue Q;
	Position p;
	
	Q = create_queue();
	enqueue(Q, G->adj_list[v]->data);
	while (!empty_queue(Q))
	{
		GraphVertex v = dequeue(Q);
		if (G->visited[v->value] == FALSE)
		{
			visit(v);
			G->visited[v->value] = TRUE;
		}

		// �� v �ڽӵ�����δ���ʶ��� w ���
		for (p = G->adj_list[v->value]->next; p; p = p->next)
		{
			GraphVertex w = p->data;
			if (G->visited[w->value] == FALSE)
				enqueue(Q, w);
		}
	}
	destroy_queue(Q);
}