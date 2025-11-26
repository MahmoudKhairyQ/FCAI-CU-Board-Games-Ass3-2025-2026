#pragma once
#ifndef NUMERICAL_UI_H
#define NUMERICAL_UI_H

#include "BoardGame_Classes.h"
#include "Numerical_Board.h"

class NumericalUI : public UI<int> {
public:
    NumericalUI(string message);
    Move<int>* get_move(Player<int>* player) override;
    Player<int>* create_player(string& name, int symbol, PlayerType type) override;

private:
    int get_number_input(Player<int>* player);
};

#endif