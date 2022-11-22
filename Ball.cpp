#include "Ball.h"

Ball::Ball(int _x, int _y, int _lengthOfSide) :x(_x), y(_y), lengthOfSide(_lengthOfSide), untied(false),startSpeedX(1),startSpeedY(1),velocityX(1),velocityY(1),mainSprite(createSprite("Utils/data/63-Breakout-Tiles.png"))
{
	bonus = new Bonus * [14];
	for (int i = 0; i < 14; ++i) {
		bonus[i] = nullptr;
	}
}

Ball::~Ball()
{
	destroySprite(mainSprite);
	for (int i = 0; i < 14; ++i) {
		if (bonus[i] != nullptr) {
			delete bonus[i];
		}
	}
	delete[] bonus;
}

void Ball::findCenter()
{
	centerX=x + lengthOfSide / 2;
	centerY=y + lengthOfSide / 2;
}

Ball::operator Sprite* () const
{
	return mainSprite;
}
