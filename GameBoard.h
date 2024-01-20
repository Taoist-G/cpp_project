#pragma once
#include <vector>
#include <string>
#include <tuple>
#include <stack>

struct boards_before {
    int x, y, z;
    std::string value;
};

class GameBoard {
public:
    GameBoard(int difficulty);
    GameBoard(std::string filename);
    void movePlayer(char direction);
    bool isGameOver() const;
    void printBoard(int difficulty) const;
    void printBoard(std::string filename) const;
    void saveGameToFile(const std::string& filename);
    void loadGameFromFile(const std::string& filename);
    void undo();
    void getChange();


private:
    bool isValidMove;
    bool isEnter;
    bool isLeave;
    std::vector<std::string> mapNames;
    std::vector<std::vector<std::vector<std::string>>> boards;
    std::vector<std::vector<std::string>> empty_space;
    std::vector<std::vector<std::string>> inf_space;
    std::vector<std::tuple<int, int, int>> destinations;
    // contains记录包含关系 第一个元素包含第二个元素 第一个和第二个元素是对应地图的序号
    // 第三第四个元素是第二个元素对应地图在第一个元素对应地图中的行和列
    std::vector<std::tuple<int, int, int, int, int>> contains;
    int playerMap, playerRow, playerCol, checkMap, checkRow, checkCol, infMap, infRow, infCol;

    std::stack<std::array<int,3>> player;

    std::vector<std::vector<std::vector<std::string>>> boards_old;
    std::vector<std::tuple<int, int, int, int,int>> contains_old;
    std::stack<int> isBoardsChange;
    std::stack<int> isContainsChange;

    std::vector<boards_before> before_vector;
    std::stack<std::vector<boards_before>> boardsStack;

    std::stack<std::vector<std::tuple<int, int, int, int,int>>> containsStack;

    void initializeBoard(int choice);
    void initializeBoard(std::string filename);
    void moveBox(char direction, int oldMap, int oldRow, int oldCol, int newMap, int newRow, int newCol);
    void enterInternalBox(char direction, int oldRow, int oldCol, int oldMap, int boxRow, int boxCol);
    void leaveInternalBox(char direction, int newMap, int newRow, int newCol);
    void moveInternalBox(char direction, int oldMap, int oldRow, int oldCol, int newMap, int newRow, int newCol);
    void repaintDest();
};
