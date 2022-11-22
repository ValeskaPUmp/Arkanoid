#include "Chunk.h"

std::forward_list<Block*> Chunk::spawn() 
{
	//if (heightAreaWithBlocks == 0) return;
	blocks = new Block * [9];
	int defaultBlockWidth = (width / 3);
	int defaultBlockHeight = heightAreaWithBlocks / 3;
	std::forward_list<Block*> pinkBlocksInChunk;
	bool pinkBlock = (rand() % 2);
	blocks[0] = new Block(x, y + retreat, defaultBlockWidth, defaultBlockHeight, pinkBlock,pinkBlock?pinkSpr:blockSpr);
	if (pinkBlock)pinkBlocksInChunk.push_front(blocks[0]);
	for (int i = 1; i < CounterForBlocks; ++i) {
		srand(i + (int)blocks[i - 1]);
		bool pinkBlock = (rand() % 2);
		if (!(i % 3)) {
			blocks[i] = new Block(blocks[i - 3]->x, blocks[i - 1]->y + defaultBlockHeight, defaultBlockWidth, defaultBlockHeight, pinkBlock, pinkBlock ? pinkSpr : blockSpr);
			if (pinkBlock) pinkBlocksInChunk.push_front(blocks[i]);
			continue;
		}
		blocks[i] = new Block(blocks[i - 1]->x + defaultBlockWidth, blocks[i - 1]->y, defaultBlockWidth, defaultBlockHeight, pinkBlock, pinkBlock ? pinkSpr : blockSpr);
		if (pinkBlock) pinkBlocksInChunk.push_front(blocks[i]);
	}
	return pinkBlocksInChunk;
}
void Chunk::intersect(Ball* ball)
{
	
	for (int i = 0; i < 9; ++i) {
		if (blocks[i] == nullptr)continue;
		for (int k = 0; k < 14; ++k) {
			if (ball->bonus[k] != nullptr) {
				if (blocks[i]->x <= ball->bonus[k]->x + ball->bonus[k]->width && blocks[i]->x + blocks[i]->width >= ball->bonus[k]->x
						&& blocks[i]->y <= ball->bonus[k]->y + ball->bonus[k]->height && blocks[i]->y + blocks[i]->height >= ball->bonus[k]->y) {
					
				}
				else {
					
				}
					
			}

		}
		
		double distanceX = abs(ball->centerX - blocks[i]->x);
		double distanceY = abs(ball->centerY - blocks[i]->y);
		if (blocks[i]->x <= ball->x + ball->lengthOfSide && blocks[i]->x + blocks[i]->width >= ball->x
			&& blocks[i]->y <= ball->y + ball->lengthOfSide && blocks[i]->y + blocks[i]->height >= ball->y) {
			if (ball->y-ball->lengthOfSide/2>blocks[i]->y && ball->y+ ball->lengthOfSide/2 / 2 <blocks[i]->y+blocks[i]->height) {
				ball->velocityX *= -1;
				if (abs(ball->velocityX * 0.9) >= ball->startSpeedX * 0.4) ball->velocityX *= 0.9;
				std::cout << "x:" << ball->velocityX << '\n';
			}
			else {
				ball->velocityY *= -1;
				if (abs(ball->velocityY * (0.9)) >= ball->startSpeedY * 0.4) ball->velocityY *= 0.9;
				std::cout << "y:" << ball->velocityY << '\n';
			}
			
			++ball->destroyedBlocks;
			--CounterForBlocks;
			//destroySprite(blocks[i]->mainSprite);
			if (ball->destroyedBlocks == 10) {
				ball->destroyedBlocks = 0;
				for (int k = 0; k < 14; ++k) {
					if (ball->bonus[k] == nullptr) {
						ball->bonus[k]=(new Bonus(blocks[i]->x + blocks[i]->width / 2, blocks[i]->y + blocks[i]->height / 2, (rand() % 2)));
						break;
					}
				}
			}
			delete blocks[i];
			blocks[i] = nullptr;
			break;
		}
		
		/*if ((distanceX < ball->lengthOfSide / 2)
			&& distanceY < 0 
			|| (distanceY < ball->lengthOfSide/2) 
			&& distanceX < 0 
			|| ((distanceX *distanceX + distanceY * distanceY) < ((ball->lengthOfSide / 2)*(ball->lengthOfSide)))){
			if (distanceX < distanceY) {
				ball->velocityY *= -1;

			}
			else {
				ball->velocityX *= -1;
			}
			destroySprite(blocks[i]->mainSprite);
			delete blocks[i];
			blocks[i] = nullptr;
			break;
			
		}
		*/
		
		
		
		/*if (distance <= (ball->lengthOfSide / 2) + blocks[i]->height / 2) {
			if (abs(ball->velocityX * 0.9) > ball->startSpeedX * 0.4 ) {
				ball->velocityX *= 0.9;
			}
			if(abs(ball->velocityY * (0.9)) > ball->startSpeedY * 0.4) ball->velocityY *= 0.9;
			ball->velocityY *= -1;
			break;
		}
		if (distance <= ball->lengthOfSide / 2 + sqrt(blocks[i]->width * blocks[i]->width + blocks[i]->height * blocks[i]->height) / 2) {
			if (abs(ball->velocityX * 0.9) > ball->startSpeedX * 0.4) {
				ball->velocityX *= 0.9;
			}
			if (abs(ball->velocityY * (0.9)) > ball->startSpeedY * 0.4) ball->velocityY *= 0.9;
			ball->velocityY *= -1;
			break;
		}
		if (distance <= ball->lengthOfSide / 2 + blocks[i]->width / 2) {
			if (abs(ball->velocityY * 0.9) > ball->startSpeedY * 0.4) {
				ball->velocityX *= 0.9;
			}
			if (abs(ball->velocityX * (0.9)) > ball->startSpeedX * 0.4) {
				ball->velocityY *= 0.9;
			}
			ball->velocityX *= -1;
			break;
		}*/
			
		}
	}

Chunk::operator bool() const
{
	return CounterForBlocks > 0;
}
void Chunk::showObjects()
{
	if (blocks == nullptr) return;
	for (int i = 0; i < 9; ++i) {
		if (blocks[i] == nullptr) continue;
		drawSprite(blocks[i]->mainSprite, blocks[i]->x, blocks[i]->y);
	}
}

void Chunk::showTest()
{ 
	

	drawSprite(chunk_sprite, x, y);
}

Chunk::Chunk(int _x,  int _y,const int& _retreat,int _width,int _height,int _heightAreaWithBlocks,Sprite* pinkSpr, Sprite* blockSpr, Sprite* chunkSpr):x(_x),y(_y),width(_width),heightAreaWithBlocks(_heightAreaWithBlocks),height(_height),retreat(_retreat),CounterForBlocks(9),chunk_sprite(chunkSpr),blockSpr(blockSpr),pinkSpr(pinkSpr)
{
	
	
}

Chunk::Chunk(int _x, int _y, int _width, int _height):x(_x),y(_y),width(_width),height(_height),heightAreaWithBlocks(0)
{
}


Chunk::~Chunk()
{
	std::cout << "destroy"<<'\n';
	for (int i = 0; i < 9; ++i) {
		if (blocks[i] != nullptr) {
			delete blocks[i];
		}
	}
	delete[] blocks;

}
