#pragma once
#include "Point.h"
#include <vector>
#include <iostream>

class Board
{
	std::vector < std::vector<int>> board;
	int blueTilesCounter_;
	int redTilesCounter_;
	int freeTilesCounter_;
	const int redTile = 3;
	const int blueTile = 2;
	const int blackTile = 1;
	const int freeTile = 0;
	const int unreachableTile = -1;
public:
	Board();
	void draw() const;
	int getBlueTilesCounter() const;
	int getRedTilesCounter() const;
	int getFreeTilesCounter() const;
	void incBlueTilesCounterBy(int add);
	void decBlueTilesCounterBy(int sub);
	void incRedTilesCounterBy(int add);
	void decRedTilesCounterBy(int add);
	void incFreeTilesCounterBy(int add);
	void decFreeTilesCounterBy(int sub);
};

