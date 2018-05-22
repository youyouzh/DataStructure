#pragma once
#include "linear_list.h"

template <class T>
class ExtendedLinearList : public LinearList<T>
{
public:
	virtual ~ExtendedLinearList(){}
	// clear the list
	virtual void clear() = 0;
	// insert the element at end of list
	virtual void push_back(const T& element) = 0;
};