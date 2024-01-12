#include "GameBoard.h"
#include <iostream>
#include <fstream>
#include <sstream>

GameBoard::GameBoard(int difficulty) {
    isValidMove = true;
    initializeBoard(difficulty);
}

void GameBoard::initializeBoard(int difficulty) {
    // #是墙  P是玩家  =是玩家的目的地  当玩家位于玩家目的地上时会变为p  B是箱子  -是箱子的目的地  当箱子位于箱子目的地上时变为b
    // In是含有内部结构的箱子 n=1,2,3...   当含有内部结构的箱子位于目的地上变为in
    // 创建地图时如果有In,n就对应该箱子内部结构的地图的序号，后面检索地图时使用I后面的n来检索地图的,如I1箱子的内部结构的地图放在第二个
//    levels = {
//            {
//                    {
//                            {'#', '#', '#', '#', '#'},
//                            {'#', 'P', 'B', '-', '#'},
//                            {'#', '=', '.', '.', '#'},
//                            {'#', '.', '.', '.', '#'},
//                            {'#', '.', '.', '.', '#'},
//                            {'#', '.', '.', '.', '#'},
//                            {'#', '#', '#', '#', '#'}
//                    },
//            },
//            {
//                    {
//                            {'#', '#', '#', '#', '#', '#', '#', '#'},
//                            {'#', '.', '.', '.', '#', '-', '.', '#'},
//                            {'#', '.', 'B', '-', '#', 'B', '.', '#'},
//                            {'#', '.', '.', '.', '#', '.', '=', '#'},
//                            {'#', '.', '.', '.', '.', '.', '.', '#'},
//                            {'#', '.', '.', '.', '.', '.', '.', '#'},
//                            {'#', '-', 'B', 'P', 'B', 'B', '-', '#'},
//                            {'#', '#', '#', '#', '#', '#', '#', '#'}
//                    },
//            },
//            {
//                    {
//                            {"#", "#", "#", "#", "#"},
//                            {"#", "P", "B", "-", "#"},
//                            {"#", ".", ".", ".", "#"},
//                            {"#", ".", "I1", ".", "#"},
//                            {"#", ".", ".", ".", "#"},
//                            {"#", ".", ".", ".", "#"},
//                            {"#", "#", "#", "#", "#"}
//                    },
//                    {
//                            {"#", "#", "#", "#", "#", "#", "#", "#"},
//                            {"#", ".", ".", ".", "#", "-", ".", "#"},
//                            {".", ".", "B", "-", "#", "B", ".", "#"},
//                            {".", ".", ".", ".", "#", ".", ".", "#"},
//                            {".", ".", ".", ".", ".", ".", ".", "#"},
//                            {"#", ".", ".", ".", "#", ".", "=", "#"},
//                            {"#", "-", "B", ".", "#", "B", ".", "#"},
//                            {"#", "#", "#", "#", "#", "#", "#", "#"}
//                    }
//            },
//    };
//    boards = levels[difficulty];
    boards = {
            {
                    {"#", "#", "#", "#", "#"},
                    {"#", ".", "B", "-", "#"},
                    {"#", ".", ".", ".", "#"},
                    {"#", ".", "I1", "B", "#"},
                    {"#", ".", ".", "-", "#"},
                    {"#", ".", ".", ".", "#"},
                    {"#", "=", ".", ".", "#"},
                    {"#", "#", "#", "#", "#"}
            },
            {
                    {"#", "#", "#", "#", "#", "#", "#", "#"},
                    {"#", ".", ".", ".", ".", ".", ".", "#"},
                    {".", ".", ".", ".", ".", ".", ".", "#"},
                    {".", ".", ".", ".", ".", ".", ".", "#"},
                    {"B", "P", "B", "B", "b", "b", "-", "#"},
                    {"#", ".", ".", ".", ".", ".", ".", "#"},
                    {"#", ".", "I2", ".", "#", ".", ".", "#"},
                    {"#", "#", "#", "#", "#", "#", "#", "#"}
            },
            {
                    {"#", "#", "#", "#", "#", "#", "#", "#"},
                    {"#", ".", ".", ".", ".", ".", ".", "#"},
                    {".", ".", ".", ".", ".", ".", ".", "#"},
                    {".", ".", ".", ".", ".", ".", ".", "#"},
                    {"B", ".", ".", ".", "B", ".", ".", "#"},
                    {"#", ".", ".", ".", ".", ".", ".", "#"},
                    {"#", ".", ".", ".", ".", ".", ".", "#"},
                    {"#", "#", "#", "#", "#", "#", "#", "#"}
            }

    };


    destinations.clear();
    contains.clear();
    contains.emplace_back(0,1,3,2);
    contains.emplace_back(1,2,6,2);
    for (int i = 0; i < boards.size(); ++i) {
        for (int row = 0; row < boards[i].size(); ++row) {
            for (int col = 0; col < boards[i][row].size(); ++col) {
                if (boards[i][row][col] == "-" || boards[i][row][col] == "b") {
                    destinations.emplace_back(i,row, col);
                }
                if (boards[i][row][col] == "P" || boards[i][row][col] == "p") {
                    playerMap = i;
                    playerRow = row;
                    playerCol = col;
                }
                if (boards[i][row][col] == "=" || boards[i][row][col] == "p") {
                    checkMap = i;
                    checkRow = row;
                    checkCol = col;
                }
            }
        }
    }
}

//遍历所有地图检测点，如果没有箱子或玩家，则在地图上重新打印检测点
void GameBoard::repaintDest(){
    for (auto & destination : destinations) {
        if (boards[std::get<0>(destination)][std::get<1>(destination)][std::get<2>(destination)] != "b"
         && boards[std::get<0>(destination)][std::get<1>(destination)][std::get<2>(destination)] != "P"
         && boards[std::get<0>(destination)][std::get<1>(destination)][std::get<2>(destination)].substr(0,1) != "I"
         && boards[std::get<0>(destination)][std::get<1>(destination)][std::get<2>(destination)].substr(0,1) != "i") {
            boards[std::get<0>(destination)][std::get<1>(destination)][std::get<2>(destination)] = "-";
        }
    }
    if (boards[checkMap][checkRow][checkCol] != "B"
        && boards[checkMap][checkRow][checkCol] != "p"
        && boards[checkMap][checkRow][checkCol].substr(0,1) != "I"
        && boards[checkMap][checkRow][checkCol].substr(0,1) != "i"){
        boards[checkMap][checkRow][checkCol] = "=";
    }
}


//oldMap是移动前的地图,oldRow和oldCol是移动前的位置,newMap是移动后的地图,newRow和newCol是移动后的位置
//在这个函数中我们移动的是原本位于newMap上newRow和newCol位置上的普通箱子,移动到newBoxMap上newBoxRow和newBoxCol位置
void GameBoard::moveBox(char direction, int oldMap, int oldRow, int oldCol, int newMap, int newRow, int newCol) {
    int newBoxMap = newMap;
    int newBoxRow = newRow;
    int newBoxCol = newCol;
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

    if (newBoxRow >= 0 && newBoxRow < boards[newBoxMap].size() &&
        newBoxCol >= 0 && newBoxCol < boards[newBoxMap][0].size() &&
        boards[newBoxMap][newBoxRow][newBoxCol] != "#") {
        // 如果箱子移动方向紧挨着另一个箱子
        // 递归判断另一个箱子是否能移动，如果能则移动，不能将isValidMove设为false
        if (boards[newBoxMap][newBoxRow][newBoxCol] == "B" || boards[newBoxMap][newBoxRow][newBoxCol] == "b") {
            moveBox(direction, newMap, newRow, newCol, newBoxMap, newBoxRow, newBoxCol);
        } else if (boards[newBoxMap][newBoxRow][newBoxCol].substr(0,1) == "I" || boards[newBoxMap][newBoxRow][newBoxCol].substr(0,1) == "i") {
            moveInternalBox(direction, newMap, newRow, newCol, newBoxMap, newBoxRow, newBoxCol);
        }
        if (isValidMove) {
            // 移动箱子
            if (boards[newBoxMap][newBoxRow][newBoxCol] == "-") {
                boards[newBoxMap][newBoxRow][newBoxCol] = "b";
            } else {
                boards[newBoxMap][newBoxRow][newBoxCol] = "B";
            }
            boards[newMap][newRow][newCol] = ".";
            repaintDest();
        }
    } else {
        this->isValidMove = false;
        std::cout << "Cannot push the box. Try again.\n";
    }
}


// oldRow和oldCol是要进入有内部结构的玩家或箱子的原本位置,boxMap是移动前的地图,也就是箱子所在的地图,boxRow和boxCol是有内部结构的箱子的位置
void GameBoard::enterInternalBox(char direction, int oldRow, int oldCol, int boxMap, int boxRow, int boxCol){
    //boxId是获取有内部结构箱子的序号，用来找到对应的地图
    int boxId = std::stoi(boards[boxMap][boxRow][boxCol].substr(1, 2));
    int r, c;
    switch (direction) {
        case 'W': {
            r = boards[boxId].size() - 1;
            c = boards[boxId][0].size() / 2;
            break;
        }
        case 'S': {
            r = 0;
            c = boards[boxId][0].size() / 2;
            break;
        }
        case 'A': {
            r = boards[boxId].size() / 2;
            c = boards[boxId][0].size() - 1;
            break;
        }
        case 'D': {
            r = boards[boxId].size() / 2;
            c = 0;
            break;
        }
    }
    if (boards[boxId][r][c] != "#") {
        //内部箱子边缘入口处是空的
        if (boards[boxId][r][c] == ".") {
            if (boards[boxMap][oldRow][oldCol] == "P" || boards[boxMap][oldRow][oldCol] == "p") {
                boards[boxId][r][c] = "P";
                boards[playerMap][playerRow][playerCol] = ".";
                playerMap = boxId;
                playerRow = r;
                playerCol = c;
            } else if (boards[boxMap][oldRow][oldCol] == "B" || boards[boxMap][oldRow][oldCol] == "b") {
                if (boards[boxId][r][c] == "-") {
                    boards[boxId][r][c] = "p";
                } else {
                    boards[boxId][r][c] = "P";
                }
                boards[boxMap][oldRow][oldCol] = ".";
            } else if (boards[boxMap][oldRow][oldCol].substr(0,1) == "I" || boards[boxMap][oldRow][oldCol].substr(0,1) == "i") {
                if (boards[boxId][r][c] == "-") {
                    boards[boxId][r][c] = "i" + boards[boxMap][oldRow][oldCol].substr(1);
                } else {
                    boards[boxId][r][c] = "I" + boards[boxMap][oldRow][oldCol].substr(1);
                }
                boards[boxMap][oldRow][oldCol] = ".";
            }
        }
            //内部箱子边缘入口处是普通箱子
        else if (boards[boxId][r][c] == "B" || boards[boxId][r][c] == "b") {
            if (boards[boxMap][oldRow][oldCol] == "P" || boards[boxMap][oldRow][oldCol] == "p") {
                moveBox(direction, boxMap ,oldRow, oldCol, boxId, r, c);
                boards[boxId][r][c] = boards[boxMap][oldRow][oldCol];
                if (boards[boxMap][oldRow][oldCol] == "P" || boards[boxMap][oldRow][oldCol] == "p"){
                    playerMap = boxId;
                    playerRow = r;
                    playerCol = c;
                }
            } else if (boards[boxMap][oldRow][oldCol] == "B" || boards[boxMap][oldRow][oldCol] == "b") {
                moveBox(direction, boxMap, oldRow, oldCol, boxId, r, c);
                boards[boxId][r][c] = boards[boxMap][oldRow][oldCol];
                if (boards[boxMap][oldRow][oldCol] == "P" || boards[boxMap][oldRow][oldCol] == "p"){
                    playerMap = boxId;
                    playerRow = r;
                    playerCol = c;
                }
            }
        }
            //内部箱子边缘入口处是含有内部结构的箱子
        else if (boards[boxId][r][c].substr(0, 1) == "I") {
            if (boards[boxMap][oldRow][oldCol] == "P" || boards[boxMap][oldRow][oldCol] == "p") {
                moveInternalBox(direction,boxMap ,oldRow, oldCol, boxId, r, c);
                boards[boxId][r][c] = boards[boxMap][oldRow][oldCol];
                if (boards[boxMap][oldRow][oldCol] == "P" || boards[boxMap][oldRow][oldCol] == "p"){
                    playerMap = boxId;
                    playerRow = r;
                    playerCol = c;
                }
            } else if (boards[boxMap][oldRow][oldCol] == "B" || boards[boxMap][oldRow][oldCol] == "b" ||
                       boards[boxMap][oldRow][oldCol].substr(0,1) == "I" || boards[boxMap][oldRow][oldCol].substr(0,1) == "i") {
                moveInternalBox(direction, boxMap, oldRow, oldCol, boxId, r, c);
                boards[boxId][r][c] = boards[boxMap][oldRow][oldCol];
                if (boards[boxMap][oldRow][oldCol] == "P" || boards[boxMap][oldRow][oldCol] == "p"){
                    playerMap = boxId;
                    playerRow = r;
                    playerCol = c;
                }
            }
        }
        if (isValidMove){

            boards[boxMap][oldRow][oldCol] = ".";
            this->isValidMove = false;
        }
    } else {
        std::cout << "Cannot enter the box. Try again.\n";
    }
}


// oldMap是有内部结构的箱子的地图,newMap是包含有内部结构的箱子的地图,
// oldRow和oldCol是玩家或箱子原本在有内部结构的箱子中的位置,newRow和newCol是玩家或箱子走出有内部结构的箱子之后的位置
void GameBoard::leaveInternalBox(char direction, int oldMap, int oldRow, int oldCol) {
    int newMap;
    int newRow;
    int newCol;
    for (auto& tuple : contains) {
        if (std::get<1>(tuple) == oldMap) {
            newMap = std::get<0>(tuple);
            switch (direction) {
                case 'W':
                    newRow = std::get<2>(tuple) - 1;
                    newCol = std::get<3>(tuple);
                    break;
                case 'S':
                    newRow = std::get<2>(tuple) + 1;
                    newCol = std::get<3>(tuple);
                    break;
                case 'A':
                    newRow = std::get<2>(tuple);
                    newCol = std::get<3>(tuple) - 1;
                    break;
                case 'D':
                    newRow = std::get<2>(tuple);
                    newCol = std::get<3>(tuple) + 1;
                    break;
            }
            if (boards[newMap][newRow][newCol] != "#") {
                if (boards[newMap][newRow][newCol] == ".") {
                    if(boards[oldMap][oldRow][oldCol] == "P" || boards[oldMap][oldRow][oldCol] == "p") {
                        boards[newMap][newRow][newCol] = "P";
                        boards[oldMap][oldRow][oldCol] = ".";
                        playerMap = newMap;
                        playerRow = newRow;
                        playerCol = newCol;
                    }
                } else if (boards[newMap][newRow][newCol] == "B" || boards[newMap][newRow][newCol] == "b") {
                    moveBox(direction, oldMap, oldRow, oldCol, newMap, newRow, newCol);
                } else if (boards[newMap][newRow][newCol].substr(0, 1) == "I" || boards[newMap][newRow][newCol].substr(0, 1) == "i"){
                    moveInternalBox(direction, oldMap, oldRow, oldCol, newMap, newRow, newCol);
                } else {
                    boards[newMap][newRow][newCol] = "p";
                    boards[playerMap][playerRow][playerCol] = ".";
                    playerMap = newMap;
                    playerRow = newRow;
                    playerCol = newCol;
                }
            } else {
                std::cout << "Cannot leave the box. Try again.\n";
            }
        }
    }
}


//oldMap是移动前的地图,oldRow和oldCol是移动前的位置,newMap是移动后的地图,newRow和newCol是移动后的位置
//在这个函数中我们移动的是原本位于newMap上newRow和newCol位置上的有内部结构的箱子,移动到newBoxMap上newBoxRow和newBoxCol位置
void GameBoard::moveInternalBox(char direction, int oldMap, int oldRow, int oldCol, int newMap, int newRow, int newCol) {
    int boxId = std::stoi(boards[newMap][newRow][newCol].substr(1, 2));
//    int newBoxRow = newRow + (newRow - playerRow);
//    int newBoxCol = newCol + (newCol - playerCol);
    int newBoxMap = newMap;
    int newBoxRow = newRow;
    int newBoxCol = newCol;
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

    if (newBoxRow >= 0 && newBoxRow < boards[newBoxMap].size() &&
        newBoxCol >= 0 && newBoxCol < boards[newBoxMap][0].size() &&
        boards[newBoxMap][newBoxRow][newBoxCol] != "#") {
        // 如果箱子移动方向紧挨着另一个箱子
        // 递归判断另一个箱子是否能移动，如果能则移动，不能将isValidMove设为false
        if (boards[newBoxMap][newBoxRow][newBoxCol] == "B" || boards[newBoxMap][newBoxRow][newBoxCol] == "b") {
            moveBox(direction, newMap, newRow, newCol, newBoxMap, newBoxRow, newBoxCol);
        } else if (boards[newBoxMap][newBoxRow][newBoxCol].substr(0,1) == "I" || boards[newBoxMap][newBoxRow][newBoxCol].substr(0,1) == "i") {
            moveInternalBox(direction, newMap, newRow, newCol, newBoxMap, newBoxRow, newBoxCol);
        }
        if (isValidMove) {
            // 移动箱子
            if (boards[newBoxMap][newBoxRow][newBoxCol] == "-") {
                boards[newBoxMap][newBoxRow][newBoxCol] = "i" + boards[newMap][newRow][newCol].substr(1);
            } else {
                boards[newBoxMap][newBoxRow][newBoxCol] = "I" + boards[newMap][newRow][newCol].substr(1);
            }
            for (auto& tuple : contains) {
                if (std::get<1>(tuple) == boxId) {
                    std::get<2>(tuple) = newBoxRow;
                    std::get<3>(tuple) = newBoxCol;
                }
            }
            boards[newMap][newRow][newCol] = ".";
            repaintDest();
        }
    } else {
        //判断是否可以进入有内部结构的箱子
        if (boards[newBoxMap][newBoxRow][newBoxCol] == "#" &&
        (boards[newMap][newRow][newCol].substr(0, 1) == "I"
        || boards[newMap][newRow][newCol].substr(0, 1) == "i")){
            enterInternalBox(direction, playerRow, playerCol, playerMap, newRow, newCol);
        }else {
            this->isValidMove = false;
            std::cout << "Cannot enter the box. Try again.\n";
        }
    }
}


//用来实现玩家的移动逻辑
void GameBoard::movePlayer(char direction) {
    int newPlayerMap = playerMap;
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
    if (newPlayerRow >= 0 && newPlayerRow < boards[newPlayerMap].size() &&
        newPlayerCol >= 0 && newPlayerCol < boards[newPlayerMap][0].size() &&
        boards[newPlayerMap][newPlayerRow][newPlayerCol] != "#") {

        isValidMove = true;
        // 如果新位置是普通箱子
        if (boards[newPlayerMap][newPlayerRow][newPlayerCol] == "B"
        || boards[newPlayerMap][newPlayerRow][newPlayerCol] == "b") {
            moveBox(direction, playerMap, playerRow, playerCol, newPlayerMap, newPlayerRow, newPlayerCol);
            if (isValidMove){
                // 更新后面
                if (boards[newPlayerMap][newPlayerRow][newPlayerCol] == "=") {
                    boards[newPlayerMap][newPlayerRow][newPlayerCol] = "p";
                } else {
                    boards[newPlayerMap][newPlayerRow][newPlayerCol] = "P";
                }
                boards[playerMap][playerRow][playerCol] = ".";
                playerMap = newPlayerMap;
                playerRow = newPlayerRow;
                playerCol = newPlayerCol;
            }
        }
        // 如果新位置是有内部结构的箱子
        else if(boards[newPlayerMap][newPlayerRow][newPlayerCol].substr(0,1) == "I"
        || boards[newPlayerMap][newPlayerRow][newPlayerCol].substr(0,1) == "i"){
            moveInternalBox(direction, playerMap, playerRow, playerCol, newPlayerMap, newPlayerRow, newPlayerCol);
            if (isValidMove){
                // 更新后面
                if (boards[newPlayerMap][newPlayerRow][newPlayerCol] == "=") {
                    boards[newPlayerMap][newPlayerRow][newPlayerCol] = "p";
                } else {
                    boards[newPlayerMap][newPlayerRow][newPlayerCol] = "P";
                }
                boards[playerMap][playerRow][playerCol] = ".";
                playerMap = newPlayerMap;
                playerRow = newPlayerRow;
                playerCol = newPlayerCol;
            }
        }
        else {
            //旧位置更新为空
            boards[playerMap][playerRow][playerCol] = ".";
            //更新玩家新位置
            playerMap = newPlayerMap;
            playerRow = newPlayerRow;
            playerCol = newPlayerCol;
            if (boards[newPlayerMap][newPlayerRow][newPlayerCol] == "="){
                boards[newPlayerMap][newPlayerRow][newPlayerCol] = "p";
            } else {
                boards[newPlayerMap][newPlayerRow][newPlayerCol] = "P";
            }
        }
    } else {
        // 玩家走出Recursive Box
        if (newPlayerRow < 0 || newPlayerRow >= boards[newPlayerMap].size() ||
            newPlayerCol < 0 || newPlayerCol >= boards[newPlayerMap][0].size()){
            leaveInternalBox(direction, playerMap, playerRow, playerCol);
        } else {
            std::cout << "Invalid move. Try again.\n";
        }
    }
    repaintDest();
}


//打印所有地图状态
void GameBoard::printBoard(int difficulty) const {
    std::cout << "Current level: " << difficulty + 1 << std::endl;
    for (int map = 0; map < boards.size(); ++map) {
        for (int i = 0; i < boards[map].size(); i++) {
            for (int j = 0; j < boards[map][0].size(); j++) {
                std::cout << boards[map][i][j] << " ";
            }
            if (map == 0) {
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
            }
            std::cout << '\n';
        }
        std::cout << '\n';
    }
    std::cout << '\n';

}


//遍历所有地图，检查所有检测点上是否都满足有箱子，从而判断游戏是否结束
bool GameBoard::isGameOver() const {
    for (const auto & destination : destinations) {
        if (boards[std::get<0>(destination)][std::get<1>(destination)][std::get<2>(destination)] != "b"
        && boards[std::get<0>(destination)][std::get<1>(destination)][std::get<2>(destination)].substr(0,1) != "i"){
            return false;
        }
    }
    if (boards[checkMap][checkRow][checkCol] != "p"){
        return false;
    }
    return true;
}


