// linked implementation of a stack
// derives from the ADT stack

#pragma once

#include "stack.h"
#include "chain_node.h"
#include "u_exception.h"

template <class T>
class LinkedStack : public Stack<T>
{
public:
	explicit LinkedStack(int capacity = 10);
	~LinkedStack();

	bool empty() const override;
	int size() const override;
	T& top() override;
	void pop() override;
	void push(const T& element) override;

private:
	// pointer to stack top
	ChainNode<T>* stack_top;
	// number of elements in stack
	int stack_size;
};

template <class T>
LinkedStack<T>::LinkedStack(int capacity)
{
	stack_top = nullptr;
	stack_size = 0;
}

template <class T>
LinkedStack<T>::~LinkedStack()
{
	while (stack_top != nullptr)
	{
		// delete top node
		ChainNode<T>* next_node = stack_top->next;
		delete stack_top;
		stack_top = next_node;
	}
}

template <class T>
bool LinkedStack<T>::empty() const
{
	return stack_size == 0;
}

template <class T>
int LinkedStack<T>::size() const
{
	return stack_size;
}

template <class T>
T& LinkedStack<T>::top()
{
	if (stack_size == 0)
	{
		throw StackEmptyException();
	}

	return stack_top->element;
}

template <class T>
void LinkedStack<T>::pop()
{
	if (stack_size == 0)
	{
		throw StackEmptyException();
	}
	ChainNode<T>* next_node = stack_top->next;
	delete stack_top;
	stack_top = next_node;
	
	stack_size--;
}

template <class T>
void LinkedStack<T>::push(const T& element)
{
	stack_top = new ChainNode<T>(element, stack_top);
	stack_size++;
}
