#pragma once
#include "5x5_Tik_tac_toe_Board.h"

/**
 * @file 5x5_Tik_tac_toe_ui.h
 * @brief Header file for the 5x5 Tic Tac Toe user interface.
 */

/**
 * @class Tic_tac_toe_ui
 * @brief Handles the user interface and game flow for 5x5 Tic Tac Toe.
 *
 * This class manages player interactions, input handling, and
 * coordinates the game loop between human and AI players.
 */
class Tic_tac_toe_ui
{
private:
	Tik_tac_toe_B& board;   ///< Reference to the game board.
	bool vsAI;              ///< Flag indicating if playing against AI.

public:
	/**
	 * @brief Constructor for the UI class.
	 * @param b Reference to the Tik_tac_toe_B board object.
	 * @param ai Set to true for Human vs AI mode, false for Human vs Human (default: false).
	 */
	Tic_tac_toe_ui(Tik_tac_toe_B& b, bool ai = false);

	/**
	 * @brief Runs the main game loop until the game ends.
	 */
	void playGame();

	/**
	 * @brief Gets the move input from a human player.
	 * @param[out] row The row index selected by the player.
	 * @param[out] col The column index selected by the player.
	 */
	void getMove(int& row, int& col);

	/**
	 * @brief Generates a move for the AI player.
	 * @param[out] row The row index chosen by the AI.
	 * @param[out] col The column index chosen by the AI.
	 */
	void getAIMove(int& row, int& col);
};