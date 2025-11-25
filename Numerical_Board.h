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

class SUSBoard {
private:
    char board[3][3];
    bool claimed[8];

    bool lineMatchesSUS(int lineIdx) const;

public:
    SUSBoard();
    bool placeLetter(int row, int col, char letter, int& pointsScored);
    bool isFull() const;
    void displayBoard() const;
};

class ObstaclesBoard {
private:
    char board[6][6];
    int obstaclesCount;
    int movesCount;

public:
    ObstaclesBoard();
    bool placeMove(int row, int col, char symbol);
    void addRandomObstacles();
    bool checkWin(char symbol);
    bool checkDraw();
    bool isGameOver();
    void displayBoard();
    bool isValidMove(int row, int col);
};

#endif
