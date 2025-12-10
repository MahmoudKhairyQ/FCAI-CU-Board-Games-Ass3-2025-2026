#include "FourXFour_UI.h"
#include <iostream>

FourXFourUI::FourXFourUI(string message) : UI<char>(message, 3) {
    board = new FourXFourBoard();
}

FourXFourUI::~FourXFourUI() {
    delete board;
}

Move<char>* FourXFourUI::get_move(Player<char>* player) {
    int row, col;

    while (true) {
        std::cout << player->get_name() << " (" << player->get_symbol()
            << "), enter row and column (0-3): ";
        std::cin >> row >> col;

        if (row < 0 || row > 3 || col < 0 || col > 3) {
            std::cout << "Invalid position. Please enter values between 0 and 3.\n";
        }
        else {
            break;
        }
    }

    return new Move<char>(row, col, player->get_symbol());
}

Player<char>* FourXFourUI::create_player(string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}