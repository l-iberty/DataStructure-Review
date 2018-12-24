#define _CRT_SECURE_NO_WARNINGS

// 820�㷨��--���Ա�
//
// < 820 >
//
// 2015-��.1
// ����������ϲ�. Ҫ�󣺲������ظ�Ԫ��
// Source.cpp ʵ����˳���(����)���������֣�
// @see merge1()
// @see merge2()
//
// 2014-��.1
// ��������
// @see reverse_list()
//
// 2016-��.1
// @see adjust_array()
//
// 2011-��.3
// @see circle_list()
//
// < 408 >
//
// 2009-42
// �ҵ��������еĵ����� k ��Ԫ��
// @see find_Kth()
//
// 2010-42
// ����ѭ������
// @see rol()

#include <stdio.h>
#include <stdlib.h>

typedef struct _ArrayList *ArrayList;
typedef struct _List *List;
typedef struct _List *Position;

struct _ArrayList
{
	int len;
	int *data;
};

struct _List
{
	int data;
	List next;
};


/////////////////////// ArrayList /////////////////////// 

ArrayList init_arraylist(int *x, int len)
{
	ArrayList L = (ArrayList)malloc(sizeof(struct _ArrayList));
	L->data = (int*)malloc(len * sizeof(int));
	L->len = len;
	for (int i = 0; i < len; i++)
	{
		L->data[i] = x[i];
	}
	return L;
}

ArrayList create_arraylist(int len)
{
	ArrayList L = (ArrayList)malloc(sizeof(struct _ArrayList));
	L->data = (int*)malloc(len * sizeof(int));
	L->len = len;
	return L;
}

void destory_arraylist(ArrayList L)
{
	free(L->data);
	free(L);
}

void print_arraylist(ArrayList L)
{
	for (int i = 0; i < L->len; i++)
		printf("%d ", L->data[i]);
	printf("\n");
}

// ���ظ�Ԫ�ض�ֻ���ֱ���һ��, ��ʹ����ͬһ����
ArrayList merge1(ArrayList L1, ArrayList L2)
{
	ArrayList L;
	int i, j, k;

	L = create_arraylist(L1->len + L2->len);
	i = j = k = 0;
	while (i < L1->len && j < L2->len)
	{
		if (L1->data[i] < L2->data[j])
		{
			if (L->data[k - 1] != L1->data[i]) // ������ǰԪ���� L ĩβԪ�ز�ͬ�ű�����
				L->data[k++] = L1->data[i++];
			else
				i++; // �����ظ�Ԫ��
		}
		else if (L2->data[j] < L1->data[i])
		{
			if (L->data[k - 1] != L2->data[j])
				L->data[k++] = L2->data[j++];
			else
				j++;
		}
		else
			i++; // Խ�� L1 �� L2 �е���ͬԪ��
	}
	while (i < L1->len)
	{
		if (L->data[k - 1] != L1->data[i])
			L->data[k++] = L1->data[i++];
		else
			i++;
	}
	while (j < L2->len)
	{
		if (L->data[k - 1] != L->data[j])
			L->data[k++] = L2->data[j++];
		else
			j++;
	}

	L->len = k;
	return L;
}

void adjust_array(int array[], int n)
{
	int i, j, m, t;

	if (n % 3 != 0)
	{
		fprintf(stderr, "error");
		return;
	}

	m = n / 3;

	// ���� A1, A2, ... , Am �� C1, C2, ... , Cm
	for (i = 0, j = 2 * m; i < m && j < n; i++, j++)
	{
		t = array[i];
		array[i] = array[j];
		array[j] = t;
	}

	// ���� B1, B2, ... , Bm
	int *pb = array + m;
	for (i = 0; i < m / 2; i++)
	{
		t = pb[i];
		pb[i] = pb[m - i];
		pb[m - i] = t;
	}
}

/////////////////////// List ///////////////////////

List create_list()
{
	List L = (List)malloc(sizeof(struct _List));
	L->next = NULL;
	return L;
}

void push_back(List L, int x)
{
	List Cell;
	Position p;

	Cell = (List)malloc(sizeof(struct _List));
	Cell->data = x;
	Cell->next = NULL;

	for (p = L; p->next; p = p->next);
	p->next = Cell;
}

List init_list(int *x, int len)
{
	List L;

	L = create_list();
	for (int i = 0; i < len; i++)
		push_back(L, x[i]);

	return L;
}

void print_list(List L)
{
	Position p;
	for (p = L->next; p; p = p->next)
		printf("%d ", p->data);
	printf("\n");
}

// ���ظ�Ԫ�ض�ֻ���ֱ���һ��, ��ʹ����ͬһ����
List merge2(List L1, List L2)
{
	Position p, p1, p2;
	p = L1;
	p1 = L1->next;
	p2 = L2->next;
	while (p1 && p2)
	{
		if (p1->data < p2->data)
		{
			if (p->data != p1->data) // ֻ�з��ظ�Ԫ�ر�����
			{
				p->next = p1;
				p = p1;
			}
			p1 = p1->next; // �����ظ�Ԫ��ʱֱ������
		}
		else if (p2->data < p1->data)
		{
			if (p->data != p2->data)
			{
				p->next = p2;
				p = p2;
			}
			p2 = p2->next;
		}
		else // Խ�� L1 �� L2 �е���ͬԪ��
		{
			p = p1;
			p1 = p1->next;
			p2 = p2->next;
		}
	}
	if (p1 == NULL)
		p->next = p2;
	else
		p->next = p1;
	return L1;
}

void reverse_list(List L)
{
	Position prev, current, next;

	prev = NULL;
	current = L->next;
	while (current)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	// ѭ�������� prev ָ��ĩβԪ��
	L->next = prev;
}

List circle_list(int x[], int n)
{
	int i;
	List L, node, p;
	L = create_list();
	p = L;
	for (i = 0; i < n; i++)
	{
		node = (List)malloc(sizeof(struct _List));
		node->data = x[i];
		node->next = p;
		p->next = node;
		p = p->next;
	}
	p->next = L->next;
	return L;
}

// �ҵ��������еĵ����� k ��Ԫ��
// ˼��: q �ӱ�ͷ��ʼ���ƶ����� k ��λ��, Ȼ�� p �ӱ�ͷ��ʼ�ƶ�, p �� q ͬ���ƽ�,
// ֱ�� q �ﵽ��β��, ��ʱ p ��ָ��Ϊ������ k ��Ԫ�ؽڵ�.
Position find_Kth(List L, int k)
{
	Position p, q;
	p = q = L->next;
	while (k-- > 0 && q != NULL)
	{
		q = q->next;
	}
	if (k > 0) // �����ڵ����� k ��Ԫ�ؽڵ�
		return NULL;

	while (q != NULL)
	{
		p = p->next;
		q = q->next;
	}
	return p;
}

// ����ѭ������
// @param ԭʼ���� r[]
// @param �����������е����� q[]
// @param ���г��� n
// @param ��λ�� p ( 0<p<n )
void rol(int r[], int q[], int n, int p)
{
	int i, j;
	int front, rear; // ��ͷ, ��β
	
	// �� r[] ��ǰ p ��Ԫ����� 
	front = rear = 0;
	for (i = 0; i < p; i++)
		q[rear++] = r[i];

	// �� r[] �ĺ� n-p ��Ԫ�ؿ�������ͷ
	for (j = 0; j < n - p; j++)
		r[j] = r[i++];

	// �����е�Ԫ�����γ���, ���ŵ� r[n-p ~ n-1]
	for (i = n - p; i < n; i++)
		r[i] = q[front++];
}

/////////////////////// Test ///////////////////////

// test for `merge1`
void test1()
{
	int a[] = { 3, 5, 7, 10, 10, 10, 14 };
	int b[] = { 4, 4, 7, 8, 13, 14, 16, 18, 20 };
	ArrayList L1 = init_arraylist(a, _countof(a));
	ArrayList L2 = init_arraylist(b, _countof(b));
	ArrayList L = merge1(L1, L2);
	print_arraylist(L);
}

// test for `merge2'
void test2()
{
	int a[] = { 3, 5, 7, 10, 10, 14 };
	int b[] = { 4, 4, 7, 8, 13, 14, 16, 18, 20 };
	List L1 = init_list(a, _countof(a));
	List L2 = init_list(b, _countof(b));
	List L = merge2(L1, L2);
	print_list(L);
}

// test for `reverse_list'
void test3()
{
	int a[] = { 3, 5, 7, 10, 10, 14 };
	List L = init_list(a, _countof(a));
	reverse_list(L);
	print_list(L);
}

// test for `adjust_array'
void test4()
{
	int a[15] =
	{
		0, 1, 2, 3, 4,
		10, 11, 12, 13, 14,
		5, 6, 7, 8, 9
	};
	adjust_array(a, _countof(a));

	for (int i = 0; i < _countof(a); i++)
		printf("%d ", a[i]);
	printf("\n");
}

// test for `circle_list'
void test5()
{
	int a[] = { 23, 56, 23, 1, 10 };
	List L = circle_list(a, _countof(a));
	print_list(L);
}

// test for `find_Kth'
void test6()
{
	int a[] = { 3, 5, 7, 0, 2, 10, 10, 14 };
	List L;
	int k;
	Position p;

	L = init_list(a, _countof(a));
	print_list(L);
	printf("k=? ");
	scanf("%d", &k);
	p = find_Kth(L, k);
	if (p != NULL)
		printf("%d\n", p->data);
	else
		printf("not found\n");
}

// test for `rol'
void test7()
{
	ArrayList L1, L2;
	int a[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	int p;

	L1 = init_arraylist(a, _countof(a));
	L2 = create_arraylist(_countof(a));

	print_arraylist(L1);
	printf("p=? ");
	scanf("%d", &p);
	rol(L1->data, L2->data, L1->len, p);
	print_arraylist(L1);
}

int main()
{
	test7();
}