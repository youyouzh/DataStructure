#pragma once
#include <algorithm>

using namespace std;
// 各种排序算法
/*
template<class T>
void swap(T& a, T& b)
{
	T temp(a);
	a = b;
	b = temp;
}
*/
template<class T>
void selectionSort(T a[], int n)
{ // 选择排序
	bool sorted = false;
	for (int size = n; !sorted && (size > 1); size--) 
	{
		int indexOfMax = 0;
		sorted = true;
		// 查找最大元素
		for (int i = 1; i < size; i++) 
		{
			if (a[indexOfMax] <= a[i]) 
			{
				indexOfMax = i;
				sorted = false;
			}
		}

		// 移动最大元素到尾部
		swap(a[indexOfMax], a[size - 1]);
	}
}

template<class T>
void bubbleSort(T a[], int n)
{// 冒泡排序
	bool swapped = false;
	for (int i = n; !swapped && (i > 1); i--) 
	{
		// 如果扫描第一步没有交换，则有序，结束循环
		for (int j = 0; j < n - 1; j++) 
		{
			if (a[j] > a[j + 1]) 
			{
				swap(a[j], a[j + 1]);
				swapped = true;
			}
		}
	}
}

template<class T>
void countSort(T a[], int n)
{// 计数排序，按名次排序
	// 名次数组
	T rank = new T[n];
	// 初始化名次
	for (int i = 0; i < n; i++) 
	{
		rank[i] = 0;
	}

	// 比较所有元素对
	for (int i = 0; i < n; i++) 
	{
		for (int j = 1; j < n; j++) 
		{
			if (a[i] >= a[j]) 
			{
				rank[i]++;
			}
			else 
			{
				rank[j]++;
			}
		}
	}

	for (int i = 0; i < n; i++) 
	{
		// 把正确的元素移动到a[i]
		while (rank[i] != i) 
		{
			int temp = rank[i];
			swap(a[i], a[temp]);
			swap(rank[i], rank[temp]);
		}
	}
}

template<class T>
void insertionSort(T a[], int n)
{// 插入排序
	for (int i = 1; i < n; i++) 
	{ // 把a[i]插入到a[0:i-1]
		T temp = a[i];
		int j;
		for (j = i - 1; j >= 0 && temp < a[j]; j--)
		{
			// 元素往后移动一个位置
			a[j + 1] = a[j];
		}
		a[j + 1] = temp;
	}
}