#include "FiveXFive_UI.h"
#include <iostream>

FiveXFiveUI::FiveXFiveUI(string message) : UI<char>(message, 3) {
    board = new FiveXFiveBoard();
}

FiveXFiveUI::~FiveXFiveUI() {
    delete board;
}

Move<char>* FiveXFiveUI::get_move(Player<char>* player) {
    int row, col;

    while (true) {
        std::cout << player->get_name() << " (" << player->get_symbol() 
                  << "), enter row and column (0-4): ";
        std::cin >> row >> col;

        if (row < 0 || row > 4 || col < 0 || col > 4) {
            std::cout << "Invalid position. Please enter values between 0 and 4.\n";
        } else {
            break;
        }
    }

    return new Move<char>(row, col, player->get_symbol());
}

Player<char>* FiveXFiveUI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}