// vector implementation of a linear list
// derives from abstract class linearList just to make sure
// all methods of the ADT are implemented
// USES STL ALGORITHMS TO SIMPLIFY CODE
// iterator class for vectorList included

#pragma once

#include<iostream>
#include<sstream>
#include<string>
#include<vector>
#include<algorithm>
#include<iterator>
#include "linear_list.h"
#include "u_exception.h"

using namespace std;

template<class T>
class VectorList : public LinearList<T> 
{
public:
	// constructor, copy constructor and destructor
	VectorList(int capacity = 10);
	VectorList(const VectorList<T>&);
	~VectorList() {delete element;}

	// ADT method
	bool empty() const override { return element->empty(); };
	int size() const override { return element->size(); };
	T& get(int the_index) const override;
	int index_of(const T& the_element) const override;
	void erase(int the_index) override;
	void insert(int the_index, const T& the_element) override;
	void output(ostream& out) const override;

	// additional method
	int capacity() const { return element->capacity(); };
      
	// iterators to start and end of list
	typedef typename vector<T>::iterator iterator;
	iterator begin() { return element->begin(); }
	iterator end() { return element->end(); }

protected:  
	void check_index(int the_index) const;
	vector<T>* element;     // vector to hold list elements
};

template<class T>
VectorList<T>::VectorList(int capacity)
{// Constructor.
	if (capacity < 1)
	{
		ostringstream s;
		s << "Initial capacity = " << capacity << " Must be > 0";
		throw IllegalParameterValueException(s.str());
	}

	// create an empty vector with capacity 0
	element = new vector<T>;

	// increase vector capacity from 0 to initialCapacity
	element->reserve(capacity);
}

template<class T>
VectorList<T>::VectorList(const VectorList<T>& the_list)
{// Copy constructor.
    element = new vector<T>(*the_list.element);
}

template<class T>
void VectorList<T>::check_index(int the_index) const
{// Verify that theIndex is between 0 and size() - 1.
	if (the_index < 0 || the_index >= size())
	{
		ostringstream s;
		s << "index = " << the_index << " size = " << size();
		throw IllegalIndexException(s.str());
	}
}

template<class T>
T& VectorList<T>::get(int the_index) const
{// Return element whose index is theIndex.
 // Throw illegalIndex exception if no such element.
	check_index(the_index);
	return (*element)[the_index];
}

template<class T>
int VectorList<T>::index_of(const T& the_element) const
{// Return index of first occurrence of theElement.
 // Return -1 if theElement not in list.

    // search for theElement
    int the_index = (int) (find(element->begin(), element->end(), the_element) - element->begin());

    // check if theElement was found
    if (the_index == size())
    {
		// not found
	    return -1;
    }
    else
    {
	    return the_index;
    }
 }

template<class T>
void VectorList<T>::erase(int the_index)
{// Delete the element whose index is theIndex.
 // Throw illegalIndex exception if no such element.
	check_index(the_index);
	element->erase(begin() + the_index);
}

template<class T>
void VectorList<T>::insert(int the_index, const T& the_element)
{// Insert theElement so that its index is theIndex.
	if (the_index < 0 || the_index > size())
	{// invalid index
		ostringstream s;
		s << "index = " << the_index << " size = " << size();
		throw IllegalIndexException(s.str());
	}

	// may throw an uncaught exception if insufficient
	// memory to resize vector
    element->insert(element->begin() + the_index, the_element);
}

template<class T>
void VectorList<T>::output(ostream& out) const
{// Put the list into the stream out.
	copy(element->begin(), element->end(), ostream_iterator<T>(cout, "  "));
}

// overload <<
template <class T>
ostream& operator<<(ostream& out, const VectorList<T>& x)
{
	x.output(out); 
	return out;
}
