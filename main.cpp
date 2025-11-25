#include "Numerical_Board.h"
#include "Numerical_UI.h"
#include <iostream>
using namespace std;

void displayMenu()
{
    cout << "\n";
    cout << "========================================" << endl;
    cout << "     WELCOME TO OUR GAMES APP" << endl;
    cout << "========================================" << endl;
    cout << "\n  Please select a game to play:\n" << endl;
    cout << "  [1]  SUS" << endl;
    cout << "  [2]  Four-in-a-row" << endl;
    cout << "[3]  5×5 Tic Tac Toe" << endl;
    cout << "  [4]  Word Tic-Tac-Toe" << endl;
    cout << "  [5]  Misère Tic-Tac-Toe" << endl;
    cout << "  [6]  Diamond Tic-Tac-Toe" << endl;
    cout << "  [7]  4×4 Tic-Tac-Toe" << endl;
    cout << "  [8]  Pyramid Tic-Tac-Toe" << endl;
    cout << "  [9]  Numerical Tic-Tac-Toe" << endl;
    cout << "  [10] Obstacles Tic-Tac-Toe" << endl;
    cout << "  [11] Infinity Tic-Tac-Toe" << endl;
    cout << "\n  [12] Exit" << endl;
    cout << "\n========================================" << endl;
    cout << "Enter your choice: ";
}

void chooseGame(int choice)
{
    string game_name;
    cout << "\n";
    if (choice == 1)
    {
        game_name = "SUS";
        cout << game_name << " loaded." << endl;
        SUSBoard susBoard;
        SUSUI susUI(susBoard);
        susUI.playGame();
    }
    else if (choice == 2)
    {
        game_name = "Four-in-a-row";
        cout << game_name << " loaded." << endl;
    }
    else if (choice == 3)
    {
        game_name = "5x5 Tic Tac Toe";
        cout << game_name << " loaded." << endl;
    }
    else if (choice == 4)
    {
        game_name = "Word Tic-Tac-Toe";
        cout << game_name << " loaded." << endl;
    }
    else if (choice == 5)
    {
        game_name = "Misère Tic-Tac-Toe";
        cout << game_name << " loaded." << endl;
    }
    else if (choice == 6)
    {
        game_name = "Diamond Tic-Tac-Toe";
        cout << game_name << " loaded." << endl;
    }
    else if (choice == 7)
    {
        game_name = "4x4 Tic-Tac-Toe";
        cout << game_name << " loaded." << endl;
    }
    else if (choice == 8)
    {
        game_name = "Pyramid Tic-Tac-Toe";
        cout << game_name << " loaded." << endl;
    }
    else if (choice == 9)
    {

        game_name = "Numerical Tic-Tac-Toe";
        cout << game_name << " loaded." << endl;
        NumericalBoard board;
        NumericalUI ui(board);
        ui.playGame();

    }
    else if (choice == 10)
    {
        game_name = "Obstacles Tic-Tac-Toe";
        cout << game_name << " loaded." << endl;
        ObstaclesBoard board;
        ObstaclesUI ui(board);
        ui.playGame();
    }
    else if (choice == 11)
    {
        game_name = "Infinity Tic-Tac-Toe";
        cout << game_name << " loaded." << endl;
    }
    else if (choice == 12)
    {
        cout << "\n Exiting the application. Goodbye!\n" << endl;
        exit(0);
    }
}
int main() {
    while (true)
    {
        int choice;
        displayMenu();
        cin >> choice;

        if (choice > 12 || choice < 1)
        {
            cout << "\n Invalid choice. Please try again.\n" << endl;
            continue;
        }

        chooseGame(choice);
    }

    return 0;
}
