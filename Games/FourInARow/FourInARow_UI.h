#ifndef _FOURINAROW_UI_H
#define _FOURINAROW_UI_H

#include "BoardGame_Classes.h"
#include <string>

class Connect4_AI; // Forward declaration

class FourInARowUI : public UI<char> {
private:
    Connect4_AI* aiHelper;

public:
    FourInARowUI(std::string message);
    virtual ~FourInARowUI();

    Move<char>* get_move(Player<char>* player) override;
    Player<char>* create_player(std::string& name, char symbol, PlayerType type) override;
};

#endif