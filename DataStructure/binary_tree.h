// abstract class binary tree
// abstract data type specification for binary trees
// all methods are pure virtual functions
// T is node type

#pragma once

#include <functional>

template <class T>
class BinaryTree
{
public:
	typedef std::function<void(T*)> VisitFunction;

	virtual ~BinaryTree() {}
	virtual bool empty() const = 0;
	virtual int size() const = 0;

	// parameter is a pointer to a function whose return
	// type is void and has a single argument of type T*
	virtual void pre_order(const VisitFunction&) = 0;
	virtual void in_order(const VisitFunction&) = 0;
	virtual void post_order(const VisitFunction&) = 0;
	virtual void level_order(const VisitFunction&) = 0;
};
