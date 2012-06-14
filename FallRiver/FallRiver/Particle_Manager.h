#include <string>
#include <map>
#include <vector>
using namespace std;

#ifndef __Particle_Manager_h__
#define __Particle_Manager_h__

class Emitter;
class Particle_Manager
{
private:
	vector<Emitter*> loaded;
	vector<Emitter*> active;
	Particle_Manager() { };
	~Particle_Manager() { };
public: 
	int LoadEmitter(char * filepath);
	int ActivateEmitter(int id);
	void Render();
	void Update(float fElapsedTime);
	static Particle_Manager* GetInstance(void);
};

#endif
