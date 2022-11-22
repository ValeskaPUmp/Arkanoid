#include "MyFramework.h"


void MyFramework::PreInit(int& width, int& height, bool& fullscreen)
{
	width = 1920;
	height = 1080;
	window_width = width;
	window_height = height;
	fullscreen = false;

}

bool MyFramework::Init() 
{
	 blockSprite = createSprite("Utils/data/03-Breakout-Tiles.png");
	pinkSprite = createSprite("Utils/data/05-Breakout-Tiles.png");
	chunkSprite = createSprite("Utils/data/30-Breakout-Tiles.png");
	gameOver=createSprite("Utils/data/gameoverjpg.jpg");
	setSpriteSize(gameOver, window_width, window_height);
	AllPinkBlocks = new std::forward_list<Block*>;
	background = createSprite("Utils/data/background-2.jpg");
	setSpriteSize(background, window_width,window_height);
	double interrelation = sqrt((window_width * window_height) / (800 * 600));
	squareInterrelation = interrelation;
	int sideRetreat =25*interrelation ;
	int upperRetreat = 100*interrelation;
	int defaultChunkWidth = (window_width - 2 * sideRetreat) / 6;
	int defaultChunkHeight = (upperRetreat+45 * interrelation);
	const double amountOfChunks = (static_cast<int>((window_height / defaultChunkHeight)) * 6);
	std::cout << amountOfChunks;
	amountChunks = amountOfChunks;
	const int filledChunks = 12;
	setSpriteSize(chunkSprite, defaultChunkWidth, defaultChunkHeight);
	setSpriteSize(blockSprite, defaultChunkWidth / 3, (defaultChunkHeight - upperRetreat) / 3);
	setSpriteSize(pinkSprite, defaultChunkWidth / 3, (defaultChunkHeight - upperRetreat) / 3);
	chunks = new Chunk * [amountOfChunks];
 	chunks[0] = new Chunk(sideRetreat, 0, upperRetreat, defaultChunkWidth, defaultChunkHeight, defaultChunkHeight - upperRetreat,pinkSprite,blockSprite,chunkSprite);
	std::forward_list<Block*> pinkBlockinFirstChunk=chunks[0]->spawn();
	AllPinkBlocks->push_front(pinkBlockinFirstChunk.front());
	pinkBlockinFirstChunk.pop_front();
	AllPinkBlocks->splice_after(AllPinkBlocks->begin(), pinkBlockinFirstChunk, pinkBlockinFirstChunk.before_begin(), pinkBlockinFirstChunk.end());
	for (int k = 1; k < amountOfChunks; ++k) {
		if (!(k % 6)) {
			if (k < filledChunks) {
				chunks[k] = new Chunk(chunks[k-6]->x , chunks[k-1]->y+defaultChunkHeight-1*interrelation, 0, defaultChunkWidth, defaultChunkHeight, defaultChunkHeight - upperRetreat, pinkSprite, blockSprite, chunkSprite);
				std::forward_list<Block*> pinkBlocksinCurrentChunk = chunks[k]->spawn();
				AllPinkBlocks->splice_after(AllPinkBlocks->begin(), pinkBlocksinCurrentChunk, pinkBlocksinCurrentChunk.before_begin(), pinkBlocksinCurrentChunk.end());
				continue;
			}
			chunks[k] = new Chunk(chunks[k - 6]->x, chunks[k - 1]->y + defaultChunkHeight-1*interrelation, defaultChunkWidth, defaultChunkHeight);
			continue;
		}
		if (k < filledChunks) {
			
			chunks[k] = new Chunk(chunks[k - 1]->x+defaultChunkWidth-2*interrelation, chunks[k - 1]->y , k<6?upperRetreat:0, defaultChunkWidth, defaultChunkHeight, defaultChunkHeight - upperRetreat,  pinkSprite, blockSprite, chunkSprite);
			std::forward_list<Block*> pinkBlocksinCurrentChunk = chunks[k]->spawn();
			AllPinkBlocks->splice_after(AllPinkBlocks->begin(), pinkBlocksinCurrentChunk, pinkBlocksinCurrentChunk.before_begin(), pinkBlocksinCurrentChunk.end());
			continue;
		}
		chunks[k] = new Chunk(chunks[k - 1]->x + defaultChunkWidth-2*interrelation, chunks[k - 1]->y, defaultChunkWidth, defaultChunkHeight);
	}
	platform = new Platform(window_width / 2-50*interrelation,chunks[amountChunks-1]->y+defaultChunkHeight-35*interrelation, interrelation);
	setSpriteSize(platform->mainSprite, 100 * interrelation, 35 * interrelation);
	ball = new Ball(platform->x+platform->width/2-12*interrelation/2,platform->y-12*interrelation, 12 * interrelation);
	setSpriteSize(ball->mainSprite, 12 * interrelation, 12 * interrelation);
	return true;
}

void MyFramework::Close()
{
	delete ball;
	destroySprite(background);
	delete platform;
	delete[] chunks;
	delete AllPinkBlocks;
	destroySprite(gameOver);
	
}

bool MyFramework::Tick()
{
	if (gameoverflag) {
		drawSprite(gameOver, 0, 0);
		return false;
	}
	if (restart) {
		restart = false;
		destroySprite(gameOver);
		Init();
		return false;
	}
	++TickCounter;
	ball->findCenter();
	drawSprite(background,0,0);
	int AmountOfBlocks = 0;
	for (int k = 12; k < amountChunks; ++k) {
		//chunks[k]->showTest();
	}
	for (int k = 0; k < 12; ++k) {
		//chunks[k]->showTest();
		chunks[k]->showObjects();

		if (*chunks[k] && ball->x >= chunks[k]->x-10 && ball->x <= chunks[k]->x+chunks[k]->width+10 && ball->y >= chunks[k]->y-10 && ball->y <= chunks[k]->y+chunks[k]->width+10) {
			
			chunks[k]->intersect(ball);
			
			
		}
		AmountOfBlocks += chunks[k]->CounterForBlocks;
	}
	if (AmountOfBlocks == 0 || ball->y > platform->y + platform->height + 10) {
		
		gameoverflag = true;
		delete ball;
		destroySprite(pinkSprite);
		destroySprite(blockSprite);
		destroySprite(chunkSprite);
		destroySprite(background);
		destroySprite(blockSprite);
		delete platform;
		for (int i = 0; i < 12; ++i) {
			if(chunks[i]!=nullptr)delete chunks[i];
			
		}
		delete[] chunks;
		delete AllPinkBlocks;
		return false;
	}
	if (platform->x < ball->x + ball->lengthOfSide && platform->x + platform->width > ball->x
		&& platform->y < ball->y + ball->lengthOfSide && platform->y + platform->height > ball->y) {
		if (ball->y+ball->lengthOfSide / 2 >= platform->y && ball->y + ball->lengthOfSide / 2 <= platform->y + platform->height) {
			ball->velocityX *= -1.;
			if (abs(ball->velocityX * 1.1) <= ball->startSpeedX * 3)ball->velocityX *= 1.1;
		}
		else {
			ball->velocityY *= -1.;
			if(abs(ball->velocityY * (1.1)) <= ball->startSpeedY * 3) ball->velocityY *= 1.1;
		}
		std::cout << ball->velocityX << std::endl;
	}
	for (int i = 0; i < 14; ++i) {
		if (ball->bonus[i] != nullptr) {
			if (ball->bonus[i]->width == 0) ball->bonus[i]->spawnBonus(32 * squareInterrelation, 12 * squareInterrelation);
			ball->bonus[i]->y += 1;
			drawSprite(ball->bonus[i]->mainSprite, ball->bonus[i]->x - ball->bonus[i]->width / 2, ball->bonus[i]->y - ball->bonus[i]->height / 2);
			if (platform->x < ball->bonus[i]->x + ball->bonus[i]->width && platform->x + platform->width >ball->bonus[i]->x
				&& platform->y < ball->bonus[i]->y + ball->bonus[i]->height && platform->y + platform->height > ball->bonus[i]->y) {
				if (ball->bonus[i]->isIncreasing) {
					if (abs(ball->velocityX + 0.3) <= ball->startSpeedX * 3 && abs(ball->velocityY + 0.3) <= ball->startSpeedY * 3) {
						ball->velocityX = ball->velocityX > 0 ? ball->velocityX + 0.3 : ball->velocityX - 0.3;
						ball->velocityY = ball->velocityY > 0 ? ball->velocityY + 0.3 : ball->velocityY - 0.3;
					}
				}
				else {
					
					if (abs(ball->velocityX - 0.3) >= ball->startSpeedX * 0.4 && (abs(ball->velocityY - 0.3) >= ball->startSpeedY * 0.4) ){

						ball->velocityX = ball->velocityX < 0 ? ball->velocityX + 0.3 : ball->velocityX - 0.3;
						ball->velocityY = ball->velocityY > 0 ? ball->velocityY + 0.3 : ball->velocityY - 0.3;
					}
				}
				delete ball->bonus[i];
				ball->bonus[i] = nullptr;
				std::cout << ball->velocityX << std::endl;
			}
		}
	}
	drawSprite(platform->mainSprite, platform->x, platform->y);
	if (ball->x + ball->velocityX > window_width - ball->lengthOfSide ) {
		ball->velocityX *= -1;
	}
	if (ball->x + ball->velocityX <= 0) {
		ball->velocityX *= -1;
	}
	if (ball->y - ball->velocityY <= 0) {
		ball->velocityY *= -1;
	}
	if (ball->untied) {
		ball->y -= ball->velocityY;
		ball->x += ball->velocityX;
	}
	drawSprite(ball->mainSprite, ball->x, ball->y);
	if (TickCounter==flag+5000 ) {//10sec
		std::forward_list<Block*>::iterator i;
		for (i = AllPinkBlocks->begin(); i != AllPinkBlocks->end(); ++i) {
			(*i)->changeSignatureToTransparent();
		}
	}
	if (TickCounter == flag+6500) {//3sec
		flag = TickCounter;
		std::forward_list<Block*>::iterator i;
		for (i = AllPinkBlocks->begin(); i != AllPinkBlocks->end(); ++i) {
			(*i)->returnBlockToNormalState();
		}
	};
	return false;
}

void MyFramework::onMouseMove(int x, int y, int xrelative, int yrelative)
{
	mouseX = x;
	mouseY = y;
	
	
}

void MyFramework::onMouseButtonClick(FRMouseButton button, bool isReleased)
{
	if (button == FRMouseButton::LEFT) {
		if (!isReleased) {
			if (!ball->untied) {
				double distance = sqrt(pow(mouseX - ball->centerX, 2) + pow(ball->centerY - mouseY, 2));
				ball->velocityX *= ((mouseX - ball->x) / distance);
				ball->velocityY *= ((abs(mouseY - ball->y)) / distance);
				ball->untied = true;
			}
		}
	}
	if (button == FRMouseButton::RIGHT) {
		if (!isReleased) {
			if (gameoverflag) {
				gameoverflag = false;
				restart = true;
			}
		}
	}
}

void MyFramework::onKeyPressed(FRKey k)
{
	int platformStep = window_width/12;
	if (k == FRKey::RIGHT) {
		while (platform->x + platformStep > window_width - platform->width) platformStep /= 2;
		platform->x += platformStep;
		if (!ball->untied) ball->x += platformStep;
	}
	if (k == FRKey::LEFT) {
		while (platform->x - platformStep < 0) platformStep /= 2;
		platform->x -= platformStep;
		if (!ball->untied) ball->x -= platformStep;
	}
}

void MyFramework::onKeyReleased(FRKey k)
{
	
}
