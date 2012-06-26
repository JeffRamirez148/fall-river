#include "Bullet.h"
#include "DestroyBullet.h"
#include "EventSystem.h"
#include "MessageSystem.h"
#include "DirectInput.h"
#include "ViewManager.h"
#include "BaseCharacter.h"
#include "CGame.h"
#include "GamePlayState.h"
#include "Particle_Manager.h"
#include "Emitter.h"

Bullet::Bullet()
{
	m_nObjectType = OBJ_BULLET;
}

Bullet::~Bullet()
{
}

void Bullet::Update(float fElapsedTime) 
{

	DirectInput* pDI = DirectInput::GetInstance();

	m_nPosX += m_fSpeedX * fElapsedTime;
	m_nPosY += m_fSpeedY* fElapsedTime;
}

void Bullet::Render() 
{
	ViewManager* pVM = ViewManager::GetInstance();

	RECT reRect = {long(GetPosX() - GamePlayState::GetInstance()->GetCamera().x), long(GetPosY() - GamePlayState::GetInstance()->GetCamera().y), long(reRect.left+GetWidth()), long(reRect.top + GetHeight())};

	pVM->DrawRect(reRect, 255, 0, 255);
}

void Bullet::HandleEvent(Event* pEvent) 
{
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
		DestroyBullet* pMsg = new DestroyBullet(this);
		MessageSystem::GetInstance()->SendMsg(pMsg);
		pMsg = nullptr;

		EventSystem::GetInstance()->SendUniqueEvent( "target_hit", pBase );
	}
	return true;
}
