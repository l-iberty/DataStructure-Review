#ifndef GRAPH_H
#define GRAPH_H

#define FALSE 0
#define TRUE  1
#define INFINITY 255
#define MIN_DATA -1

/* for floyd.cpp */
#define N 4 // 顶点数

typedef struct ListEntry *List;
typedef struct ListEntry *Queue;
typedef struct ListEntry *Position;

typedef struct GraphVertexEntry
{
	int value;
	int weight;
} *GraphVertex;

typedef struct GraphEntry
{
	int nr_vertex; // 顶点数
	List *adj_list; // 邻接表
	int *visited;
	int *indegree;
} *Graph;

typedef struct _TableEntry
{
	int vertex;
	int known;
	int dist;
	int path;
} *TableEntry;

typedef struct _Table
{
	int nr_ent;
	TableEntry *entries;
} *Table;

struct ListEntry
{
	GraphVertex data;
	List next;
};

typedef struct HeapEntry
{
	int capacity;
	int size;
	TableEntry *elements;
} *PriorityQueue;

/* graph.cpp */
/* List */
List create_list();
void push_front(List L, GraphVertex data);
void push_back(List L, GraphVertex data);
void print_list(List L);
void destroy_list(List L);

/* Queue */
Queue create_queue();
void enqueue(Queue Q, GraphVertex data);
GraphVertex dequeue(Queue Q);
int empty_queue(Queue Q);
void destroy_queue(Queue Q);

/* Graph */
Graph init_graph(int nr_vertex);
void add_vertex(Graph G, int v, int u, int weight);
void print_graph(Graph G);
void destory_graph(Graph G);
void visit(GraphVertex vertex);
void reset_visited(Graph G);
GraphVertex make_graph_vertex(int value, int weight);
void print_edge(int v, int u);

/* heap.cpp */
PriorityQueue init_heap(int nr_elem);
void insert(PriorityQueue H, TableEntry elem);
TableEntry delete_min(PriorityQueue H);
int empty_heap(PriorityQueue H);
int full_heap(PriorityQueue H);
void percolate_up(PriorityQueue H, int idx);
void percolate_down(PriorityQueue H, int idx);
void destroy_heap(PriorityQueue H);

/* table.cpp */
Table init_table(int nr_ent, int start_vertex);
void print_table(Table T);
void print_path(Table T, int vertex);
TableEntry make_table_entry(int vertex, int known, int dist, int path);
void destroy_table(Table T);
int find_smallest_unknown_dist(Table T);

/* bfs.cpp */
void bfs(Graph G, int v);

/* dfs.cpp */
void dfs(Graph G, int v);

/* top_sort.cpp */
void indegree_counter(Graph G);
void count_indegree(Graph G, int v);
int find_vertex_of_zero_indgree(Graph G);
void top_sort(Graph G);
void top_sort2(Graph G);

/* unweighted_shortest_path.cpp */
Table unweighted_shortest_path(Graph G, int start_vertex);

/* dijikstra.cpp */
Table dijikstra(Graph G, int start_vertex);

/* prim.cpp */
Table prim(Graph G, int start_vertex);

/* floyd.cpp */
void floyd(int adj_matrix[N][N], int dist[N][N], int path[N][N]);

#endif // GRAPH_H
