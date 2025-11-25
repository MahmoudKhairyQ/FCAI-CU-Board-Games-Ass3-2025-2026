#include "Tic_tac_toe_ui.h"
#include <iostream>


Tic_tac_toe_ui::Tic_tac_toe_ui(Tik_tac_toe_B& b) : board(b) {}

void Tic_tac_toe_ui::getMove(int& row, int& col) {
    while (true) {
        std::cout << "Enter row and column (0-4): ";
        std::cin >> row >> col;
        if (row < 0 || row > 4 || col < 0 || col > 4) {
            std::cout << "Invalid position. Try again.\n";
        }
        else {
            break;
        }
    }
}

void Tic_tac_toe_ui::playGame() {
    int currentPlayer = 1;
    char symbol;
    
    while (true) {
        board.displayBoard();
        
        symbol = (currentPlayer == 1) ? 'X' : 'O';
        std::cout << "Player " << currentPlayer << " (" << symbol << ") - Your turn\n";
        
        int row, col;
        getMove(row, col);
        
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
            std::cout << "Player 2 (O): " << countO << " three-in-a-rows\n";
            
            if (countX > countO) {
                std::cout << "Player 1 (X) wins!\n";
            } else if (countO > countX) {
                std::cout << "Player 2 (O) wins!\n";
            } else {
                std::cout << "It's a draw!\n";
            }
            break;
        }
        
        currentPlayer = (currentPlayer == 1) ? 2 : 1;
    }
}

