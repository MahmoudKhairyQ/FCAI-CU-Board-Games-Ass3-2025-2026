#include "5x5_Tik_tac_toe_ui.h"
#include <iostream>
#include <cstdlib>


Tic_tac_toe_ui::Tic_tac_toe_ui(Tik_tac_toe_B& b, bool ai) : board(b), vsAI(ai) {}

void Tic_tac_toe_ui::getMove(int& row, int& col) {
    while (true) {
        std::cout << "Enter row and column (0-4): ";
        if (!(std::cin >> row >> col)) {
            std::cout << "Invalid input. Please enter numbers.\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }
        if (row < 0 || row > 4 || col < 0 || col > 4) {
            std::cout << "Invalid position. Try again.\n";
        }
        else {
            break;
        }
    }
}

void Tic_tac_toe_ui::getAIMove(int& row, int& col) {
    // Simple AI: pick a random empty cell
    do {
        row = rand() % 5;
        col = rand() % 5;
    } while (!board.isCellEmpty(row, col));
    
    std::cout << "AI plays at row " << row << ", col " << col << "\n";
}

void Tic_tac_toe_ui::playGame() {
    int currentPlayer = 1;
    char symbol;

    while (true) {
        board.displayBoard();

        symbol = (currentPlayer == 1) ? 'X' : 'O';
        
        int row, col;
        
        if (currentPlayer == 2 && vsAI) {
            std::cout << "AI (O) - Thinking...\n";
            getAIMove(row, col);
        } else {
            std::cout << "Player " << currentPlayer << " (" << symbol << ") - Your turn\n";
            getMove(row, col);
        }

        if (!board.placeSymbol(row, col, symbol)) {
            std::cout << "Cell occupied. Try again.\n";
            continue;
        }

        if (board.checkWin()) {
            board.displayBoard();

            int countX = board.countThreeInRow('X');
            int countO = board.countThreeInRow('O');

            std::cout << "=== GAME OVER ===\n";
            std::cout << "Player 1 (X): " << countX << " three-in-a-rows\n";
            if (vsAI) {
                std::cout << "AI (O): " << countO << " three-in-a-rows\n";
            } else {
                std::cout << "Player 2 (O): " << countO << " three-in-a-rows\n";
            }

            if (countX > countO) {
                std::cout << "Player 1 (X) wins!\n";
            }
            else if (countO > countX) {
                if (vsAI) {
                    std::cout << "AI (O) wins!\n";
                } else {
                    std::cout << "Player 2 (O) wins!\n";
                }
            }
            else {
                std::cout << "It's a draw!\n";
            }
            break;
        }

        currentPlayer = (currentPlayer == 1) ? 2 : 1;
    }
}