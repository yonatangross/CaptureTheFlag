#pragma once
#include "Cell.h"


class Board
{
public:
	enum BOARD_SIZE {NUM_OF_COLS=14,NUM_OF_ROWS=14,SCREEN_HEIGHT=25,SCREEN_WIDTH=80};
	enum SIGNS { PL0_FLAG = '$', PL1_FLAG = '#', SEA='~',FOREST='^'};
	Cell board[NUM_OF_ROWS][NUM_OF_COLS];
	
	// Initialization
	void initialBoard();
	void resetBoard();

	// Print
	void printBoard();
	static void printCell(const Cell& currCell);
};

