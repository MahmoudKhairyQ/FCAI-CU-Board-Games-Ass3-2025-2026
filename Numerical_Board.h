#pragma once
#ifndef NUMERICAL_BOARD_H
#define NUMERICAL_BOARD_H

#include <vector>

class NumericalBoard {
private:
    int board[3][3];                  // The 3x3 board
    std::vector<int> usedNumbers;     // Numbers already placed

public:
    NumericalBoard();
    bool placeNumber(int row, int col, int num);  // Place a number on the board
    bool checkWin();                             // Check if someone won
    bool checkDraw();                            // Check if board is full without a winner
    void displayBoard();                         // Print the board
    bool isNumberUsed(int num);                  // Check if number is already used
};

#endif
