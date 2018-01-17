#define _CRT_SECURE_NO_WARNINGS
#include "Utils.h"
#include <string>
using namespace std;
class Step
{

	int selectedToolInd = 0; // which tool need use
	Directions direction; // dirction of step
	bool lastMoveValid = false; // if need to countime with the last move
	//moves file
	int cycle = -1; //when the next step should by excute - for files
	bool lastline = false; // is it the last step of the file

	bool stepReocrded = false; //if this move been recorded
public :
	//getters/setters
	int getSelectedToolInd() const { return selectedToolInd; } // selected index
	void setSelectedToolInd(int selectedToolInd) { this->selectedToolInd = selectedToolInd; }
	


	void setLastMoveValid(bool valid) { this->lastMoveValid = valid; }
	bool getLastMoveValid() { return this->lastMoveValid; }

	void setlastline(bool lastline) { this->lastline = lastline; }
	bool getlastline() { return this->lastline; }

	void setStepReocrded(bool stepReocrded) { this->stepReocrded = stepReocrded; }
	bool getStepReocrded() { return this->stepReocrded; }

	Directions getDirection() const { return direction; }
	void setDirection(Directions dir) { direction = dir; }

	void setCycle(int c) { cycle = c; }


	//oprtor to comapre between stpes 
	bool operator <= (Step other);
	
	//set a line from file to step
	void setNextMove(string line);

	//used in setNextMove cast char as dirction 
	Directions CharToDirction(char d);
	
	//check if need to move to next Step
	bool Step::checkNextMove(int cycle);

	//check if the current step is valid - for files
	bool Step::CheckValidMove(int gameCycle);
};