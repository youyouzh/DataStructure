// linked binary tree implementation of a binary search tree
// implements all dictionary and bsTree methods

#pragma once

#include "dictionary.h"
#include "linked_binary_tree.h"

template <class K, class E>
class BinarySearchTree : public Dictionary<K, E>,
	public LinkedBinaryTree<std::pair<K, E>>
{
public:
	typedef std::pair<K, E> Pair;
	typedef LinkedBinaryTree<Pair> LBT;

	// 实现 Dictionary 的方法
	bool empty() const override;
	int size() const override;
	void insert(const Pair& pair) override;
	void erase(const K& key) override;
	Pair* find(const K& key) const override;

	BinaryTreeNode<Pair>* find_node(const K& key) const;

	// 按键升序排列的输出
	void ascend();
};

template <class K, class E>
bool BinarySearchTree<K, E>::empty() const
{
	return LBT::tree_size == 0;
}

template <class K, class E>
int BinarySearchTree<K, E>::size() const
{
	return LBT::tree_size;
}


template <class K, class E>
std::pair<K, E>* BinarySearchTree<K, E>::find(const K& key) const
{
	return &find_node(key)->element;
}

template <class K, class E>
BinaryTreeNode<std::pair<K, E>>* BinarySearchTree<K, E>::find_node(const K& key) const
{
	// 二叉树搜索
	BinaryTreeNode<Pair> *find_node = LBT::root;
	while (find_node != nullptr)
	{
		// 检查元素
		if (key < find_node->element.first)
		{ // 小于则往左孩子查找
			find_node = find_node->left_child;
		}
		else if (key > find_node->element.first)
		{ // 大于则往右孩子查找
			find_node = find_node->right_child;
		}
		else
		{ // 相等则找到
			return find_node;
		}
	}

	// 无匹配对
	return nullptr;
}


template <class K, class E>
void BinarySearchTree<K, E>::insert(const Pair& pair)
{ // 插入pair，如果存在与其关键字相同，则覆盖
	// 首先寻找插入位置
	BinaryTreeNode<Pair> *find_node = LBT::root;  // 查找指针
	BinaryTreeNode<Pair> *find_parent_node = nullptr; // 查找指针的父节点指针

	while(find_node != nullptr)
	{
		find_parent_node = find_node;
		// 查找元素
		if (pair.first < find_node->element.first)
		{ // 小于则往左孩子查找
			find_node = find_node->left_child;
		}
		else if (pair.first > find_node->element.first)
		{ // 大于则往右孩子查找
			find_node = find_node->right_child;
		}
		else
		{ // 覆盖旧值
			find_node->element.second = pair.second;
			return;
		}
	}

	// 为pair建立一个新节点
	auto *new_node = new BinaryTreeNode<Pair>(pair);
	if (LBT::root == nullptr)
	{ // 树为空
		LBT::root = new_node;
	}
	else
	{
		if (pair.first < find_parent_node->element.first)
		{ // 小值插入为左孩子
			find_parent_node->left_child = new_node;
		}
		else
		{ // 大值插入为右孩子
			find_parent_node->right_child = new_node;
		}
	}
}

template <class K, class E>
void BinarySearchTree<K, E>::erase(const K& key)
{ // 删除关键字为key的数对
	// 首先查找关键字为key的节点
	BinaryTreeNode<Pair> *find_node = LBT::root; // 查找指针
	BinaryTreeNode<Pair> *find_parent_node = nullptr;  // 查找指针的父节点指针
	while (find_node != nullptr && find_node->element.first != key)
	{
		find_parent_node = find_node;
		if (key < find_node->element.first)
		{
			find_node = find_node->left_child;
		}
		else
		{
			find_node = find_node->right_child;
		}
	}

	// 如果没有找到相符节点，则返回
	if (find_node == nullptr)
	{
		return;
	}

	// 当删除的节点有两个孩子节点时，转化为删除单孩子节点或者叶子节点
	if (find_node->left_child != nullptr && find_node->right_child != nullptr)
	{
		// 在当前节点的左子树中寻找最大元素节点
		BinaryTreeNode<Pair> *left_subtree_max_node = find_node->left_child;
		BinaryTreeNode<Pair> *left_subtree_max_parent_node = find_node;

		// 顺着右孩子搜索最大值
		while (left_subtree_max_node->right_child != nullptr)
		{
			left_subtree_max_parent_node = left_subtree_max_node;
			left_subtree_max_node = left_subtree_max_node->right_child;
		}

		// 将最大元素移动到删除的节点find_pointer
		// 不能使用：find_pointer->element = max_pointer->element; key为常量时会失效
		auto *move_subtree = new BinaryTreeNode<Pair>(left_subtree_max_node->element,
			find_node->left_child,
			find_node->right_child);
		
		if (find_parent_node == nullptr)
		{ // 如果删除节点为根节点
			LBT::root = move_subtree;
		}
		else if (find_node == find_parent_node->left_child)
		{ // 删除节点为其父节点左孩子
			find_parent_node->left_child = move_subtree;
		}
		else
		{ // 删除节点为其父节点右孩子
			find_parent_node->right_child = move_subtree;
		}

		// 转化为删除一个单孩子节点或者叶子节点
		if (left_subtree_max_parent_node == find_node)
		{ // find_node左子树的第一个孩子节点为最大值，删除单孩子节点
			find_parent_node = move_subtree;
		}
		else
		{ // 叶子节点为最大值，删除叶子节点
			find_parent_node = left_subtree_max_parent_node;
		}

//		delete find_node;
		find_node = left_subtree_max_node;
	}

	// 删除节点，重新组织树结构，使得树为二叉搜索树
	// find_node最多只有一个孩子
	BinaryTreeNode<Pair> *child_node = nullptr;  // 孩子节点指针
	if (find_node->left_child != nullptr)
	{ // 左孩子
		child_node = find_node->left_child;
	}
	else
	{ // 右孩子或者为空
		child_node = find_node->right_child;
	}

	// 删除find_node
	if (find_node == LBT::root)
	{ // 删除根节点
		LBT::root = child_node;
	}
	else if (find_node == find_parent_node->left_child)
	{ // 删除左孩子节点
		find_parent_node->left_child = child_node;
	}
	else
	{ // 删除右孩子节点
		find_parent_node->right_child = child_node;
	}

	--LBT::tree_size;
	// find_node will be deleted when return
//	delete find_node;
}

template <class K, class E>
void BinarySearchTree<K, E>::ascend()
{
	LBT::in_order_output();
}
