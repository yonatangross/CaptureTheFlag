#pragma once
#include <string>
#include "Tool.h"
#include "Utils.h"

using namespace std;
class Player
{

public:
	enum Tools { FIRST, SECOND, THIRD, NUM_OF_TOOLS };

	// CTOR / DTOR
	Player(const string& name, Directions direction) :name(name), tools{}, direction(direction){}

	// Getters / Setters
	void setTool(const Cell& pos, int toolInd, char toolSign);
	void setKeys(char keyLeft, char keyRight, char keyUp, char keyDown);
	int getScore() const { return score; }
	void setScore(int score) { this->score = score; }
	string getName() const { return name; }
	Directions getDirection() const { return direction; }
	void setName(const string& name) { this->name = name; }

	// Directions
	void changeDir(char keyPressed);

	// Tools Getters / Setters
	char getToolSign(int toolInd) const { return tools[toolInd].getSign(); } // sign
	bool getToolState(int toolInd) const { return tools[toolInd].getActive(); } // state
	void setToolState(int toolInd, bool active) { this->tools[toolInd].setActive(active); }
	int getSelectedToolInd() const { return selectedToolInd; } // selected index
	void setSelectedToolInd(int selectedToolInd) { this->selectedToolInd = selectedToolInd; }
	Cell getToolUsedCell(int toolInd) const { return tools[toolInd].getUsedCell(); } // used cell
	void setToolUsedCell(Cell usedCell, int toolInd) { this->tools[toolInd].setUsedCell(usedCell); } 
	int getNumOfActiveTools()const { return tools[0].getActive() + tools[1].getActive() + tools[2].getActive(); } // num of active tools
	static int getOtherPlayerIndex(int playerIndex) { return  (playerIndex + 1) % 2; }

private:
	string name;
	int score = 0;
	Tool tools[NUM_OF_TOOLS];
	int selectedToolInd = 0;
	char dirKeys[NUM_OF_DIRS];	// the keys for the four possible directions
	Directions direction;
};

