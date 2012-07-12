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
	return loaded.size() - 1;
}

int Particle_Manager::ActivateEmitter(int id)
{
	Emitter* tmp = new Emitter();
	tmp->spawnRate = loaded[id]->spawnRate;
	tmp->loopin = loaded[id]->loopin;
	tmp->rect = loaded[id]->rect;
	tmp->maxParticles = loaded[id]->maxParticles;
	tmp->endVel = loaded[id]->endVel;
	tmp->endScaleX = loaded[id]->endScaleX;
	tmp->endScaleY = loaded[id]->endScaleY;
	tmp->endColor = loaded[id]->endColor;
	tmp->startVel = loaded[id]->startVel;
	tmp->startScaleX = loaded[id]->startScaleX;
	tmp->startScaleY = loaded[id]->startScaleY;
	tmp->startColor = loaded[id]->startColor;
	tmp->blendModeS = loaded[id]->blendModeS;
	tmp->blendModeD = loaded[id]->blendModeD;
	tmp->imageID = loaded[id]->imageID;
	tmp->lifeSpan = loaded[id]->lifeSpan;
	tmp->lifeTime = loaded[id]->lifeTime;
	tmp->age = 0;
	tmp->endRot = loaded[id]->endRot;
	tmp->startRot = loaded[id]->startRot;
	tmp->spawnTimer = 0.0f;
	active.push_back(tmp);
	active[active.size() - 1]->spawn = true;
	return active.size() - 1;
}

void Particle_Manager::Render()
{
	for( unsigned int i = 0; i < active.size(); ++i)
		active[i]->Render();
}

void Particle_Manager::Update(float fElapsedTime)
{
	for( unsigned int i = 0; i < active.size(); ++i)
	{
		active[i]->SetAge( active[i]->GetAge() + fElapsedTime * 10);

		//Update Existance
		if(!active[i]->GetLooping())
		{
			float tmpActive = active[i]->GetAge();
			float tmpLife = active[i]->GetLifeTime();
			if(tmpActive >= tmpLife)
				active[i]->spawn = false;
		}
		if(active[i]->_m_vparticles.size() > 0 )
			active[i]->Update(fElapsedTime);
	}
}
