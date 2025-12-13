#pragma once
#ifndef SUS_UI_H
#define SUS_UI_H

#include "BoardGame_Classes.h"
#include "SUS_Board.h"

class SUS_AIPlayer : public Player<char> {
private:
    char opponentSymbol;

public:
    SUS_AIPlayer(string name, char symbol, char opponent)
        : Player(name, symbol, PlayerType::COMPUTER), opponentSymbol(opponent) {
    }

    Move<char>* generate_move() {
        SUSBoard* board = dynamic_cast<SUSBoard*>(this->get_board_ptr());
        if (!board) return nullptr;

        vector<pair<int, int>> empty_cells;

        for (int x = 0; x < 3; x++) {
            for (int y = 0; y < 3; y++) {
                if (board->isPositionEmpty(x, y)) {
                    empty_cells.push_back({ x, y });
                }
            }
        }

        if (empty_cells.empty()) return nullptr;

        int random_index = rand() % empty_cells.size();
        int x = empty_cells[random_index].first;
        int y = empty_cells[random_index].second;

        return new Move<char>(x, y, this->get_symbol());
    }
};

class SUSUI : public UI<char> {
private:
    SUSBoard* susBoard;
    int player1Score, player2Score;

public:
    SUSUI(string message);
    ~SUSUI();
    Move<char>* get_move(Player<char>* player) override;
    Player<char>* create_player(string& name, char symbol, PlayerType type) override;

    void displayFinalResults(Player<char>* player1, Player<char>* player2);
    void run_game();

private:
    char choosePlayerLetter(const string& playerName);
    void displayBoard(bool showCoordinates = true);
    Move<char>* get_ai_move(Player<char>* aiPlayer);
    void play_game_without_draw();
};

#endif