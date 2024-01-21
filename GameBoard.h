#pragma once
#include <vector>
#include <string>
#include <tuple>
#include <stack>

struct boards_before {
    int x, y, z;
    std::string value;
};

struct inf_empty_before {
    int x, y;
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
    void undo();
    void getChange();
    int getDifficulty();
    std::string get_filename();
    std::vector<std::vector<std::vector<std::string>>>getBoards();
    std::vector<std::vector<std::string>>get_empty_space();
    std::vector<std::vector<std::string>>get_inf_space();
    std::vector<std::vector<std::string>>get_inf_space2();
    void set_filename(std::string filename);
    void set_difficulty(int n);
    int haveBasicMap;
    int playerMap;

private:
     bool isValidMove;
     bool isEnter;
     bool isLeave;
    //
    int difficulty;
    std::string filename;
    //用于game的restart
    std::vector<std::string> mapNames;
    std::vector<std::vector<std::vector<std::string>>> boards;
    std::vector<std::vector<std::string>> empty_space;
    std::vector<std::vector<std::string>> inf_space;
    std::vector<std::vector<std::string>> inf_space_2;
    std::vector<std::tuple<int, int, int>> destinations;
    // contains记录包含关系 第一个元素包含第二个元素 第一个和第二个元素是对应地图的序号
    // 第三第四个元素是第二个元素对应地图在第一个元素对应地图中的行和列
    std::vector<std::tuple<int, int, int, int, int>> contains;
     int playerRow, playerCol, checkMap, checkRow, checkCol, infMap, infRow, infCol;

    std::stack<std::array<int,3>> player;

    std::vector<std::vector<std::vector<std::string>>> boards_old;
    std::vector<std::vector<std::string>> empty_space_old;
    std::vector<std::vector<std::string>> inf_space_old;
    std::vector<std::vector<std::string>> inf2_space_old;
    std::vector<std::tuple<int, int, int, int,int>> contains_old;
    std::stack<int> isBoardsChange;
    std::stack<int> isContainsChange;
    std::stack<int> isInfChange;
    std::stack<int> isInf2Change;
    std::stack<int> isEmptyChange;

    std::vector<boards_before> before_vector;
    std::stack<std::vector<boards_before>> boardsStack;

    std::vector<inf_empty_before> before_infempty_vector;
    std::stack<std::vector<inf_empty_before>> infStack;
    std::stack<std::vector<inf_empty_before>> inf2Stack;
    std::stack<std::vector<inf_empty_before>> emptyStack;

    std::stack<std::vector<std::tuple<int, int, int, int,int>>> containsStack;

    void initializeBoard(int choice);
    void initializeBoard(std::string filename);
    void moveBox(char direction, int oldMap, int oldRow, int oldCol, int newMap, int newRow, int newCol);
    void enterInternalBox(char direction, int oldRow, int oldCol, int oldMap, int boxRow, int boxCol);
    void leaveInternalBox(char direction, int newMap, int newRow, int newCol);
    void moveInternalBox(char direction, int oldMap, int oldRow, int oldCol, int newMap, int newRow, int newCol);
    void repaintDest();
};
