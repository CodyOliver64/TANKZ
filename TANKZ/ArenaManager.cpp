#include "ArenaManager.h"
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
#include "gamedefs.h"
#include "gameobjects.h"
#include "random.h"
#include "SpriteManager.h"

Block::Block()
{
};
Block::Block(float_t x1, float_t y1, float_t x2, float_t y2)
{
	leftX = x1;
	rightX = x2;
	bottomY = y1;
	topY = y2;
};
Block::~Block()
{
};

ArenaManager* ArenaManager::sInstance = NULL;

ArenaManager* ArenaManager::CreateInstance()
{
	if (sInstance == nullptr)
	{
		sInstance = new ArenaManager();
	}
	return sInstance;
}


ArenaManager::ArenaManager()
{
	//init();
};
ArenaManager::~ArenaManager()
{
};

Block* ArenaManager::getBlocks()
{
	return blocks;
};

void ArenaManager::init()
{
	// Initalize border sprites
	SpriteManager::getInstance()->getSpritePtrs()[10]->setPosition(450, 325); // Top Right Block
	SpriteManager::getInstance()->getSpritePtrs()[11]->setPosition(400, 325); // Begin Top Row
	SpriteManager::getInstance()->getSpritePtrs()[12]->setPosition(350, 325);
	SpriteManager::getInstance()->getSpritePtrs()[13]->setPosition(300, 325);
	SpriteManager::getInstance()->getSpritePtrs()[14]->setPosition(250, 325);
	SpriteManager::getInstance()->getSpritePtrs()[15]->setPosition(200, 325);
	SpriteManager::getInstance()->getSpritePtrs()[16]->setPosition(150, 325);
	SpriteManager::getInstance()->getSpritePtrs()[17]->setPosition(100, 325);
	SpriteManager::getInstance()->getSpritePtrs()[18]->setPosition(50, 325);
	SpriteManager::getInstance()->getSpritePtrs()[19]->setPosition(0, 325);
	SpriteManager::getInstance()->getSpritePtrs()[20]->setPosition(-50, 325);
	SpriteManager::getInstance()->getSpritePtrs()[21]->setPosition(-100, 325);
	SpriteManager::getInstance()->getSpritePtrs()[22]->setPosition(-150, 325);
	SpriteManager::getInstance()->getSpritePtrs()[23]->setPosition(-200, 325);
	SpriteManager::getInstance()->getSpritePtrs()[24]->setPosition(-250, 325);
	SpriteManager::getInstance()->getSpritePtrs()[25]->setPosition(-300, 325);
	SpriteManager::getInstance()->getSpritePtrs()[26]->setPosition(-350, 325);
	SpriteManager::getInstance()->getSpritePtrs()[27]->setPosition(-400, 325);
	SpriteManager::getInstance()->getSpritePtrs()[28]->setPosition(-450, 325);
	SpriteManager::getInstance()->getSpritePtrs()[29]->setPosition(-500, 325); // Top Left Block
	SpriteManager::getInstance()->getSpritePtrs()[30]->setPosition(-500, 275); // Begin Left Column
	SpriteManager::getInstance()->getSpritePtrs()[31]->setPosition(-500, 225);
	SpriteManager::getInstance()->getSpritePtrs()[32]->setPosition(-500, 175);
	SpriteManager::getInstance()->getSpritePtrs()[33]->setPosition(-500, 125);
	SpriteManager::getInstance()->getSpritePtrs()[34]->setPosition(-500, 75);
	SpriteManager::getInstance()->getSpritePtrs()[35]->setPosition(-500, 25);
	SpriteManager::getInstance()->getSpritePtrs()[36]->setPosition(-500, -25);
	SpriteManager::getInstance()->getSpritePtrs()[37]->setPosition(-500, -75);
	SpriteManager::getInstance()->getSpritePtrs()[38]->setPosition(-500, -125);
	SpriteManager::getInstance()->getSpritePtrs()[39]->setPosition(-500, -175);
	SpriteManager::getInstance()->getSpritePtrs()[40]->setPosition(-500, -225);
	SpriteManager::getInstance()->getSpritePtrs()[41]->setPosition(-500, -275);
	SpriteManager::getInstance()->getSpritePtrs()[42]->setPosition(-500, -325);
	SpriteManager::getInstance()->getSpritePtrs()[43]->setPosition(-500, -375); // Bottom Left Block
	SpriteManager::getInstance()->getSpritePtrs()[44]->setPosition(450, -375); // Bottom Right Block
	SpriteManager::getInstance()->getSpritePtrs()[45]->setPosition(400, -375); // Begin Bottom Row
	SpriteManager::getInstance()->getSpritePtrs()[46]->setPosition(350, -375);
	SpriteManager::getInstance()->getSpritePtrs()[47]->setPosition(300, -375);
	SpriteManager::getInstance()->getSpritePtrs()[48]->setPosition(250, -375);
	SpriteManager::getInstance()->getSpritePtrs()[49]->setPosition(200, -375);
	SpriteManager::getInstance()->getSpritePtrs()[50]->setPosition(150, -375);
	SpriteManager::getInstance()->getSpritePtrs()[51]->setPosition(100, -375);
	SpriteManager::getInstance()->getSpritePtrs()[52]->setPosition(50, -375);
	SpriteManager::getInstance()->getSpritePtrs()[53]->setPosition(0, -375);
	SpriteManager::getInstance()->getSpritePtrs()[54]->setPosition(-50, -375);
	SpriteManager::getInstance()->getSpritePtrs()[55]->setPosition(-100, -375);
	SpriteManager::getInstance()->getSpritePtrs()[56]->setPosition(-150, -375);
	SpriteManager::getInstance()->getSpritePtrs()[57]->setPosition(-200, -375);
	SpriteManager::getInstance()->getSpritePtrs()[58]->setPosition(-250, -375);
	SpriteManager::getInstance()->getSpritePtrs()[59]->setPosition(-300, -375);
	SpriteManager::getInstance()->getSpritePtrs()[60]->setPosition(-350, -375);
	SpriteManager::getInstance()->getSpritePtrs()[61]->setPosition(-400, -375);
	SpriteManager::getInstance()->getSpritePtrs()[62]->setPosition(-450, -375);
	SpriteManager::getInstance()->getSpritePtrs()[63]->setPosition(450, -325);	// Begin Right Column
	SpriteManager::getInstance()->getSpritePtrs()[64]->setPosition(450, -275);
	SpriteManager::getInstance()->getSpritePtrs()[65]->setPosition(450, -225);
	SpriteManager::getInstance()->getSpritePtrs()[66]->setPosition(450, -175);
	SpriteManager::getInstance()->getSpritePtrs()[67]->setPosition(450, -125);
	SpriteManager::getInstance()->getSpritePtrs()[68]->setPosition(450, -75);
	SpriteManager::getInstance()->getSpritePtrs()[69]->setPosition(450, -25);
	SpriteManager::getInstance()->getSpritePtrs()[70]->setPosition(450, 25);
	SpriteManager::getInstance()->getSpritePtrs()[71]->setPosition(450, 75);
	SpriteManager::getInstance()->getSpritePtrs()[72]->setPosition(450, 125);
	SpriteManager::getInstance()->getSpritePtrs()[73]->setPosition(450, 175);
	SpriteManager::getInstance()->getSpritePtrs()[74]->setPosition(450, 225);
	SpriteManager::getInstance()->getSpritePtrs()[75]->setPosition(450, 275);

	// Initialize obstacle sprites
	SpriteManager::getInstance()->getSpritePtrs()[76]->setPosition(-325, -200); // Left Obstacle
	SpriteManager::getInstance()->getSpritePtrs()[77]->setPosition(-325, -150);
	SpriteManager::getInstance()->getSpritePtrs()[78]->setPosition(-325, -100);
	SpriteManager::getInstance()->getSpritePtrs()[79]->setPosition(-275, -100);
	SpriteManager::getInstance()->getSpritePtrs()[80]->setPosition(-275, -50);
	SpriteManager::getInstance()->getSpritePtrs()[81]->setPosition(-275, 0);
	SpriteManager::getInstance()->getSpritePtrs()[82]->setPosition(-275, 50);
	SpriteManager::getInstance()->getSpritePtrs()[83]->setPosition(-325, 50);
	SpriteManager::getInstance()->getSpritePtrs()[84]->setPosition(-325, 100);
	SpriteManager::getInstance()->getSpritePtrs()[85]->setPosition(-325, 150);

	SpriteManager::getInstance()->getSpritePtrs()[86]->setPosition(275, -200); // Right Obstacle
	SpriteManager::getInstance()->getSpritePtrs()[87]->setPosition(275, -150);
	SpriteManager::getInstance()->getSpritePtrs()[88]->setPosition(275, -100);
	SpriteManager::getInstance()->getSpritePtrs()[89]->setPosition(225, -100);
	SpriteManager::getInstance()->getSpritePtrs()[90]->setPosition(225, -50);
	SpriteManager::getInstance()->getSpritePtrs()[91]->setPosition(225, 0);
	SpriteManager::getInstance()->getSpritePtrs()[92]->setPosition(225, 50);
	SpriteManager::getInstance()->getSpritePtrs()[93]->setPosition(275, 50);
	SpriteManager::getInstance()->getSpritePtrs()[94]->setPosition(275, 100);
	SpriteManager::getInstance()->getSpritePtrs()[95]->setPosition(275, 150);

	SpriteManager::getInstance()->getSpritePtrs()[96]->setPosition(-125, 175); // Top Obstacle
	SpriteManager::getInstance()->getSpritePtrs()[97]->setPosition(-75, 175);
	SpriteManager::getInstance()->getSpritePtrs()[98]->setPosition(-25, 175);
	SpriteManager::getInstance()->getSpritePtrs()[99]->setPosition(25, 175);
	SpriteManager::getInstance()->getSpritePtrs()[100]->setPosition(75, 175);

	SpriteManager::getInstance()->getSpritePtrs()[101]->setPosition(-125, -225); // Bottom Obstacle
	SpriteManager::getInstance()->getSpritePtrs()[102]->setPosition(-75, -225);
	SpriteManager::getInstance()->getSpritePtrs()[103]->setPosition(-25, -225);
	SpriteManager::getInstance()->getSpritePtrs()[104]->setPosition(25, -225);
	SpriteManager::getInstance()->getSpritePtrs()[105]->setPosition(75, -225);

	SpriteManager::getInstance()->getSpritePtrs()[106]->setPosition(-25, -25); // Center Obstacle

	// Initialize Colliders on Blocks (left X, bottom Y, right X, top Y)
	blocks[0] = Block(-500, 275, 500, 325); // Top Row
	blocks[1] = Block(-500, -425, 500, -375); // Bottom Row
	blocks[2] = Block(-500, -425, -450, 325); // Left Col
	blocks[3] = Block(450, -425, 500, 325); // Right Col
	blocks[4] = Block(-125, 125, 125, 175); // Top Obstacle
	blocks[5] = Block(-125, -275, 125, -225); // Bottom Obstacle
	blocks[6] = Block(-325, -250, -275, -100); // Left Obstacle
	blocks[7] = Block(-275, -150, -225, 50); 
	blocks[8] = Block(-325, 0, -275, 150); 
	blocks[9] = Block(275, -250, 325, -100); // Right Obstacle
	blocks[10] = Block(225, -150, 275, 50); 
	blocks[11] = Block(275, 0, 325, 150); 
	blocks[12] = Block(-25, -75, 25, -25); // Center Obstacle

	mEnabled = true;

}