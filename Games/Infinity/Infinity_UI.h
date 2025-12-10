#pragma once
#ifndef INFINITY_UI_H
#define INFINITY_UI_H

#include "BoardGame_Classes.h"
#include "Infinity_Board.h"

class InfinityUI : public UI<char> {
private:
    InfinityBoard* boardPtr;

public:
    InfinityUI(std::string msg, InfinityBoard* b);
    Move<char>* get_move(Player<char>* player) override;
    Player<char>* create_player(std::string& name, char symbol, PlayerType type) override;
};

#endif
