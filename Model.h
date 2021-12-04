#pragma once
#include <iostream>
#include <vector>
#include "Board.h"

class Controller: public IController
{
	Board* board_;
	Board* temp;
	const int depth_ = 1;
	std::vector<std::pair<int, int>> machineTiles;
public:
	bool is1RingNeighbor(int y, int x, int neighbor_y, int neighbor_x);
	bool canMove(int from_y, int from_x,int to_y,int to_x, Board* board,int player);
	bool isNeighbor(int y, int x, int neighbor_y, int neighbor_x) const;
	int runMinMax(int recursive_level,int alpha,int beta);
	int getStaticEvaluation(Board* board);
	void temporaryMovement(int from_y,int from_x,int to_y,int to_x, Board& board, int player);
	void makeMove(int from_y, int from_x, int to_y, int to_x);
	void Game() override;
	void setBoard(Board* board) override;
	Controller();
	Controller( Board* board);
};

