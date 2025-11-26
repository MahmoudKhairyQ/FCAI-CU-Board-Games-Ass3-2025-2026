#pragma once
#ifndef FIVEXFIVE_BOARD_H
#define FIVEXFIVE_BOARD_H

#include "BoardGame_Classes.h"

class FiveXFiveBoard : public Board<char> {
public:
    FiveXFiveBoard();
    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
    int countThreeInRow(char symbol);
};

#endif