#pragma once
#include <iostream>
#include "Framework.h"
#include <time.h>
#include <stdlib.h>
#include <forward_list>
#include <algorithm>
#include <deque>
class Bonus
{
public:
	int x;
	int y;
	int height = 0;
	int width = 0;
	bool isIncreasing;
	double speed = 0.6;
	Sprite* mainSprite;
	Bonus(int _width,int _height,bool _isIncreasing);
	~Bonus();
	void spawnBonus(int width, int height);

};


