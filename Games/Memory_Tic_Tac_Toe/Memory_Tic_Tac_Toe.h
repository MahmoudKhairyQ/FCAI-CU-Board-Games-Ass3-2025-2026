/**
 * @class MemoryTicTacToe
 * @brief Implements a Tic-Tac-Toe game with an AI that remembers past moves.
 *
 * This class manages a 3×3 Tic-Tac-Toe board with two layers:
 * - `board`: the actual game board storing X/O.
 * - `hidden_board`: what is shown to the player (initially all empty).
 *
 * The AI uses a memory map to store its previous moves and make
 * strategic decisions based on that memory.
 */

#ifndef MEMORY_TICTACTOE_H
#define MEMORY_TICTACTOE_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <map>


class MemoryTicTacToe {
private:
    char board[3][3];  ///< Actual board storing the current game state.
    char hidden_board[3][3]; ///< Board displayed to the player.
    std::string player1_name, player2_name; ///< Names of the two players.
    std::map<std::pair<int, int>, char> moves_memory; ///< AI memory of past moves.

    /**
     * @brief Displays the current visible board to the console.
     */
    void printBoard();

    /**
     * @brief Checks if the board has any empty cells left.
     *
     * @return True if the board is full, false otherwise.
     */
    bool isBoardFull();

    /**
     * @brief Handles a human player's move input.
     *
     * @param player Name of the player making the move.
     * @param mark Symbol used by the player ('X' or 'O').
     */
    void playerMove(const std::string& player, char mark);

    /**
     * @brief Generates and executes the AI player's move.
     *
     * The AI uses its memory of previous moves to make strategic decisions.
     *
     * @param player Name of the AI player.
     * @param mark Symbol used by the AI ('X' or 'O').
     */
    void aiMove(const std::string& player, char mark);

    /**
     * @brief Checks whether the specified player has won the game.
     *
     * Evaluates horizontal, vertical, and diagonal lines.
     *
     * @param mark Player symbol to check ('X' or 'O').
     * @return True if the player has three in a row; otherwise false.
     */
    bool checkWin(char mark);

public:
    /**
     * @brief Constructs the Memory Tic-Tac-Toe game.
     *
     * Initializes the board and sets the AI player's name.
     *
     * @param aiName Name assigned to the AI player (default: "AI_Player").
     */
    MemoryTicTacToe(const std::string& aiName = "AI_Player");

    /**
     * @brief Runs the main game loop until a win or draw occurs.
     *
     * Alternates turns between players, updates the board, and checks for win/draw.
     */
    void play();
};

#endif
