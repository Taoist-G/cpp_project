#include "CommandLineInterface.h"
#include <iostream>

void CommandLineInterface::displayGame(const GameBoard& game, int difficulty) const {
    game.printBoard(difficulty);
}

void CommandLineInterface::displayMainMenu() const {
    std::cout << "Welcome to Sokoban!\n";
    std::cout << "1. Level 1\n";
    std::cout << "2. Level 2\n";
    std::cout << "3. Level 3\n";
    std::cout << "E. Exit\n";
    std::cout << "Select level : ";
}
