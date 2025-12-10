#pragma once
#ifndef SUS_UI_H
#define SUS_UI_H

#include "BoardGame_Classes.h"
#include "SUS_Board.h"

class SUSUI : public UI<char> {
private:
    SUSBoard* susBoard;
    int player1Score, player2Score;

public:
    SUSUI(string message);
    ~SUSUI();
    Move<char>* get_move(Player<char>* player) override;
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;

private:
    char choosePlayerLetter(const string& playerName);
};

#endif