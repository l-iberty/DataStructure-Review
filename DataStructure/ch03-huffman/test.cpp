#include "huffman.h"
#include "binheap.h"

#define N 15

int main()
{
	char Elements[N] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i',
		'j', 'k', 'l', 'm', 'n', 'o' };
	double Weights1[N] = {
		8.167, // a (14)
		1.492, // b (3)
		2.782, // c (7)
		4.253, // d (9)
		12.702, // e (15)
		2.228, // f (5)
		2.105, // g (4)
		6.094, // h (10)
		6.966, // i (12)
		0.153, // j (1)
		0.722, // k (2)
		4.025, // l (8)
		2.406, // m (6)
		6.749, // n (11)
		7.507 // o (13)
		// 频度排序: j k b g f m c l d h n i o a e
	};


	// 以 Weight2 构造的 huffman 树形如 huffman2.vsdx
	double Weights2[N] = {
		14, // a (14)
		3, // b (3)
		7, // c (7)
		9, // d (9)
		15, // e (15)
		5, // f (5)
		4, // g (4)
		10, // h (10)
		12, // i (12)
		1, // j (1)
		2, // k (2)
		8, // l (8)
		6, // m (6)
		11, // n (11)
		13, // o (13)
		// 频度排序: j k b g f m c l d h n i o a e
	};

	int i;
	HuffmanTree T;
	HuffmanTree *Leaves;
	std::stack<char> code;

	T = CreateHuffmanTree(Elements, Weights2, N, &Leaves);
	for (i = 1; i <= N; i++)
	{
		printf("%s -- ", Leaves[i]->Element);

		GetCode(Leaves[i], code);
		while (!code.empty())
		{
			printf("%d", code.top());
			code.pop();
		}
		printf("\n");
	}

	LayerWalker(T);
	printf("\n");

	FreeHuffmanTree(T);
	free(Leaves[0]);
	free(Leaves);
}