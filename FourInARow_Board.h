#ifndef _FOURINAROW_BOARD_H
#define _FOURINAROW_BOARD_H

#include "BoardGame_Classes.h"

class FourInARowBoard : public Board<char> {
public:
    FourInARowBoard();
    virtual ~FourInARowBoard() {}

    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
    bool check_four_at(const std::vector<std::vector<char>>& b, int r, int c, int dr, int dc, char sym);
};

#endif