// linked binary tree using nodes of type binaryTreeNode
// derives from the abstract class binaryTree

#pragma once

#include <iostream>
#include <functional>
#include "binary_tree.h"
#include "binary_tree_node.h"
#include "array_queue.h"
#include "u_exception.h"

template <class T>
class LinkedBinaryTree : public BinaryTree<BinaryTreeNode<T> >
{
public:
	typedef std::function<void(BinaryTreeNode<T>*)> VisitFunction;

	LinkedBinaryTree();
	LinkedBinaryTree(BinaryTreeNode<T>*, int);
	~LinkedBinaryTree() override;

	// ADT methods
	bool empty() const override;
	int size() const override;
	void pre_order(const VisitFunction&) override;
	void in_order(const VisitFunction&) override;
	void post_order(const VisitFunction&) override;
	void level_order(const VisitFunction&) override;

	void make_tree(const T& element,
		LinkedBinaryTree<T>&,
		LinkedBinaryTree<T>&);
	void make_tree(BinaryTreeNode<T> *root, int tree_size);
	LinkedBinaryTree<T>& remove_left_subtree();
	LinkedBinaryTree<T>& remove_right_subtree();

	void pre_order_output() const;
	void in_order_output() const;
	void post_order_output() const;
	void level_order_output() const;
	void erase();
	T* root_element() const;
	int height() const;

protected:
	// pointer to root
	BinaryTreeNode<T> *root;
	// number of nodes in tree
	int tree_size;
	// visit function
	static VisitFunction visit;
	// used to count nodes in a subtree
	static int count;

	static void pre_order(BinaryTreeNode<T> *tree);
	static void in_order(BinaryTreeNode<T> *tree);
	static void post_order(BinaryTreeNode<T> *tree);

	static void count_nodes(BinaryTreeNode<T> *tree);
	static void dispose(BinaryTreeNode<T> *node);
	static void output(BinaryTreeNode<T> *node);
	static void add_to_count(BinaryTreeNode<T> *node);
	static int height(BinaryTreeNode<T> *tree);

};
// use the explicit declarations that follow are used for our purpose instead
std::function<void(BinaryTreeNode<int>*)> LinkedBinaryTree<int>::visit;
std::function<void(BinaryTreeNode<std::pair<int, int>>*)> LinkedBinaryTree<std::pair<int, int>>::visit;
std::function<void(BinaryTreeNode<std::pair<int, char>>*)> LinkedBinaryTree<std::pair<int, char>>::visit;
std::function<void(BinaryTreeNode<std::pair<const int, char>>*)> LinkedBinaryTree<std::pair<const int, char>>::visit;
//void(*LinkedBinaryTree<int>::visit)(BinaryTreeNode<int>*);
//void(*LinkedBinaryTree<std::pair<int, int> >::visit)(BinaryTreeNode<std::pair<int, int> >*);
//void(*LinkedBinaryTree<std::pair<const int, char> >::visit)(BinaryTreeNode<std::pair<const int, char> >*);
//void(*LinkedBinaryTree<std::pair<int, char> >::visit)(BinaryTreeNode<std::pair<int, char> >*);
//void(*LinkedBinaryTree<std::pair<const int, int> >::visit)(BinaryTreeNode<std::pair<const int, int> >*);

template <class T>
LinkedBinaryTree<T>::LinkedBinaryTree()
{
	root = nullptr;
	tree_size = 0;
}

template <class T>
LinkedBinaryTree<T>::LinkedBinaryTree(BinaryTreeNode<T>* root, int tree_size)
{
	this->root = root;
	this->tree_size = tree_size;
}

template <class T>
LinkedBinaryTree<T>::~LinkedBinaryTree()
{
//	 erase();
}

template <class T>
bool LinkedBinaryTree<T>::empty() const
{
	return tree_size == 0;
}

template <class T>
int LinkedBinaryTree<T>::size() const
{
	return tree_size;
}

template <class T>
void LinkedBinaryTree<T>::pre_order(const VisitFunction& visit)
{
	// bind the visit function
	this->visit = visit;
	pre_order(root);
}

template <class T>
void LinkedBinaryTree<T>::in_order(const VisitFunction& visit)
{
	this->visit = visit;
	in_order(root);
}

template <class T>
void LinkedBinaryTree<T>::post_order(const VisitFunction& visit)
{
	this->visit = visit;
	post_order(root);
}

template <class T>
void LinkedBinaryTree<T>::level_order(const VisitFunction& visit)
{
	// Level-order traversal
	ArrayQueue<BinaryTreeNode<T>*> queue;
	BinaryTreeNode<T> *node = root;

	while (node != nullptr)
	{
		visit(node);
		// put t's children on queue
		if (node->left_child != nullptr)
		{
			queue.push(node->left_child);
		}
		if (node->right_child != nullptr)
		{
			queue.push(node->right_child);
		}

		// get next node to visit
		try
		{
			node = queue.front();
		} 
		catch(QueueEmptyException)
		{
			return;
		}
		queue.pop();
	}
}

template <class T>
void LinkedBinaryTree<T>::make_tree(const T& element, 
	LinkedBinaryTree<T>& left, 
	LinkedBinaryTree<T>& right)
{
	// Combine left, right, and element to make new tree.
	root = new BinaryTreeNode<T>(element, left.root, right.root);
	tree_size = left.size() + right.size() + 1;

	// deny access from trees left and right
	left.root = right.root = nullptr;
	left.tree_size = right.tree_size = 0;
}

template <class T>
void LinkedBinaryTree<T>::make_tree(BinaryTreeNode<T> *root, int tree_size)
{
	this->root = root;
	this->tree_size = tree_size;
}

template <class T>
LinkedBinaryTree<T>& LinkedBinaryTree<T>::remove_left_subtree()
{
	if (tree_size == 0)
	{
		throw EmptyTreeException();
	}

	// detach left subtree and save in leftSubtree
	LinkedBinaryTree<T> left_subtree;
	left_subtree.root = root->left_child;

	// count left subtree nodes
	count = 0;
	left_subtree.tree_size = count_nodes(left_subtree.root);
	root->left_child = nullptr;
	tree_size -= left_subtree.tree_size;

	return left_subtree;
	// when return, left tree while be delete
}

template <class T>
LinkedBinaryTree<T>& LinkedBinaryTree<T>::remove_right_subtree()
{
	if (tree_size == 0)
	{
		throw EmptyTreeException();
	}

	// detach right subtree and save in leftSubtree
	LinkedBinaryTree<T> right_subtree;
	right_subtree.root = root->right_child;

	// count right subtree nodes
	count = 0;
	right_subtree.tree_size = count_nodes(right_subtree.root);
	root->right_subtree = nullptr;
	tree_size -= right_subtree.tree_size;

	return right_subtree;
	// when return, right tree while be delete
}

template <class T>
void LinkedBinaryTree<T>::pre_order_output() const
{
	pre_order(output());
	std::cout << std::endl;
}

template <class T>
void LinkedBinaryTree<T>::in_order_output() const
{
	in_order(output());
	std::cout << std::endl;
}

template <class T>
void LinkedBinaryTree<T>::post_order_output() const
{
	post_order(output());
	std::cout << std::endl;
}

template <class T>
void LinkedBinaryTree<T>::level_order_output() const
{
	level_order(output);
	std::cout << std::endl;
}

template <class T>
void LinkedBinaryTree<T>::erase()
{
	if (root == nullptr)
	{
		return;
	}
	// post order tree and dispose node
	post_order(dispose);
	root = nullptr;
	tree_size = 0;
}

template <class T>
T* LinkedBinaryTree<T>::root_element() const
{
	if (tree_size == 0)
	{
		return nullptr;
	}
	else
	{
		return &root->element;
	}
}

template <class T>
int LinkedBinaryTree<T>::height() const
{
	return height(root);
}

template <class T>
void LinkedBinaryTree<T>::pre_order(BinaryTreeNode<T>* tree)
{
	// Preorder traversal
	if (tree != nullptr)
	{
		// visit tree
		LinkedBinaryTree<T>::visit(tree);
		// visit left child
		pre_order(tree->left_child);
		// visit right child
		pre_order(tree->right_child);
	}
}

template <class T>
void LinkedBinaryTree<T>::in_order(BinaryTreeNode<T>* tree)
{
	// Inorder traversal
	if (tree != nullptr)
	{
		in_order(tree->left_child);
		LinkedBinaryTree<T>::visit(tree);
		in_order(tree->right_child);
	}
}

template <class T>
void LinkedBinaryTree<T>::post_order(BinaryTreeNode<T>* tree)
{
	// Postorder traversal
	if (tree != nullptr)
	{
		post_order(tree->left_child);
		post_order(tree->right_child);
		LinkedBinaryTree<T>::visit(tree);
	}
}

template <class T>
void LinkedBinaryTree<T>::count_nodes(BinaryTreeNode<T>* tree)
{
	visit = add_to_count;
	count = 0;
	pre_order(tree);
}

template <class T>
void LinkedBinaryTree<T>::dispose(BinaryTreeNode<T>* node)
{
	delete node;
	// 删除指针，避免野指针
	node = nullptr;
}

template <class T>
void LinkedBinaryTree<T>::output(BinaryTreeNode<T>* node)
{
	std::cout << node->element << "  ";
}

template <class T>
void LinkedBinaryTree<T>::add_to_count(BinaryTreeNode<T>* node)
{
	count++;
}

template <class T>
int LinkedBinaryTree<T>::height(BinaryTreeNode<T>* tree)
{
	// return height of tree rooted at tree
	if (tree == nullptr)
	{
		return 0;
	}

	int left_height = height(tree->left_child);
	int right_height = height(tree->right_child);
	if (left_height > right_height)
	{
		return ++left_height;
	}
	else
	{
		return ++right_height;
	}
}
