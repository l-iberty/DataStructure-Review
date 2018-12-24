#include "list.h"
#include <stdio.h>
#include <stdlib.h>

// 并集 不含重复元素
List list_union(List L1, List L2)
{
	List p = L1, p1 = L1->next, p2 = L2->next;

	while (p1 && p2)
	{
		if (p1->data < p2->data)
		{
			p->next = p1;
			p = p1;
			p1 = p1->next;
		}
		else if (p1->data > p2->data)
		{
			p->next = p2;
			p = p2;
			p2 = p2->next;
		}
		else
		{
			p->next = p1;
			p = p1;
			// 推进 p1, p2, 越过与 p->data 相等的元素
			while (p1 && p1->data == p->data)
				p1 = p1->next;
			while (p2 && p2->data == p->data)
				p2 = p2->next;
		}
	}
	if (p1 == NULL)
		p->next = p2;
	else
		p->next = p1;

	return L1;
}

// 交集 不含重复元素
List list_intersect(List L1, List L2)
{
	List L = create_list();
	List p = L, p1 = L1->next, p2 = L2->next;

	while (p1 && p2)
	{
		if (p1->data < p2->data)
		{
			p1 = p1->next;
		}
		else if (p1->data > p2->data)
		{
			p2 = p2->next;
		}
		else
		{
			p->next = p1;
			p = p1;
			// 推进 p1, p2, 越过与 p->data 相等的元素
			while (p1 && p1->data == p->data)
				p1 = p1->next;
			while (p2 && p2->data == p->data)
				p2 = p2->next;

		}
	}
	return L;
}

// 插入排序
List list_insert_sort(List L)
{
	List p, cur, next;
	p = L->next;
	L->next = NULL;
	while (p != NULL)
	{
		for (cur = L; cur->next; cur = cur->next)
		{
			if (p->data < cur->next->data)
				break;
		}
		next = p->next;
		p->next = cur->next;
		cur->next = p;
		p = next;
	}
	return L;
}

// 选择排序（需要前驱指针）
List list_select_sort(List L)
{
	List L1, tail, p, min, min_prev;

	L1 = create_list(); // 排序结果存入新表 L1
	tail = L1; // L1 的尾指针

	while (L->next != NULL)
	{
		min = L->next;
		for (p = L->next; p; p = p->next)
		{
			if (p->data < min->data)
				min = p;
		}
		// 在旧表中删除 min
		min_prev = find_prev(L, min->data);
		min_prev->next = min->next;
		// 将 min 链接到新表的末尾
		min->next = tail->next;
		tail->next = min;
		tail = tail->next;
	}
	return L1;
}

int main()
{
	/*int x1[] = { 6, 9, 9, 10, 13, 18 };
	int x2[] = { 1, 2, 5, 6, 6, 9, 9, 12, 15, 18, 18, 18, 20 };
	List L1 = init_list(x1, _countof(x1));
	List L2 = init_list(x2, _countof(x2));
	List L = list_intersect(L1, L2);
	print_list(L);*/

	int x[] = { 12, 14, 7, 9, 23, 18, 15, 15, 19, 4, 67 };
	List L = init_list(x, _countof(x));
	//list_insert_sort(L);
	L = list_select_sort(L);
	print_list(L);
}