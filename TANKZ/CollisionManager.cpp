#include "CollisionManager.h"
#include "baseTypes.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "PlaneManager.h"
#include "GameManager.h"

#include <windows.h>

CollisionManager* CollisionManager::sInstance = nullptr;

CollisionManager* CollisionManager::createInstance()
{
	if (sInstance == nullptr)
	{
		sInstance = new CollisionManager();
	}
	return sInstance;
}

CollisionManager* CollisionManager::getInstance()
{
	return sInstance;
}

void CollisionManager::init()
{

}

void CollisionManager::update(DWORD deltaTime)
{
	checkForPlaneShotDown();
}

void CollisionManager::checkForPlaneShotDown()
{
	Sprite** spritePtrs = SpriteManager::getInstance()->getSpritePtrs();
	int32_t numberOfSprites = SpriteManager::getNumberOfSprites();
	for (int32_t i = 0; i < numberOfSprites; i++)
	{
		// Skip any sprite without a collider
		if (spritePtrs[i]->getCollider() == nullptr)
		{
			continue;
		}
		ColliderTag tag = spritePtrs[i]->getCollider()->getTag();
		// Skip the sprite if it is not a plane
		if (!(tag == ColliderTag::PLANE_A) && !(tag == ColliderTag::PLANE_B))
		{
			continue;
		}
		// Check if PLANE_A(s) is colliding with any of the bullets from Turret B
		if (tag == ColliderTag::PLANE_A)
		{
			// Check for no friendly fire
			for (int32_t j = SpriteManager::SpriteName::BULLET_B_1; j <= SpriteManager::SpriteName::BULLET_B_3; j++)
			{
				if (onCollision(spritePtrs[i], spritePtrs[j]))
				{
					spritePtrs[i]->disableSprite();
					spritePtrs[i]->setVelocity(0, 0);
					spritePtrs[i]->setPosition(512, 768);
					if (i == SpriteManager::SpriteName::PLANE_A_1) PlaneManager::getInstance()->setResetPositionRequired(1);
					if (i == SpriteManager::SpriteName::PLANE_A_2) PlaneManager::getInstance()->setResetPositionRequired(2);
					GameManager::getInstance()->resetBullet(spritePtrs[j],j);
				}
			}
		}
		// Check if PLANEB(s) is colliding with any of the bullets from Turret A
		else if (tag == ColliderTag::PLANE_B)
		{
			// Check for no friendly fire
			for (int32_t j = SpriteManager::SpriteName::BULLET_A_1; j <= SpriteManager::SpriteName::BULLET_A_3; j++)
			{
				if (onCollision(spritePtrs[i], spritePtrs[j]))
				{
					spritePtrs[i]->disableSprite();
					spritePtrs[i]->setVelocity(0, 0);
					spritePtrs[i]->setPosition(512, 768);
					if (i == SpriteManager::SpriteName::PLANE_B_1) PlaneManager::getInstance()->setResetPositionRequired(3);
					if (i == SpriteManager::SpriteName::PLANE_B_2) PlaneManager::getInstance()->setResetPositionRequired(4);
					GameManager::getInstance()->resetBullet(spritePtrs[j], j);
				}
			}
		}
	}
}

bool8_t CollisionManager::onCollision(Sprite* spriteA, Sprite* spriteB)
{
	// Calculate positions for collider of SpriteA
	Coord2D* positionA = spriteA->getPosition();
	Collider* colliderA = spriteA->getCollider();

	float_t leftA = positionA->x + colliderA->getOffsetX();
	float_t rightA = leftA + colliderA->getWidth();
	float_t bottomA = positionA->y + colliderA->getOffsetY();
	float_t topA = bottomA + colliderA->getHeight();
	// Calculate positions for collider of SpriteB
	Coord2D* positionB = spriteB->getPosition();
	Collider* colliderB = spriteB->getCollider();

	float_t leftB = positionB->x + colliderB->getOffsetX();
	float_t rightB = leftB + colliderB->getWidth();
	float_t bottomB = positionB->y + colliderB->getOffsetY();
	float_t topB = bottomB + colliderB->getHeight();
	// Check for collision
	if (leftA < rightB && rightA > leftB && topA > bottomB && bottomA < topB)
	{
		return TRUE;
	}
	return FALSE;
}

void CollisionManager::shutdown()
{
	int32_t numberOfSprites = SpriteManager::getNumberOfSprites();
	Sprite** spritePtrs = SpriteManager::getInstance()->getSpritePtrs();
	Sprite* first = spritePtrs[0];
	for (int32_t i = 0; i < numberOfSprites; i++)
	{
		if (spritePtrs[i]->getCollider() != nullptr)
		{
			delete spritePtrs[i]->getCollider();
		}
	}
}

