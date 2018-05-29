// winner tree as a complete binary tree mapped into an array
// derives from the ADT winnerTree

#pragma once

#include <iostream>
#include "winner_tree.h"
#include "u_exception.h"

template <class T>
class CompleteWinnerTree : public WinnerTree<T>
{
public:
	CompleteWinnerTree(T *player, int number_of_players);
	~CompleteWinnerTree();

	void initialize(T* player, int number) override;
	int winner() const override;
	int winner(int i) const;
	void replay(int player) override;
	void output() const;

private:
	// lowest level external nodes
	int lowest_level;
	// 2^log(n-1) - 1
	int offset;
	// array for winner tree
	int *tree;
	int number_of_players;
	// array of players
	T *player;
	// Simulation competition process
	void play(int, int, int);
};

template <class T>
CompleteWinnerTree<T>::CompleteWinnerTree(T* player, int number_of_players)
{
	tree = nullptr;
	initialize(player, number_of_players);
}

template <class T>
CompleteWinnerTree<T>::~CompleteWinnerTree()
{
	delete[] tree;
}

template <class T>
void CompleteWinnerTree<T>::initialize(T* player, int number_of_players)
{
	// Create winner tree for thePlayer[1:numberOfPlayers].
	if (number_of_players < 2)
	{
		throw IllegalParameterValueException("must have at least 2 players");
	}
	this->player = player;
	this->number_of_players = number_of_players;
	if (tree != nullptr)
	{
		delete[] tree;
	}
	this->tree = new int[number_of_players];

	auto i = 0;
	auto s = 0;
	// compute s = 2^log (n-1)
	for (s = 1; 2 * s <= number_of_players - 1; s += s);
	lowest_level = 2 * (number_of_players - s);
	offset = 2 * s - 1;

	// play matches for lowest-level external nodes
	for ( i = 2; i <= lowest_level; i += 2)
	{
		play((offset + i) / 2, i - 1, i);
	}

	// handle remaining external nodes
	if (number_of_players % 2 == 1)
	{   // special case for add n, play internal and external node
		play(number_of_players / 2, tree[number_of_players - 1], lowest_level + 1);
		i = lowest_level + 3;
	}
	else
	{
		i = lowest_level + 2;
	}

	// i is left-most remaining external node
	for (; i <= number_of_players; i += 2)
	{
		play((i - lowest_level + number_of_players - 1) / 2, i - 1, i);
	}
}

template <class T>
int CompleteWinnerTree<T>::winner() const
{
	return tree[1];
}

template <class T>
int CompleteWinnerTree<T>::winner(int i) const
{
	return (i < number_of_players) ? tree[i] : 0;
}

template <class T>
void CompleteWinnerTree<T>::replay(int player)
{
	// Replay matches for player thePlayer.
	if (player <= 0 || player > number_of_players)
	{
		throw IllegalParameterValueException("Player index is illegal");
	}

	auto match_node = 0,   // node where next match is to be played
		left_child = 0,   // left child of match_node
		right_child = 0;  // right child of match_node

	// find first match node and its children
	if (this->player <= lowest_level)
	{
		// begin at lowest level
		match_node = (offset + player) / 2;
		left_child = 2 * match_node - offset;
		right_child = left_child + 1;
	}
	else
	{
		match_node = (player - lowest_level + number_of_players - 1) / 2;
		if (2 * match_node == number_of_players - 1)
		{
			left_child = tree[2 * match_node];
			right_child = player;
		}
		else
		{
			left_child = 2 * match_node - number_of_players + 1 + lowest_level;
			right_child = left_child + 1;
		}
	}

	tree[match_node] = (this->player[left_child] <= this->player[right_child]) ? left_child : right_child;
	// special case for second match
	if (match_node == number_of_players - 1 && number_of_players % 2 == 1)
	{
		match_node /= 2;
		tree[match_node] = (this->player[tree[number_of_players - 1]] <= this->player[lowest_level + 1]) ?
			tree[number_of_players - 1] : lowest_level + 1;
	}

	// play remaining matches
	match_node /= 2;  // move to parent
	for (; match_node >= 1; match_node /= 2)
	{
		tree[match_node] = (this->player[tree[2 * match_node]] <= this->player[tree[2 * match_node + 1]]) ?
			tree[2 * match_node] : tree[2 * match_node + 1];
	}
}

template <class T>
void CompleteWinnerTree<T>::output() const
{
	std::cout << "number of players  = " << number_of_players
		<< " lowExt = " << lowest_level
		<< " offset = " << offset << std::endl;
	std::cout << "complete winner tree pointers are" << std::endl;
	for (auto i = 1; i < number_of_players; i++)
	{
		std::cout << tree[i] << ' ';
	}
	std::cout << std::endl;
}

template <class T>
void CompleteWinnerTree<T>::play(int p, int left_child, int right_child)
{
	// play matches beginning at tree[p]
	// leftChild is left child of p
	// rightChild is right child of p
	tree[p] = (player[left_child] <= player[right_child]) ? left_child : right_child;

	// more matches possible if at right child
	while (p % 2 == 1 && p > 1)
	{ // at a right child
		tree[p / 2] = (player[tree[p - 1]] <= player[tree[p]]) ? tree[p - 1] : tree[p];
		p /= 2;
	}
}
