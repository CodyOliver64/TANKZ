
#ifndef SPRITE_MANAGER_H
#define SPRITE_MANAGER_H

#include "Sprite.h"
#include "openGLFramework.h"
//#include "Collider.h"

#include <windows.h>

class SpriteManager
{
public:
	~SpriteManager() {};

	enum SpriteName
	{
		PLANE_A_1,
		PLANE_B_1,
		BULLET_A_1,
		BULLET_A_2,
		BULLET_A_3,
		BULLET_B_1,
		BULLET_B_2,
		BULLET_B_3,
		INDICATOR_A,
		INDICATOR_B,
		BLOCK_1,
		BLOCK_2,
		BLOCK_3,
		BLOCK_4,
		BLOCK_5,
		BLOCK_6,
		BLOCK_7,
		BLOCK_8,
		BLOCK_9,
		BLOCK_10,
		BLOCK_11,
		BLOCK_12,
		BLOCK_13,
		BLOCK_14,
		BLOCK_15,
		BLOCK_16,
		BLOCK_17,
		BLOCK_18,
		BLOCK_19,
		BLOCK_20,
		BLOCK_21,
		BLOCK_22,
		BLOCK_23,
		BLOCK_24,
		BLOCK_25,
		BLOCK_26,
		BLOCK_27,
		BLOCK_28,
		BLOCK_29,
		BLOCK_30,
		BLOCK_31,
		BLOCK_32,
		BLOCK_33,
		BLOCK_34,
		BLOCK_35,
		BLOCK_36,
		BLOCK_37,
		BLOCK_38,
		BLOCK_39,
		BLOCK_40,
		BLOCK_41,
		BLOCK_42,
		BLOCK_43,
		BLOCK_44,
		BLOCK_45,
		BLOCK_46,
		BLOCK_47,
		BLOCK_48,
		BLOCK_49,
		BLOCK_50,
		BLOCK_51,
		BLOCK_52,
		BLOCK_53,
		BLOCK_54,
		BLOCK_55,
		BLOCK_56,
		BLOCK_57,
		BLOCK_58,
		BLOCK_59,
		BLOCK_60,
		BLOCK_61,
		BLOCK_62,
		BLOCK_63,
		BLOCK_64,
		BLOCK_65,
		BLOCK_66,
		BLOCK_67,
		BLOCK_68,
		BLOCK_69,
		BLOCK_70,
		BLOCK_71,
		BLOCK_72,
		BLOCK_73,
		BLOCK_74,
		BLOCK_75,
		BLOCK_76,
		BLOCK_77,
		BLOCK_78,
		BLOCK_79,
		BLOCK_80,
		BLOCK_81,
		BLOCK_82,
		BLOCK_83,
		BLOCK_84,
		BLOCK_85,
		BLOCK_86,
		BLOCK_87,
		BLOCK_88,
		BLOCK_89,
		BLOCK_90,
		BLOCK_91,
		BLOCK_92,
		BLOCK_93,
		BLOCK_94,
		BLOCK_95,
		BLOCK_96,
		BLOCK_97,
		GAME_END_1,
		GAME_END_2,
		BACKGROUND,
		START_SCREEN,
		LOADING,
		EXPLOSION_A_1,
		EXPLOSION_A_2,
		EXPLOSION_A_3,
		EXPLOSION_B_1,
		EXPLOSION_B_2,
		EXPLOSION_B_3,
		LIFE_A_1,
		LIFE_A_2,
		LIFE_A_3,
		LIFE_B_1,
		LIFE_B_2,
		LIFE_B_3,
	};

	static SpriteManager* createInstance();
	static SpriteManager* getInstance();

	void init();
	void update(DWORD milliseconds);
	void renderSprites();
	void shutDown();

	Sprite** getSpritePtrs();
	static int32_t getNumberOfSprites();

	int renderFlag = 2;

	void updateSpriteManager(DWORD milliseconds);

	bool animationActive[2] = { false, false };

private:
	SpriteManager() {};

	DWORD currentFrameTime;

	Sprite** spritePtrs;
	static SpriteManager* sInstance;
	static const uint8_t numBlocks = 97;
	static const uint8_t NUM_SPRITES = 27 + numBlocks;
	

	void initBackgroundSpritePtrs();
	void initPlayerSpritePtrs();
	void initBulletSpritePtrs();
	void initIndicatorSpritePtrs();
	void initBlockSpritePtrs();
	void initLivesSpritePtrs();
	void initGameDisplay();
	void initExplosionSpritePtrs();

	void initRotations();
	void initColliders();
	void animateSprite(int player);

	DWORD mLastUpdateTime[2] = { 1000, 1000 };
	DWORD mCurrentTime[2] = { 2000, 2000 };

	int currentAnimFrame[2] = { 0,0 }; 

};

#endif
