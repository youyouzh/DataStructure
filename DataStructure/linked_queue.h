// linked implementation of a queue
// derives from the ADT queue

#pragma once

#include <sstream>
#include "queue.h"
#include "chain_node.h"
#include "u_exception.h"

template <class T>
class LinkedQueue : public Queue<T>
{
public:
	explicit LinkedQueue(int capacity = 10);
	~LinkedQueue();

	bool empty() const override;
	int size() const override;
	T& front() override;
	T& back() override;
	void pop() override;
	void push(const T& element) override;

private:
	// pointer to queue front
	ChainNode<T>* queue_front;
	// pointer to queue back
	ChainNode<T>* queue_back;
	// number of elements in queue
	int queue_size;
};

template <class T>
LinkedQueue<T>::LinkedQueue(int capacity)
{
	queue_back = queue_front = nullptr;
	queue_size = 0;
}

template <class T>
LinkedQueue<T>::~LinkedQueue()
{
	while (queue_front != nullptr)
	{
		// delete front node
		ChainNode<T>* next_nodex = queue_front->next;
		delete queue_front;
		queue_front = next_nodex;
	}
}

template <class T>
bool LinkedQueue<T>::empty() const
{
	return queue_size == 0;
}

template <class T>
int LinkedQueue<T>::size() const
{
	return queue_size;
}

template <class T>
T& LinkedQueue<T>::front()
{
	if (queue_size == 0)
	{
		throw QueueEmptyException();
	}
	return queue_front->element;
}

template <class T>
T& LinkedQueue<T>::back()
{
	if (queue_size == 0)
	{
		throw QueueEmptyException();
	}
	return queue_back->element;
}

template <class T>
void LinkedQueue<T>::pop()
{
	if (queue_front == nullptr)
	{
		throw QueueEmptyException();
	}
	// Delete front element.
	ChainNode<T>* next_node = queue_front->next;
	delete queue_front;
	queue_front = next_node;
	queue_size--;
}

template <class T>
void LinkedQueue<T>::push(const T& element)
{
	// create node for new element
	ChainNode<T>* new_node = new ChainNode<T>(element, nullptr);

	// add new node to back of queue
	if (queue_size == 0)
	{ // queue empty
		queue_front = new_node;
	}
	else
	{ // queue not empty
		queue_back->next = new_node;
	}

	queue_back = new_node;
	queue_size++;
}
