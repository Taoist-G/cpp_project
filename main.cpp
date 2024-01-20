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
            playGame(5);
        }else if (menuChoice=='6')
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

        if(choice=='W'||choice=='w') {
            gameBoard.movePlayer('W');
            gameBoard.getChange();
        }else if (choice=='A'||choice=='a')
        {
            gameBoard.movePlayer('A');
            gameBoard.getChange();
        }else if (choice=='S'||choice=='s')
        {
            gameBoard.movePlayer('S');
            gameBoard.getChange();
        }else if (choice=='D'||choice=='d')
        {
            gameBoard.movePlayer('D');
            gameBoard.getChange();
        }else if (choice=='Z'||choice=='z')
        {
            std::cout<<"please input filename: ";
            std::string filename1;
            std::cin>>filename1;
            gameBoard.saveGameToFile(filename1);
            std::cout << "Save successfully\n";
        }else if (choice=='U'||choice=='u')
        {
            std::cout << "undo successfully\n";
            gameBoard.undo();
        }else if (choice=='R'||choice=='r')
        {
            std::cout << "Restarting current game\n";
            playGame(difficulty);
            return;
        }else if (choice=='Q'||choice=='q')
        {
            std::cout << "Game Quit\n";
            return;
        }else{
            std::cout << "Invalid choice. Try again.\n";
        }
               
    }

    cli.displayGame(gameBoard, difficulty);
    std::cout << "Congratulations! You've passed the level " << difficulty << std::endl;
}


void playGame(std::string filename) {
    GameBoard gameBoard(filename);
    CommandLineInterface cli;

    // 游戏主循环
    while (!gameBoard.isGameOver()) {
        cli.displayGame(gameBoard, filename);

        char choice;
        std::cin >> choice;

        if(choice=='W'||choice=='w') {
            gameBoard.movePlayer('W');
            gameBoard.getChange();
        }else if (choice=='A'||choice=='a')
        {
            gameBoard.movePlayer('A');
            gameBoard.getChange();
        }else if (choice=='S'||choice=='s')
        {
            gameBoard.movePlayer('S');
            gameBoard.getChange();
        }else if (choice=='D'||choice=='d')
        {
            gameBoard.movePlayer('D');
            gameBoard.getChange();
        }else if (choice=='Z'||choice=='z')
        {
            std::cout<<"please input filename: ";
            std::string filename1;
            std::cin>>filename1;
            gameBoard.saveGameToFile(filename1);
            std::cout << "Save successfully\n";
        }else if (choice=='U'||choice=='u')
        {
            std::cout << "undo successfully\n";
            gameBoard.undo();
        }else if (choice=='R'||choice=='r')
        {
            std::cout << "Restarting current game\n";
            playGame(filename);
            return;
        }else if (choice=='Q'||choice=='q')
        {
            std::cout << "Game Quit\n";
            return;
        }else{
            std::cout << "Invalid choice. Try again.\n";
        }
    }

    cli.displayGame(gameBoard, filename);
    std::cout << "Congratulations! You've passed the level " << 5 << std::endl;
}
