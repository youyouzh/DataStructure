#pragma once

template <class T>
class WinnerTree
{
public:
	virtual ~WinnerTree() {}

	// 赢者树初始化
	virtual void initialize(T *player, int number_of_players) = 0;

	// 返回赢者的索引
	virtual int winner() const = 0;

	// 在参赛者分数变化后重赛
	virtual void replay(int player) = 0;
};