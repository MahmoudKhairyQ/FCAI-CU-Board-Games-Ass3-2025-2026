#pragma once
#ifndef NUMERICAL_UI_H
#define NUMERICAL_UI_H

#include "Numerical_Board.h"

class NumericalUI {
private:
    NumericalBoard& board;

public:
    NumericalUI(NumericalBoard& b);
    void playGame();           // Main loop of the game
    int getPlayerInput(int player);  // Get number from player
    void getMove(int& row, int& col); // Get row and column
};

#endif
