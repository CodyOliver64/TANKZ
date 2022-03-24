#define GAME_CPP
#include <windows.h>											// Header File For Windows
#include <stdio.h>												// Header File For Standard Input / Output
#include <stdarg.h>												// Header File For Variable Argument Routines
#include <math.h>												// Header File For Math Operations
#include <gl\gl.h>												// Header File For The OpenGL32 Library
#include <gl\glu.h>												// Header File For The GLu32 Library
#include "glut.h"
#include "baseTypes.h"
#include "openglframework.h"	
#include "gamedefs.h"
#include "collInfo.h"
#include "object.h"
#include "random.h"
#include "gameObjects.h"
#include "openGLStuff.h"
#include "game.h"
#include "PlayerManager.h"
#include "SpriteManager.h"
#include "BulletManager.h"
#include "ArenaManager.h"
#include "AudioManager.h"

// Declarations
const char8_t CGame::mGameTitle[] = "TANKZ";
CGame* CGame::sInstance = NULL;
BOOL Initialize(GL_Window* window, Keys* keys)					// Any OpenGL Initialization Goes Here
{
	initOpenGLDrawing(window, keys, 0.0f, 0.0f, 0.0f);
	CGame::CreateInstance();
	CGame::GetInstance()->init();
	return TRUE;
}

void CGame::init()
{
	if (!spritesLoaded)
	{
		SpriteManager::createInstance();
		SpriteManager::getInstance()->init();
		spritesLoaded = true;
	}

	AudioManager::createInstance();
	AudioManager::getInstance()->init();
	AudioManager::getInstance()->playBackground();

	PlayerManagerC::CreateInstance();
	BulletManager::CreateInstance();
	ArenaManager::CreateInstance();

	PlayerManagerC::GetInstance()->init();
	BulletManager::GetInstance()->init();
	ArenaManager::GetInstance()->init();
}
void CGame::UpdateFrame(DWORD milliseconds)
{
	keyProcess();
	BulletManager::GetInstance()->updateBullets(milliseconds);
	PlayerManagerC::GetInstance()->updatePlayerManager(milliseconds);
	SpriteManager::getInstance()->updateSpriteManager(milliseconds);

	timerForRestart -= milliseconds;
}

void CGame::DrawScene(void)
{
	startOpenGLDrawing();
	SpriteManager::getInstance()->renderSprites();
}

CGame* CGame::CreateInstance()
{
	sInstance = new CGame();
	return sInstance;
}
void CGame::shutdown()
{
	AudioManager::getInstance()->shutdown();
}
void CGame::DestroyGame(void)
{
	delete PlayerManagerC::GetInstance();
	delete SpriteManager::getInstance();
	delete BulletManager::GetInstance();
	delete ArenaManager::GetInstance();
	delete AudioManager::getInstance();
}

void CGame::RestartGame()
{
	if (timerForRestart > 0)return;

	shutdown();
	init();
	gameStart = false;
	gameIsOver = false;
	timerForRestart = RESTART_TIME;
	SpriteManager::getInstance()->renderFlag = 2;
}

void CGame::gameOver(int player)
{
	if (!gameIsOver)
	{
		SpriteManager::getInstance()->renderFlag = player;
		gameIsOver = true;
	}
}

void CGame::startGame()
{
	SpriteManager::getInstance()->renderFlag = -1;
	gameStart = true;
}