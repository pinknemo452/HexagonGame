#pragma once
#include "Point.h"
#include "IController.h"
#include <vector>
#include <iostream>


class Board
{
	std::vector < std::vector<int>> board_;
	int blueTilesCounter_;
	int redTilesCounter_;
	int freeTilesCounter_;
	const int redTile = 3;
	const int blueTile = 2;
	const int blackTile = 1;
	const int freeTile = 0;
	const int unreachableTile = -1;
	IController* model_;
	Board() = default;
public:
	Board(IController* model);
	void start();
	void draw() const;
	int getTile(int y, int x) const;
	int getBlueTilesCounter() const;
	int getRedTilesCounter() const;
	int getFreeTilesCounter() const;
	void save();
	void load();
	void changeTile(int y, int x, int value);
	void incBlueTilesCounterBy(int add);
	void decBlueTilesCounterBy(int sub);
	void incRedTilesCounterBy(int add);
	void decRedTilesCounterBy(int sub);
	void incFreeTilesCounterBy(int add);
	void decFreeTilesCounterBy(int sub);
	int checkWin();
	std::pair<std::pair<int, int>, std::pair<int, int>> getPlayerInput();
	Board(const Board& board);
};

