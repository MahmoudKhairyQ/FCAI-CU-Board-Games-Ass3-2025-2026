#include "Misere_Board.h"
#include <iostream>

MisereBoard::MisereBoard() : Board(3, 3) {
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            board[i][j] = ' ';
}

bool MisereBoard::check_three_in_row(char symbol) {
    // Check rows
    for (int i = 0; i < 3; ++i) {
        if (board[i][0] == symbol && board[i][1] == symbol && board[i][2] == symbol)
            return true;
    }

    // Check columns
    for (int i = 0; i < 3; ++i) {
        if (board[0][i] == symbol && board[1][i] == symbol && board[2][i] == symbol)
            return true;
    }

    // Check diagonals
    if (board[0][0] == symbol && board[1][1] == symbol && board[2][2] == symbol)
        return true;
    if (board[0][2] == symbol && board[1][1] == symbol && board[2][0] == symbol)
        return true;

    return false;
}

bool MisereBoard::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char symbol = move->get_symbol();

    if (x < 0 || x >= 3 || y < 0 || y >= 3 || board[x][y] != ' ')
        return false;

    board[x][y] = symbol;
    n_moves++;
    return true;
}

bool MisereBoard::is_win(Player<char>* player) {
    char player_symbol = player->get_symbol();
    char opponent_symbol = (player_symbol == 'X') ? 'O' : 'X';

    // You win if opponent made three in a row OR board is full without you making three
    if (check_three_in_row(opponent_symbol) || (n_moves == 9 && !check_three_in_row(player_symbol))) {
        return true;
    }

    return false;
}

bool MisereBoard::is_lose(Player<char>* player) {
    // You lose if you make three in a row
    return check_three_in_row(player->get_symbol());
}

bool MisereBoard::is_draw(Player<char>* player) {
    return false; // Draw handled in is_win
}

bool MisereBoard::game_is_over(Player<char>* player) {
    char player_symbol = player->get_symbol();
    char opponent_symbol = (player_symbol == 'X') ? 'O' : 'X';

    return check_three_in_row(player_symbol) || 
           check_three_in_row(opponent_symbol) || 
           n_moves == 9;
}