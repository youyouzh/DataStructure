#pragma once

template <class T>
class ChainNode
{
public:
	// data members
	T element;
	// link point
	ChainNode<T> *next;

	// methods
	ChainNode() {}

	// construct
	explicit ChainNode(const T& element)
	{
		this->element = element;
	}

	// copy construct
	ChainNode(const T& element, ChainNode<T>* next)
	{
		this->element = element;
		this->next = next;
	}
};