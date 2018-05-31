#pragma once

// 名次算法
template<class T>
void rank(T a[], int n, int r[])
{// 给数组a的n个元素拍名次，结果在r中返回

	// 初始化名次
	for (int i = 0; i < n; i++) {
		r[i] = 0;
	}

	// 比较所有元素对
	for (int i = 0; i < n; i++) {
		for (int j = 1; j < i; j++) {
			if (a[j] <= a[i]) {
				// i大则名次加一
				r[i]++;
			} 
			else {
				// j大则j名次加一
				r[j]++;
			}
		}
	}

}

template<class T>
void rankSort(T a[], int n, int r[])
{// 根据排名来进行计数排序
	T *u = new T[n];

	// 把a中元素移动到u中正确位置
	for (int i = 0; i < n; i++) {
		u[r[i]] = a[i];
	}

	// 把u中元素移回a
	for (int i = 0; i < n; i++) {
		a[i] = u[i];
	}
}