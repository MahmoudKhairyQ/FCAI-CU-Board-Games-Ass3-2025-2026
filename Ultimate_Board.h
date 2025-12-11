#pragma once
#ifndef ULTIMATE_BOARD_H
#define ULTIMATE_BOARD_H

#include "BoardGame_Classes.h"

class UltimateBoard : public Board<char> {
public:
    UltimateBoard();
    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
    int countThreeInRow(char symbol);

private:
    static const int MAIN_SIZE = 3;   // 3x3 main grid
    static const int SUB_SIZE = 3;    // each main cell has 3x3 subgrid

    // 3x3 main grid status (' ', 'X', 'O', or 'D')
    std::vector<std::vector<char>> main_grid;

    // subboards[main_r][main_c] -> SUB_SIZE x SUB_SIZE matrix
    std::vector<std::vector<std::vector<std::vector<char>>>> subboards;

    // Helper checks
    bool subboard_has_winner(int main_r, int main_c, char symbol) const;
    bool subboard_is_full(int main_r, int main_c) const;
    bool main_grid_has_three_in_row(char symbol) const;
};

#endif

