// 0/1��������
/*
 * ������
 * ��n����Ʒ��һ������Ϊc�ı�������n����Ʒ��ѡȡװ������Ʒ��
 * ��Ʒi������Ϊwi����ֵΪpi��
 * ����Լ����װ������Ʒ����������������������
 * ����Լ������Ʒ�ܼ�ֵ��ߵĿ���װ��
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