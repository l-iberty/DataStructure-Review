#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <iostream>

#define LeftChild(i) (i * 2)


typedef int(*CMPFUNC)(void *x, void *y);

template<class T, CMPFUNC compare>
class PriorityQueue
{
private:
	T *mElements;
	int mCapacity;
	int mSize;
private:
	void PercolateDown(int Index);
	void PercolateUp(int Index);
	void BuildHeap();
public:
	PriorityQueue(int MaxElements, T MinData);
	PriorityQueue(T *Elements, int Size, T MinData);
	~PriorityQueue();
	void Insert(T X);
	T DeleteMin();
	T FindMin();
	bool IsEmpty();
	bool IsFull();
	int GetSize();
};


////////////////////////////////////////////////////////////////////////


template<class T, CMPFUNC compare>
PriorityQueue<T, compare>::PriorityQueue(int MaxElements, T MinData)
{
	mElements = new T[MaxElements + 1];
	mElements[0] = MinData;
	mCapacity = MaxElements;
	mSize = 0;
}

template<class T, CMPFUNC compare>
PriorityQueue<T, compare>::PriorityQueue(T *Elements, int Size, T MinData)
{
	mElements = new T[Size + 1];
	mElements[0] = MinData;
	mCapacity = Size;
	mSize = Size;

	for (int i = 1; i <= Size; i++)
		mElements[i] = Elements[i - 1];

	BuildHeap();
}

template<class T, CMPFUNC compare>
PriorityQueue<T, compare>::~PriorityQueue()
{
	delete[] mElements;
}

template<class T, CMPFUNC compare>
void PriorityQueue<T, compare>::PercolateDown(int Index)
{
	int i, Child;
	T Temp;

	Temp = mElements[Index];
	for (i = Index; i * 2 <= mSize; i = Child)
	{
		// Find smaller child.
		Child = LeftChild(i);
		if (Child < mSize &&
			compare((T)mElements[Child + 1], (T)mElements[Child]) < 0)
		{
			Child++;
		}

		if (compare((T)Temp, (T)mElements[Child]) > 0)
			mElements[i] = mElements[Child];
		else
			break;
	}
	mElements[i] = Temp;
}

template<class T, CMPFUNC compare>
void PriorityQueue<T, compare>::PercolateUp(int Index)
{
	int i;
	T Temp;

	Temp = mElements[Index];
	for (i = Index; i > 0; i /= 2)
	{
		if (compare((T)Temp, (T)mElements[i / 2]) < 0)
			mElements[i] = mElements[i / 2];
		else
			break;
	}
	mElements[i] = Temp;
}

template<class T, CMPFUNC compare>
void PriorityQueue<T, compare>::BuildHeap()
{
	for (int i = mSize / 2; i > 0; i--)
		PercolateDown(i);
}

template<class T, CMPFUNC compare>
void PriorityQueue<T, compare>::Insert(T X)
{
	if (IsFull())
	{
		std::cout << "Priority queue is full." << std::endl;
		return;
	}

	mElements[++mSize] = X;
	PercolateUp(mSize);
}

template<class T, CMPFUNC compare>
T PriorityQueue<T, compare>::DeleteMin()
{
	int i, Child;
	T MinElement, LastElement;

	if (IsEmpty())
	{
		std::cout << "Priority queue is empty.\n";
		return mElements[0];
	}

	MinElement = mElements[1];
	LastElement = mElements[mSize--];

	for (i = 1; i * 2 <= mSize; i = Child)
	{
		// Find smaller child.
		Child = LeftChild(i);
		if (Child < mSize &&
			compare((T)mElements[Child + 1], (T)mElements[Child]) < 0)
		{
			Child++;
		}

		if (compare((T)mElements[Child], (T)LastElement) < 0)
			mElements[i] = mElements[Child];
		else
			break;
	}
	mElements[i] = LastElement;

	return MinElement;
}

template<class T, CMPFUNC compare>
T PriorityQueue<T, compare>::FindMin()
{
	if (IsEmpty())
	{
		std::cout << "Priority queue is empty." << std::endl;
		return mElements[0];
	}
	return mElements[1];
}

template<class T, CMPFUNC compare>
bool PriorityQueue<T, compare>::IsEmpty()
{
	return (mSize == 0);
}

template<class T, CMPFUNC compare>
bool PriorityQueue<T, compare>::IsFull()
{
	return (mSize == mCapacity);
}

template<class T, CMPFUNC compare>
int PriorityQueue<T, compare>::GetSize()
{
	return mSize;
}


#endif // PRIORITY_QUEUE_H
