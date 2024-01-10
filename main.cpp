#include <iostream>
#include "GameBoard.h"
#include "CommandLineInterface.h"

void playGame(int difficulty);

int main() {
    CommandLineInterface cli;

    // 初始菜单循环
    while (true) {
        cli.displayMainMenu();

        char menuChoice;
        std::cin >> menuChoice;

        switch (menuChoice) {
            case '1':
                playGame(0);
                break;
            case '2':
                playGame(1);
                break;
            case '3':
                playGame(2);
                break;
            case 'E':
            case 'e':
                std::cout << "Exiting the game. Goodbye!\n";
                return 0;
            default:
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
                break;
            case 'A':
            case 'a':
                gameBoard.movePlayer('A');
                break;
            case 'S':
            case 's':
                gameBoard.movePlayer('S');
                break;
            case 'D':
            case 'd':
                gameBoard.movePlayer('D');
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
