#pragma once
#ifndef OBSTACLES_UI_H
#define OBSTACLES_UI_H

#include "BoardGame_Classes.h"
#include "Obstacles_Board.h"

class ObstaclesUI : public UI<char> {
public:
    ObstaclesUI(string message);
    Move<char>* get_move(Player<char>* player) override;
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
};

#endif