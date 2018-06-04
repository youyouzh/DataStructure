// abstract class queue
// abstract data type specification for queue data structure
// all methods are pure virtual functions

#pragma once

template <class T>
class Queue
{
public:
	virtual ~Queue() {}
	
	// 如果队列为空则返回true
	virtual bool empty() const = 0;

	// 返回队列中的元素个数
	virtual int size() const = 0;

	// 返回队列头部的元素
	virtual T& front() = 0;

	// 返回队列尾部的元素
	virtual T& back() = 0;

	// 删除队列头部的元素（出队列）
	virtual void pop() = 0;

	// 往队列尾部插入元素（入队列）
	virtual void push(const T& element) = 0;
};