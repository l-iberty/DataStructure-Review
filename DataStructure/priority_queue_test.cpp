#include <iostream>
#include <deque>
#include <cstdint>
#include "heap.h"


template<class T>
struct greater {
	int operator()(const T& x, const T& y) {
		if (x < y) {
			return -1;
		} else if (x > y) {
			return 1;
		} else {
			return 0;
		}
	}
};

template<class T>
struct less {
	int operator()(const T& x, const T& y) {
		if (x < y) {
			return 1;
		} else if (x > y) {
			return -1;
		} else {
			return 0;
		}
	}
};

int main() {
	const int min_elem = INT_MIN;
	int elems[] = { 65, 68, 31, 21, 49, 29, 30, 25, 12, 17, 37 };
	priority_queue<int, less<int>> heap(elems, sizeof(elems) / sizeof(elems[0]), min_elem);
	heap.push(15);
	heap.push(5);
	heap.push(13);
	heap.dbg_print();

	while (!heap.empty()) {
		std::cout << heap.pop() << " ";
	}
	std::cout << std::endl;
}
