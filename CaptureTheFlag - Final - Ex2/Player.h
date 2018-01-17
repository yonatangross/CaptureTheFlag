#pragma once


#include <string>
#include "Tool.h"
#include "Utils.h"
#include "FileHandler.h"
#include <iostream>
#include <fstream>
#include "FileUtils.h"
#include <algorithm>
#include <cstdint>
#include <cassert>
#include "Step.h"

using namespace std;
class Player
{

public:
	enum Tools { FIRST, SECOND, THIRD, NUM_OF_TOOLS };
	
	// CTOR / DTOR
	Player::Player(const string& _name,  string extion);

	// Getters / Setters
	void setTool(const Cell& pos, int toolInd, char toolSign);
	void setKeys(char keyLeft, char keyRight, char keyUp, char keyDown);
	int getScore() const { return score; }
	void setScore(int score) { this->score = score; }
	string getName() const { return name; }
	
	void setName(const string& name) { this->name = name; }
	
	int getSelectToolInd() { return step.getSelectedToolInd(); }
	// Directions
	void changeDir(char keyPressed);

	// Tools Getters / Setters
	char getToolSign(int toolInd) const { return tools[toolInd].getSign(); } // sign
	bool getToolState(int toolInd) const { return tools[toolInd].getActive(); } // state
	void setToolState(int toolInd, bool active) { this->tools[toolInd].setActive(active); }
	void setLastMoveValid(bool valid) { step.setLastMoveValid(valid); }
	Directions getDirection() const {return step.getDirection(); }
	bool getLastMoveValid() { return step.getLastMoveValid(); }
	void setSelectedToolInd(int selectedToolInd) { step.setSelectedToolInd(selectedToolInd); }
	int getSelectedToolInd() const { return step.getSelectedToolInd(); } // selected index
	
	void setStepReocrded(bool stepReocrded) { step.setStepReocrded(stepReocrded); }
	bool getStepReocrded() { return step.getStepReocrded(); }

	void stepToNextStep();
	

	bool getLastline() { return step.getlastline(); }
	Cell getToolUsedCell(int toolInd) const { return tools[toolInd].getUsedCell(); } // used cell
	void setToolUsedCell(Cell usedCell, int toolInd) { this->tools[toolInd].setUsedCell(usedCell); } 
	int getNumOfActiveTools()const { return tools[0].getActive() + tools[1].getActive() + tools[2].getActive(); } // num of active tools
	static int getOtherPlayerIndex(int playerIndex) { return  (playerIndex + 1) % 2; }

	//record 
	void recoredMove(int cycle);
	char directionToChar(Directions d);

	void closeFile();
	void setrecordFile(string path, string FileName);
	//move from files
	
	void setmovesFile(string fileName);
	bool checkNextMove(int cycle);
	void setNextMove();
	void getInputFiles(string path);
	int getNumOfMovesFiles();
private:
	
	//playerData
	string name;
	int score = 0;

	//player setting
	char dirKeys[NUM_OF_DIRS];	// the keys for the four possible directions
	Tool tools[NUM_OF_TOOLS];
	
	//step settings
	Step  step;
	Step  nextStep;
	
	FileHandler files;


};

