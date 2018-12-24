#ifndef AVL_TREE
#define AVL_TREE

#define MAX(a,b) (((a)>(b))?(a):(b))

typedef struct AvlTree_t *AvlTree;

struct AvlTree_t
{
	int data;
	int height;
	AvlTree left;
	AvlTree right;
};

AvlTree avl_insert(AvlTree T, int data);
AvlTree avl_delete(AvlTree T, int data);
AvlTree avl_find_max(AvlTree T);
AvlTree avl_find_min(AvlTree T);
AvlTree single_rotate_left(AvlTree K);
AvlTree single_rotate_right(AvlTree K);
AvlTree double_rotate_left(AvlTree K);
AvlTree double_rotate_right(AvlTree K);
int height(AvlTree T);
void pre_order(AvlTree T);
void in_order(AvlTree T);
void destroy(AvlTree T);

#endif // AVL_TREE
