#include "Bullet.h"
#include "DestroyBullet.h"
#include "EventSystem.h"
#include "MessageSystem.h"
#include "DirectInput.h"
#include "ViewManager.h"
#include "BaseCharacter.h"
#include "CGame.h"
#include "GamePlayState.h"

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

	if(pDI->KeyDown(DIK_RIGHT) && GamePlayState::GetInstance()->CanMoveRight() )
		SetVelX(-100 + m_fSpeedX);
	else if(pDI->KeyDown(DIK_LEFT) && GamePlayState::GetInstance()->CanMoveLeft() )
		SetVelX(100 + m_fSpeedX);
	else
		SetVelX(m_fSpeedX);

	if(pDI->KeyDown(DIK_UP) && GamePlayState::GetInstance()->CanMoveUp() )
		SetVelY(100+m_fSpeedY);
	else if(pDI->KeyDown(DIK_DOWN) && GamePlayState::GetInstance()->CanMoveDown() )
		SetVelY(-100+m_fSpeedY);
	else
		SetVelY(m_fSpeedY);

	m_nPosX += m_nVelX * fElapsedTime;
	m_nPosY += m_nVelY * fElapsedTime;
}

void Bullet::Render() 
{
	ViewManager* pVM = ViewManager::GetInstance();

	pVM->DrawRect(GetRect(), 100, 40, 255);
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
