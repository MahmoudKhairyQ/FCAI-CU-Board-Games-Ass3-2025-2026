#include "FourInARow_UI.h"
#include "FourInARow_Board.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <climits>

using namespace std;

class Connect4_AI {
private:
    char aiSymbol;
    char opponentSymbol;
    
public:
    Connect4_AI(char aiSym, char oppSym) : aiSymbol(aiSym), opponentSymbol(oppSym) {}
    
    bool checkWin(const vector<vector<char>>& board, char symbol) {
        for (int row = 0; row < 6; row++) {
            for (int col = 0; col < 4; col++) {
                if (board[row][col] == symbol && 
                    board[row][col+1] == symbol && 
                    board[row][col+2] == symbol && 
                    board[row][col+3] == symbol) {
                    return true;
                }
            }
        }
        
        for (int col = 0; col < 7; col++) {
            for (int row = 0; row < 3; row++) {
                if (board[row][col] == symbol && 
                    board[row+1][col] == symbol && 
                    board[row+2][col] == symbol && 
                    board[row+3][col] == symbol) {
                    return true;
                }
            }
        }
        
        for (int row = 0; row < 3; row++) {
            for (int col = 0; col < 4; col++) {
                if (board[row][col] == symbol && 
                    board[row+1][col+1] == symbol && 
                    board[row+2][col+2] == symbol && 
                    board[row+3][col+3] == symbol) {
                    return true;
                }
            }
        }
        
        for (int row = 0; row < 3; row++) {
            for (int col = 3; col < 7; col++) {
                if (board[row][col] == symbol && 
                    board[row+1][col-1] == symbol && 
                    board[row+2][col-2] == symbol && 
                    board[row+3][col-3] == symbol) {
                    return true;
                }
            }
        }
        
        return false;
    }
    
    int getBestMove(const vector<vector<char>>& board) {
        if (board[0][3] == ' ') return 3;
        
        vector<int> available;
        for (int col = 0; col < 7; col++) {
            if (board[0][col] == ' ') {
                available.push_back(col);
            }
        }
        
        if (available.empty()) return 3;
        
        for (int col : available) {
            vector<vector<char>> tempBoard = board;
            for (int row = 5; row >= 0; row--) {
                if (tempBoard[row][col] == ' ') {
                    tempBoard[row][col] = aiSymbol;
                    if (checkWin(tempBoard, aiSymbol)) {
                        return col;
                    }
                    break;
                }
            }
        }
        
        for (int col : available) {
            vector<vector<char>> tempBoard = board;
            for (int row = 5; row >= 0; row--) {
                if (tempBoard[row][col] == ' ') {
                    tempBoard[row][col] = opponentSymbol;
                    if (checkWin(tempBoard, opponentSymbol)) {
                        return col;
                    }
                    break;
                }
            }
        }
        
        if (!available.empty()) {
            for (int col : {3, 2, 4, 1, 5, 0, 6}) {
                for (int availableCol : available) {
                    if (availableCol == col) {
                        return col;
                    }
                }
            }
        }
        
        return available[0];
    }
};

FourInARowUI::FourInARowUI(std::string message) : UI<char>(message, 3) {
    srand(time(0));
}

FourInARowUI::~FourInARowUI() {}

Player<char>** FourInARowUI::setup_players() {
    Player<char>** players = new Player<char>*[2];
    
    // Player X
    string nameX;
    cout << "Enter Player X name: ";
    cin.ignore();
    getline(cin, nameX);
    
    cout << "Choose Player X type:" << endl;
    cout << "1. Human" << endl;
    cout << "2. Computer" << endl;
    
    int choiceX;
    cin >> choiceX;
    
    PlayerType typeX = (choiceX == 2) ? PlayerType::COMPUTER : PlayerType::HUMAN;
    players[0] = create_player(nameX, 'X', typeX);
    
    // Player O
    string nameO;
    cout << "Enter Player O name: ";
    cin.ignore();
    getline(cin, nameO);
    
    cout << "Choose Player O type:" << endl;
    cout << "1. Human" << endl;
    cout << "2. Computer" << endl;
    
    int choiceO;
    cin >> choiceO;
    
    PlayerType typeO = (choiceO == 2) ? PlayerType::COMPUTER : PlayerType::HUMAN;
    players[1] = create_player(nameO, 'O', typeO);
    
    return players;
}

Move<char>* FourInARowUI::get_move(Player<char>* player) {
    if (player->get_type() == PlayerType::COMPUTER) {
        char aiSymbol = player->get_symbol();
        char opponentSymbol = (aiSymbol == 'X') ? 'O' : 'X';
        
        cout << player->get_name() << " (" << aiSymbol << ") is thinking..." << endl;
        
        Board<char>* boardPtr = player->get_board_ptr();
        if (!boardPtr) {
            return new Move<char>(0, 3, aiSymbol);
        }
        
        vector<vector<char>> currentBoard = boardPtr->get_board_matrix();
        
        Connect4_AI ai(aiSymbol, opponentSymbol);
        int bestCol = ai.getBestMove(currentBoard);
        
        cout << player->get_name() << " chooses column: " << bestCol << endl;
        
        return new Move<char>(0, bestCol, aiSymbol);
    }
    
    int col;
    
    while (true) {
        cout << "\nColumns: 0 1 2 3 4 5 6\n";
        cout << player->get_name() << " (" << player->get_symbol() << "), enter column (0-6): ";
        
        if (!(cin >> col)) {
            cout << "Invalid input. Enter a number between 0 and 6.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        if (col < 0 || col > 6) {
            cout << "Column out of range. Please enter 0..6.\n";
            continue;
        }

       // check if the column is full (top spot isn’t empty)
        Board<char>* bptr = player->get_board_ptr();
        if (bptr) {
            auto mat = bptr->get_board_matrix();
            if (mat.size() > 0 && mat[0][col] != ' ') {
                cout << "Column is full. Choose another column.\n";
                continue;
            }
        }

        break;
    }

    // board decides the row (drops into the lowest empty spot)
    return new Move<char>(0, col, player->get_symbol());
}

Player<char>* FourInARowUI::create_player(std::string& name, char symbol, PlayerType type) {
    string typeStr = (type == PlayerType::COMPUTER) ? "computer" : "human";
    cout << "Creating " << typeStr << " player: " << name << " (" << symbol << ")" << endl;
    
    return new Player<char>(name, symbol, type);
}

Player<char>** FourInARowUI::setup_players() {
    return UI<char>::setup_players();  
}