// ֵ���ظ�������������
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
	// ����Ѱ�Ҳ���λ��
	BinaryTreeNode<Pair> *find_node = LBT::root;  // ����ָ��
	BinaryTreeNode<Pair> *find_parent_node = nullptr; // ����ָ��ĸ��ڵ�ָ��

	while (find_node != nullptr)
	{
		find_parent_node = find_node;
		// ����Ԫ��
		if (pair.first < find_node->element.first)
		{ // С���������Ӳ���
			find_node = find_node->left_child;
		}
		else if (pair.first > find_node->element.first)
		{ // ���������Һ��Ӳ���
			find_node = find_node->right_child;
		}
		else
		{ // �ؼ�����ͬ�������ʹ�����Һ���
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

	// Ϊpair����һ���½ڵ�
	auto *new_node = new BinaryTreeNode<Pair>(pair);
	if (LBT::root == nullptr)
	{ // ��Ϊ��
		LBT::root = new_node;
	}
	else
	{
		if (pair.first < find_parent_node->element.first)
		{ // Сֵ����Ϊ����
			find_parent_node->left_child = new_node;
		}
		else if (pair.first > find_parent_node->element.first)
		{ // ��ֵ����Ϊ�Һ���
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
