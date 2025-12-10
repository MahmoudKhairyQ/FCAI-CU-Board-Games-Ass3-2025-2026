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

static bool check_four_at(const std::vector<std::vector<char>>& b, int r, int c, int dr, int dc, char sym) {
    for (int k = 0; k < 4; ++k) {
        int rr = r + k*dr;
        int cc = c + k*dc;
        if (rr < 0 || rr >= rows || cc < 0 || cc >= cols) return false;
        if (b[rr][cc] != sym) return false;
    }
    return true;
}

bool FourInARowBoard::is_win(Player<char>* player) {
    if (!player) return false;
    char sym = player->get_symbol();
    auto b = get_board_matrix();

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            if (b[i][j] != sym) continue;
            
            if (check_four_at(b, i, j, 0, 1, sym)) return true;
            if (check_four_at(b, i, j, 1, 0, sym)) return true;
            if (check_four_at(b, i, j, 1, 1, sym)) return true;
            if (check_four_at(b, i, j, 1, -1, sym)) return true;
        }
    }
    return false;
}

bool FourInARowBoard::is_lose(Player<char>* player) {
    (void)player;
    return false;
}

bool FourInARowBoard::is_draw(Player<char>* player) {
    (void)player;
    return n_moves >= (rows * columns);
}

bool FourInARowBoard::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}