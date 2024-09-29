���Ա�

## ����
### ����
���Ա�linear list��Ҳ��Ϊ�����һ�����Ա���n��������ͬ���Ե�����Ԫ�ص��������У�����ÿһ��ʵ������Ԫ�ص�һ�����򼯺ϡ�

���Ա������������򵥡�Ҳ����õ�һ�����ݽṹ��

### ��������
һ�����Ա�Ӧ�þ���һϵ�л�������������������ĳ�����������������������
```c++
// ���Ա�ĳ�����������

#ifndef LINEAR_LIST
#define LINEAR_LIST

#include <ostream>

template<class T>
class LinearList
{
   public:
	// ����Ϊ�գ��򷵻�true�����򷵻�false
    virtual bool empty() const = 0;

	// �������Ա�Ĵ�С��Ԫ�ظ�����
    virtual int size() const = 0;
      
	// �������Ա�������Ϊindex��Ԫ��
    virtual T& get(int index) const = 0;
      
	// �������Ա��е�һ�γ��ֵ�element�����������element�����ڣ��򷵻�-1
    virtual int index_of(const T& element) const = 0;

	// ɾ������Ϊindex��Ԫ�أ���������index��Ԫ����������1����ǰ�ƶ�һ��λ�ã�
    virtual void erase(int index) = 0;
      
	// ��element�������Ա�������Ϊindex��λ���ϣ��������ڻ����index��Ԫ����������1�������ƶ�һ��λ�ã�
    virtual void insert(int index, const T& element) = 0;

	// �����������Ԫ��
    virtual void output(std::ostream& out) const = 0;
};

#endif
```

### ����
���Ա����������ԣ�

- �ڷǿձ���ÿ������Ԫ�ض���һ��ȷ����λ��
- ���Ա������Ԫ��֮���������ż��ϵ
- ���Ա��бش���Ψһ��һ������һԪ�ء�
- ���Ա��бش���Ψһ��һ�������Ԫ�ء�
- �����һ��Ԫ��֮�⣬����Ԫ�ؾ���Ψһ�ĺ��(���)
- ����һ��Ԫ��֮�⣬����Ԫ�ؾ���Ψһ��ǰ��(ǰ��)
- һ������Ԫ�ؿ��ɶ�����������

## �������������Ա�
����ʹ���������洢���Ա�Ԫ�أ��򵥵Ŀ���������ʾ�������Ա�

- ʹ��һά�������洢��Ԫ��
- ʹ�������˳���±����������Ա��Ԫ��˳��
- ʹ�ñ���`list_size`����¼��ǰ�洢�����Ա�Ԫ�ظ���
- ʹ��`array_length`�������鳤��
- ͨ��Ϊ���鶯̬�����ڴ����洢Ԫ�أ�������ռ䲻���ǣ���̬�������鳤��

��Ӧ�ľ���ʵ�ֿ��Բο����´���ʵ��ϸ�ڣ�[array_list.h](https://github.com/youyouzh/DataStructure/blob/master/DataStructure/array_list.h)

## `vector`����
��C++�У�����ʹ��STL�ṩ�ļ����������`vector`���������Ա�������Ѿ��ṩ�˷ḻ�Ķ�����Ĳ���������ֻ��Ҫ�����Ƿ�װ�����Ա��ͨ�÷������ɡ�

����ʵ�ֿ��Բο���[vector_list](https://github.com/youyouzh/DataStructure/blob/master/DataStructure/vector_list.h)

## �����������������Ա�
����ʽ�����У�

- ���ݶ���ʵ����ÿһ��Ԫ�ض���һ����Ԫ��ڵ�������
- ÿһ���ڵ㶼��ȷ������һ����ؽڵ��λ����Ϣ
- ʹ�ýڵ�Ĺ�����Ϣ��ָ�룬����������Ԫ��֮���˳��

���������������Ա��ʵ�ֲο���[chain.h](https://github.com/youyouzh/DataStructure/blob/master/DataStructure/chain.h)

## ���ܱȽ�
`array`,`vector`,`chain`���������Ա����ڴ�Ϳռ�ıȽ����������ӹ�ϵ��

- `array`�ռ����Ǳ�����ռ���ʲ�ס25%ʱ�����룬`vector`����1.5������������������������
- Ӧ�����ѡ����������ʱ�������ڿռ������ϵĲ��첻�Ǿ���������
- ����`get()`ʱ�临�Ӷ�`O(list_size)`,����Ϊ`O(1)`
- `index_of`������ʱ��Լ��`array`��6��
- �����ɾ��ʱ��������ʱ��Լ��`array`	��33����46��
- �б�Ĳ���λ������������ڴ���������¸��ٻ���ʧЧ
- ��Ϊ��������ʱ������Ԫ�صķ����������ڴ�ռ䣬��������ܶ�
- ���������������ϱ��ֲ��ã����������������һЩ�������ݽṹ�����Ǳ��ֱ���������

## ջ
ջ��һ����������Ա�������ɾ���������ڱ��ͬһ�˽��У���һ�˳�Ϊջ������һ�˳�Ϊջ�ס������Ƚ����(FILO)ԭ��

ջ�ĳ��������������£�
```c++
#pragma once

template <class T>
class Stack
{
public:
	virtual ~Stack() {}
	// ���ջΪ���򷵻�true
	virtual bool empty() const = 0;

	// ����ջ�е�Ԫ�ظ���
	virtual int size() const = 0;

	// ����ջ��Ԫ��
	virtual T& top() = 0;

	// ɾ��ջ��Ԫ�أ���ջ��
	virtual void pop() = 0;

	// ��ջ������Ԫ�أ���ջ��
	virtual void push(const T& element) = 0;
};
```
ջ�����Ա�����Ҳ�����ж���������ʽ��

- `array`������ʽʵ�ֲο���[arrah_stack.h](https://github.com/youyouzh/DataStructure/blob/master/DataStructure/array_stack.h)
- `chain`������ʽʵ�ֲο���[linked_stack.h](https://github.com/youyouzh/DataStructure/blob/master/DataStructure/linked_stack.h)
- �����Ա�������ʵ�ַ�ʽ�ο���[derived_array_stack.h](https://github.com/youyouzh/DataStructure/blob/master/DataStructure/derived_array_stack.h),[derived_linked_stack.h](https://github.com/youyouzh/DataStructure/blob/master/DataStructure/derived_linked_stack.h)

## ����
���к�ջһ����Ҳ��һ����������Ա����еĲ����ɾ�������ֱ������Ա�����˽��У���ˣ�������һ���Ƚ��ȳ���FIFO�������Ա�

���еĳ��������������£�
```c++
#pragma once

template <class T>
class Queue
{
public:
	virtual ~Queue() {}
	
	// �������Ϊ���򷵻�true
	virtual bool empty() const = 0;

	// ���ض����е�Ԫ�ظ���
	virtual int size() const = 0;

	// ���ض���ͷ����Ԫ��
	virtual T& front() = 0;

	// ���ض���β����Ԫ��
	virtual T& back() = 0;

	// ɾ������ͷ����Ԫ�أ������У�
	virtual void pop() = 0;

	// ������β������Ԫ�أ�����У�
	virtual void push(const T& element) = 0;
};
```

���е�����ʵ�ַ�ʽ�ο���[array_queue.h](https://github.com/youyouzh/DataStructure/blob/master/DataStructure/array_queue.h),[linked_queue.h](https://github.com/youyouzh/DataStructure/blob/master/DataStructure/linked_queue.h)

���ǵ����е��ض�������һ��ʹ�û��ε����Ա�������������