#include <Windows.h>
#include <vector>
#include <fmod.h>
#include <fmod.hpp>
#include <mmsystem.h>               // Multimedia header file.
#pragma comment(lib, "winmm.lib")   // Multimedia import library.
#pragma comment (lib, "fmodex_vc.lib" )
using namespace std;

#ifndef __AudioManager_h__
#define __AudioManager_h__


class GamePlayState;
class HighScoresMenuState;
class WinMenuState;
class DefeatMenuState;
class CreditsMenuState;
class LoadMenuState;
class PauseMenuState;
class MainMenuState;
class HowToPlayMenuState;
class CutScene;
class sound;
class AudioManager;

class AudioManager
{
private: 
	FMOD::ChannelGroup* _masterChannel;
	FMOD::System* _sys;
	FMOD_RESULT _result;
	float _t;
	FMOD_VECTOR _lastpos;
	FMOD_VECTOR _forward;
	FMOD_VECTOR _up;
	FMOD_VECTOR _vel;
	FMOD_SPEAKERMODE _speakermode;
	FMOD_CAPS _caps;
	vector<sound*> _sfxSound;
	float _sfxVolume;
	bool _sfxMute;
	float _gasConstant;
	vector<sound*> _musicSound;
	float _musicVolume;
	bool _musicMute;

public:
	AudioManager* GetInstance();

	int RegisterSound(char* filePath);

	void TogleMuteSound();

	void setSoundVolume(float volume);

	void setSoundLooping(int soundID, bool loop);

	void setSoundPaused(int aSoundID, FMOD_VECTOR aPosition);

	void setSoundVel(int aSoundID, string aFMOD_VECTOR_velocity);

	bool isSoundPlaying(int aSoundID);

	float getSoundVolume(string aVoid_37);

	bool getSundLoop(int aSoundID);

	FMOD_VECTOR getSoundPos(int aSoundID);

	FMOD_VECTOR getSoundVel(int aSoundID);

	void playMusic(int aSoundID);

	int registerMusic(char* aFilePath);

	void toggleMuteMusic();

	void setMusicVolume(float aFvolume);

	void setMusicLooping(int aSoundID, bool aLoop);

	void setMusicPos(int aSoundID, FMOD_VECTOR aPosition);

	void setMusicVel(int aSoundID, FMOD_VECTOR aVelocity);

	FMOD_VECTOR getListenerPos(int aSoundID);

	FMOD_VECTOR getListenerVel(int aSoundID);

	void Update(float fElapsedTime);
};

#endif
