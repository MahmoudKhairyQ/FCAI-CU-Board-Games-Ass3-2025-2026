#pragma once
#ifndef PYRAMID_UI_H
#define PYRAMID_UI_H

#include "BoardGame_Classes.h"
#include "Pyramid_Board.h"

class PyramidUI : public UI<char> {
private:
    PyramidBoard* board;

public:
    PyramidUI(string message);
    ~PyramidUI();
    Move<char>* get_move(Player<char>* player) override;
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
    bool is_playable_cell(const std::vector<std::vector<char>>& mat, int row, int col) const;
    
};

#endif
