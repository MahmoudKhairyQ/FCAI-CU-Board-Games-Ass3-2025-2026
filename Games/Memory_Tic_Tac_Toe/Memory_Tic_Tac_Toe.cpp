#include "Memory_Tic_Tac_Toe.h"

using namespace std;

MemoryTicTacToe::MemoryTicTacToe(const string& aiName) {
    player1_name = "Player 1";
    player2_name = aiName;

    srand(time(0));

    // Initialize boards
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++) {
            board[i][j] = ' ';
            hidden_board[i][j] = ' ';
        }
}

void MemoryTicTacToe::printBoard() {
    cout << "\n  1 2 3\n";
    for (int i = 0; i < 3; i++) {
        cout << i + 1 << " ";
        for (int j = 0; j < 3; j++) {
            cout << hidden_board[i][j];
            if (j < 2) cout << "|";
        }
        cout << endl;
        if (i < 2) cout << "  -+-+-\n";
    }
}

bool MemoryTicTacToe::isBoardFull() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == ' ')
                return false;
    return true;
}

void MemoryTicTacToe::playerMove(const string& player, char mark) {
    int row, col;
    while (true) {
        cout << player << "'s turn. Enter row and column (1-3): ";
        cin >> row >> col;
        if (row >= 1 && row <= 3 && col >= 1 && col <= 3 && board[row - 1][col - 1] == ' ') {
            board[row - 1][col - 1] = mark;
            hidden_board[row - 1][col - 1] = ' '; // hide immediately
            break;
        }
        cout << "Invalid move! Try again.\n";
    }
}

void MemoryTicTacToe::aiMove(const string& player, char mark) {
    int row, col;
    do {
        row = rand() % 3;
        col = rand() % 3;
    } while (board[row][col] != ' ');

    board[row][col] = mark;
    hidden_board[row][col] = ' '; // hide immediately
    moves_memory[{row, col}] = mark;
    cout << player << " placed a mark at (" << row + 1 << "," << col + 1 << ")" << endl;
}

bool MemoryTicTacToe::checkWin(char mark) {
    // Check rows
    for (int i = 0; i < 3; i++)
        if (board[i][0] == mark && board[i][1] == mark && board[i][2] == mark) return true;

    // Check columns
    for (int j = 0; j < 3; j++)
        if (board[0][j] == mark && board[1][j] == mark && board[2][j] == mark) return true;

    // Check diagonals
    if (board[0][0] == mark && board[1][1] == mark && board[2][2] == mark) return true;
    if (board[0][2] == mark && board[1][1] == mark && board[2][0] == mark) return true;

    return false;
}

void MemoryTicTacToe::play() {
    int mode;
    cout << "Select mode:\n1. Player vs Player\n2. Player vs AI\n3. AI vs AI\n";
    cin >> mode;

    char player1_mark = 'X';
    char player2_mark = 'O';

    while (!isBoardFull()) {
        printBoard();

        if (mode == 1) {
            playerMove(player1_name, player1_mark);
            if (checkWin(player1_mark)) { printBoard(); cout << player1_name << " wins!\n"; return; }
            if (isBoardFull()) break;
            playerMove("Player 2", player2_mark);
            if (checkWin(player2_mark)) { printBoard(); cout << "Player 2 wins!\n"; return; }
        }
        else if (mode == 2) {
            playerMove(player1_name, player1_mark);
            if (checkWin(player1_mark)) { printBoard(); cout << player1_name << " wins!\n"; return; }
            if (isBoardFull()) break;
            aiMove(player2_name, player2_mark);
            if (checkWin(player2_mark)) { printBoard(); cout << player2_name << " wins!\n"; return; }
        }
        else if (mode == 3) {
            aiMove(player1_name, player1_mark);
            if (checkWin(player1_mark)) { printBoard(); cout << player1_name << " wins!\n"; return; }
            if (isBoardFull()) break;
            aiMove(player2_name, player2_mark);
            if (checkWin(player2_mark)) { printBoard(); cout << player2_name << " wins!\n"; return; }
        }
    }

    printBoard();
    cout << "Game Over! It's a draw!\n";
}
