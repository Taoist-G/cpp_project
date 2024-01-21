#include "GameWindow.h"
#include "WindowSetup.h"
#include <FL/Fl_Box.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/fl_ask.H>
#include <FL/Fl_File_Chooser.H>
#include <iostream>
GameWindow::GameWindow(int W, int H, const char* title, GameBoard& gb)
    : Fl_Window(W, H, title), gameBoard(gb) {
}

void GameWindow::updateGameGUI() {
    this->clear();
    // 清除现有的小部件
    int cellWidth = 100;
    int cellHeight = 100;
    // 假设地图渲染区域的宽度为 mapWidth
    int mapWidth = 900; // 假设所有行的列数相同
    // 设置提示文本的位置和尺寸
    int x_pos = mapWidth + 20; // 地图右侧的起始位置
    int y_pos = 250;            // 顶部开始的位置
    int textWidth = 300;       // 文本框的宽度
    int textHeight = 30;       // 文本框的高度
    // 添加提示文本
    Fl_Box *moveText = new Fl_Box(x_pos, y_pos, textWidth, textHeight, "W/A/S/D: Move\n\nR: Restart\n\nQ: Quit\n\nU: Undo\n\nZ: Save Progress\n\n1~9: Check Inner Box & Basic Map");
    moveText->labelsize(25); 
    this->add(moveText);

    x_pos=20;y_pos=20;
    if ( gameBoard.playerMap >=0) {
        displayBoard(gameBoard.getBoards()[gameBoard.playerMap], x_pos, y_pos, cellWidth, cellHeight,currentWindow,gameBoard.playerMap);
    }else

    if ( gameBoard.playerMap == -1) {
        displayBoard(gameBoard.get_inf_space(), x_pos, y_pos, cellWidth, cellHeight,currentWindow,-1);
    }else
    if ( gameBoard.playerMap == -2) {
        displayBoard(gameBoard.get_inf_space2(), x_pos, y_pos, cellWidth, cellHeight,currentWindow,-2);
    }else
    if ( gameBoard.playerMap == -3) {
        displayBoard(gameBoard.get_empty_space(), x_pos, y_pos, cellWidth, cellHeight,currentWindow,-3);
    }
    this->redraw();
}

int GameWindow::handle(int event) {
    if (event == FL_KEYDOWN) {
        int key = Fl::event_key();
        int boardIndex = key - '1'; 
        if (key >= '1' && key <= '9') {
            if (boardIndex >= 0 && boardIndex < gameBoard.getBoards().size()) {
                showBoardInNewWindow(boardIndex);
            }
            return 1;
        }
       switch (key) {
                    case 'w':
                    case 'W':
                        gameBoard.movePlayer('W');
                        gameBoard.getChange();
                        break;
                    case 'a':
                    case 'A':
                        gameBoard.movePlayer('A');
                        gameBoard.getChange();

                        break;
                    case 's':
                    case 'S':
                        gameBoard.movePlayer('S');                        
                        gameBoard.getChange();
                        break;
                    case 'd':
                    case 'D':
                        gameBoard.movePlayer('D');                        
                        gameBoard.getChange();
                        break;
                    case 'z':
                    case 'Z':
                        saveGame();
                        break;
                    case 'u':
                    case 'U':
                        gameBoard.undo();
                        std::cout << "Undo successfully\n"; 
                        break;
                    case 'r':
                    case 'R':
                        std::cout << "Restarting current game\n";
                        if (!gameBoard.get_filename().empty()) {
                            // 如果有存档文件名，则重新加载游戏
                            playGame(gameBoard.get_filename());
                        } else {
                            // 否则，重新开始当前难度的游戏
                            std::cout << "Restarting current game\n";
                            std::cout <<gameBoard.getDifficulty()<<"\n";
                            playGame(gameBoard.getDifficulty());
                        }
                        return 1;
                    case 'q':
                    case 'Q':
                        gameBoard.set_filename("");
                        gameBoard.set_difficulty(-1);
                        if (currentWindow) {
                            currentWindow->hide();
                            delete currentWindow;
                        }
                        setupGUI(); // 关闭窗口
                        return 1;

                    default:
                        break;
                }
        updateGameGUI();
        if (gameBoard.isGameOver()) {
            // 游戏结束，关闭游戏窗口并退回初始界面
            std::string message="Congratulations! You've passed the level";
            if (gameBoard.getDifficulty()>0&&gameBoard.getDifficulty()<6){
                message += std::to_string(gameBoard.getDifficulty());
            }
            fl_message("%s", message.c_str());

            if (currentWindow) {
                currentWindow->clear();
                delete currentWindow;
                currentWindow = nullptr;
            }
            // gameBoard.set_filename(nullptr);
            
            gameBoard.set_difficulty(-1);
            setupHomePage();
            return 1; // 表示事件已处理
        }

        return 1; // 表示事件已处理
    }
    return Fl_Window::handle(event);
}
void GameWindow::displayBoard(const std::vector<std::vector<std::string>>& board, int x_pos, int y_pos, int cellWidth, int cellHeight, Fl_Window* window, int boardIndex) {
    Fl_Box* titleBox;
    if (gameBoard.haveBasicMap && boardIndex == gameBoard.getBoards().size() - 1) {
        titleBox = new Fl_Box(1000, 10, 300, 30, "Current State: Basic Map");
    } else if (boardIndex == 0) {
        titleBox = new Fl_Box(1000, 10, 300, 30, "Current State: Inner Box 1");
    } else if (boardIndex == 1) {
        titleBox = new Fl_Box(1000, 10, 300, 30, "Current State: Inner Box 2");
    } else if (boardIndex == 2) {
        titleBox = new Fl_Box(1000, 10, 300, 30, "Current State: Inner Box 3");
    } else if (boardIndex == 3) {
        titleBox = new Fl_Box(1000, 10, 300, 30, "Current State: Inner Box 4");
    } else if (boardIndex == 4) {
        titleBox = new Fl_Box(1000, 10, 300, 30, "Current State: Inner Box 5");
    } else if (boardIndex == 5) {
        titleBox = new Fl_Box(1000, 10, 300, 30, "Current State: Inner Box 6");
    } else if (boardIndex == 6) {
        titleBox = new Fl_Box(1000, 10, 300, 30, "Current State: Inner Box 7");
    } else if (boardIndex == 7) {
        titleBox = new Fl_Box(1000, 10, 300, 30, "Current State: Inner Box 8");
    } else if (boardIndex == 8) {
        titleBox = new Fl_Box(1000, 10, 300, 30, "Current State: Inner Box 9");
    } else if (boardIndex == -1) {
        titleBox = new Fl_Box(1000, 10, 300, 30, "Current State: Inf Space 1");
    } else if (boardIndex == -2) { 
        titleBox = new Fl_Box(1000, 10, 300, 30, "Current State: Inf Space 2");
    } else if (boardIndex == -3) { 
        titleBox = new Fl_Box(1000, 10, 300, 30, "Current State: Empty Space");
    }
    titleBox->labelfont(FL_BOLD);
    titleBox->labelsize(25);
    this->add(titleBox);

    for (size_t i = 0; i < board.size(); ++i) {
        for (size_t j = 0; j < board[i].size(); ++j) {
            std::string imagePath = getImagePath(board[i][j]);
            displayCell(imagePath, j * cellWidth + x_pos, i * cellHeight + y_pos, cellWidth, cellHeight, window);
        }
    }
}


void GameWindow::displayCell(const std::string& imagePath, int x, int y, int width, int height, Fl_Window* window) {
    Fl_PNG_Image* img = new Fl_PNG_Image(imagePath.c_str());
    Fl_Image* scaledImage = img->copy(width, height);
    delete img;
    Fl_Box* box = new Fl_Box(x, y, width, height);
    box->image(scaledImage);
    window->add(box);
}


std::string GameWindow::getImagePath(const std::string &symbol) {

    std::string imagePath;
            if (symbol == ".") { imagePath = "sokoban/empty.png"; }
            else if (symbol == "#") { imagePath = "sokoban/solid.png"; }
            else if (symbol == "P") { imagePath = "sokoban/player.png"; }
            else if (symbol == "p") { imagePath = "sokoban/player_win.png"; }
            else if (symbol == "B") { imagePath = "sokoban/crate.png"; }
            else if (symbol == "b") { imagePath = "sokoban/darkened_center_image.png"; }
            else if (symbol.substr(0, 1) == "I"|| symbol.substr(0, 1) == "i") {
                if (symbol.substr(0, 1) == "I") {
                        imagePath = "sokoban/numbered_image_";
                    } else{
                        imagePath = "sokoban/darkened_center_numbered_image_";
                    }
                    imagePath += symbol.substr(1, 2);
                    imagePath += ".png";
                }
            else if (symbol == "-") { imagePath = "sokoban/target.png"; }
            else if (symbol == "=") { imagePath = "sokoban/player_target.png"; }
            else { imagePath = "sokoban/darkened_image.png";}
    return imagePath;
}

void GameWindow::showBoardInNewWindow(int boardIndex) {
    int cellWidth = 100;
    int cellHeight = 100;

    int windowWidth = gameBoard.getBoards()[boardIndex][0].size() * cellWidth;
    int windowHeight = gameBoard.getBoards()[boardIndex].size() * cellHeight;

    std::string windowTitle;
    if (gameBoard.haveBasicMap && boardIndex == gameBoard.getBoards().size() - 1) {
        windowTitle = "Basic Map";
    } else {
        windowTitle = "I" + std::to_string(boardIndex + 1);
    }

    // 获取屏幕宽度和高度
    int screenWidth = Fl::w();
    int screenHeight = Fl::h();

    // 计算新窗口的位置
    int windowPosX = (screenWidth - windowWidth) / 2; // 放置在屏幕右端
    int windowPosY = (screenHeight - windowHeight) / 2; // 垂直居中

    Fl_Window* newWindow = new Fl_Window(windowPosX, windowPosY, windowWidth, windowHeight, windowTitle.c_str());
    displayBoard(gameBoard.getBoards()[boardIndex], 0, 0, cellWidth, cellHeight, newWindow,boardIndex);
    newWindow->end();
    newWindow->show();
}


void GameWindow::saveGame() {
    // 打开文件选择器窗口以保存文件
    Fl_File_Chooser chooser("save/", "*", Fl_File_Chooser::CREATE, "Save Game");
    chooser.show();

    // 等待用户选择或关闭文件选择器
    while(chooser.shown()) {
        Fl::wait();
    }

    const char* filename = chooser.value();
    if (filename != nullptr) {

        gameBoard.saveGameToFile(filename);
        fl_message("Game saved successfully!");
    }
}