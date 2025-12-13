#include "SUS_Board.h"
#include <iostream>
#include <algorithm>

SUSBoard::SUSBoard() : Board<char>(3, 3) {
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            board[i][j] = ' ';
    for (int i = 0; i < 8; ++i) {
        claimed[i] = false;
        lineOwner[i] = ' ';
    }
}

bool SUSBoard::lineMatchesSUS(int lineIdx) const {
    char a = ' ', b = ' ', c = ' ';
    switch (lineIdx) {
    case 0: a = board[0][0]; b = board[0][1]; c = board[0][2]; break;
    case 1: a = board[1][0]; b = board[1][1]; c = board[1][2]; break;
    case 2: a = board[2][0]; b = board[2][1]; c = board[2][2]; break;
    case 3: a = board[0][0]; b = board[1][0]; c = board[2][0]; break;
    case 4: a = board[0][1]; b = board[1][1]; c = board[2][1]; break;
    case 5: a = board[0][2]; b = board[1][2]; c = board[2][2]; break;
    case 6: a = board[0][0]; b = board[1][1]; c = board[2][2]; break;
    case 7: a = board[0][2]; b = board[1][1]; c = board[2][0]; break;
    default: return false;
    }
    return (a == 'S' && b == 'U' && c == 'S');
}

int SUSBoard::calculatePlayerScore(char playerSymbol) const {
    int score = 0;

    for (int line = 0; line < 8; line++) {
        if (claimed[line]) {
            if (lineOwner[line] == playerSymbol) {
                score++;
            }
        }
    }
    return score;
}

bool SUSBoard::update_board(Move<char>* move) {
    int x = move->get_x();
    int y = move->get_y();
    char letter = move->get_symbol();

    if (x < 0 || x >= 3 || y < 0 || y >= 3 || board[x][y] != ' ')
        return false;
    if (letter != 'S' && letter != 'U')
        return false;

    board[x][y] = letter;
    n_moves++;

    for (int i = 0; i < 8; ++i) {
        if (!claimed[i] && lineMatchesSUS(i)) {
            claimed[i] = true;
            lineOwner[i] = letter;
        }
    }

    return true;
}

bool SUSBoard::is_win(Player<char>* player) {
    return false;
}

bool SUSBoard::is_lose(Player<char>* player) {
    return false;
}

bool SUSBoard::is_draw(Player<char>* player) {
    return n_moves == 9;
}

bool SUSBoard::game_is_over(Player<char>* player) {
    return n_moves == 9;
}

int SUSBoard::getTotalScore() const {
    int score = 0;
    for (int i = 0; i < 8; ++i) {
        if (claimed[i]) score++;
    }
    return score;
}

int SUSBoard::getPlayerScore(char playerSymbol) const {
    return calculatePlayerScore(playerSymbol);
}

bool SUSBoard::isFull() const {
    return n_moves == 9;
}

bool SUSBoard::isPositionEmpty(int x, int y) const {
    if (x < 0 || x >= 3 || y < 0 || y >= 3) return false;
    return board[x][y] == ' ';
}

char SUSBoard::getBoardValue(int x, int y) const {
    if (x < 0 || x >= 3 || y < 0 || y >= 3) return ' ';
    return board[x][y];
}

void SUSBoard::setBoardValue(int x, int y, char value) {
    if (x < 0 || x >= 3 || y < 0 || y >= 3) return;
    board[x][y] = value;
}

bool SUSBoard::checkSUSWin(Player<char>* player) {
    char symbol = player->get_symbol();
    int score = calculatePlayerScore(symbol);
    return (score > 0);
}

bool SUSBoard::checkGameOver() {
    if (n_moves == 9) {
        int scoreS = getPlayerScore('S');
        int scoreU = getPlayerScore('U');
        return true;
    }
    return false;
}

pair<int, int> SUSBoard::getFinalScores() const {
    int scoreS = 0;
    int scoreU = 0;

    for (int i = 0; i < 8; ++i) {
        if (claimed[i]) {
            if (lineOwner[i] == 'S') {
                scoreS++;
            }
            else if (lineOwner[i] == 'U') {
                scoreU++;
            }
        }
    }

    return make_pair(scoreS, scoreU);
}