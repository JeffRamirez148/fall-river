#ifndef __Emitter_h__
#define __Emitter_h__
#include <vector>
using namespace std;
#include <D3DX9.h>
#pragma comment(lib, "D3DX9.lib")
#include "AudioManager.h"

class Particle;

class Emitter
{
	public: 
	vector<Particle*> _m_vparticles;
	float spawnRate;
	bool loopin;
	RECT rect;
	int maxParticles;
	D3DXVECTOR3 endVel;
	float endScaleX;
	float endScaleY;
	int endColor;
	D3DXVECTOR3 startVel;
	float startScaleX;
	float startScaleY;
	int startColor;
	int blendModeS;
	int blendModeD;
	float spawnTimer;
	int imageID;
	float lifeSpan;
	float lifeTime;
	float age;
	float endRot;
	float startRot;
	int soundID;


	Emitter( float newSpawnRate, bool newLooping, RECT newRect,int newMaxParticles, 
			D3DXVECTOR3 newStartVec, D3DXVECTOR3 newEndVec, float newStartScaleX, float newStartScaleY,
			 float newEndScaleX, float newEndScaleY, int newBlendModeS, int newBlendModeD, int newImageID, float newParticleLifeSpan,
			 float newEmitterLifeTime, int newStartColor, int newEndColor,  float newStartRot, float newEndRot);
	Emitter();
	Emitter& operator=(const Emitter& emitter);
	Emitter(const Emitter& emitter);
	void Update(float fElapsedTime);
	void Render();

	bool spawn;
	float GetAge(void) { return age; }
	bool GetLooping(void) { return loopin;}
	float GetLifeTime(void) { return lifeTime; }
	RECT GetRect(void) {return rect; }
	int GetImageID(void) {return imageID; }
	int GetSoundID(void) {return soundID; }

	void SetAge(float newAge) { age = newAge; }
	void SetLifeTime(float newLifeTime) { lifeTime = newLifeTime; }
	void SetLifeSpan(float newLifeSpan) { lifeSpan = newLifeSpan; }
	void SetStartScaleX(float newScaleX) { startScaleX = newScaleX; }
	void SetEndScaleX(float newScaleX) { endScaleX = newScaleX; }
	void SetStartScaleY(float newScaleY) { startScaleY = newScaleY; }
	void SetEndScaleY(float newScaleY) { endScaleY = newScaleY; }
	void SetSpawnRate(float newSpawnRate) { spawnRate = newSpawnRate; }
	void SetLoopin(bool loop) { loopin = loop; }
	void SetBlendModeS(int blendMode) { blendModeS = blendMode; }
	void SetBlendModeD(int blendMode) { blendModeD = blendMode; }
	void SetImageID(int newImageID) { imageID = newImageID; }
	void SetStartColor(int newStartColor) { startColor = newStartColor; }
	void SetEndColor(int newEndColor) { endColor = newEndColor; }
	void SetMaxParticles(int newMax) { maxParticles = newMax; }
	void SetStartRotation(float newRot) { startRot = newRot; }
	void SetEndRotation(float newRot) { endRot = newRot; }                   
	void SetRect(RECT newRect) { rect = newRect;}
	void SetSoundID( int id)
	{ 
		soundID = id;
		AudioManager::GetInstance()->setSoundLooping( soundID, true);
		AudioManager::GetInstance()->playSound(soundID);
	}
};

#endif
