#include "Board.h"
#include <iostream>


Board::Board(IController* model) :board_{
	{-1,-1,-1,-1, 2,-1,-1,-1,-1},
	{-1,-1, 0, 0, 0, 0, 0,-1,-1},
	{ 3, 0, 0, 0, 0, 0, 0, 0, 3},
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{ 0, 0, 0, 1, 0, 1, 0, 0, 0},
	{ 0, 0, 0, 0, 1, 0, 0, 0, 0},
	{ 2, 0, 0, 0, 0, 0, 0, 0, 2},
	{-1, 0, 0, 0, 0, 0, 0, 0,-1},
	{-1,-1,-1, 0, 3, 0,-1,-1,-1}} 
{
	model_ = model;
	model_->setBoard(this);
	redTilesCounter_ = 3;
	blueTilesCounter_ = 3;
	freeTilesCounter_ = 52;
}


void Board::start()
{
	model_->Game();
}

void Board::draw() const
{
	std::cout << "                 ___         " << "\n";
	std::cout << "             ___/ "<<board_[0][4] <<" \\___       " << "\n";
	std::cout << "         ___/ "<<board_[1][3] <<" \\___/ "<<board_[1][5] <<" \\___     " << "\n";
	std::cout << "     ___/ "<<board_[1][2] <<" \\___/ "<<board_[1][4] <<" \\___/ "<<board_[1][6] <<" \\___   " << "\n";
	std::cout << " ___/ "<<board_[2][1] <<" \\___/ "<<board_[2][3] <<" \\___/ "<<board_[2][5] <<" \\___/ "<<board_[2][7] <<" \\___ " << "\n";
	std::cout << "/ "<<board_[2][0] <<" \\___/ "<<board_[2][2] <<" \\___/ "<<board_[2][4] <<" \\___/ "<<board_[2][6] <<" \\___/ "<<board_[2][8] <<" \\" << "\n";
	std::cout << "\\___/ "<<board_[3][1] <<" \\___/ "<<board_[3][3] <<" \\___/ "<<board_[3][5] <<" \\___/ "<<board_[3][7] <<" \\___/" << "\n";
	std::cout << "/ "<<board_[3][0] <<" \\___/ "<<board_[3][2] <<" \\___/ "<<board_[3][4] <<" \\___/ "<<board_[3][6] <<" \\___/ "<<board_[3][8] <<" \\" << "\n";
	std::cout << "\\___/ "<<board_[4][1] <<" \\___/ "<</*board_[4][3]*/ " " <<" \\___/ "<</*board_[4][5]*/ " " <<" \\___/ "<<board_[4][7] <<" \\___/" << "\n";
	std::cout << "/ "<<board_[4][0] <<" \\___/ "<<board_[4][2] <<" \\___/ "<<board_[4][4] <<" \\___/ "<<board_[4][6] <<" \\___/ "<<board_[4][8] <<" \\" << "\n";
	std::cout << "\\___/ "<<board_[5][1] <<" \\___/ "<<board_[5][3] <<" \\___/ "<<board_[5][5] <<" \\___/ "<<board_[5][7] <<" \\___/" << "\n";
	std::cout << "/ "<<board_[5][0] <<" \\___/ "<<board_[5][2] <<" \\___/ "<</*board_[5][4]*/ " " <<" \\___/ "<<board_[5][6] <<" \\___/ "<<board_[5][8] <<" \\" << "\n";
	std::cout << "\\___/ "<<board_[6][1] <<" \\___/ "<<board_[6][3] <<" \\___/ "<<board_[6][5] <<" \\___/ "<<board_[6][7] <<" \\___/" << "\n";
	std::cout << "/ "<<board_[6][0] <<" \\___/ "<<board_[6][2] <<" \\___/ "<<board_[6][4] <<" \\___/ "<<board_[6][6] <<" \\___/ "<<board_[6][8] <<" \\" << "\n";
	std::cout << "\\___/ "<<board_[7][1] <<" \\___/ "<<board_[7][3] <<" \\___/ "<<board_[7][5] <<" \\___/ "<<board_[7][7] <<" \\___/" << "\n";
	std::cout << "    \\___/ "<<board_[7][2] <<" \\___/ "<<board_[7][4] <<" \\___/ "<<board_[7][6] <<" \\___/  " << "\n";
	std::cout << "        \\___/ "<<board_[8][3] <<" \\___/ "<<board_[8][5] <<" \\___/    " << "\n";
	std::cout << "            \\___/ "<<board_[8][4] <<" \\___/      " << "\n";
	std::cout << "                \\___/        " << "\n";
}

void Board::decBlueTilesCounterBy(int sub)
{
	blueTilesCounter_ -= sub;
}

void Board::decRedTilesCounterBy(int sub)
{
	redTilesCounter_ -= sub;
}

void Board::changeTile(int y, int x, int value)
{
	board_[y][x] = value;
}

void Board::decFreeTilesCounterBy(int sub)
{
	redTilesCounter_ -= sub;
}

std::pair<std::pair<int,int>, std::pair<int,int>> Board::getPlayerInput()
{
	std::cout << "Enter you turn(from y x to y x): ";
	int i, j;
	int y, x;
	std::cin >> i >> j >> y >> x;
	return std::make_pair(std::make_pair(i,j),std::make_pair(y,x));
}

Board::Board(const Board& board):board_(board.board_)
{
	this->blueTilesCounter_ = board.blueTilesCounter_;
	this->redTilesCounter_ = board.redTilesCounter_;
	this->freeTilesCounter_ = board.freeTilesCounter_;
}

int Board::getBlueTilesCounter() const
{
	return blueTilesCounter_;
}

int Board::getRedTilesCounter() const
{
	return redTilesCounter_;
}

int Board::getFreeTilesCounter() const
{
	return freeTilesCounter_;
}

void Board::incBlueTilesCounterBy(int add)
{
	blueTilesCounter_ += add;
}

void Board::incRedTilesCounterBy(int add)
{
	redTilesCounter_ += add;
}

int Board::getTile(int y, int x) const
{
	return board_[y][x];
}

void Board::incFreeTilesCounterBy(int add)
{
	freeTilesCounter_ += add;
}