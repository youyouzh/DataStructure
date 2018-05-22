// linked stack derived from chain
// derives from abstract class stack just to make sure
// all methods of the ADT are implemented

#pragma once

#include "chain.h"
#include "stack.h"
#include "u_exception.h"

template <class T>
class DerivedLinkedStack : private Chain<T>, 
	                       public Stack<T>
{
public:
	explicit DerivedLinkedStack(int capacity = 10);

	bool empty() const override;

	int size() const override;

	T& top() override;

	void pop() override;

	void push(const T& element) override;
};

template <class T>
DerivedLinkedStack<T>::DerivedLinkedStack(int capacity) : Chain<T>(capacity) { }

template <class T>
bool DerivedLinkedStack<T>::empty() const
{
	return Chain<T>::empty();
}

template <class T>
int DerivedLinkedStack<T>::size() const
{
	return Chain<T>::size();
}

template <class T>
T& DerivedLinkedStack<T>::top()
{
	if (Chain<T>::empty())
	{
		throw StackEmptyException();
	}
	// get the first element
	return Chain<T>::get(0);
}

template <class T>
void DerivedLinkedStack<T>::pop()
{
	if (Chain<T>::empty())
	{
		throw StackEmptyException();
	}
	// remove the first element
	Chain<T>::erase(0);
}

template <class T>
void DerivedLinkedStack<T>::push(const T& element)
{
	Chain<T>::insert(0, element);
}
