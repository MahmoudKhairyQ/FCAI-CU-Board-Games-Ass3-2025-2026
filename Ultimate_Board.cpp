#include "Ultimate_Board.h"
#include <iostream>

UltimateBoard::UltimateBoard()
    : Board<char>(MAIN_SIZE * SUB_SIZE, MAIN_SIZE * SUB_SIZE) // 9x9 combined board for display
{
    // initialize combined board to spaces
    for (int r = 0; r < rows; ++r)
        for (int c = 0; c < columns; ++c)
            board[r][c] = ' ';

    // init main grid (3x3) to ' ' (undecided)
    main_grid.assign(MAIN_SIZE, std::vector<char>(MAIN_SIZE, ' '));

    // init subboards: MAIN_SIZE x MAIN_SIZE each with SUB_SIZE x SUB_SIZE ' ' cells
    subboards.resize(MAIN_SIZE);
    for (int i = 0; i < MAIN_SIZE; ++i) {
        subboards[i].resize(MAIN_SIZE);
        for (int j = 0; j < MAIN_SIZE; ++j) {
            subboards[i][j].assign(SUB_SIZE, std::vector<char>(SUB_SIZE, ' '));
        }
    }
}

bool UltimateBoard::update_board(Move<char>* move) {
    if (!move) return false;

    int r = move->get_x();
    int c = move->get_y();
    char symbol = move->get_symbol();

    // Validate global coordinates (0..8)
    if (r < 0 || r >= rows || c < 0 || c >= columns) return false;

    // If combined cell already taken, reject
    if (board[r][c] != ' ') return false;

    // Place symbol in combined board
    board[r][c] = symbol;
    ++n_moves;

    // Map to main/sub indices
    int main_r = r / SUB_SIZE;
    int main_c = c / SUB_SIZE;
    int sub_r = r % SUB_SIZE;
    int sub_c = c % SUB_SIZE;

    // place symbol inside subboards structure
    subboards[main_r][main_c][sub_r][sub_c] = symbol;

    // If this subboard now has a winner, mark main_grid if not already
    if (main_grid[main_r][main_c] == ' ') {
        if (subboard_has_winner(main_r, main_c, symbol)) {
            main_grid[main_r][main_c] = symbol;
        } else if (subboard_is_full(main_r, main_c)) {
            // mark draw for that subboard
            main_grid[main_r][main_c] = 'D';
        }
    }

    return true;
}

bool UltimateBoard::subboard_has_winner(int main_r, int main_c, char symbol) const {
    // check rows and columns and diagonals inside the SUB_SIZE x SUB_SIZE subboard
    const auto& s = subboards[main_r][main_c];

    // rows
    for (int i = 0; i < SUB_SIZE; ++i) {
        bool all = true;
        for (int j = 0; j < SUB_SIZE; ++j) {
            if (s[i][j] != symbol) { all = false; break; }
        }
        if (all) return true;
    }

    // cols
    for (int j = 0; j < SUB_SIZE; ++j) {
        bool all = true;
        for (int i = 0; i < SUB_SIZE; ++i) {
            if (s[i][j] != symbol) { all = false; break; }
        }
        if (all) return true;
    }

    // diag
    bool d1 = true, d2 = true;
    for (int i = 0; i < SUB_SIZE; ++i) {
        if (s[i][i] != symbol) d1 = false;
        if (s[i][SUB_SIZE - 1 - i] != symbol) d2 = false;
    }
    return d1 || d2;
}

bool UltimateBoard::subboard_is_full(int main_r, int main_c) const {
    const auto& s = subboards[main_r][main_c];
    for (int i = 0; i < SUB_SIZE; ++i)
        for (int j = 0; j < SUB_SIZE; ++j)
            if (s[i][j] == ' ') return false;
    return true;
}

bool UltimateBoard::main_grid_has_three_in_row(char symbol) const {
    // check 3x3 main_grid for three-in-a-row of 'symbol'
    // rows
    for (int i = 0; i < MAIN_SIZE; ++i) {
        bool all = true;
        for (int j = 0; j < MAIN_SIZE; ++j) {
            if (main_grid[i][j] != symbol) { all = false; break; }
        }
        if (all) return true;
    }

    // cols
    for (int j = 0; j < MAIN_SIZE; ++j) {
        bool all = true;
        for (int i = 0; i < MAIN_SIZE; ++i) {
            if (main_grid[i][j] != symbol) { all = false; break; }
        }
        if (all) return true;
    }

    // diags
    bool d1 = true, d2 = true;
    for (int i = 0; i < MAIN_SIZE; ++i) {
        if (main_grid[i][i] != symbol) d1 = false;
        if (main_grid[i][MAIN_SIZE - 1 - i] != symbol) d2 = false;
    }
    return d1 || d2;
}

bool UltimateBoard::is_win(Player<char>* player) {
    if (!player) return false;
    char sym = player->get_symbol();
    return main_grid_has_three_in_row(sym);
}

bool UltimateBoard::is_lose(Player<char>* player) {
    // lose is simply opponent winning in main grid
    if (!player) return false;
    char sym = player->get_symbol();
    char opp = (sym == 'X') ? 'O' : 'X';
    return main_grid_has_three_in_row(opp);
}

bool UltimateBoard::is_draw(Player<char>* player) {
    // Draw when full (81 moves) and no main-grid winner
    if (main_grid_has_three_in_row('X') || main_grid_has_three_in_row('O')) return false;
    return n_moves >= MAIN_SIZE * MAIN_SIZE * SUB_SIZE * SUB_SIZE;
}

bool UltimateBoard::game_is_over(Player<char>* player) {
    return is_win(player) || is_draw(player);
}

int UltimateBoard::countThreeInRow(char symbol) {
    // Count the number of three-in-row lines in the main grid (0..8 possible -> realistic 0..8)
    int count = 0;
    // rows
    for (int i = 0; i < MAIN_SIZE; ++i) {
        bool all = true;
        for (int j = 0; j < MAIN_SIZE; ++j) if (main_grid[i][j] != symbol) { all = false; break; }
        if (all) ++count;
    }
    // cols
    for (int j = 0; j < MAIN_SIZE; ++j) {
        bool all = true;
        for (int i = 0; i < MAIN_SIZE; ++i) if (main_grid[i][j] != symbol) { all = false; break; }
        if (all) ++count;
    }
    // diags
    bool d1 = true, d2 = true;
    for (int i = 0; i < MAIN_SIZE; ++i) {
        if (main_grid[i][i] != symbol) d1 = false;
        if (main_grid[i][MAIN_SIZE - 1 - i] != symbol) d2 = false;
    }
    if (d1) ++count;
    if (d2) ++count;

    return count;
}
