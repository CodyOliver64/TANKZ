#define RESTART_TIME 3000

class CGame
{
public:
	const char8_t* GetGameTitle() { return mGameTitle; };
	static CGame	*CreateInstance();
	static CGame	*GetInstance() {return sInstance;};
	~CGame();
	void DrawScene();
	void UpdateFrame(DWORD milliseconds);
	void DestroyGame();
	void RestartGame();
	void init();
	void shutdown();
	void gameOver(int player);
	void startGame();
	static const uint32_t mScreenWidth = 1024;
	static const uint32_t mScreenHeight = 768;
	static const uint32_t mBitsPerPixel = 32;

	bool gameStart = false;
	bool spritesLoaded = false;
	bool gameIsOver = false;
private:
	static const char8_t mGameTitle[20];
	static CGame *sInstance;
	CGame(){};

	int timerForRestart{ RESTART_TIME };
};