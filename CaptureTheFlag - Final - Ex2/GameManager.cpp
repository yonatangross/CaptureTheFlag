#include "GameManager.h"


char GameManager::mainMenu(bool record)
{
	char userSelection;

	



	clearScreen();
	//gotoxy(x_printing_location, y_printing_location);
	cout << "< 1 > Name the Players\n";
	//gotoxy(x_printing_location, y_printing_location + 1);
	cout << "< 2 > Start the Game\n";
	//gotoxy(x_printing_location, y_printing_location + 2);
	cout << "< 3 > Start the Reversed Game\n";
	//gotoxy(x_printing_location, y_printing_location + 3);
	cout << "< 4 > Reset the Score\n";
	//gotoxy(x_printing_location, y_printing_location + 4);
	
	cout << "< 5 > ";
	if (record)
	{
		cout << "Stop ";
	}
	else
	{
		cout << "Start ";
	}
	cout<< "recording Game \n";
	//gotoxy(x_printing_location, y_printing_location + 4);
	cout << "< 9 > Exit" << endl;
	userSelection = _getch();
	Sleep(200);
	return  userSelection;
}



void GameManager::run(int argc, char *argv[])
{

	commadData(argc, argv);
	
	if (game.getFileMoves() && !game.getFileBoard())
	{
		cout << " can't active moves from file with random board ";
			return; 
	}
	game.checkQuietGame();

	if (game.getFileBoard())
	{
		game.initFileBorad();
	}
	

	if (!game.getQuietGame())
	{
		printPicture();
		printNames();
	}
	
	if (!game.getFileMoves())
	{
		runWithMenu(EMPTY_CHOICE);
	}
	else
	{
		game.initFileMoves();
		while (game.CheckFilesExists())
		{
			if (!game.getQuietGame())
			{
				clearScreen();
			}
			StartTheGame();
			Sleep(50*game.getDiley());
		}
		if (game.getQuietGame())
		{
			game.PrintScoreQuiet();
		}
		quitGame = true;
	}

	
	
	
	
}

void GameManager::runWithMenu( MAIN_MENU runmode)
{
	char userChoice;
	
	
	while (!quitGame)
	{

		if ( game.getFileBoard() && !game.CheckFilesExists())
		{
			clearScreen();
			quitGame = true;
			cout << "No more board files";
		}
		else
		{
			if (runmode == EMPTY_CHOICE)
				userChoice = mainMenu(game.getRecordingGame());
			else
				userChoice = runmode;
			clearScreen();
		}

		if (userChoice == NAMING)
		{
			game.namePlayers();
		}
		else if (userChoice == START_GAME)
		{
			quitGame = StartTheGame();
			
		}
		else if (userChoice == START_REVERSED_GAME)
		{
			reversedGame = true;
			game.printReveresedInstructions();
			quitGame =StartTheGame();
			reversedGame = false;
			
		}
		else if (userChoice == RESET_SCORE)
		{
			game.resetScore();
		}
		else if (userChoice == RECORD_GAME)
		{
			game.setrecordGame();
		}
		else if (userChoice == EXIT)
		{
			quitGame = true;
			cout << "Thank You and Good Bye =]\n";
		}
		else
		{
			clearScreen();
			cout << "incorrect Input, please enter again";
			for (size_t i = 0; i < 3; i++)
			{
				cout << '.';
				Sleep(100);
			}
			cin.clear();
			runmode = EMPTY_CHOICE;
		}
	}
}

bool GameManager::StartTheGame()
{
	
	bool quitGame;
	quitGame = game.run(reversedGame);
	//game.resetBoard();
	
	game.setGameOver(false);
	return quitGame;
}
void GameManager::commadData(int argc, char *argv[])
{
	
	for (size_t i = 1; i < argc;)
	{
		if (strcmp(argv[i], "-board") == 0)
		{
			if (strcmp(argv[i + 1], "f") == 0)
				game.setFileBoardOn();

			i += 2;
			continue;
		}

		if (strcmp(argv[i], "-moves") == 0)
		{
			if (strcmp(argv[i + 1], "f") == 0)
				game.setFileMovesOn();

			i += 2;
			continue;
		}

		if (strcmp(argv[i], "-path") == 0)
		{
			game.setPath(argv[i + 1]);
			i += 2;
			continue;
		}


		if (strcmp(argv[i], "-quiet") == 0)
		{
			game.setQuietGameON();
			++i;
			continue;
		}


		if (strcmp(argv[i], "-delay") == 0)
		{
			game.setDelay(atoi(argv[i ++]));
			continue;
		}
		i++;
	}
}



		



void GameManager::printPicture()
{
	string painting =
		"\n\n\n"
		"                       _____             _                       \n"
		"                      /  __ \\           | |                      \n"
		"                      | /  \\/ __ _ _ __ | |_ _   _ _ __ ___  \n"
		"                      | |    / _` | '_ \\| __| | | | '__/ _ \\ \n"
		"                      | \\__/| (_| | |_) | |_| |_| | | |  __/ \n"
		"                       \\____/\\__,_| .__/ \\__|\\__,_|_|  \\___| \n"
		"                                  | |                            \n"
		"                                  |_|    \n\n\n"


		"                       _   _           ______ _              \n"
		"                      | | | |          |  ___| |             \n"
		"                      | |_| |__   ___  | |_  | | __ _  __ _  \n"
		"                      | __| '_ \\ / _ \\ |  _| | |/ _` |/ _` | \n"
		"                      | |_| | | |  __/ | |   | | (_| | (_| | \n"
		"                       \\__|_| |_|\\___| \\_|   |_|\\__,_|\\__, | \n"
		"                                                       __/ | \n"
		"                                                     |___/  \n";

	cout << painting;
	Sleep(500);
}


void GameManager::printNames()
{
	string names = "By Yoni and Elhanan.";
	gotoxy(Board::SCREEN_WIDTH / 2 + 15, Board::SCREEN_HEIGHT - 3);
	for (size_t i = 0; i < names.length(); i++)
	{
		cout << names[i];
		Sleep(50);
	}
	Sleep(1000);
}
