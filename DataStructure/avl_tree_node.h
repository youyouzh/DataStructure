#pragma once
#include "binary_tree_node.h"

template <class T>
class AVLTreeNode : public BinaryTreeNode<T>
{
public:
	T element;
	// Æ½ºâÒò×Ó
	int balance_factor;

	// left subtree
	AVLTreeNode *left_child;
	// right subtree
	AVLTreeNode *right_child;

	AVLTreeNode();
	explicit AVLTreeNode(const T& element);
	AVLTreeNode(const T& element,
		AVLTreeNode *left_child,
		AVLTreeNode *right_child);
};

template <class T>
AVLTreeNode<T>::AVLTreeNode()
{
	balance_factor = 0;
	left_child = right_child = nullptr;
}

template <class T>
AVLTreeNode<T>::AVLTreeNode(const T& element)
{
	this->balance_factor = 0;
	this->element = element;
	left_child = right_child = nullptr;
}

template <class T>
AVLTreeNode<T>::AVLTreeNode(const T& element,
	AVLTreeNode* left_child,
	AVLTreeNode* right_child)
{
	this->element = element;
	this->left_child = left_child;
	this->right_child = right_child;
	if (nullptr == left_child && nullptr == right_child)
	{
		this->balance_factor = 0;
	}
	else if (nullptr == left_child && nullptr != right_child)
	{
		this->balance_factor = -1;
	}
	else
	{
		this->balance_factor = 1;
	}
}
