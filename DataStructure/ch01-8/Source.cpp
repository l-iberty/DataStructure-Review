#include <stdio.h>
#include <stdlib.h>

typedef struct _ListNode* ListNode;

struct _ListNode {
	int data;
	ListNode next;
};

ListNode CreateList()
{
	ListNode node = (ListNode)malloc(sizeof(struct _ListNode));
	node->data = 0;
	node->next = node;
	return node;
}


void DispList(ListNode head)
{
	ListNode current;

	current = head->next;
	while (current != head)
	{
		printf("%d ", current->data);
		current = current->next;
	}
	printf("\n");
}

void Insert(ListNode head, int data)
{
	ListNode node = (ListNode)malloc(sizeof(struct _ListNode));
	if (node != NULL)
	{
		node->data = data;
		node->next = head->next;
		head->next = node;
	}
}

/**
 * ���� n �Ľڵ㱻���
 * ��ͷ�ڵ���, ��Ч�ڵ㹲�� num ��
 */
void J(ListNode head, int n, int num)
{
	int i;
	int count;
	ListNode tail, current;

	/* �Ƴ�ͷ�ڵ� */
	tail = head->next;
	while (tail->next != head)
	{
		tail = tail->next;
	}
	tail->next = head->next;
	free(head);

	i = 0;
	count = 0;
	current = tail->next;
	while (count < num)
	{
		/* �� data == 0, ˵���ýڵ��Ѿ������ */
		if (current->data != 0)
		{
			if (++i == n)
			{
				printf("%d ", current->data);
				current->data = 0;
				i = 0;
				count++;
			}
		}
		current = current->next;
	}
}

int main()
{
	int i;
	ListNode list = CreateList();

	for (i = 10; i > 0; i--)
		Insert(list, i);

	DispList(list);
	
	printf("Begin: ");
	J(list, 3, 10);
	printf("\nEnd\n");
}