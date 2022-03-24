#ifndef COLLIDER_H
#define COLLIDER_H

#include "baseTypes.h"
//#include "Sprite.h"

class Sprite;

typedef enum ColliderTag
{
	INVALID_COLLIDER,
	PLANE_A,
	PLANE_B,
	BULLET_A,
	BULLET_B
};

class Collider
{

public:


	Collider(int32_t, int32_t, int32_t, int32_t, ColliderTag, Sprite*);
	~Collider() {};

	void renderCollider();
	ColliderTag getTag();
	//void setAssociatedSprite(Sprite* sprite);
	//void init();
	int32_t getOffsetX();
	int32_t getOffsetY();
	int32_t getWidth();
	int32_t getHeight();
private:

	// Variables defining the bounding box of the collider
	int32_t mOffsetX;
	int32_t mOffsetY;
	int32_t mWidth;
	int32_t mHeight;

	ColliderTag mColliderTag;

	// The sprite to which the collider is associated;
	Sprite* mSprite;
	
};

#endif