#pragma once

#include "extended_linear_list.h"
#include "chain.h"

template <class T>
class ExtendedChain : public ExtendedLinearList<T>, public Chain<T>
{
public:
	explicit ExtendedChain(int capacity = 10);
	ExtendedChain(const ExtendedChain<T>& list);

	// ADT methods
//	bool empty() const;
//	int size() const;
//	T& get(int index) const;
//	int index_of(const T& element);
	void erase(int index) override;
	void insert(int index, const T& element) override;
	// clear the list
	void clear() override;
	// Insert the element at the end of the chain.
	void push_back(const T& element) override;
//	void output(ostream& out) const;
	
	// additional methods
	void zero();

protected:
	// pointer to last node in chain
	ChainNode<T>* last_node;
};

template <class T>
ExtendedChain<T>::ExtendedChain(int capacity) : Chain<T>(capacity) {}

template <class T>
ExtendedChain<T>::ExtendedChain(const ExtendedChain<T>& list) : Chain<T>(list) {}

template <class T>
void ExtendedChain<T>::erase(int index)
{
	Chain<T>::check_index(index);

	ChainNode<T>* delete_node = nullptr;
	ChainNode<T>* current_node = Chain<T>::first_node;
	if (index == 0)
	{
		delete_node = Chain<T>::first_node;
		Chain<T>::first_node = Chain<T>::first_node->next;
	}
	else
	{
		auto position = 0;
		while (position++ < index - 1)
		{
			current_node = current_node->next;
		}
		delete_node = current_node->next;
		current_node->next = current_node->next->next;
		if (delete_node == last_node)
		{
			last_node = current_node;
		}
	}

	--Chain<T>::list_size;
	delete delete_node;
}

template <class T>
void ExtendedChain<T>::insert(int index, const T& element)
{
	// check index invalid
	if (index < 0 || index > Chain<T>::list_size)
	{
		std::ostringstream s;
		s << "index = " << index << " size = " << Chain<T>::list_size;
		throw IllegalIndexException(s.str());
	}

	if (index == 0)
	{
		// insert at front
		Chain<T>::first_node = new ChainNode<T>(element, Chain<T>::first_node);
		if (Chain<T>::list_size == 0)
		{
			last_node = Chain<T>::first_node;
		}
	}
	else
	{
		ChainNode<T>* current_node = Chain<T>::first_node;
		auto position = 0;
		while (position++ < index - 1)
		{
			current_node = current_node->next;
		}
		// insert after current_node
		if (Chain<T>::list_size == index)
		{
			last_node = current_node->next;
		}
	}
}

template <class T>
void ExtendedChain<T>::clear()
{
	auto next_node = Chain<T>::first_node;
	while (Chain<T>::first_node != nullptr)
	{
		next_node = Chain<T>::first_node->next;
		delete(Chain<T>::first_node);
		Chain<T>::first_node = next_node;
	}
	Chain<T>::list_size = 0;
}

template <class T>
void ExtendedChain<T>::push_back(const T& element)
{
	ChainNode<T>* new_node = new ChainNode<T>(element, nullptr);
	if (Chain<T>::first_node == nullptr)
	{
		// chain is empty, first_node is equal last_node
		Chain<T>::first_node = last_node = new_node;
	}
	else
	{
		last_node->next = new_node;
		last_node = new_node;
	}
	++Chain<T>::list_size;
}

template <class T>
void ExtendedChain<T>::zero()
{
	Chain<T>::first_node = nullptr;
	last_node = nullptr;
	Chain<T>::list_size = 0;
}
