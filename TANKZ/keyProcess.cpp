#include <windows.h>													// Header File For The Windows Library
#include <gl/gl.h>														// Header File For The OpenGL32 Library
#include <gl/glu.h>														// Header File For The GLu32 Library
#include "glut.h"
#include "openglframework.h"														// Header File For The NeHeGL Basecode

#include "PlayerManager.h"
#include "BulletManager.h"
#include "baseTypes.h"
#include "game.h"
#include "AudioManager.h"

#define KEY_W 0x57
#define KEY_A 0x41
#define KEY_S 0x53
#define KEY_D 0x44

#define KEY_I 0x49
#define KEY_J 0x4A
#define KEY_K 0x4B
#define KEY_L 0x4C

#define KEY_SPACE 0x20
#define KEY_ENTER 0x0D
#define KEY_NUM_FIVE 0x65

#define KEY_F 0x46
#define KEY_G 0x47
#define KEY_NUM_TWO 0x62
#define KEY_NUM_THREE 0x63

//handles keyboard processing
void keyProcess(void)
{
	if (g_keys->keyDown[VK_ESCAPE])								// Is ESC Being Pressed?
	{
		TerminateApplication(g_window);						// Terminate The Program
	}

	if (CGame::GetInstance()->gameStart)
	{
		//Restart Game
		if (g_keys->keyDown[VK_F1])
		{
			CGame::GetInstance()->RestartGame();
		}


		//Player 1 Fire Button
		if (g_keys->keyDown[KEY_SPACE])
		{
			BulletManager::GetInstance()->fireBullet(0);
		}

		//Player 2 Fire Button
		if (g_keys->keyDown[KEY_NUM_FIVE])
		{
			BulletManager::GetInstance()->fireBullet(1);
		}

		//Player 1 Rotate Buttons
		if (g_keys->keyDown[KEY_F])
		{
			PlayerManagerC::GetInstance()->rotateCannonLeft(0);
		}
		if (g_keys->keyDown[KEY_G])
		{
			PlayerManagerC::GetInstance()->rotateCannonRight(0);
		}
		//Player 2 Rotate Buttons
		if (g_keys->keyDown[KEY_NUM_TWO])
		{
			PlayerManagerC::GetInstance()->rotateCannonLeft(1);
		}
		if (g_keys->keyDown[KEY_NUM_THREE])
		{
			PlayerManagerC::GetInstance()->rotateCannonRight(1);
		}


		//Player 1 - Movement Controls
		if (g_keys->keyDown[KEY_W])
		{
			PlayerManagerC::GetInstance()->moveUp(0);
		}

		if (g_keys->keyDown[KEY_S])
		{
			PlayerManagerC::GetInstance()->moveDown(0);
		}

		if (g_keys->keyDown[KEY_A])
		{
			PlayerManagerC::GetInstance()->moveLeft(0);
		}

		if (g_keys->keyDown[KEY_D])
		{
			PlayerManagerC::GetInstance()->moveRight(0);
		}

		//Player 2 - Movement Controls
		if (g_keys->keyDown[KEY_I])
		{
			PlayerManagerC::GetInstance()->moveUp(1);
		}

		if (g_keys->keyDown[KEY_K])
		{
			PlayerManagerC::GetInstance()->moveDown(1);
		}

		if (g_keys->keyDown[KEY_J])
		{
			PlayerManagerC::GetInstance()->moveLeft(1);
		}

		if (g_keys->keyDown[KEY_L])
		{
			PlayerManagerC::GetInstance()->moveRight(1);
		}
	}
	else
	{
		if (g_keys->keyDown[KEY_ENTER])
		{
			CGame::GetInstance()->startGame();
			AudioManager::getInstance()->playStartSound();
		}
	}


}