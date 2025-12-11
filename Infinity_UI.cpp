#include "Infinity_UI.h"
#include <iostream>
#include <limits>

InfinityUI::InfinityUI(std::string msg, InfinityBoard* b)
    : UI<char>(msg, 3), boardPtr(b) {}

Player<char>* InfinityUI::create_player(std::string& name, char symbol, PlayerType type) {
    return new Player<char>(name, symbol, type);
}

Move<char>* InfinityUI::get_move(Player<char>* player) {
    int r, c;

    while (true) {
        std::cout << "\n";
        display_board_matrix(boardPtr->get_board_matrix());

        std::cout << player->get_name() << " (" << player->get_symbol()
                  << ") enter row & column (0-2): ";

        if (!(std::cin >> r >> c)) {
            std::cout << "Enter valid integers.\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        if (r < 0 || r > 2 || c < 0 || c > 2) {
            std::cout << "Out of range.\n";
            continue;
        }

        if (!boardPtr->is_empty(r, c)) {
            std::cout << "Cell not empty.\n";
            continue;
        }

        break;
    }

    return new Move<char>(r, c, player->get_symbol());
}
