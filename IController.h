#pragma once
class Board;
class IController
{
public:
	virtual void Game() = 0;
	virtual void setBoard(Board* board) = 0;
};

