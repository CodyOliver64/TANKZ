#define NUM_PLAYER_VECTORS 6

class BulletManager
{
public:
    BulletManager();
    ~BulletManager();

    static BulletManager* CreateInstance();
    static BulletManager* GetInstance() { return sInstance; };
    void updateBullets(DWORD milliseconds);
    void checkCollision();

    void resetBullet(int player);

    void fireBullet(int player);

    void init();

private:
    //bool CollideField();
    void CollideArena(int bullet, int bulletX, int bulletY);

    static BulletManager* sInstance;

    float bulletPosX[NUM_PLAYER_VECTORS]; // 0 - 2 = Player 1 bullets, 3-5 = player 2 bullets
    float bulletPosY[NUM_PLAYER_VECTORS];
    float bulletVelocityX[NUM_PLAYER_VECTORS];
    float bulletVelocityY[NUM_PLAYER_VECTORS];
    float bulletBounces[NUM_PLAYER_VECTORS];
    float bulletActive[NUM_PLAYER_VECTORS];

    DWORD mLastUpdateTime[2] = { 1000, 1000 };
    DWORD mCurrentTime[2] = { 2000, 2000 };
    int numBounces = 3;

    bool mEnabled;
    float mRadius;

};



