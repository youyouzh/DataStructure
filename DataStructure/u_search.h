#pragma once

#include <vector>

using namespace std;

// 各种查找算法
template<class T>
int sequentialSearch(T a[], int n, const T& x)
{
	// 顺序查找数组a中值为x的位置
	int i;
	for (i = 0; i < n && a[i] != x; i++);
	if (i == n) {
		return -1;
	}
	else {
		return i;
	}
}