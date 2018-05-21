#pragma once

#include<iostream>
#include<sstream>
#include "linear_list.h"
#include "chain_node.h"
#include "u_exception.h"

template <class T>
class Chain : public LinearList<T>
{
public:
	explicit Chain(int capacity = 10);
	Chain(const Chain<T>&);
	~Chain();

	// ADT method
	bool empty() const override;
	int size() const override;
	T& get(int index) const override;
	int index_of(const T& element) const override;
	void erase(int index) override;
	void insert(int index, const T& element) override;
	void output(std::ostream& out) const override;

protected:
	void check_index(int index) const;
	// the first_node of chain
	ChainNode<T>* first_node;
	int list_size;
};

template <class T>
Chain<T>::Chain(int capacity)
{
	if (capacity < 1)
	{
		std::ostringstream s;
		s << "Initial capacity = " << capacity << " Must be > 0";
		throw IllegalParameterValueException(s.str());
	}

	first_node = nullptr;
	list_size = 0;
}

template <class T>
Chain<T>::Chain(const Chain<T>& list)
{
	list_size = list.list_size;

	// empty list
	if (list_size == 0)
	{
		first_node = nullptr;
		return;
	}

	// non-empty list
	ChainNode<T>* source_node = list.first_node;
	ChainNode<T>* target_node = list.first_node;
	// copy the first node
	first_node = new ChainNode<T>(source_node);
	source_node = source_node->next;
	while (source_node != nullptr)
	{
		target_node->next = new ChainNode<T>(source_node);
		target_node = target_node->next;
		source_node = source_node->next;
	}
	target_node->next = nullptr;
}

template <class T>
Chain<T>::~Chain()
{
	while (first_node != nullptr)
	{
		ChainNode<T>* next_node = first_node->next;
		delete first_node;
		first_node = next_node;
	}
}

template <class T>
bool Chain<T>::empty() const
{
	return first_node == nullptr;
}

template <class T>
int Chain<T>::size() const
{
	return list_size;
}


template <class T>
void Chain<T>::check_index(int index) const
{
	if (index < 0 || index >= list_size)
	{
		std::ostringstream s;
		s << "index = " << index << " size = " << list_size;
		throw IllegalIndexException(s.str());
	}
}

template <class T>
T& Chain<T>::get(int index) const
{
	// check the index invalid
	check_index(index);
	ChainNode<T>* current_node = first_node;
	// move to desired node
	for (auto i = 0; i < index; i++)
	{
		current_node = current_node->next;
	}
	return current_node->element;
}

template <class T>
int Chain<T>::index_of(const T& element) const
{
	// search the chain for the element
	ChainNode<T>* current_node = first_node;
	auto position = 0;
	while (current_node != nullptr)
	{
		if (current_node->element == element)
		{
			return position;
		}
		position++;
		current_node = current_node->next;
	}
	return -1;
}

template <class T>
void Chain<T>::erase(int index)
{
	// check the index is invalid
	check_index(index);

	auto current_node = first_node;
	auto delete_node = first_node;

	// handle first_node node
	if (index == 0)
	{
		delete_node = first_node;
		first_node = first_node->next;
	}
	else
	{
		auto position = 0;
		// find the node in front of the delete node
		while (position++ < index - 1)
		{
			current_node = current_node->next;
		}
		delete_node = current_node->next;
		current_node->next = current_node->next->next;
	}

	delete delete_node;
	list_size--;
}

template <class T>
void Chain<T>::insert(int index, const T& element)
{
	// check index invalid
	if (index < 0 || index > list_size)
	{
		std::ostringstream s;
		s << "index = " << index << " size = " << list_size;
		throw IllegalIndexException(s.str());
	}


	if (index == 0)
	{
		// insert at front
		first_node = new ChainNode<T>(element, first_node);
	}
	else
	{
		ChainNode<T>* current_node = first_node;
		auto position = 0;
		// find the position where insert
		while (position++ < index - 1)
		{
			current_node = current_node->next;
		}
		// insert after current
		current_node->next = new ChainNode<T>(element, current_node->next);
	}


	list_size++;

}

template <class T>
void Chain<T>::output(std::ostream& out) const
{
	ChainNode<T>* current_node = first_node;
	while (current_node != nullptr)
	{
		out << current_node->element << "  ";
		current_node = current_node->next;
	}
}

template <class T>
std::ostream& operator<<(std::ostream& out, const Chain<T>& list)
{
	list.output(out);
	return out;
}