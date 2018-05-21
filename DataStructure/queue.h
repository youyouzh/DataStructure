// abstract class queue
// abstract data type specification for queue data structure
// all methods are pure virtual functions

#pragma once

template <class T>
class Queue
{
public:
	virtual ~Queue() {}
	
	// return true iff queue is empty
	virtual bool empty() const = 0;

	// return number of elements in queue
	virtual int size() const = 0;

	// return reference to the front element
	virtual T& front() = 0;

	// return reference to the back element
	virtual T& back() = 0;

	// remove the front element
	virtual void pop() = 0;

	// add theElement at the back of the queue
	virtual void push(const T& element) = 0;
};