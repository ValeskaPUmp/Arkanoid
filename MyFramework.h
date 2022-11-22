#pragma once

#include "Chunk.h"
class MyFramework:public Framework
{
public:
	Ball* ball = nullptr;
	Sprite* background = nullptr;
	Sprite* blockSprite;
	Sprite* pinkSprite;
	Sprite* chunkSprite;
	Platform* platform = nullptr;
	Chunk** chunks = nullptr;
	Sprite* gameOver =nullptr;
	std::forward_list<Block*>* AllPinkBlocks = nullptr;
	int flag = 0;
	int TickCounter = 0;
	bool restart = false;
	bool gameoverflag = false;
	double squareInterrelation;
	int window_width = 0;
	int mouseX;
	int mouseY;
	int window_height = 0;
	int amountChunks = 0;
	
	virtual void PreInit(int& width, int& height, bool& fullscreen);

	// return : true - ok, false - failed, application will exit
	virtual bool Init();

	virtual void Close();

	// return value: if true will exit the application
	virtual bool Tick();

	// param: xrel, yrel: The relative motion in the X/Y direction 
	// param: x, y : coordinate, relative to window
	virtual void onMouseMove(int x, int y, int xrelative, int yrelative);

	virtual void onMouseButtonClick(FRMouseButton button, bool isReleased);

	virtual void onKeyPressed(FRKey k);

	virtual void onKeyReleased(FRKey k);

	virtual const char* GetTitle() {
		return "Arkanoid";
	};

};



