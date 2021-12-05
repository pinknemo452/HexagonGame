#pragma once
#include <iostream>
#include <vector>
#include "Board.h"

class Controller: public IController
{
	Board* board_;
	Board* temp;
	std::vector<std::pair<int, int>> machineTiles;
	std::vector<std::pair<int, int>> humanTiles;
	struct EvaluationAndMove
	{
		int evaluation;
		std::pair<int, int> from;
		std::pair<int, int> to;
	};
public:
	bool is1RingNeighbor(int y, int x, int neighbor_y, int neighbor_x);
	bool canMove(int from_y, int from_x,int to_y,int to_x, Board* board,int player);
	bool isNeighbor(int y, int x, int neighbor_y, int neighbor_x) const;
	EvaluationAndMove minimax(int depth,int alpha,int beta,bool maximazingPlayer);
	int getStaticEvaluation(Board* board);
	void temporaryMovement(int from_y,int from_x,int to_y,int to_x, Board& board, int player);
	void Game() override;
	void setBoard(Board* board) override;
	bool isPlayerCanMove();
	bool isGameOver();
	Controller();
	Controller( Board* board);
};

