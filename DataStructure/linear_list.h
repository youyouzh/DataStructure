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
