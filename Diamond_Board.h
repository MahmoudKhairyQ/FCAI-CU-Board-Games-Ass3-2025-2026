#pragma once
#ifndef DIAMOND_BOARD_H
#define DIAMOND_BOARD_H

#include "BoardGame_Classes.h"
#include <vector>

class DiamondBoard : public Board<char> {
private:
    bool validCell[5][5];
        
    bool hasThreeInLine(char symbol, int& lineType) const;
    
    bool hasFourInLine(char symbol, int& lineType) const;

public:
    DiamondBoard();
    bool update_board(Move<char>* move) override;
    bool is_win(Player<char>* player) override;
    bool is_lose(Player<char>* player) override;
    bool is_draw(Player<char>* player) override;
    bool game_is_over(Player<char>* player) override;
    bool isValidPosition(int row, int col) const;

};

#endif