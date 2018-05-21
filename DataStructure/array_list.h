#pragma once

#include<iostream>
#include<sstream>

#include "linear_list.h"
#include "u_exception.h"
#include "helper.h"

template <class T>
class ArrayList : public LinearList<T>
{
public:
	explicit ArrayList(int capacity = 10);
	ArrayList(const ArrayList<T>&);
	~ArrayList();

	// ADT method
	bool empty() const override;
	int size() const override;
	T& get(int index) const override;
	int index_of(const T& element) const override;
	void erase(int index) override;
	void insert(int index, const T& element) override;
	void output(std::ostream& out) const override;

	// additional method
	int capacity() const;

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
ArrayList<T>::ArrayList(int capacity)
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
ArrayList<T>::ArrayList(const ArrayList<T>& list)
{
	array_length = list.array_length;
	list_size = list.list_size;
	element = new T[array_length];

	// copy the list elements
	for (auto i = 0; i < list_size; i++)
	{
		element[i] = list.element[i];
	}
}

template <class T>
ArrayList<T>::~ArrayList()
{
	delete [] element;
}

template <class T>
bool ArrayList<T>::empty() const
{
	return list_size == 0;
}

template <class T>
int ArrayList<T>::size() const
{
	return list_size;
}

template <class T>
void ArrayList<T>::check_index(int index) const
{
	if (index < 0 || index >= list_size)
	{
		std::ostringstream s;
		s << "index = " << index << " size = " << list_size;
		throw IllegalIndexException(s.str());
	}
}

template <class T>
T& ArrayList<T>::get(int index) const
{
	// first check index, if it is illgeal, throw exception
	check_index(index);
	return element[index];
}

template <class T>
int ArrayList<T>::index_of(const T& element) const
{
	// search for theElement
	for (auto i = 0; i < list_size; i++)
	{
		if (this->element[i] == element)
		{
			return i;
		}
	}
	return -1;
}

template <class T>
void ArrayList<T>::erase(int index)
{
	// Throw illegalIndex exception if no such element.
	check_index(index);

	// valid index, shift elements with higher index
	for (auto i = index + 1; i < list_size; i++)
	{
		element[i - 1] = element[i];
	}

	// invoke destructor
	element[--list_size].~T(); 
}

template <class T>
void ArrayList<T>::insert(int index, const T& element)
{
	// check the index is invalid
	if (index < 0 || index > list_size)
	{
		std::ostringstream s;
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
	for (auto i = list_size - 1; i >= index; i--)
	{
		this->element[i + 1] = this->element[i];
	}

	this->element[index] = element;
	list_size++;
}

template <class T>
void ArrayList<T>::output(std::ostream& out) const
{
	for (auto i = 0; i < list_size; i++)
	{
		out << element[i] << "  ";
	}
}

template <class T>
int ArrayList<T>::capacity() const
{
	return array_length;
}

// overload <<
template <class T>
std::ostream& operator<<(std::ostream& out, const ArrayList<T>& list)
{
	list.output(out); 
	return out;
}