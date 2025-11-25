#pragma once
#include "Tic_tac_toe_board.h"

class Tic_tac_toe_ui
{
	private:
		Tik_tac_toe_B& board;
public:
	Tic_tac_toe_ui(Tik_tac_toe_B& b);
		void playGame();           // Main loop of the game
		void getMove(int& row, int& col); // Get row and column
};

