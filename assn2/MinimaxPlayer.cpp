/*
* MinimaxPlayer.cpp
*
*  Created on: Apr 17, 2015
*      Author: wong
*/
#include <iostream>
#include <assert.h>
#include "MinimaxPlayer.h"
#include <list>
#include <tuple>
#include <algorithm>

using std::vector;

struct potStates {
	vector<OthelloBoard*> states;
	vector<int> c;
	vector<int> r;
};

potStates successor(OthelloBoard * b, char);


MinimaxPlayer::MinimaxPlayer(char symb) :
	Player(symb) {

}

MinimaxPlayer::~MinimaxPlayer() {

}

void MinimaxPlayer::get_move(OthelloBoard* b, int& col, int& row) {
	// To be filled in by you
	bool whichWay;
	
	if (this->get_symbol() == b->get_p1_symbol())
		whichWay = true;
	else
		whichWay = false;

	minimax_decision(b, col, row, whichWay);

}
void MinimaxPlayer::minimax_decision(OthelloBoard*b, int &cMove, int & rMove,bool minMax)
{
	int myRow = b->get_num_rows(), myCols = b->get_num_cols(), v = 0;
	potStates currPath;

	//For this assinment p2 is always going to be minimizing.
	if (minMax)
	{
		v = max_value(b);
		currPath = successor(b, b->get_p1_symbol());
		for (int k = 0; k < currPath.states.size(); k++)
		{
			if (v == min_value(currPath.states[k]))
			{
				cMove = currPath.c[k];
				rMove = currPath.r[k];
				printf("Minimax decided on row %d, col %d\n", rMove, cMove);

			}
		}
	}
	else
	{
		v = min_value(b);
		currPath = successor(b, b->get_p2_symbol());
		for (int k = 0; k < currPath.states.size(); k++)
		{
			if (v == max_value(currPath.states[k]))
			{
				cMove = currPath.c[k];
				rMove = currPath.r[k];
				printf("Minimax decided on row %d, col %d\n", rMove, cMove);

			}
		}
	}

}
int MinimaxPlayer::utility(OthelloBoard*b, char player)
{
	return b->count_score(player);
}
int MinimaxPlayer::min_value(OthelloBoard*b)
{
	//check if we have moves remaining
	//if NOT it's a terminal state
	char p = b->get_p2_symbol();
	
	if (!b->has_legal_moves_remaining(p))
	{
		return utility(b,p);
	}
	int v = 100000;
	potStates minSuc;
	minSuc = successor(b, p);
	int iter = minSuc.states.size();
	for (int k = 0; k < iter; k++)
	{
		v = std::min(v, max_value(minSuc.states[k]));
	}

	return v;
}
int MinimaxPlayer::max_value(OthelloBoard*b)
{
	//check if we have moves remaining
	//if NOT it's a terminal state
	char p = b->get_p1_symbol();
	if (!b->has_legal_moves_remaining(p))
	{
		return utility(b,p);
	}
	int v = -100000;
	potStates maxSuc;
	maxSuc = successor(b, p);
	int iter = maxSuc.states.size();
	for (int k = 0; k < iter; k++)
	{
		v = std::max(v, min_value(maxSuc.states[k]));
	}

	return v;

}
potStates successor(OthelloBoard* b, char symbol) {
	int col = b->get_num_cols();
	int row = b->get_num_rows();
	potStates successors;

	for (int i = 0; i < col; i++) {
		for (int j = 0; j < row; j++) {
			if (b->is_legal_move(i, j, symbol)) {
				OthelloBoard* newState;
				newState = new OthelloBoard(*b);

				//play the move and store it
				newState->play_move(i, j, symbol);

				//assign to struct
				successors.states.push_back(newState);
				successors.c.push_back(i);
				successors.r.push_back(j);
			}
		}
	}
	return successors;
}

MinimaxPlayer* MinimaxPlayer::clone() {
	MinimaxPlayer* result = new MinimaxPlayer(symbol);
	return result;
}
