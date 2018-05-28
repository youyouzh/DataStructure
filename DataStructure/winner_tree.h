#pragma once

template <class T>
class WinnerTree
{
public:
	virtual ~WinnerTree() {}

	// Ӯ������ʼ��
	virtual void initialize(T *player, int number_of_players) = 0;

	// ����Ӯ�ߵ�����
	virtual int winner() const = 0;

	// �ڲ����߷����仯������
	virtual void replay(int player) = 0;
};