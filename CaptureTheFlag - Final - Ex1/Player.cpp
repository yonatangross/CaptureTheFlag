#include "Player.h"


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
			direction = Directions(&key - dirKeys);
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

