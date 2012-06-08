#include <string>
#include <map>
#include <vector>
using namespace std;

#ifndef __Particle_Manager_h__
#define __Particle_Manager_h__

// #include "GamePlayState.h"
// #include "Emitter.h"

class GamePlayState;
class Emitter;
class Particle_Manager;

class Particle_Manager
{
	private:
	map<string, Emitter> loaded;
	vector<Emitter*> active;
	public: 
	
};

#endif
