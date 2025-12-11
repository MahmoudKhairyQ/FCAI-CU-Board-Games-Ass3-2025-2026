#pragma once
#ifndef Ultimate_UI_H
#define Ultimate_UI_H

#include "BoardGame_Classes.h"
#include "Ultimate_Board.h"

class UltimateUI : public UI<char> {
private:
    UltimateBoard* board;

public:
    UltimateUI(string message);
    ~UltimateUI();
    Move<char>* get_move(Player<char>* player) override;
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
    bool is_playable_cell(const std::vector<std::vector<char>>& mat, int row, int col) const;

};

#endif

