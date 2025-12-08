#include "Diamond_Board.h"
#include <iostream>
#include <algorithm>

DiamondBoard::DiamondBoard() : Board(5, 5) {
    for (int i = 0; i < 5; ++i)
        for (int j = 0; j < 5; ++j)
            board[i][j] = ' ';

    static const bool pattern[5][5] = {
        {0, 0, 1, 0, 0},
        {0, 1, 1, 1, 0},
        {1, 1, 1, 1, 1},
        {0, 1, 1, 1, 0},
        {0, 0, 1, 0, 0}
    };

    for (int i = 0; i < 5; ++i)
        for (int j = 0; j < 5; ++j)
            validCell[i][j] = pattern[i][j];
}


bool DiamondBoard::isValidPosition(int row, int col) const {
    if (row < 0 || row >= 5 || col < 0 || col >= 5)
        return false;
    return validCell[row][col];
}

bool DiamondBoard::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char symbol = move->get_symbol();

    if (!isValidPosition(x, y) || board[x][y] != ' ')
        return false;

    board[x][y] = symbol;
    n_moves++;
    return true;
}

bool DiamondBoard::hasThreeInLine(char symbol, int& lineType) const {

    for (int row = 0; row < 5; ++row) {
        for (int col = 0; col <= 2; ++col) {
            if (isValidPosition(row, col) && isValidPosition(row, col + 1) && isValidPosition(row, col + 2)) {
                if (board[row][col] == symbol && board[row][col + 1] == symbol && board[row][col + 2] == symbol) {
                    lineType = 1;
                    return true;
                }
            }
        }
    }

    for (int row = 0; row <= 2; ++row) {
        for (int col = 0; col < 5; ++col) {
            if (isValidPosition(row, col) && isValidPosition(row + 1, col) && isValidPosition(row + 2, col)) {
                if (board[row][col] == symbol && board[row + 1][col] == symbol && board[row + 2][col] == symbol) {
                    lineType = 2;
                    return true;
                }
            }
        }
    }

    for (int row = 0; row <= 2; ++row) {
        for (int col = 0; col <= 2; ++col) {
            if (isValidPosition(row, col) && isValidPosition(row + 1, col + 1) && isValidPosition(row + 2, col + 2)) {
                if (board[row][col] == symbol && board[row + 1][col + 1] == symbol && board[row + 2][col + 2] == symbol) {
                    lineType = 3;
                    return true;
                }
            }
        }
    }

    for (int row = 0; row <= 2; ++row) {
        for (int col = 2; col < 5; ++col) {
            if (isValidPosition(row, col) && isValidPosition(row + 1, col - 1) && isValidPosition(row + 2, col - 2)) {
                if (board[row][col] == symbol && board[row + 1][col - 1] == symbol && board[row + 2][col - 2] == symbol) {
                    lineType = 4;
                    return true;
                }
            }
        }
    }

    return false;
}

bool DiamondBoard::hasFourInLine(char symbol, int& lineType) const {

    for (int row = 0; row < 5; ++row) {
        for (int col = 0; col <= 1; ++col) {
            if (isValidPosition(row, col) && isValidPosition(row, col + 1) &&
                isValidPosition(row, col + 2) && isValidPosition(row, col + 3)) {
                if (board[row][col] == symbol && board[row][col + 1] == symbol &&
                    board[row][col + 2] == symbol && board[row][col + 3] == symbol) {
                    lineType = 1;
                    return true;
                }
            }
        }
    }

    for (int row = 0; row <= 1; ++row) {
        for (int col = 0; col < 5; ++col) {
            if (isValidPosition(row, col) && isValidPosition(row + 1, col) &&
                isValidPosition(row + 2, col) && isValidPosition(row + 3, col)) {
                if (board[row][col] == symbol && board[row + 1][col] == symbol &&
                    board[row + 2][col] == symbol && board[row + 3][col] == symbol) {
                    lineType = 2;
                    return true;
                }
            }
        }
    }

    for (int row = 0; row <= 1; ++row) {
        for (int col = 0; col <= 1; ++col) {
            if (isValidPosition(row, col) && isValidPosition(row + 1, col + 1) &&
                isValidPosition(row + 2, col + 2) && isValidPosition(row + 3, col + 3)) {
                if (board[row][col] == symbol && board[row + 1][col + 1] == symbol &&
                    board[row + 2][col + 2] == symbol && board[row + 3][col + 3] == symbol) {
                    lineType = 3;
                    return true;
                }
            }
        }
    }

    for (int row = 0; row <= 1; ++row) {
        for (int col = 3; col < 5; ++col) {
            if (isValidPosition(row, col) && isValidPosition(row + 1, col - 1) &&
                isValidPosition(row + 2, col - 2) && isValidPosition(row + 3, col - 3)) {
                if (board[row][col] == symbol && board[row + 1][col - 1] == symbol &&
                    board[row + 2][col - 2] == symbol && board[row + 3][col - 3] == symbol) {
                    lineType = 4;
                    return true;
                }
            }
        }
    }

    return false;
}

bool DiamondBoard::is_win(Player<char>* player) {
    char symbol = player->get_symbol();
    int threeLineType = 0, fourLineType = 0;

    bool hasThree = hasThreeInLine(symbol, threeLineType);
    bool hasFour = hasFourInLine(symbol, fourLineType);

    if (hasThree && hasFour) {
        if (threeLineType != fourLineType) {
            return true;
        }
    }

    return false;
}

bool DiamondBoard::is_lose(Player<char>* player) {
    return false;
}

bool DiamondBoard::is_draw(Player<char>* player) {
    if (is_win(player)) return false;

    int validCellsCount = 0;
    for (int i = 0; i < 5; ++i)
        for (int j = 0; j < 5; ++j)
            if (validCell[i][j]) validCellsCount++;

    return (n_moves >= validCellsCount);
}

bool DiamondBoard::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}
