#pragma once

#include "dictionary.h"
#include "avl_tree_node.h"
#include <utility>

template <class K, class V>
class AVLTree : public Dictionary<K, V>
{
public:
	typedef std::pair<K, V> Pair;

	bool empty() const override;
	int size() const override;
	void insert(const Pair& pair) override;
	void erase(const K& key) override;
	Pair* find(const K& key) const override;

protected:
	// pointer to root
	AVLTreeNode<Pair> *root;
	// number of nodes in tree
	int tree_size;
};
