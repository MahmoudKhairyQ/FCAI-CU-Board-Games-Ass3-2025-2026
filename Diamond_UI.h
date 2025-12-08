#pragma once
#ifndef DIAMOND_UI_H
#define DIAMOND_UI_H

#include "BoardGame_Classes.h"
#include "Diamond_Board.h"

class DiamondUI : public UI<char> {
private:
    DiamondBoard* diamondBoard;

public:
    DiamondUI(string message);
    ~DiamondUI();
    Move<char>* get_move(Player<char>* player) override;
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
    };

#endif