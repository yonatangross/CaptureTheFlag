#pragma once
#include "Board.h"
#include "Player.h"

class Game
{
	enum WINNING_REASON { OUT_OF_TOOLS, FLAG };
public:
	enum SIDE_MENU { CONTINUE = '1', RESTART = '2', MAIN_MENU = '8', QUIT = '9' };
	enum { PL0, PL1, NUM_OF_PLAYERS, ESC = 27 };

	Game()
	{				//	left,right, up, down
		players[PL0].setKeys('a', 'd', 'w', 'x');
		players[PL1].setKeys('j', 'l', 'i', 'm');
	}
	// Getters / Setters
	void setGameOver(bool gameOver) { this->gameOver = gameOver; }


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
	static void checkFirstPlayerWin(const Cell& futureCell, bool& win, int toolInd);
	static void checkSecondPlayerWin(const Cell& futureCell, bool& win, int toolInd, int otherToolInd);
	void updateWinningCombat(int playerIndex, const Cell& currCell, const Cell& futureCell, int toolInd, int otherToolInd);
	void updateLosingCombat(int playerIndex, const Cell& currCell, int toolInd);
	void checkNoToolsWin(int playerIndex, bool combatWin);
	
	// Initialization
	void resetBoard() { playBoard.resetBoard(); }
	Cell findAndSetTool(int minLine, int maxLine, char toolSign);
	void randomizeTools();
	void namePlayers();

	// Printing
	static void printSideMenu();
	static void printHeader();
	void printScore() const;
	void printWinningMessage(int winningPlayerIndex, int losingPlayerIndex, WINNING_REASON winningReason) const;
	void printReveresedInstructions() const;

	// Score
	void resetScore();
	void handleWinner(int winningPlayerIndex, int losingPlayerIndex, WINNING_REASON winningReason);

private:
	bool reversedGame = false;
	bool gameOver = false;
	Board playBoard;
	Player players[NUM_OF_PLAYERS] = { { "A",DOWN },{ "B",UP } };
};

