#include "BaseCharacter.h"
#include "Enemy.h"
#include "GamePlayState.h"
#include "Particle_Manager.h"
#include "Emitter.h"
#include "ViewManager.h"
#include "EventSystem.h"
#include "Bullet.h"

BaseCharacter::BaseCharacter()
{
	m_nObjectType = OBJ_CHARACTER;
	died = false;
	goreTime = 0.0f;
	bleeding = false;
	blood.curAnimID = ViewManager::GetInstance()->RegisterAnimation("resource/graphics/SQUIRT1.xml");
	blood.fTime = 0;
	blood.curAnimation = 0;
	blood.curFrame = 0;
	bloodAngle = 0;
	gore = false;
	pushX = 0;
	pushY = 0;
}

BaseCharacter::~BaseCharacter()
{

}

void BaseCharacter::Update(float fElapsedTime)
{
	// Modify the token's position by its velocity
	m_nPosX += (m_nVelX * fElapsedTime) + (pushX * fElapsedTime);
	m_nPosY += (m_nVelY * fElapsedTime) + (pushY * fElapsedTime);
	goreTime += fElapsedTime;

	//for(unsigned int i = 0; i < bloodA.size(); ++i)
	//{
	//	Particle_Manager::GetInstance()->GetActiveEmitter( bloodA[i] )->loopin = !Particle_Manager::GetInstance()->GetActiveEmitter( bloodA[i] )->loopin;
	//}

	if(m_nHealth <= 0 && this->GetCharacterType() == CHA_PLAYER && !died )
	{
		GamePlayState* tmp = GamePlayState::GetInstance();
		Particle_Manager* m_pPM = Particle_Manager::GetInstance();
		RECT tmpRect = {long(m_nPosX - 5), long(m_nPosY - 5), long(m_nPosX + 5), long(m_nPosY + 5) };
		int goreA1 = m_pPM->ActivateEmitter(tmp->GetGoreL1());
		m_pPM->GetActiveEmitter(goreA1)->SetRect(tmpRect);
		int goreA2 = m_pPM->ActivateEmitter(tmp->GetGoreL2());
		m_pPM->GetActiveEmitter(goreA2)->SetRect(tmpRect);
		int goreA3 = m_pPM->ActivateEmitter(tmp->GetGoreL3());
		m_pPM->GetActiveEmitter(goreA3)->SetRect(tmpRect);
		int goreA4 = m_pPM->ActivateEmitter(tmp->GetGoreL4());
		m_pPM->GetActiveEmitter(goreA4)->SetRect(tmpRect);
		int goreA5 = m_pPM->ActivateEmitter(tmp->GetGoreL5());
		m_pPM->GetActiveEmitter(goreA5)->SetRect(tmpRect);
		int goreA6 = m_pPM->ActivateEmitter(tmp->GetGoreL6());
		m_pPM->GetActiveEmitter(goreA6)->SetRect(tmpRect);
		int goreA7 = m_pPM->ActivateEmitter(tmp->GetGoreL7());
		m_pPM->GetActiveEmitter(goreA7)->SetRect(tmpRect);
		int goreA8 = m_pPM->ActivateEmitter(tmp->GetGoreL8());
		m_pPM->GetActiveEmitter(goreA8)->SetRect(tmpRect);
		died = true;
	}

	//Updating the player's frame and timer for animations
	if(bleeding)
	{
		Animation* thisAnim = ViewManager::GetInstance()->GetAnimation(blood.curAnimID);
		blood.fTime += fElapsedTime;

		if(blood.fTime >= thisAnim->frames[blood.curAnimation][blood.curFrame].duration)
		{
			blood.fTime -= thisAnim->frames[blood.curAnimation][blood.curFrame].duration;
			blood.curFrame++;
			if(blood.curFrame < (int)thisAnim->frames[blood.curAnimation].size())
			{
				if(strcmp(thisAnim->frames[blood.curAnimation][blood.curFrame].eventMsg,"none") != 0)
					EventSystem::GetInstance()->SendEvent(thisAnim->frames[blood.curAnimation][blood.curFrame].eventMsg, this);
			}
			if((blood.curFrame == thisAnim->frames[blood.curAnimation].size()) && thisAnim->looping[blood.curAnimation])
			{
				this->SetBleeding(false);
				blood.curFrame = 0;
			}
			else if(blood.curFrame == thisAnim->frames[blood.curAnimation].size() && !thisAnim->looping[blood.curAnimation])
			{
				blood.curFrame--;
				this->SetBleeding(false);
			}
		}
	}
	else
		blood.curFrame = 0;
}

void BaseCharacter::Render()
{
	if(bleeding)
	{ 
		float centerX, centerY, posX, posY;
		centerX = (GetRect2().right - GetRect2().left) * .5f;
		centerY = (GetRect2().bottom - GetRect2().top) * .5f;
		D3DCOLOR color = 0x6affffff;
		if(bloodAngle == 0) // Left, Up
		{
			posX = (GetPosX() - GamePlayState::GetInstance()->GetCamera().x);
			posY = (GetPosY() - GamePlayState::GetInstance()->GetCamera().y);
		}
		else if(bloodAngle == 0.785398f) // Up
		{
			posX = (GetPosX() - GamePlayState::GetInstance()->GetCamera().x) + GetWidth() * 2 - 25;
			posY = (GetPosY() - GamePlayState::GetInstance()->GetCamera().y) - 30;
		}
		else if(bloodAngle == 1.570796f) // Right, Up
		{
			posX = (GetPosX() - GamePlayState::GetInstance()->GetCamera().x) + GetWidth() * 2 + 25;
			posY = (GetPosY() - GamePlayState::GetInstance()->GetCamera().y) - 30;
		}
		else if(bloodAngle == 0.785398f + 1.570796f) // Right
		{
			posX = (GetPosX() - GamePlayState::GetInstance()->GetCamera().x) + GetWidth() * 2 + 35;
			posY = (GetPosY() - GamePlayState::GetInstance()->GetCamera().y);
		}
		else if(bloodAngle == 3.14159f) // Right, Down
		{
			posX = (GetPosX() - GamePlayState::GetInstance()->GetCamera().x) + GetWidth() * 2 + 40;
			posY = (GetPosY() - GamePlayState::GetInstance()->GetCamera().y) + GetHeight()  * 2 - 10;
		}
		else if(bloodAngle == 3.14159f + 0.785398f) // Down
		{
			posX = (GetPosX() - GamePlayState::GetInstance()->GetCamera().x) + GetWidth() * 2 + 10;
			posY = (GetPosY() - GamePlayState::GetInstance()->GetCamera().y) + GetHeight()  * 2 + 10;
		}
		else if(bloodAngle == 3.14159f + 1.570796f) // Left, Down
		{
			posX = (GetPosX() - GamePlayState::GetInstance()->GetCamera().x) + GetWidth() * .5f + 10;
			posY = (GetPosY() - GamePlayState::GetInstance()->GetCamera().y) + GetHeight()  * 2 - 10;
		}
		else if(bloodAngle == -1.570796f + 0.785398f) // Left
		{
			posX = (GetPosX() - GamePlayState::GetInstance()->GetCamera().x);
			posY = (GetPosY() - GamePlayState::GetInstance()->GetCamera().y) + GetHeight();
		}
		//RECT tmpRECT = { , , , };

		//ViewManager::GetInstance()->DrawRect(tmpRECT, 255, 255, 255, 255);		
		if(gore)
		{
			ViewManager::GetInstance()->DrawAnimation(&blood, (GetPosX() - GamePlayState::GetInstance()->GetCamera().x),  (GetPosY() - GamePlayState::GetInstance()->GetCamera().y) + GetHeight(), 1.0f, 1.0f, centerX,centerY,										-1.570796f + 0.785398f, color);
			ViewManager::GetInstance()->DrawAnimation(&blood, (GetPosX() - GamePlayState::GetInstance()->GetCamera().x) + GetWidth() * .5f + 10,  (GetPosY() - GamePlayState::GetInstance()->GetCamera().y) + GetHeight()  * 2 - 10, 1.0f, 1.0f, centerX,centerY,	3.14159f + 1.570796f, color);
			ViewManager::GetInstance()->DrawAnimation(&blood, (GetPosX() - GamePlayState::GetInstance()->GetCamera().x) + GetWidth() * 2 + 10,  (GetPosY() - GamePlayState::GetInstance()->GetCamera().y) + GetHeight()  * 2 + 10, 1.0f, 1.0f, centerX,centerY,		3.14159f + 0.785398f, color);
			ViewManager::GetInstance()->DrawAnimation(&blood, (GetPosX() - GamePlayState::GetInstance()->GetCamera().x) + GetWidth() * 2 + 40,  (GetPosY() - GamePlayState::GetInstance()->GetCamera().y) + GetHeight()  * 2 - 10, 1.0f, 1.0f, centerX,centerY,		3.14159f, color);
			ViewManager::GetInstance()->DrawAnimation(&blood, (GetPosX() - GamePlayState::GetInstance()->GetCamera().x) + GetWidth() * 2 + 35,  (GetPosY() - GamePlayState::GetInstance()->GetCamera().y), 1.0f, 1.0f, centerX,centerY,								0.785398f + 1.570796f, color);
			ViewManager::GetInstance()->DrawAnimation(&blood, (GetPosX() - GamePlayState::GetInstance()->GetCamera().x) + GetWidth() * 2 + 25,  (GetPosY() - GamePlayState::GetInstance()->GetCamera().y) - 30, 1.0f, 1.0f, centerX,centerY,						1.570796f, color);
			ViewManager::GetInstance()->DrawAnimation(&blood, (GetPosX() - GamePlayState::GetInstance()->GetCamera().x) + GetWidth() * 2 - 25,  (GetPosY() - GamePlayState::GetInstance()->GetCamera().y) - 30, 1.0f, 1.0f, centerX,centerY,						0.785398f, color);
			ViewManager::GetInstance()->DrawAnimation(&blood, (GetPosX() - GamePlayState::GetInstance()->GetCamera().x),  (GetPosY() - GamePlayState::GetInstance()->GetCamera().y), 1.0f, 1.0f, centerX,centerY,													0, color);
		}
		else
			ViewManager::GetInstance()->DrawAnimation(&blood, posX,  posY, 1.0f, 1.0f, centerX,centerY, bloodAngle, color);
	}
}

bool BaseCharacter::CheckCollision(IObjects* pBase)
{
	if( BaseObject::CheckCollision(pBase)  == true )
	{
		if(pBase->GetObjectType() == OBJ_BULLET )
		{
			Bullet* tmpBullet = (Bullet*)(pBase);
			if(tmpBullet->GetOwner()->GetOwner() == this)
				return false;
			GamePlayState* tmp = GamePlayState::GetInstance();
			Particle_Manager* m_pPM = Particle_Manager::GetInstance();
			D3DXVECTOR3 tmpVel;
			tmpVel.x = tmpBullet->GetSpeedX();
			tmpVel.y = tmpBullet->GetSpeedY();
			tmpVel.z = 0;
			int bloodA1;
			int bloodA2;
			int bloodA3;

			RECT tmpRect1 = GetRect2();//tmpBullet->GetRect();
			//RECT tmpRect1 = {LONG(m_nPosX - 5), LONG(m_nPosY - 5), LONG(m_nPosX + 5), LONG(m_nPosY + 5) };


			if( tmpVel.x > 0 && tmpVel.y > 0)
			{
				bloodA1 = m_pPM->ActivateEmitter(tmp->GetBloodL1());
				bloodA2 = m_pPM->ActivateEmitter(tmp->GetBloodL7());
				bloodA3 = m_pPM->ActivateEmitter(tmp->GetBloodL3());
				bloodAngle = 3.14159f;
				//tmpRect1.left += (this->GetRect2().right - this->GetRect2().left);
				//tmpRect1.right += (this->GetRect2().right - this->GetRect2().left);
				//tmpRect1.top += (this->GetRect2().bottom - this->GetRect2().top);
				//tmpRect1.bottom += (this->GetRect2().bottom - this->GetRect2().top);
			}
			else if( tmpVel.x > 0 && tmpVel.y < 0)
			{
				bloodA1 = m_pPM->ActivateEmitter(tmp->GetBloodL2());
				bloodA2 = m_pPM->ActivateEmitter(tmp->GetBloodL8());
				bloodA3 = m_pPM->ActivateEmitter(tmp->GetBloodL3());
				bloodAngle = 1.570796f;
				//tmpRect1.left += (this->GetRect2().right - this->GetRect2().left);
				//tmpRect1.right += (this->GetRect2().right - this->GetRect2().left);
				//tmpRect1.top -= (this->GetRect2().bottom - this->GetRect2().top);
				//tmpRect1.bottom -= (this->GetRect2().bottom - this->GetRect2().top);
			}
			else if(tmpVel.x > 0 && tmpVel.y == 0)
			{
				bloodA1 = m_pPM->ActivateEmitter(tmp->GetBloodL3());
				bloodA2 = m_pPM->ActivateEmitter(tmp->GetBloodL2());
				bloodA3 = m_pPM->ActivateEmitter(tmp->GetBloodL1());
				bloodAngle = 1.570796f + 0.785398f;
				//tmpRect1.left += (this->GetRect2().right - this->GetRect2().left);
				//tmpRect1.right += (this->GetRect2().right - this->GetRect2().left);
			}
			else if(tmpVel.x < 0 && tmpVel.y == 0)
			{
				bloodA1 = m_pPM->ActivateEmitter(tmp->GetBloodL4());
				bloodA2 = m_pPM->ActivateEmitter(tmp->GetBloodL5());
				bloodA3 = m_pPM->ActivateEmitter(tmp->GetBloodL6());
				bloodAngle = -1.570796f + 0.785398f;
				//tmpRect1.left -= (this->GetRect2().right - this->GetRect2().left);
				//tmpRect1.right -= (this->GetRect2().right - this->GetRect2().left);
			}
			else if(tmpVel.x < 0 && tmpVel.y < 0)
			{
				bloodA1 = m_pPM->ActivateEmitter(tmp->GetBloodL5());
				bloodA2 = m_pPM->ActivateEmitter(tmp->GetBloodL4());
				bloodA3 = m_pPM->ActivateEmitter(tmp->GetBloodL8());
				bloodAngle = 0;
				//tmpRect1.left -= (this->GetRect2().right - this->GetRect2().left);
				//tmpRect1.right -= (this->GetRect2().right - this->GetRect2().left);
				//tmpRect1.top -= (this->GetRect2().bottom - this->GetRect2().top);
				//tmpRect1.bottom -= (this->GetRect2().bottom - this->GetRect2().top);
			}
			else if(tmpVel.x < 0 && tmpVel.y > 0)
			{
				bloodA1 = m_pPM->ActivateEmitter(tmp->GetBloodL6());
				bloodA2 = m_pPM->ActivateEmitter(tmp->GetBloodL4());
				bloodA3 = m_pPM->ActivateEmitter(tmp->GetBloodL7());
				bloodAngle = 3.14159f + 1.570796f;
				//tmpRect1.left -= (this->GetRect2().right - this->GetRect2().left);
				//tmpRect1.right -= (this->GetRect2().right - this->GetRect2().left);
				//tmpRect1.top += (this->GetRect2().bottom - this->GetRect2().top);
				//tmpRect1.bottom += (this->GetRect2().bottom - this->GetRect2().top);
			}
			else if(tmpVel.x == 0 && tmpVel.y > 0)
			{
				bloodA1 = m_pPM->ActivateEmitter(tmp->GetBloodL7());
				bloodA2 = m_pPM->ActivateEmitter(tmp->GetBloodL6());
				bloodA3 = m_pPM->ActivateEmitter(tmp->GetBloodL1());
				bloodAngle = 3.14159f + 0.785398f;

				//tmpRect1.top += (this->GetRect2().bottom - this->GetRect2().top);
				//tmpRect1.bottom += (this->GetRect2().bottom - this->GetRect2().top);
			}
			else if(tmpVel.x == 0 && tmpVel.y < 0)
			{
				bloodA1 = m_pPM->ActivateEmitter(tmp->GetBloodL8());
				bloodA2 = m_pPM->ActivateEmitter(tmp->GetBloodL5());
				bloodA3 = m_pPM->ActivateEmitter(tmp->GetBloodL2());
				bloodAngle = 0.785398f;
				//tmpRect1.top -= (this->GetRect2().bottom - this->GetRect2().top);
				//tmpRect1.bottom -= (this->GetRect2().bottom - this->GetRect2().top);
			}
			m_pPM->GetActiveEmitter(bloodA1)->SetRect(tmpRect1);
			m_pPM->GetActiveEmitter(bloodA2)->SetRect(tmpRect1);
			m_pPM->GetActiveEmitter(bloodA3)->SetRect(tmpRect1);

			if(rand()% 3 == 0)
				bloodA.push_back(bloodA1);
			if(rand()% 3 == 0)
				bloodA.push_back(bloodA2);
			if(rand()% 3 == 0)
				bloodA.push_back(bloodA3);
		}
		else if( pBase->GetObjectType() == OBJ_CHARACTER)
		{
			BaseCharacter* tmp = (BaseCharacter*)(pBase);
			if( tmp->GetCharacterType() == CHA_ENEMY && this->GetCharacterType() != CHA_ENEMY && goreTime >= 1)
			{
				GamePlayState* tmp = GamePlayState::GetInstance();
				Particle_Manager* m_pPM = Particle_Manager::GetInstance();
				RECT tmpRect = GetRect2();//{LONG(m_nPosX - 5), LONG(m_nPosY - 5), LONG(m_nPosX + 5), LONG(m_nPosY + 5) };
				int goreA1 = m_pPM->ActivateEmitter(tmp->GetGoreL1());
				m_pPM->GetActiveEmitter(goreA1)->SetRect(tmpRect);
				int goreA2 = m_pPM->ActivateEmitter(tmp->GetGoreL2());
				m_pPM->GetActiveEmitter(goreA2)->SetRect(tmpRect);
				int goreA3 = m_pPM->ActivateEmitter(tmp->GetGoreL3());
				m_pPM->GetActiveEmitter(goreA3)->SetRect(tmpRect);
				int goreA4 = m_pPM->ActivateEmitter(tmp->GetGoreL4());
				m_pPM->GetActiveEmitter(goreA4)->SetRect(tmpRect);
				int goreA5 = m_pPM->ActivateEmitter(tmp->GetGoreL5());
				m_pPM->GetActiveEmitter(goreA5)->SetRect(tmpRect);
				int goreA6 = m_pPM->ActivateEmitter(tmp->GetGoreL6());
				m_pPM->GetActiveEmitter(goreA6)->SetRect(tmpRect);
				int goreA7 = m_pPM->ActivateEmitter(tmp->GetGoreL7());
				m_pPM->GetActiveEmitter(goreA7)->SetRect(tmpRect);
				int goreA8 = m_pPM->ActivateEmitter(tmp->GetGoreL8());
				m_pPM->GetActiveEmitter(goreA8)->SetRect(tmpRect);
				goreTime = 0;
				bleeding = true;
				bloodAngle = 0;
				gore = true;
			}
		}
		return true;
	}
	return false;
}

RECT BaseCharacter::GetRect()
{
	RECT cRect = {long(GetPosX()), long(GetPosY()), long(GetPosX()+GetWidth()), long(GetPosY()+GetHeight())};
	//Animation* thisAnim = ViewManager::GetInstance()->GetAnimation(m_playerAnim.curAnimID);
	//Frame thisFrame = thisAnim->frames[m_playerAnim.curAnimation][m_playerAnim.curFrame];
	//RECT cRect = {long(GetPosX()+ thisFrame.colRect.left), long(GetPosY() + thisFrame.colRect.top), long(GetPosX()+GetWidth()), long(GetPosY()+GetHeight())};
	return cRect;
	
	//return thisFrame.colRect;
}

RECT BaseCharacter::GetRect2()
{
	Animation* thisAnim = ViewManager::GetInstance()->GetAnimation(m_playerAnim.curAnimID);
	Frame thisFrame = thisAnim->frames[m_playerAnim.curAnimation][m_playerAnim.curFrame];
	RECT cRect = {long(GetPosX()+ thisFrame.colRect.left), long(GetPosY() + thisFrame.colRect.top), long(GetPosX()+GetWidth()), long(GetPosY()+GetHeight())};
	return cRect;
}