#include "GameManager.h"
#include "Utils.h"
#include "FileUtils.h"
#include <Windows.h>
int main(int argc, char *argv[])
{
	GameManager  gameManager;

	hideCursor();
	gameManager.run(argc,argv); 
	
}

