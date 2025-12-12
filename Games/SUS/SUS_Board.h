#pragma once
#ifndef SUS_BOARD_H
#define SUS_BOARD_H

#include "BoardGame_Classes.h"

class SUSBoard : public Board<char> {
private:
    bool claimed[8];
    bool lineMatchesSUS(int lineIdx) const;

protected:
    using Board<char>::board; // <-- Add this line to make 'board' accessible

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
    char getBoardValue(int x, int y) const;
    void setBoardValue(int x, int y, char value); // <-- Add declaration if missing
};

#endif