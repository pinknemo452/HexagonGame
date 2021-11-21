#pragma once
#include "Board.h"
#include <iostream>

class Controller
{
	Board* board_;
public:
	bool canMove(int from_y, int from_x,int to_y,int to_x);
	bool isNeighbor(int y, int x, int neighbor_y, int neighbor_x) const;
	Controller( Board* board);
};

