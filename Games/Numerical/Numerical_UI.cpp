#include "Numerical_UI.h"
#include <iostream>

NumericalUI::NumericalUI(string message) : UI<int>(message, 3) {}

Move<int>* NumericalUI::get_move(Player<int>* player) {
    int row, col, number;

    number = get_number_input(player);

    while (true) {
        std::cout << player->get_name() << ", enter row and column (0-2): ";
        std::cin >> row >> col;

        if (row < 0 || row > 2 || col < 0 || col > 2) {
            std::cout << "Invalid position. Please enter values between 0 and 2.\n";
        } else {
            break;
        }
    }

    return new Move<int>(row, col, number);
}

int NumericalUI::get_number_input(Player<int>* player) {
    int number;
    string player_name = player->get_name();
    char player_symbol = player->get_symbol();

    while (true) {
        if (player_symbol == 'X') {
            std::cout << player_name << " (odd numbers), enter your number (1,3,5,7,9): ";
        } else {
            std::cout << player_name << " (even numbers), enter your number (2,4,6,8): ";
        }

        std::cin >> number;

        if (player_symbol == 'X' && (number % 2 == 0 || number < 1 || number > 9)) {
            std::cout << "Player X must use odd numbers between 1-9.\n";
        } else if (player_symbol == 'O' && (number % 2 != 0 || number < 2 || number > 8)) {
            std::cout << "Player O must use even numbers between 2-8.\n";
        } else {
            break;
        }
    }

    return number;
}

Player<int>* NumericalUI::create_player(string& name, int symbol, PlayerType type) {
    return new Player<int>(name, symbol, type);
}