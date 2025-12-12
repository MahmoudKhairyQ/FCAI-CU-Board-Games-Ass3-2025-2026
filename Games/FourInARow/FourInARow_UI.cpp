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
        int rows = board.size();
        int cols = (rows > 0) ? board[0].size() : 0;
        
        // Check horizontal
        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols - 3; col++) {
                if (board[row][col] == symbol && 
                    board[row][col+1] == symbol && 
                    board[row][col+2] == symbol && 
                    board[row][col+3] == symbol) {
                    return true;
                }
            }
        }
        
        // Check vertical
        for (int col = 0; col < cols; col++) {
            for (int row = 0; row < rows - 3; row++) {
                if (board[row][col] == symbol && 
                    board[row+1][col] == symbol && 
                    board[row+2][col] == symbol && 
                    board[row+3][col] == symbol) {
                    return true;
                }
            }
        }
        
        // Check diagonal (down-right)
        for (int row = 0; row < rows - 3; row++) {
            for (int col = 0; col < cols - 3; col++) {
                if (board[row][col] == symbol && 
                    board[row+1][col+1] == symbol && 
                    board[row+2][col+2] == symbol && 
                    board[row+3][col+3] == symbol) {
                    return true;
                }
            }
        }
        
        // Check diagonal (down-left)
        for (int row = 0; row < rows - 3; row++) {
            for (int col = 3; col < cols; col++) {
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
        int rows = board.size();
        int cols = (rows > 0) ? board[0].size() : 0;
        
        // If center is available, take it
        if (cols > 3 && board[0][3] == ' ') {
            return 3;
        }
        
        // Get all available columns
        vector<int> available;
        for (int col = 0; col < cols; col++) {
            if (board[0][col] == ' ') {
                available.push_back(col);
            }
        }
        
        if (available.empty()) {
            return 3; // Default to center if no available
        }
        
        // 1. Check if AI can win immediately
        for (int col : available) {
            vector<vector<char>> tempBoard = board;
            // Find the row to place the piece
            for (int row = rows - 1; row >= 0; row--) {
                if (tempBoard[row][col] == ' ') {
                    tempBoard[row][col] = aiSymbol;
                    if (checkWin(tempBoard, aiSymbol)) {
                        return col;
                    }
                    break;
                }
            }
        }
        
        // 2. Check if need to block opponent's immediate win
        for (int col : available) {
            vector<vector<char>> tempBoard = board;
            for (int row = rows - 1; row >= 0; row--) {
                if (tempBoard[row][col] == ' ') {
                    tempBoard[row][col] = opponentSymbol;
                    if (checkWin(tempBoard, opponentSymbol)) {
                        return col;
                    }
                    break;
                }
            }
        }
        
        // 3. Try to create future opportunities (center first)
        vector<int> preferredOrder = {3, 2, 4, 1, 5, 0, 6};
        for (int col : preferredOrder) {
            // Check if column is in available list
            bool isAvailable = false;
            for (int availCol : available) {
                if (availCol == col) {
                    isAvailable = true;
                    break;
                }
            }
            if (isAvailable) {
                return col;
            }
        }
        
        // 4. Fallback: return first available column
        return available[0];
    }
};

FourInARowUI::FourInARowUI(std::string message) : UI<char>(message, 3) {
    srand(time(0));
}

FourInARowUI::~FourInARowUI() {}

Move<char>* FourInARowUI::get_move(Player<char>* player) {
    // Handle computer player
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
    
    // Handle human player
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

        // Check if the column is full
        Board<char>* bptr = player->get_board_ptr();
        if (bptr) {
            auto mat = bptr->get_board_matrix();
            if (!mat.empty() && mat[0][col] != ' ') {
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

