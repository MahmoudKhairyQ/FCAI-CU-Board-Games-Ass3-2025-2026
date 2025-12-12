#include "Obstacles_UI.h"
#include <iostream>

ObstaclesUI::ObstaclesUI(string message) : UI<char>(message, 3) {}

Move<char>* ObstaclesUI::get_move(Player<char>* player) {
    int row, col;

    while (true) {
        std::cout << player->get_name() << " (" << player->get_symbol() 
                  << "), enter row and column (0-5): ";
        std::cin >> row >> col;

        if (row < 0 || row > 5 || col < 0 || col > 5) {
            std::cout << "Invalid position. Please enter values between 0 and 5.\n";
        } else {
            break;
        }
    }

    return new Move<char>(row, col, player->get_symbol());
}

Player<char>* ObstaclesUI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}