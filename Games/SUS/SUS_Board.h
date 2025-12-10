#pragma once
#ifndef SUS_BOARD_H
#define SUS_BOARD_H

#include "BoardGame_Classes.h"

class SUSBoard : public Board<char> {
private:
    bool claimed[8];
    bool lineMatchesSUS(int lineIdx) const;

public:
    SUSBoard();
    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
    int getScore() const;
    bool isFull() const;
    bool isPositionEmpty(int x, int y) const;
};

#endif