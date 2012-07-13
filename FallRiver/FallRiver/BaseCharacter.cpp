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
}

BaseCharacter::~BaseCharacter()
{

}

void BaseCharacter::Update(float fElapsedTime)
{
	// Modify the token's position by its velocity
	m_nPosX += m_nVelX * fElapsedTime;
	m_nPosY += m_nVelY * fElapsedTime;

	if(m_nHealth <= 0 && this->GetCharacterType() != CHA_NPC && this->GetCharacterType() != CHA_COMPANION)
	{
		GamePlayState* tmp = GamePlayState::GetInstance();
		Particle_Manager* m_pPM = Particle_Manager::GetInstance();
		RECT tmpRect = {m_nPosX - 5, m_nPosY - 5, m_nPosX + 5, m_nPosY + 5 };
		goreA = m_pPM->ActivateEmitter(tmp->GetGoreL());
		m_pPM->GetActiveEmitter(goreA)->SetRect(tmpRect);
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

			if( tmpVel.x > 0 && tmpVel.y > 0)
			{
				bloodA1 = m_pPM->ActivateEmitter(tmp->GetBloodL1());
				bloodA2 = m_pPM->ActivateEmitter(tmp->GetBloodL7());
				bloodA3 = m_pPM->ActivateEmitter(tmp->GetBloodL3());
				tmpRect1.left += (this->GetRect().right - this->GetRect().left);
				tmpRect1.right += (this->GetRect().right - this->GetRect().left);
				tmpRect1.top += (this->GetRect().bottom - this->GetRect().top);
				tmpRect1.bottom += (this->GetRect().bottom - this->GetRect().top);
			}
			else if( tmpVel.x > 0 && tmpVel.y < 0)
			{
				bloodA1 = m_pPM->ActivateEmitter(tmp->GetBloodL2());
				bloodA2 = m_pPM->ActivateEmitter(tmp->GetBloodL8());
				bloodA3 = m_pPM->ActivateEmitter(tmp->GetBloodL3());
				tmpRect1.left += (this->GetRect().right - this->GetRect().left);
				tmpRect1.right += (this->GetRect().right - this->GetRect().left);
				tmpRect1.top -= (this->GetRect().bottom - this->GetRect().top);
				tmpRect1.bottom -= (this->GetRect().bottom - this->GetRect().top);
			}
			else if(tmpVel.x > 0 && tmpVel.y == 0)
			{
				bloodA1 = m_pPM->ActivateEmitter(tmp->GetBloodL3());
				bloodA2 = m_pPM->ActivateEmitter(tmp->GetBloodL2());
				bloodA3 = m_pPM->ActivateEmitter(tmp->GetBloodL1());
				tmpRect1.left += (this->GetRect().right - this->GetRect().left);
				tmpRect1.right += (this->GetRect().right - this->GetRect().left);
			}
			else if(tmpVel.x < 0 && tmpVel.y == 0)
			{
				bloodA1 = m_pPM->ActivateEmitter(tmp->GetBloodL4());
				bloodA2 = m_pPM->ActivateEmitter(tmp->GetBloodL5());
				bloodA3 = m_pPM->ActivateEmitter(tmp->GetBloodL6());
				tmpRect1.left -= (this->GetRect().right - this->GetRect().left);
				tmpRect1.right -= (this->GetRect().right - this->GetRect().left);
			}
			else if(tmpVel.x < 0 && tmpVel.y < 0)
			{
				bloodA1 = m_pPM->ActivateEmitter(tmp->GetBloodL5());
				bloodA2 = m_pPM->ActivateEmitter(tmp->GetBloodL4());
				bloodA3 = m_pPM->ActivateEmitter(tmp->GetBloodL8());
				tmpRect1.left -= (this->GetRect().right - this->GetRect().left);
				tmpRect1.right -= (this->GetRect().right - this->GetRect().left);
				tmpRect1.top -= (this->GetRect().bottom - this->GetRect().top);
				tmpRect1.bottom -= (this->GetRect().bottom - this->GetRect().top);
			}
			else if(tmpVel.x < 0 && tmpVel.y > 0)
			{
				bloodA1 = m_pPM->ActivateEmitter(tmp->GetBloodL6());
				bloodA2 = m_pPM->ActivateEmitter(tmp->GetBloodL4());
				bloodA3 = m_pPM->ActivateEmitter(tmp->GetBloodL7());
				tmpRect1.left -= (this->GetRect().right - this->GetRect().left);
				tmpRect1.right -= (this->GetRect().right - this->GetRect().left);
				tmpRect1.top += (this->GetRect().bottom - this->GetRect().top);
				tmpRect1.bottom += (this->GetRect().bottom - this->GetRect().top);
			}
			else if(tmpVel.x == 0 && tmpVel.y > 0)
			{
				bloodA1 = m_pPM->ActivateEmitter(tmp->GetBloodL7());
				bloodA2 = m_pPM->ActivateEmitter(tmp->GetBloodL6());
				bloodA3 = m_pPM->ActivateEmitter(tmp->GetBloodL1());
				tmpRect1.top += (this->GetRect().bottom - this->GetRect().top);
				tmpRect1.bottom += (this->GetRect().bottom - this->GetRect().top);
			}
			else if(tmpVel.x == 0 && tmpVel.y < 0)
			{
				bloodA1 = m_pPM->ActivateEmitter(tmp->GetBloodL8());
				bloodA2 = m_pPM->ActivateEmitter(tmp->GetBloodL5());
				bloodA3 = m_pPM->ActivateEmitter(tmp->GetBloodL2());
				tmpRect1.top -= (this->GetRect().bottom - this->GetRect().top);
				tmpRect1.bottom -= (this->GetRect().bottom - this->GetRect().top);
			}
			m_pPM->GetActiveEmitter(bloodA1)->SetRect(tmpRect1);
			m_pPM->GetActiveEmitter(bloodA2)->SetRect(tmpRect1);
			m_pPM->GetActiveEmitter(bloodA3)->SetRect(tmpRect1);
		}
		return true;
	}
	return false;
}

RECT BaseCharacter::GetRect()
{
	//RECT cRect = {long(GetPosX()), long(GetPosY()), long(GetPosX()+GetWidth()), long(GetPosY()+GetHeight())};
	Animation thisAnim = ViewManager::GetInstance()->GetAnimation(m_playerAnim.curAnimID);
	Frame thisFrame = thisAnim.frames[m_playerAnim.curAnimation][m_playerAnim.curFrame];
	RECT cRect = {long(GetPosX()+ thisFrame.colRect.left), long(GetPosY() + thisFrame.colRect.top), long(GetPosX()+GetWidth()), long(GetPosY()+GetHeight())};
	return cRect;
	
	//return thisFrame.colRect;
}