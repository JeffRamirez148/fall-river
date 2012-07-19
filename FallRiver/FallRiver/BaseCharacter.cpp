#include "BaseCharacter.h"
#include "Enemy.h"
#include "GamePlayState.h"
#include "Particle_Manager.h"
#include "Emitter.h"
#include "ViewManager.h"
#include "Bullet.h"

BaseCharacter::BaseCharacter()
{
	m_nObjectType = OBJ_CHARACTER;
	died = false;
	goreTime = 0.0f;
}

BaseCharacter::~BaseCharacter()
{

}

void BaseCharacter::Update(float fElapsedTime)
{
	// Modify the token's position by its velocity
	m_nPosX += m_nVelX * fElapsedTime;
	m_nPosY += m_nVelY * fElapsedTime;
	goreTime += fElapsedTime;

	//for(unsigned int i = 0; i < bloodA.size(); ++i)
	//{
	//	Particle_Manager::GetInstance()->GetActiveEmitter( bloodA[i] )->loopin = !Particle_Manager::GetInstance()->GetActiveEmitter( bloodA[i] )->loopin;
	//}

	if(m_nHealth <= 0 && this->GetCharacterType() == CHA_PLAYER && !died )
	{
		GamePlayState* tmp = GamePlayState::GetInstance();
		Particle_Manager* m_pPM = Particle_Manager::GetInstance();
		RECT tmpRect = {LONG(m_nPosX - 5), LONG(m_nPosY - 5), LONG(m_nPosX + 5), LONG(m_nPosY + 5) };
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
}

void BaseCharacter::Render()
{

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

			RECT tmpRect1 = tmpBullet->GetRect();
			//RECT tmpRect1 = {LONG(m_nPosX - 5), LONG(m_nPosY - 5), LONG(m_nPosX + 5), LONG(m_nPosY + 5) };


			if( tmpVel.x > 0 && tmpVel.y > 0)
			{
				bloodA1 = m_pPM->ActivateEmitter(tmp->GetBloodL1());
				bloodA2 = m_pPM->ActivateEmitter(tmp->GetBloodL7());
				bloodA3 = m_pPM->ActivateEmitter(tmp->GetBloodL3());
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
				//tmpRect1.left += (this->GetRect2().right - this->GetRect2().left);
				//tmpRect1.right += (this->GetRect2().right - this->GetRect2().left);
			}
			else if(tmpVel.x < 0 && tmpVel.y == 0)
			{
				bloodA1 = m_pPM->ActivateEmitter(tmp->GetBloodL4());
				bloodA2 = m_pPM->ActivateEmitter(tmp->GetBloodL5());
				bloodA3 = m_pPM->ActivateEmitter(tmp->GetBloodL6());
				//tmpRect1.left -= (this->GetRect2().right - this->GetRect2().left);
				//tmpRect1.right -= (this->GetRect2().right - this->GetRect2().left);
			}
			else if(tmpVel.x < 0 && tmpVel.y < 0)
			{
				bloodA1 = m_pPM->ActivateEmitter(tmp->GetBloodL5());
				bloodA2 = m_pPM->ActivateEmitter(tmp->GetBloodL4());
				bloodA3 = m_pPM->ActivateEmitter(tmp->GetBloodL8());
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
				//tmpRect1.top += (this->GetRect2().bottom - this->GetRect2().top);
				//tmpRect1.bottom += (this->GetRect2().bottom - this->GetRect2().top);
			}
			else if(tmpVel.x == 0 && tmpVel.y < 0)
			{
				bloodA1 = m_pPM->ActivateEmitter(tmp->GetBloodL8());
				bloodA2 = m_pPM->ActivateEmitter(tmp->GetBloodL5());
				bloodA3 = m_pPM->ActivateEmitter(tmp->GetBloodL2());
				//tmpRect1.top -= (this->GetRect2().bottom - this->GetRect2().top);
				//tmpRect1.bottom -= (this->GetRect2().bottom - this->GetRect2().top);
			}
			m_pPM->GetActiveEmitter(bloodA1)->SetRect(tmpRect1);
			m_pPM->GetActiveEmitter(bloodA2)->SetRect(tmpRect1);
			m_pPM->GetActiveEmitter(bloodA3)->SetRect(tmpRect1);
			bloodA.push_back(bloodA1);
			bloodA.push_back(bloodA2);
			bloodA.push_back(bloodA3);
		}
		else if( pBase->GetObjectType() == OBJ_CHARACTER)
		{
			BaseCharacter* tmp = (BaseCharacter*)(pBase);
			if( tmp->GetCharacterType() == CHA_ENEMY && this->GetCharacterType() != CHA_ENEMY && goreTime >= 1)
			{
				GamePlayState* tmp = GamePlayState::GetInstance();
				Particle_Manager* m_pPM = Particle_Manager::GetInstance();
				RECT tmpRect = {LONG(m_nPosX - 5), LONG(m_nPosY - 5), LONG(m_nPosX + 5), LONG(m_nPosY + 5) };
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
			}
		}
		return true;
	}
	return false;
}

RECT BaseCharacter::GetRect()
{
	RECT cRect = {long(GetPosX()), long(GetPosY()), long(GetPosX()+GetWidth()), long(GetPosY()+GetHeight())};
	//Animation thisAnim = ViewManager::GetInstance()->GetAnimation(m_playerAnim.curAnimID);
	//Frame thisFrame = thisAnim.frames[m_playerAnim.curAnimation][m_playerAnim.curFrame];
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