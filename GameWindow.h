#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <FL/Fl_Window.H>
#include "GameBoard.h"

class GameWindow : public Fl_Window {
public:
    GameBoard gameBoard;
    GameWindow(int W, int H, const char* title, GameBoard& gb);
    void updateGameGUI();
    int handle(int event);
    void displayBoard(const std::vector<std::vector<std::string>> &board, int x_pos, int y_pos, int cellWidth, int cellHeight, Fl_Window* window,int boardIndex);
    void displayCell(const std::string &imagePath, int x, int y, int width, int height, Fl_Window* window);
    std::string getImagePath(const std::string &symbol);
    void saveGame();
    void showBoardInNewWindow(int boardIndex);
};

#endif // GAMEWINDOW_H
