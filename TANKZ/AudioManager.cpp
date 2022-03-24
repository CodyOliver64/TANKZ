#include "AudioManager.h"
#include "baseTypes.h"
#include "SoundSystem.h"

AudioManager* AudioManager::sInstance = nullptr;

AudioManager* AudioManager::createInstance()
{
	if (sInstance == nullptr)
	{
		sInstance = new AudioManager();
	}
	return sInstance;
}

void AudioManager::init()
{
	mSoundSystem = new SoundSystem();
	mSoundSystem->createSound(&fireSound1, "Sounds/Shoot.wav");
	mSoundSystem->createSound(&fireSound2, "Sounds/Jump.wav");
	mSoundSystem->createSound(&hitSound1, "Sounds/DM-CGS-49.wav");
	mSoundSystem->createSound(&hitSound2, "Sounds/CrashSound.wav");

	mSoundSystem->createSound(&backgroundMusic, "Sounds/Mars3.wav");
	mSoundSystem->createSound(&winSound, "Sounds/WinJingle2.wav");
	mSoundSystem->createSound(&startSound, "Sounds/start2.wav");

	mSoundSystem->createSound(&bounceSound, "Sounds/Scoop2.wav");
	
}

void AudioManager::update()
{

}

void AudioManager::shutdown()
{
	// Release sounds
	mSoundSystem->releaseSound(fireSound1);
	mSoundSystem->releaseSound(fireSound1);
	mSoundSystem->releaseSound(hitSound1);
	mSoundSystem->releaseSound(hitSound2);
	mSoundSystem->releaseSound(backgroundMusic);
	mSoundSystem->releaseSound(winSound);
	mSoundSystem->releaseSound(startSound);
	mSoundSystem->releaseSound(bounceSound);
	delete mSoundSystem;
}

void AudioManager::playFiringSound(int player)
{
	if (player == 0)
	{
		mSoundSystem->playSound(fireSound1, false);
	}
	else
	{
		mSoundSystem->playSound(fireSound2, false);
	}
}

void AudioManager::playHitSound(int player)
{
	if (player == 0)
	{
		mSoundSystem->playSound(hitSound1, false);
	}
	else
	{
		mSoundSystem->playSound(hitSound2, false);
	}
}

void AudioManager::playStartSound()
{
	mSoundSystem->playSound(startSound, false);
}

void AudioManager::playWinSound()
{
	mSoundSystem->playSound(winSound, false);
}

void AudioManager::playBackground()
{
	mSoundSystem->playSound(backgroundMusic, true);
}

void AudioManager::stopBackground()
{
	mSoundSystem->releaseSound(backgroundMusic);
}

void AudioManager::playBounceSound()
{
	mSoundSystem->playSound(bounceSound, false);
}

