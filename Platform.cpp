#include "Platform.h"
Platform::Platform(int _x, int _y,const double& interrelation):x(_x),y(_y),width(100*interrelation),height(35*interrelation),mainSprite(createSprite("Utils/data/51-Breakout-Tiles.png"))
{

	
}


Platform::~Platform()
{
	destroySprite(mainSprite);
}
