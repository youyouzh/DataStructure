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

/*
 * 选择排序
 * 依次查找前k个最大元素，并移动到n-k的位置
 */
template<class T>
void selectionSort(T a[], int n)
{
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

/*
 * 冒泡排序
 * 比较相邻的元素。如果第一个比第二个大，就交换他们两个。
 * 对每一对相邻元素做同样的工作，从开始第一对到结尾的最后一对。在这一点，最后的元素应该会是最大的数。
 * 针对所有的元素重复以上的步骤，除了最后一个。
 * 持续每次对越来越少的元素重复上面的步骤，直到没有任何一对数字需要比较。
 */
template<class T>
void bubbleSort(T a[], int n)
{
	// 每次冒泡查找一次最大的数
	for (auto i = 0; i < n - 1; i++)
	{
		// 冒泡未排序的数
		for (auto j = 0; j < n - 1 - i; j++)
		{
			if (a[j] > a[j + 1])
			{
				// 一次冒泡
				swap(a[j], a[j + 1]);
			}
		}
	}
}

/*
 * 计数排序，按名次排序
 */
template<class T>
void countSort(T a[], int n)
{
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

/*
 * 插入排序
 */
template<class T>
void insertionSort(T a[], int n)
{
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

/*
 * 快速排序递归过程
 */
template<class T>
void QSortRecursion(T a[], int left, int right)
{
	if (left >= right)
	{
		return;
	}

	auto i = left;
	auto j = right + 1;
	auto key = a[left];
	while (true)
	{
		// 从左到右找比key大的值
		while (a[++i] < key)
		{
			// 如果到最右边则结束，没有比key大的数
			if (i == right)
			{
				break;
			}
		}

		// 从右向左找比key小的值
		while (a[--j] > key)
		{
			// 如果到最左边则结束，没有比key小的数
			if (i == left)
			{
				break;
			}
		}

		// 如果i和j相遇，不存在比key小且比key大的两个数
		if (i >= j)
		{
			break;
		}

		// 如果存在这样的数，则交换位置，保证左边小于右边
		swap(a[i], a[j]);
	}

	// 中枢值于j对应值交互
	swap(a[left], a[j]);

	// 递归排序左边部分
	QSortRecursion(a, left, j - 1);
	// 递归排序右边部分
	QSortRecursion(a, j + 1, right);
}

/*
* 快速排序
* 1. 设置两个变量i、j，排序开始的时候：i=0，j=N-1；
* 2. 以第一个数组元素作为关键数据，赋值给key，即key=A[0]；
* 3. 从j开始向前搜索，即由后开始向前搜索(j--)，找到第一个小于key的值A[j]，将A[j]和A[i]的值交换；
* 4. 从i开始向后搜索，即由前开始向后搜索(i++)，找到第一个大于key的A[i]，将A[i]和A[j]的值交换；
* 5. 重复第3、4步，直到i=j； (3,4步中，没找到符合条件的值，即3中A[j]不小于key,4中A[i]不大于key的时候改变j、i的值，使得j=j-1，i=i+1，直至找到为止。找到符合条件的值，进行交换的时候i， j指针位置不变。另外，i==j这一过程一定正好是i+或j-完成的时候，此时令循环结束）。
*/
template<class T>
void QSort(T a[], int n)
{
	QSortRecursion(a, 0, n);
}