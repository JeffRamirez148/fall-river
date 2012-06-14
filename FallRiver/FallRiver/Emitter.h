#ifndef __Emitter_h__
#define __Emitter_h__
#include <vector>
using namespace std;
#include <D3DX9.h>
#pragma comment(lib, "D3DX9.lib")

class Particle;

class Emitter
{
	vector<Particle*> _m_vparticles;
	float spawnRate;
	bool loopin;
	RECT rect;
	int maxParticles;
	D3DXVECTOR3 endVel;
	float endScale;
	int endColor;
	D3DXVECTOR3 startVel;
	float startScale;
	int startColor;
	int blendMode;
	float spawnTimer;
	int imageID;
	float lifeSpan;
	float lifeTime;
	float age;

public: 
	Emitter( float newSpawnRate, bool newLooping, RECT newRect,int newMaxParticles, 
			 D3DXVECTOR3 newStartVec, D3DXVECTOR3 newEndVec, float newStartScale, 
			 float newEndScale, int newBlendMode, int newImageID, float newParticleLifeSpan,
			 float newEmitterLifeTime, int newStartColor, int newEndColor, float newSpawnTimer);
	void Update(float fElapsedTime);
	void Render();

	float GetAge(void) { return age; }
	bool GetLooping(void) { return loopin;}
	float GetLifeTime(void) { return lifeTime; }

	void SetAge(float newAge) { age = newAge; }
};

#endif
