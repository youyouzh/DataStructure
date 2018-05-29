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

	// ʵ�� Dictionary �ķ���
	bool empty() const override;
	int size() const override;
	void insert(const Pair& pair) override;
	void erase(const K& key) override;
	Pair* find(const K& key) const override;

	BinaryTreeNode<Pair>* find_node(const K& key) const;

	// �����������е����
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
	// ����������
	BinaryTreeNode<Pair> *find_node = LBT::root;
	while (find_node != nullptr)
	{
		// ���Ԫ��
		if (key < find_node->element.first)
		{ // С���������Ӳ���
			find_node = find_node->left_child;
		}
		else if (key > find_node->element.first)
		{ // ���������Һ��Ӳ���
			find_node = find_node->right_child;
		}
		else
		{ // ������ҵ�
			return find_node;
		}
	}

	// ��ƥ���
	return nullptr;
}


template <class K, class E>
void BinarySearchTree<K, E>::insert(const Pair& pair)
{ // ����pair�������������ؼ�����ͬ���򸲸�
	// ����Ѱ�Ҳ���λ��
	BinaryTreeNode<Pair> *find_node = LBT::root;  // ����ָ��
	BinaryTreeNode<Pair> *find_parent_node = nullptr; // ����ָ��ĸ��ڵ�ָ��

	while(find_node != nullptr)
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
		{ // ���Ǿ�ֵ
			find_node->element.second = pair.second;
			return;
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
		else
		{ // ��ֵ����Ϊ�Һ���
			find_parent_node->right_child = new_node;
		}
	}
}

template <class K, class E>
void BinarySearchTree<K, E>::erase(const K& key)
{ // ɾ���ؼ���Ϊkey������
	// ���Ȳ��ҹؼ���Ϊkey�Ľڵ�
	BinaryTreeNode<Pair> *find_node = LBT::root; // ����ָ��
	BinaryTreeNode<Pair> *find_parent_node = nullptr;  // ����ָ��ĸ��ڵ�ָ��
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

	// ���û���ҵ�����ڵ㣬�򷵻�
	if (find_node == nullptr)
	{
		return;
	}

	// ��ɾ���Ľڵ����������ӽڵ�ʱ��ת��Ϊɾ�������ӽڵ����Ҷ�ӽڵ�
	if (find_node->left_child != nullptr && find_node->right_child != nullptr)
	{
		// �ڵ�ǰ�ڵ����������Ѱ�����Ԫ�ؽڵ�
		BinaryTreeNode<Pair> *left_subtree_max_node = find_node->left_child;
		BinaryTreeNode<Pair> *left_subtree_max_parent_node = find_node;

		// ˳���Һ����������ֵ
		while (left_subtree_max_node->right_child != nullptr)
		{
			left_subtree_max_parent_node = left_subtree_max_node;
			left_subtree_max_node = left_subtree_max_node->right_child;
		}

		// �����Ԫ���ƶ���ɾ���Ľڵ�find_pointer
		// ����ʹ�ã�find_pointer->element = max_pointer->element; keyΪ����ʱ��ʧЧ
		auto *move_subtree = new BinaryTreeNode<Pair>(left_subtree_max_node->element,
			find_node->left_child,
			find_node->right_child);
		
		if (find_parent_node == nullptr)
		{ // ���ɾ���ڵ�Ϊ���ڵ�
			LBT::root = move_subtree;
		}
		else if (find_node == find_parent_node->left_child)
		{ // ɾ���ڵ�Ϊ�丸�ڵ�����
			find_parent_node->left_child = move_subtree;
		}
		else
		{ // ɾ���ڵ�Ϊ�丸�ڵ��Һ���
			find_parent_node->right_child = move_subtree;
		}

		// ת��Ϊɾ��һ�������ӽڵ����Ҷ�ӽڵ�
		if (left_subtree_max_parent_node == find_node)
		{ // find_node�������ĵ�һ�����ӽڵ�Ϊ���ֵ��ɾ�������ӽڵ�
			find_parent_node = move_subtree;
		}
		else
		{ // Ҷ�ӽڵ�Ϊ���ֵ��ɾ��Ҷ�ӽڵ�
			find_parent_node = left_subtree_max_parent_node;
		}

//		delete find_node;
		find_node = left_subtree_max_node;
	}

	// ɾ���ڵ㣬������֯���ṹ��ʹ����Ϊ����������
	// find_node���ֻ��һ������
	BinaryTreeNode<Pair> *child_node = nullptr;  // ���ӽڵ�ָ��
	if (find_node->left_child != nullptr)
	{ // ����
		child_node = find_node->left_child;
	}
	else
	{ // �Һ��ӻ���Ϊ��
		child_node = find_node->right_child;
	}

	// ɾ��find_node
	if (find_node == LBT::root)
	{ // ɾ�����ڵ�
		LBT::root = child_node;
	}
	else if (find_node == find_parent_node->left_child)
	{ // ɾ�����ӽڵ�
		find_parent_node->left_child = child_node;
	}
	else
	{ // ɾ���Һ��ӽڵ�
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
