#pragma once
#include "Block.h"

class Chunk
{
	
	Block** blocks = nullptr;
	
	const int heightAreaWithBlocks;
	Sprite* chunk_sprite;
	Sprite* pinkSpr; 
	Sprite* blockSpr; 

public:
	int CounterForBlocks;
	const int width;
	const int height;
	int x = 0;
	int y = 0;
	int retreat = 0;
	Chunk(int _x, int _y,const int& _retreat,int _width,int _height,int heightAreaWithBlocks,Sprite* pinkSpr,Sprite* blockSpr,Sprite* chunkSpr);
	Chunk(int _x, int _y, int _width, int _height);
	~Chunk();
	std::forward_list<Block*> spawn() ;
	void showObjects();
	void showTest();
	void intersect(Ball* ball);
	operator bool() const;
};


