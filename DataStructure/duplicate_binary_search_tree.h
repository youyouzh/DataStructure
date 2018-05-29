// 值可重复的索引二叉树
#pragma once

#include "binary_search_tree.h"

template <class K, class V>
class DuplicateIndexedBinarySearchTree : public BinarySearchTree<K, V>
{
public:
	typedef std::pair<K, V> Pair;
	typedef LinkedBinaryTree<Pair> LBT;

	void insert(const std::pair<K, V>& pair) override;
};

template <class K, class V>
void DuplicateIndexedBinarySearchTree<K, V>::insert(const std::pair<K, V>& pair)
{
	// 首先寻找插入位置
	BinaryTreeNode<Pair> *find_node = LBT::root;  // 查找指针
	BinaryTreeNode<Pair> *find_parent_node = nullptr; // 查找指针的父节点指针

	while (find_node != nullptr)
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
		{ // 关键字相同，则随机使用左右孩子
			if (rand() % 2)
			{
				find_node = find_node->left_child;
			}
			else
			{
				find_node = find_node->right_child;
			}
			break;
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
		else if (pair.first > find_parent_node->element.first)
		{ // 大值插入为右孩子
			find_parent_node->right_child = new_node;
		}
		else
		{
			if (find_parent_node->left_child == find_node)
			{
				new_node->left_child = find_node;
				find_parent_node->left_child = new_node;
			}
			else
			{
				new_node->right_child = find_node;
				find_parent_node->right_child = new_node;
			}
		}
	}
}
