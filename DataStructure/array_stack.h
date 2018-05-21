// array implementation of a stack
// derives from the ADT stack

#pragma once

#include <sstream>

#include "stack.h"
#include "helper.h"
#include "u_exception.h"

template <class T>
class ArrayStack : public Stack<T>
{
public:
	explicit ArrayStack(int capacity = 10);

	~ArrayStack() override;
	bool empty() const override;
	int size() const override;
	T& top() override;
	void pop() override;
	void push(const T& element) override;

private:
	// current top of stack
	int stack_top;
	// stack capacity
	int array_length;
	// element array
	T* stack;
};

template <class T>
ArrayStack<T>::ArrayStack(int capacity)
{
	if (capacity < 0)
	{
		std::ostringstream s;
		s << "Initial capacity = " << capacity << " Must be > 0";
		throw IllegalParameterValueException(s.str());
	}

	array_length = capacity;
	stack_top = -1;
	stack = new T[array_length];
}

template <class T>
ArrayStack<T>::~ArrayStack()
{
	delete[] stack;
}

template <class T>
bool ArrayStack<T>::empty() const
{
	return stack_top == -1;
}

template <class T>
int ArrayStack<T>::size() const
{
	return stack_top + 1;
}

template <class T>
T& ArrayStack<T>::top()
{
	// check whether stack is empty
	if (stack_top == -1)
	{
		throw StackEmptyException();
	}
	return stack[stack_top];
}

template <class T>
void ArrayStack<T>::pop()
{
	// check whether stack is empty
	if (stack_top == -1)
	{
		throw StackEmptyException();
	}
	stack[stack_top--].~T();
}

template <class T>
void ArrayStack<T>::push(const T& element)
{
	if (stack_top == array_length - 1)
	{
		// no space, double capacity
		change_lenghth_1_d(stack, array_length, array_length * 2);
		array_length *= 2;
	}
	// add at stack top
	stack[++stack_top] = element;
}
