#include "Numerical_Board.h"
#include <iostream>

NumericalBoard::NumericalBoard() : Board(3, 3) {
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            board[i][j] = 0;
}

bool NumericalBoard::isNumberUsed(int num) {
    return std::find(usedNumbers.begin(), usedNumbers.end(), num) != usedNumbers.end();
}

bool NumericalBoard::update_board(Move<int>* move) {
    int x = move->get_x();
    int y = move->get_y();
    int num = move->get_symbol();

    if (x < 0 || x >= 3 || y < 0 || y >= 3 || board[x][y] != 0)
        return false;

    if (isNumberUsed(num))
        return false;

    board[x][y] = num;
    usedNumbers.push_back(num);
    n_moves++;
    return true;
}

bool NumericalBoard::is_win(Player<int>* player) {
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

bool NumericalBoard::is_lose(Player<int>* player) {
    return false;
}

bool NumericalBoard::is_draw(Player<int>* player) {
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (board[i][j] == 0)
                return false;
    return !is_win(player);
}

bool NumericalBoard::game_is_over(Player<int>* player) {
    return is_win(player) || is_draw(player);
}