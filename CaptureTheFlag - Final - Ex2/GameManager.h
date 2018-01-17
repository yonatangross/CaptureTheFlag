#pragma once
#include <iostream>

#include <string.h>
#include <algorithm>
#include "Game.h"
#include "Utils.h"
#include <Windows.h>
#include <conio.h>
#include "FileUtils.h"
#include <filesystem>
using namespace std;
class GameManager
{


public:
	enum MAIN_MENU { NAMING = '1', START_GAME = '2', START_REVERSED_GAME = '3', RESET_SCORE = '4',RECORD_GAME='5' ,  EXIT = '9', EMPTY_CHOICE = '0' };

	// CTOR
	GameManager() : reversedGame(false),quitGame(false)
	{
	}

	static char mainMenu(bool record);
	void run(int argc, char *argv[]);
	void runWithMenu( MAIN_MENU runmode);
	void commadData(int argc, char *argv[]);
	bool StartTheGame();
	
	// Printing
	static void printPicture();
	static void printNames();
	
	Game game;
	bool reversedGame;
	bool quitGame;
	int gameRound = 0;
	

};

