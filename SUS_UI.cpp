#include "SUS_UI.h"
#include <iostream>

SUSUI::SUSUI(string message) : UI<char>(message, 3) {
    susBoard = new SUSBoard();
    player1Score = player2Score = 0;
}

SUSUI::~SUSUI() {
    delete susBoard;
}

Move<char>* SUSUI::get_move(Player<char>* player) {
    int row, col;
    char letter = player->get_symbol();

    while (true) {
        std::cout << player->get_name() << " (" << letter << "), enter row and column (0-2): ";
        std::cin >> row >> col;

        if (row < 0 || row > 2 || col < 0 || col > 2) {
            std::cout << "Invalid position. Please enter values between 0 and 2.\n";
        } else {
            break;
        }
    }

    return new Move<char>(row, col, letter);
}

char SUSUI::choosePlayerLetter(const string& playerName) {
    char letter;
    while (true) {
        std::cout << playerName << ", choose your letter (S or U): ";
        std::cin >> letter;
        letter = toupper(letter);
        if (letter == 'S' || letter == 'U') {
            break;
        }
        std::cout << "Invalid letter. Please choose S or U.\n";
    }
    return letter;
}

Player<char>* SUSUI::create_player(string& name, char symbol, PlayerType type) {
    // For SUS game, players choose their letters
    char chosenLetter = choosePlayerLetter(name);
    return new Player<char>(name, chosenLetter, type);
}