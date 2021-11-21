#pragma once
#include "Board.h"
#include <iostream>
#include <vector>

class Controller
{
	Board* board_;
	Board* temp;
	const int depth_ = 1;
public:
	bool canMove(int from_y, int from_x,int to_y,int to_x);
	bool isNeighbor(int y, int x, int neighbor_y, int neighbor_x) const;
	int runMinMax(int y,int x,int recursive_level,int alpha,int beta);
	int getStaticEvaluation();
	void temporaryMovement(int from_y,int from_x,int to_y,int to_x, Board& board);
	void makeMove(int from_y, int from_x, int to_y, int to_x);
	void Game();
	Controller( Board* board);
};

