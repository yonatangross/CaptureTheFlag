#include "GameManager.h"
#include "Utils.h"


int main()
{
	GameManager  gameManager;

	hideCursor();
	gameManager.run(GameManager::EMPTY_CHOICE); 
}

