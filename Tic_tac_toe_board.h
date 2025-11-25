#pragma once

#include <vector>

class Tik_tac_toe_B {
private:
    char board[5][5];                  // The 5x5 board
    int moveCount;                     // Track number of moves

public:
    Tik_tac_toe_B();
    bool placeSymbol(int row, int col, char symbol);  // Place X or O on the board
    bool checkWin();                             // Check if game is over
    bool checkDraw();                            // Check if board is full
    void displayBoard();                         // Print the board
    int countThreeInRow(char symbol);           // Count three-in-a-row for a player
};

