#pragma once
#ifndef FOURXFOUR_UI_H
#define FOURXFOUR_UI_H

#include "BoardGame_Classes.h"
#include "FourXFour_Board.h"

class FourXFourUI : public UI<char> {
private:
    FourXFourBoard* board;

public:
    FourXFourUI(string message);
    ~FourXFourUI();
    Move<char>* get_move(Player<char>* player) override;
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;
	bool is_playable_cell(const std::vector<std::vector<char>>& mat, int row, int col) const;
};

#endif