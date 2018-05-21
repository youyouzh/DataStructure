#pragma once

#include "array_list.h"

template<class T>
class ArrayListWithIterator : public ArrayList<T>
{
public:
	
	// iterators to start and end of list
	class iterator;
	iterator begin()
	{
		return iterator(ArrayList<T>::element);
	}

	iterator end()
	{
		return iterator(ArrayList<T>::element + ArrayList<T>::list_size);
	}

	// iterator for arrayList
	class iterator
	{
	public:
		// typedefs required by C++ for a bidirectional iterator
		typedef std::bidirectional_iterator_tag iterator_category;
		typedef T value_type;
		typedef ptrdiff_t difference_type;
		typedef T* pointer;
		typedef T& reference;

		// constructor
		explicit iterator(T* the_position = 0) { position = the_position; }

		// dereferencing operators
		T& operator*() const { return *position; }
		T* operator->() const { return &*position; }

		// increment
		iterator& operator++()   // preincrement
		{
			++position; 
			return *this;
		}
		iterator operator++(int) // postincrement
		{
			iterator old = *this;
			++position;
			return old;
		}

		// decrement
		iterator& operator--()   // predecrement
		{
			--position; 
			return *this;
		}
		iterator operator--(int) // postdecrement
		{
			iterator old = *this;
			--position;
			return old;
		}

		// equality testing
		bool operator!=(const iterator right) const
		{
			return position != right.position;
		}
		bool operator==(const iterator right) const
		{
			return position == right.position;
		}
	protected:
		T* position;
	};  // end of iterator class
};

// overload <<
template <class T>
std::ostream& operator<<(std::ostream& out, const ArrayListWithIterator<T>& list)
{
	list.output(out);
	return out;
}