#include "Word_Tic_tac_board.h"
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;


// Constructor - initializes board and loads dictionary
Word_Tik_tak_Board::Word_Tik_tak_Board() : moveCount(0) {
    // Initialize board with empty spaces
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            board[i][j] = ' ';
    
    // Load dictionary from file
    loadDictionary("dic.txt");
}

// Load valid 3-letter words from file
void Word_Tik_tak_Board::loadDictionary(const std::string& filename) {
    ifstream file(filename);
    string word;
    
    if (!file.is_open()) {
        cout << "Warning: Could not open dictionary file: " << filename << std::endl;
        return;
    }
    
    while (file >> word) {
        // Convert to uppercase and add to dictionary
        transform(word.begin(), word.end(), word.begin(), ::toupper);
        if (word.length() == 3) {
            dictionary.insert(word);
        }
    }
    file.close();
}

// Check if a word exists in dictionary
bool Word_Tik_tak_Board::isValidWord(const string& word) {
    string upperWord = word;
    transform(upperWord.begin(), upperWord.end(), upperWord.begin(), ::toupper);
    return dictionary.find(upperWord) != dictionary.end();
}

// Place a letter on the board
bool Word_Tik_tak_Board::placeLetter(int row, int col, char letter) {
    // Check bounds
    if (row < 0 || row >= 3 || col < 0 || col >= 3)
        return false;
    
    // Check if cell is empty
    if (board[row][col] != ' ')
        return false;
    
    // Convert to uppercase
    letter = toupper(letter);
    
    // Check if it's a valid letter (A-Z)
    if (letter < 'A' || letter > 'Z')
        return false;
    
    board[row][col] = letter;
    moveCount++;
    return true;
}

// Get the winning word (for display purposes)
string Word_Tik_tak_Board::getWinningWord() {
    string word;
    
    // Check rows
    for (int i = 0; i < 3; ++i) {
        word = "";
        word += board[i][0];
        word += board[i][1];
        word += board[i][2];
        if (word.find(' ') == string::npos && isValidWord(word))
            return word;
    }
    
    // Check columns
    for (int j = 0; j < 3; ++j) {
        word = "";
        word += board[0][j];
        word += board[1][j];
        word += board[2][j];
        if (word.find(' ') == string::npos && isValidWord(word))
            return word;
    }
    
    // Check diagonal (top-left to bottom-right)
    word = "";
    word += board[0][0];
    word += board[1][1];
    word += board[2][2];
    if (word.find(' ') == string::npos && isValidWord(word))
        return word;
    
    // Check diagonal (top-right to bottom-left)
    word = "";
    word += board[0][2];
    word += board[1][1];
    word += board[2][0];
    if (word.find(' ') == string::npos && isValidWord(word))
        return word;
    
    return "";  // No winning word found
}

// Check if someone has won (formed a valid 3-letter word)
bool Word_Tik_tak_Board::checkWin() {
    return !getWinningWord().empty();
}

// Check if board is full without a winner (draw)
bool Word_Tik_tak_Board::checkDraw() {
    if (checkWin())
        return false;
    return moveCount >= 9;  // 3x3 = 9 cells
}

// Display the board
void Word_Tik_tak_Board::displayBoard() {
    cout << "\n===============================\n";
    cout << "      WORD TIC-TAC-TOE         \n";
    cout << "===============================\n\n";
    
    cout << "     0   1   2\n";
    cout << "   +---+---+---+\n";
    
    for (int i = 0; i < 3; ++i) {
        cout << " " << i << " |";
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == ' ')
                cout << " . ";
            else
                cout << " " << board[i][j] << " ";
            cout << "|";
        }
        cout << "\n";
        cout << "   +---+---+---+\n";
    }
    
    cout << "\n  Moves made: " << moveCount << "/9\n";
    cout << "===============================\n\n";
}

// Check if a cell is empty
bool Word_Tik_tak_Board::isCellEmpty(int row, int col) const {
    if (row < 0 || row >= 3 || col < 0 || col >= 3) return false;
    return board[row][col] == ' ';
}
