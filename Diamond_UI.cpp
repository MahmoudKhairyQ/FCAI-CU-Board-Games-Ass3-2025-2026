#include "Diamond_UI.h"
#include <iostream>

DiamondUI::DiamondUI(string message) : UI<char>(message, 3) {
    diamondBoard = new DiamondBoard();
}

DiamondUI::~DiamondUI() {
    delete diamondBoard;
}

Move<char>* DiamondUI::get_move(Player<char>* player) {
    int row, col;

    while (true) {
        std::cout << "\n";
        std::cout << player->get_name() << " (" << player->get_symbol() << "), enter row and column (0-4): ";
        std::cin >> row >> col;

        if (!(std::cin >> row >> col)) {
            std::cout << "Invalid input. Please enter two integers (row and column).\n";
            std::cin.clear();
            continue;
        }
        
        if (!diamondBoard->isValidPosition(row, col)) {
            std::cout << "Invalid position. Please enter values between 0 and 4.\n";
            continue;
        }

        break;
    }


    return new Move<char>(row, col, player->get_symbol());
}

Player<char>* DiamondUI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}
