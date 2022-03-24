#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include "baseTypes.h"
#include "Sprite.h"

#include <windows.h>

class CollisionManager
{

public:
	~CollisionManager() {};

	static CollisionManager* createInstance();
	static CollisionManager* getInstance();

	void init();
	void update(DWORD deltaTime);
	void shutdown();

private:
	CollisionManager() {};

	static CollisionManager* sInstance;
	// Checks if any plane was hit by enemy bullets
	void checkForPlaneShotDown();
	// Returns true if two sprite's collider's are colliding
	bool8_t onCollision(Sprite*, Sprite*);
};

#endif