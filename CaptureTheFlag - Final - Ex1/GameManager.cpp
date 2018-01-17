#include "GameManager.h"
#include "Game.h"
#include "Utils.h"
#include <Windows.h>
#include <conio.h>



char GameManager::mainMenu()
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
	cout << "< 9 > Exit" << endl;
	userSelection = _getch();
	Sleep(200);
	return  userSelection;
}

void GameManager::run(MAIN_MENU runmode)
{
	char userChoice;
	Game game;

	printPicture();
	printNames();

	while (!quitGame)
	{
		if (runmode == EMPTY_CHOICE)
			userChoice = mainMenu();
		else
			userChoice = runmode;
		clearScreen();

		if (userChoice == NAMING)
		{
			game.namePlayers();
		}
		else if (userChoice == START_GAME)
		{
			quitGame = game.run(reversedGame); // quit game or continue
			game.resetBoard();
			game.setGameOver(false);
		}
		else if (userChoice == START_REVERSED_GAME)
		{
			reversedGame = true;
			game.printReveresedInstructions();
			quitGame = game.run(reversedGame); // quit game or continue
			reversedGame = false;
			game.resetBoard();
			game.setGameOver(false);
		}
		else if (userChoice == RESET_SCORE)
		{
			game.resetScore();
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
