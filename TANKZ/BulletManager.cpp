#include <assert.h>
#include <windows.h>											// Header File For Windows
#include <stdio.h>												// Header File For Standard Input / Output
#include <stdarg.h>												// Header File For Variable Argument Routines
#include <math.h>												// Header File For Math Operations
#include <gl\gl.h>												// Header File For The OpenGL32 Library
#include <gl\glu.h>												// Header File For The GLu32 Library
#include "glut.h"
#include "baseTypes.h"
#include "ShapeDraw.h"
#include "collInfo.h"
#include "object.h"
#include "BulletManager.h"
#include "ArenaManager.h"
#include "gamedefs.h"
#include "gameobjects.h"
#include "random.h"
#include "SpriteManager.h"
#include "PlayerManager.h"
#include "AudioManager.h"
#include "game.h"
#include <cmath>



BulletManager* BulletManager::sInstance = NULL;


BulletManager* BulletManager::CreateInstance()
{
	if (sInstance == nullptr)
	{
		sInstance = new BulletManager();
	}
	return sInstance;
}


BulletManager::BulletManager()
{
};
BulletManager::~BulletManager()
{
};

void BulletManager::updateBullets(DWORD milliseconds)
{
	int player = 0;

	//Loop through total number of bullets
	for (int i = 0; i < NUM_PLAYER_VECTORS; ++i)
	{
		if (i == 3)
		{
			player = 1;
		}


		//Update inactive bullets as plane moves
		if (bulletActive[i] == 0)
		{
			bulletPosX[i] = PlayerManagerC::GetInstance()->getPlayerXPos(player) + 15;
			bulletPosY[i] = PlayerManagerC::GetInstance()->getPlayerYPos(player) + 12;
			SpriteManager::getInstance()->getSpritePtrs()[2 + i]->setPosition(bulletPosX[i], bulletPosY[i]);
		}
		
		//Update active bullets to move with their current velocity
		else if (bulletActive[i] == 1)
		{
			CollideArena(i, bulletPosX[i] + bulletVelocityX[i], bulletPosY[i] + bulletVelocityY[i]);
			bulletPosX[i] = bulletPosX[i] + bulletVelocityX[i];
			bulletPosY[i] = bulletPosY[i] + bulletVelocityY[i];
			SpriteManager::getInstance()->getSpritePtrs()[2 + i]->setPosition(bulletPosX[i], bulletPosY[i]);
			
		}

		checkCollision();
	}

	//Update shot timers for both Players Ammo
	mCurrentTime[0] += milliseconds;
	mCurrentTime[1] += milliseconds;
}

void BulletManager::fireBullet(int player)
{
	
	if (mCurrentTime[player] - mLastUpdateTime[player] > 1000)
	{
		//Play Fire Sound
		AudioManager::getInstance()->playFiringSound(player);


		//Loop through bullet pool based on player chosen and try to fire the first active bullet found
		for (int i = player * 3; i < 3 * (player + 1); ++i)
		{
			if (bulletActive[i] == 0)
			{
				//Set Velocity based on current cannon rotation
				switch (PlayerManagerC::GetInstance()->getCannonRotation(player))
					{
					case CANNON_RIGHT:
						bulletVelocityX[i] = 5;
						bulletVelocityY[i] = 0;
						break;
					case CANNON_UP_RIGHT:
						bulletVelocityX[i] = 5;
						bulletVelocityY[i] = 5;
						break;
					case CANNON_UP:
						bulletVelocityX[i] = 0;
						bulletVelocityY[i] = 5;
						break;
					case CANNON_UP_LEFT:
						bulletVelocityX[i] = -5;
						bulletVelocityY[i] = 5;
						break;
					case CANNON_LEFT:
						bulletVelocityX[i] = -5;
						bulletVelocityY[i] = 0;
						break;
					case CANNON_DOWN_LEFT:
						bulletVelocityX[i] = -5;
						bulletVelocityY[i] = -5;
						break;
					case CANNON_DOWN:
						bulletVelocityX[i] = 0;
						bulletVelocityY[i] = -5;
						break;
					case CANNON_DOWN_RIGHT:
						bulletVelocityX[i] = 5;
						bulletVelocityY[i] = -5;
						break;
					}

				//Set bullet active
				bulletActive[i] = 1;
				SpriteManager::getInstance()->getSpritePtrs()[2 + i]->enableSprite();

				break;
			}
		}

		//return if all bullets are currently active, update time between shots
		mLastUpdateTime[player] = mCurrentTime[player];
		return;
	}
}

void BulletManager::checkCollision()
{
	//Loop through player 1's active bullets, checking if they are colliding with 2
	int player = 1;
	float playerXPos = PlayerManagerC::GetInstance()->getPlayerXPos(1);
	float playerYPos = PlayerManagerC::GetInstance()->getPlayerYPos(1);

	for (int i = 0; i < NUM_PLAYER_VECTORS; ++i)
	{
		//Switch position check for other players bullets
		if (i == 3)
		{
			player = 0;
			playerXPos = PlayerManagerC::GetInstance()->getPlayerXPos(0);
			playerYPos = PlayerManagerC::GetInstance()->getPlayerYPos(0);
		}

		//Skipp bullet if inactive
		if (bulletActive[i] == 0)
		{
			continue;
		}
		
		// if a bullet collides with a player
		if (playerXPos < (bulletPosX[i] + 25) && (playerXPos + 50) > bulletPosX[i] && playerYPos < (bulletPosY[i] + 25) && (playerYPos + 50) > bulletPosY[i])
		{
			//Play hit sound
			AudioManager::getInstance()->playHitSound(player);

			//Activate hit animation
			SpriteManager::getInstance()->animationActive[player] = true;
			
			resetBullet(i);

			//decrease player health and check for game over
			PlayerManagerC::GetInstance()->playerHealth[player]--;
			if (PlayerManagerC::GetInstance()->playerHealth[player] <= 0)
			{
				AudioManager::getInstance()->stopBackground();
				AudioManager::getInstance()->playWinSound();
				CGame::GetInstance()->gameOver(player);
			}
		}
	}
}

void BulletManager::CollideArena(int bullet, int bulletX, int bulletY)
{
	ArenaManager* arena = ArenaManager::GetInstance();
	Block* blocks = arena->getBlocks();
	bool bounceCheck = 0;
	int bulletLeft = bulletX;
	int bulletRight = bulletLeft + mRadius;
	int bulletTop = bulletY - mRadius;
	int bulletBottom = bulletTop - mRadius;

	for (int j = 0; j < 13; j++)
	{
		Block block = blocks[j];
		if (bulletLeft < block.rightX && bulletRight > block.leftX && bulletTop > block.bottomY && bulletBottom < block.topY)
		{
			AudioManager::getInstance()->playBounceSound();
			bulletBounces[bullet]--;
			if (bulletBounces[bullet] < 0)
			{
				resetBullet(bullet);
				return;
			}
			float dx = 0;
			float dy = 0;
			if (bulletVelocityX[bullet] >= 0) // Bullet approaching from left
			{
				dx = std::abs(block.leftX - bulletRight);
			}
			else // Bullet approaching from right
			{
				dx = std::abs(bulletLeft - block.rightX);
			}
			if (bulletVelocityY[bullet] >= 0) // Bullet approaching from bottom
			{
				dy = std::abs(block.bottomY - bulletTop);
			}
			else // Bullet approaching from top
			{
				dy = std::abs(bulletBottom - block.topY);
			}
			
			if (dx < dy)
			{
				bulletVelocityX[bullet] = -bulletVelocityX[bullet];
			}
			else if (dx == dy) {
				bulletVelocityX[bullet] = -bulletVelocityX[bullet];
				bulletVelocityY[bullet] = -bulletVelocityY[bullet];
			}
			else if (dy < dx) {
				bulletVelocityY[bullet] = -bulletVelocityY[bullet];
			}
			return;
		}
	}
};

void BulletManager::resetBullet(int bullet)
{
	bulletActive[bullet] = 0;
	bulletVelocityX[bullet] = 0;
	bulletVelocityY[bullet] = 0;
	bulletBounces[bullet] = numBounces;
	SpriteManager::getInstance()->getSpritePtrs()[2 + bullet]->disableSprite();

}

void BulletManager::init()
{
	int player = 0;
	//Set Player Bullet Attributes
	for (int i = 0; i < 6; ++i)
	{
		//Set next players bullets after three have been loaded
		if (i == 3)
		{
			player = 1;
		}

		bulletPosX[i] = PlayerManagerC::GetInstance()->getPlayerXPos(player) + 50;
		bulletPosY[i] = PlayerManagerC::GetInstance()->getPlayerYPos(player);
		bulletVelocityX[i] = 0;
		bulletVelocityY[i] = 0;
		bulletBounces[i] = numBounces;
		bulletActive[i] = 0;

		SpriteManager::getInstance()->getSpritePtrs()[2 + i]->setPosition(bulletPosX[i], bulletPosY[i]);
		SpriteManager::getInstance()->getSpritePtrs()[2 + i]->disableSprite();
	}


	mRadius = 25.0;

	mEnabled = true;
}
