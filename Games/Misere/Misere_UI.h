#pragma once
#ifndef MISERE_UI_H
#define MISERE_UI_H

#include "BoardGame_Classes.h"
#include "Misere_Board.h"

class MisereUI : public UI<char> {
public:
    MisereUI(string message);
    Move<char>* get_move(Player<char>* player) override;
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
};

#endif