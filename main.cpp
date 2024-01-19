#include <iostream>
#include "GameBoard.h"
#include "CommandLineInterface.h"
#include <fstream>
#include <sstream>

void playGame(int difficulty);
void playGame(std::string filename);

int main() {
    CommandLineInterface cli;

    // 初始菜单循环
    while (true) {
        cli.displayMainMenu();

        char menuChoice;
        std::cin >> menuChoice;

        if (menuChoice=='1') {
            playGame(1);
        }else if (menuChoice=='2')
        {
            playGame(2);
        }else if (menuChoice=='3')
        {
            playGame(3);
        }else if (menuChoice=='4')
        {
            playGame(4);
        }else if (menuChoice=='5')
        {
            std::cout<<"please input filename: ";
            std::string filename1;
            std::cin>>filename1;
            playGame(filename1);
        }else if (menuChoice=='E'||menuChoice=='e')
        {
            std::cout << "Exiting the game. Goodbye!\n";
            return 0;
        }else {
            std::cout << "Invalid choice. Try again.\n";
        }
    }
}


void playGame(int difficulty) {
    GameBoard gameBoard(difficulty);
    CommandLineInterface cli;

    // 游戏主循环
    while (!gameBoard.isGameOver()) {
        cli.displayGame(gameBoard, difficulty);

        char choice;
        std::cin >> choice;

        switch (choice) {
            case 'W':
            case 'w':
                gameBoard.movePlayer('W');
                gameBoard.getChange();
                break;
            case 'A':
            case 'a':
                gameBoard.movePlayer('A');
                gameBoard.getChange();
                break;
            case 'S':
            case 's':
                gameBoard.movePlayer('S');
                gameBoard.getChange();
                break;
            case 'D':
            case 'd':
                gameBoard.movePlayer('D');
                gameBoard.getChange();
                break;
            case 'z':
                std::cout << "Save successfully\n";
                gameBoard.saveGameToFile("save_test");
                break;
            case 'u':
                std::cout << "undo successfully\n";
                gameBoard.undo();
                break;
            case 'R':
            case 'r':
                std::cout << "Restarting current game\n";
                playGame(difficulty);
                return;
            case 'Q':
            case 'q':
                std::cout << "Game Quit\n";
                return;
            default:
                std::cout << "Invalid choice. Try again.\n";
        }
    }

    cli.displayGame(gameBoard, difficulty);
    std::cout << "Congratulations! You've passed the level " << difficulty+1 << std::endl;
}


void playGame(std::string filename) {
    GameBoard gameBoard(filename);
    CommandLineInterface cli;

    // 游戏主循环
    while (!gameBoard.isGameOver()) {
        cli.displayGame(gameBoard, filename);

        char choice;
        std::cin >> choice;

        switch (choice) {
            case 'W':
            case 'w':
                gameBoard.movePlayer('W');
                gameBoard.getChange();
                break;
            case 'A':
            case 'a':
                gameBoard.movePlayer('A');
                gameBoard.getChange();
                break;
            case 'S':
            case 's':
                gameBoard.movePlayer('S');
                gameBoard.getChange();
                break;
            case 'D':
            case 'd':
                gameBoard.movePlayer('D');
                gameBoard.getChange();
                break;
            case 'z':
                std::cout << "Save successfully\n";
                gameBoard.saveGameToFile("save_test");
                break;
            case 'u':
                std::cout << "undo successfully\n";
                gameBoard.undo();
                break;
            case 'R':
            case 'r':
                std::cout << "Restarting current game\n";
                playGame(filename);
                return;
            case 'Q':
            case 'q':
                std::cout << "Game Quit\n";
                return;
            default:
                std::cout << "Invalid choice. Try again.\n";
        }
    }

    cli.displayGame(gameBoard, filename);
    std::cout << "Congratulations! You've passed the level " << 5 << std::endl;
}


//只需要存储哪个地图的哪个位置发生了变化以及变化前的元素，和contains变化前的四个参数。
//两个stack分别存这一步有没有导致地图元素变化或者contains变化。
//玩家每走一步，先是对前后的boards进行对比，找到有没有变化，有变化就对地图判断stack进行push(1)，所有变化位置和变化前元素存进地图stack，没变化push(0)。
//同时对前后contains进行对比，找找有没有变化，有变化就对con判断stack进行push(1)，将变化前的contains存入con_stack，没变化push(0)
//
//在进行撤销时，先对两个判断stack进行top和pop，如果是0则跳过修改，如果是1对地图或con的stack分别top和pop。
//如果地图判断是1，将对应坐标的元素改为之前存的元素；如果con判断是1，将contains清零然后存入top对应的contains。