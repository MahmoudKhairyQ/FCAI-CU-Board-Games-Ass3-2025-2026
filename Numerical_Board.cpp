#include "Numerical_Board.h"
#include <iostream>
#include <algorithm>

NumericalBoard::NumericalBoard() {
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            board[i][j] = 0;   // 0 = empty
}

bool NumericalBoard::isNumberUsed(int num) {
    return std::find(usedNumbers.begin(), usedNumbers.end(), num) != usedNumbers.end();
}

bool NumericalBoard::placeNumber(int row, int col, int num) {
    if (board[row][col] != 0 || isNumberUsed(num))
        return false;
    board[row][col] = num;
    usedNumbers.push_back(num);
    return true;
}

bool NumericalBoard::checkWin() {
    int sum;

    // Check rows
    for (int i = 0; i < 3; ++i) {
        if (board[i][0] != 0 && board[i][1] != 0 && board[i][2] != 0) {
            sum = board[i][0] + board[i][1] + board[i][2];
            if (sum == 15) return true;
        }
    }

    // Check columns
    for (int i = 0; i < 3; ++i) {
        if (board[0][i] != 0 && board[1][i] != 0 && board[2][i] != 0) {
            sum = board[0][i] + board[1][i] + board[2][i];
            if (sum == 15) return true;
        }
    }

    // Check diagonals
    if (board[0][0] != 0 && board[1][1] != 0 && board[2][2] != 0) {
        sum = board[0][0] + board[1][1] + board[2][2];
        if (sum == 15) return true;
    }

    if (board[0][2] != 0 && board[1][1] != 0 && board[2][0] != 0) {
        sum = board[0][2] + board[1][1] + board[2][0];
        if (sum == 15) return true;
    }

    return false;
}


bool NumericalBoard::checkDraw() {
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (board[i][j] == 0)
                return false;
    return !checkWin();
}

void NumericalBoard::displayBoard() {
    std::cout << "\n===============================\n";
    std::cout << "          GAME BOARD          \n";
    std::cout << "===============================\n\n";
    
    for (int i = 0; i < 3; ++i) {
        std::cout << " ";
        for (int j = 0; j < 3; ++j) {
        if (board[i][j] == 0)
      std::cout << " . ";
         else if (board[i][j] < 10)
       std::cout << " " << board[i][j] << " ";
            else
   std::cout << board[i][j] << " ";
          
      if (j < 2)
      std::cout << "|";
        }
     std::cout << "\n";
    
        if (i < 2) {
   std::cout << "       -----------\n";
        }
    }
    
    std::cout << "\n===============================\n";
    std::cout << "  Row/Col indices: 0, 1, 2\n\n";
}
