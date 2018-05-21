// abstract class stack
// abstract data type specification for stack data structure
// all methods are pure virtual functions

#pragma once

template <class T>
class Stack
{
public:
	virtual ~Stack() {}
	// return true if stack is empty
	virtual bool empty() const = 0;

	// return number of elements in stack
	virtual int size() const = 0;

	// return reference to the top element
	virtual T& top() = 0;

	// remove the top element
	virtual void pop() = 0;

	// insert theElement at the top of the stack
	virtual void push(const T& element) = 0;
};