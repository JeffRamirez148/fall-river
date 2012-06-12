//#include <Windows.h>
#include <vector>
#include <fmod.h>
#include <fmod.hpp>
//#include <mmsystem.h>               // Multimedia header file.
//#pragma comment(lib, "winmm.lib")   // Multimedia import library.
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
#include "sound.h"
class AudioManager;

class AudioManager
{
private: 
// Variables
	//General
	FMOD::ChannelGroup* _masterChannel;
	FMOD::System* _sys;
	FMOD_RESULT _result;
	float _t;
	FMOD_VECTOR _lastpos;
	FMOD_VECTOR _forward;
	FMOD_VECTOR _up;
	FMOD_VECTOR _vel;
    FMOD_VECTOR listenerpos;
	FMOD_SPEAKERMODE _speakermode;
	FMOD_CAPS _caps;
	float _gasConstant;

	// Sound
	vector<sound*> _sfxSound;
	float _sfxVolume;
	bool _sfxMute;

	// Music
	vector<sound*> _musicSound;
	float _musicVolume;
	bool _musicMute;

// Functions
	AudioManager(void);
	~AudioManager(void);
public:
	// General
	void Update(float fElapsedTime);
	static AudioManager* GetInstance();

	// Sound
	void playSound(int aSoundID);
	int RegisterSound(char* filePath);
	void TogleMuteSound() {_sfxMute = !_sfxMute; }
	void setSoundVolume(float volume) {_sfxVolume = volume; }
	void setSoundLooping(int soundID, bool loop)
	{ 
		_sfxSound[soundID]->looping = loop;
		if(loop)
			_sfxSound[soundID]->noise->setMode(FMOD_LOOP_NORMAL);
		else
			_sfxSound[soundID]->noise->setMode(FMOD_LOOP_OFF);
	}
	void setSoundPos(int aSoundID, FMOD_VECTOR aPosition) { _sfxSound[aSoundID]->pos = aPosition; }
	void setSoundVel(int aSoundID, FMOD_VECTOR aVelocity) { _sfxSound[aSoundID]->vel = aVelocity; }
	bool isSoundPlaying(int aSoundID) {return _sfxSound[aSoundID]->isPlaying;}
	float getSoundVolume(string aVoid_37) {return _sfxVolume; }
	bool getSoundLoop(int aSoundID) {return _sfxSound[aSoundID]->looping; }
	FMOD_VECTOR getSoundPos(int aSoundID) {return _sfxSound[aSoundID]->pos;}
	FMOD_VECTOR getSoundVel(int aSoundID) {return _sfxSound[aSoundID]->vel;}

	// Music
	void playMusic(int aSoundID);
	int registerMusic(char* aFilePath);
	void toggleMuteMusic() { _musicMute = !_musicMute;}
	void setMusicVolume(float aFvolume) {_musicVolume = aFvolume;}
	void setMusicLooping(int aSoundID, bool aLoop)
	{
		_musicSound[aSoundID]->looping = aLoop;
		if(aLoop)
			_musicSound[aSoundID]->noise->setMode(FMOD_LOOP_NORMAL);
		else
			_musicSound[aSoundID]->noise->setMode(FMOD_LOOP_OFF);
	}
	void setMusicPos(int aSoundID, FMOD_VECTOR aPosition) { _musicSound[aSoundID]->pos = aPosition; }
	void setMusicVel(int aSoundID, FMOD_VECTOR aVelocity) { _musicSound[aSoundID]->vel = aVelocity; }
	bool isMusicPlaying(int aSoundID) { return _musicSound[aSoundID]->isPlaying; }
	float getMusicVolume(void) {return _musicVolume; }
	FMOD_VECTOR GetMusicPos(int aSoundID) { return _musicSound[aSoundID]->pos; }
	FMOD_VECTOR GetMusicVel(int aSoundID) { return _musicSound[aSoundID]->vel; }

	// Listener
	void SetListenerPos(FMOD_VECTOR aPosition) { listenerpos = aPosition; }
	void SetListenerVel(FMOD_VECTOR aVelocity) { _vel = aVelocity; }
	FMOD_VECTOR getListenerPos(void) { return listenerpos; }
	FMOD_VECTOR getListenerVel(void) { return _vel; }
};

#endif
