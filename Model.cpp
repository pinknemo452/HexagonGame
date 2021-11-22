#include "Model.h"
Controller::Controller(Board* board) {
    board_ = board;
    temp = new Board(*board_);
}

bool Controller::canMove(int from_y, int from_x, int to_y, int to_x,Board* board , int player)
{
    return isNeighbor(from_y, from_x, to_y, to_x) && board->getTile(to_y, to_x) == 0 && board->getTile(from_y,from_x) == player;
}

bool Controller::isNeighbor(int y, int x, int neighbor_y, int neighbor_x) const
{
    if (y == neighbor_y && x == neighbor_x)
        return false;
    if (y - neighbor_y >= 3 || x - neighbor_x >= 3)
        return false;
       
    if (x % 2 == 0)
        if (y - 1 == neighbor_y && x == neighbor_x ||
            y - 2 == neighbor_y && x == neighbor_x ||
            y + 1 == neighbor_y && x == neighbor_x ||
            y + 2 == neighbor_y && x == neighbor_x ||
            y - 1 == neighbor_y && x - 1 == neighbor_x ||
            y == neighbor_y && x - 1 == neighbor_x ||
            y == neighbor_y && x + 1 == neighbor_x ||
            y + 1 == neighbor_y && x + 1 == neighbor_x ||
            y + 1 == neighbor_y && x - 1 == neighbor_x ||
            y == neighbor_y && x - 2 == neighbor_x ||
            y + 1 == neighbor_y && x - 2 == neighbor_x ||
            y + 2 == neighbor_y && x - 1 == neighbor_x ||
            y - 1 == neighbor_y && x - 2 == neighbor_x ||
            y - 1 == neighbor_y && x + 1 == neighbor_x ||
            y - 1 == neighbor_y && x + 2 == neighbor_x ||
            y == neighbor_y && x + 2 == neighbor_x ||
            y + 1 == neighbor_y && x + 2 == neighbor_x ||
            y + 2 == neighbor_y && x + 1 == neighbor_x)
            return true;
         
    if (x % 2 == 1)
        if (y - 2 == neighbor_y && x - 1 == neighbor_x ||
            y - 2 == neighbor_y && x == neighbor_x ||
            y - 2 == neighbor_y && x + 1 == neighbor_x ||
            y - 1 == neighbor_y && x - 2 == neighbor_x ||
            y - 1 == neighbor_y && x - 1 == neighbor_x ||
            y - 1 == neighbor_y && x == neighbor_x ||
            y - 1 == neighbor_y && x + 1 == neighbor_x ||
            y - 1 == neighbor_y && x + 2 == neighbor_x ||
            y == neighbor_y && x - 2 == neighbor_x ||
            y == neighbor_y && x - 1 == neighbor_x ||
            y == neighbor_y && x + 1 == neighbor_x ||
            y == neighbor_y && x + 2 == neighbor_x ||
            y + 1 == neighbor_y && x - 2 == neighbor_x ||
            y + 1 == neighbor_y && x - 1 == neighbor_x ||
            y + 1 == neighbor_y && x == neighbor_x ||
            y + 1 == neighbor_y && x + 1 == neighbor_x ||
            y + 1 == neighbor_y && x + 2 == neighbor_x ||
            y + 2 == neighbor_y && x + 0 == neighbor_x)
            return true;
    return false;
}

int Controller::runMinMax(int y,int x,int recursive_level,int alpha,int beta)
{
    int evaluation = 100;
    std::pair<int, int> bestMove(100,100);
    int Min = -100;
    if (recursive_level >= 1)
        return getStaticEvaluation(temp);
    for(int i = 0;i < 9;i++)
        for (int j = 0; j < 9; j++) {
            if (i == 0 && j == 0 && y + i > 8 && x + j > 8 && y + i >= 0 && x + j >= 0)
                continue;
            if (canMove(y, x, y + i, x + j,temp,3)) {
                Board* temp_clone = new Board(*temp);
                temporaryMovement(y, x, y + i, x + j, *temp,3);
                evaluation = runMinMax(y + i, x + j, recursive_level + 1, 0, 0);
                delete temp;
                temp = new Board(*temp_clone);
                delete temp_clone;
                if (evaluation > Min) {
                    Min = evaluation;
                    bestMove = std::make_pair(y + i,x + j);
                }
            }

        }
    if (bestMove == std::make_pair(100, 100))
        return getStaticEvaluation(temp);
    if (recursive_level == 0)
        temporaryMovement(y,x,bestMove.first,bestMove.second,*board_,3);
    return Min;
}

int Controller::getStaticEvaluation(Board* board)
{
    return board->getRedTilesCounter()-board->getBlueTilesCounter();
}

void Controller::temporaryMovement(int from_y, int from_x, int to_y, int to_x, Board& board,int player)
{
    int antiplayer = player == 3 ? 2 : 3;
    int movement_type = 2;
    if (from_x % 2 == 0) {
        if (to_y - from_y == 0 && to_x - from_x == -1 ||
            to_y - from_y == -1 && to_x - from_x == 0 ||
            to_y - from_y == 0 && to_x - from_x == 1 ||
            to_y - from_y == 1 && to_x - from_x == 1 ||
            to_y - from_y == 1 && to_x - from_x == 0 ||
            to_y - from_y == 1 && to_x - from_x == -1) {
            movement_type = 1;

        }
    }
    else if (from_x % 2 == 1) {
        if (to_y - from_y == -1 && to_x - from_x == -1 ||
            to_y - from_y == -1 && to_x - from_x == 0 ||
            to_y - from_y == -1 && to_x - from_x == 1 ||
            to_y - from_y == 0 && to_x - from_x == 1 ||
            to_y - from_y == 1 && to_x - from_x == 0 ||
            to_y - from_y == 0 && to_x - from_x == -1) {
            movement_type = 1;
        }
    }
    if (movement_type == 1) {
        board.changeTile(to_y, to_x, player);
        for (int i = -1; i < 2; i++)
            for (int j = -1; j < 2; j++) {
                if (i != 0 && j != 0 && to_y + i < 9 && to_x + j < 9 && to_y + i >= 0 && to_x + j >= 0)
                {
                    if (board.getTile(to_y + i, to_x + j) == antiplayer)
                        if (to_x % 2 == 0) {
                            if (i == -1 && j == -1 ||
                                i == -1 && j == 1) {
                            }
                            else
                            {
                                board.changeTile(to_y + i, to_x + j, player);
                            }
                        }
                        else if (to_x % 2 == 1) {
                            if (i == 1 && j == -1 ||
                                i == 1 && j == 1){ }
                            else
                            {
                                board.changeTile(to_y + i, to_x + j, player);
                            }
                        }
                }
            }
    }
    if (movement_type == 2)
    {
        board.changeTile(to_y, to_x, player);
        board.changeTile(from_y, from_x, 0);
        for (int i = -2; i < 3; i++)
            for (int j = -2; j < 3; j++)
                if (i != 0 && j != 0 && to_y + i < 9 && to_x +j < 9 && to_y + i >= 0 && to_x + j >= 0)
                    if (board.getTile(to_y + i,to_x + j) == antiplayer && isNeighbor(to_y, to_x, to_y + i, to_x + j))
                        board.changeTile(to_y + i, to_x + j,player);
    }
}

void Controller::makeMove(int from_y, int from_x, int to_y, int to_x)
{
    int movement_type;
    if (from_x % 2 == 0) {
        if (to_y - from_y == 0 && to_x - from_x == -1 ||
            to_y - from_y == -1 && to_x - from_x == 0 ||
            to_y - from_y == 0 && to_x - from_x == 1 ||
            to_y - from_y == 1 && to_x - from_x == 1 ||
            to_y - from_y == 1 && to_x - from_x == 0 ||
            to_y - from_y == 1 && to_x - from_x == -1)
            movement_type = 1;
    }
    else if (from_x % 2 == 1) {
        if (to_y - from_y == -1 && to_x - from_x == -1 ||
            to_y - from_y == -1 && to_x - from_x == 0 ||
            to_y - from_y == -1 && to_x - from_x == 1 ||
            to_y - from_y == 0 && to_x - from_x == 1 ||
            to_y - from_y == 1 && to_x - from_x == 0 ||
            to_y - from_y == 0 && to_x - from_x == -1)
            movement_type = 1;
    }
    else
    {
        movement_type = 2;
    }
    if (movement_type == 1) {

    }
}

void Controller::Game()
{
    board_->draw();
    while (board_->getFreeTilesCounter() != 0)
    {
        auto input = board_->getPlayerInput();
        auto from = input.first;
        auto to = input.second;
        int from_y = from.first;
        int from_x = from.second;
        int to_y = to.first;
        int to_x = to.second;
        if (canMove(from_y, from_x, to_y, to_x,board_,2)) {
            temporaryMovement(from_y, from_x, to_y, to_x, *board_,2);
        }
        else
        {
            continue;
        }
        delete temp;
        temp = new Board(*board_);
        runMinMax(2, 0, 0, 0, 0);
        board_->draw();
    }
}

void Controller::setBoard(Board* board)
{
    board_ = board;
    temp = new Board(*board_);
}

Controller::Controller()
{
}
