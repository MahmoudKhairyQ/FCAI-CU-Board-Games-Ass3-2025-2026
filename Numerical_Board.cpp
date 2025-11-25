#include "Numerical_Board.h"
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>

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

// SUSBoard implementation

SUSBoard::SUSBoard() {
    for (int r = 0; r < 3; ++r)
        for (int c = 0; c < 3; ++c)
            board[r][c] = '\0';
    for (int i = 0; i < 8; ++i)
        claimed[i] = false;
}

bool SUSBoard::lineMatchesSUS(int lineIdx) const {
    char a = '\0', b = '\0', c = '\0';
    switch (lineIdx) {
    case 0:
        a = board[0][0]; b = board[0][1]; c = board[0][2];
        break;
    case 1:
        a = board[1][0]; b = board[1][1]; c = board[1][2];
        break;
    case 2:
        a = board[2][0]; b = board[2][1]; c = board[2][2];
        break;
    case 3:
        a = board[0][0]; b = board[1][0]; c = board[2][0];
        break;
    case 4:
        a = board[0][1]; b = board[1][1]; c = board[2][1];
        break;
    case 5:
        a = board[0][2]; b = board[1][2]; c = board[2][2];
        break;
    case 6:
        a = board[0][0]; b = board[1][1]; c = board[2][2];
        break;
    case 7:
        a = board[0][2]; b = board[1][1]; c = board[2][0];
        break;
    default:
        return false;
    }
    return (a == 'S' && b == 'U' && c == 'S');
}

bool SUSBoard::placeLetter(int row, int col, char letter, int& pointsScored) {
    pointsScored = 0;
    if (row < 0 || row > 2 || col < 0 || col > 2) return false;
    if (letter != 'S' && letter != 'U') return false;
    if (board[row][col] != '\0') return false;

    board[row][col] = letter;

    int idx;
    idx = row;
    if (!claimed[idx] && lineMatchesSUS(idx)) { claimed[idx] = true; ++pointsScored; }
    idx = 3 + col;
    if (!claimed[idx] && lineMatchesSUS(idx)) { claimed[idx] = true; ++pointsScored; }
    if (row == col) {
        idx = 6;
        if (!claimed[idx] && lineMatchesSUS(idx)) { claimed[idx] = true; ++pointsScored; }
    }
    if (row + col == 2) {
        idx = 7;
        if (!claimed[idx] && lineMatchesSUS(idx)) { claimed[idx] = true; ++pointsScored; }
    }

    return true;
}

bool SUSBoard::isFull() const {
    for (int r = 0; r < 3; ++r)
        for (int c = 0; c < 3; ++c)
            if (board[r][c] == '\0') return false;
    return true;
}

void SUSBoard::displayBoard() const {
    std::cout << "\n===============================\n";
    std::cout << "            SUS BOARD          \n";
    std::cout << "===============================\n\n";
    for (int r = 0; r < 3; ++r) {
        std::cout << " ";
        for (int c = 0; c < 3; ++c) {
            char ch = board[r][c];
            if (ch == '\0') std::cout << " . ";
            else std::cout << " " << ch << " ";
            if (c < 2) std::cout << "|";
        }
        std::cout << "\n";
        if (r < 2) std::cout << "       -----------\n";
    }
    std::cout << "\n===============================\n";
    std::cout << "  Row/Col indices: 0, 1, 2\n\n";
}

// ObstaclesBoard implementation

ObstaclesBoard::ObstaclesBoard() {
    for (int i = 0; i < 6; ++i)
        for (int j = 0; j < 6; ++j)
            board[i][j] = '.';
    obstaclesCount = 0;
    movesCount = 0;
}

bool ObstaclesBoard::isValidMove(int row, int col) {
    if (row < 0 || row >= 6 || col < 0 || col >= 6) return false;
    return board[row][col] == '.';
}

bool ObstaclesBoard::placeMove(int row, int col, char symbol) {
    if (!isValidMove(row, col)) return false;
    board[row][col] = symbol;
    movesCount++;
    return true;
}

void ObstaclesBoard::addRandomObstacles() {
    int added = 0;
    while (added < 2 && obstaclesCount < 36) {
        int row = rand() % 6;
        int col = rand() % 6;
        if (board[row][col] == '.') {
            board[row][col] = '#';
            obstaclesCount++;
            added++;
        }
    }
}

bool ObstaclesBoard::checkWin(char symbol) {
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == symbol && board[i][j + 1] == symbol &&
                board[i][j + 2] == symbol && board[i][j + 3] == symbol)
                return true;
        }
    }

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 6; ++j) {
            if (board[i][j] == symbol && board[i + 1][j] == symbol &&
                board[i + 2][j] == symbol && board[i + 3][j] == symbol)
                return true;
        }
    }

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == symbol && board[i + 1][j + 1] == symbol &&
                board[i + 2][j + 2] == symbol && board[i + 3][j + 3] == symbol)
                return true;
        }
    }

    for (int i = 0; i < 3; ++i) {
        for (int j = 3; j < 6; ++j) {
            if (board[i][j] == symbol && board[i + 1][j - 1] == symbol &&
                board[i + 2][j - 2] == symbol && board[i + 3][j - 3] == symbol)
                return true;
        }
    }

    return false;
}

bool ObstaclesBoard::checkDraw() {
    for (int i = 0; i < 6; ++i)
        for (int j = 0; j < 6; ++j)
            if (board[i][j] == '.')
                return false;
    return true;
}

bool ObstaclesBoard::isGameOver() {
    return checkWin('O') || checkWin('X') || checkDraw();
}

void ObstaclesBoard::displayBoard() {
    std::cout << "\n=========================================\n";
    std::cout << "        OBSTACLES TIC-TAC-TOE         \n";
    std::cout << "=========================================\n\n";

    std::cout << "   ";
    for (int j = 0; j < 6; ++j) std::cout << j << "   ";
    std::cout << "\n";

    for (int i = 0; i < 6; ++i) {
        std::cout << i << "  ";
        for (int j = 0; j < 6; ++j) {
            std::cout << board[i][j];
            if (j < 5) std::cout << " | ";
        }
        std::cout << "\n";
        if (i < 5) std::cout << "   " << std::string(23, '-') << "\n";
    }
    std::cout << "\n=========================================\n";
}
