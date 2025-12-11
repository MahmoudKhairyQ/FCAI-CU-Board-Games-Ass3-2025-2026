#include "FourXFour_UI.h"
#include <iostream>

FourXFourUI::FourXFourUI(string message) : UI<char>(message, 3) {
    board = new FourXFourBoard();
}

FourXFourUI::~FourXFourUI() {
    delete board;
}

bool FourXFourUI::is_playable_cell(const vector<vector<char>>& mat, int row, int col) const {
    // Check bounds
    if (row < 0 || row >= static_cast<int>(mat.size()) ||
        col < 0 || col >= static_cast<int>(mat[row].size()))
        return false;
    // Playable cells are those not marked as '#' (wall/invalid)
    return mat[row][col] != '#';
}

Move<char>* FourXFourUI::get_move(Player<char>* player) {
    int row, col;
    char symbol = player->get_symbol();

    // Computer player
    if (player->get_type() == PlayerType::COMPUTER) {
        vector<pair<int, int>> choices;
        // FIX: Use board->get_board() to get the current matrix
        const vector<vector<char>>& mat = board->get_board();
        for (int r = 0; r < mat.size(); ++r)
            for (int c = 0; c < mat[r].size(); ++c)
                if (is_playable_cell(mat, r, c) && mat[r][c] == ' ')
                    choices.emplace_back(r, c);

        if (choices.empty()) return new Move<char>(0, 0, symbol);

        auto p = choices[rand() % choices.size()];
        std::cout << player->get_name() << " (" << symbol << ") chooses: row " << p.first << " col " << p.second << std::endl;
        return new Move<char>(p.first, p.second, symbol);
    }

    // Human player input
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