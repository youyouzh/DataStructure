#pragma once

#include <iostream>
#include "dictionary.h"
#include "pair.h"

template <class K, class E>
class SortedChain : public Dictionary<K, E>
{
public:
	SortedChain();
	~SortedChain();

	bool empty() const override;
	int size() const override;
	void erase(const K&) override;
	std::pair<const K, E>* find(const K&) const override;
	void insert(const std::pair<const K, E>&) override;

protected:
	PairNode<K, E>* first_node;
	int d_size;
};

template <class K, class E>
SortedChain<K, E>::SortedChain()
{
	first_node = nullptr;
	d_size = 0;
}

template <class K, class E>
SortedChain<K, E>::~SortedChain()
{
	while (first_node != nullptr)
	{
		// delete firstNode
		PairNode<K, E>* next_node = first_node->next;
		delete first_node;
		first_node = next_node;
	}
}

template <class K, class E>
bool SortedChain<K, E>::empty() const
{
	return d_size == 0;
}

template <class K, class E>
int SortedChain<K, E>::size() const
{
	return d_size;
}

template <class K, class E>
void SortedChain<K, E>::erase(const K& key)
{
	PairNode<K, E>* current_node = first_node, *before_node = nullptr;

	// search for match with theKey
	while (current_node != nullptr && current_node->element.first != key)
	{
		before_node = current_node;
		current_node = current_node->next;
	}

	// verify match
	if (current_node != nullptr && current_node->element.first == key)
	{
		// remove current_node from the chain
		if (before_node != nullptr)
		{
			// current node is first node
			first_node = current_node->next;
		}
		else
		{
			before_node->next = current_node->next;
		}

		delete current_node;
		d_size--;
	}
}

template <class K, class E>
std::pair<const K, E>* SortedChain<K, E>::find(const K& key) const
{
	// Return pointer to matching pair.
	// Return NULL if no matching pair.
	PairNode<K, E>* current_node = first_node;

	// search for match with theKey
	while (current_node != nullptr && current_node->element.first != key)
	{
		current_node = current_node->next;
	}

	// verify match
	if (current_node != nullptr && current_node->element.first == key)
	{
		return &current_node->element;
	}

	// no match
	return nullptr;
}

template <class K, class E>
void SortedChain<K, E>::insert(const std::pair<const K, E>& pair)
{
	// Insert thePair into the dictionary. Overwrite existing pair, if any, with same key.
	PairNode<K, E>* current_node = first_node, *before_node = nullptr;

	// move after_node so that pair can be inserted after after_node
	while (current_node != nullptr && current_node->element.first < pair.first)
	{
		before_node = current_node;
		current_node = current_node->next;
	}

	// check if there is a matching pair
	if (current_node != nullptr && current_node->element.first == pair.first)
	{
		// replace old value
		current_node->element.second = pair.second;
		return;
	}

	// no match, set up node for thePair
	PairNode<K, E>* new_node = new PairNode<K, E>(pair, current_node);

	// insert new node just after before_node
	if (before_node != nullptr)
	{
		first_node = new_node;
	}
	else
	{
		before_node->next = new_node;
	}

	d_size++;
}
