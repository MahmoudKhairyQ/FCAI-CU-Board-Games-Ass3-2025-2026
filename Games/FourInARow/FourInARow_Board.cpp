#include "FourInARow_Board.h"
#include <iostream>

FourInARowBoard::FourInARowBoard() : Board<char>(6, 7) {
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < columns; ++j)
            board[i][j] = ' ';
}

bool FourInARowBoard::update_board(Move<char>* move) {
    if (!move) return false;
    int col = move->get_y();
    char symbol = move->get_symbol();

    if (col < 0 || col >= columns) return false;

    // find the first empty row from the bottom
    int placeRow = -1;
    for (int r = rows - 1; r >= 0; --r) {
        if (board[r][col] == ' ') {
            placeRow = r;
            break;
        }
    }
    if (placeRow == -1) return false;

    board[placeRow][col] = symbol;
    n_moves++;
    return true;
}

bool FourInARowBoard::is_win(Player<char>* player) {
    if (!player) return false;
    char sym = player->get_symbol();

    int rows = get_rows();
    int columns = get_columns();

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            if (board[i][j] != sym) continue;

            // Check horizontal
            if (j + 3 < columns) {
                if (board[i][j] == sym && board[i][j + 1] == sym &&
                    board[i][j + 2] == sym && board[i][j + 3] == sym)
                    return true;
            }

            // Check vertical
            if (i + 3 < rows) {
                if (board[i][j] == sym && board[i + 1][j] == sym &&
                    board[i + 2][j] == sym && board[i + 3][j] == sym)
                    return true;
            }

            // Check diagonal down-right
            if (i + 3 < rows && j + 3 < columns) {
                if (board[i][j] == sym && board[i + 1][j + 1] == sym &&
                    board[i + 2][j + 2] == sym && board[i + 3][j + 3] == sym)
                    return true;
            }

            // Check diagonal down-left
            if (i + 3 < rows && j - 3 >= 0) {
                if (board[i][j] == sym && board[i + 1][j - 1] == sym &&
                    board[i + 2][j - 2] == sym && board[i + 3][j - 3] == sym)
                    return true;
            }
        }
    }
    return false;
}

bool FourInARowBoard::is_lose(Player<char>* player) {
    (void)player;  // Unused parameter
    return false;
}

bool FourInARowBoard::is_draw(Player<char>* player) {
    (void)player;  // Unused parameter
    return n_moves >= (rows * columns);
}

bool FourInARowBoard::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}