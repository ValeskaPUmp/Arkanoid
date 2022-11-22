#pragma once
#include "Bonus.h"

class Ball
{
public:
	double x;
	double y;
	int centerX;
	int centerY;
	bool untied;
	double velocityY;
	double velocityX;
	double startSpeedX;
	double startSpeedY;
	int destroyedBlocks = 0;
	int lengthOfSide;
	Bonus** bonus = nullptr;
	Sprite* mainSprite;
	Ball(int _x, int _y, int _lengthOfSide);
	~Ball();
	void findCenter();
	operator Sprite*() const;
};


