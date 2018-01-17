#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include "Board.h"
#include "Player.h"
#include "FileUtils.h"
#define boradFileExtension   "gboard"
#define PL0FileExtension  "moves-a_small"
#define PL1FileExtension   "moves-b_small"
class Game
{
	enum WINNING_REASON { OUT_OF_TOOLS, FLAG };
	

public:
	enum SIDE_MENU { CONTINUE = '1', RESTART = '2', MAIN_MENU = '8', QUIT = '9' };
	enum { PL0, PL1, NUM_OF_PLAYERS, ESC = 27 };
	enum playerNames { NONE = -1, A = 0, B = 1 };
	Game()
	{				//	left,right, up, down
		players[PL0].setKeys('a', 'd', 'w', 'x');
		players[PL1].setKeys('j', 'l', 'i', 'm');
		
	}
	// Getters / Setters

	bool getFileBoard() { return fileBoard;}
	void setFileBoardOn() { fileBoard = true;}

	bool getFileMoves() { return fileMoves;}
	void setFileMovesOn() { fileMoves = true; }

	bool getQuietGame () { return quietGame; }
	void setQuietGameON() { quietGame = true; }
	void checkQuietGame();
	int getDiley() { return delay; }
	void setDelay(int newDelay) { delay = newDelay; }
	void setPath(char* newPath) {strcpy_s(path,100, newPath);}
	char* getPath(){ return path; }

	void stopLastTool(int playerIndex);
	void setToolToPlayer(Cell toolPostions[2][3]);
	void setGameOver(bool gameOver) { this->gameOver = gameOver; }
	bool getRecordingGame() { return recordingGame; }
	
	// Input Interpretation
	bool run(bool Reversed);
	void getInput(char& keyPressed, bool &quitGame);
	void handleSideMenu(bool& quitGame);
	static void reguliseInput(char &keyPressed);
	void characterizeKey(char keyPressed);
	void readTool(char keyPressed, int playerIndex);
	static int getToolInd(char keyPressed, int playerIndex);
	void moveHandler(char keyPressed, int playerIndex);

	// Move
	
	bool playTheGame();
	void executeStep(int playerIndex);
	Cell getFutureCell(const Cell& currentCell, Directions direction);
	static bool isValidMove(const Cell& currentCell, Directions direction);
	void handleJunction(int playerIndex, const Cell& currentCell, const Cell& futureCell, int toolInd);
	bool validField(int playerIndex, int toolInd, int otherToolInd) const;
	bool handleFlags(int playerIndex, char futureCellChar);
	void moveTool(int playerIndex, const Cell& currCell, const Cell& futureCell, int toolInd);
	static bool handleForest(char toolChar);
	static bool handleSea(char toolChar);
	static bool isMyTool(int playerIndex, char currCellChar, char futureCellChar);

	//Combat
	void handleCombat(int playerIndex, const Cell& currCell, const Cell& futureCell, int toolInd, int otherToolInd);
	//void checkFirstPlayerWin(const Cell & futureCell, bool & win, int toolInd, int otherToolInd);
	static void checkFirstPlayerWin(const Cell& futureCell, bool& win, int toolInd , int otherToolInd);
	static void checkSecondPlayerWin(const Cell& futureCell, bool& win, int toolInd, int otherToolInd);
	void updateWinningCombat(int playerIndex, const Cell& currCell, const Cell& futureCell, int toolInd, int otherToolInd);
	void updateLosingCombat(int playerIndex, const Cell& currCell, int toolInd);
	void checkNoToolsWin(int playerIndex, bool combatWin);
	
	// Initialization
	void resetBoard() { playBoard.resetBoard(); }
	
	void namePlayers();
	void initFileMoves();
	void setrecordGame() { recordingGame = !recordingGame; }

	// Printing
	static void printSideMenu();
	static void printHeader();
	void printScore() const;
	void PrintScoreQuiet();
	void printWinningQuietMessage(string winningPlayerName);
	void printWinningMessage(int winningPlayerIndex, int losingPlayerIndex, WINNING_REASON winningReason) const;
	void printReveresedInstructions() const;

	// Score
	void resetScore();
	void handleWinner(int winningPlayerIndex, int losingPlayerIndex, WINNING_REASON winningReason);


	//open and close files;
	void initFileBorad();
	void initRecordingfiles();
	bool CheckFilesExists();
	void closeFiles();
	void setMovefiles();
	
	

private:
	bool reversedGame = false;
	bool gameOver = false;
	bool recordingGame = false;
	int cycle = 0; //count game turns
	int GameRound = 0; //count number of games
	bool fileBoard = false; // default: random board
	bool fileMoves = false; // default: Keyboard
	bool quietGame = false; // relevant onley with fileBoard and fileMoves

	char path[100]; //path




	int delay = 20; //irrelevant on quiet game.

	Board playBoard;
	Player players[NUM_OF_PLAYERS] = { { "A" ,PL0FileExtension },{ "B",PL1FileExtension } };
};

