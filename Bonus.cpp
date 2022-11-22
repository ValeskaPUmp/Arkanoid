#include "Bonus.h"

Bonus::Bonus(int _x, int _y, bool _isIncreasing):x(_x),y(_y),isIncreasing(_isIncreasing)
{
	mainSprite=_isIncreasing? createSprite("Utils/data/42-Breakout-Tiles.png"):createSprite("Utils/data/41-Breakout-Tiles.png");

	
}

Bonus::~Bonus()
{
	destroySprite(mainSprite);
	
}

void Bonus::spawnBonus(int _width, int _height)
{
	setSpriteSize(mainSprite, _width, _height);
	width = _width;
	height = _height;
}
