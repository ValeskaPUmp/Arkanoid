#include "Block.h"

Block::Block(int _x,  int _y,int _width,int _height, bool _pink,Sprite* sprite):x(_x),y(_y),width(_width),height(_height),pink(_pink),mainSprite(sprite)
{
	

	
}
void Block::returnBlockToNormalState()
{
	y *= -1;
}


void Block::changeSignatureToTransparent()
{
	y *= -1;
}



