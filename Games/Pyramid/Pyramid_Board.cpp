#include "Pyramid_Board.h"
#include <iostream>

PyramidBoard::PyramidBoard() : Board<char>(3, 5) {
    // Create centered pyramid:
    // Row 0 -> 1 cell  (center)
    // Row 1 -> 3 cells (centered)
    // Row 2 -> 5 cells (full row)
    for (int r = 0; r < this->rows; ++r) {
        int nCells = 2 * r + 1;
        int start = (this->columns - nCells) / 2; // center-align
        for (int c = 0; c < this->columns; ++c) {
            if (c >= start && c < start + nCells)
                this->board[r][c] = ' '; // playable empty
            else
                this->board[r][c] = '#'; // non-playable sentinel
        }
    }
    this->n_moves = 0;
}

bool in_bounds(int r, int c, int rows, int columns) {
    return r >= 0 && r < rows && c >= 0 && c < columns;
}


bool PyramidBoard::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char symbol = move->get_symbol();

    // Must be a playable empty cell
    if (this->board[x][y] != ' ') return false;

    this->board[x][y] = symbol;
    this->n_moves++;
    return true;
}

int PyramidBoard::countThreeInRow(char symbol) {
    int count = 0;
    // Directions to check (8 directions)
    const int dr[] = { -1,-1,-1, 0, 0, 1, 1, 1 };
    const int dc[] = { -1, 0, 1,-1, 1,-1, 0, 1 };

    for (int r = 0; r < this->rows; ++r) {
        for (int c = 0; c < this->columns; ++c) {
            if (this->board[r][c] != symbol) continue;
            // start only from playable cells
            if (this->board[r][c] == '#') continue;
            for (int d = 0; d < 8; ++d) {
                int r1 = r + dr[d], c1 = c + dc[d];
                int r2 = r + 2 * dr[d], c2 = c + 2 * dc[d];
                if (!in_bounds(r1, c1, this->rows, this->columns)) continue;
                if (!in_bounds(r2, c2, this->rows, this->columns)) continue;
                if (this->board[r1][c1] == symbol && this->board[r2][c2] == symbol) {
                    // ensure all three are playable (not '#')
                    if (this->board[r1][c1] != '#' && this->board[r2][c2] != '#')
                        ++count;
                }
            }
        }
    }
    return count;
}

bool PyramidBoard::is_win(Player<char>* player) {
    if (!player) return false;
    return countThreeInRow(player->get_symbol()) > 0;
}

bool PyramidBoard::is_lose(Player<char>* player) {
    if (!player) return false;
    char opp = (player->get_symbol() == 'X') ? 'O' : 'X';
    return countThreeInRow(opp) > 0;
}

bool PyramidBoard::is_draw(Player<char>* /*player*/) {
    return false;
}

bool PyramidBoard::game_is_over(Player<char>* player) {
    return is_win(player) || is_lose(player) || is_draw(player);
}