#include "CommandLineInterface.h"
#include <iostream>

void CommandLineInterface::displayGame(const GameBoard& game, int difficulty) const {
    game.printBoard(difficulty);
}

void CommandLineInterface::displayMainMenu() const {
    std::cout << "Welcome to Sokoban!\n";
    std::cout << "1. Easy\n";
    std::cout << "2. Medium\n";
    std::cout << "3. Hard\n";
    std::cout << "E. Exit\n";
    std::cout << "Select difficulty (1-3): ";
}
