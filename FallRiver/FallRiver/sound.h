#ifndef __sound_h__
#define __sound_h__

#include <Windows.h>

#include <fmod.h>
#include <fmod.hpp>
#include <mmsystem.h>               // Multimedia header file.
#pragma comment(lib, "winmm.lib")   // Multimedia import library.
#pragma comment (lib, "fmodex_vc.lib" )
// #include "AudioManager.h"

class AudioManager;

struct sound
{
	FMOD::Sound* noise;
	int id;
	bool looping;
	bool isPlaying;
	FMOD::Channel* channel;
	FMOD_VECTOR pos;
	FMOD_VECTOR vel;
	float humidity;
	float temperature;
	float molecularWeight;
};

#endif
