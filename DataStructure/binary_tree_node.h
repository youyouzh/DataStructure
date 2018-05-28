// abstract class binary tree
// abstract data type specification for binary trees
// all methods are pure virtual functions
// T is node type

#pragma once

template <class T>
class BinaryTreeNode
{
public:
	T element;
	// left subtree
	BinaryTreeNode *left_child;
	// right subtree
	BinaryTreeNode *right_child;

	BinaryTreeNode();
	explicit BinaryTreeNode(const T& element);
	BinaryTreeNode(const T& element, 
		BinaryTreeNode *left_child, 
		BinaryTreeNode *right_child);
};

template <class T>
BinaryTreeNode<T>::BinaryTreeNode()
{
	left_child = right_child = nullptr;
}

template <class T>
BinaryTreeNode<T>::BinaryTreeNode(const T& element)
{
	this->element = element;
}

template <class T>
BinaryTreeNode<T>::BinaryTreeNode(const T& element, 
	BinaryTreeNode* left_child, 
	BinaryTreeNode* right_child) : element(element)
{
	this->left_child = left_child;
	this->right_child = right_child;
}
