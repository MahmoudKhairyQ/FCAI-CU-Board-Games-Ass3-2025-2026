#include "Obstacles_Board.h"
#include <iostream>

ObstaclesBoard::ObstaclesBoard() : Board(6, 6), obstaclesCount(0), movesSinceLastObstacle(0) {
    for (int i = 0; i < 6; ++i)
        for (int j = 0; j < 6; ++j)
            board[i][j] = ' ';
    srand(time(0));
}

bool ObstaclesBoard::check_four_in_row(char symbol) {
    // Check horizontal
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == symbol && board[i][j+1] == symbol &&
                board[i][j+2] == symbol && board[i][j+3] == symbol)
                return true;
        }
    }

    // Check vertical
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 6; ++j) {
            if (board[i][j] == symbol && board[i+1][j] == symbol &&
                board[i+2][j] == symbol && board[i+3][j] == symbol)
                return true;
        }
    }

    // Check diagonals
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == symbol && board[i+1][j+1] == symbol &&
                board[i+2][j+2] == symbol && board[i+3][j+3] == symbol)
                return true;
        }
    }

    for (int i = 0; i < 3; ++i) {
        for (int j = 3; j < 6; ++j) {
            if (board[i][j] == symbol && board[i+1][j-1] == symbol &&
                board[i+2][j-2] == symbol && board[i+3][j-3] == symbol)
                return true;
        }
    }

    return false;
}

bool ObstaclesBoard::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char symbol = move->get_symbol();

    if (x < 0 || x >= 6 || y < 0 || y >= 6 || board[x][y] != ' ')
        return false;

    board[x][y] = symbol;
    n_moves++;
    movesSinceLastObstacle++;

    // Add obstacles every 2 moves
    if (movesSinceLastObstacle >= 2) {
        addRandomObstacles();
        movesSinceLastObstacle = 0;
    }

    return true;
}

void ObstaclesBoard::addRandomObstacles() {
    int added = 0;
    while (added < 2 && obstaclesCount < 30) { // Leave some space for moves
        int row = rand() % 6;
        int col = rand() % 6;
        if (board[row][col] == ' ') {
            board[row][col] = '#';
            obstaclesCount++;
            added++;
        }
    }
}

bool ObstaclesBoard::is_win(Player<char>* player) {
    return check_four_in_row(player->get_symbol());
}

bool ObstaclesBoard::is_lose(Player<char>* player) {
    char opponent_symbol = (player->get_symbol() == 'X') ? 'O' : 'X';
    return check_four_in_row(opponent_symbol);
}

bool ObstaclesBoard::is_draw(Player<char>* player) {
    for (int i = 0; i < 6; ++i)
        for (int j = 0; j < 6; ++j)
            if (board[i][j] == ' ')
                return false;
    return true;
}

bool ObstaclesBoard::game_is_over(Player<char>* player) {
    return is_win(player) || is_lose(player) || is_draw(player);
}