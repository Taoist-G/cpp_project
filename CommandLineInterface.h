#pragma once
#include "GameBoard.h"

class CommandLineInterface {
public:
    void displayGame(const GameBoard& game, int difficulty) const;
    void displayGame(const GameBoard& game, std::string filename) const;
    void displayMainMenu() const;
};
