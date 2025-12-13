#include "SUS_UI.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

SUSUI::SUSUI(string message) : UI<char>(message, 3) {
    susBoard = new SUSBoard();
    player1Score = player2Score = 0;
    srand(time(0));
}

SUSUI::~SUSUI() {
    delete susBoard;
}

void SUSUI::displayBoard(bool showCoordinates) {
    if (showCoordinates) {
        cout << "\n";
        cout << "   0   1   2  \n";
    }
    cout << "  ------------\n";

    for (int i = 0; i < 3; ++i) {
        if (showCoordinates) {
            cout << i << " | ";
        }
        else {
            cout << "  | ";
        }
        for (int j = 0; j < 3; ++j) {
            char c = susBoard->getBoardValue(i, j);
            if (c == ' ') {
                cout << "  | ";
            }
            else {
                cout << c << " | ";
            }
        }
        cout << "\n";
        cout << "  ------------\n";
    }
    if (showCoordinates) {
        cout << "  ------------\n";
    }
    cout << "\n";
}

Move<char>* SUSUI::get_move(Player<char>* player) {
    if (player->get_type() == PlayerType::COMPUTER ||
        player->get_type() == PlayerType::AI ||
        player->get_type() == PlayerType::RANDOM) {
        return get_ai_move(player);
    }

    int row, col;
    char letter = player->get_symbol();

    while (true) {
        cout << player->get_name() << " (" << letter << "), enter row and column (0-2): ";
        cin >> row >> col;

        if (row < 0 || row > 2 || col < 0 || col > 2) {
            cout << "Invalid position. Please enter values between 0 and 2.\n";
            continue;
        }

        if (!susBoard->isPositionEmpty(row, col)) {
            cout << "Position already occupied. Choose another.\n";
            continue;
        }

        break;
    }

    return new Move<char>(row, col, letter);
}

Move<char>* SUSUI::get_ai_move(Player<char>* aiPlayer) {
    vector<pair<int, int>> empty_cells;

    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            if (susBoard->isPositionEmpty(x, y)) {
                empty_cells.push_back({ x, y });
            }
        }
    }

    if (empty_cells.empty()) {
        return nullptr;
    }

    int random_index = rand() % empty_cells.size();
    int x = empty_cells[random_index].first;
    int y = empty_cells[random_index].second;

    cout << "\nAI " << aiPlayer->get_name() << " (" << aiPlayer->get_symbol()
        << ") chooses: " << x << " " << y << "\n";

    return new Move<char>(x, y, aiPlayer->get_symbol());
}

void SUSUI::displayFinalResults(Player<char>* player1, Player<char>* player2) {
    pair<int, int> scores = susBoard->getFinalScores();
    int score1 = scores.first;
    int score2 = scores.second;

    cout << "\n=======================================\n";
    cout << "           GAME OVER!\n";
    cout << "=======================================\n\n";

    cout << "=== FINAL SCORES ===\n";
    cout << player1->get_name() << " (" << player1->get_symbol()
        << "): " << score1 << " SUS sequences\n";
    cout << player2->get_name() << " (" << player2->get_symbol()
        << "): " << score2 << " SUS sequences\n\n";

    if (score1 > score2) {
        cout << player1->get_name() << " (" << player1->get_symbol()
            << ") WINS!\n";
    }
    else if (score2 > score1) {
        cout << player2->get_name() << " (" << player2->get_symbol()
            << ") WINS!\n";
    }
    else {
        cout << "IT'S A DRAW!\n";
        cout << "Both players have the same score!\n";
    }

    cout << "\n=======================================\n";
}

void SUSUI::play_game_without_draw() {
    Player<char>** players = this->setup_players();

    cout << "\nStarting SUS Game...\n";
    cout << "Initial board (all empty):\n";
    displayBoard();

    while (true) {
        for (int i = 0; i < 2; i++) {
            Player<char>* currentPlayer = players[i];

            Move<char>* move = this->get_move(currentPlayer);

            if (!move) continue;

            if (susBoard->update_board(move)) {
                displayBoard(false);

                delete move;

                if (susBoard->isFull()) {
                    displayFinalResults(players[0], players[1]);

                    delete players[0];
                    delete players[1];
                    delete[] players;
                    return;
                }
            }
            else {
                cout << "Invalid move! Try again.\n";
                delete move;
                i--;
            }
        }
    }
}

void SUSUI::run_game() {
    play_game_without_draw();
}

char SUSUI::choosePlayerLetter(const string& playerName) {
    char letter;
    while (true) {
        cout << playerName << ", choose your letter (S or U): ";
        cin >> letter;
        letter = toupper(letter);
        if (letter == 'S' || letter == 'U') {
            break;
        }
        cout << "Invalid letter. Please choose S or U.\n";
    }
    return letter;
}

Player<char>* SUSUI::create_player(string& name, char symbol, PlayerType type) {
    char chosenLetter = choosePlayerLetter(name);

    if (type == PlayerType::COMPUTER || type == PlayerType::AI) {
        char opponent = (chosenLetter == 'S') ? 'U' : 'S';
        return new SUS_AIPlayer(name, chosenLetter, opponent);
    }

    return new Player<char>(name, chosenLetter, type);
}