#pragma once

#include <string>
#include <iostream>

// custom exception
class UException : std::exception
{
public:
	explicit UException(const std::string& message = "something is error")
	{
		this->message = message;
	}
	void output_message() const { std::cout << message << std::endl; }
private:
	std::string message;
};

// illegal parameter value
class IllegalParameterValueException : public UException
{
public:
	explicit IllegalParameterValueException(const std::string& message = "Illegal parameter value")
	{
		this->message = message;
	}
private:
	std::string message;
};

// illegal index
class IllegalIndexException : UException
{
public:
	explicit IllegalIndexException(const std::string& message = "Illegal index")
	{
		this->message = message;
	}
private:
	std::string message;
};

// stack is empty
class StackEmptyException : UException
{
public:
	explicit StackEmptyException(const std::string& message = "Stack empty")
	{
		this->message = message;
	}
private:
	std::string message;
};

// queue is empty
class QueueEmptyException : UException
{
public:
	explicit QueueEmptyException(const std::string& message = "Queue empty")
	{
		this->message = message;
	}
private:
	std::string message;
}; 

// tree is empty
class EmptyTreeException : UException
{
public:
	explicit EmptyTreeException(const std::string& message = "Tree is empty")
	{
		this->message = message;
	}
private:
	std::string message;
};

// max heap is empty
class EmptyHeapException : UException
{
public:
	explicit EmptyHeapException(const std::string& message = "Heap is empty")
	{
		this->message = message;
	}
private:
	std::string message;
};

// method is undefined
class UndefinedMethodException : UException
{
public:
	explicit UndefinedMethodException(const std::string& message = "This method is undefined")
	{
		this->message = message;
	}
private:
	std::string message;
};