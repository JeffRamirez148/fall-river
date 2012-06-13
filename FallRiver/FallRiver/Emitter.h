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
	D3DXVECTOR3 pos;

public: 
	void Update(float fElapsedTime);

	void Render();
};

#endif
