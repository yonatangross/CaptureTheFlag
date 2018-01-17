#include "Step.h"




//set a line from file to step
void Step::setNextMove(string line)
{
	char * charar = new char[line.size() + 1];

	//for split 
	strcpy(charar, &line[0]);

	char * spltlien = strtok(charar, ",");

	//set the next cycle
	cycle = atoi(spltlien);
	spltlien = strtok(NULL, ",");

	//set the next tool 
	selectedToolInd = atoi(spltlien) % TOOL_BORDER - 1;
	spltlien = strtok(NULL, ",");

	//set next dirction
	direction = CharToDirction(spltlien[0]);

	//check if valid
	lastMoveValid = selectedToolInd < TOOLS_NUMBER && direction < NUM_OF_DIRS;
	delete[] charar;
}


//oprtor to comapre between stpes  - denped on the cycle
bool Step::operator<=(Step other)
{
	return cycle <= other.cycle;
}


//used in setNextMove cast char as dirction 
Directions Step::CharToDirction(char d)
{
	switch (d)
	{
	case 'U':
		return Directions::UP;
		break;
	case 'D':
		return Directions::DOWN;
		break;
	case 'L':
		return Directions::LEFT;
		break;
	case 'R':
		return Directions::RIGHT;
		break;
	case 'S':
		return Directions::STOP;
		break;
		
	default:
		return Directions::NUM_OF_DIRS;
	}
}

// check if the game cycle is in cycle , if so move the nextStep to step 
bool Step::checkNextMove(int gameCycle)
{
	
 		return (gameCycle == cycle );


}

//check that game cycle is less then cycle , if so excute the step
bool Step::CheckValidMove(int gameCycle)
{
	
	return (gameCycle >= cycle && lastMoveValid);
}
