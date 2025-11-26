#pragma once
#ifndef MISERE_BOARD_H
#define MISERE_BOARD_H

#include "BoardGame_Classes.h"

class MisereBoard : public Board<char> {
private:
    bool check_three_in_row(char symbol);

public:
    MisereBoard();
    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
};

#endif