#include "Numerical_UI.h"
#include <iostream>

NumericalUI::NumericalUI(NumericalBoard& b) : board(b) {}

int NumericalUI::getPlayerInput(int player) {
    int num;
    while (true) {
        if (player == 1)
            std::cout << "Player 1 (odd), enter your number (1,3,5,7,9): ";
        else
			std::cout << "Player 2 (even), enter your number (2,4,6,8): ";
        std::cin >> num;
        if (player == 1 && (num % 2 == 0)) {
            std::cout << "Player 1 must use odd numbers.\n";
        }
        else if (player == 2 && (num % 2 != 0)) {
            std::cout << "Player 2 must use even numbers.\n";
        }
        else if (board.isNumberUsed(num)) {
            std::cout << "Number already used. Try again.\n";
        }
        else if (num < 1 || num > 9) {
            std::cout << "Invalid number. Choose 1-9.\n";
        }
        else {
            break;
        }
    }
    return num;
}

void NumericalUI::getMove(int& row, int& col) {
    while (true) {
        std::cout << "Enter row and column (0-2): ";
        std::cin >> row >> col;
        if (row < 0 || row > 2 || col < 0 || col > 2) {
            std::cout << "Invalid position. Try again.\n";
        }
        else {
            break;
        }
    }
}

void NumericalUI::playGame() {
    int currentPlayer = 1;
    while (true) {
        board.displayBoard();
        int num = getPlayerInput(currentPlayer);
        int row, col;
        getMove(row, col);
        if (!board.placeNumber(row, col, num)) {
            std::cout << "Cell occupied or number used. Try again.\n";
            continue;
        }

        if (board.checkWin()) {
            board.displayBoard();
            std::cout << "Player " << currentPlayer << " wins!\n";
            break;
        }

        if (board.checkDraw()) {
            board.displayBoard();
            std::cout << "It's a draw!\n";
            break;
        }

        currentPlayer = (currentPlayer == 1) ? 2 : 1;
    }
}
