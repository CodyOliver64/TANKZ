#include <windows.h>											// Header File For Windows
#include <stdio.h>												// Header File For Standard Input / Output
#include <stdarg.h>												// Header File For Variable Argument Routines
#include <math.h>												// Header File For Math Operations
#include <gl\gl.h>												// Header File For The OpenGL32 Library
#include <gl\glu.h>												// Header File For The GLu32 Library
#include "glut.h"
#include "baseTypes.h"
#include "collInfo.h"
#include "object.h"
#include "field.h"
#include "ShapeDraw.h"

//BlockC::BlockC()
//{
//};
//BlockC::BlockC(float_t x1, float_t y1, float_t x2, float_t y2, char8_t rInput, char8_t gInput, char8_t bInput)
//{
//	leftX = x1;
//	rightX = x2;
//	bottomY = y1;
//	topY = y2;
//	r = rInput;
//	g = gInput;
//	b = bInput;
//};
//BlockC::~BlockC()
//{
//};


void FieldC::moveUp()
{
	int y;
	y=5;
}
FieldC::FieldC(float_t x, float_t y, uint32_t height, uint32_t width, uint32_t initColor)
{
    mEnabled = true;
    mFieldColor = initColor;
	mWidth = width;
	mHeight = height;
	mPosition.x = x;
	mPosition.y = y;

	char8_t r = (char8_t)(mFieldColor >> 16 & 0xFF);
	char8_t g = (char8_t)(mFieldColor >> 8 & 0xFF);
	char8_t b = (char8_t)(mFieldColor >> 0 & 0xFF);
	float_t xScale = 4000.0f / 1024.0f;
	float_t yScale = 4000.0f / 768.0f;
	/*blocks[0] = BlockC(-480, -1180, 480, -1020, r, g, b);
	blocks[1] = BlockC(-480, 1020, 480, 1180, r, g, b);
	blocks[2] = BlockC(860, -700, 1020, 700, r, g, b);
	blocks[3] = BlockC(-1020, -700, -860, 700, r, g, b);
	blocks[4] = BlockC(-1180, 540, -1020,1180, r, g, b);
	blocks[5] = BlockC(-1180, -1180, -1020, -540, r, g, b);
	blocks[6] = BlockC(1020, -1180, 1180, -540, r, g, b);
	blocks[7] = BlockC(1020, 540, 1180, 1180, r, g, b);
	numBlocks = 8;*/
};
FieldC::~FieldC()
{
};
void FieldC::update(DWORD milliseconds)
{
};

void FieldC::render()
{
	float_t left = mPosition.x - (float_t)mWidth/2.0f;
	float_t right = mPosition.x + (float_t)mWidth/2.0f;
	float_t bottom = mPosition.y - (float_t)mHeight/2.0f;
	float_t top = mPosition.y + (float_t)mHeight/2.0f;

	char8_t r = (char8_t)(mFieldColor>>16 & 0xFF);
	char8_t g = (char8_t)(mFieldColor>>8 & 0xFF);
	char8_t b = (char8_t)(mFieldColor>>0 & 0xFF);

	DrawLine(left,top,right,top,r,g,b);
	DrawLine(right,top,right,bottom,r,g,b);
	DrawLine(right,bottom,left,bottom,r,g,b);
	DrawLine(left,bottom,left,top,r,g,b);
	/*for (int i = 0; i < numBlocks; i++)
	{
		DrawRectangle(blocks[i].leftX, blocks[i].bottomY, blocks[i].rightX, blocks[i].topY, blocks[i].r, blocks[i].g, blocks[i].b, 1);
	}*/
};
