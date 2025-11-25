#include "Tic_tac_toe_board.h"
#include <iostream>

Tik_tac_toe_B::Tik_tac_toe_B() : moveCount(0) {
    for (int i = 0; i < 5; ++i)
        for (int j = 0; j < 5; ++j)
            board[i][j] = ' ';
}

bool Tik_tac_toe_B::placeSymbol(int row, int col, char symbol) {
    if (row < 0 || row >= 5 || col < 0 || col >= 5)
        return false;
    if (board[row][col] != ' ')
        return false;
    board[row][col] = symbol;
    moveCount++;
    return true;
}

int Tik_tac_toe_B::countThreeInRow(char symbol) {
    int count = 0;
    
    // Check horizontal
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j <= 2; ++j) {
            if (board[i][j] == symbol && board[i][j+1] == symbol && board[i][j+2] == symbol)
                count++;
        }
    }
    
    // Check vertical
    for (int i = 0; i <= 2; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (board[i][j] == symbol && board[i+1][j] == symbol && board[i+2][j] == symbol)
                count++;
        }
    }
    
    // Check diagonal (top-left to bottom-right)
    for (int i = 0; i <= 2; ++i) {
        for (int j = 0; j <= 2; ++j) {
            if (board[i][j] == symbol && board[i+1][j+1] == symbol && board[i+2][j+2] == symbol)
                count++;
        }
    }
    
    // Check diagonal (top-right to bottom-left)
    for (int i = 0; i <= 2; ++i) {
        for (int j = 2; j < 5; ++j) {
            if (board[i][j] == symbol && board[i+1][j-1] == symbol && board[i+2][j-2] == symbol)
                count++;
        }
    }
    
    return count;
}

bool Tik_tac_toe_B::checkWin() {
    return moveCount >= 24;
}

bool Tik_tac_toe_B::checkDraw() {
    if (moveCount < 24)
        return false;
    return countThreeInRow('X') == countThreeInRow('O');
}

void Tik_tac_toe_B::displayBoard() {
    std::cout << "\n===============================\n";
    std::cout << "          GAME BOARD          \n";
    std::cout << "===============================\n\n";
    
    for (int i = 0; i < 5; ++i) {
        std::cout << " ";
        for (int j = 0; j < 5; ++j) {
            if (board[i][j] == ' ')
                std::cout << " . ";
            else
                std::cout << " " << board[i][j] << " ";
            
            if (j < 4)
                std::cout << "|";
        }
        std::cout << "\n";
        
        if (i < 4) {
            std::cout << "       -------------------\n";
        }
    }
    
    std::cout << "\n===============================\n";
    std::cout << "  Row/Col indices: 0, 1, 2, 3, 4\n";
    std::cout << "  Moves: " << moveCount << "/24\n";
    std::cout << "  X: " << countThreeInRow('X') << " | O: " << countThreeInRow('O') << "\n\n";
}

