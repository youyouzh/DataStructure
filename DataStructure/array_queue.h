// circular array implementation of a queue
// derives from the ADT queue

#pragma once

#include <sstream>
#include "queue.h"
#include "u_exception.h"

template <class T>
class ArrayQueue : public Queue<T>
{
public:
	explicit ArrayQueue(int capacity = 10);

	~ArrayQueue() override;
	bool empty() const override;
	int size() const override;
	T& front() override;
	T& back() override;
	void pop() override;
	void push(const T& element) override;

private:
	// position of the front element
	int the_front;
	// position of the back element
	int the_back;
	// queue length
	int array_length;
	// element array
	T* queue;
};

template <class T>
ArrayQueue<T>::ArrayQueue(int capacity)
{
	if (capacity < 0)
	{
		std::ostringstream s;
		s << "Initial capacity = " << capacity << " Must be > 0";
		throw IllegalParameterValueException();
	}
	array_length = capacity;
	queue = new T[array_length];
	the_back = the_front = 0;
}

template <class T>
ArrayQueue<T>::~ArrayQueue()
{
	delete[] queue;
}

template <class T>
bool ArrayQueue<T>::empty() const
{
	return the_back == the_front;
}

template <class T>
int ArrayQueue<T>::size() const
{
	return (the_back - the_front + array_length) % array_length;
}

template <class T>
T& ArrayQueue<T>::front()
{
	if (the_front == the_back)
	{
		throw QueueEmptyException();
	}
	return queue[(the_front + 1) % array_length];
}

template <class T>
T& ArrayQueue<T>::back()
{
	if (the_front == the_back)
	{
		throw QueueEmptyException();
	}
	return  queue[the_back];
}

template <class T>
void ArrayQueue<T>::pop()
{
	if (the_front == the_back)
	{
		throw QueueEmptyException();
	}
	// remove the front element
	the_front = (the_front + 1) % array_length;
	queue[the_front].~T();
}

template <class T>
void ArrayQueue<T>::push(const T& element)
{
	// increase array length if necessary
	if ((the_back + 1) % array_length == the_front)
	{
		// double array length, allocate a new array
		T* new_queue = new T[2 * array_length];

		// copy elements into new array
		auto start = (the_front + 1) % array_length;
		auto position = 0;
		if (start < 2)
		{ // if no wraps around
			for (auto i = start; i < start + array_length - 1; i++)
			{
				new_queue[position++] = queue[i];
			}
		}
		else
		{ // queue wraps around
			position = 0;
			// back part
			for (auto i = start; i < array_length - 1; i++)
			{
				new_queue[position++] = queue[i];
			}
			// front part
			for (auto i = 0; i < the_back + 1; i++)
			{
				new_queue[position++] = queue[i];
			}
		}

		// switdh th new queue and set the front and the back
		the_front = 2 * array_length - 1;
		the_back = array_length - 2;
		array_length *= 2;
		queue = new_queue;
	}

	// insert new element
	the_back = (the_back + 1) % array_length;
	queue[the_back] = element;
}
