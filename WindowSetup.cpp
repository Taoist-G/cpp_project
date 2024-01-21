#include "WindowSetup.h"
#include "GameWindow.h"
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_File_Chooser.H>
#include <iostream>

void setupHomePage() {
    // 创建主页面窗口
    currentWindow = new Fl_Window(1600, 1200, "Welcome to Sokoban!");

    // 设置标题
    Fl_Box* title_box = new Fl_Box(90, 150, 1450, 200, "Sokoban");
    title_box->box(FL_NO_BOX);
    title_box->labelfont(FL_BOLD + FL_ITALIC);
    title_box->labelsize(96);
    title_box->labeltype(FL_NORMAL_LABEL);

    // 添加按钮
    Fl_Button* start_button = new Fl_Button(700, 500, 200, 50, "Start");
    start_button->callback(startGame);

    Fl_Button* load_button = new Fl_Button(700, 700, 200, 50, "Load");
    load_button->callback(loadGame);

    Fl_Button* exit_button = new Fl_Button(700, 900, 200, 50, "Exit");
    exit_button->callback(exit_callback);

    currentWindow->end();
    currentWindow->show();
}

void startGame(Fl_Widget*, void*) {
    if (currentWindow) {
        currentWindow->hide();
        delete currentWindow;
    }
    setupGUI();
}

void loadGame(Fl_Widget*, void*) {
    Fl_File_Chooser chooser("save/", "*", Fl_File_Chooser::SINGLE, "Choose a Save File");
    chooser.show();

    // 等待用户做出选择
    while(chooser.shown()) {
        Fl::wait();
    }

    // 获取选择的文件名
    const char* filename = chooser.value();
    
    if (filename != nullptr) {
        std::string filenameStr(filename); // 将 const char* 转换为 std::string
        playGame(filenameStr);
    }
}

void setupGUI() {
    // Set the window size to 1600x1200
    currentWindow = new Fl_Window(1600, 1200, "Welcome to Sokoban!");

    // Scale up the title box
    Fl_Box *title_box = new Fl_Box(100, 100, 1400, 100, "Please Select a Level!");
    title_box->box(FL_NO_BOX);
    title_box->labelfont(FL_BOLD+FL_ITALIC);
    title_box->labelsize(48);
    title_box->labeltype(FL_NORMAL_LABEL);

    // Create an array to hold level numbers
    static int levels[] = {1, 2, 3, 4, 5};

    // Adjust the button layout
    int button_width = 400;
    int button_height = 80;
    int spacing = 80; // Space between buttons
    int starting_y = 300; // Starting y position for the first button

    for (int i = 0; i < 5; i++) {
        int y = starting_y + i * (button_height + spacing);
        Fl_Button *level_button = new Fl_Button(600, y, button_width, button_height);
        char label[10];
        sprintf(label, "Level %d", levels[i]);
        level_button->copy_label(label);
        level_button->callback(level_callback, (void*)&levels[i]);
    }

    // Place the exit button at the bottom
    Fl_Button *back_button = new Fl_Button(600, 1100, button_width, button_height, "Back");
    back_button->callback(backToStart);

    currentWindow->end();
    currentWindow->show();
}

void level_callback(Fl_Widget*, void* userdata) {
    int level = *(static_cast<int*>(userdata));
    
    playGame(level);  // You will need to properly link this callback to playGame
}

void exit_callback(Fl_Widget*, void*) {
    std::cout << "Exiting the game. Goodbye!\n";
    exit(0);
}

void backToStart(Fl_Widget*, void*) {
    if (currentWindow) {
        currentWindow->hide();
        delete currentWindow;
    }
    setupHomePage();
}


void playGame(int difficulty) {
    if (currentWindow) {
        currentWindow->clear();
        delete currentWindow;
    }
    GameBoard game(difficulty);
    std::vector<std::vector<std::vector<std::string>>> gameboard = game.getBoards();
    currentWindow = new GameWindow(1600, 1200, "Game Board", game);
    static_cast<GameWindow*>(currentWindow)->updateGameGUI();
    currentWindow->end();
    currentWindow->show();
}

void playGame(std::string filename) {
    if (currentWindow) {
        currentWindow->hide();
        delete currentWindow;
    }
    GameBoard game(filename);
    game.set_filename(filename);
    std::vector<std::vector<std::vector<std::string>>> gameboard = game.getBoards();
    currentWindow = new GameWindow(1600, 1200, "Game Board", game);
    static_cast<GameWindow*>(currentWindow)->updateGameGUI();
    currentWindow->end();
    currentWindow->show();
}
