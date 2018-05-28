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
	const T& top() override; // ���ظ��ڵ�
	void pop() override;     // ɾ�����ڵ�
	void push(const T& element) override; // ��ӽڵ�

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
	// ɾ�����ڵ�
	// �����Ϊ�գ��׳��쳣
	if (heap_size == 0)
	{
		throw EmptyHeapException();
	}

	// ɾ�����Ԫ��
	heap[1].~T();

	// ɾ�����һ��Ԫ�أ�Ȼ�����½���
	T last_element = heap[heap_size--];

	auto current_node = 1,
		child_node = 2;

	// �Ӹ���ʼ��Ϊ���һ��Ԫ��Ѱ��λ��
	while (child_node <= heap_size)
	{
		// �ҵ�current_node����һ������
		if (child_node < heap_size && heap[child_node] < heap[child_node + 1])
		{
			child_node++;
		}

		// �ҵ����һ��Ԫ���Ƿ���Է��ڵ�ǰλ��
		if (last_element >= heap[child_node])
		{
			break;
		}

		// �����ԵĻ����Ѻ��������ƶ�
		heap[current_node] = heap[child_node];
		// �����ƶ�һ��Ѱ��λ��
		current_node = child_node;
		child_node *= 2;
	}
	// �ƶ����һ��Ԫ��
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

	// ������β����ӽڵ㣬�Ӹýڵ㵽���ڵ㣬����ð�ݣ�С�Ľڵ������ƶ�
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
{ // ������heap[1:size]�н������
	// ����ռ䲻�㣬���·���
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

	// �ѻ�, �����һ�����к��ӵĽڵ㿪ʼ
	for (auto root = heap_size / 2; root >= 1; root--)
	{
		T root_element = this->heap[root];

		// ΪԪ��root_elementѰ��λ��
		// ����child_node�ĸ��ڵ���Ԫ��root_element��λ��
		auto child_node = 2 * root;
		while (child_node <= heap_size)
		{
			// heap[child_node]Ӧ�����ֵ��������
			if (child_node < heap_size && this->heap[child_node] < this->heap[child_node + 1])
			{
				child_node++;
			}

			// �Ƿ���԰�Ԫ�� root_element ����heap[child_node / 2]
			if (root_element >= this->heap[child_node])
			{
				break;
			}
			else
			{ 
				// �Ѻ���������
				this->heap[child_node / 2] = this->heap[child_node];
				// �ƶ�����һ��
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