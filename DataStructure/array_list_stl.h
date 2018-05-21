#pragma once

// array list with stl algorithm
#include<iostream>
#include<sstream>
#include<string>
#include<algorithm>

#include "linear_list.h"
#include "u_exception.h"
#include "helper.h"

template<class T>
class ArrayListSTL : public LinearList<T>
{
public:
	explicit ArrayListSTL(int capacity = 10);
	ArrayListSTL(const ArrayListSTL<T>&);
	~ArrayListSTL();

	// ADT method
	bool empty() const override;
	int size() const override;
	T& get(int index) const override;
	int index_of(const T& element) const override;
	void erase(int index) override;
	void insert(int index, const T& element) override;
	void output(std::ostream& out) const override;

	// additional method
	int get_capacity() const;

protected:
	// throw IllegalIndexException if index invalid
	void check_index(int index) const;
	// 1D array to hold list elements
	T* element;
	// capacity of the 1D array
	int array_length;
	// number of elements in list
	int list_size;
};

template <class T>
ArrayListSTL<T>::ArrayListSTL(int capacity)
{
	if (capacity < 0)
	{
		std::ostringstream s;
		s << "Initial capacity = " << capacity << " Must be > 0";
		throw IllegalParameterValueException(s.str());
	}
	array_length = capacity;
	element = new T[array_length];
	list_size = 0;
}

template <class T>
ArrayListSTL<T>::ArrayListSTL(const ArrayListSTL<T>& list)
{
	array_length = list.array_length;
	list_size = list.list_size;
	element = new T[array_length];

	// copy the list elements
	copy(list.element, list.element + list_size, element);
}

template <class T>
ArrayListSTL<T>::~ArrayListSTL()
{
	delete[] element;
}

template <class T>
bool ArrayListSTL<T>::empty() const
{
	return list_size == 0;
}

template <class T>
int ArrayListSTL<T>::size() const
{
	return list_size;
}

template <class T>
void ArrayListSTL<T>::check_index(int index) const
{
	if (index < 0 || index >= list_size)
	{
		ostringstream s;
		s << "index = " << index << " size = " << list_size;
		throw IllegalIndexException(s.str());
	}
}

template <class T>
T& ArrayListSTL<T>::get(int index) const
{
	// first check index, if it is illgeal, throw exception
	check_index(index);
	return element[index];
}

template <class T>
int ArrayListSTL<T>::index_of(const T& element) const
{
	auto const index = static_cast<int> (find(this->element, this->element + list_size, element) - element);
	// check if theElement was found
	if (index == list_size)
	{
		// Return -1 if theElement not in list.
		return -1;
	}
	else
	{
		return index;
	}
}

template <class T>
void ArrayListSTL<T>::erase(int index)
{
	// Throw illegalIndex exception if no such element.
	check_index(index);

	// valid index, shift elements with higher index
	copy(element + index + 1, element + index,
		element + index);

	// invoke destructor
	element[--index].~T();
}

template <class T>
void ArrayListSTL<T>::insert(int const index, const T& element)
{
	// check the index is invalid
	if (index < 0 || index > list_size)
	{
		ostringstream s;
		s << "index = " << index << " size = " << list_size;
		throw IllegalIndexException(s.str());
	}

	// check the space is enough, 
	if (list_size == array_length)
	{ // no space, double capacity
		change_lenghth_1_d(this->element, array_length, 2 * array_length);
		array_length *= 2;
	}

	// shift elements right one position
	copy_backward(this->element + index, this->element + list_size, this->element + list_size + 1);

	this->element[index] = element;
	list_size++;
}

template <class T>
void ArrayListSTL<T>::output(ostream& out) const
{
	copy(element, element + list_size, ostreambuf_iterator<T>(cout, "  "));
}

template <class T>
int ArrayListSTL<T>::get_capacity() const
{
	return array_length;
}

// overload <<
template <class T>
ostream& operator<<(ostream& out, const ArrayListSTL<T>& list)
{
	list.output(out);
	return out;
}