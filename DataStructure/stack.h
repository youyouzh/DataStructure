// abstract class stack
// abstract data type specification for stack data structure
// all methods are pure virtual functions

#pragma once

template <class T>
class Stack
{
public:
	virtual ~Stack() {}
	// 如果栈为空则返回true
	virtual bool empty() const = 0;

	// 返回栈中的元素个数
	virtual int size() const = 0;

	// 返回栈顶元素
	virtual T& top() = 0;

	// 删除栈顶元素（出栈）
	virtual void pop() = 0;

	// 往栈顶插入元素（入栈）
	virtual void push(const T& element) = 0;
};