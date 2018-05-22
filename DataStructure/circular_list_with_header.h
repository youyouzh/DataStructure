#pragma once

#include<iostream>
#include<sstream>
#include<string>
#include "chain_node.h"
#include "u_exception.h"

template<class T>
class CircularListWithHeader
{
public:
	// constructor
	CircularListWithHeader();

	// some methods
	int size() const { return list_size; }
	int index_of(const T& element) const;
	void insert(int index, const T& element);
	void output(std::ostream& out) const;

protected:
	void check_index(int index) const;
	// throw IllegalIndexException if index invalid
	ChainNode<T>* header_node;  // pointer to header node
	int list_size;              // number of elements in list
};

template<class T>
CircularListWithHeader<T>::CircularListWithHeader()
{// Constructor.
    header_node = new ChainNode<T>();
	header_node->next = header_node;
	list_size = 0;
}

template<class T>
void CircularListWithHeader<T>::check_index(int index) const
{// Verify that index is between 0 and list_size - 1.
	if (index < 0 || index >= list_size)
	{
		std::ostringstream s;
		s << "index = " << index << " size = " << list_size;
		throw IllegalIndexException(s.str());
	}

}

template<class T>
int CircularListWithHeader<T>::index_of(const T& element) const
{// Return index of first occurrence of element.
 // Return -1 if element not in list.

 // Put element in header node
	header_node->element = element;

	// search the chain for element
	ChainNode<T>* currentNode = header_node->next;
	int index = 0;  // index of currentNode
	while (currentNode->element != element)
	{
		// move to next node
		currentNode = currentNode->next;
		index++;
	}

	// make sure we found matching element
	if (currentNode == header_node)
		return -1;
	else
		return index;
}

template<class T>
void CircularListWithHeader<T>::insert(int index, const T& element)
{// Insert element so that its index is index.
	if (index < 0 || index > list_size)
	{// invalid index
		std::ostringstream s;
		s << "index = " << index << " size = " << list_size;
		throw IllegalIndexException(s.str());
	}

	// find predecessor of new element
	ChainNode<T>* p = header_node;
	for (int i = 0; i < index; i++)
		p = p->next;

	// insert after p
	p->next = new ChainNode<T>(element, p->next);

	list_size++;
}

template<class T>
void CircularListWithHeader<T>::output(std::ostream& out) const
{// Put the list into the stream out.
	for (ChainNode<T>* currentNode = header_node->next;
		currentNode != header_node;
		currentNode = currentNode->next)
		out << currentNode->element << "  ";
}

// overload <<
template <class T>
std::ostream& operator<<(std::ostream& out, const CircularListWithHeader<T>& list)
{
	list.output(out); return out;
}
