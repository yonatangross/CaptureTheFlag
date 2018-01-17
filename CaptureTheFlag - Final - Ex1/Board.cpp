#include "Board.h"
#include <iostream>
#include <Windows.h>
#include <wincon.h>
#include "Utils.h"

using namespace std;

// Initialization
void Board::initialBoard()
{
	// initial Forests.
	board[4][3].setCh(FOREST);
	board[5][3].setCh(FOREST);
	board[6][3].setCh(FOREST);
	board[6][4].setCh(FOREST);
	board[7][1].setCh(FOREST);
	board[7][2].setCh(FOREST);
	board[7][3].setCh(FOREST);
	board[7][4].setCh(FOREST);
	board[8][1].setCh(FOREST);
	board[8][4].setCh(FOREST);
	board[9][4].setCh(FOREST);

	// initial Seas 
	board[4][10].setCh(SEA);
	board[5][9].setCh(SEA);
	board[5][10].setCh(SEA);
	board[6][8].setCh(SEA);
	board[6][9].setCh(SEA);
	board[6][10].setCh(SEA);
	board[7][10].setCh(SEA);
	board[7][11].setCh(SEA);
	board[8][10].setCh(SEA);
	board[8][11].setCh(SEA);
	board[8][12].setCh(SEA);
	board[9][10].setCh(SEA);
	board[9][11].setCh(SEA);
	board[10][10].setCh(SEA);

	// initial flags
	board[1][11].setCh(PL0_FLAG); // $ for flag A
	board[13][2].setCh(PL1_FLAG); // # for flag B
}
void Board::resetBoard()
{
		for (auto i = 1; i < NUM_OF_ROWS; i++)
			for (auto j = 1; j < NUM_OF_COLS; j++)
				this->board[i][j].setCh(' ');
}

// Print
void Board::printBoard()
{
	CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo;
	HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE);

	//                  1   2   3   4   5   6   7   8   9  10  11  12  13
	setColor(YELLOW);
	gotoxy(0, 9);
	cout << "\t         A   B   C   D   E   F   G   H   I   J   K   L   M" << endl;
	resetColor();
	cout << "\t    +-------------------------------------------------------+" << endl;

	for (auto i = 1; i < NUM_OF_ROWS; i++)
	{
		if (i < 10)
			cout << "\t    + ";
		else
			cout << "\t    +";
		setColor(YELLOW);
		cout << i;
		resetColor();
		cout << "|";
		for (auto j = 1; j < NUM_OF_COLS; j++)
		{
			cout << " ";
			GetConsoleScreenBufferInfo(hStd, &screenBufferInfo);
			board[i][j].setX(screenBufferInfo.dwCursorPosition.X);
			board[i][j].setY(screenBufferInfo.dwCursorPosition.Y);
			board[i][j].setRow(i);
			board[i][j].setCol(j);
			printCell(board[i][j]);
			cout << " |";
		}
		cout << endl;
	}
	cout << "\t    +-------------------------------------------------------+";
}
void Board::printCell(const Cell& currCell)
{
	if (currCell.getCh() == PL0_FLAG || currCell.getCh() == PL1_FLAG)
	{
		setColor(RED);
		currCell.draw(currCell.getCh());
		resetColor();
	}
	else if (currCell.getCh() == FOREST)
	{
		setColor(GREEN);
		currCell.draw(currCell.getCh());
		resetColor();
	}
	else if (currCell.getCh() == SEA)
	{
		setColor(BLUE);
		currCell.draw(currCell.getCh());
		resetColor();
	}
	else
		currCell.draw(currCell.getCh());
}


