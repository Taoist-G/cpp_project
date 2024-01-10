#pragma once
#include <vector>
#include <string>

class GameBoard {
public:
    GameBoard(int difficulty);
    void movePlayer(char direction);
    bool isGameOver() const;
    void printBoard(int difficulty) const;


private:
    int currentLevel{};
    bool isValidMove;
    std::vector<std::vector<std::vector<char>>> levels;
    std::vector<std::vector<char>> board;
    std::vector<std::pair<int, int>> destinations;
    int playerRow{}, playerCol{}, checkRow{}, checkCol{};

    void initializeBoard(int choice);
    void moveMultiBox(char direction, int boxRow, int boxCol);
    void repaintDest();
};
