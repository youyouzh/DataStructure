线性表

## 概述
### 定义
线性表（linear list）也称为有序表，一个线性表是n个具有相同特性的数据元素的有限序列，它的每一个实例都是元素的一个有序集合。

线性表是最基本、最简单、也是最常用的一种数据结构。

### 基本操作
一个线性表应该具有一系列基本方法，可以用下面的抽象数据类型来进行描述：
```c++
// 线性表的抽象数据描述

#ifndef LINEAR_LIST
#define LINEAR_LIST

#include <ostream>

template<class T>
class LinearList
{
   public:
	// 若表为空，则返回true，否则返回false
    virtual bool empty() const = 0;

	// 返回线性表的大小（元素个数）
    virtual int size() const = 0;
      
	// 返回线性表中索引为index的元素
    virtual T& get(int index) const = 0;
      
	// 返回线性表中第一次出现的element的索引，如果element不存在，则返回-1
    virtual int index_of(const T& element) const = 0;

	// 删除索引为index的元素，索引大于index的元素其索引减1（往前移动一个位置）
    virtual void erase(int index) = 0;
      
	// 将element插入线性表中索引为index的位置上，索引大于或等于index的元素其索引加1（往后移动一个位置）
    virtual void insert(int index, const T& element) = 0;

	// 从左到右输出表元素
    virtual void output(std::ostream& out) const = 0;
};

#endif
```

### 特性
线性表有下列特性：

- 在非空表中每个数据元素都有一个确定的位置
- 线性表的相邻元素之间存在着序偶关系
- 线性表中必存在唯一的一个“第一元素”
- 线性表中必存在唯一的一个“最后元素”
- 除最后一个元素之外，其他元素均有唯一的后继(后件)
- 除第一个元素之外，其他元素均有唯一的前驱(前件)
- 一个数据元素可由多个数据项组成

## 数组描述的线性表
可以使用数组来存储线性表元素，简单的可以如下所示描述线性表：

- 使用一维数组来存储表元素
- 使用数组的顺序下标来描述线性表的元素顺序
- 使用变量`list_size`来记录当前存储的线性表元素个数
- 使用`array_length`描述数组长度
- 通过为数组动态分配内存来存储元素，当数组空间不足是，动态倍增数组长度

相应的具体实现可以参考以下代码实现细节：[array_list.h](https://github.com/youyouzh/DataStructure/blob/master/DataStructure/array_list.h)

## `vector`描述
在C++中，可以使用STL提供的技术数组的类`vector`来描述线性表，这个类已经提供了丰富的对数组的操作，我们只需要将它们封装成线性表的通用方法即可。

具体实现可以参考：[vector_list](https://github.com/youyouzh/DataStructure/blob/master/DataStructure/vector_list.h)

## 单向链表描述的线性表
在链式描述中：

- 数据对象实例的每一个元素都用一个单元或节点来描述
- 每一个节点都明确包含另一个相关节点的位置信息
- 使用节点的关联信息（指针，链）来描述元素之间的顺序

单向链表描述线性表的实现参考：[chain.h](https://github.com/youyouzh/DataStructure/blob/master/DataStructure/chain.h)

## 性能比较
`array`,`vector`,`chain`描述的线性表，在内存和空间的比较有如下优劣关系：

- `array`空间满是倍增，占有率不住25%时，减半，`vector`按照1.5倍倍增，链表不会有数据冗余
- 应用设计选择描述方法时，三者在空间需求上的差异不是决定性因素
- 链表`get()`时间复杂度`O(list_size)`,其他为`O(1)`
- `index_of`链表用时大约是`array`的6倍
- 插入和删除时，链表用时大约是`array`	的33倍和46倍
- 列表的插入位置随机，访问内存随机，导致高速缓存失效
- 因为数组描述时，数组元素的访问是连续内存空间，会比链表快很多
- 尽管链表在性能上表现不好，但是链表可以描述一些复杂数据结构，他们表现比数组优秀

## 栈
栈是一种特殊的线性表，其插入和删除操作都在表的同一端进行，这一端称为栈顶，另一端称为栈底。满足先进后出(FILO)原则。

栈的抽象数据描述如下：
```c++
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
```
栈和线性表类似也可以有多种描述方式：

- `array`描述方式实现参考：[arrah_stack.h](https://github.com/youyouzh/DataStructure/blob/master/DataStructure/array_stack.h)
- `chain`描述方式实现参考：[linked_stack.h](https://github.com/youyouzh/DataStructure/blob/master/DataStructure/linked_stack.h)
- 从线性表派生的实现方式参考：[derived_array_stack.h](https://github.com/youyouzh/DataStructure/blob/master/DataStructure/derived_array_stack.h),[derived_linked_stack.h](https://github.com/youyouzh/DataStructure/blob/master/DataStructure/derived_linked_stack.h)

## 队列
队列和栈一样，也是一种特殊的线性表，队列的插入和删除操作分别在线性表的两端进行，因此，队列是一个先进先出（FIFO）的线性表。

队列的抽象数据描述如下：
```c++
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
```

队列的两种实现方式参考：[array_queue.h](https://github.com/youyouzh/DataStructure/blob/master/DataStructure/array_queue.h),[linked_queue.h](https://github.com/youyouzh/DataStructure/blob/master/DataStructure/linked_queue.h)

考虑到队列的特定，我们一般使用环形的线性表来进行描述。