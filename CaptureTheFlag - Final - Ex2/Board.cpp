#include "Board.h"

using namespace std;

bool Board::init(bool fromfile , bool quiet , Cell toolPostions[][3])
{
	SetCells();
	bool result = true;
	//init random game;
	if (!fromfile )
	{
		initialBoard();
		 randomizeTools(toolPostions);
	}
	else
	{
		
		result = fromFileIsOK(toolPostions);
	}
		
	if (!quiet && result)
		printBoard();
	return result;
	
}

void Board::SetCells()
{
	for (size_t i = 1; i <NUM_OF_ROWS ; i++)
	{
		for (size_t j = 1; j < NUM_OF_COLS; j++)
		{
			board[i][j].setRow(i);
			board[i][j].setCol(j);
			board[i][j].setCh(' ');
		}
	}
	
}
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
	//board[1][11].setCh(PL0_FLAG); // $ for flag A
	//board[13][2].setCh(PL1_FLAG); // # for flag B
	
}

bool Board::fromFileIsOK( Cell toolPostions[][3])
{
	std::string line;

	files.openInputFile();
	
	//check if flags are stes
	bool playerAflagSet = false;
	bool playerBflagSet = false;

	//check if there are error for player a 
	bool playerAfault = false;
	bool playerBfault = false;

	//check if wrong char exists 
	bool wrongChar = false;
	std::vector <char>  wrongCH;


	for (size_t i = 1; i < NUM_OF_ROWS; i++)
	{
		line = files.getNextline();
		for (size_t j = 0; j < NUM_OF_COLS - 1 && j<=line.length() ; j++)
		{
			if (line[j] != ' ')
			{
			
				if (line[j] >= '1' && line[j] <= '9') //char is  Digit:
				{
					if (line[j] > '3' && line[j] < '7')// Wrong Digit:
					{
						wrongChar = true;
						wrongCH.push_back(line[j]);
					}
					else //means correct number:
					{
						int tool = line[j] - '0';
						if (toolPostions[tool / TOOL_BORDER][(tool % TOOL_BORDER) - 1].isUnIntilizedCell())
						{
							//init tool postions;
							Cell c;
							c.setCol(j + 1);
							c.setRow(i);
							c.setCh(line[j]);
							toolPostions[tool / TOOL_BORDER][tool % TOOL_BORDER - 1] = c;
							board[i][j + 1].setCh(line[j]);
						}
						else // means double initialization:
						{
							if (line[j] < '5')
								playerAfault = true;
							else
								playerBfault = true;
						}
					}
				}

				else// char, not a digit:
					if (line[j] == 'A' || line[j] == 'B' || line[j] == 'T' || line[j] == 'S')
					{
						board[i][j + 1].setCh(line[j]);
						if (line[j] == 'A')
						{
							if (playerAflagSet == true)
								playerAfault = true;
							playerAflagSet = true;
						}
						if (line[j] == 'B')
						{
							if (playerBflagSet == true)
								playerBfault = true;
							playerBflagSet = true;
						}
					}
					else
					{
						wrongChar = true;
						wrongCH.push_back(line[j]);
					}

			}
		}
	}//end of file loop
	files.closeInputFile();

	//verify that all tools are initialized:


	for (size_t j = 0; j < 3; j++)
		if (toolPostions[0][j].isUnIntilizedCell())
			playerAfault = true;

	for (size_t j = 0; j < 3; j++)
		if (toolPostions[1][j].isUnIntilizedCell())
			playerBfault = true;

	//vrify both flags setted:
	if (playerAflagSet==false)
		playerAfault = true;

	if (playerBflagSet == false)
		playerBfault = true;


	//print messages:
	string boardFileName = files.getInputFileName();
	if (playerAfault == true)
		cout << "Wrong settings for player A tools in file " << boardFileName << endl;
	if (playerBfault == true)
		cout << "Wrong settings for player B tools in file " << boardFileName << endl;
	if (wrongChar)
	{
		printcharError(wrongCH, boardFileName);
	}
	

	return !(playerAfault || playerBfault || wrongChar);
}

void Board::printcharError(vector<char> wrongCH, string boardFileName)
{
	std::map<char, int>  chars;
	for (auto ch : wrongCH)
		if (!chars[ch])//char wasnt print already
		{
			++chars[ch];//count the char
			cout << "Wrong character on board : " << ch << "in file" << boardFileName << endl;
		}

}

void Board::initInputFiles()
{
	files.getInputFiles();
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
 


void Board::printToFileBorad(std::string FileName)
{
	files.setrecordFile(FileName);
	for (auto i = 1; i < NUM_OF_ROWS; i++)
	{
		for (auto j = 1; j < NUM_OF_COLS; j++)
		{
			 
			 char ch = printCellToFile(board[i][j]);
			files.writeChar(ch);
		}
		string str = "# " + to_string(i) + " \n";
		files.writeLine(str);
		
	}
	files.writeLine("------------ -'\nABCDEFGHIJKLM");

	files.closeRecorderFile();
	
	
}

	char Board::printCellToFile(const Cell& cell)
	{
		
		switch (cell.getCh())
		{
		case PL0_FLAG : 
			return  'A'; break; 
		case PL1_FLAG:
			return 'B'; break;
		case FOREST:
			return 'T'; break;
		case SEA:
			return 'S'; break;
		 default:
			 return cell.getCh(); break;
		}
		
	}


	Cell Board::findAndSetTool(int minLine, int maxLine, char toolSign)
	{
		Cell res;
		auto found = false;
		int colPos;
		int rowPos;

		while (!found) // finds free location
		{
			colPos = 1 + rand() % (Board::NUM_OF_COLS - 1); // rand (1,13)
			rowPos = minLine + rand() % (maxLine - minLine);
			if (board[rowPos][colPos].getCh() == ' ') // check if cell is free of tools/flags.
			{
				found = true;
				res = board[rowPos][colPos];
				board[rowPos][colPos].setCh(toolSign);
			}
		}
		return res;
	}
	void Board::randomizeTools(Cell toolPostions[][3])
	{
		enum { MIN_LINE = 1, MAX_LINE = 5, diff = 8 };
		Cell freePos;
		char toolSign;
		int add;
		int min;
		int max; 
		for (size_t j = 0; j < 2; j++)
		{
			add = (j * TOOL_BORDER + 1)+'0';
			min = j * diff + MIN_LINE;
			max =j * diff + MAX_LINE;
			toolSign = j+'A';
			freePos = findAndSetTool(min, max, toolSign);
			
			freePos.setCh(toolSign);
			printCell(freePos);
			for (auto i = 0; i < 3; i++) // first player
			{
				toolSign = i + add ;
				freePos = findAndSetTool(min, max, toolSign); // finds free location and sets the new tool on the board.
				freePos.setCh(toolSign);
				//board[freePos.getRow()][freePos.getCol()].setCh(toolSign);
				Cell c;
				c.setCol(freePos.getCol());
				c.setRow(freePos.getRow());
				c.setCh(toolSign);

				
				toolPostions[j][i] = c;
				freePos.setCh(toolSign);
				//freePos.draw(toolSign);
			}
		}
	
	

		 // finds free location and sets the new tool on the board.
		
		
	
	}