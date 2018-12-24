#ifndef BIN_TREE_H
#define BIN_TREE_H
#include <stdio.h>
#include <stdlib.h>

#define max(a,b) ((a>b)?a:b)
#define abs(a) ((a>0)?a:(-(a)))

typedef struct _BinTree *BinTree;
typedef struct _BinTree *BSTree;

struct _BinTree
{
	int data;
	BinTree left;
	BinTree right;
};

/////////////////////// BinTree ///////////////////////

BinTree build_tree(int pre[], int pre_from, int pre_to,
	int in[], int in_from, int in_to);

void pre_order(BinTree T);
void in_order(BinTree T);
void post_order(BinTree T);
void destroy_tree(BinTree T);

#endif
