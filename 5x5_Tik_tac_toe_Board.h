#pragma once

#include <vector>

/**
 * @file 5x5_Tik_tac_toe_Board.h
 * @brief Header file for the 5x5 Tic Tac Toe board game.
 */

/**
 * @class Tik_tac_toe_B
 * @brief Represents a 5x5 Tic Tac Toe game board.
 *
 * This class manages the game board state, move placement,
 * win/draw detection, and counting three-in-a-row sequences.
 */
class Tik_tac_toe_B {
private:
    char board[5][5];   ///< The 5x5 game board array.
    int moveCount;      ///< Tracks the total number of moves made.

public:
    /**
     * @brief Default constructor. Initializes the board to empty state.
     */
    Tik_tac_toe_B();

    /**
     * @brief Places a symbol (X or O) on the board at the specified position.
     * @param row The row index (0-4).
     * @param col The column index (0-4).
     * @param symbol The symbol to place ('X' or 'O').
     * @return true if the symbol was placed successfully, false otherwise.
     */
    bool placeSymbol(int row, int col, char symbol);

    /**
     * @brief Checks if the game has ended (all moves made).
     * @return true if the game is over, false otherwise.
     */
    bool checkWin();

    /**
     * @brief Checks if the board is full (draw condition).
     * @return true if the board is full, false otherwise.
     */
    bool checkDraw();

    /**
     * @brief Displays the current state of the board to the console.
     */
    void displayBoard();

    /**
     * @brief Counts the number of three-in-a-row sequences for a given symbol.
     * @param symbol The symbol ('X' or 'O') to count sequences for.
     * @return The number of three-in-a-row sequences found.
     */
    int countThreeInRow(char symbol);

    /**
     * @brief Checks if a specific cell on the board is empty.
     * @param row The row index (0-4).
     * @param col The column index (0-4).
     * @return true if the cell is empty, false otherwise.
     */
    bool isCellEmpty(int row, int col) const;
};