// abstract class linearList
// abstract data type specification for linear list data structure
// all methods are pure virtual functions

#ifndef LINEAR_LIST
#define LINEAR_LIST

#include <ostream>

template<class T>
class LinearList
{
   public:
	// return true if list is empty
    virtual bool empty() const = 0;

	// return number of elements in list
    virtual int size() const = 0;
      
	// return element whose index is index
    virtual T& get(int index) const = 0;
      
	// return index of first occurence of element
    virtual int index_of(const T& element) const = 0;

	// remove the element whose index is index
    virtual void erase(int index) = 0;
      
	// insert element so that its index is index
    virtual void insert(int index, const T& element) = 0;

	// insert list into stream out
    virtual void output(std::ostream& out) const = 0;
};

#endif
