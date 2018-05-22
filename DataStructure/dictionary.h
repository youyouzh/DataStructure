// abstract class dictionary
// abstract data type specification for dictionary data structure
// all methods are pure virtual functions
// K is key type and E is value type

#pragma once

template<class K, class E>
class Dictionary
{
public:
	virtual ~Dictionary() {}

	// return true if dictionary is empty
	virtual bool empty() const = 0;

	// return number of pairs in dictionary
	virtual int size() const = 0;

	// return pointer to matching pair
	virtual std::pair<K, E>* find(const K&) const = 0;
	
	// remove matching pair
	virtual void erase(const K&) = 0;
	
	// insert a (key, value) pair into the dictionary
	virtual void insert(const std::pair<K, E>&) = 0;
};