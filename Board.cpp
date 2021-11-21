#include "Board.h"
#include "Hexagon.h"
#include <iostream>


Board::Board() :board{
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
	redTilesCounter_ = 3;
	blueTilesCounter_ = 3;
	freeTilesCounter_ = 52;
}

void Board::draw() const
{
	std::cout << "                 ___         " << "\n";
	std::cout << "             ___/ "<<board[0][4] <<" \\___       " << "\n";
	std::cout << "         ___/ "<<board[1][3] <<" \\___/ "<<board[1][5] <<" \\___     " << "\n";
	std::cout << "     ___/ "<<board[1][2] <<" \\___/ "<<board[1][4] <<" \\___/ "<<board[1][6] <<" \\___   " << "\n";
	std::cout << " ___/ "<<board[2][1] <<" \\___/ "<<board[2][3] <<" \\___/ "<<board[2][5] <<" \\___/ "<<board[2][7] <<" \\___ " << "\n";
	std::cout << "/ "<<board[2][0] <<" \\___/ "<<board[2][2] <<" \\___/ "<<board[2][4] <<" \\___/ "<<board[2][6] <<" \\___/ "<<board[2][8] <<" \\" << "\n";
	std::cout << "\\___/ "<<board[3][1] <<" \\___/ "<<board[3][3] <<" \\___/ "<<board[3][5] <<" \\___/ "<<board[3][7] <<" \\___/" << "\n";
	std::cout << "/ "<<board[3][0] <<" \\___/ "<<board[3][2] <<" \\___/ "<<board[3][4] <<" \\___/ "<<board[3][6] <<" \\___/ "<<board[3][8] <<" \\" << "\n";
	std::cout << "\\___/ "<<board[4][1] <<" \\___/ "<</*board[4][3]*/ " " <<" \\___/ "<</*board[4][5]*/ " " <<" \\___/ "<<board[4][7] <<" \\___/" << "\n";
	std::cout << "/ "<<board[4][0] <<" \\___/ "<<board[4][2] <<" \\___/ "<<board[4][4] <<" \\___/ "<<board[4][6] <<" \\___/ "<<board[4][8] <<" \\" << "\n";
	std::cout << "\\___/ "<<board[5][1] <<" \\___/ "<<board[5][3] <<" \\___/ "<<board[5][5] <<" \\___/ "<<board[5][7] <<" \\___/" << "\n";
	std::cout << "/ "<<board[5][0] <<" \\___/ "<<board[5][2] <<" \\___/ "<</*board[5][4]*/ " " <<" \\___/ "<<board[5][6] <<" \\___/ "<<board[5][8] <<" \\" << "\n";
	std::cout << "\\___/ "<<board[6][1] <<" \\___/ "<<board[6][3] <<" \\___/ "<<board[6][5] <<" \\___/ "<<board[6][7] <<" \\___/" << "\n";
	std::cout << "/ "<<board[6][0] <<" \\___/ "<<board[6][2] <<" \\___/ "<<board[6][4] <<" \\___/ "<<board[6][6] <<" \\___/ "<<board[6][8] <<" \\" << "\n";
	std::cout << "\\___/ "<<board[7][1] <<" \\___/ "<<board[7][3] <<" \\___/ "<<board[7][5] <<" \\___/ "<<board[7][7] <<" \\___/" << "\n";
	std::cout << "    \\___/ "<<board[7][2] <<" \\___/ "<<board[7][4] <<" \\___/ "<<board[7][6] <<" \\___/  " << "\n";
	std::cout << "        \\___/ "<<board[8][3] <<" \\___/ "<<board[8][5] <<" \\___/    " << "\n";
	std::cout << "            \\___/ "<<board[8][4] <<" \\___/      " << "\n";
	std::cout << "                \\___/        " << "\n";
}

void Board::decBlueTilesCounterBy(int sub)
{
	blueTilesCounter_ -= sub;
}

int Board::getBlueTilesCounter() const
{
	return blueTilesCounter_;
}

int Board::getRedTilesCounter() const
{
	return redTilesCounter_;
}

void Board::incBlueTilesCounterBy(int add)
{
	blueTilesCounter_ += add;
}

void Board::incRedTilesCounterBy(int add)
{
	redTilesCounter_ += add;
}
