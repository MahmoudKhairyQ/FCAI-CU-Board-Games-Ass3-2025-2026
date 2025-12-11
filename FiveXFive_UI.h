#pragma once
#ifndef FIVEXFIVE_UI_H
#define FIVEXFIVE_UI_H

#include "BoardGame_Classes.h"
#include "FiveXFive_Board.h"

class FiveXFiveUI : public UI<char> {
private:
    FiveXFiveBoard* board;

public:
    FiveXFiveUI(string message);
    ~FiveXFiveUI();
    Move<char>* get_move(Player<char>* player) override;
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
};

#endif