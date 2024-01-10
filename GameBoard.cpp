#include "GameBoard.h"
#include <iostream>

GameBoard::GameBoard(int difficulty) {
    isValidMove = true;
    initializeBoard(difficulty);
}

void GameBoard::initializeBoard(int difficulty) {
    // #是墙  P是玩家  =是玩家的目的地  当玩家位于玩家目的地上时会变为p  B是箱子  -是箱子的目的地  当箱子位于箱子目的地上时变为b  
    levels = {
            {
                    {'#', '#', '#', '#', '#'},
                    {'#', 'P', 'B', '-', '#'},
                    {'#', '=', ' ', ' ', '#'},
                    {'#', ' ', ' ', ' ', '#'},
                    {'#', ' ', ' ', ' ', '#'},
                    {'#', ' ', ' ', ' ', '#'},
                    {'#', '#', '#', '#', '#'}
            },
            {
                    {'#', '#', '#', '#', '#', '#', '#', '#'},
                    {'#', ' ', ' ', ' ', '#', '-', ' ', '#'},
                    {'#', ' ', 'B', '-', '#', 'B', ' ', '#'},
                    {'#', ' ', ' ', ' ', '#', ' ', '=', '#'},
                    {'#', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
                    {'#', ' ', ' ', ' ', '#', ' ', ' ', '#'},
                    {'#', '-', 'B', 'P', '#', 'B', ' ', '#'},
                    {'#', '#', '#', '#', '#', '#', '#', '#'}
            },
            {
                    {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
                    {'#', '=', ' ', ' ', '#', ' ', ' ', ' ', 'B', '#'},
                    {'#', ' ', ' ', ' ', '#', ' ', 'B', ' ', '-', '#'},
                    {'#', ' ', 'B', '-', '#', ' ', ' ', ' ', ' ', '#'},
                    {'#', ' ', ' ', ' ', '#', 'B', ' ', ' ', ' ', '#'},
                    {'#', 'B', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
                    {'#', '-', ' ', 'B', ' ', 'B', '-', 'B', 'P', '#'},
                    {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}
            },

    };

    currentLevel = difficulty;
    board = levels[currentLevel];
    destinations.clear();
    for (int row = 0; row < board.size(); ++row) {
        for (int col = 0; col < board[row].size(); ++col) {
            if (board[row][col] == '-') {
                destinations.emplace_back(row, col);
            }
            if (board[row][col] == 'P') {
                playerRow = row;
                playerCol = col;
            }
            if (board[row][col] == '=') {
                checkRow = row;
                checkCol = col;
            }
        }
    }

}

void GameBoard::repaintDest(){
    for (auto & destination : destinations) {
        if (board[destination.first][destination.second] != 'b'
         && board[destination.first][destination.second] != 'P') {
            board[destination.first][destination.second] = '-';
        }
    }
    if (board[checkRow][checkCol] != 'B'
        && board[checkRow][checkCol] != 'p'){
        board[checkRow][checkCol] = '=';
    }
}

void GameBoard::moveMultiBox(char direction, int boxRow, int boxCol) {
    int newBoxRow = boxRow;
    int newBoxCol = boxCol;
    switch (direction) {
        case 'W':
            newBoxRow--;
            break;
        case 'S':
            newBoxRow++;
            break;
        case 'A':
            newBoxCol--;
            break;
        case 'D':
            newBoxCol++;
            break;
    }

    if (newBoxRow >= 0 && newBoxRow < board.size() &&
        newBoxCol >= 0 && newBoxCol < board[0].size() &&
        board[newBoxRow][newBoxCol] != '#') {
            if (board[newBoxRow][newBoxCol] == 'B' || board[newBoxRow][newBoxCol] == 'b') {
                moveMultiBox(direction,newBoxRow,newBoxCol);
                if (isValidMove) {
                    board[boxRow][boxCol] = ' ';
                    if (board[newBoxRow][newBoxCol] == '-') {
                        board[newBoxRow][newBoxCol] = 'b';
                    } else {
                        board[newBoxRow][newBoxCol] = 'B';
                    }
                }
            }else {
                board[boxRow][boxCol] = ' ';
                if (board[newBoxRow][newBoxCol] == '-'){
                    board[newBoxRow][newBoxCol] = 'b';
                } else {
                    board[newBoxRow][newBoxCol] = 'B';
                }
            }
    }else {
        this->isValidMove = false;
        std::cout << "Invalid move. Try again.\n";
    }
    repaintDest();
}

void GameBoard::movePlayer(char direction) {
    int newPlayerRow = playerRow;
    int newPlayerCol = playerCol;
    // 根据方向更新玩家的位置
    switch (direction) {
        case 'W':
            newPlayerRow--;
            break;
        case 'S':
            newPlayerRow++;
            break;
        case 'A':
            newPlayerCol--;
            break;
        case 'D':
            newPlayerCol++;
            break;
        default:
            std::cout << "Invalid direction. Try again.\n";
            return;
    }
    // 检查新位置是否合法
    if (newPlayerRow >= 0 && newPlayerRow < board.size() &&
        newPlayerCol >= 0 && newPlayerCol < board[0].size() &&
        board[newPlayerRow][newPlayerCol] != '#') {

        isValidMove = true;
        // 如果新位置是箱子
        if (board[newPlayerRow][newPlayerCol] == 'B' || board[newPlayerRow][newPlayerCol] == 'b') {

            int newBoxRow = newPlayerRow + (newPlayerRow - playerRow);
            int newBoxCol = newPlayerCol + (newPlayerCol - playerCol);

            if (newBoxRow >= 0 && newBoxRow < board.size() &&
                newBoxCol >= 0 && newBoxCol < board[0].size() &&
                board[newBoxRow][newBoxCol] != '#') {
                // 如果箱子移动方向紧挨着另一个箱子
                if (board[newBoxRow][newBoxCol] == 'B' || board[newBoxRow][newBoxCol] == 'b'){
                    // 递归判断另一个箱子是否能移动，如果能则移动，不能将isValidMove设为false
                    moveMultiBox(direction,newBoxRow,newBoxCol);
                }
                if (isValidMove) {
                    if (board[newBoxRow][newBoxCol] == '-') {
                        // 箱子推到了目的地，更改表示
                        board[newBoxRow][newBoxCol] = 'b';
                    } else {
                        board[newBoxRow][newBoxCol] = 'B';
                    }


                    if (newPlayerRow == checkRow && newPlayerCol == checkCol) {
                        board[newPlayerRow][newPlayerCol] = 'p';
                    } else {
                        board[newPlayerRow][newPlayerCol] = 'P';
                    }

                    board[playerRow][playerCol] = ' ';
                    playerRow = newPlayerRow;
                    playerCol = newPlayerCol;
                }
            } else {
                std::cout << "Cannot push the box. Try again.\n";
            }
        } else {
            // 更新游戏板状态，移动玩家
            board[playerRow][playerCol] = ' ';
            playerRow = newPlayerRow;
            playerCol = newPlayerCol;
            if (newPlayerRow == checkRow && newPlayerCol == checkCol){
                board[newPlayerRow][newPlayerCol] = 'p';
            } else {
                board[newPlayerRow][newPlayerCol] = 'P';
            }
        }
    } else {
        std::cout << "Invalid move. Try again.\n";
    }
    repaintDest();
}



void GameBoard::printBoard(int difficulty) const {
    std::cout << "Current level: " << difficulty+1  << std::endl;
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[0].size(); j++) {
            std::cout << board[i][j] << ' ';
        }
        switch (i) {
            case 0:
                std::cout << " | P: Player  p: Player on checkpoint  |";
                break;
            case 1:
                std::cout << " | B: Box  b: Box on storage point     |";
                break;
            case 2:
                std::cout << " | =: Checkpoint  -: Storage point     |";
                break;
            case 3:
                std::cout << " | #: Wall                             |";
                break;
            case 4:
                std::cout << " | R: Restart                          |";
                break;
            case 5:
                std::cout << " | Q: Quit(Back to menu)               |";
                break;
            case 6:
                std::cout << " | W/A/S/D: Move                       |";
                break;
            default:
                break;
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}


bool GameBoard::isGameOver() const {
    for (const auto & destination : destinations) {
        if (board[destination.first][destination.second] != 'b'){
            return false;
        }
    }
    if (board[checkRow][checkCol] != 'p'){
        return false;
    }
    return true;
}


