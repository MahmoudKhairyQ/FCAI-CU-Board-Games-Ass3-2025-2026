#pragma once
#ifndef NUMERICAL_UI_H
#define NUMERICAL_UI_H

#include "Numerical_Board.h"

class NumericalUI {#pragma once
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

class SUSUI {
private:
    SUSBoard& board;
    char playerLetter[3];
    int score[3];

    void getMove(int& row, int& col);
    char choosePlayer1Letter();

public:
    SUSUI(SUSBoard& b);
    void playGame();
};

class ObstaclesUI {
private:
    ObstaclesBoard& board;

public:
    ObstaclesUI(ObstaclesBoard& b);
    void playGame();
    void getMove(int& row, int& col, int player);
};

#endif
private:
    NumericalBoard& board;

public:
    NumericalUI(NumericalBoard& b);
    void playGame();           // Main loop of the game
    int getPlayerInput(int player);  // Get number from player
    void getMove(int& row, int& col); // Get row and column
};

#endif

