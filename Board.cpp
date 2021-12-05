#include "Board.h"
#include <string>
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
	redTilesCounter_ = 3;
	blueTilesCounter_ = 3;
	freeTilesCounter_ = 52;
	model_->setBoard(this);
}


void Board::start()
{
	model_->Game();
}
std::string getString(int value,int number) {
	std::string str2_0;
	if (value == 3)
		str2_0 = "\x1b[31m" + std::to_string(number) +"\x1b[0m";
	if (value == 2)
		str2_0 = "\x1b[34m" + std::to_string(number) + "\x1b[0m";
	if (value == 0)
		str2_0 = "\x1b[37m" + std::to_string(number) + "\x1b[0m";
	if (number < 10) {
		if (value == 3)
			str2_0 = "\x1b[31m" + std::to_string(number) + " \x1b[0m";
		if (value == 2)
			str2_0 = "\x1b[34m" + std::to_string(number) + " \x1b[0m";
		if (value == 0)
			str2_0 = "\x1b[37m" + std::to_string(number) + " \x1b[0m";
	}
	return str2_0;
}
void Board::draw() const
{
		

	std::cout << "\n";
	std::cout << "                     ____         " << "\n";
	std::cout << "                ____/ "<< getString(board_[0][4],5) <<" \\____       " << "\n";
	std::cout << "           ____/ "<< getString(board_[1][3],4) <<" \\____/ "<< getString(board_[1][5],11) <<" \\____     " << "\n";
	std::cout << "      ____/ "<< getString(board_[1][2],3) <<" \\____/ "<< getString(board_[1][4],10) <<" \\____/ "<< getString(board_[1][6],18) <<" \\____   " << "\n";
	std::cout << " ____/ "<< getString(board_[2][1],2) <<" \\____/ "<< getString(board_[2][3],9) <<" \\____/ "<< getString(board_[2][5],17) <<" \\____/ "<< getString(board_[2][7],26) <<" \\____ " << "\n";
	std::cout << "/ "<</*board_[2][0]*/getString(board_[2][0],1) <<" \\____/ "<< getString(board_[2][2],8) <<" \\____/ "<< getString(board_[2][4],16) <<" \\____/ "<< getString(board_[2][6],25) <<" \\____/ "<< getString(board_[2][8],35) <<" \\" << "\n";
	std::cout << "\\____/ "<< getString(board_[3][1],7) <<" \\____/ "<< getString(board_[3][3],15) <<" \\____/ "<< getString(board_[3][5],24) <<" \\____/ "<< getString(board_[3][7],34) <<" \\____/" << "\n";
	std::cout << "/ "<< getString(board_[3][0],6) <<" \\____/ "<< getString(board_[3][2],14) <<" \\____/ "<< getString(board_[3][4],23) <<" \\____/ "<< getString(board_[3][6],33) <<" \\____/ "<< getString(board_[3][8],43) <<" \\" << "\n";
	std::cout << "\\____/ "<< getString(board_[4][1],13) <<" \\____/ "<</*board_[4][3]*/ "  " <<" \\____/ "<</*board_[4][5]*/ "  " <<" \\____/ "<< getString(board_[4][7],42) <<" \\____/" << "\n";
	std::cout << "/ "<< getString(board_[4][0],12) <<" \\____/ "<< getString(board_[4][2],21) <<" \\____/ "<< getString(board_[4][4],31) <<" \\____/ "<< getString(board_[4][6],41) <<" \\____/ "<< getString(board_[4][8],50) <<" \\" << "\n";
	std::cout << "\\____/ "<< getString(board_[5][1],20) <<" \\____/ "<< getString(board_[5][3],30) <<" \\____/ "<< getString(board_[5][5],40) <<" \\____/ "<< getString(board_[5][7],49) <<" \\____/" << "\n";
	std::cout << "/ "<< getString(board_[5][0],19) <<" \\____/ "<< getString(board_[5][2],29) <<" \\____/ "<</*board_[5][4]*/ "  " <<" \\____/ "<< getString(board_[5][6],48) <<" \\____/ "<< getString(board_[5][8],56) <<" \\" << "\n";
	std::cout << "\\____/ "<< getString(board_[6][1],28) <<" \\____/ "<< getString(board_[6][3],38) <<" \\____/ "<< getString(board_[6][5],47) <<" \\____/ "<< getString(board_[6][7],55) <<" \\____/" << "\n";
	std::cout << "/ "<< getString(board_[6][0],27) <<" \\____/ "<< getString(board_[6][2],37) <<" \\____/ "<< getString(board_[6][4],46) <<" \\____/ "<< getString(board_[6][6],54) <<" \\____/ "<< getString(board_[6][8],61) <<" \\" << "\n";
	std::cout << "\\____/ "<< getString(board_[7][1],36) <<" \\____/ "<< getString(board_[7][3],45) <<" \\____/ "<< getString(board_[7][5],53) <<" \\____/ "<< getString(board_[7][7],60) <<" \\____/" << "\n";
	std::cout << "     \\____/ "<< getString(board_[7][2],44) <<" \\____/ "<< getString(board_[7][4],52) <<" \\____/ "<< getString(board_[7][6],59) <<" \\____/  " << "\n";
	std::cout << "          \\____/ "<< getString(board_[8][3],51) <<" \\____/ "<< getString(board_[8][5],58) <<" \\____/    " << "\n";
	std::cout << "               \\____/ "<< getString(board_[8][4],57) <<" \\____/      " << "\n";
	std::cout << "                    \\____/        " << "\n";
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
	if (board_[y][x] == 2)
		this->decBlueTilesCounterBy(1);
	if (board_[y][x] == 3)
		this->decRedTilesCounterBy(1);
	if (board_[y][x] == 0)
		this->decFreeTilesCounterBy(1);

	if (value == 2)
		this->incBlueTilesCounterBy(1);
	if (value == 3)
		this->incRedTilesCounterBy(1);
	if (value == 0)
		this->incFreeTilesCounterBy(1);

	board_[y][x] = value;

}

void Board::decFreeTilesCounterBy(int sub)
{
	freeTilesCounter_ -= sub;
}

int Board::checkWin()
{
	if (getBlueTilesCounter() == 0) {
		return 3;
	}
	if (getRedTilesCounter() == 0) {
		return 2;
	}
	if (getFreeTilesCounter() == 0) {
		return 1;
	}
	return 0;
}

//TODO: fix parser
std::pair<int,int> parse_input(int i){
	if (i >= 57)
		return std::make_pair(8 - (i - 57) / 2, 4 + (i - 57));
	else if (i >= 51)
		return std::make_pair(8 - (i - 51) / 2 - ((i - 51) % 2), 3 + (i - 51));
	else if (i >= 44)
		return std::make_pair(7 - (i - 44) / 2, 2 + (i - 44));
	else if (i >= 36)
		return std::make_pair(7 - (i - 36) / 2 -((i - 36) % 2), 1 + (i - 36));
	else if (i >= 27)
		return std::make_pair(6 - (i - 27) / 2, (i - 27));
	else if (i >= 19)
		return std::make_pair(5 - (i - 19) / 2, (i - 19));
	else if (i >= 12)
		return std::make_pair(4 - (i - 12) / 2, (i - 12));
	else if (i >= 6)
		return std::make_pair(3 - (i - 6) / 2, (i - 6));
	else {
		return std::make_pair(2 - i / 2, i - 1);
	}
}
std::pair<std::pair<int,int>, std::pair<int,int>> Board::getPlayerInput()
{
	std::cout << "Enter you turn(from  to ): ";
	int i, j;
	
	std::cin >> i >> j;
	return std::make_pair(parse_input(i),parse_input(j));
}

Board::Board(const Board& board):board_(board.board_),blueTilesCounter_(board.blueTilesCounter_),redTilesCounter_(board.redTilesCounter_),freeTilesCounter_(board.freeTilesCounter_)
{
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