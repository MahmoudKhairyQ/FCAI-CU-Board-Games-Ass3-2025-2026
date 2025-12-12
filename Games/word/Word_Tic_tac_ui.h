#pragma once
#include "Word_Tic_tac_board.h"

/**
 * @file Word_Tic_tac_ui.h
 * @brief Header file for the Word Tic-Tac-Toe user interface.
 */

/**
 * @class Word_Tik_tak_UI
 * @brief Handles the user interface and game flow for Word Tic-Tac-Toe.
 *
 * This class manages player interactions, input handling, and
 * coordinates the game loop between human and AI players.
 */
class Word_Tik_tak_UI {
private:
    Word_Tik_tak_Board& board;  ///< Reference to the game board.
    bool vsAI;                  ///< Flag indicating if playing against AI.

public:
    /**
     * @brief Constructor for the UI class.
     * @param b Reference to the Word_Tik_tak_Board object.
     * @param ai Set to true for Human vs AI mode, false for Human vs Human (default: false).
     */
    Word_Tik_tak_UI(Word_Tik_tak_Board& b, bool ai = false);

    /**
     * @brief Runs the main game loop until the game ends.
     */
    void playGame();

    /**
     * @brief Gets the move input from a human player.
     * @param[out] row The row index selected by the player.
     * @param[out] col The column index selected by the player.
     * @param[out] letter The letter chosen by the player.
     */
    void getMove(int& row, int& col, char& letter);

    /**
     * @brief Generates a move for the AI player.
     * @param[out] row The row index chosen by the AI.
     * @param[out] col The column index chosen by the AI.
     * @param[out] letter The letter chosen by the AI.
     */
    void getAIMove(int& row, int& col, char& letter);
};
