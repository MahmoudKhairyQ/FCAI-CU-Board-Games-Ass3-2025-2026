#include "FourInARow_UI.h"
#include <iostream>

FourInARowUI::FourInARowUI(std::string message) : UI<char>(message, 3) {}

FourInARowUI::~FourInARowUI() {}

Move<char>* FourInARowUI::get_move(Player<char>* player) {
    int col;
    while (true) {
        std::cout << "\nColumns: 0 1 2 3 4 5 6\n";
        std::cout << player->get_name() << " (" << player->get_symbol() << "), enter column (0-6): ";
        
        if (!(std::cin >> col)) {
            std::cout << "Invalid input. Enter a number between 0 and 6.\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        if (col < 0 || col > 6) {
            std::cout << "Column out of range. Please enter 0..6.\n";
            continue;
        }

       // check if the column is full (top spot isn’t empty)
        Board<char>* bptr = player->get_board_ptr();
        if (bptr) {
            auto mat = bptr->get_board_matrix();
            if (mat.size() > 0 && mat[0][col] != ' ') {
                std::cout << "Column is full. Choose another column.\n";
                continue;
            }
        }

        break;
    }

    // board decides the row (drops into the lowest empty spot)
    return new Move<char>(0, col, player->get_symbol());
}

Player<char>* FourInARowUI::create_player(std::string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}

Player<char>** FourInARowUI::setup_players() {
    return UI<char>::setup_players();  
}