// node with a next and element field; element is a pair<const K,E>

#pragma once

template <class K, class E>
struct PairNode
{
	typedef  std::pair<const K, E> PairType;

	PairType element;

	PairNode<K, E>* next;

	explicit PairNode(const PairType& pair) : element(pair) {}

	PairNode(const PairType pair, PairNode<K, E>* next) : element(pair) { this->next = next; }
};
