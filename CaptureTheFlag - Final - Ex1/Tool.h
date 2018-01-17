#pragma once
#include "Cell.h"

class Tool
{
	char sign;
	Cell usedCell; //last cell's properties. 
	bool active;
public:
	Tool() :  sign(' '),
			  active(true)
	{}

	// Getters / Setters
	char getSign() const { return sign; }
	void setSign(char sign) { this->sign = sign; }
	bool getActive() const{return active;}
	void setActive(bool active){this->active = active;}
	Cell getUsedCell() const { return usedCell; }
	void setUsedCell(Cell usedCell) { this->usedCell = usedCell; }

};

