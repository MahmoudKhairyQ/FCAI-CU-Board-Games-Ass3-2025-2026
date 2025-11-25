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
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input. Enter a number.\n";
            continue;
        }

        if (num < 1 || num > 9) {
            std::cout << "Invalid number. Choose 1-9.\n";
        }
        else if (player == 1 && (num % 2 == 0)) {
            std::cout << "Player 1 must use odd numbers.\n";
        }
        else if (player == 2 && (num % 2 != 0)) {
            std::cout << "Player 2 must use even numbers.\n";
        }
        else if (board.isNumberUsed(num)) {
            std::cout << "Number already used. Try again.\n";
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
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input. Enter two numbers.\n";
            continue;
        }
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

// SUS

SUSUI::SUSUI(SUSBoard& b) : board(b) {
    for (int i = 0; i < 3; ++i) {
        playerLetter[i] = '\0';
        score[i] = 0;
    }

    playerLetter[1] = 'S';
    playerLetter[2] = 'U';
}

char SUSUI::choosePlayer1Letter() {
    char ch;
    while (true) {
        std::cout << "Player 1: choose your letter ('S' or 'U'): ";
        std::cin >> ch;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input. Enter S or U.\n";
            continue;
        }
        if (ch == 'S' || ch == 's') return 'S';
        if (ch == 'U' || ch == 'u') return 'U';
        std::cout << "Invalid choice. Enter S or U.\n";
    }
}

void SUSUI::getMove(int& row, int& col) {
    while (true) {
        std::cout << "Enter row and column (0-2): ";
        std::cin >> row >> col;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input. Enter two numbers.\n";
            continue;
        }
        if (row < 0 || row > 2 || col < 0 || col > 2) {
            std::cout << "Invalid position. Try again.\n";
        }
        else {
            break;
        }
    }
}

void SUSUI::playGame() {
    playerLetter[1] = choosePlayer1Letter();
    playerLetter[2] = (playerLetter[1] == 'S') ? 'U' : 'S';
    std::cout << "Player 1 is '" << playerLetter[1] << "', Player 2 is '" << playerLetter[2] << "'\n\n";

    int currentPlayer = 1;
    while (true) {
        board.displayBoard();
        std::cout << "Score - Player1: " << score[1] << "  Player2: " << score[2] << "\n";
        std::cout << "Player " << currentPlayer << " (" << playerLetter[currentPlayer] << ")'s turn.\n";

        int row, col;
        getMove(row, col);

        int points = 0;
        if (!board.placeLetter(row, col, playerLetter[currentPlayer], points)) {
            std::cout << "Cell occupied or invalid. Try again.\n";
            continue;
        }

        if (points > 0) {
            score[currentPlayer] += points;
            std::cout << "Player " << currentPlayer << " scored " << points << " point(s)!\n";
        }

        if (board.isFull()) {
            board.displayBoard();
            std::cout << "\nFinal Score - Player1: " << score[1] << "  Player2: " << score[2] << "\n";
            if (score[1] > score[2]) std::cout << "Player 1 wins!\n";
            else if (score[2] > score[1]) std::cout << "Player 2 wins!\n";
            else std::cout << "It's a tie!\n";
            break;
        }

        currentPlayer = (currentPlayer == 1) ? 2 : 1;
    }
}

// Obstacles Tic-Tac-Toe

ObstaclesUI::ObstaclesUI(ObstaclesBoard& b) : board(b) {}

void ObstaclesUI::getMove(int& row, int& col, int player) {
    while (true) {
        std::cout << "Player " << player << " (" << (player == 1 ? 'O' : 'X') << "), enter row and column (0-5): ";
        std::cin >> row >> col;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input. Enter two numbers.\n";
            continue;
        }
        if (row < 0 || row > 5 || col < 0 || col > 5) {
            std::cout << "Invalid position. Try again.\n";
        }
        else if (!board.isValidMove(row, col)) {
            std::cout << "Cell occupied or blocked. Try again.\n";
        }
        else {
            break;
        }
    }
}

void ObstaclesUI::playGame() {
    srand(time(0));
    int currentPlayer = 1;
    int movesInCurrentRound = 0;

    while (true) {
        board.displayBoard();

        int row, col;
        getMove(row, col, currentPlayer);

        char symbol = (currentPlayer == 1) ? 'O' : 'X';
        board.placeMove(row, col, symbol);

        if (board.checkWin(symbol)) {
            board.displayBoard();
            std::cout << "Player " << currentPlayer << " wins!\n";
            break;
        }

        if (board.checkDraw()) {
            board.displayBoard();
            std::cout << "It's a draw!\n";
            break;
        }

        movesInCurrentRound++;

        if (movesInCurrentRound == 2) {
            board.addRandomObstacles();
            movesInCurrentRound = 0;
        }

        currentPlayer = (currentPlayer == 1) ? 2 : 1;
    }
}
