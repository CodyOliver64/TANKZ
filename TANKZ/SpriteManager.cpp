#include "SpriteManager.h"
#include "openGLFramework.h"
#include "PlayerManager.h"
#include "openGLStuff.h"
#include <malloc.h>
#include <windows.h>
#include<assert.h>

SpriteManager* SpriteManager::sInstance = nullptr;

SpriteManager* SpriteManager::createInstance()
{
	if (sInstance == nullptr)
	{
		sInstance = new SpriteManager();
	}
	return sInstance;
}

SpriteManager* SpriteManager::getInstance()
{
	return sInstance;
}

void SpriteManager::updateSpriteManager(DWORD milliseconds)
{
	//Update movement timers for both Players
	mCurrentTime[0] += milliseconds;
	mCurrentTime[1] += milliseconds;

	if (animationActive[0])
	{
		animateSprite(0);
	}
	if (animationActive[1])
	{
		animateSprite(1);
	}
}

void SpriteManager::init()
{
	// Allocate memory for all the sprites
	spritePtrs = (Sprite**)malloc(NUM_SPRITES * sizeof(Sprite*));


	//Display loading screen while creating sprites
	spritePtrs[SpriteName::LOADING] = new Sprite(-515, -400, 1024, 800, "Sprites/SmallLoad.png", 4);
	spritePtrs[SpriteName::LOADING]->init();
	startOpenGLDrawing();
	spritePtrs[SpriteName::LOADING]->render();
	SwapBuffers(g_window->hDC);


	// Generate all sprites for the game
	initBackgroundSpritePtrs();
	initPlayerSpritePtrs();
	initBulletSpritePtrs();
	initIndicatorSpritePtrs();
	initBlockSpritePtrs();
	initLivesSpritePtrs();
	initGameDisplay();
	initExplosionSpritePtrs();

	// Initialize all object sprites
	for (int i = 0; i < NUM_SPRITES - 6; i++) 
	{
		spritePtrs[i]->init();
	}

	// Initialize sprite rotations
	spritePtrs[SpriteName::INDICATOR_A]->setRotation(-90.0f);
	spritePtrs[SpriteName::INDICATOR_B]->setRotation(-90.0f);
}

void SpriteManager::initBackgroundSpritePtrs()
{
	spritePtrs[SpriteName::BACKGROUND] = new Sprite(-510, -380, 1024, 780, "Sprites/bg_glitchGarden-1920x1080.jpg", 0);
	
}

void SpriteManager::initPlayerSpritePtrs()
{
	// Initialize Player 1
	spritePtrs[SpriteName::PLANE_A_1] = new Sprite(0, 0, 50, 50, "Sprites/P1BaseRedTank.png", 1);
	
	// Initialize Player 2
	spritePtrs[SpriteName::PLANE_B_1] = new Sprite(100, 100, 50, 50, "Sprites/P2 BlueTank.png", 1);
}

void SpriteManager::initBulletSpritePtrs()
{
	// Initialize bullets for turret A
	for (uint8_t i = SpriteName::BULLET_A_1; i <= SpriteName::BULLET_A_3; i++)
	{
		spritePtrs[i] = new Sprite(25, 25, 25, 25, "Sprites/LivesA.png", 2);
	}
	// Initialize bullets for turret B
	for (uint8_t i = SpriteName::BULLET_B_1; i <= SpriteName::BULLET_B_3; i++)
	{
		spritePtrs[i] = new Sprite(890, 47, 25, 25, "Sprites/LivesB.png", 2);
	}
}

void SpriteManager::initIndicatorSpritePtrs()
{
	// Initialize Player 1
	spritePtrs[SpriteName::INDICATOR_A] = new Sprite(-396, 23, 50, 65, "Sprites/TurretP1.png", 1);



	// Initialize Player 2
	spritePtrs[SpriteName::INDICATOR_B] = new Sprite(354, 23, 50, 65, "Sprites/TurretP2.png", 1);
}

void SpriteManager::initBlockSpritePtrs()
{
	// Initialize all Blocks
	for (int i = 0; i < numBlocks; i++) {
		spritePtrs[SpriteName::BLOCK_1 + i] = new Sprite(150, 150, 50, 50, "Sprites/tanks_crateWood.png", 1);
	}
}

void SpriteManager::initExplosionSpritePtrs()
{
	
	spritePtrs[SpriteName::EXPLOSION_A_1] = new Sprite(0, 0, 50, 50, "Sprites/PNG/Default size/tank_explosion2.png", 1);
	spritePtrs[SpriteName::EXPLOSION_A_2] = new Sprite(0, 0, 50, 50, "Sprites/PNG/Default size/tank_explosion3.png", 1);
	spritePtrs[SpriteName::EXPLOSION_A_3] = new Sprite(0, 0, 50, 50, "Sprites/PNG/Default size/tank_explosion4.png", 1);

	spritePtrs[SpriteName::EXPLOSION_A_1]->disableSprite();
	spritePtrs[SpriteName::EXPLOSION_A_2]->disableSprite();
	spritePtrs[SpriteName::EXPLOSION_A_3]->disableSprite();

	spritePtrs[SpriteName::EXPLOSION_B_1] = new Sprite(0, 0, 50, 50, "Sprites/PNG/Default size/tank_explosion2.png", 1);
	spritePtrs[SpriteName::EXPLOSION_B_2] = new Sprite(0, 0, 50, 50, "Sprites/PNG/Default size/tank_explosion3.png", 1);
	spritePtrs[SpriteName::EXPLOSION_B_3] = new Sprite(0, 0, 50, 50, "Sprites/PNG/Default size/tank_explosion4.png", 1);

	spritePtrs[SpriteName::EXPLOSION_B_1]->disableSprite();
	spritePtrs[SpriteName::EXPLOSION_B_2]->disableSprite();
	spritePtrs[SpriteName::EXPLOSION_B_3]->disableSprite();

}

void SpriteManager::initLivesSpritePtrs()
{

	spritePtrs[SpriteName::LIFE_A_1] = new Sprite(-445, 345, 45, 45, "Sprites/LivesA.png", 3);
	spritePtrs[SpriteName::LIFE_A_2] = new Sprite(-395, 345, 45, 45, "Sprites/LivesA.png", 3);
	spritePtrs[SpriteName::LIFE_A_3] = new Sprite(-345, 345, 45, 45, "Sprites/LivesA.png", 3);

	spritePtrs[SpriteName::LIFE_B_1] = new Sprite(505, 345, 45, 45, "Sprites/LivesB.png", 3);
	spritePtrs[SpriteName::LIFE_B_2] = new Sprite(455, 345, 45, 45, "Sprites/LivesB.png", 3);
	spritePtrs[SpriteName::LIFE_B_3] = new Sprite(405, 345, 45, 45, "Sprites/LivesB.png", 3);
}

void SpriteManager::initGameDisplay()
{
	spritePtrs[SpriteName::GAME_END_1] = new Sprite(-515, -400, 1024, 800, "Sprites/Player Two Wins.png", 4);
	spritePtrs[SpriteName::GAME_END_2] = new Sprite(-515, -400, 1024, 800, "Sprites/Player One Wins.png", 4);

	spritePtrs[SpriteName::START_SCREEN] = new Sprite(-515, -400, 1024, 800, "Sprites/TitleScreen.png", 4);
}

void SpriteManager::update(DWORD milliseconds)
{
	currentFrameTime = milliseconds;
	for (uint8_t i = 0; i < NUM_SPRITES; i++)
	{
		spritePtrs[i]->updateSprite(milliseconds);
	}
}

void SpriteManager::renderSprites()
{
		//Render action if game is in play
		if (renderFlag == -1)
		{
			//Render gameObjects
			spritePtrs[SpriteName::BACKGROUND]->render();
			spritePtrs[SpriteName::BULLET_A_1]->render();
			spritePtrs[SpriteName::BULLET_A_2]->render();
			spritePtrs[SpriteName::BULLET_A_3]->render();
			spritePtrs[SpriteName::BULLET_B_1]->render();
			spritePtrs[SpriteName::BULLET_B_2]->render();
			spritePtrs[SpriteName::BULLET_B_3]->render();
			spritePtrs[SpriteName::PLANE_A_1]->render();
			spritePtrs[SpriteName::PLANE_B_1]->render();
			spritePtrs[SpriteName::INDICATOR_A]->render();
			spritePtrs[SpriteName::INDICATOR_B]->render();
			spritePtrs[SpriteName::EXPLOSION_A_1]->render();
			spritePtrs[SpriteName::EXPLOSION_A_2]->render();
			spritePtrs[SpriteName::EXPLOSION_A_3]->render();
			spritePtrs[SpriteName::EXPLOSION_B_1]->render();
			spritePtrs[SpriteName::EXPLOSION_B_2]->render();
			spritePtrs[SpriteName::EXPLOSION_B_3]->render();

			//Render arena
			for (int i = 0; i < numBlocks; i++) {
				spritePtrs[SpriteName::BLOCK_1 + i]->render();
			}

			//Render health UI
			PlayerManagerC* player = PlayerManagerC::GetInstance();
			for (int i = 0; i < 3; i++)
			{
				if (i < player->playerHealth[0])
				{
					spritePtrs[SpriteName::LIFE_A_1 + i]->render();
				}
			}
			for (int i = 0; i < 3; i++)
			{
				if (i < player->playerHealth[1])
				{
					spritePtrs[SpriteName::LIFE_B_1 + i]->render();
				}
			}
		}
		
		//Render action if player 1 wins
		else if (renderFlag == 0)
		{
			spritePtrs[SpriteName::GAME_END_1]->render();
		}

		//Render action if player 2 wins
		else if (renderFlag == 1)
		{
			spritePtrs[SpriteName::GAME_END_2]->render();
		}

		//Render action game has not started yet
		else if (renderFlag == 2)
		{
			spritePtrs[SpriteName::START_SCREEN]->render();
		}
}

void SpriteManager::shutDown()
{
	for (uint8_t i = 0; i < NUM_SPRITES; i++)
	{
		delete spritePtrs[i];
	}
	free(spritePtrs);
}

Sprite** SpriteManager::getSpritePtrs()
{
	return spritePtrs;
}

int32_t SpriteManager::getNumberOfSprites()
{
	return NUM_SPRITES;
}

void SpriteManager::animateSprite(int player)
{
	if (mCurrentTime[player] - mLastUpdateTime[player] > 150)
	{

		//check if our last frame has played and reset animation
		if (currentAnimFrame[player] == 3)
		{
			spritePtrs[(SpriteName::EXPLOSION_A_3 + (3 * player))]->disableSprite();
			currentAnimFrame[player] = 0;
			animationActive[player] = false;
			return;
		}

		//animate sprite to next frame based on player passed
		if (currentAnimFrame[player] != 0)
		{
			spritePtrs[(SpriteName::EXPLOSION_A_1 - 1 + (3 * player)) + currentAnimFrame[player]]->disableSprite();
		}
		spritePtrs[(SpriteName::EXPLOSION_A_1 + (3 * player)) + currentAnimFrame[player]]->enableSprite();
		currentAnimFrame[player]++;


		mLastUpdateTime[player] = mCurrentTime[player];
	}

}