#include "Pyramid_UI.h"
#include <iostream>

using namespace std;

PyramidUI::PyramidUI(string message) : UI<char>(message, 3) {
    board = new PyramidBoard();
}

PyramidUI::~PyramidUI() {
    delete board;
}

bool PyramidUI::is_playable_cell(const vector<vector<char>>& mat, int row, int col) const {
    // Check bounds
    if (row < 0 || row >= static_cast<int>(mat.size()) ||
        col < 0 || col >= static_cast<int>(mat[row].size()))
        return false;
    // Playable cells are those not marked as '#' (wall/invalid)
    return mat[row][col] != '#';
}


Move<char>* PyramidUI::get_move(Player<char>* player) {
    if (!player) return nullptr;

    Board<char>* bptr = player->get_board_ptr();
    PyramidBoard* pb = nullptr;
    if (bptr) {
        // board pointer may point to a Pyramid instance
        pb = dynamic_cast<PyramidBoard*>(bptr);
    }
    if (!pb) pb = this->board; // fallback to local board

    auto mat = pb->get_board_matrix();
    int rows = static_cast<int>(mat.size());
    int cols = (rows > 0) ? static_cast<int>(mat[0].size()) : 0;
    char symbol = player->get_symbol();

    // Computer player: choose random playable empty cell
    if (player->get_type() == PlayerType::COMPUTER) {
        vector<pair<int,int>> choices;
        for (int r = 0; r < rows; ++r)
            for (int c = 0; c < cols; ++c)
                if (is_playable_cell(mat, r, c) && mat[r][c] == ' ')
                    choices.emplace_back(r, c);

        if (choices.empty()) return new Move<char>(0, 0, symbol);

        auto p = choices[rand() % choices.size()];
        cout << player->get_name() << " (" << symbol << ") chooses: row " << p.first << " col " << p.second << endl;
        return new Move<char>(p.first, p.second, symbol);
    }

    // Human player
    int r, c;
    while (true) {
        // Display helpful layout indices
        cout << "\nPyramid coordinates (row col). Playable cells are shown as '.'\n";
        for (int i = 0; i < rows; ++i) {
            cout << i << " | ";
            for (int j = 0; j < cols; ++j) {
                char ch = mat[i][j];
                if (ch == '#') cout << "  ";
                else if (ch == ' ') cout << ". ";
                else cout << ch << " ";
            }
            cout << "\n";
        }

        cout << player->get_name() << " (" << symbol << "), enter row and column: ";
        if (!(cin >> r >> c)) {
            cout << "Invalid input. Please enter two integers.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        if (r < 0 || r >= rows || c < 0 || c >= cols) {
            cout << "Out of range. Try again.\n";
            continue;
        }

        if (!is_playable_cell(mat, r, c)) {
            cout << "That position is not playable. Choose a different cell.\n";
            continue;
        }

        if (mat[r][c] != ' ') {
            cout << "Cell already occupied. Choose another.\n";
            continue;
        }

        break;
    }

    return new Move<char>(r, c, symbol);
}

Player<char>* PyramidUI::create_player(string& name, char symbol, PlayerType type) {
    cout << "Creating " << ((type == PlayerType::COMPUTER) ? "computer" : "human")
         << " player: " << name << " (" << symbol << ")\n";
    return new Player<char>(name, symbol, type);
}

