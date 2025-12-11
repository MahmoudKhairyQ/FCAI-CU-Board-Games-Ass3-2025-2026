#pragma once
#ifndef NUMERICAL_BOARD_H
#define NUMERICAL_BOARD_H

#include "BoardGame_Classes.h"
#include <vector>
#include <algorithm>

class NumericalBoard : public Board<int> {
private:
    std::vector<int> usedNumbers;

public:
    NumericalBoard();
    bool update_board(Move<int>* move) override;
    bool is_win(Player<int>* player) override;
    bool is_lose(Player<int>* player) override;
    bool is_draw(Player<int>* player) override;
    bool game_is_over(Player<int>* player) override;
    bool isNumberUsed(int num);
};

#endif