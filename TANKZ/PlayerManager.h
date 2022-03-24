class PlayerManagerC
{
public:
    PlayerManagerC();
    ~PlayerManagerC();

    static PlayerManagerC* CreateInstance();
    static PlayerManagerC* GetInstance() { return sInstance; };
    void updatePlayerManager(DWORD milliseconds);

    void update(DWORD milliseconds);

    void DoCollisions();
    void disable() { mEnabled = false; };
    void enable() { mEnabled = true; };

    void moveUp();

    void	moveUp(int player);
    void	moveDown(int player);
    void	moveLeft(int player);
    void	moveRight(int player);

    void rotateCannonLeft(int player);
    void rotateCannonRight(int player);

    float getPlayerXPos(int player);
    float getPlayerYPos(int player);
    int getCannonRotation(int player);

    void init();

    int playerHealth[2]{ 3, 3 };


private:
    bool CollideArena(int playerX, int playerY);
    bool CollidePlayer(int playerX, int playerY, int playerNum);

    static PlayerManagerC* sInstance;

    float playerPosX[2];
    float playerPosY[2];

    bool mEnabled;
    float mRadius;

    int cannonRotation[2] = { -90, -90 };

    float speed = 2;

    DWORD mLastUpdateTime[2] = { 1000, 1000 };
    DWORD mCurrentTime[2] = { 2000, 2000 };

};

