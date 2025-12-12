#include "Infinity_Board.h"
#include <iostream>
#include <algorithm>

InfinityBoard::InfinityBoard() : Board<char>(3, 3) {
    ownerCount['X'] = 0;
    ownerCount['O'] = 0;

    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            board[i][j] = ' ';
}

bool InfinityBoard::is_empty(int row, int col) const {
    return board[row][col] == ' ';
}

static bool check_three(const std::vector<std::vector<char>>& b, char s) {
    for (int i = 0; i < 3; i++)
        if (b[i][0] == s && b[i][1] == s && b[i][2] == s) return true;

    for (int j = 0; j < 3; j++)
        if (b[0][j] == s && b[1][j] == s && b[2][j] == s) return true;

    if (b[0][0] == s && b[1][1] == s && b[2][2] == s) return true;
    if (b[0][2] == s && b[1][1] == s && b[2][0] == s) return true;

    return false;
}

bool InfinityBoard::update_board(Move<char>* move) {
    int r = move->get_x();
    int c = move->get_y();
    char s = move->get_symbol();

    if (!is_empty(r, c)) return false;

    board[r][c] = s;
    moveHistory.push_back({r, c, s});
    ownerCount[s]++;
    n_moves++;

    if (ownerCount[s] > 3) {
        for (auto it = moveHistory.begin(); it != moveHistory.end(); ++it) {
            int rr = std::get<0>(*it);
            int cc = std::get<1>(*it);
            char owner = std::get<2>(*it);

            if (owner == s) {
                board[rr][cc] = ' ';
                moveHistory.erase(it);
                ownerCount[s]--;
                n_moves--;
                break;
            }
        }
    }

    return true;
}

bool InfinityBoard::is_win(Player<char>* player) {
    return check_three(get_board_matrix(), player->get_symbol());
}

bool InfinityBoard::is_lose(Player<char>* player) {
    char me = player->get_symbol();
    char opp = (me == 'X') ? 'O' : 'X';
    return check_three(get_board_matrix(), opp);
}

bool InfinityBoard::is_draw(Player<char>* player) {
    return false;
}

bool InfinityBoard::game_is_over(Player<char>* player) {
    return is_win(player) || is_lose(player);
}
