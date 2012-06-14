#include "Emitter.h"
#include "Particle_Manager.h"
#include "Particle.h"
void Emitter::Update(float fElapsedTime) 
{
	// Spawn particle?
	spawnTimer += fElapsedTime;
	if(spawnTimer >= spawnRate)
	{
		spawnTimer = 0;
		Particle* tmpParticle = new Particle;
		tmpParticle->SetColor( startColor );
		// Members to be loaded in and set
		tmpParticle->SetImageID(imageID);
		tmpParticle->SetLifeSpan(lifeSpan);
		tmpParticle->SetMode(blendMode);
		D3DXVECTOR3 tmpPos;
		tmpPos.x = (rand() % int(rect.right)) + rect.left;
		tmpPos.y = (rand() % int(rect.bottom)) + rect.top;
		tmpPos.z = 0;
		tmpParticle->SetPos(tmpPos);
		tmpParticle->SetVel(startVel);
		D3DXVECTOR3 tmpDir;
		tmpDir.x = (rand() % 3) + 1;
		tmpDir.y = (rand() % 3) + 1;
		tmpDir.z = 0;
		tmpParticle->SetDir(tmpDir);
		_m_vparticles.push_back(tmpParticle);
	}

	bool keepGoing;
	for( unsigned int i = 0; i < _m_vparticles.size(); ++i)
	{
		keepGoing = true;
		// Update Existance
		_m_vparticles[i]->SetLifeSpan((_m_vparticles[i]->GetLifeSpan()) - fElapsedTime);
		// Is the particle dead?
		if((_m_vparticles[i]->GetLifeSpan()) <= 0)
		{
			_m_vparticles.erase( _m_vparticles.begin() + i, _m_vparticles.begin() + i + 1);
			// Possible memory leak
			keepGoing = false;
			--i;
		}

		// If the particle isn't dead keep going
		if(keepGoing)
		{
			// Update Color 
			int tmpColor = _m_vparticles[i]->GetColor();
			int tmpA = tmpColor >> 24;
			int tmpR = (tmpColor << 8) >> 24;
			int tmpG = (tmpColor << 16) >> 24;
			int tmpB = (tmpColor << 24) >> 24;
			int endA = endColor >> 24;
			int endR = (endColor << 8) >> 24;
			int endG = (endColor << 16) >> 24;
			int endB = (endColor << 24) >> 24;
			if(startColor > endColor)
			{
				tmpA -= (int)fElapsedTime;
				tmpR -= (int)fElapsedTime;
				tmpG -= (int)fElapsedTime;
				tmpB -= (int)fElapsedTime;
				if(tmpA < endA)
					tmpA = endA;
				if(tmpR < endR)
					tmpR = endR;
				if(tmpG < endG)
					tmpG = endG;
				if(tmpB < endB)
					tmpB = endB;
				tmpColor = (tmpA << 24) + (tmpR << 16) + (tmpG << 8) + tmpB;
				if(tmpColor < endColor)
					tmpColor = endColor;
			}
			else
			{
				tmpA += (int)fElapsedTime;
				tmpR += (int)fElapsedTime;
				tmpG += (int)fElapsedTime;
				tmpB += (int)fElapsedTime;
				if(tmpA > endA)
					tmpA = endA;
				if(tmpR > endR)
					tmpR = endR;
				if(tmpG > endG)
					tmpG = endG;
				if(tmpB > endB)
					tmpB = endB;
				tmpColor = (tmpA << 24) + (tmpR << 16) + (tmpG << 8) + tmpB;
				if(tmpColor > endColor)
					tmpColor = endColor;
			}
			_m_vparticles[i]->SetColor(tmpColor);

			// Update Scale
			float tmpScale = _m_vparticles[i]->GetScale();
			if(startScale > endScale)
			{
				tmpScale -= fElapsedTime;
				if(tmpScale < endScale)
					tmpScale = endScale;
			}
			else
			{
				tmpScale += fElapsedTime;
				if(tmpScale > endScale)
					tmpScale = endScale;
			}
			_m_vparticles[i]->SetScale(tmpScale);

			// Update Pos
			D3DXVECTOR3 tmpPos = _m_vparticles[i]->GetPos();
			D3DXVECTOR3 tmpVel = _m_vparticles[i]->GetVel();
			D3DXVECTOR3 tmpDir = _m_vparticles[i]->GetDir();
			tmpPos += tmpVel + tmpDir;
			_m_vparticles[i]->SetPos(tmpPos);
		}
	}
}

void Emitter::Render() 
{
	for( unsigned int i = 0; i < _m_vparticles.size(); ++i)
	{
		_m_vparticles[i]->Render();
	}
}

Emitter::Emitter( float newSpawnRate, bool newLooping, RECT newRect,int newMaxParticles, 
			D3DXVECTOR3 newStartVec, D3DXVECTOR3 newEndVec, float newStartScale, 
			 float newEndScale, int newBlendMode, int newImageID, float newParticleLifeSpan,
			 float newEmitterLifeTime, int newStartColor, int newEndColor, float newSpawnTimer)
{
	spawnRate = newSpawnRate;
	loopin = newLooping;
	rect = newRect;
	maxParticles = newMaxParticles;
	endVel = newEndVec;
	endScale = newEndScale;
	endColor = newEndColor;
	startVel = newStartVec;
	startScale = newStartScale;
	startColor = newStartColor;
	blendMode = newBlendMode;
	spawnTimer = newSpawnTimer;
	imageID = newImageID;
	lifeSpan = newParticleLifeSpan;
	lifeTime = newEmitterLifeTime;
	age = 0;
}