// abstract class max priority queue
// all methods are pure virtual functions

#pragma once

template <class T>
class MaxPriorityQueue
{
public:
	virtual ~MaxPriorityQueue() {}

	// return true iff queue is empty
	virtual bool empty() const = 0;

	// return number of elements in queue
	virtual int size() const = 0;

	// return reference to the max element
	virtual const T& top() = 0;

	// remove the top element
	virtual void pop() = 0;

	// add theElement to the queue
	virtual void push(const T& element) = 0;
};