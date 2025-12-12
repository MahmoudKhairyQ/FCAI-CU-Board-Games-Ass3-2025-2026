#include "BoardGame_Classes.h"
#include "Numerical_Board.h"
#include "Numerical_UI.h"
#include "SUS_Board.h"
#include "SUS_UI.h"
#include "5x5_Tik_tac_toe_Board.h"
#include "5x5_Tik_tac_toe_ui.h"
#include "Misere_Board.h"
#include "Misere_UI.h"
#include "FourXFour_Board.h"
#include "FourXFour_UI.h"
#include "Pyramid_Board.h"
#include "Pyramid_UI.h"
#include "Ultimate_Board.h"
#include "Ultimate_UI.h"
#include "Obstacles_Board.h"
#include "Obstacles_UI.h"
#include "FourInARow_Board.h"
#include "FourInARow_UI.h"
#include "Diamond_Board.h"
#include "Diamond_UI.h"
#include "Word_Tic_tac_board.h"
#include "Word_Tic_tac_ui.h"
#include "Infinity_Board.h"
#include "Infinity_UI.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void displayMenu() {
    cout << "\n";
    cout << "========================================" << endl;
    cout << "     WELCOME TO OUR GAMES APP" << endl;
    cout << "========================================" << endl;
    cout << "\nChoose your option:" << endl;
    cout << "1) SUS" << endl;
    cout << "2) Four-in-a-row" << endl;
    cout << "3) 5 x 5 Tic Tac Toe" << endl;
    cout << "4) Word Tic-tac-toe" << endl;
    cout << "5) Misere Tic Tac Toe" << endl;
    cout << "6) Diamond Tic-Tac-Toe" << endl;
    cout << "7) 4 x 4 Tic-Tac-Toe" << endl;
    cout << "8) Pyramid Tic-Tac-Toe" << endl;
    cout << "9) Numerical Tic-Tac-Toe" << endl;
    cout << "10) Obstacles Tic-Tac-Toe" << endl;
    cout << "11) Infinity Tic-Tac-Toe" << endl;
    cout << "12) Ultimate Tic Tac Toe" << endl;
    cout << "13) Memory Tic-Tac-Toe" << endl;
    cout << "14) Exit" << endl;
    cout << "\n========================================" << endl;
    cout << "Enter your choice: ";
}
void playWord_Tic_tac_toe() {
    cout << "\n=== Starting Word Tic-tac-toe ===\n" << endl;
    
    // Ask if player wants to play vs Human or AI
    cout << "Choose game mode:\n";
    cout << "1. Human vs Human\n";
    cout << "2. Human vs AI\n";
    cout << "Enter choice: ";
    int mode;
    cin >> mode;
    
    bool vsAI = (mode == 2);
    
    Word_Tik_tak_Board board;
    Word_Tik_tak_UI ui(board, vsAI);
    ui.playGame();
}
void playInfinityGame() {
    std::cout << "\n=== Starting Infinity Tic-Tac-Toe ===\n" << std::endl;
    InfinityBoard* board = new InfinityBoard();
    InfinityUI* ui = new InfinityUI("Infinity Tic-Tac-Toe", board);
    Player<char>** players = ui->setup_players();
    GameManager<char> game(board, players, ui);
    game.run();

    delete players[0];
    delete players[1];
    delete[] players;
    delete ui;
    delete board;
}

void playNumericalGame() {
    cout << "\n=== Starting Numerical Tic-Tac-Toe ===\n" << endl;

    NumericalBoard* board = new NumericalBoard();
    NumericalUI* ui = new NumericalUI("Numerical Tic-Tac-Toe");
    Player<int>** players = ui->setup_players();
    GameManager<int> game(board, players, ui);
    game.run();

    delete players[0];
    delete players[1];
    delete[] players;
    delete ui;
    delete board;
}

void playSUSGame() {
    cout << "\n=== Starting SUS Game ===\n" << endl;

    SUSBoard* board = new SUSBoard();
    SUSUI* ui = new SUSUI("Welcome to our SUS Game");
    Player<char>** players = ui->setup_players();
    GameManager<char> game(board, players, ui);
    game.run();

    delete players[0];
    delete players[1];
    delete[] players;
    delete ui;
    delete board;
}

void playFiveXFiveGame() {
    cout << "\n=== Starting 5x5 Tic Tac Toe ===\n" << endl;
    
    // Ask if player wants to play vs Human or AI
    cout << "Choose game mode:\n";
    cout << "1. Human vs Human\n";
    cout << "2. Human vs AI\n";
    cout << "Enter choice: ";
    int mode;
    cin >> mode;
    cin.ignore(10000, '\n');  // Clear input buffer
    
    bool vsAI = (mode == 2);
    
    Tik_tac_toe_B board;
    Tic_tac_toe_ui ui(board, vsAI);
    ui.playGame();
}

void playMisereGame() {
    cout << "\n=== Starting Misère Tic-Tac-Toe ===\n" << endl;
    cout << "Rules: Avoid making three in a row! If you make three in a row, you LOSE!\n" << endl;

    MisereBoard* board = new MisereBoard();
    MisereUI* ui = new MisereUI("Misère Tic-Tac-Toe");
    Player<char>** players = ui->setup_players();
    GameManager<char> game(board, players, ui);
    game.run();

    delete players[0];
    delete players[1];
    delete[] players;
    delete ui;
    delete board;
}

void playObstaclesGame() {
    cout << "\n=== Starting Obstacles Tic-Tac-Toe ===\n" << endl;

    ObstaclesBoard* board = new ObstaclesBoard();
    ObstaclesUI* ui = new ObstaclesUI("Obstacles Tic-Tac-Toe");
    Player<char>** players = ui->setup_players();
    GameManager<char> game(board, players, ui);
    game.run();

    delete players[0];
    delete players[1];
    delete[] players;
    delete ui;
    delete board;
}

void playFourInARowGame() {
    cout << "\n=== Starting Four-in-a-row (Connect 4) ===\n" << endl;
    cout << "Rules: Drop your pieces in columns. First to get 4 in a row wins!\n" << endl;

    FourInARowBoard* board = new FourInARowBoard();
    FourInARowUI* ui = new FourInARowUI("Four-in-a-row");
    Player<char>** players = ui->setup_players();
    GameManager<char> game(board, players, ui);
    game.run();

    delete players[0];
    delete players[1];
    delete[] players;
    delete ui;
    delete board;
}

void playFourXFourGame() {
    cout << "\n=== Starting 4x4 Tic Tac Toe ===\n" << endl;

    FourXFourBoard* board = new FourXFourBoard();
    FourXFourUI* ui = new FourXFourUI("4x4 Tic Tac Toe");
    Player<char>** players = ui->setup_players();
    GameManager<char> game(board, players, ui);
    game.run();

    delete players[0];
    delete players[1];
    delete[] players;
    delete ui;
    delete board;
}

void playPyramidGame() {
    cout << "\n=== Starting Pyramid Tic Tac Toe ===\n" << endl;

    PyramidBoard* board = new PyramidBoard();
    PyramidUI* ui = new PyramidUI("Pyramid Tic Tac Toe");
    Player<char>** players = ui->setup_players();
    GameManager<char> game(board, players, ui);
    game.run();

    delete players[0];
    delete players[1];
    delete[] players;
    delete ui;
    delete board;
}

void playUltimateGame() {
    cout << "\n=== Starting Ultimate Tic Tac Toe ===\n" << endl;

    UltimateBoard* board = new UltimateBoard();
    UltimateUI* ui = new UltimateUI("Ultimate Tic Tac Toe");
    Player<char>** players = ui->setup_players();
    GameManager<char> game(board, players, ui);
    game.run();

    delete players[0];
    delete players[1];
    delete[] players;
    delete ui;
    delete board;
}

void playDiamondGame() {
    cout << "\n=== Starting Diamond Tic-Tac-Toe ===\n" << endl;
    DiamondBoard* board = new DiamondBoard();
    DiamondUI* ui = new DiamondUI("Diamond Tic-Tac-Toe");
    Player<char>** players = ui->setup_players();
    GameManager<char> game(board, players, ui);
    game.run();

    delete players[0];
    delete players[1];
    delete[] players;
    delete ui;
    delete board;
}

void chooseGame(int choice) {
switch (choice) {
    case 1: playSUSGame(); break;
    case 2: playFourInARowGame(); break;
    case 3: playFiveXFiveGame(); break;
    case 4: playWord_Tic_tac_toe(); break;
    case 5: playMisereGame(); break;
    case 6: playDiamondGame(); break;
    case 7: playFourXFourGame(); break;
    case 8: playPyramidGame(); break;
    case 9: playNumericalGame(); break;
    case 10: playObstaclesGame(); break;
    case 11: playInfinityGame(); break;
    case 12: playUltimateGame(); break;
    case 13: cout << "Memory Tic-Tac-Toe - Coming soon!\n"; break;
    case 14:
        cout << "\nExiting the application. Goodbye!\n" << endl;
        exit(0);
        break;
    default: cout << "Invalid choice!" << endl; break;
    }
}

int main() {
    cout << "Initializing Games Application..." << endl;
    srand(time(0));
    
    while (true) {
        int choice;
        displayMenu();

        if (!(cin >> choice)) {
            cout << "\nInvalid input. Please enter a number.\n" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        if (choice < 1 || choice > 14) {
            cout << "\nInvalid choice. Please enter a number between 1 and 14.\n" << endl;
            continue;
        }

        chooseGame(choice);

        cout << "\nPress Enter to continue to main menu...";
        cin.ignore();
        cin.get();
    }

    return 0;
}
