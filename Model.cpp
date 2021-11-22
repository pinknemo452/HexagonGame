#include "Model.h"
Controller::Controller(Board* board) {
    board_ = board;
    temp = new Board(*board);
}

bool Controller::canMove(int from_y, int from_x, int to_y, int to_x)
{
    return isNeighbor(from_y, from_x, to_y, to_x) && board_->getTile(to_y, to_x) == 0;
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
        return getStaticEvaluation();
    for(int i = 0;i < 9;i++)
        for (int j = 0; j < 9; j++) {
            if (i == 0 && j == 0)
                continue;
            if (canMove(y, x, y + i, x + j)) {
                Board* temp_clone = new Board(*temp);
                temporaryMovement(y, x, y + i, x + j, *temp);
                evaluation = runMinMax(y + i, x + j, recursive_level + 1, 0, 0);
                delete temp;
                temp = new Board(*temp_clone);
                if (evaluation > Min) {
                    Min = evaluation;
                    bestMove = std::make_pair(i, j);
                }
            }

        }
    if (bestMove == std::make_pair(100, 100))
        return getStaticEvaluation();
    if (recursive_level == 0)
        temporaryMovement(y,x,bestMove.first,bestMove.second,*board_);
    return Min;
}

int Controller::getStaticEvaluation()
{
    return board_->getRedTilesCounter()-board_->getBlueTilesCounter();
}

void Controller::temporaryMovement(int from_y, int from_x, int to_y, int to_x, Board& board)
{
    int movement_type;
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
            to_y - from_y == 0 && to_x - from_x == -1)
            movement_type = 1;
    }
    else
    {
        movement_type = 2;
    }
    if (movement_type == 1) {
        board.changeTile(to_y, to_x, 3);
        for (int i = -1; i < 2; i++)
            for (int j = -1; j < 2; j++) {
                if (i != 0 && j != 0)
                {
                    if (board.getTile(to_y + i, to_x + j) == 2)
                        if (to_x % 2 == 0) {
                            if (i == -1 && j == -1 ||
                                i == -1 && j == 1) {
                            }
                            else
                            {
                                board.changeTile(to_y + i, to_x + j, 3);
                            }
                        }
                        else if (to_x % 2 == 1) {
                            if (i == 1 && j == -1 ||
                                i == 1 && j == 1){ }
                            else
                            {
                                board.changeTile(to_y + i, to_x + j, 3);
                            }
                        }
                }
            }
    }
    if (movement_type == 2)
    {
        board.changeTile(to_y, to_x, 3);
        board.changeTile(from_y, from_x, 0);
        for (int i = -2; i < 3; i++)
            for (int j = -2; j < 3; j++)
                if (i != 0 && j != 0)
                    if (isNeighbor(to_y, to_x, to_y + i, to_x + j))
                        board.changeTile(to_y + i, to_x + j,3);
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
        if (canMove(from_y, from_x, to_y, to_x)) {
            temporaryMovement(from_y, from_x, to_y, to_x, *board_);
        }
        else
        {
            continue;
        }
        runMinMax(0, 0, 0, 0, 0);
        board_->draw();
    }
}

void Controller::setBoard(Board* board)
{
    board_ = board;
    temp = new Board(*board);
}

Controller::Controller()
{
}
