#pragma once
#include <vector>
#include <string>
#include <set>
using namespace std;

/**
 * @file Word_Tic_tac_board.h
 * @brief Header file for the Word Tic-Tac-Toe board game.
 */

/**
 * @class Word_Tik_tak_Board
 * @brief Represents a 3x3 Word Tic-Tac-Toe game board.
 *
 * This class manages a word-based tic-tac-toe game where players
 * place letters to form valid 3-letter words from a dictionary.
 */
class Word_Tik_tak_Board {
private:
    char board[3][3];           ///< The 3x3 game board array.
    int moveCount;              ///< Tracks the number of moves made.
    set<string> dictionary;     ///< Set of valid 3-letter words loaded from dictionary file.

public:
    /**
     * @brief Default constructor. Initializes the board and loads the dictionary.
     */
    Word_Tik_tak_Board();

    /**
     * @brief Loads valid words from a dictionary file.
     * @param filename The path to the dictionary file (e.g., "dic.txt").
     */
    void loadDictionary(const string& filename);

    /**
     * @brief Places a letter on the board at the specified position.
     * @param row The row index (0-2).
     * @param col The column index (0-2).
     * @param letter The letter to place (A-Z).
     * @return true if the letter was placed successfully, false otherwise.
     */
    bool placeLetter(int row, int col, char letter);

    /**
     * @brief Checks if a word exists in the loaded dictionary.
     * @param word The word to validate.
     * @return true if the word is valid, false otherwise.
     */
    bool isValidWord(const string& word);

    /**
     * @brief Checks if a player has formed a valid word (win condition).
     * @return true if a valid word has been formed, false otherwise.
     */
    bool checkWin();

    /**
     * @brief Checks if the board is full with no winner (draw condition).
     * @return true if the game is a draw, false otherwise.
     */
    bool checkDraw();

    /**
     * @brief Displays the current state of the board to the console.
     */
    void displayBoard();

    /**
     * @brief Retrieves the winning word that was formed.
     * @return The winning word as a string, or empty string if no winner.
     */
    string getWinningWord();

    /**
     * @brief Checks if a specific cell on the board is empty.
     * @param row The row index (0-2).
     * @param col The column index (0-2).
     * @return true if the cell is empty, false otherwise.
     */
    bool isCellEmpty(int row, int col) const;
};