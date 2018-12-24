#include <stdio.h>
#include <stdlib.h>
#include <queue>
using namespace std;

#define max(a,b) ((a>b)?a:b)

typedef struct _AvlTree* AvlTree;

struct _AvlTree {
	int data;
	AvlTree left;
	AvlTree right;
	int height;
};

int Height(AvlTree T)
{
	if (T == NULL)
		return -1;

	return T->height;
}

AvlTree SingleRotateWithLeft(AvlTree K)
//
//            5(K)                 3(K1)
//           /   \                /    \
//         3(K1)  6     ->       2      5(K)
//         / \                  /       / \
//        2   4                1       4   6
//       /
//      1
//
//           (K)                (K1)
//          /   \               /  \
//        (K1)   Z     ->      X   (K)
//        / \                      / \
//       X   Y                    Y   Z
//
//
{
	AvlTree K1;
	
	K1 = K->left;
	K->left = K1->right;
	K1->right = K;

	K->height = max(Height(K->left), Height(K->right)) + 1;
	K1->height = max(Height(K1->left), Height(K1->right)) + 1;

	return K1;
}

AvlTree SingleRotateWithRight(AvlTree K)
//
//        2(K)                      4(K1)
//       /   \                      /   \
//      1    4(K1)      ->        2(K)   5
//           / \                  / \     \
//          3   5                1   3     6
//               \
//                6
//
//        (K)                      (K1)
//       /   \                     /  \
//      X   (K1)       ->         (K)  Z
//          /  \                  / \
//         Y    Z                X   Y
//
{
	AvlTree K1;

	K1 = K->right;
	K->right = K1->left;
	K1->left = K;

	K->height = max(Height(K->left), Height(K->right)) + 1;
	K1->height = max(Height(K1->left), Height(K1->right)) + 1;

	return K1;
}

AvlTree DoubleRotateWithLeft(AvlTree K)
//
//          (K)                      (K2)
//         /   \                    /    \
//       (K1)   D        ->       (K1)   (K)
//       /  \                     /  \   / \
//      A   (K2)                 A    B C   D
//          /  \
//         B    C
//------------------------------------------------------
//                                          (K)
//                                         /   \
//           K1和K2之间，右单旋转 ->       (K2)  (D)
//                                       /  \
//                                     (K1)  C
//                                     /  \
//                                    A    B
//
//                                         (K2)
//                                        /    \
//           K和K2之间，左单旋转 ->       (K1)   (K)
//                                      /  \   /  \
//                                     A    B C    D
//
{
	// 不使用两次单旋转
	/*AvlTree K1, K2;
	K1 = K->left;
	K2 = K1->right;
	K->left = K2->right;
	K1->right = K2->left;
	K2->left = K1;
	K2->right = K;

	K1->height = max(Height(K1->left), Height(K1->right)) + 1;
	K->height = max(Height(K->left), Height(K->right)) + 1;
	K2->height = max(Height(K2->left), Height(K2->right)) + 1;

	return K2;*/

	// 使用两次单旋转
	K->left = SingleRotateWithRight(K->left);
	return SingleRotateWithLeft(K);

}

AvlTree DoubleRotateWithRight(AvlTree K)
//
//          (K)                          (K2)
//         /   \                        /    \
//        A    (K1)         ->        (K)   (K1)
//             /  \                   / \   /  \
//           (K2)  D                 A   B C    D
//           /  \
//          B    C
//-------------------------------------------------------
//
//                                      (K)
//       K1和K2之间，左单旋转 ->         /   \
//                                    A    (K2)
//                                         /  \
//                                        B   (K1)
//                                            /  \
//                                           C    D
//
//       K和K2之间，右单旋转 ->         (K2)
//                                    /   \
//                                  (K)   (K1)
//                                 /  \   /  \
//                                A    B C    D
//
{
	// 不使用两次单旋转
	/*AvlTree K1, K2;
	K1 = K->right;
	K2 = K1->left;
	K->right = K2->left;
	K1->left = K2->right;
	K2->left = K;
	K2->right = K1;

	K->height = max(Height(K->left), Height(K->right)) + 1;
	K1->height = max(Height(K1->left), Height(K1->right)) + 1;
	K2->height = max(Height(K2->left), Height(K2->right)) + 1;

	return K2;*/

	// 使用两次单旋转
	K->right = SingleRotateWithLeft(K->right);
	return SingleRotateWithRight(K);
}

AvlTree Insert(AvlTree T, int x)
{
	if (T == NULL)
	{
		T = (AvlTree)malloc(sizeof(struct _AvlTree));
		T->data = x;
		T->height = 0;
		T->left = T->right = NULL;
	}
	else if (x < T->data)
	{
		T->left = Insert(T->left, x);
		if (Height(T->left) - Height(T->right) == 2)
		{
			// 节点 T 的左右子树不平衡, 需要在 T 处进行旋转
			if (x < T->left->data)
			{
				// x 被插入到左子树的"外面"
				T = SingleRotateWithLeft(T);
			}
			else if (x > T->left->data)
			{
				// x 被插入到左子树的"里面"
				T = DoubleRotateWithLeft(T);
			}
		}
	}
	else if (x > T->data)
	{
		T->right = Insert(T->right, x);
		if (Height(T->right) - Height(T->left) == 2)
		{
			// 节点 T 的左右子树不平衡, 需要在 T 处进行旋转
			if (x > T->right->data)
			{
				// x 被插入到右子树的"外面"
				T = SingleRotateWithRight(T);
			}
			else if (x < T->right->data)
			{
				// x 被插入到右子树的"里面"
				T = DoubleRotateWithRight(T);
			}
		}
	}

	T->height = max(Height(T->left), Height(T->right)) + 1;
	return T;
}

void PreOrder(AvlTree T)
{
	if (T != NULL)
	{
		printf("%d ", T->data);
		PreOrder(T->left);
		PreOrder(T->right);
	}
}

void InOrder(AvlTree T)
{
	if (T != NULL)
	{
		InOrder(T->left);
		printf("%d ", T->data);
		InOrder(T->right);
	}
}

void LayerOrder(AvlTree T)
{
	queue<AvlTree> q;
	q.push(T);
	while (!q.empty())
	{
		AvlTree Tmp = q.front();
		q.pop();
		if (Tmp != NULL)
		{
			printf("%d ", Tmp->data);
			if (Tmp->left)
				q.push(Tmp->left);
			if (Tmp->right)
				q.push(Tmp->right);
		}
	}
}

void FreeAvlTree(AvlTree T)
{
	if (T != NULL)
	{
		FreeAvlTree(T->left);
		FreeAvlTree(T->right);
		free(T);
	}
}

int main()
{
	AvlTree T = NULL;
	int data[16] = { 3, 2, 1, 4, 5, 6, 7, 16, 15, 14, 13, 12, 11, 10, 8, 9 };
	int i;

	for (i = 0; i < 16; i++)
		T = Insert(T, data[i]);

	printf("Layer: ");
	LayerOrder(T);
	printf("\n");

	printf("Pre: ");
	PreOrder(T);
	printf("\n");

	printf("In: ");
	InOrder(T);
	printf("\n");

	FreeAvlTree(T);
}