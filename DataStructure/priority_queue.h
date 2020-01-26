#include <cstdlib>
#include <iostream>

template<class T, class Compare>
class priority_queue {
public:
	priority_queue(int capacity, const T& min_elem);
	priority_queue(T* elements, int n, const T& min_elem);
	~priority_queue();

	bool empty() { return size_ == 0; }
	bool full() { return size_ == capacity_; }

	T pop();
	void push(const T& x);

	void dbg_print() {
		for (int i = 1; i <= size_; i++) {
			std::cout << elements_[i] << " ";
		}
		std::cout << std::endl;
	}

private:
	void build_heap();
	void percolate_down(int pos);
	void percolate_up(int pos);

	T* elements_;
	Compare comp;
	int size_;
	int capacity_;
};

template<class T, class Compare>
priority_queue<T, Compare>::priority_queue(int capacity, const T& min_elem)
	: size_(0), capacity_(capacity) {
	elements_ = static_cast<T*>(malloc(sizeof(T)*(capacity + 1)));
	if (elements_ == nullptr) {
		exit(1);
	}
	elements_[0] = min_elem;
}

template<class T, class Compare>
priority_queue<T, Compare>::priority_queue(T* elements, int n, const T& min_elem)
	: size_(n), capacity_(n * 2) {
	elements_ = static_cast<T*>(malloc(sizeof(T)*(capacity_ + 1)));
	if (elements_ == nullptr) {
		exit(1);
	}
	elements_[0] = min_elem;
	for (int i = 1; i <= n; i++) {
		elements_[i] = elements[i - 1];
	}
	build_heap();
}

template<class T, class Compare>
priority_queue<T, Compare>::~priority_queue() {
	for (int i = 0; i <= size_; i++) {
		elements_[i].~T();
	}
	free(elements_);
}

template<class T, class Compare>
T priority_queue<T, Compare>::pop() {
	if (empty()) {
		std::cout << "pop() error: empty.\n";
		return elements_[0];
	}

	T x = elements_[1];
	elements_[1] = elements_[size_--];
	percolate_down(1);

	return x;
}

template<class T, class Compare>
void priority_queue<T, Compare>::push(const T& x) {
	if (full()) {
		std::cout << "push() error: full.\n";
		return;
	}
	elements_[++size_] = x;
	percolate_up(size_);
}

template<class T, class Compare>
void priority_queue<T, Compare>::percolate_down(int pos) {
	T x = elements_[pos];
	int i, child;
	for (i = pos; i * 2 <= size_; i = child) {
		child = i * 2;
		if (child < size_ &&
			comp(elements_[child + 1], elements_[child]) < 0) {
			++child;
		}
		if (comp(x, elements_[child]) > 0) {
			elements_[i] = elements_[child];
		} else {
			break;
		}
	}
	elements_[i] = x;
}

template<class T, class Compare>
void priority_queue<T, Compare>::percolate_up(int pos) {
	T x = elements_[pos];
	int i;
	for (i = pos; i > 0; i /= 2) {
		if (comp(x, elements_[i / 2]) < 0) { // 如果i/2==0, 那么x<elements_[0]为假([0]=MinData)
			elements_[i] = elements_[i / 2];
		} else {
			break;
		}
	}
	elements_[i] = x;
}

template<class T, class Compare>
void priority_queue<T, Compare>::build_heap() {
	for (int i = size_ / 2; i > 0; i--) {
		percolate_down(i);
	}
}
