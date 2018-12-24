// 820算法题--树
//
// 2015-四.2
// 交换二叉树的左右子树, 使用非递归实现
// @see exchange2()
//
// Source.cpp 扩展了其他算法的非递归实现：
// @see pre_order2() 先序遍历的非递归实现
// @see in_order2() 中序遍历的非递归实现
//
// 2014-四.2
// 计算二叉树的叶子数和高度
// @see count_leaves()
// @see height()
// @see height2() 非递归实现
//
// 2016-四.2
// 计算二叉树的根节点左右子树相隔最远的叶子节点之间的距离
// @see max_distance()

#include <stdio.h>
#include <stdlib.h>

#define max(a,b) ((a>b)?a:b)
#define MAX_SIZE 20

typedef struct _BinTree *BinTree;
typedef struct _BinTree *BSTree;
typedef struct _Stack *Stack;
typedef struct _Queue *Queue;

struct _BinTree
{
	int data;
	BinTree left;
	BinTree right;
};

struct _Stack
{
	BinTree *data;
	int size;
	int top;
};

struct _Queue
{
	BinTree *data;
	int front;
	int rear;
	int max_size;
};

/////////////////////// BinTree ///////////////////////

BinTree build_tree(int pre[], int pre_from, int pre_to,
	int in[], int in_from, int in_to)
{
	BinTree root;
	int i, shift;
	// 根节点 pre[pre_from]
	root = (BinTree)malloc(sizeof(struct _BinTree));
	root->data = pre[pre_from];

	// 在中序序列中找到根节点 pre[pre_from]
	for (i = in_from; i <= in_to; i++)
	{
		if (in[i] == pre[pre_from])
			break;
	}
	if (i > in_to) // not found
		return NULL;

	shift = i - in_from;
	root->left = build_tree(pre, pre_from + 1, pre_from + shift,
		in, in_from, i - 1);
	root->right = build_tree(pre, pre_from + shift + 1, pre_to,
		in, i + 1, in_to);

	return root;
}

void pre_order(BinTree T)
{
	if (T)
	{
		printf("%d ", T->data);
		pre_order(T->left);
		pre_order(T->right);
	}
}

void in_order(BinTree T)
{
	if (T)
	{
		in_order(T->left);
		printf("%d ", T->data);
		in_order(T->right);
	}
}

void post_order(BinTree T)
{
	if (T)
	{
		post_order(T->left);
		post_order(T->right);
		printf("%d ", T->data);
	}
}

void destroy_tree(BinTree T)
{
	if (T)
	{
		destroy_tree(T->left);
		destroy_tree(T->right);
		free(T);
	}
}

BSTree insert_bstree(BSTree T, int x)
{
	if (T == NULL)
	{
		T = (BSTree)malloc(sizeof(struct _BinTree));
		T->data = x;
		T->left = T->right = NULL;
	}
	else if (x < T->data)
		T->left = insert_bstree(T->left, x);
	else
		T->right = insert_bstree(T->right, x);

	return T;
}

BSTree find_min(BSTree T)
{
	while (T)
		T = T->left;
	return T;
}

BSTree find_max(BSTree T)
{
	while (T)
		T = T->right;
	return T;
}

BSTree delete_bstree(BSTree T, int x)
{
	BSTree Tmp;

	if (T == NULL)
		return NULL;

	if (x < T->data)
		T->left = delete_bstree(T->left, x);
	else if (x>T->data)
		T->right = delete_bstree(T->right, x);
	else
	{
		if (T->left && T->right)
		{
			Tmp = find_min(T->right);
			T->data = Tmp->data;
			T->right = delete_bstree(T->right, Tmp->data);
		}
		else
		{
			Tmp = T;
			if (T->left == NULL)
				T = T->right;
			else
				T = T->left;
			free(Tmp);
		}
	}
	return T;
}

/////////////////////// Stack ///////////////////////

Stack create_stack(int size)
{
	Stack S = (Stack)malloc(sizeof(struct _Stack));
	S->data = (BinTree*)malloc(size*sizeof(BinTree));
	S->top = -1;
	S->size = size;
	return S;
}

int stack_full(Stack S)
{
	return (S->top == S->size - 1);
}

int stack_empty(Stack S)
{
	return (S->top == -1);
}

void push(Stack S, BinTree x)
{
	if (stack_full(S))
	{
		fprintf(stderr, "stack full");
		return;
	}
	S->data[++S->top] = x;
}

BinTree pop(Stack S)
{
	if (stack_empty(S))
	{
		fprintf(stderr, "stack empty");
		return NULL;
	}
	return S->data[S->top--];
}

BinTree top(Stack S)
{
	if (stack_empty(S))
	{
		fprintf(stderr, "stack empty");
		return NULL;
	}
	return S->data[S->top];

}

void destroy_stack(Stack S)
{
	free(S->data);
	free(S);
}

/////////////////////// Stack ///////////////////////

Queue create_queue(int max_size)
{
	Queue Q = (Queue)malloc(sizeof(struct _Queue));
	Q->data = (BinTree*)malloc((max_size + 1) * sizeof(BinTree));
	Q->max_size = max_size + 1;
	Q->front = Q->rear = 0;
	return Q;
}

int queue_full(Queue Q)
{
	return (Q->rear + 1) % Q->max_size == Q->front;
}

int queue_empty(Queue Q)
{
	return Q->front == Q->rear;
}

int queue_size(Queue Q)
{
	return (Q->rear + Q->max_size - Q->front) % Q->max_size;
}

void enqueue(Queue Q, BinTree x)
{
	if (queue_full(Q))
	{
		fprintf(stderr, "queue full");
		return;
	}
	Q->data[Q->rear++] = x;
}

BinTree dequeue(Queue Q)
{
	if (queue_empty(Q))
	{
		fprintf(stderr, "queue empty");
		return NULL;
	}
	return Q->data[Q->front++];
}

void destroy_queue(Queue Q)
{
	free(Q->data);
	free(Q);
}

/////////////////////// Solution ///////////////////////
;
void exchange1(BinTree T)
{
	if (T)
	{
		exchange1(T->left);
		exchange1(T->right);
		BinTree Tmp = T->left;
		T->left = T->right;
		T->right = Tmp;
	}
}

// 使用非递归算法交换左右子树
// 算法思想：
// 先将根节点入栈，当栈非空时：将栈顶元素pop出来，交换其左右子树，若交换后左右子树非空，
// 则将其左右子树入栈. 迭代，直到栈空.
// 非递归算法的交换操作是自顶向下的，递归算法是自底向上的.
void exchange2(BinTree T)
{
	Stack S;
	BinTree t, tmp;

	if (T == NULL)
		return;

	S = create_stack(MAX_SIZE);
	push(S, T);
	while (!stack_empty(S))
	{
		t = pop(S);
		tmp = t->left;
		t->left = t->right;
		t->right = tmp;

		if (t->left)
			push(S, t->left);
		if (t->right)
			push(S, t->right);
	}
	destroy_stack(S);
}

// 先序遍历的非递归实现
void pre_order2(BinTree T)
{
	if (T == NULL)
		return;

	Stack S = create_stack(MAX_SIZE);
	push(S, T);
	while (!stack_empty(S))
	{
		BinTree t = pop(S);
		printf("%d ", t->data);
		if (t->right)
			push(S, t->right);
		if (t->left)
			push(S, t->left);
	}
	destroy_stack(S);
}

// 中序遍历的非递归实现
void in_order2(BinTree T)
{
	if (T == NULL)
		return;

	Stack S = create_stack(MAX_SIZE);
	BinTree t = T;

	// 初始化: 从根节点开始, 向左推进, 把沿途的节点压栈
	while (t)
	{
		push(S, t);
		t = t->left;
	}

	// 访问栈顶元素t; 访问结束后从t的右子树开始, 向左边推进, 把沿途的节点压栈
	while (!stack_empty(S))
	{
		t = pop(S);
		printf("%d ", t->data);

		t = t->right;
		while (t)
		{
			push(S, t);
			t = t->left;
		}
	}

	destroy_stack(S);
}

int count_leaves(BinTree T)
{
	if (T == NULL) return 0;

	if (!T->left && !T->right)
		return 1;
	else
		return (count_leaves(T->left) + count_leaves(T->right));
}

int height(BinTree T)
{
	if (T == NULL) return 0;
	return max(height(T->left), height(T->right)) + 1;
}

// 思路:
// 高度 = 层数, 以层序遍历为框架; 需要记录每层的节点数, 当把一层的
// 节点处理完后, level++
int height2(BinTree T)
{
	Queue Q;
	int level = 0;

	Q = create_queue(MAX_SIZE);
	enqueue(Q, T);
	while (!queue_empty(Q))
	{
		int size = queue_size(Q); // 当前层有多少节点?
		while (size-- > 0)
		{
			BinTree t = dequeue(Q);
			if (t->left)
				enqueue(Q, t->left);
			if (t->right)
				enqueue(Q, t->right);
		}
		level++;
	}
	return level;
}

// 计算二叉树的根节点左右子树相隔最远的叶子节点之间的距离
// 定义"距离": 把树看成无向图, 连通两个节点之间的边数称为这两个节点之间的距离
// 思路:
// 分别求出根节点处左右子树中最深的2个节点的深度, 二者的深度之和即为二者之间的距离
// PS. 最深的节点一定是叶子节点; 最深节点的深度 = 树的深度 = 树的高度
int max_distance(BinTree T)
{
	return height(T->left) + height(T->right);
}

/////////////////////// Test ///////////////////////

// test for `exchange1'
void test1()
{
	BinTree T;
	int pre[] = { 4, 7, 5, 6, 8, 1, 2, 3 };
	int in[] = { 5, 7, 8, 6, 4, 2, 3, 1 };

	T = build_tree(pre, 0, _countof(pre) - 1,
		in, 0, _countof(in) - 1);
	exchange1(T);
	pre_order(T);
	printf("\n");
	in_order(T);
	destroy_tree(T);
}

// test for `exchange2'
void test2()
{
	BinTree T;
	int pre[] = { 4, 7, 5, 6, 8, 1, 2, 3 };
	int in[] = { 5, 7, 8, 6, 4, 2, 3, 1 };

	T = build_tree(pre, 0, _countof(pre) - 1,
		in, 0, _countof(in) - 1);
	exchange2(T);
	printf("\n");
	pre_order(T);
	printf("\n");
	in_order(T);
	printf("\n");
	destroy_tree(T);
}

// test for `pre_order2'
void test3()
{
	BinTree T;
	int pre[] = { 4, 7, 5, 6, 8, 1, 2, 3 };
	int in[] = { 5, 7, 8, 6, 4, 2, 3, 1 };

	T = build_tree(pre, 0, _countof(pre) - 1,
		in, 0, _countof(in) - 1);
	pre_order2(T);
	destroy_tree(T);
}

// test for `in_order2'
void test4()
{
	BinTree T;
	int pre[] = { 4, 7, 5, 6, 8, 1, 2, 3 };
	int in[] = { 5, 7, 8, 6, 4, 2, 3, 1 };

	T = build_tree(pre, 0, _countof(pre) - 1,
		in, 0, _countof(in) - 1);
	in_order2(T);
	destroy_tree(T);
}

// test for BSTree
void test5()
{
	BSTree T = NULL;
	int x[] = { 45, 14, 11, 52, 63, 32, 56, 24 };
	for (int i = 0; i < _countof(x); i++)
		T = insert_bstree(T, x[i]);

	delete_bstree(T, 52);
	pre_order(T);
	printf("\n");
	in_order(T);
	destroy_tree(T);
}

// test for `count_leaves', `height' and `height2'
void test6()
{
	BSTree T = NULL;
	int x[] = { 45, 14, 11, 52, 63, 32, 56, 24 };
	for (int i = 0; i < _countof(x); i++)
		T = insert_bstree(T, x[i]);

	printf("leaves: %d\nheight: %d, %d\n",
		count_leaves(T), height(T), height2(T));
	destroy_tree(T);
}

// test for `max_distance'
void test7()
{
	BSTree T = NULL;
	int x[] = { 45, 14, 11, 52, 63, 32, 56, 24, 54 };
	for (int i = 0; i < _countof(x); i++)
		T = insert_bstree(T, x[i]);

	printf("%d\n", max_distance(T));
	destroy_tree(T);
}


int main()
{
	test4();
}

