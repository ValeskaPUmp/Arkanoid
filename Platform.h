#pragma once
#include "Ball.h"
class Platform
{
public:
	int x;
	int y;
	const int width;
	const int height;
	Sprite* const mainSprite;
	Platform(int _x, int _y,const double& interrelation);
	~Platform();
};


