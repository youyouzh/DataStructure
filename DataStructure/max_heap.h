// heap implementation of a max priority queue
// derives from the ADT maxPriorityQueue

#pragma once

#include "max_priority_queue.h"
#include "u_exception.h"
#include "helper.h"
#include <sstream>

template <class T>
class MaxHeap : public MaxPriorityQueue<T>
{
public:
	explicit MaxHeap(int capacity = 10);
	~MaxHeap();

	bool empty() const override;
	int size() const override;
	const T& top() override; // 返回父节点
	void pop() override;     // 删除最大节点
	void push(const T& element) override; // 添加节点

	void initialize(T *heap, int size);
	void deactivate_array();
	void output(std::ostream& out) const;

	T* get_heap() const;

private:
	// number of elements in queue
	int heap_size;
	// queue capacity + 1
	int array_length;
	// element array
	T *heap;
};

template <class T>
MaxHeap<T>::MaxHeap(int capacity)
{
	if (capacity < 0)
	{
		std::ostringstream s;
		s << "Initial capacity = " << capacity << " Must be > 0";
		throw IllegalParameterValueException(s.str());
	}

	array_length = capacity + 1;
	heap = new T[array_length];
	heap_size = 0;
}

template <class T>
MaxHeap<T>::~MaxHeap()
{
	delete[] heap;
}

template <class T>
bool MaxHeap<T>::empty() const
{
	return heap_size == 0;
}

template <class T>
int MaxHeap<T>::size() const
{
	return heap_size;
}

template <class T>
const T& MaxHeap<T>::top()
{
	if (heap_size == 0)
	{
		throw EmptyHeapException();
	}
	return heap[1];
}

template <class T>
void MaxHeap<T>::pop()
{
	// 删除最大节点
	// 如果堆为空，抛出异常
	if (heap_size == 0)
	{
		throw EmptyHeapException();
	}

	// 删除最大元素
	heap[1].~T();

	// 删除最后一个元素，然后重新建堆
	T last_element = heap[heap_size--];

	auto current_node = 1,
		child_node = 2;

	// 从根开始，为最后一个元素寻找位置
	while (child_node <= heap_size)
	{
		// 找到current_node最大的一个儿子
		if (child_node < heap_size && heap[child_node] < heap[child_node + 1])
		{
			child_node++;
		}

		// 找到最后一个元素是否可以放在当前位置
		if (last_element >= heap[child_node])
		{
			break;
		}

		// 不可以的话，把孩子向上移动
		heap[current_node] = heap[child_node];
		// 向下移动一层寻找位置
		current_node = child_node;
		child_node *= 2;
	}
	// 移动最后一个元素
	heap[current_node] = last_element;
}

template <class T>
void MaxHeap<T>::push(const T& element)
{ // add element to heap
    // increase array length if necessary
	if (heap_size == array_length - 1)
	{
		// double array length
		change_lenghth_1_d(heap, array_length, array_length * 2);
		array_length *= 2;
	}

	// 首先在尾部添加节点，从该节点到父节点，依次冒泡，小的节点往下移动
	// find place for element
	// current node starts at new leaf
	auto current_node = ++heap_size;
	// move up tree
	while (current_node != 1 && heap[current_node / 2] < element)
	{
		// move element down
		heap[current_node] = heap[current_node / 2];
		// move to parent
		current_node /= 2;
	}
	heap[current_node] = element;
}

template <class T>
void MaxHeap<T>::initialize(T *heap, int size)
{ // 在数组heap[1:size]中建大根堆
	// 如果空间不足，重新分配
	if (size > array_length - 1)
	{
		delete[] this->heap;
		this->heap = new T[size + 1];
		array_length = size + 1;
	}
	this->heap_size = size;
	for (auto i = 0; i <= size; i++)
	{
		this->heap[i] = heap[i];
	}

	// 堆化, 从最后一个具有孩子的节点开始
	for (auto root = heap_size / 2; root >= 1; root--)
	{
		T root_element = this->heap[root];

		// 为元素root_element寻找位置
		// 孩子child_node的父节点是元素root_element的位置
		auto child_node = 2 * root;
		while (child_node <= heap_size)
		{
			// heap[child_node]应该是兄弟中最大者
			if (child_node < heap_size && this->heap[child_node] < this->heap[child_node + 1])
			{
				child_node++;
			}

			// 是否可以把元素 root_element 放在heap[child_node / 2]
			if (root_element >= this->heap[child_node])
			{
				break;
			}
			else
			{ 
				// 把孩子往上移
				this->heap[child_node / 2] = this->heap[child_node];
				// 移动到下一层
				child_node *= 2;
			}
		}
		this->heap[child_node / 2] = root_element;
	}
}

template <class T>
void MaxHeap<T>::deactivate_array()
{
	heap = nullptr;
	array_length = heap_size = 0;
}

template <class T>
T* MaxHeap<T>::get_heap() const
{
	return heap;
}


template <class T>
void MaxHeap<T>::output(std::ostream& out) const
{
	// Put the list into the stream out.
	for (auto i = 1; i < heap_size + 1; i++)
	{
		out << heap[i] << "  ";
	}
}

template <class T>
std::ostream& operator<<(std::ostream& out, const MaxHeap<T>& heap)
{
	heap.output(out);
	return out;
}