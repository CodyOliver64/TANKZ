#include "Collider.h"
#include "baseTypes.h"
#include "Sprite.h"
#include "ShapeDraw.h"

Collider::Collider(int32_t x, int32_t y, int32_t width, int32_t height, ColliderTag tag, Sprite* sprite)
{
	mOffsetX = x;
	mOffsetY = y;
	mWidth = width;
	mHeight = height;
	mColliderTag = tag;
	mSprite = sprite;
}

ColliderTag Collider::getTag()
{
	return mColliderTag;
}

int32_t Collider::getOffsetX()
{
	return mOffsetX;
}

int32_t Collider::getOffsetY()
{
	return mOffsetY;
}

int32_t Collider::getHeight()
{
	return mHeight;
}

int32_t Collider::getWidth()
{
	return mWidth;
}


void Collider::renderCollider()
{
	Coord2D* spritePosition = mSprite->getPosition();

	float_t left = spritePosition->x + mOffsetX;
	float_t right = left + mWidth;
	float_t bottom = spritePosition->y + mOffsetY;
	float_t top = bottom + mHeight;

	char8_t r = (char8_t)(0x00FF0000 >> 16 & 0xFF);
	char8_t g = (char8_t)(0x00FF0000 >> 8 & 0xFF);
	char8_t b = (char8_t)(0x00FF0000 >> 0 & 0xFF);

	DrawLine(left, top, right, top, r, g, b);
	DrawLine(right, top, right, bottom, r, g, b);
	DrawLine(right, bottom, left, bottom, r, g, b);
	DrawLine(left, bottom, left, top, r, g, b);
}