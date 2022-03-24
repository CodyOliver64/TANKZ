#define STATE_MANAGER_CPP
#include <windows.h>											// Header File For Windows
#include <stdio.h>												// Header File For Standard Input / Output
#include <stdarg.h>												// Header File For Variable Argument Routines
#include <math.h>												// Header File For Math Operations
#include <gl\gl.h>											// Header File For The OpenGL32 Library
#include <gl\glu.h>												// Header File For The GLu32 Library
#include "glut.h"
#include <assert.h>
#include "baseTypes.h"
#include "openglframework.h"	
#include "gamedefs.h"
#include "spriteDemoManager.h"
#include "random.h"

#include "soil.h"

SpriteDemoManagerC* SpriteDemoManagerC::sInstance = NULL;


SpriteDemoManagerC* SpriteDemoManagerC::CreateInstance()
{
	if (sInstance != NULL)return sInstance;
	else

		sInstance = new SpriteDemoManagerC();
	return sInstance;
}
void SpriteDemoManagerC::init(int height, int width)
{
	mHeight = height;
	mWidth = width;

	mMoodArray = (int*)malloc(height * width * sizeof(int));
	mPosArrayX = (float*)malloc(height * width * sizeof(float));
	mPosArrayY = (float*)malloc(height * width * sizeof(float));
	mSpriteIDArray = (int*)malloc(height * width * sizeof(int));

	randomizeSprites();


	/* load an image file directly as a new OpenGL texture */
	mSpriteTextureMap = SOIL_load_OGL_texture("snoods_default.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

	mSpriteTextureMapBullets = SOIL_load_OGL_texture("tanks_spritesheetDefault.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);


	mVertexArray = (VertexFormatPos3Tex2*)malloc(height * width * 4 * sizeof(VertexFormatPos3Tex2));
}
void SpriteDemoManagerC::shutdown()
{
	free(mMoodArray);
	free(mPosArrayX);
	free(mPosArrayY);
	free(mSpriteIDArray);
}
void SpriteDemoManagerC::renderSprites()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 1);
#if 1
	glBegin(GL_QUADS);

	// draw player
	GLfloat xPositionLeft = (getXPosition(0, 0) - 32.0f) * 4000.0f / 1024.0f;
	xPositionLeft = xPositionLeft / 2.0f;
	GLfloat xPositionRight = (getXPosition(0, 0) + 32.0f) * 4000.0f / 1024.0f;
	xPositionRight = xPositionRight / 2.0f;

	GLfloat yPositionTop = (getYPosition(0, 0) - 16.0f) * 1600.0f / 168.0f;
	yPositionTop = yPositionTop / 2.0f;
	GLfloat yPositionBottom = (getYPosition(0, 0) + 16.0f) * 1600.0f / 168.0f;
	yPositionBottom = yPositionBottom / 2.0f;

	GLfloat xTextureCoord = getSpriteID(0, 0) * (1.0f / 8.0f);
	GLfloat yTextureCoord = getMood(0, 0) * (1.0f / 4.0f);

	glColor4ub(0xFF, 0xFF, 0xFF, 0xFF);
	glTexCoord2f(xTextureCoord, yTextureCoord);
	glVertex3f(xPositionLeft, yPositionTop, 0.0);
	glTexCoord2f(xTextureCoord + (1.0f / 8.0f), yTextureCoord);
	glVertex3f(xPositionRight, yPositionTop, 0.0);
	glTexCoord2f(xTextureCoord + (1.0 / 8.0f), yTextureCoord + (1.0 / 4.0f));
	glVertex3f(xPositionRight, yPositionBottom, 0.0);
	glTexCoord2f(xTextureCoord, yTextureCoord + (1.0 / 4.0f));
	glVertex3f(xPositionLeft, yPositionBottom, 0.0);
	glEnd();

	


	// draw bullet
	/*glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 2);
	glBegin(GL_QUADS);
	xPositionLeft = (getXPosition(1, 0) - 32.0f) * 15000.0f / 1024.0f;
	xPositionLeft = xPositionLeft / 2.0f;
	xPositionRight = (getXPosition(1, 0) + 32.0f) * 15000.0f / 1024.0f;
	xPositionRight = xPositionRight / 2.0f;

	yPositionTop = (getYPosition(1, 0) - 16.0f) * 4600.0f / 168.0f;
	yPositionTop = yPositionTop / 2.0f;
	yPositionBottom = (getYPosition(1, 0) + 16.0f) * 4600.0f / 168.0f;
	yPositionBottom = yPositionBottom / 2.0f;

	xTextureCoord = getSpriteID(1, 0) * (1.0f / 7.5f);
	yTextureCoord = getMood(1, 0) * (1.0f / 40.0f);

	glColor4ub(0xFF, 0xFF, 0xFF, 0xFF);
	glTexCoord2f(xTextureCoord, yTextureCoord);

	glVertex3f(xPositionLeft, yPositionTop, 0.0);
	glTexCoord2f(xTextureCoord + (1.0f / 15.0f), yTextureCoord);

	glVertex3f(xPositionRight, yPositionTop, 0.0);
	glTexCoord2f(xTextureCoord + (1.0 / 15.0f), yTextureCoord + (1.0 / 6.0f));

	glVertex3f(xPositionRight, yPositionBottom, 0.0);
	glTexCoord2f(xTextureCoord, yTextureCoord + (1.0 / 6.0f));

	glVertex3f(xPositionLeft, yPositionBottom, 0.0);*/

#else
	VertexFormatPos3Tex2* vert = mVertexArray;

	for (int y = 0; y < mHeight; ++y)
	{
		for (int x = 0; x < mWidth; ++x)
		{
			GLfloat xPositionLeft = (getXPosition(x, y) - 32.0f) * 4000.0f / 1024.0f;
			xPositionLeft = xPositionLeft / 2.0f;
			GLfloat xPositionRight = (getXPosition(x, y) + 32.0f) * 4000.0f / 1024.0f;
			xPositionRight = xPositionRight / 2.0f;

			GLfloat yPositionTop = (getYPosition(x, y) - 16.0f) * 1600.0f / 168.0f;
			yPositionTop = yPositionTop / 2.0f;
			GLfloat yPositionBottom = (getYPosition(x, y) + 16.0f) * 1600.0f / 168.0f;
			yPositionBottom = yPositionBottom / 2.0f;

			GLfloat xTextureCoord = getSpriteID(x, y) * (1.0f / 8.0f);
			GLfloat yTextureCoord = getMood(x, y) * (1.0f / 4.0f);

			vert->px = xPositionLeft;
			vert->py = yPositionTop;
			vert->pz = 0.0f;
			vert->tu = xTextureCoord;
			vert->tv = yTextureCoord;
			vert++;

			vert->px = xPositionRight;
			vert->py = yPositionTop;
			vert->pz = 0.0f;
			vert->tu = xTextureCoord + (1.0f / 8.0f);
			vert->tv = yTextureCoord;
			vert++;

			vert->px = xPositionRight;
			vert->py = yPositionBottom;
			vert->pz = 0.0f;
			vert->tu = xTextureCoord + (1.0f / 8.0f);
			vert->tv = yTextureCoord + (1.0f / 4.0f);
			vert++;

			vert->px = xPositionLeft;
			vert->py = yPositionBottom;
			vert->pz = 0.0f;
			vert->tu = xTextureCoord;
			vert->tv = yTextureCoord + (1.0f / 4.0f);
			vert++;
		}
	}

	glColor4ub(0xFF, 0xFF, 0xFF, 0xFF);
	glInterleavedArrays(GL_T2F_V3F, sizeof(VertexFormatPos3Tex2), mVertexArray);
	glDrawArrays(GL_QUADS, 0, 4 * mWidth * mHeight);

#endif
	glEnd();
}




//Basic Sprite Movement
void SpriteDemoManagerC::moveUp(int x, int y)
{


	int offset = y * mWidth + x;
	mPosArrayY[offset]++;
}

void SpriteDemoManagerC::moveDown(int x, int y)
{


	int offset = y * mWidth + x;
	mPosArrayY[offset]--;
}

void SpriteDemoManagerC::moveLeft(int x, int y)
{


	int offset = y * mWidth + x;
	mPosArrayX[offset]--;
}

void SpriteDemoManagerC::moveRight(int x, int y)
{


	int offset = y * mWidth + x;
	mPosArrayX[offset]++;
}







void SpriteDemoManagerC::updateSprites(DWORD milliseconds)
{
	mCurrentTime += milliseconds;

	if (mCurrentTime - mLastUpdateTime > MOOD_UPDATE_DELTA_TIME)
	{
		int numberToUpdate = getRangedRandom((mWidth * mHeight) / 20, ((mWidth * mHeight) / 20) + 20);
		mLastUpdateTime = mCurrentTime;
		for (int i = 0; i < numberToUpdate; ++i)
		{
			int x = getRangedRandom(0, mWidth - 1);
			int y = getRangedRandom(0, mHeight - 1);
			setMood(x, y, getRangedRandom(0, 3));
		}
	}
}
void SpriteDemoManagerC::randomizeSprites()
{
	//set player sprite
	setID(0, 0, 1);  //xTextureCoord
	setMood(0, 0, 0); //yTextureCoord
	float xPos = (float)(0 - mWidth / 2) * 64.0f;
	float yPos = (float)(0 - mHeight / 2) * 32.0f;
	setPosition(0, 0, xPos, yPos);

	//set bullet sprite
	setID(1, 0, 1);  //xTextureCoord
	setMood(1, 0, 1); //yTextureCoord
	xPos = (float)(1 - mWidth / 2) * 64.0f;
	yPos = (float)(1 - mHeight / 2) * 32.0f;
	setPosition(1, 0, xPos, yPos);
}
void SpriteDemoManagerC::setMood(int x, int y, int mood)
{


	int offset = y * mWidth + x;
	mMoodArray[offset] = mood;
}
void SpriteDemoManagerC::setID(int x, int y, int id)
{


	int offset = y * mWidth + x;
	mSpriteIDArray[offset] = id;
}
void SpriteDemoManagerC::setPosition(int x, int y, float xPosition, float yPosition)
{


	int offset = y * mWidth + x;
	mPosArrayX[offset] = xPosition;
	mPosArrayY[offset] = yPosition;
}

float SpriteDemoManagerC::getXPosition(int x, int y)
{


	int offset = y * mWidth + x;

	return mPosArrayX[offset];
}
float SpriteDemoManagerC::getYPosition(int x, int y)
{


	int offset = y * mWidth + x;

	return mPosArrayY[offset];
}
int	SpriteDemoManagerC::getMood(int x, int y)
{


	int offset = y * mWidth + x;

	return mMoodArray[offset];
}
int	SpriteDemoManagerC::getSpriteID(int x, int y)
{


	int offset = y * mWidth + x;

	return mSpriteIDArray[offset];
}