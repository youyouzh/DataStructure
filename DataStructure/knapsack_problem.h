// 0/1背包问题
/*
 * 描述：
 * 有n个物品和一个容量为c的背包，从n个物品中选取装包的物品。
 * 物品i的重量为wi，价值为pi。
 * 可行约束：装包的物品总重量不超过背包的容量
 * 最优约束：物品总价值最高的可行装包
 */

#pragma once

template <class T>
class KnapsackProblem
{
public:
	void compute();

private:
	int n;
	T *w;
	T *p;
	T c;
};