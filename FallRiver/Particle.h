#include <Windows.h>
using namespace std;

#ifndef __Particle_h__
#define __Particle_h__

// #include "Emitter.h"

class Emitter;
class Particle;

class Particle
{

private: 
	int m_nFrameX;
	int m_nFrameY;
	DWORD m_dwDelay;
	//D3DVec2 vel;
	float lifeSpan;
	//D3DVec2 pos;
	int color;
	int imageID;

public: 
	void Update(float aFElapsedTime);
	void Render();
};

#endif
