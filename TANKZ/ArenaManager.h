#pragma once
typedef float float_t;
class Block
{
public:
    Block();
    Block(float_t leftX, float_t bottomY, float_t rightX, float_t topY);
    ~Block();
    //bool8_t checkCollision();
    float_t leftX;
    float_t rightX;
    float_t topY;
    float_t bottomY;
};

class ArenaManager
{
public:
	ArenaManager();
	~ArenaManager();

    Block* getBlocks();
	static ArenaManager* CreateInstance();
	static ArenaManager* GetInstance() {return sInstance;};

    void init();

private:
	static ArenaManager* sInstance;

    Block blocks[13];
    bool mEnabled;

};

