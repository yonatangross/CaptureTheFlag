#pragma once
#include <iostream>

using namespace std;
class GameManager
{
	bool reversedGame;
	bool quitGame;
public:
	enum MAIN_MENU { NAMING = '1', START_GAME = '2', START_REVERSED_GAME = '3', RESET_SCORE = '4', EXIT = '9', EMPTY_CHOICE = '0' };

	// CTOR
	GameManager() : reversedGame(false),quitGame(false)
	{
	}

	static char mainMenu();
	void run(MAIN_MENU runmode);

	// Printing
	static void printPicture();
	static void printNames();

};

