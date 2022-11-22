#pragma once
#include "Platform.h"
 
class Block
{
public:
	const int width;
	const int height;
	int x ;
	int y;
	bool pink;
	Sprite* mainSprite;
	Block(int _x, int _y, int _width, int _height,bool _pink,Sprite* sprite);
	void changeSignatureToTransparent();
	void returnBlockToNormalState();
};


