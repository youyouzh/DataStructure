// array stack derived from ArrayList
// derives from abstract class stack just to make sure
// all methods of the ADT are implemented

#pragma once

#include "array_list.h"
#include "stack.h"
#include "u_exception.h"

template <class T>
class DerivedArrayStack : private ArrayList<T>,
	               public Stack<T>
{
public:
	explicit DerivedArrayStack(int capacity);

	bool empty() const override;

	int size() const override;

	T& top() override;

	void pop() override;

	void push(const T& element) override;
};

template <class T>
DerivedArrayStack<T>::DerivedArrayStack(int capacity) : ArrayList<T>(capacity) { }

template <class T>
bool DerivedArrayStack<T>::empty() const
{
	return ArrayList<T>::empty();
}

template <class T>
int DerivedArrayStack<T>::size() const
{
	return ArrayList<T>::size();
}

template <class T>
T& DerivedArrayStack<T>::top()
{
	// check stack empty
	if (empty())
	{
		throw StackEmptyException();
	}
	// return the last element
	return ArrayList<T>::get(ArrayList<T>::size() - 1);
}

template <class T>
void DerivedArrayStack<T>::pop()
{
	if (empty())
	{
		throw StackEmptyException();
	}
	// erase the last element
	ArrayList<T>::erase(ArrayList<T>::size() - 1);
}

template <class T>
void DerivedArrayStack<T>::push(const T& element)
{
	// insert at the first index
	ArrayList<T>::insert(ArrayList<T>::size(), element);
}
