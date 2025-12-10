#include "Misere_UI.h"
#include <iostream>

MisereUI::MisereUI(string message) : UI<char>(message, 3) {}

Move<char>* MisereUI::get_move(Player<char>* player) {
    int row, col;

    while (true) {
        std::cout << player->get_name() << " (" << player->get_symbol() 
                  << "), enter row and column (0-2): ";
        std::cin >> row >> col;

        if (row < 0 || row > 2 || col < 0 || col > 2) {
            std::cout << "Invalid position. Please enter values between 0 and 2.\n";
        } else {
            break;
        }
    }

    return new Move<char>(row, col, player->get_symbol());
}

Player<char>* MisereUI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}