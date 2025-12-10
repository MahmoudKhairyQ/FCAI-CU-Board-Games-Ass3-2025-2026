#pragma once
#ifndef INFINITY_BOARD_H
#define INFINITY_BOARD_H

#include "BoardGame_Classes.h"
#include <deque>
#include <tuple>
#include <unordered_map>

class InfinityBoard : public Board<char> {
private:
    std::deque<std::tuple<int,int,char>> moveHistory;

    std::unordered_map<char, int> ownerCount;

public:
    InfinityBoard();
    virtual ~InfinityBoard() {}

    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;

    bool is_empty(int row, int col) const;
};

#endif
