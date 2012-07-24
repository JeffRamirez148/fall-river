#include "Bullet.h"
#include "DestroyBullet.h"
#include "EventSystem.h"
#include "MessageSystem.h"
#include "DirectInput.h"
#include "ViewManager.h"
#include "BaseCharacter.h"
#include "CGame.h"
#include "GamePlayState.h"
#include "Emitter.h"

Bullet::Bullet()
{
	m_nObjectType = OBJ_BULLET;
	m_fStartPosX = 0;
	m_fStartPosY = 0;
	m_nRotation = 0;
	SetVelX(0);
	SetVelY(0);
}

Bullet::~Bullet()
{
}

void Bullet::Update(float fElapsedTime) 
{
	float distx = m_fStartPosX - GetPosX();
	float disty = m_fStartPosY - GetPosY();

	if( distx < 0 )
		distx = -distx;
	if( disty < 0 )
		disty = -disty;

	float totdist = distx - disty;
	if(totdist < 0)
		totdist = -totdist;

	if( (distx > GetOwner()->GetRange() || disty > GetOwner()->GetRange()) && GetOwner()->GetWeaponType() != WPN_SHOTGUN )
	{
		DestroyBullet* pMsg = new DestroyBullet(this);
		MessageSystem::GetInstance()->SendMsg(pMsg);
		pMsg = nullptr;
	}
	else if( totdist > GetOwner()->GetRange() && GetOwner()->GetWeaponType() == WPN_SHOTGUN )
	{
		DestroyBullet* pMsg = new DestroyBullet(this);
		MessageSystem::GetInstance()->SendMsg(pMsg);
		pMsg = nullptr;
	}

	m_nPosX += m_fSpeedX * fElapsedTime;
	m_nPosY += m_fSpeedY* fElapsedTime;
}

void Bullet::Render() 
{
	ViewManager* pVM = ViewManager::GetInstance();

	/*if( GetSpeedX() > 0 && GetSpeedY() > 0 )
		pVM->DrawStaticTexture(this->GetImageID(), GetPosX() - GamePlayState::GetInstance()->GetCamera().x, GetPosY() - GamePlayState::GetInstance()->GetCamera().y, 1.0f, 1.0f, 0, 0, 0, 45);
	else if( GetSpeedX() > 0 && GetSpeedY() == 0 )
		pVM->DrawStaticTexture(this->GetImageID(), GetPosX() - GamePlayState::GetInstance()->GetCamera().x, GetPosY() - GamePlayState::GetInstance()->GetCamera().y);
	else if( GetSpeedX() > 0 && GetSpeedY() < 0 )
		pVM->DrawStaticTexture(this->GetImageID(), GetPosX() - GamePlayState::GetInstance()->GetCamera().x, GetPosY() - GamePlayState::GetInstance()->GetCamera().y, 1.0f, 1.0f, 0, 0, 0, -45);
	else if( GetSpeedX() == 0 && GetSpeedY() > 0 )
		pVM->DrawStaticTexture(this->GetImageID(), GetPosX() - GamePlayState::GetInstance()->GetCamera().x, GetPosY() - GamePlayState::GetInstance()->GetCamera().y, 1.0f, 1.0f, 0, 0, 0, 90);
	else if( GetSpeedX() == 0 && GetSpeedY() < 0 )
		pVM->DrawStaticTexture(this->GetImageID(), GetPosX() - GamePlayState::GetInstance()->GetCamera().x, GetPosY() - GamePlayState::GetInstance()->GetCamera().y, 1.0f, 1.0f, 0, 0, 0, -90);
	else if( GetSpeedX() < 0 && GetSpeedY() > 0 )
		pVM->DrawStaticTexture(this->GetImageID(), GetPosX() - GamePlayState::GetInstance()->GetCamera().x, GetPosY() - GamePlayState::GetInstance()->GetCamera().y, 1.0f, 1.0f, 0, 0, 0, 135);
	else if( GetSpeedX() < 0 && GetSpeedY() == 0 )
		pVM->DrawStaticTexture(this->GetImageID(), GetPosX() - GamePlayState::GetInstance()->GetCamera().x, GetPosY() - GamePlayState::GetInstance()->GetCamera().y, 1.0f, 1.0f, 0, 0, 0, 180);
	else if( GetSpeedX() < 0 && GetSpeedY() < 0 )
		pVM->DrawStaticTexture(this->GetImageID(), GetPosX() - GamePlayState::GetInstance()->GetCamera().x, GetPosY() - GamePlayState::GetInstance()->GetCamera().y, 1.0f, 1.0f, 0, 0, 0, -135);*/

	pVM->DrawStaticTexture(this->GetImageID(), GetPosX() - GamePlayState::GetInstance()->GetCamera().x, GetPosY() - GamePlayState::GetInstance()->GetCamera().y, 0.9f, 0.9f, 0, 0, 0, m_nRotation);
}

void Bullet::HandleEvent(Event* pEvent) 
{
	pEvent;
}

RECT Bullet::GetRect()
{
	RECT cRect = {long(GetPosX()), long(GetPosY()), long(GetPosX()+GetWidth()), long(GetPosY()+GetHeight()) };
	return cRect;
}

bool Bullet::CheckCollision(IObjects* pBase)
{
	RECT cRect;
	if( IntersectRect( &cRect, &GetRect(), &pBase->GetRect() ) == false  )
		return false;
	else if(pBase->GetObjectType() == OBJ_CHARACTER && GetOwner()->GetOwner() != pBase)
	{
		BaseCharacter* tmp = (BaseCharacter*)pBase;

		tmp->SetHealth(tmp->GetHealth()-GetOwner()->GetDamage());

		DestroyBullet* pMsg = new DestroyBullet(this);
		MessageSystem::GetInstance()->SendMsg(pMsg);
		pMsg = nullptr;
		
		EventSystem::GetInstance()->SendUniqueEvent( "target_hit", pBase );

	}
	return true;
}
