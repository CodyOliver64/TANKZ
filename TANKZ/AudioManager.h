#ifndef AUDIO_MANAGER_H
#define AUDIO_MANAGER_H

#include "SoundSystem.h"

class AudioManager
{
		
public:
	~AudioManager() {};

	static AudioManager* createInstance();
	static AudioManager* getInstance() { return sInstance; }

	void init();
	void update();
	void shutdown();

	// Play sound for firing of bullets
	void playFiringSound(int player);

	// Play sound when enemy plane enters allied area
	void playHitSound(int player);

	void playBackground();
	void stopBackground();
	void playStartSound();
	void playWinSound();
	void playBounceSound();

	SoundSystem* mSoundSystem;
private:
	AudioManager() {};

	static AudioManager* sInstance;

	Sound fireSound1;
	Sound fireSound2;
	Sound hitSound1;
	Sound hitSound2;

	Sound backgroundMusic;
	Sound winSound;
	Sound startSound;
	Sound bounceSound;
};

#endif