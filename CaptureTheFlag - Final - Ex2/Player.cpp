#include "Player.h"


Player::Player(const string& _name, string extion)
{
	name = _name;
	
	
	files.setEndWith(extion);
}

void Player::setKeys(char keyLeft, char keyRight, char keyUp, char keyDown)
{
	dirKeys[LEFT] = keyLeft;
	dirKeys[RIGHT] = keyRight;
	dirKeys[UP] = keyUp;
	dirKeys[DOWN] = keyDown;
}

void Player::changeDir(char keyPressed)
{
	for (const auto& key : dirKeys)
	{
		if (key == keyPressed)
		{
			step.setDirection ( Directions(&key - dirKeys));
			return;
		}
	}
}
void Player::setTool(const Cell& pos, int toolInd, char toolSign)
{
	this->tools[toolInd].setUsedCell(pos);
	this->tools[toolInd].setSign(toolSign);
	this->tools[toolInd].setActive(true);
}

void  Player::getInputFiles(string path)
{
	files.setPath(path);
	files.getInputFiles();
	
}

int Player::getNumOfMovesFiles()
{
	return files.getNumOfInputFiles();
}


void  Player::setmovesFile(string FileName)
{
	//open file and check if exists
	bool fileExists = files.openInputFile(FileName);
	
	//if file not exists - set attr 
	if (!fileExists)
	{
		step.setlastline(true);
		step.CheckValidMove(false);
		step.setCycle(-1);
		nextStep.setCycle(-1);
		return;
	}
	//get next line
	setNextMove();
	//check more line exists
	if (nextStep.getlastline())
	{
		return;
	}
	// read secend row ;
	stepToNextStep();
}
void Player::setrecordFile(string path , string FileName)
{
	files.setPath(path);
	files.setrecordFile(FileName);
	
}

//set the step that need to be done ; 

bool Player::checkNextMove(int cycle)
{
	//if next step - is in the cycle 
	if (nextStep.checkNextMove(cycle))
	{
		//change next step to step , and get the next step from file
		stepToNextStep();
		return true;
	}
	//if next step is last line and more step - change next step to not valid
	if (nextStep.getlastline() && !step.getLastMoveValid())
	{
		step.setlastline(true);
		return false;
	}
	//check if current step can by excited
	return step.CheckValidMove(cycle);
		

	
	
	
	
}


void Player::stepToNextStep()
{
	// move next step to step 
	step = nextStep;
	
	//if last line stop
	if (step.getlastline())
	{
		return;
	}
	//else get the next liggal step from file;
	setNextMove();
	while (nextStep <= step  && !nextStep.getlastline())
	{
		setNextMove();
	}
	
}


void Player::setNextMove()
{

	//init next step;
	nextStep.setLastMoveValid(false);
	nextStep.setlastline(false);

	while (!nextStep.getLastMoveValid())
	{
		//get line for file;
	string line = files.getNextline();
	//set end of file for next step
	if (files.getendOfFile())
	{
		nextStep.setLastMoveValid(true);
		nextStep.setlastline(true);
		return;
	}
	//if line not empty change next step to step;
	if (line != "")
	{
		//remove spaces
		std::remove(line.begin(), line.end(), ' ');

		nextStep.setNextMove(line);
	}
	
	}
	
	
}

 
void Player::closeFile()
{
	files.closeRecorderFile();
	
}

//recocd move to file;
void Player::recoredMove(int cycle)
{
	char dir = step.getLastMoveValid() ? directionToChar(step.getDirection()) : 'S';
	files.writeLine(to_string (cycle) + "," + tools[step.getSelectedToolInd()].getSign() + "," + dir + "\n");
	
}

//cast enum diraction as char 
char Player::directionToChar(Directions d)
{
	switch (d)
	{
	case UP:
		return 'U';
		break;
	case DOWN:
		return 'D';
		break;
	case LEFT:
		return 'L';
		break;
	case RIGHT:
		return 'R';
		break;

	default:
		break;

		return 'S';
	}
}




