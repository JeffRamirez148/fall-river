#include "Emitter.h"
#include "Particle_Manager.h"
#include "Particle.h"
#include "ViewManager.h"
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
		tmpParticle->SetModeS(blendModeS);
		tmpParticle->SetModeD(blendModeD);

		D3DXVECTOR3 tmpPos;
		tmpPos.x = float((rand() % int(rect.right - rect.left)) + rect.left);
		tmpPos.y = float((rand() % int(rect.bottom - rect.top)) + rect.top);
		tmpPos.z = 0.0f;
		tmpParticle->SetPos(tmpPos);
		tmpParticle->SetVel(startVel);
		D3DXVECTOR3 tmpDir;
		tmpDir.x = float(((rand() % 3) - 1) >> 1);
		tmpDir.y = float(((rand() % 3) - 1) >> 1);
		tmpDir.z = 0.0f;
		tmpParticle->SetDir(tmpDir);
		_m_vparticles.push_back(tmpParticle);
	}

	bool keepGoing;
	for( unsigned int i = 0; i < _m_vparticles.size(); ++i)
	{
		float t = _m_vparticles[i]->GetTime();
		t += fElapsedTime;
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
			// Update Alpha
			if(startColor >> 24 > endColor >> 24)
			{
				tmpA -= 1;
				if(tmpA < endA)
					tmpA = endA;
			}
			else
			{
				tmpA += 1;
				if(tmpA > endA)
					tmpA = endA;
			}
			// Update Red
			if((startColor << 8) >> 24 > (endColor << 8) >> 24)
			{
				tmpR -= 1;
				if(tmpR < endR)
					tmpR = endR;
			}
			else
			{
				tmpR += 1;
				if(tmpR > endR)
					tmpR = endR;
			}

			// Update Green
			if((startColor << 16) >> 24 > (endColor << 16) >> 24)
			{
				tmpG -= 1;
				if(tmpG < endG)
					tmpG = endG;
			}
			else
			{
				tmpG += 1;
				if(tmpG > endG)
					tmpG = endG;
			}

			// Update Blue
			if((startColor << 24) >> 24 > (endColor << 24) >> 24)
			{
				tmpB -= 1;
				if(tmpB < endB)
					tmpB = endB;
			}
			else
			{
				tmpB += 1;
				if(tmpB > endB)
					tmpB = endB;
			}
			
			tmpColor = (tmpA << 24) + (tmpR << 16) + (tmpG << 8) + tmpB;
			_m_vparticles[i]->SetColor(tmpColor);

			// Update Scale
			float tmpScaleX = _m_vparticles[i]->GetScaleX();
			float tmpScaleY = _m_vparticles[i]->GetScaleY();
			if(startScaleX > endScaleX)
			{
				tmpScaleX -= fElapsedTime;
				if(tmpScaleX < endScaleX)
					tmpScaleX = endScaleX;
			}
			else
			{
				tmpScaleX += fElapsedTime;
				if(tmpScaleX > endScaleX)
					tmpScaleX = endScaleX;
			}
			_m_vparticles[i]->SetScaleX(tmpScaleX);

			if(startScaleY > endScaleY)
			{
				tmpScaleX -= fElapsedTime;
				if(tmpScaleY < endScaleY)
					tmpScaleY = endScaleY;
			}
			else
			{
				tmpScaleY += fElapsedTime;
				if(tmpScaleY > endScaleY)
					tmpScaleY = endScaleY;
			}
			_m_vparticles[i]->SetScaleY(tmpScaleY);

			// Update Vel
			if(t > .0001f)
			{
			D3DXVECTOR3 tmpVel = _m_vparticles[i]->GetVel();
			if(startVel.x > endVel.x)
			{
				tmpVel.x -= fElapsedTime;
				if(tmpVel.x < endVel.x)
					tmpVel.x = endVel.x;
			}
			else
			{
				tmpVel.x += fElapsedTime;
				if(tmpVel.x > endVel.x)
					tmpVel.x = endVel.x;
			}

			if(startVel.y > endVel.y)
			{
				tmpVel.y -= fElapsedTime;
				if(tmpVel.y < endVel.y)
					tmpVel.y = endVel.y;
			}
			else
			{
				tmpVel.y += fElapsedTime;
				if(tmpVel.y > endVel.y)
					tmpVel.y = endVel.y;
			}

			if(startVel.z > endVel.z)
			{
				tmpVel.z -= fElapsedTime;
				if(tmpVel.z < endVel.z)
					tmpVel.z = endVel.z;
			}
			else
			{
				tmpVel.z += fElapsedTime;
				if(tmpVel.z > endVel.z)
					tmpVel.z = endVel.z;
			}
			_m_vparticles[i]->SetVel(tmpVel);
			// Update Pos

			D3DXVECTOR3 tmpPos = _m_vparticles[i]->GetPos();
			D3DXVECTOR3 tmpDir = _m_vparticles[i]->GetDir();
			tmpPos += tmpVel + tmpDir;
			_m_vparticles[i]->SetPos(tmpPos);
			t = 0;
			}

			float tmpRot = _m_vparticles[i]->GetRotation();
			// Update Rotation
			if(startRot > endRot)
			{
				tmpRot -= fElapsedTime;
				if(tmpRot < endRot)
					tmpRot = endRot;
			}
			else
			{
				tmpRot += fElapsedTime;
				if(tmpRot > endRot)
					tmpRot = endRot;
			}
		}
	}
}

void Emitter::Render() 
{
	ViewManager* view = ViewManager::GetInstance();
	view->DrawUnfilledRect( this->rect, 255, 255, 255 );
	for( unsigned int i = 0; i < _m_vparticles.size(); ++i)
	{
		_m_vparticles[i]->Render();
	}
}

Emitter::Emitter( float newSpawnRate, bool newLooping, RECT newRect,int newMaxParticles, 
			D3DXVECTOR3 newStartVec, D3DXVECTOR3 newEndVec, float newStartScaleX, float newStartScaleY,
			 float newEndScaleX, float newEndScaleY, int newBlendModeS, int newBlendModeD, int newImageID, float newParticleLifeSpan,
			 float newEmitterLifeTime, int newStartColor, int newEndColor,  float newStartRot, float newEndRot)
{
	spawnRate = newSpawnRate;
	loopin = newLooping;
	rect = newRect;
	maxParticles = newMaxParticles;
	endVel = newEndVec;
	endScaleX = newEndScaleX;
	endScaleY = newEndScaleY;

	endColor = newEndColor;
	startVel = newStartVec;
	startScaleX = newStartScaleX;
	startScaleY = newStartScaleY;

	startColor = newStartColor;
	blendModeS = newBlendModeS;
	blendModeD = newBlendModeD;

	imageID = newImageID;
	lifeSpan = newParticleLifeSpan;
	lifeTime = newEmitterLifeTime;
	age = 0;
	endRot = newEndRot;
	startRot = newStartRot;
	spawnTimer = 0.0f;
}