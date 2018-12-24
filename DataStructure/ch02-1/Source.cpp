#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _BiStack {
	int *data;
	int size;
	int top1;
	int top2;
} *BiStack;

BiStack CreateBiStack(int size)
{
	BiStack stack = (BiStack)malloc(sizeof (struct _BiStack));
	stack->data = (int*)malloc(sizeof(int) * size);
	memset(stack->data, 0, sizeof(int) * size);
	stack->size = size;
	stack->top1 = -1;
	stack->top2 = size;

	return stack;
}

void Push(BiStack stack, int type, int v)
{
	if (stack->top1 == stack->top2 - 1)
	{
		printf("Overflow\n");
		return;
	}

	if (type == 1)
		stack->data[++stack->top1] = v;
	else if (type == 2)
		stack->data[--stack->top2] = v;
	else
		printf("Push Error\n");
}

int Pop(BiStack stack, int type)
{
	if (type == 1 && stack->top1 == -1)
	{
		printf("Empty-1\n");
		return -1;
	}
	if (type == 2 && stack->top2 == stack->size)
	{
		printf("Empty-2\n");
		return -1;
	}


	if (type == 1)
		return stack->data[stack->top1--];
	else if (type == 2)
		return stack->data[stack->top2++];
	else
	{
		printf("Pop Error\n");
		return -1;
	}
}

void FreeStack(BiStack stack)
{
	free(stack->data);
	free(stack);
}

void DispStack(BiStack stack)
{
	for (int i = 0; i < stack->size; i++)
	{
		printf("%d ", stack->data[i]);
	}
	printf("\n");
}

int main()
{
	BiStack stack = CreateBiStack(10);
	Push(stack, 1, 6);
	Push(stack, 1, 4);
	Push(stack, 1, 7);
	Push(stack, 2, 12);
	Push(stack, 2, 5);
	Push(stack, 2, 2);
	Push(stack, 2, 10);
	Push(stack, 2, 15);
	Push(stack, 2, 20);
	Push(stack, 2, 8);
	Push(stack, 2, 18);
	
	DispStack(stack);

	for (int i = 0; i < stack->size; i++)
	{
		printf("%d, ", Pop(stack, 1));
		printf("%d\n", Pop(stack, 2));
	}

	FreeStack(stack);

}