#include "GameBoard.h"
#include <iostream>
#include <fstream>
#include <sstream>

GameBoard::GameBoard(int difficulty) {
    isValidMove = true;
    isEnter = false;
    isLeave = false;
    initializeBoard(difficulty);
}

GameBoard::GameBoard(std::string filename) {
    isValidMove = true;
    isEnter = false;
    isLeave = false;
    initializeBoard(filename);
}

void GameBoard::initializeBoard(int difficulty) {

    std::vector<std::vector<std::vector<std::string>>> boards1;
    boards1 = {
            {
                    {".", ".", ".", ".", "."},
                    {".", ".", ".", ".", "."},
                    {".", ".", ".", ".", "."},
                    {".", ".", ".", ".", "."},
                    {".", ".", ".", ".", "."},
                    {".", ".", ".", ".", "."},
                    {".", ".", ".", ".", "."}

            },
            {
                    {"#", "#", "#", "#", "#"},
                    {"#", "P", ".", "=", "#"},
                    {"#", ".", "I2", ".", "."},
                    {"#", ".", ".", ".", "#"},
                    {"#", "#", "#", "#", "#"}
            },
            {
                    {"#", "#", "#", "#", "#"},
                    {"#", ".", ".", ".", "#"},
                    {".", ".", "I1", ".", "#"},
                    {"#", ".", ".", ".", "#"},
                    {"#", "#", "#", "#", "#"}
            },
    };


    std::vector<std::vector<std::vector<std::string>>> boards2;
    boards2 = {
            {
                    {"#", "#", "#", "#", "#", "#", "#"},
                    {"#", ".", ".", ".", ".", ".", "#"},
                    {"#", ".", ".", ".", ".", ".", "#"},
                    {"#", "P", "I1", "I2", "B", ".", "#"},
                    {"#", ".", ".", ".", ".", ".", "#"},
                    {"#", ".", ".", ".", ".", ".", "#"},
                    {"#", "=", ".", ".", ".", ".", "#"},
                    {"#", "#", "#", "#", "#", "#", "#"}
            },
            {
                    {"#", "#", "#", "#", "#", "#", "#", "#"},
                    {"#", ".", ".", ".", ".", ".", ".", "#"},
                    {".", ".", ".", ".", ".", ".", ".", "#"},
                    {".", ".", ".", ".", ".", ".", ".", "#"},
                    {".", ".", ".", "B", "b", "-", ".", "#"},
                    {"#", ".", ".", ".", ".", ".", ".", "#"},
                    {"#", ".", ".", ".", "#", ".", ".", "#"},
                    {"#", "#", "#", "#", "#", "#", "#", "#"}
            },
            {
                    {"#", "#", "#", "#", "#", "#", "#", "#"},
                    {"#", ".", ".", ".", ".", ".", ".", "#"},
                    {".", ".", ".", ".", ".", ".", ".", "#"},
                    {".", ".", ".", ".", ".", ".", ".", "-"},
                    {".", ".", ".", "-", "-", ".", ".", "B"},
                    {"#", ".", ".", ".", ".", ".", ".", "."},
                    {"#", ".", ".", ".", ".", ".", ".", "#"},
                    {"#", "#", "#", "#", "#", "#", "#", "#"}
            }
    };

    std::vector<std::vector<std::vector<std::string>>> boards3;
    boards3 = {
            {
                    {".", ".", ".", ".", "."},
                    {".", ".", ".", ".", "."},
                    {".", ".", ".", ".", "."},
                    {".", ".", ".", ".", "."},
                    {".", ".", ".", ".", "."},
                    {".", ".", ".", ".", "."},
                    {".", ".", ".", ".", "."}
            },
            {
                    {"#", "#", "#", "#", "#", "#", "#", "#", "#"},
                    {"#", "I1", "B", "I2", "I3", "B", "B", "P", "B"},
                    {"#", "#", ".", "#", "#", "#", ".", ".", "#"},
                    {"#", "#", ".", ".", ".", ".", ".", ".", "#"},
                    {"#", "#", ".", ".", ".", ".", ".", ".", "#"},
                    {"#", "#", ".", ".", ".", ".", ".", ".", "#"},
                    {"#", "#", "#", "#", "#", "#", "#", "#", "#"},
                    {"#", "#", "#", "#", "#", "#", "#", "#", "#"}
            },
            {
                    {"#", "#", "#"},
                    {"#", "-", "#"},
                    {"#", "B", "#"}
            },
            {
                    {"#", "#", "#"},
                    {"#", "=", "#"},
                    {"#", ".", "#"}
            },
    };

    std::vector<std::vector<std::vector<std::string>>> boards4;
    boards4 = {
            {
                    {".", ".", ".", ".", "."},
                    {".", ".", ".", ".", "."},
                    {".", ".", ".", ".", "."},
                    {".", ".", ".", ".", "."},
                    {".", ".", ".", ".", "."},
                    {".", ".", ".", ".", "."},
                    {".", ".", ".", ".", "."}
            },
            {
                    {"#", "#", "#", "#"},
                    {"#", "I2", "I3", "#"},
                    {"#", "#", "#", "#"}
            },
            {
                    {"#", ".", "P"},
                    {"#", ".", "."},
                    {"#", ".", "B"}
            },
            {
                    {".", ".", "#"},
                    {".", "=", "#"},
                    {".", "-", "#"}
            },
    };
    // 地图上标志的含义
    // #是墙  P是玩家  =是玩家的检测点  当玩家位于玩家检测点上时会变为p  B是箱子  -是箱子的检测点  当箱子位于箱子检测点上时变为b
    // In是含有内部结构的箱子 n=1,2,3...   当含有内部结构的箱子位于检测点上变时为in  n=1,2,3...
    // 创建地图时如果有In,n就对应该箱子内部结构的地图的序号，后面检索地图时使用I/i后面的n来检索地图的,如I1箱子的内部结构的地图放在第二个

    destinations.clear();
    contains.clear();
    // 初始化时手动设置有内部结构的箱子的被包含关系和坐标
    // contains记录包含关系 第一个元素包含第二个元素 第一个和第二个元素是对应地图的序号
    // 第三第四个元素是第二个元素对应地图在第一个元素对应地图中的行和列
    switch (difficulty) {
        case 1:
            // Internal Structures
            boards = boards1;
            contains.emplace_back(2,1,2,2);
            contains.emplace_back(1,2,2,2);
            break;
        case 2:
            boards = boards2;
            contains.emplace_back(0,1,3,2);
            contains.emplace_back(0,2,3,3);
            break;
        case 3:
            // Greedy Snake
            boards = boards3;
            contains.emplace_back(1,1,1,1);
            contains.emplace_back(1,2,1,4);
            contains.emplace_back(1,3,1,5);
            break;
        case 4:
            // Recursive Box
            boards = boards4;
            contains.emplace_back(1,2,1,1);
            contains.emplace_back(1,3,1,2);
            break;
    }

    for (int i = 0; i < boards.size(); ++i) {
        for (int row = 0; row < boards[i].size(); ++row) {
            for (int col = 0; col < boards[i][row].size(); ++col) {
                if (boards[i][row][col] == "-" || boards[i][row][col] == "b" || boards[i][row][col].substr(0,1) == "i") {
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

void GameBoard::initializeBoard(std::string filename) {

    destinations.clear();
    contains.clear();
   
    std::ifstream inFile(filename);
    if (!inFile) {
        std::cerr << "Error: Unable to open file for loading." << std::endl;
        return;
    }

    std::string line;
    bool isReadingBoards = false;
    bool isReadingContains = false;
    std::vector<std::vector<std::string>> currentMap;

    while (getline(inFile, line)) {
        // Check for map start
        if (line.find("[Map ") != std::string::npos) {
            isReadingBoards = true;
            isReadingContains = false;
            if (!currentMap.empty()) {
                boards.push_back(currentMap);
                currentMap.clear();
            }
            continue;
        }
        // Check for map end
        if (line.find("[Map End]") != std::string::npos) {
            isReadingBoards = false;
            if (!currentMap.empty()) {
                boards.push_back(currentMap);
                currentMap.clear();
            }
            continue;
        }
        // Check for contains start
        if (line.find("[Contains]") != std::string::npos) {
            isReadingBoards = false;
            isReadingContains = true;
            continue;
        }
        // Check for contains end
        if (line.find("[Contains End]") != std::string::npos) {
            isReadingContains = false;
            continue;
        }

        // Read the current line into the appropriate data structure
        if (isReadingBoards) {
            std::istringstream iss(line);
            std::vector<std::string> row;
            std::string cell;
            while (iss >> cell) {
                row.push_back(cell);
            }
            currentMap.push_back(row);
        }
        else if (isReadingContains) {
            std::istringstream iss(line);
            int map, innerMap, row, col;
            if (iss >> map >> innerMap >> row >> col) {
                contains.emplace_back(map, innerMap, row, col);
            }
        }
    }
    inFile.close();

    for (int i = 0; i < boards.size(); ++i) {
        for (int row = 0; row < boards[i].size(); ++row) {
            for (int col = 0; col < boards[i][row].size(); ++col) {
                if (boards[i][row][col] == "-" || boards[i][row][col] == "b" || boards[i][row][col].substr(0,1) == "i") {
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

void GameBoard::saveGameToFile(const std::string& filename) {
    std::ofstream outFile(filename);
    if (!outFile) {
        std::cerr << "Error: Unable to open file for saving." << std::endl;
        return;
    }

    // 保存地图信息
    for (int i = 0; i < boards.size(); ++i) {
        outFile << "[Map " << i + 1 << "]" << std::endl;
        for (const auto& row : boards[i]) {
            for (const auto& cell : row) {
                outFile << cell << " ";
            }
            outFile << std::endl;
        }
        outFile << "[Map End]" << std::endl;
    }

    // 保存contains信息
    outFile << "[Contains]" << std::endl;
    for (const auto& contain : contains) {
        outFile << std::get<0>(contain) << " "
                << std::get<1>(contain) << " "
                << std::get<2>(contain) << " "
                << std::get<3>(contain) << std::endl;
    }
    outFile << "[Contains End]" << std::endl;

    outFile.close();
}


// 遍历所有地图检测点，如果没有箱子或玩家，则在地图上重新打印检测点
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


// oldMap是“推动者”所在的地图,oldRow和oldCol是“推动者”的位置,newMap是“被推者”所在的地图,newRow和newCol是“被推者”的位置
// 在这个函数中我们移动的是原本位于newMap上newRow和newCol位置上的普通箱子,移动到newBoxMap上newBoxRow和newBoxCol位置
// direction表示推动的方向，newBoxMap,newBoxRow和newBoxCol会在函数中根据direction计算出来
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
    // 检测箱子被推到的位置是否出界或撞墙
    if (newBoxRow >= 0 && newBoxRow < boards[newBoxMap].size() &&
        newBoxCol >= 0 && newBoxCol < boards[newBoxMap][0].size() &&
        boards[newBoxMap][newBoxRow][newBoxCol] != "#") {

        // 如果箱子移动方向紧挨着另一个箱子
        // 递归判断另一个箱子是否能移动，如果能则移动，不能将isValidMove设为false，表示前一个箱子不能移动

        // 要移动到的位置上的箱子是普通箱子
        if (boards[newBoxMap][newBoxRow][newBoxCol] == "B" || boards[newBoxMap][newBoxRow][newBoxCol] == "b") {
            moveBox(direction, newMap, newRow, newCol, newBoxMap, newBoxRow, newBoxCol);
            // 前一个位于newBoxMap上的newBoxRow和newBoxCol位置的普通箱子可以向前移动
            if (isValidMove) {
                // 移动位于newMap中位于newRow和newCol上的普通箱子到newBoxMap上的newBoxRow和newBoxCol位置
                if (boards[newBoxMap][newBoxRow][newBoxCol] == "-") {
                    boards[newBoxMap][newBoxRow][newBoxCol] = "b";
                } else {
                    boards[newBoxMap][newBoxRow][newBoxCol] = "B";
                }
                boards[newMap][newRow][newCol] = ".";
                repaintDest();
            }
        }
        // 要移动到的位置上的箱子是有内部结构的箱子
        else if (boards[newBoxMap][newBoxRow][newBoxCol].substr(0,1) == "I" || boards[newBoxMap][newBoxRow][newBoxCol].substr(0,1) == "i") {
            moveInternalBox(direction, newMap, newRow, newCol, newBoxMap, newBoxRow, newBoxCol);
            // 前面位于newBoxMap上的newBoxRow和newBoxCol位置的有内部结构的箱子可以向前移动
            // 并且当前箱子没有进入前一个有内部结构的箱子(在moveInternalBox中会判断当前现在箱子是否可以进入前面有内部结构的箱子，如果可以会执行进入)
            if (isValidMove && !isEnter) {
                // 移动位于newMap中位于newRow和newCol上的普通箱子到newBoxMap上的newBoxRow和newBoxCol位置
                if (boards[newBoxMap][newBoxRow][newBoxCol] == "-") {
                    boards[newBoxMap][newBoxRow][newBoxCol] = "b";
                } else {
                    boards[newBoxMap][newBoxRow][newBoxCol] = "B";
                }
                boards[newMap][newRow][newCol] = ".";
                repaintDest();
            }
            if (isEnter) {
                isEnter = false;
            }
        }
        // 箱子移动方向为空地或检测点
        else {
            // 移动位于newMap中位于newRow和newCol上的普通箱子到newBoxMap上的newBoxRow和newBoxCol位置
            if (boards[newBoxMap][newBoxRow][newBoxCol] == "-") {
                boards[newBoxMap][newBoxRow][newBoxCol] = "b";
            } else {
                boards[newBoxMap][newBoxRow][newBoxCol] = "B";
            }
            boards[newMap][newRow][newCol] = ".";
            repaintDest();
        }
    } else {
        // 箱子被推到的位置出界，检测能否离开有内部结构的箱子(如果在一个有内部结构的箱子内部的话)
        if (newBoxRow < 0 || newBoxRow >= boards[newBoxMap].size() ||
            newBoxCol < 0 || newBoxCol >= boards[newBoxMap][0].size()){
            leaveInternalBox(direction, newMap, newRow, newCol);
        } else {
            this->isValidMove = false;
            std::cout << "Cannot push the box. Try again.\n";
        }
    }
}


// oldRow和oldCol是要进入有内部结构的箱子的玩家或箱子的原本位置,oldMap是要进入有内部结构的箱子的玩家或箱子原来所在的地图
// 也就是玩家或箱子所在的地图(不是箱子本身对应的地图，是包含箱子的那个地图),boxRow和boxCol是要进入的有内部结构的箱子在包含箱子的地图(oldMap)中的行和列
void GameBoard::enterInternalBox(char direction, int oldRow, int oldCol, int oldMap, int boxRow, int boxCol){
    // boxId是获取有内部结构箱子的序号，用来找到对应的地图，r和c是进入有内部结构的箱子之后的位置
    this->isValidMove = true;
    int boxId;
    int r, c;
    // 根据是否离开一个有内部结构的箱子进入另一个有内部结构的箱子，判断boxId是oldMap还是包含oldMap的地图的序号
    // 并且进入另一个有内部结构的箱子的位置也需要调整，针对文档中Recursive Box的情况进行特判
    if (isLeave){
        int containMap;
        for (auto& tuple : contains) {
            if (std::get<1>(tuple) == oldMap) {
                containMap = std::get<0>(tuple);
            }
        }
        // boxId此时为包含oldMap的地图的序号
        boxId = std::stoi(boards[containMap][boxRow][boxCol].substr(1, 2));
        isLeave = false;
        // 计算从不同方向进入后，对应的进入后的位置
        switch (direction) {
            case 'W': {
                r = boards[boxId].size() - 1;
                c = oldCol;
                break;
            }
            case 'S': {
                r = 0;
                c = oldCol;
                break;
            }
            case 'A': {
                r = oldRow;
                c = boards[boxId][0].size() - 1;
                break;
            }
            case 'D': {
                r = oldRow;
                c = 0;
                break;
            }
        }
    } else {
        // boxId此时为oldMap本身地图的序号
        boxId = std::stoi(boards[oldMap][boxRow][boxCol].substr(1, 2));
        // 计算从不同方向进入后，对应的进入后的位置
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
    }

    // 判断能否进入有内部结构的箱子
    if (boards[boxId][r][c] != "#") {
        // 内部箱子边缘入口处是空地或检测点
        if (boards[boxId][r][c] == "." || boards[boxId][r][c] == "-" || boards[boxId][r][c] == "=") {
            // 进来的是玩家
            if (boards[oldMap][oldRow][oldCol] == "P" || boards[oldMap][oldRow][oldCol] == "p") {
                if (boards[boxId][r][c] == "=") {
                    boards[boxId][r][c] = "p";
                    playerMap = boxId;
                    playerRow = r;
                    playerCol = c;
                } else {
                    boards[boxId][r][c] = "P";
                    playerMap = boxId;
                    playerRow = r;
                    playerCol = c;
                }
                isEnter = true;
                boards[oldMap][oldRow][oldCol] = ".";
            }
            // 进来的是普通箱子
            else if (boards[oldMap][oldRow][oldCol] == "B" || boards[oldMap][oldRow][oldCol] == "b") {
                if (boards[boxId][r][c] == "-") {
                    boards[boxId][r][c] = "b";
                } else {
                    boards[boxId][r][c] = "B";
                }
                boards[oldMap][oldRow][oldCol] = ".";
                isEnter = true;
            }
            // 进来的是有内部结构的箱子，更改进来的有内部结构的箱子对应的包含关系和位置信息
            else if (boards[oldMap][oldRow][oldCol].substr(0, 1) == "I" || boards[oldMap][oldRow][oldCol].substr(0, 1) == "i") {
                if (boards[boxId][r][c] == "-") {
                    boards[boxId][r][c] = "i" + boards[oldMap][oldRow][oldCol].substr(1);
                    for (auto& tuple : contains) {
                        if (std::get<1>(tuple) == std::stoi(boards[oldMap][oldRow][oldCol].substr(1, 2))) {
                            std::get<0>(tuple) = boxId;
                            std::get<2>(tuple) = r;
                            std::get<3>(tuple) = c;
                        }
                    }
                } else {
                    boards[boxId][r][c] = "I" + boards[oldMap][oldRow][oldCol].substr(1);
                    for (auto& tuple : contains) {
                        if (std::get<1>(tuple) == std::stoi(boards[oldMap][oldRow][oldCol].substr(1, 2))) {
                            std::get<0>(tuple) = boxId;
                            std::get<2>(tuple) = r;
                            std::get<3>(tuple) = c;
                        }
                    }
                }
                isEnter = true;
                boards[oldMap][oldRow][oldCol] = ".";
            }
        }
        // 内部箱子边缘入口处是普通箱子
        else if (boards[boxId][r][c] == "B" || boards[boxId][r][c] == "b") {
            // 进来的是玩家
            if (boards[oldMap][oldRow][oldCol] == "P" || boards[oldMap][oldRow][oldCol] == "p") {
                moveBox(direction, oldMap , oldRow, oldCol, boxId, r, c);
                boards[boxId][r][c] = boards[oldMap][oldRow][oldCol];
                boards[oldMap][oldRow][oldCol] = ".";
                playerMap = boxId;
                playerRow = r;
                playerCol = c;
                isEnter = true;
            }
            // 进来的是普通箱子或有内部结构的箱子
            else if (boards[oldMap][oldRow][oldCol] == "B" || boards[oldMap][oldRow][oldCol] == "b" ||
                     boards[oldMap][oldRow][oldCol].substr(0, 1) == "I" || boards[oldMap][oldRow][oldCol].substr(0, 1) == "i") {
                moveBox(direction, oldMap, oldRow, oldCol, boxId, r, c);
                if (boards[boxId][r][c] == "-"){
                    boards[boxId][r][c] = "b";
                } else {
                    boards[boxId][r][c] = "B";
                }
                isEnter = true;
                boards[oldMap][oldRow][oldCol] = ".";
            }
        }
        // 内部箱子边缘入口处是含有内部结构的箱子
        else if (boards[boxId][r][c].substr(0, 1) == "I") {
            // 进来的是玩家
            if (boards[oldMap][oldRow][oldCol] == "P" || boards[oldMap][oldRow][oldCol] == "p") {
                moveInternalBox(direction, oldMap , oldRow, oldCol, boxId, r, c);
                boards[boxId][r][c] = boards[oldMap][oldRow][oldCol];
                boards[oldMap][oldRow][oldCol] = ".";
                playerMap = boxId;
                playerRow = r;
                playerCol = c;
                isEnter = true;
            }
            // 进来的是普通箱子或有内部结构的箱子
            else if (boards[oldMap][oldRow][oldCol] == "B" || boards[oldMap][oldRow][oldCol] == "b" ||
                     boards[oldMap][oldRow][oldCol].substr(0, 1) == "I" || boards[oldMap][oldRow][oldCol].substr(0, 1) == "i") {
                moveInternalBox(direction, oldMap, oldRow, oldCol, boxId, r, c);
                boards[boxId][r][c] = boards[oldMap][oldRow][oldCol];
                boards[oldMap][oldRow][oldCol] = ".";
                isEnter = true;
            }
        }
        this->isValidMove = true;
    } else {
        this->isValidMove = false;
        std::cout << "Cannot enter the box. Try again.\n";
    }
    repaintDest();
}


// oldMap是有内部结构的箱子对应的地图(就是自己本身的地图)序号,newMap是包含有内部结构的箱子的地图,
// oldRow和oldCol是玩家或箱子原本在有内部结构的箱子中的位置,newRow和newCol是玩家或箱子走出有内部结构的箱子之后的位置
void GameBoard::leaveInternalBox(char direction, int oldMap, int oldRow, int oldCol) {
    int newMap;
    int newRow;
    int newCol;

    isLeave = true;
    // 遍历contains，检索并计算走出之后的地图和在地图中的位置，并进行移动
    for (auto& tuple : contains) {
        // 找到了该有内部结构的箱子对应的数据
        if (std::get<1>(tuple) == oldMap) {
            // 获取走出之后新地图的序号和在新地图中的位置
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
            // 判断能否走出有内部结构的箱子
            if (boards[newMap][newRow][newCol] != "#") {
                // 走出后的位置是普通箱子
                if (boards[newMap][newRow][newCol] == "B" || boards[newMap][newRow][newCol] == "b") {
                    moveBox(direction, oldMap, oldRow, oldCol, newMap, newRow, newCol);
                    // 可以推动走出有内部结构的位置上的普通箱子,走出有内部结构的箱子
                    if (isValidMove){
                        // 走出去的是玩家
                        if(oldMap == playerMap && oldRow == playerRow && oldCol == playerCol) {
                            if (boards[newMap][newRow][newCol] == "="){
                                boards[newMap][newRow][newCol] = "p";
                            } else {
                                boards[newMap][newRow][newCol] = "P";
                            }
                            if (boards[oldMap][oldRow][oldCol] == "P" || boards[oldMap][oldRow][oldCol] == "p") {
                                boards[oldMap][oldRow][oldCol] = ".";
                            }
                            playerMap = newMap;
                            playerRow = newRow;
                            playerCol = newCol;
                        }
                        // 出去的是有内部结构的箱子
                        else if (boards[oldMap][oldRow][oldCol].substr(0,1) == "I" || boards[oldMap][oldRow][oldCol].substr(0,1) == "i") {
                            if (boards[newMap][newRow][newCol] == "-"){
                                boards[newMap][newRow][newCol] = "i" + boards[oldMap][oldRow][oldCol].substr(1);
                            } else {
                                boards[newMap][newRow][newCol] = "I" + boards[oldMap][oldRow][oldCol].substr(1);
                            }
                            for (auto& tuple : contains) {
                                if (std::get<1>(tuple) == std::stoi(boards[oldMap][oldRow][oldCol].substr(1, 2))) {
                                    std::get<0>(tuple) = newMap;
                                    std::get<2>(tuple) = newRow;
                                    std::get<3>(tuple) = newCol;
                                }
                            }
                            boards[oldMap][oldRow][oldCol] = ".";
                        }
                        // 出去的是普通箱子
                        else {
                            if (boards[newMap][newRow][newCol] == "-"){
                                boards[newMap][newRow][newCol] = "b";
                            } else {
                                boards[newMap][newRow][newCol] = "B";
                            }
                            boards[oldMap][oldRow][oldCol] = ".";
                        }
                    }
                }
                // 走出后的位置是有内部结构的箱子
                else if (boards[newMap][newRow][newCol].substr(0, 1) == "I" || boards[newMap][newRow][newCol].substr(0, 1) == "i"){
                    moveInternalBox(direction, oldMap, oldRow, oldCol, newMap, newRow, newCol);
                    // 可以推动走出有内部结构的位置上的有内部结构的箱子,走出有内部结构的箱子
                    if (isValidMove && !isEnter){
                        // 走出去的是玩家
                        if(oldMap == playerMap && oldRow == playerRow && oldCol == playerCol) {
                            if (boards[newMap][newRow][newCol] == "="){
                                boards[newMap][newRow][newCol] = "p";
                            } else {
                                boards[newMap][newRow][newCol] = "P";
                            }
                            if (boards[oldMap][oldRow][oldCol] == "P" || boards[oldMap][oldRow][oldCol] == "p") {
                                boards[oldMap][oldRow][oldCol] = ".";
                            }
                            playerMap = newMap;
                            playerRow = newRow;
                            playerCol = newCol;
                        }
                        // 出去的是有内部结构的箱子
                        else if (boards[oldMap][oldRow][oldCol].substr(0,1) == "I" || boards[oldMap][oldRow][oldCol].substr(0,1) == "i") {
                            if (boards[newMap][newRow][newCol] == "-"){
                                boards[newMap][newRow][newCol] = "i" + boards[oldMap][oldRow][oldCol].substr(1);
                            } else {
                                boards[newMap][newRow][newCol] = "I" + boards[oldMap][oldRow][oldCol].substr(1);
                            }
                            for (auto& tuple : contains) {
                                if (std::get<1>(tuple) == std::stoi(boards[oldMap][oldRow][oldCol].substr(1, 2))) {
                                    std::get<0>(tuple) = newMap;
                                    std::get<2>(tuple) = newRow;
                                    std::get<3>(tuple) = newCol;
                                }
                            }
                            boards[oldMap][oldRow][oldCol] = ".";
                        }
                        // 出去的是普通箱子
                        else {
                            if (boards[newMap][newRow][newCol] == "-"){
                                boards[newMap][newRow][newCol] = "b";
                            } else {
                                boards[newMap][newRow][newCol] = "B";
                            }
                            boards[oldMap][oldRow][oldCol] = ".";
                        }
                    }
                    // 走出的位置是有内部结构的箱子，且该有内部结构的箱子无法移动，尝试进入该有内部结构的箱子
                    else if (!isEnter){
                        enterInternalBox(direction, oldRow, oldCol, oldMap, newRow, newCol);
                    }
                }
                //走出后的位置为空地或检测点
                else {
                    // 走出去的是玩家
                    if(oldMap == playerMap && oldRow == playerRow && oldCol == playerCol) {
                        if (boards[newMap][newRow][newCol] == "="){
                            boards[newMap][newRow][newCol] = "p";
                        } else {
                            boards[newMap][newRow][newCol] = "P";
                        }
                        if (boards[oldMap][oldRow][oldCol] == "P" || boards[oldMap][oldRow][oldCol] == "p") {
                            boards[oldMap][oldRow][oldCol] = ".";
                        }
                        playerMap = newMap;
                        playerRow = newRow;
                        playerCol = newCol;
                    }
                    // 出去的是有内部结构的箱子
                    else if (boards[oldMap][oldRow][oldCol].substr(0,1) == "I" || boards[oldMap][oldRow][oldCol].substr(0,1) == "i") {
                        if (boards[newMap][newRow][newCol] == "-"){
                            boards[newMap][newRow][newCol] = "i" + boards[oldMap][oldRow][oldCol].substr(1);
                        } else {
                            boards[newMap][newRow][newCol] = "I" + boards[oldMap][oldRow][oldCol].substr(1);
                        }
                        for (auto& tuple : contains) {
                            if (std::get<1>(tuple) == std::stoi(boards[oldMap][oldRow][oldCol].substr(1, 2))) {
                                std::get<0>(tuple) = newMap;
                                std::get<2>(tuple) = newRow;
                                std::get<3>(tuple) = newCol;
                            }
                        }
                        boards[oldMap][oldRow][oldCol] = ".";
                    }
                    // 出去的是普通箱子
                    else {
                        if (boards[newMap][newRow][newCol] == "-"){
                            boards[newMap][newRow][newCol] = "b";
                        } else {
                            boards[newMap][newRow][newCol] = "B";
                        }
                        boards[oldMap][oldRow][oldCol] = ".";
                    }
                }
            } else {
                this -> isValidMove = false;
                this -> isLeave = false;
                std::cout << "Cannot leave the box. Try again.\n";
            }
        }
    }
    repaintDest();
}


// oldMap是“推动者”所在的地图,oldRow和oldCol是“推动者”的位置,newMap是“被推者”所在的地图,newRow和newCol是“被推者”的位置
// 在这个函数中我们移动的是原本位于newMap上newRow和newCol位置上的有内部结构的箱子,移动到newBoxMap上newBoxRow和newBoxCol位置
void GameBoard::moveInternalBox(char direction, int oldMap, int oldRow, int oldCol, int newMap, int newRow, int newCol) {
    // 获取位于newMap上newRow和newCol位置上的有内部结构的箱子本身地图的序号,后续用来更新该有内部结构的箱子的数据
    int boxId = std::stoi(boards[newMap][newRow][newCol].substr(1, 2));
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
    // 判断新位置是否合法
    if (newBoxRow >= 0 && newBoxRow < boards[newBoxMap].size() &&
        newBoxCol >= 0 && newBoxCol < boards[newBoxMap][0].size() &&
        boards[newBoxMap][newBoxRow][newBoxCol] != "#") {

        // 如果有内部结构的箱子移动方向紧挨着另一个箱子
        // 递归判断另一个箱子是否能移动，如果能则移动，不能将isValidMove设为false

        // 要将该有内部结构的箱子移动到的位置上是普通箱子
        if (boards[newBoxMap][newBoxRow][newBoxCol] == "B" || boards[newBoxMap][newBoxRow][newBoxCol] == "b") {
            moveBox(direction, newMap, newRow, newCol, newBoxMap, newBoxRow, newBoxCol);
            // 普通箱子可以向前移动
            if (isValidMove) {
                // 移动位于newMap中位于newRow和newCol上的有内部结构的箱子到newBoxMap上的newBoxRow和newBoxCol位置
                if (boards[newBoxMap][newBoxRow][newBoxCol] == "-") {
                    boards[newBoxMap][newBoxRow][newBoxCol] = "i" + boards[newMap][newRow][newCol].substr(1);
                } else {
                    boards[newBoxMap][newBoxRow][newBoxCol] = "I" + boards[newMap][newRow][newCol].substr(1);
                }
                // 更新有内部结构的箱子的位置数据
                for (auto& tuple : contains) {
                    if (std::get<1>(tuple) == boxId) {
                        std::get<2>(tuple) = newBoxRow;
                        std::get<3>(tuple) = newBoxCol;
                    }
                }
                boards[newMap][newRow][newCol] = ".";
                repaintDest();
            }
            // 普通箱子不能向前移动，判断这个有内部结构的箱子能否“吃掉”普通箱子
            else {
                char tempDirection;
                switch (direction) {
                    case 'W':
                        tempDirection = 'S';
                        break;
                    case 'S':
                        tempDirection = 'W';
                        break;
                    case 'A':
                        tempDirection = 'D';
                        break;
                    case 'D':
                        tempDirection = 'A';
                        break;
                }
                enterInternalBox(tempDirection, newBoxRow, newBoxCol, newMap, newRow, newCol);
                // 如果可以“吃掉”前面的普通箱子,则向前移动
                if (isValidMove) {
                    moveInternalBox(direction, oldMap, oldRow, oldCol, newMap, newRow, newCol);
                    isEnter = false;
                }
                // “被推者”无法移动，判断“推动者”能否进入“被推者”(也就是有内部结构的箱子)
                else {
                    // 判断是否可以进入有内部结构的箱子
                    if (boards[newMap][newRow][newCol].substr(0, 1) == "I" || boards[newMap][newRow][newCol].substr(0, 1) == "i"){
                        enterInternalBox(direction, oldRow, oldCol, oldMap, newRow, newCol);
                    } else {
                        this->isValidMove = false;
                        std::cout << "Cannot enter the box. Try again.\n";
                    }
                }
            }
        }
        // 要将该有内部结构的箱子移动到的位置上也是有内部结构的箱子
        else if (boards[newBoxMap][newBoxRow][newBoxCol].substr(0,1) == "I" || boards[newBoxMap][newBoxRow][newBoxCol].substr(0,1) == "i") {
            moveInternalBox(direction, newMap, newRow, newCol, newBoxMap, newBoxRow, newBoxCol);

            // 要移动位置上的箱子是有内部结构的箱子,而且前面的有内部结构的箱子无法移动,判断能否被要移动位置上的有内部结构的箱子“吃掉”

            // 不能被要移动位置上的有内部结构的箱子“吃掉”
            if (!isValidMove) {
                // 尝试能否被“吃掉”要移动位置上的有内部结构的箱子
                char tempDirection;
                switch (direction) {
                    case 'W':
                        tempDirection = 'S';
                        break;
                    case 'S':
                        tempDirection = 'W';
                        break;
                    case 'A':
                        tempDirection = 'D';
                        break;
                    case 'D':
                        tempDirection = 'A';
                        break;
                }
                enterInternalBox(tempDirection, newBoxRow, newBoxCol, newMap, newRow, newCol);
                // 可以“吃掉”要移动位置上的有内部结构的箱子,向前移动
                if (isValidMove) {
                    moveInternalBox(direction, oldMap, oldRow, oldCol, newMap, newRow, newCol);
                }
            }
            // 前面要移动位置上的有内部结构的箱子可以移动,并且没有进入前面要移动位置上的有内部结构的箱子
            else if (isValidMove && !isEnter){
                // 移动位于newMap中位于newRow和newCol上的有内部结构的箱子到newBoxMap上的newBoxRow和newBoxCol位置
                if (boards[newBoxMap][newBoxRow][newBoxCol] == "-") {
                    boards[newBoxMap][newBoxRow][newBoxCol] = "i" + boards[newMap][newRow][newCol].substr(1);
                } else {
                    boards[newBoxMap][newBoxRow][newBoxCol] = "I" + boards[newMap][newRow][newCol].substr(1);
                }
                // 更新该有内部结构的箱子的数据
                for (auto& tuple : contains) {
                    if (std::get<1>(tuple) == boxId) {
                        std::get<2>(tuple) = newBoxRow;
                        std::get<3>(tuple) = newBoxCol;
                    }
                }
                boards[newMap][newRow][newCol] = ".";
                repaintDest();
            }
            if (isEnter) {
                isEnter = false;
            }
        }
        // 要移动的位置是空地或检测点
        else {
            // 移动位于newMap中位于newRow和newCol上的有内部结构的箱子到newBoxMap上的newBoxRow和newBoxCol位置
            if (boards[newBoxMap][newBoxRow][newBoxCol] == "-") {
                boards[newBoxMap][newBoxRow][newBoxCol] = "i" + boards[newMap][newRow][newCol].substr(1);
            } else {
                boards[newBoxMap][newBoxRow][newBoxCol] = "I" + boards[newMap][newRow][newCol].substr(1);
            }
            // 更新该有内部结构的箱子的数据
            for (auto& tuple : contains) {
                if (std::get<1>(tuple) == boxId) {
                    std::get<2>(tuple) = newBoxRow;
                    std::get<3>(tuple) = newBoxCol;
                }
            }
            boards[newMap][newRow][newCol] = ".";
            repaintDest();
        }

    }
    // 先判断“被推者”是否离开当前地图，如果可以先离开，如果无法离开并且“被推者”无法移动，判断“推动者”能否进入“被推者”(也就是有内部结构的箱子)
    else {
        // 判断“被推者”是否离开当前地图
        if (newBoxRow < 0 || newBoxRow >= boards[newBoxMap].size() ||
            newBoxCol < 0 || newBoxCol >= boards[newBoxMap][0].size()){
            leaveInternalBox(direction, newMap, newRow, newCol);
        }
        // 判断是否可以进入有内部结构的箱子
        else if (boards[newBoxMap][newBoxRow][newBoxCol] == "#" &&
        (boards[newMap][newRow][newCol].substr(0, 1) == "I"
        || boards[newMap][newRow][newCol].substr(0, 1) == "i")){
            enterInternalBox(direction, oldRow, oldCol, oldMap, newRow, newCol);
        } else {
            this->isValidMove = false;
            std::cout << "Cannot enter the box. Try again.\n";
        }
    }
}


//玩家的移动逻辑
void GameBoard::movePlayer(char direction) {
    boards_old=boards;
    contains_old=contains;
    std::array<int,3>player_old={playerMap,playerRow,playerCol};
    player.push(player_old);

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

    isValidMove = true;
    isEnter = false;
    isLeave = false;

    // 检查玩家要移动的新位置是否合法
    if (newPlayerRow >= 0 && newPlayerRow < boards[newPlayerMap].size() &&
        newPlayerCol >= 0 && newPlayerCol < boards[newPlayerMap][0].size() &&
        boards[newPlayerMap][newPlayerRow][newPlayerCol] != "#") {

        // 如果新位置是普通箱子
        if (boards[newPlayerMap][newPlayerRow][newPlayerCol] == "B"
        || boards[newPlayerMap][newPlayerRow][newPlayerCol] == "b") {
            moveBox(direction, playerMap, playerRow, playerCol, newPlayerMap, newPlayerRow, newPlayerCol);
            // 新位置上的普通箱子可以被推动
            if (isValidMove){
                // 更新玩家位置
                if (boards[newPlayerMap][newPlayerRow][newPlayerCol] == "=") {
                    boards[newPlayerMap][newPlayerRow][newPlayerCol] = "p";
                } else {
                    boards[newPlayerMap][newPlayerRow][newPlayerCol] = "P";
                }
                if (boards[playerMap][playerRow][playerCol] == "P" || boards[playerMap][playerRow][playerCol] == "p") {
                    boards[playerMap][playerRow][playerCol] = ".";
                }
                playerMap = newPlayerMap;
                playerRow = newPlayerRow;
                playerCol = newPlayerCol;
            }
        }
        // 如果新位置是有内部结构的箱子
        else if(boards[newPlayerMap][newPlayerRow][newPlayerCol].substr(0,1) == "I"
        || boards[newPlayerMap][newPlayerRow][newPlayerCol].substr(0,1) == "i"){
            moveInternalBox(direction, playerMap, playerRow, playerCol, newPlayerMap, newPlayerRow, newPlayerCol);
            // 如果可以推动有内部结构的箱子并且玩家没有进入有内部结构的箱子,进入的话会自动更新玩家位置
            if (isValidMove && !isEnter){
                // 更新玩家位置
                if (boards[newPlayerMap][newPlayerRow][newPlayerCol] == "=") {
                    boards[newPlayerMap][newPlayerRow][newPlayerCol] = "p";
                } else {
                    boards[newPlayerMap][newPlayerRow][newPlayerCol] = "P";
                }
                if (boards[playerMap][playerRow][playerCol] == "P" || boards[playerMap][playerRow][playerCol] == "p") {
                    boards[playerMap][playerRow][playerCol] = ".";
                }
                playerMap = newPlayerMap;
                playerRow = newPlayerRow;
                playerCol = newPlayerCol;
            }
            // 无法推动有内部结构的箱子并且玩家没有进入有内部结构的箱子
            else if (!isValidMove && !isEnter){
                // 尝试进入有内部结构的箱子
                enterInternalBox(direction, playerRow, playerCol, playerMap, newPlayerRow, newPlayerCol);
            }
        }
        // 玩家要移动到的位置是空地或检测点
        else {
            //旧位置更新为空
            if (boards[playerMap][playerRow][playerCol] == "P" || boards[playerMap][playerRow][playerCol] == "p") {
                boards[playerMap][playerRow][playerCol] = ".";
            }
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
    }
    // 玩家走出地图界外，判断是否能够走出有递归结构的箱子
    else {
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
    std::cout << "Current level: " << difficulty << std::endl;
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

void GameBoard::printBoard(std::string filename) const {
    std::cout << "Current level: " << 5 << std::endl;
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

//只需要存储哪个地图的哪个位置发生了变化以及变化前的元素，和contains变化前的四个参数。
//两个stack分别存这一步有没有导致地图元素变化或者contains变化。
//玩家每走一步，先是对前后的boards进行对比，找到有没有变化，有变化就对地图判断stack进行push(1)，所有变化位置和变化前元素存进地图stack，没变化push(0)。
//同时对前后contains进行对比，找找有没有变化，有变化就对con判断stack进行push(1)，将变化前的contains存入con_stack，没变化push(0)
void GameBoard::getChange(){
    bool isChange=false;
    for (int i = 0; i < boards.size(); i++)
    {
        for (int j = 0; j < boards[i].size(); j++)
        {
            for (int k = 0; k < boards[i][j].size(); k++)
            {
                if (boards_old[i][j][k]!=boards[i][j][k])
                {
                    isChange=true;
                    boards_before change = {i,j,k,boards_old[i][j][k]};
                    before_vector.push_back(change);
                } 
            }
        }
    }
    if (isChange)
    {
        isBoardsChange.push(1);
        boardsStack.push(before_vector);
        before_vector.clear();
    }else{
        isBoardsChange.push(0);
    }

    isChange=false;
    for (int i = 0; i < contains.size(); i++)
    {
        if (contains_old[i]!=contains[i])
        {
            isChange=true;
        }
    }
    if (isChange)
    {
        isContainsChange.push(1);
        containsStack.push(contains_old);
    }else{
        isContainsChange.push(0);
    }

    contains_old=contains;
    boards_old=boards;
}

//在进行撤销时，先对两个判断stack进行top和pop，如果是0则跳过修改，如果是1对地图或con的stack分别top和pop。
//如果地图判断是1，将对应坐标的元素改为之前存的元素；如果con判断是1，将contains清零然后存入top对应的contains。
void GameBoard::undo(){
    if (isBoardsChange.empty())
    {
        return;
    }
    
    int isboardschange=isBoardsChange.top();
    isBoardsChange.pop();
    int iscontainschange=isContainsChange.top();
    isContainsChange.pop();
    if (isboardschange)
    {
        before_vector = boardsStack.top();
        boardsStack.pop();
        boards_before change;
        for (int i = 0; i < before_vector.size(); i++)
        {
            change=before_vector[i];
            boards[change.x][change.y][change.z]=change.value;
        }
    }

    if (iscontainschange)
    {
        contains.clear();
        contains=containsStack.top();
        containsStack.pop();
    }

    std::array<int,3>player_old=player.top();
    player.pop();
    playerMap = player_old[0];
    playerRow = player_old[1];
    playerCol = player_old[2];
    
}

