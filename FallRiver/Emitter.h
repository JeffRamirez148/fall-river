#include <Windows.h>
#include <vector>
using namespace std;

#ifndef __Emitter_h__
#define __Emitter_h__

// #include "Particle_Manager.h"
// #include "Particle.h"

class Particle_Manager;
class Particle;
class Emitter;

class Emitter
{
	private: 
		vector<Particle*> _m_vparticles;
	float spawnRate;
	bool loopin;
	RECT rect;
	int maxParticles;
	//D3DVec2 endVel;
	float endScale;
	int endColor;
	//D3DVec2 startVel;
	float startScale;
	int startColor;
	int blendMode;
	//D3DVec2 pos;

	public: 
	void Update(float fElapsedTime);

	void Render();
};

#endif
