#include "Particle_Manager.h"
#include "Emitter.h"
#include "XMLManager.h"

Particle_Manager* Particle_Manager::GetInstance(void)
{
	static Particle_Manager s_Instance;
	return &s_Instance;
}

int Particle_Manager::LoadEmitter(char * filepath)
{
	XMLManager* xml = XMLManager::GetInstance();
	Emitter* tmp = xml->ParseEmitter(filepath);
	loaded.push_back(tmp);
	return loaded.size();
}

int Particle_Manager::ActivateEmitter(int id)
{
	loaded[id - 1];
	active.push_back(loaded[id - 1]);
	return active.size();
}

void Particle_Manager::Render()
{
	for( unsigned int i = 0; i < active.size(); ++i)
		active[i]->Render();
}

void Particle_Manager::Update(float fElapsedTime)
{
	bool keepGoing;
	for( unsigned int i = 0; i < active.size(); ++i)
	{
		keepGoing = true;
		active[i]->SetAge( active[i]->GetAge() + fElapsedTime);
		//Update Existance
		if(!active[i]->GetLooping())
		{
			if(active[i]->GetAge() >= active[i]->GetLifeTime())
			{
				active.erase(active.begin() + i, active.begin() + i);
				--i;
				keepGoing = false;
			}
		}
		// Update Everything Else
		if(keepGoing)
			active[i]->Update(fElapsedTime);
	}
}
