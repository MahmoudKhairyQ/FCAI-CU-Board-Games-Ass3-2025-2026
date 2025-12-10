#include "Word_Tic_tac_ui.h"
#include <iostream>
#include <cstdlib>

Word_Tik_tak_UI::Word_Tik_tak_UI(Word_Tik_tak_Board& b, bool ai) : board(b), vsAI(ai) {}

void Word_Tik_tak_UI::getMove(int& row, int& col, char& letter) {
    while (true) {
        std::cout << "Enter row (0-2), column (0-2), and letter (A-Z): ";
        std::cin >> row >> col >> letter;
        
        // Validate row and column
        if (row < 0 || row > 2 || col < 0 || col > 2) {
            std::cout << "Invalid position! Row and column must be 0, 1, or 2.\n";
            continue;
        }
        
        // Validate letter
        letter = toupper(letter);
        if (letter < 'A' || letter > 'Z') {
            std::cout << "Invalid letter! Please enter A-Z.\n";
            continue;
        }
        
        break;
    }
}

void Word_Tik_tak_UI::getAIMove(int& row, int& col, char& letter) {
    // Simple AI: pick a random empty cell and a random letter
    do {
        row = rand() % 3;
        col = rand() % 3;
    } while (!board.isCellEmpty(row, col));
    
    // Pick a random letter A-Z
    letter = 'A' + (rand() % 26);
    
    std::cout << "AI plays: row " << row << ", col " << col << ", letter " << letter << "\n";
}

void Word_Tik_tak_UI::playGame() {
    int currentPlayer = 1;
    
    std::cout << "\n========================================\n";
    std::cout << "       WORD TIC-TAC-TOE RULES\n";
    std::cout << "========================================\n";
    std::cout << "- Place letters (A-Z) on a 3x3 board\n";
    std::cout << "- Form a valid 3-letter word to win!\n";
    std::cout << "- Words can be horizontal, vertical,\n";
    std::cout << "  or diagonal\n";
    std::cout << "- Players take turns placing one letter\n";
    std::cout << "========================================\n";
    
    while (true) {
        board.displayBoard();
        
        int row, col;
        char letter;
        
        if (currentPlayer == 2 && vsAI) {
            std::cout << "AI's turn...\n";
            getAIMove(row, col, letter);
        } else {
            std::cout << "Player " << currentPlayer << " - Your turn\n";
            getMove(row, col, letter);
        }
        
        // Try to place the letter
        if (!board.placeLetter(row, col, letter)) {
            std::cout << "That cell is already occupied! Try again.\n";
            continue;
        }
        
        // Check for win
        if (board.checkWin()) {
            board.displayBoard();
            std::cout << "=== GAME OVER ===\n";
            if (currentPlayer == 2 && vsAI) {
                std::cout << "AI wins!\n";
            } else {
                std::cout << "Player " << currentPlayer << " wins!\n";
            }
            std::cout << "Winning word: " << board.getWinningWord() << "\n";
            break;
        }
        
        // Check for draw
        if (board.checkDraw()) {
            board.displayBoard();
            std::cout << "=== GAME OVER ===\n";
            std::cout << "It's a draw! No valid word was formed.\n";
            break;
        }
        
        // Switch player
        currentPlayer = (currentPlayer == 1) ? 2 : 1;
    }
}
