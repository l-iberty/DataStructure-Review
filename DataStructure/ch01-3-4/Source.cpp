#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode ListNode;
typedef int ElemType;

struct ListNode {
	ElemType data;
	ListNode *next;
};

ListNode* CreateList()
{
	ListNode *node = (ListNode*)malloc(sizeof(ListNode));
	node->data = 0;
	node->next = NULL;
	return node;
}

void FreeList(ListNode *head)
{
	ListNode *current, *next;

	current = head;
	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
}

void DispList(ListNode *head)
{
	ListNode *current;

	current = head->next;
	while (current != NULL)
	{
		printf("%d ", current->data);
		current = current->next;
	}
	printf("\n");
}

void Insert(ListNode *head, ElemType data)
{
	ListNode *node = (ListNode*)malloc(sizeof(ListNode));
	if (node != NULL)
	{
		node->data = data;
		node->next = head->next;
		head->next = node;
	}
}

void Reverse(ListNode *head)
{
	ListNode *current, *prev, *next;

	current = head->next;
	prev = NULL;
	next = current->next;

	while (next != NULL)
	{
		current->next = prev;
		prev = current;
		current = next;
		next = current->next;
	}
	current->next = prev;
	head->next = current;
}

ListNode* Union(ListNode *la, ListNode *lb)
{
	ListNode *pa, *pb, *current;

	pa = la->next;
	pb = lb->next;
	current = la;

	/* 接在 current 后面的是 pa 和 pb 中的较小者 */

	while (pa != NULL && pb != NULL)
	{
		if (pa->data < pb->data)
		{
			current->next = pa;
			current = pa;
			pa = pa->next;
		}
		else
		{
			current->next = pb;
			current = pb;
			pb = pb->next;
		}
	}
	if (pa != NULL)
	{
		current->next = pa;
	}
	else
	{
		current->next = pb;
	}
	return la;
}

int main()
{
	/* Reverse */

	printf("Reverse\n");

	ListNode *list = CreateList();
	for (int i = 0; i < 10; i++)
	{
		Insert(list, i + 1);
	}
	DispList(list);
	Reverse(list);
	DispList(list);
	FreeList(list);

	/* Union */

	printf("\nUnion\n");

	ListNode *la = CreateList();
	ListNode *lb = CreateList();

	Insert(la, 12);
	Insert(la, 9);
	Insert(la, 5);
	Insert(la, 4);
	Insert(lb, 10);
	Insert(lb, 9);
	Insert(lb, 3);
	Insert(lb, 2);
	Insert(la, 1);

	printf("la: ");
	DispList(la);

	printf("lb: ");
	DispList(lb);

	printf("\nUnion: ");
	ListNode *lc = Union(la, lb);
	DispList(lc);

	FreeList(lc);
}