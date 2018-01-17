#include "Game.h"
#include <Windows.h>
#include <conio.h>
#include <iostream>


// Input Interpretation
bool Game::run(bool Reversed )
{
	

	/*init game by attrbiue*/
	GameRound++; // increse game counter number
	bool quitGame = false; // init quit game
	if (Reversed)
		reversedGame = true; //set revrsed
	
	// Initiallize game.
	if (!quietGame) // if not quiet game print headers
	{
		printHeader();
		printScore();
	}
	
	//init bored - this function return all the tools postion and set them to the player
	fileBoard = fileBoard && playBoard.files.getNumOfInputFiles() > 0;
		Cell toolPostions[PLAYERS_NUMER][TOOLS_NUMBER];
		gameOver = !playBoard.init(fileBoard , quietGame , toolPostions); //if there are problem with the borad - game is over before begin .no move can by excute
		
		
	

		
	
	if (!gameOver) //if the borad is fine
	{
		setToolToPlayer(toolPostions); // init tool postion from borad to players
		//if need to record - open record file 
		if (recordingGame)
		{
			initRecordingfiles();
		}
		//if moves file - open move file and init data
		if (fileMoves)
		{
			setMovefiles();
		}
		// game cycle init 
		cycle = 0;
		
		//play the game;
		bool quitGame = playTheGame();

		//set not valid both player so in the next game step should by init again
		players[PL0].setLastMoveValid(false);
		players[PL1].setLastMoveValid(false);
		
		//if recording close file - for file move the file colse on fileHandler with the last line;
		if (recordingGame)
		{
			closeFiles();
		}

		cin.clear();

	}
	//for the last file;
	if (fileBoard && playBoard.files.getNumOfInputFiles() == 0)
		return false;


		return quitGame;
	

}


void Game::setToolToPlayer(Cell toolPostions[PLAYERS_NUMER][TOOLS_NUMBER])
{
	for (size_t i = 0; i < PLAYERS_NUMER; i++)
	{
		for (size_t j = 0; j < TOOLS_NUMBER; j++)
		{
			int row = toolPostions[i][j].getRow();
			int col = toolPostions[i][j].getCol();
			players[i].setTool(playBoard.board[row][col], j, toolPostions[i][j].getCh());
			if (!quietGame)
			{
				playBoard.board[row][col].draw(toolPostions[i][j].getCh());
			}

		}
	}
}
bool Game::playTheGame()
{
	//init 
	bool quitGame = false;
	char keyPressed = 0;
	int currentPlayer = 1;


	while (!gameOver)
	{
		if (!fileMoves)
		{
			if (_kbhit())
			{
				getInput(keyPressed, quitGame);
			characterizeKey(keyPressed);
			}
			if (players[currentPlayer].getLastMoveValid())
				{
				//change valid to false - if the tool move it will cahnge back to true;
					players[currentPlayer].setLastMoveValid(false);
					executeStep(currentPlayer);
				}

			}

		//for file moves
		else
		{
			//choose the next move for payer - set the next move and decied if need to be done
			if (players[currentPlayer].checkNextMove(cycle))
			{
				//init last move as not valid - if the tool will be moved change to ture 
				players[currentPlayer].setLastMoveValid(false);
				//do the step
				if (players[currentPlayer].getDirection() != STOP)
				executeStep(currentPlayer);
				//players[currentPlayer].setNextMove();
				
			}
			if (!gameOver)
			{
				//check end of file for both player - if no one win 
				gameOver = players[currentPlayer].getLastline() && players[1 - currentPlayer].getLastline()
					&& !players[currentPlayer].getLastMoveValid() && !players[1 - currentPlayer].getLastMoveValid();
				//if no one print message for quit game no win
				if (gameOver && quietGame)
				{
					printWinningQuietMessage("NONE");
				}
			}
		}
		//change player
		currentPlayer = 1 - currentPlayer;
		//move to next cycle
		cycle++;
		if (!quietGame)
		{
			Sleep(delay);
		}
	}
	return quitGame;
}
void Game::getInput(char& keyPressed, bool &quitGame)
{
	keyPressed = 0;

	keyPressed = _getch();
	if (keyPressed == ESC)
		handleSideMenu(quitGame);
	else
		reguliseInput(keyPressed);
}


void Game::handleSideMenu(bool &quitGame)
{
	char userSelection;

	printSideMenu();
	userSelection = _getch();
	Sleep(200);
	clearScreen();
	switch (userSelection)
	{
	case CONTINUE:
		this->printHeader();
		this->printScore();
		playBoard.printBoard();
		break;
	case RESTART:
		this->resetBoard();
		this->run(reversedGame );
		break;
	case MAIN_MENU:
		gameOver = true;
		playBoard.resetBoard();
		break;
	case QUIT:
		gameOver = true;
		quitGame = true;
		break;
	default:
		cout << "Incorrect input, Please enter again.";
		for (size_t i = 0; i < 3; i++)
		{
			cout << '.';
			Sleep(500);
		}
		handleSideMenu(quitGame);
		break;
	}
}
void Game::reguliseInput(char &keyPressed)
{
	bool invalidInput = false;

	if ((keyPressed < 'A' || keyPressed > 'z') && (keyPressed < '0' || keyPressed > '9')) //Not english or Not 0-9
		invalidInput = true;
	if (invalidInput)
	{
		string invalid = "Invalid input, change to english and press numbers and english letters only.";
		gotoxy(Board::SCREEN_WIDTH / 2 - int(invalid.length()) / 2,8);
		cout << invalid;
		keyPressed = _getch();
		gotoxy(Board::SCREEN_WIDTH / 2 - int(invalid.length()) / 2, 8);
		cout << "                                                                             ";
	}
	else
		keyPressed = char(tolower(keyPressed)); // Caps Lock
}
void Game::characterizeKey(char keyPressed)
{
	string pl0Letters = "adwx", pl1Letters = "jlim";
	
	// Tool selection 
	if (keyPressed >= '1' && keyPressed <= '3')
	{
		stopLastTool(PL0);
		
		readTool(keyPressed, PL0);
	}
	if (keyPressed >= '7' && keyPressed <= '9')
	{
		stopLastTool(PL1);
		readTool(keyPressed, PL1);
	}

	// Movement selection 
	for (auto i = 0; i < pl0Letters.length(); i++)
		if (keyPressed == pl0Letters[i])
		{
			players[PL0].setLastMoveValid(true);
			players[PL0].setStepReocrded(false);
			moveHandler(keyPressed, PL0);
		}
	for (auto i = 0; i < pl1Letters.length(); i++)
		if (keyPressed == pl1Letters[i])
		{
			players[PL1].setLastMoveValid(true);
			players[PL1].setStepReocrded(false);
			moveHandler(keyPressed, PL1);
		}
}

void Game::stopLastTool(int playerIndex)
{
	players[playerIndex].setLastMoveValid(false);
	
	if (recordingGame )
	{
		players[playerIndex].setStepReocrded(false);
		int modifyCycle = cycle % 2 != playerIndex ? cycle : cycle + 1;
			
		players[playerIndex].recoredMove(modifyCycle);
	}
}


void Game::readTool(char keyPressed, int playerIndex)
{
	int toolInd;

	toolInd = getToolInd(keyPressed, playerIndex);

	if (players[playerIndex].getToolState(toolInd)) // check tool's activity
		players[playerIndex].setSelectedToolInd(toolInd);
}
int Game::getToolInd(char keyPressed, int playerIndex)
{
	int toolInd;

	if (playerIndex == PL0)
		toolInd = keyPressed - '1';
	else // playerIndex == PL1
		toolInd = keyPressed - '7';

	return toolInd;
}
void Game::moveHandler(char keyPressed, int playerIndex)
{
	players[playerIndex].changeDir(keyPressed); // changes direction.
	players[playerIndex].setLastMoveValid(true);
}

// Move
void Game::executeStep(int playerIndex)
{
	bool validMove;
	int toolInd = players[playerIndex].getSelectedToolInd();
	Cell currentCell = players[playerIndex].getToolUsedCell(toolInd);
	currentCell = playBoard.board[currentCell.getRow()][currentCell.getCol()];
	Directions playerDir = players[playerIndex].getDirection();

	validMove = isValidMove(currentCell, playerDir);
	
	if (validMove && players[playerIndex].getToolState(toolInd)) // conditions: 1. direction 2. tool state
	{
		Cell futureCell = getFutureCell(currentCell, playerDir);
		handleJunction(playerIndex, currentCell, futureCell, toolInd);
	}
}
Cell Game::getFutureCell(const Cell& currentCell, Directions direction)
{
	Cell futureCell;
	int row = currentCell.getRow();
	int col = currentCell.getCol();

	switch (direction) {
	case LEFT:
		futureCell = playBoard.board[row][col - 1];
		break;
	case RIGHT:
		futureCell = playBoard.board[row][col + 1];
		break;
	case UP:
		futureCell = playBoard.board[row - 1][col];
		break;
	case DOWN:
		futureCell = playBoard.board[row + 1][col];
		break;
	default: break;
	}
	return futureCell;
}
bool Game::isValidMove(const Cell& currentCell, Directions direction)
{
	bool validMove = false;
	int nextRow = currentCell.getRow();
	int nextCol = currentCell.getCol();

	switch (direction) {
	case LEFT:
		nextCol = currentCell.getCol() - 1;
		break;
	case RIGHT:
		nextCol = currentCell.getCol() + 1;
		break;
	case UP:
		nextRow = currentCell.getRow() - 1;
		break;
	case DOWN:
		nextRow = currentCell.getRow() + 1;
		break;
	default: break;
	}

	if ((nextRow >= 1 && nextRow < Board::NUM_OF_ROWS) && (nextCol >= 1 && nextCol < Board::NUM_OF_COLS))
		validMove = true;
	return validMove;
}
void Game::handleJunction(int playerIndex, const Cell& currentCell, const Cell& futureCell, int toolInd)
{
	auto otherPlayerIndex = Player::getOtherPlayerIndex(playerIndex);
	auto futureCellChar = futureCell.getCh();
	bool moving = true;

	if (futureCellChar == ' ')
	{
		moveTool(playerIndex, currentCell, futureCell, toolInd);
	}
	else if (futureCellChar == Board::FOREST ) // FOREST
	{
		moving = handleForest(currentCell.getCh());
		if (moving)
			moveTool(playerIndex, currentCell, futureCell, toolInd);
	}
	else if (futureCellChar == Board::SEA) // SEA
	{
		moving = handleSea(currentCell.getCh());
		if (moving)
			moveTool(playerIndex, currentCell, futureCell, toolInd);
	}
	else								// My Tools / Opponent / Flags
	{
		if (!isMyTool(playerIndex, currentCell.getCh(), futureCellChar))
		{
			if (!handleFlags(playerIndex, futureCellChar)) // check for flags.
			{
				auto otherToolInd = getToolInd(futureCellChar, otherPlayerIndex);
				if (validField(playerIndex, toolInd, otherToolInd)) // check if the opponent tool is not on FOREST/SEA
					handleCombat(playerIndex, currentCell, futureCell, toolInd, otherToolInd); // Combat and Flag handling.
			}
		}
	}
}
bool Game::validField(int playerIndex, int toolInd, int otherToolInd) const
{
	bool res = false;
	auto otherPlayerIndex = Player::getOtherPlayerIndex(playerIndex);
	auto usedFutureCellSign = players[otherPlayerIndex].getToolUsedCell(otherToolInd).getCh();

	if (usedFutureCellSign == 'F' ) // FOREST
	{
		if (handleForest(players[playerIndex].getToolSign(toolInd)))
			res = true;
	}
	else if (usedFutureCellSign == 'T') // FOREST
	{
		if (handleSea(players[playerIndex].getToolSign(toolInd)))
			res = true;
	}
	else // OPEN SPACE
		res = true;
	return res;
}
bool Game::handleFlags(int playerIndex, char futureCellChar)
{
	if (playerIndex == PL0 && futureCellChar == Board::SIGNS::PL1_FLAG)
	{
		if (!reversedGame)
			handleWinner(PL0, PL1, FLAG);
		else
			handleWinner(PL1, PL0, FLAG);
	}
	if (playerIndex == PL1 && futureCellChar == Board::SIGNS::PL0_FLAG)
	{
		if (!reversedGame)
			handleWinner(PL1, PL0, FLAG);
		else
			handleWinner(PL0, PL1, FLAG);
	}
	return gameOver;
}
void Game::moveTool(int playerIndex, const Cell& currCell, const Cell& futureCell, int toolInd)
{

	//if tool need be moved so set last turn as valid;
	players[playerIndex].setLastMoveValid(true);

	
	if (cycle %NUM_OF_PLAYERS !=playerIndex)
	{
		auto usedCurrCellChar = players[playerIndex].getToolUsedCell(toolInd).getCh();
		auto toolSign = players[playerIndex].getToolSign(toolInd);
		Cell &rCurrCell = playBoard.board[currCell.getRow()][currCell.getCol()]; // ref to current cell.
		Cell &rFutureCell = playBoard.board[futureCell.getRow()][futureCell.getCol()]; // ref to future cell.
		  // used cell's sign => future cell's sign.
		if (usedCurrCellChar< '1' || usedCurrCellChar>'9')
		rCurrCell.setCh(usedCurrCellChar);
		else 
			rCurrCell.setCh(' ');
		players[playerIndex].setToolUsedCell(rFutureCell, toolInd); // usedCell's Value => futureCell's Value.
		rFutureCell.setCh(toolSign); //  future cell's sign => tool sign.

		//print the updated cells
		if (!quietGame)
		{
			playBoard.printCell(rFutureCell);
			playBoard.printCell(rCurrCell);
		}

		//record step if setp wasn't recorded;
		if (recordingGame && !players[playerIndex].getStepReocrded())
		{
			players[playerIndex].setStepReocrded(true);
			players[playerIndex].recoredMove(cycle);
		}
		
	}

}
bool Game::handleForest(char toolChar)
{
	auto moving = false;
	switch (toolChar)
	{
	case '1':
		break;
	case '2':
		moving = true;
		break;
	case '3':
		break;
	case '7':
		moving = true;
		break;
	case '8':
		moving = true;
		break;
	case '9':
		break;
	default:;
	}
	return moving;
}
bool Game::handleSea(char toolChar)
{
	auto moving = false;
	switch (toolChar)
	{
	case '1':
		break;
	case '2':
		moving = true;
		break;
	case '3':
		moving = true;
		break;
	case '7':
		moving = true;
		break;
	case '8':
		break;
	case '9':
		moving = true;
		break;
	default:;
	}
	return moving;
}
bool Game::isMyTool(int playerIndex, char currCellChar, char futureCellChar)
{
	auto diff = currCellChar - futureCellChar;

	// my tool check
	if (diff < 0) diff *= -1;

	if (diff == 2 || diff == 1)
		return true;

	// my flag check
	if (playerIndex == PL0 && futureCellChar == Board::SIGNS::PL0_FLAG)
		return true;
	if (playerIndex == PL1 && futureCellChar == Board::SIGNS::PL1_FLAG)
		return true;
	return false;
}

//Combat
void Game::handleCombat(int playerIndex, const Cell& currCell, const Cell& futureCell, int toolInd, int otherToolInd)
{
	auto combatWin = false;

	if (playerIndex == PL0)
		checkFirstPlayerWin(futureCell, combatWin, toolInd , otherToolInd);
	else // playerIndex == 1
		checkSecondPlayerWin(futureCell, combatWin, toolInd, otherToolInd);

	if (!this->gameOver)
	{
		if (combatWin)
			updateWinningCombat(playerIndex, currCell, futureCell, toolInd, otherToolInd);
		else
			updateLosingCombat(playerIndex, currCell, toolInd);
		checkNoToolsWin(playerIndex, combatWin);
	}
}
void Game::checkFirstPlayerWin(const Cell& futureCell, bool& win, int toolInd , int otherToolInd)
{
	auto combatRow = futureCell.getRow(), combatCol = futureCell.getCol();
	auto defenseSign = futureCell.getCh();

	switch (toolInd)
	{
	case 0:
		if (combatRow < 10 && combatCol != 4) // win at row:10-13 and col:4(D)
			win = true;
		break;
	case 1:
		
		if (otherToolInd !=2  && (combatRow == 3 || combatRow == 4 || combatCol == 11))  // win 7-8 at row:3-4 col:11(K)
			win = true;
		break;
	case 2:
		if (combatRow == 8 || combatCol == 7) // win at row:8 col:7(G)
			win = true;
		break;
	default:
		break;
	}
}
void Game::checkSecondPlayerWin(const Cell& futureCell, bool& win, int toolInd, int otherToolInd)
{
	auto combatRow = futureCell.getRow(), combatCol = futureCell.getCol();
	
	checkFirstPlayerWin(futureCell, win, otherToolInd, toolInd);
	win = !win;
}
void Game::updateWinningCombat(int playerIndex, const Cell& currCell, const Cell& futureCell, int toolInd, int otherToolInd)
{
	auto otherPlayerInd = Player::getOtherPlayerIndex(playerIndex);
	auto futureCellUsedSign = players[otherPlayerInd].getToolUsedCell(otherToolInd).getCh(); // saving losing tool's used cell char.

	players[otherPlayerInd].setToolState(otherToolInd, false); // deactivate losing tool
	playBoard.board[futureCell.getRow()][futureCell.getCol()].setCh(futureCellUsedSign); // set future cell used sign.
	moveTool(playerIndex, currCell, futureCell, toolInd);
}
void Game::updateLosingCombat(int playerIndex, const Cell& currCell, int toolInd)
{
	auto usedCellChar = players[playerIndex].getToolUsedCell(toolInd).getCh();
	auto& rCell = playBoard.board[currCell.getRow()][currCell.getCol()];

	players[playerIndex].setToolState(toolInd, false); // deactivate losing tool
	rCell.setCh(usedCellChar); // set losing tool's used cell char.
	if (!quietGame)
	{
		playBoard.printCell(rCell);
	}
}
void Game::checkNoToolsWin(int playerIndex, bool combatWin)
{
	auto otherPlayerIndex = Player::getOtherPlayerIndex(playerIndex);
	if (combatWin)
	{
		if (players[otherPlayerIndex].getNumOfActiveTools() == 0)
		{
			if (!reversedGame)
				handleWinner(playerIndex, otherPlayerIndex, OUT_OF_TOOLS);
			else
				handleWinner(otherPlayerIndex, playerIndex, OUT_OF_TOOLS);
		}
	}
	else
	{
		if (players[playerIndex].getNumOfActiveTools() == 0)
		{
			if (!reversedGame)
				handleWinner(otherPlayerIndex, playerIndex, OUT_OF_TOOLS);
			else
				handleWinner(playerIndex, otherPlayerIndex, OUT_OF_TOOLS);
		}
	}
}

// Initialization

void Game::namePlayers()
{
	string tempName;
	cout << "Enter the name of the first player. " << endl;
	getline(cin, tempName);
	players[0].setName(tempName);
	cout << "Enter the name of the second player. " << endl;
	getline(cin, tempName);
	players[1].setName(tempName);
}

// Printing
void Game::printSideMenu()
{
	auto x_printing_location = (Board::SCREEN_HEIGHT / 2 - 1) - int(strlen("< 1 > Exit\n")) / 2;
	auto y_printing_location = Board::SCREEN_WIDTH / 2 - 4;

	clearScreen();
	gotoxy(x_printing_location, y_printing_location);
	cout << "< 1 > Back To Game\n";
	gotoxy(x_printing_location, y_printing_location + 1);
	cout << "< 2 > Restart Game\n";
	gotoxy(x_printing_location, y_printing_location + 2);
	cout << "< 8 > Main Menu\n";
	gotoxy(x_printing_location, y_printing_location + 3);
	cout << "< 9 > Quit Game\n";
}
void Game::printHeader()
{
	string header =
		"      _________    _____                _______________              ______\n"
		"      __  ____/______  /_   ______ _    ___  ____/__  /_____ _______ ___  /\n"
		"      _  / __ _  _ \\  __/   _  __ `/    __  /_   __  /_  __ `/_  __ `/_  / \n"
		"      / /_/ / /  __/ /_     / /_/ /     _  __/   _  / / /_/ /_  /_/ / /_/\n"
		"      \\____/  \\___/\\__/     \\__,_/      /_/      /_/  \\__,_/ _\\__, / (_)   \n"
		"                                                             /____/        ";
	cout << header;
}
void Game::printScore() const
{
	const auto tabLen = 8;
	string ScoreLine = players[PL0].getName() + "'s score: " + to_string(players[PL0].getScore())
		+ "\t\t\t" + players[PL1].getName() + "'s score: " + to_string(players[PL1].getScore());
	auto scoreLineLen = int(ScoreLine.length()) + tabLen * 3;
	auto x_printing_location = Board::SCREEN_WIDTH / 2 - scoreLineLen / 2;

	gotoxy(x_printing_location, 7);
	cout << ScoreLine << endl << endl;
}

void Game::PrintScoreQuiet()
{
	cout << "Game Summary\n";
	cout << "A points:" << players[PL0].getScore() << "\n";
	cout << "B points:" << players[PL1].getScore() << "\n";
}
void Game::printWinningQuietMessage( string  winningPlayerName)
{
	cout << "Game cycle: " << GameRound << "\n";
	cout << "Num moves: " << cycle << "\n";
	cout << "winner: " << winningPlayerName << "\n";
}
void Game::printWinningMessage(int winningPlayerIndex, int losingPlayerIndex, WINNING_REASON winningReason) const
{
	clearScreen();
	if (winningReason == OUT_OF_TOOLS)
	{
		auto outOfToolsStr = "Congratulations " + players[winningPlayerIndex].getName() + ", " + players[losingPlayerIndex].getName() + " is out of tools.";
		gotoxy(Board::SCREEN_WIDTH / 2 - int(outOfToolsStr.length()) / 2, Board::SCREEN_HEIGHT / 2);
		cout << outOfToolsStr;
	}
	else if (winningReason == FLAG)
	{
		auto flagStr = "Congratulations " + players[winningPlayerIndex].getName() + ", you captured " + players[losingPlayerIndex].getName() + "'s flag.";
		gotoxy(Board::SCREEN_WIDTH / 2 - int(flagStr.length()) / 2, Board::SCREEN_HEIGHT / 2);
		cout << flagStr;
	}
	Sleep(2000);
	clearScreen();
}
void Game::printReveresedInstructions() const
{
	auto reversedStr1 = "Reversed game starts! " + players[PL0].getName() + ", " + players[PL1].getName() + " change your sits.";
	string reversedStr2 = "Good Luck! :)";

	clearScreen();
	gotoxy(Board::SCREEN_WIDTH / 2 - int(reversedStr1.length()) / 2, Board::SCREEN_HEIGHT / 2);
	cout << reversedStr1;
	gotoxy(Board::SCREEN_WIDTH / 2 - int(reversedStr2.length()) / 2, Board::SCREEN_HEIGHT / 2 + 2);
	cout << reversedStr2;
	Sleep(2000);
	clearScreen();
}

// Score
void Game::resetScore()
{
	players[PL0].setScore(0);
	players[PL1].setScore(0);
}
void Game::handleWinner(int winningPlayerIndex, int losingPlayerIndex, WINNING_REASON winningReason)
{
	gameOver = true;
	int current_player = 1 - (cycle% NUM_OF_PLAYERS);
	if (recordingGame && !players[current_player].getStepReocrded())
		{
			players[current_player].setLastMoveValid(true);
			players[current_player].setStepReocrded(true);
			players[current_player].recoredMove(cycle);
		}
	players[winningPlayerIndex].setScore(players[winningPlayerIndex].getScore() + 1);
	if (!quietGame)
	{
		printWinningMessage(winningPlayerIndex, losingPlayerIndex, winningReason);
	}
	else
	{
		printWinningQuietMessage(players[winningPlayerIndex].getName());
	}
	
	reversedGame = false;
}

void Game::initFileBorad()
{
	playBoard.files.setEndWith(boradFileExtension);
	playBoard.files.setPath(path);
	playBoard.initInputFiles();
}


void Game::initRecordingfiles()
{
	string FileName = fileBoard ? playBoard.files.getInputFileName() : findNextRandom(path);
	if (!fileBoard)
	{
		playBoard.files.setEndWith(boradFileExtension);
		playBoard.files.setPath(path);
		playBoard.printToFileBorad(FileName);
	}
	players[PL0].setrecordFile(path, FileName);
	players[PL1].setrecordFile(path, FileName);
}

void Game::setMovefiles()
{
	string fileName= playBoard.files.getInputFileName();
	players[PL0].setmovesFile( fileName);
	players[PL1].setmovesFile( fileName);
}

void Game::closeFiles()
{
	players[PL0].closeFile();
	players[PL1].closeFile();
}



void Game::initFileMoves()
{
	players[PL0].getInputFiles(path);
	players[PL1].getInputFiles(path);
}
void Game::checkQuietGame()
{
	quietGame = quietGame && fileBoard && fileMoves;
}

bool Game::CheckFilesExists()
{
	if (playBoard.files.getNumOfInputFiles()>0)
	{ 

	return fileMoves? players[PL0].getNumOfMovesFiles() + players[PL1].getNumOfMovesFiles() > 0 :true;
	}
	return false;
}