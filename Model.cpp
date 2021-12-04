#include "Model.h"
#include <cmath>
Controller::Controller(Board* board) {
    board_ = board;
    temp = new Board(*board_);
}

bool Controller::is1RingNeighbor(int y, int x, int neighbor_y, int neighbor_x)
{
    if (y == neighbor_y && x == neighbor_x)
        return false;
    if (std::abs(y) - std::abs(neighbor_y) >= 2 || std::abs(x) - std::abs(neighbor_x) >= 2)
        return false;
    if (x % 2 == 0) {
        if (neighbor_y - y == 0 && neighbor_x - x == -1 ||
            neighbor_y - y == -1 && neighbor_x - x == 0 ||
            neighbor_y - y == 0 && neighbor_x - x == 1 ||
            neighbor_y - y == 1 && neighbor_x - x == 1 ||
            neighbor_y - y == 1 && neighbor_x - x == 0 ||
            neighbor_y - y == 1 && neighbor_x - x == -1) {
            return true;
        }
    }
    else if (x % 2 == 1) {
        if (neighbor_y - y == -1 && neighbor_x - x == -1 ||
            neighbor_y - y == -1 && neighbor_x - x == 0 ||
            neighbor_y - y == -1 && neighbor_x - x == 1 ||
            neighbor_y - y == 0 && neighbor_x - x == 1 ||
            neighbor_y - y == 1 && neighbor_x - x == 0 ||
            neighbor_y - y == 0 && neighbor_x - x == -1) {
            return true;
        }
    }
    return false;
}

bool Controller::canMove(int from_y, int from_x, int to_y, int to_x,Board* board , int player)
{
    return isNeighbor(from_y, from_x, to_y, to_x) && board->getTile(to_y, to_x) == 0 && board->getTile(from_y, from_x) == player &&( from_y != to_y || from_x != to_x);
}

bool Controller::isNeighbor(int y, int x, int neighbor_y, int neighbor_x) const
{
    if (y == neighbor_y && x == neighbor_x)
        return false;
    if (std::abs(y) - std::abs(neighbor_y) >= 3 || std::abs(x) - std::abs(neighbor_x) >= 3)
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

int Controller::runMinMax(int recursive_level,int alpha,int beta)
{
    int evaluation = 100;
    std::pair<int, int> bestMove(100,100);
    std::pair<int, int> bestElement(100, 100);
    int Min = -100;
    if (recursive_level >= 1)
        return getStaticEvaluation(temp);
    for (int k = 0;k < machineTiles.size(); ++k) {
        for (int i = -2; i < 3; i++)
            for (int j = -2; j < 3; j++) {
                if (i == 0 && j == 0 || (machineTiles[k].first + i > 8 || machineTiles[k].second + j > 8) || (machineTiles[k].first + i < 0 || machineTiles[k].second + j < 0))
                    continue;
                if (canMove(machineTiles[k].first, machineTiles[k].second, machineTiles[k].first + i, machineTiles[k].second + j, temp, 3)) {
                    Board* temp_clone = new Board(*temp);
                    temporaryMovement(machineTiles[k].first, machineTiles[k].second, machineTiles[k].first + i, machineTiles[k].second + j, *temp, 3);
                    evaluation = runMinMax(recursive_level + 1, 0, 0);
                    
                    if (evaluation > Min) {
                        Min = evaluation;
                        bestMove = std::make_pair(machineTiles[k].first + i, machineTiles[k].second + j);
                        bestElement = std::make_pair(machineTiles[k].first,machineTiles[k].second);
                    }
                    delete temp;
                    temp = new Board(*temp_clone);
                    delete temp_clone;
                }

            }
    }
    if (bestMove == std::make_pair(100, 100))
        return getStaticEvaluation(temp);
    if (recursive_level == 0) {
        machineTiles.push_back(bestMove);
        temporaryMovement(bestElement.first, bestElement.second, bestMove.first, bestMove.second, *board_, 3);
        std::cout << bestMove.first << " " << bestMove.second;
    }
    return Min;
}

Controller::EvaluationAndMove Controller::minimax(int depth, bool maximazingPlayer)
{
    if (depth == 0 || temp->checkWin() != 0)
        return EvaluationAndMove{ .evaluation = getStaticEvaluation(temp) };
    std::pair<int, int> bestMove;
    std::pair<int, int> bestElement;
    if (maximazingPlayer) {
        int maxEval = INT_MIN;
        //for each child
        for (int k = 0; k < machineTiles.size(); ++k) {
            for (int i = -2; i < 3; i++)
                for (int j = -2; j < 3; j++) {
                    if (i == 0 && j == 0 || (machineTiles[k].first + i > 8 || machineTiles[k].second + j > 8) || (machineTiles[k].first + i < 0 || machineTiles[k].second + j < 0))
                        continue;
                    if (canMove(machineTiles[k].first, machineTiles[k].second, machineTiles[k].first + i, machineTiles[k].second + j, temp, 3)) {
                        
                        Board* temp_clone = new Board(*temp);

                        temporaryMovement(machineTiles[k].first, machineTiles[k].second, machineTiles[k].first + i, machineTiles[k].second + j, *temp, maximazingPlayer ? 3 : 2);
                        auto eval = minimax(depth - 1, false);

                        //maxEval 
                        if (eval.evaluation > maxEval) {
                            maxEval = eval.evaluation;
                            bestMove = std::make_pair(machineTiles[k].first + i, machineTiles[k].second + j);
                            bestElement = std::make_pair(machineTiles[k].first, machineTiles[k].second);
                        }
                        delete temp;
                        temp = new Board(*temp_clone);
                        delete temp_clone;
                    }

                }
        }
        return { .evaluation = maxEval,.from =  bestElement,.to = bestMove};
    }
    else {
        int minEval = INT_MAX;
        for (int k = 0; k < machineTiles.size(); ++k) {
            for (int i = -2; i < 3; i++)
                for (int j = -2; j < 3; j++) {
                    if (i == 0 && j == 0 || (machineTiles[k].first + i > 8 || machineTiles[k].second + j > 8) || (machineTiles[k].first + i < 0 || machineTiles[k].second + j < 0))
                        continue;
                    if (canMove(machineTiles[k].first, machineTiles[k].second, machineTiles[k].first + i, machineTiles[k].second + j, temp, 3)) {

                        Board* temp_clone = new Board(*temp);

                        temporaryMovement(machineTiles[k].first, machineTiles[k].second, machineTiles[k].first + i, machineTiles[k].second + j, *temp, maximazingPlayer ? 3 : 2);
                        auto eval = minimax(depth - 1, false);

                        //maxEval 
                        if (eval.evaluation < minEval) {
                            minEval = eval.evaluation;
                            auto bestMove = std::make_pair(machineTiles[k].first + i, machineTiles[k].second + j);
                            auto bestElement = std::make_pair(machineTiles[k].first, machineTiles[k].second);
                        }
                        delete temp;
                        temp = new Board(*temp_clone);
                        delete temp_clone;
                    }
                }
        }
        return { .evaluation = minEval,.from = bestElement,.to = bestMove };;
    }
}

int Controller::getStaticEvaluation(Board* board)
{
    return board->getRedTilesCounter()-board->getBlueTilesCounter();
}

void Controller::temporaryMovement(int from_y, int from_x, int to_y, int to_x, Board& board,int player)
{
    int antiplayer = player == 3 ? 2 : 3;
    int movement_type = 2;
    if (is1RingNeighbor(from_y, from_x, to_y, to_x))
        movement_type = 1;
    if (movement_type == 1) {
        board.changeTile(to_y, to_x, player);
        for (int i = -1; i < 2; i++)
            for (int j = -1; j < 2; j++) {
                //index is not out of border
                if (i != 0 && j != 0 && to_y + i < 9 && to_x + j < 9 && to_y + i >= 0 && to_x + j >= 0)
                {
                    //enemy tile and in 1 ring
                    if (board.getTile(to_y + i, to_x + j) == antiplayer && is1RingNeighbor(to_y,to_x, to_y + i, to_x + j))
                        board.changeTile(to_y + i, to_x + j, player);
                        if (player == 3) {
                            machineTiles.push_back(std::make_pair(to_y + i, to_x + j));
                        }
                        else {
                            std::remove(machineTiles.begin(), machineTiles.end(), std::make_pair(to_y + i, to_x + j)); 
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
                    if (board.getTile(to_y + i, to_x + j) == antiplayer && isNeighbor(to_y, to_x, to_y + i, to_x + j)) {
                        board.changeTile(to_y + i, to_x + j, player);
                        if (player == 3) {
                            machineTiles.push_back(std::make_pair(to_y + i, to_x + j));
                        }
                        else {
                            std::remove(machineTiles.begin(), machineTiles.end(), std::make_pair(to_y + i, to_x + j));
                        }
                    }
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
        int gameState = board_->checkWin();
        if (gameState != 0) {
            if (gameState == 3) {
                std::cout << "\nRed win\n";
            }
            if (gameState == 2) {
                std::cout << "\nBlue win\n";
            }
            if (gameState == 1) {
                std::cout << "\nDraw\n";
            }
            break;
        }
            
        auto input = board_->getPlayerInput();
        //auto input = std::make_pair(std::make_pair(6, 8), std::make_pair(5, 7));
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
        board_->draw();
        delete temp;
        temp = new Board(*board_);
        auto AIturn = minimax(3, true);
        temporaryMovement(AIturn.from.first, AIturn.from.second, AIturn.to.first, AIturn.to.second, *board_, 3);
        
        board_->draw();
    }
}

void Controller::setBoard(Board* board)
{
    board_ = board;
    temp = new Board(*board_);
    machineTiles.push_back(std::make_pair(2, 0));
    machineTiles.push_back(std::make_pair(2, 8));
    machineTiles.push_back(std::make_pair(8, 4));
}

Controller::Controller()
{
}
