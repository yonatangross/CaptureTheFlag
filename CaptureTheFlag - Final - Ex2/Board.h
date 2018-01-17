#pragma once
#include "Cell.h"
#include <Windows.h>
#include <wincon.h>
#include <vector>
#include <map>
#include "Utils.h"
#include "FileHandler.h"
#include <iostream>
#include <fstream>
#include <string>


using namespace std;
class Board
{
	
public:
	enum BOARD_SIZE {NUM_OF_COLS=14,NUM_OF_ROWS=14,SCREEN_HEIGHT=25,SCREEN_WIDTH=80};
	enum SIGNS { PL0_FLAG = 'A', PL1_FLAG = 'B', SEA='S',FOREST='T'};
	Cell board[NUM_OF_ROWS][NUM_OF_COLS];
	FileHandler files;
	
	// Initialization

	bool init(bool fromfile, bool quiet, Cell toolPostions[][3]);

	void initialBoard();
	Cell findAndSetTool(int minLine, int maxLine, char toolSign);
	 bool fromFileIsOK(Cell toolPostions[][3]);
	 void randomizeTools(Cell toolPostions[][3]);
	void resetBoard();
	
	void SetCells();
	// Print
	void printBoard();
	static void printCell(const Cell& currCell);
	
	void printToFileBorad(std::string FileName);
	char printCellToFile(const Cell& cell);
	void printcharError(std::vector<char> wrongCH, std::string boardFileName);

	void initInputFiles();
};

