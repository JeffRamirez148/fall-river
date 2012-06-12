#include "AudioManager.h"


AudioManager* AudioManager::GetInstance()
{
	static AudioManager s_Instance;

	return &s_Instance;
}

// The following functions do not work yet
AudioManager::AudioManager(void)
{
}

AudioManager::~AudioManager(void)
{
}

void AudioManager::playSound(int aSoundID)
{
}

int	AudioManager::RegisterSound(char* filePath)
{
	return 1;
}

void AudioManager::playMusic(int aSoundID)
{
}

int	AudioManager::registerMusic(char* aFilePath)
{
	return 1;
}

void AudioManager::Update(float fElapsedTime)
{
}
