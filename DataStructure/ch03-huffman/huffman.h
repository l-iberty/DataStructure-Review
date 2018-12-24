#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <stack>

typedef struct _HuffmanTree *HuffmanTree;

#define BUFSIZE 4
#define MAKE_STRING(s,c) s[0] = c; s[1] = 0

struct _HuffmanTree
{
	char Element[BUFSIZE];
	double Weight;
	HuffmanTree Parent;
	HuffmanTree Left;
	HuffmanTree Right;
};

HuffmanTree CreateHuffmanTree(char *Elements, double *Weights, int N, HuffmanTree **LeafList);
void GetCode(HuffmanTree K, std::stack<char> &code);
void LayerWalker(HuffmanTree T);
void FreeHuffmanTree(HuffmanTree T);

#endif // HUFFMAN_H
