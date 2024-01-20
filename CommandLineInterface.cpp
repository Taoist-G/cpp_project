#include "CommandLineInterface.h"
#include <iostream>

void CommandLineInterface::displayGame(const GameBoard& game, int difficulty) const {
    game.printBoard(difficulty);
}

void CommandLineInterface::displayGame(const GameBoard& game, std::string filename) const {
    game.printBoard(filename);
}

void CommandLineInterface::displayMainMenu() const {
    std::cout << "Welcome to Sokoban!\n";
    std::cout << "1. Level 1\n";
    std::cout << "2. Level 2\n";
    std::cout << "3. Level 3\n";
    std::cout << "4. Level 4\n";
    std::cout << "5. Level 5\n";
    std::cout << "6. Load game\n";
    std::cout << "E. Exit\n";
    std::cout << "Select level : ";
}
