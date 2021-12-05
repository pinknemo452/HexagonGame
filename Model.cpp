#include "Model.h"
#include <cmath>
#include <algorithm>
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

Controller::EvaluationAndMove Controller::minimax(int depth,int alpha,int beta ,bool maximazingPlayer)
{
    if (depth == 0 || temp->checkWin() != 0)
        return EvaluationAndMove{ .evaluation = getStaticEvaluation(temp) };
    std::pair<int, int> bestMove;
    std::pair<int, int> bestElement;
    if (maximazingPlayer) {
        int maxEval = INT_MIN;
        auto machineTilesClone = machineTiles;
        //for each child
        bool exit_flag = false;
        for (int k = 0; k < machineTilesClone.size(); ++k) {
            for (int i = -2; i < 3; i++) {
                for (int j = -2; j < 3; j++) {
                    if (i == 0 && j == 0 || (machineTilesClone[k].first + i > 8 || machineTilesClone[k].second + j > 8) || (machineTilesClone[k].first + i < 0 || machineTilesClone[k].second + j < 0))
                        continue;
                    if (canMove(machineTilesClone[k].first, machineTilesClone[k].second, machineTilesClone[k].first + i, machineTilesClone[k].second + j, temp, 3)) {

                        Board* temp_clone = new Board(*temp);
                        auto machineTilesClone = machineTiles;
                        auto humanTilesClone = humanTiles;

                        temporaryMovement(machineTilesClone[k].first, machineTilesClone[k].second, machineTilesClone[k].first + i, machineTilesClone[k].second + j, *temp, maximazingPlayer ? 3 : 2);
                        auto eval = minimax(depth - 1, alpha, beta, false);

                        machineTiles = machineTilesClone;
                        humanTiles = humanTilesClone;

                        //maxEval 
                        if (eval.evaluation > maxEval) {
                            maxEval = eval.evaluation;
                            bestMove = std::make_pair(machineTilesClone[k].first + i, machineTilesClone[k].second + j);
                            bestElement = std::make_pair(machineTilesClone[k].first, machineTilesClone[k].second);
                        }
                        alpha = std::max(alpha, eval.evaluation);
                        if (beta <= alpha) {
                            exit_flag = true;
                            break;
                        }

                        delete temp;
                        temp = new Board(*temp_clone);
                        delete temp_clone;
                    }

                }
                if (exit_flag)
                    break;
            }
            if (exit_flag)
                break;
        }
        return { .evaluation = maxEval,.from =  bestElement,.to = bestMove};
    }
    else {
        int minEval = INT_MAX;
        auto humanTilesClone = humanTiles;
        bool exit_flag = false;
        for (int k = 0; k < humanTilesClone.size(); ++k) {
            for (int i = -2; i < 3; i++) {
                for (int j = -2; j < 3; j++) {
                    if ((humanTilesClone[k].first + i > 8 || humanTilesClone[k].second + j > 8) || (humanTilesClone[k].first + i < 0 || humanTilesClone[k].second + j < 0))
                        continue;
                    if (canMove(humanTilesClone[k].first, humanTilesClone[k].second, humanTilesClone[k].first + i, humanTilesClone[k].second + j, temp, maximazingPlayer ? 3 : 2)) {

                        Board* temp_clone = new Board(*temp);
                        auto machineTilesClone = machineTiles;
                        auto humanTilesClone = humanTiles;

                        temporaryMovement(humanTilesClone[k].first, humanTilesClone[k].second, humanTilesClone[k].first + i, humanTilesClone[k].second + j, *temp, maximazingPlayer ? 3 : 2);
                        auto eval = minimax(depth - 1, alpha, beta, true);

                        machineTiles = machineTilesClone;
                        humanTiles = humanTilesClone;

                        //minEval 
                        if (eval.evaluation < minEval) {
                            minEval = eval.evaluation;
                            auto bestMove = std::make_pair(humanTilesClone[k].first + i, humanTilesClone[k].second + j);
                            auto bestElement = std::make_pair(humanTilesClone[k].first, humanTilesClone[k].second);
                        }
                        beta = std::min(beta, eval.evaluation);
                        if (beta <= alpha) {
                            exit_flag = true;
                            break;
                        }

                        delete temp;
                        temp = new Board(*temp_clone);
                        delete temp_clone;
                    }
                }
                if (exit_flag)
                    break;
            }
            if (exit_flag)
                break;
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
        if (player == 3) {
            if(std::find(machineTiles.begin(),machineTiles.end(),std::make_pair(to_y,to_x)) == machineTiles.end())
                machineTiles.push_back(std::make_pair(to_y, to_x));
        }
        else {
            if (std::find(humanTiles.begin(), humanTiles.end(), std::make_pair(to_y, to_x)) == humanTiles.end())
                humanTiles.push_back(std::make_pair(to_y, to_x));
        }
    }
    else {
        board.changeTile(to_y, to_x, player);
        if (player == 3) {
            if (std::find(machineTiles.begin(), machineTiles.end(), std::make_pair(to_y, to_x)) == machineTiles.end())
                machineTiles.push_back(std::make_pair(to_y, to_x));
        }
        else {
            if (std::find(humanTiles.begin(), humanTiles.end(), std::make_pair(to_y, to_x)) == humanTiles.end())
                humanTiles.push_back(std::make_pair(to_y, to_x));
        }
        board.changeTile(from_y, from_x, 0);
        if (player == 3) { 
            auto ip = std::remove(machineTiles.begin(), machineTiles.end(), std::make_pair(from_y, from_x)); 
            machineTiles.resize(std::distance(machineTiles.begin(), ip));
        }
        else { 
            auto ip = std::remove(humanTiles.begin(), humanTiles.end(), std::make_pair(from_y, from_x));
            humanTiles.resize(std::distance(humanTiles.begin(), ip));
        }
    }
    for (int i = -1; i < 2; i++)
        for (int j = -1; j < 2; j++) {
            //index is not out of border
            if ((to_y + i < 9 && to_x + j < 9) && (to_y + i >= 0 && to_x + j >= 0))
            {
               //enemy tile and in 1 ring
                if (board.getTile(to_y + i, to_x + j) == antiplayer && is1RingNeighbor(to_y, to_x, to_y + i, to_x + j)) {
                    board.changeTile(to_y + i, to_x + j, player);
                    if (player == 3) {
                        if (std::find(machineTiles.begin(), machineTiles.end(), std::make_pair(to_y + i, to_x + j)) == machineTiles.end())
                            machineTiles.push_back(std::make_pair(to_y + i, to_x + j));
                        auto it = std::remove(humanTiles.begin(), humanTiles.end(), std::make_pair(to_y + i, to_x + j));
                        humanTiles.resize(std::distance(humanTiles.begin(), it));
                    }
                    else {
                        if (std::find(humanTiles.begin(), humanTiles.end(), std::make_pair(to_y + i, to_x + j)) == humanTiles.end())
                            humanTiles.push_back(std::make_pair(to_y + i, to_x + j));
                        auto it = std::remove(machineTiles.begin(), machineTiles.end(), std::make_pair(to_y + i, to_x + j));
                        machineTiles.resize(std::distance(machineTiles.begin(), it));
                    }
                }
            }
        }
    
}

void Controller::Game()
{
    
    board_->draw();
    while (true)
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
        gameState = board_->checkWin();
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
        delete temp;
        temp = new Board(*board_);
        auto AIturn = minimax(3,INT_MIN,INT_MAX, true);
        temporaryMovement(AIturn.from.first, AIturn.from.second, AIturn.to.first, AIturn.to.second, *board_, 3);
        if (AIturn.from == std::make_pair(0, 0) || AIturn.to == std::make_pair(0, 0))
            throw std::exception("Wrong AI move");
        if (machineTiles.size() != board_->getRedTilesCounter() || humanTiles.size() != board_->getBlueTilesCounter())
            throw std::exception("Model and View desync");
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

    humanTiles.push_back(std::make_pair(0, 4));
    humanTiles.push_back(std::make_pair(6, 8));
    humanTiles.push_back(std::make_pair(6, 0));
}

Controller::Controller()
{
}
