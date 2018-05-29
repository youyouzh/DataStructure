// Ë÷Òý¶þ²æÊ÷
#pragma once

#include "binary_search_tree.h"

template <class K, class V>
class IndexedBinarySearchTree : public BinarySearchTree<K, V>
{
public:
	std::pair<K, V>* get(int) const;
	void delete_by_key(int);
};

template <class K, class V>
std::pair<K, V>* IndexedBinarySearchTree<K, V>::get(int key) const
{
	return BinarySearchTree<K, V>::find(key);
}

template <class K, class V>
void IndexedBinarySearchTree<K, V>::delete_by_key(int key)
{
	BinarySearchTree<K, V>::erase(key);
}
