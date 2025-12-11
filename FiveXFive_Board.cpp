#include "FiveXFive_Board.h"
#include <iostream>

FiveXFiveBoard::FiveXFiveBoard() : Board(5, 5) {
    for (int i = 0; i < 5; ++i)
        for (int j = 0; j < 5; ++j)
            board[i][j] = ' ';
}

bool FiveXFiveBoard::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char symbol = move->get_symbol();

    if (x < 0 || x >= 5 || y < 0 || y >= 5 || board[x][y] != ' ')
        return false;

    board[x][y] = symbol;
    n_moves++;
    return true;
}

int FiveXFiveBoard::countThreeInRow(char symbol) {
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

    // Check diagonals
    for (int i = 0; i <= 2; ++i) {
        for (int j = 0; j <= 2; ++j) {
            if (board[i][j] == symbol && board[i+1][j+1] == symbol && board[i+2][j+2] == symbol)
                count++;
        }
    }

    for (int i = 0; i <= 2; ++i) {
        for (int j = 2; j < 5; ++j) {
            if (board[i][j] == symbol && board[i+1][j-1] == symbol && board[i+2][j-2] == symbol)
                count++;
        }
    }

    return count;
}

bool FiveXFiveBoard::is_win(Player<char>* player) {
    // Win is determined by having more three-in-a-rows when board is full
    return n_moves >= 24;
}

bool FiveXFiveBoard::is_lose(Player<char>* player) {
    return false;
}

bool FiveXFiveBoard::is_draw(Player<char>* player) {
    if (n_moves < 24) return false;

    char playerSymbol = player->get_symbol();
    char opponentSymbol = (playerSymbol == 'X') ? 'O' : 'X';

    int playerCount = countThreeInRow(playerSymbol);
    int opponentCount = countThreeInRow(opponentSymbol);

    return playerCount == opponentCount;
}

bool FiveXFiveBoard::game_is_over(Player<char>* player) {
    return n_moves >= 24;
}