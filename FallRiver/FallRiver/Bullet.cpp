#include "Bullet.h"
#include "DestroyBullet.h"
#include "EventSystem.h"
#include "DirectInput.h"

Bullet::Bullet()
{
	m_nObjectType = OBJ_BULLET;

	EventSystem::GetInstance()->RegisterClient( "target_destroyed", this );
}

Bullet::~Bullet()
{
	EventSystem::GetInstance()->UnregisterClient( "target_destroyed", this );
}

void Bullet::Update(float fElapsedTime) 
{
	DirectInput* pDI = DirectInput::GetInstance();

	if(pDI->KeyDown(DIK_RIGHT) )
		SetVelX(-100);
	else if(pDI->KeyDown(DIK_LEFT) )
		SetVelX(100);
	else
		SetVelX(0);

	if(pDI->KeyDown(DIK_UP) )
		SetVelY(100);
	else if(pDI->KeyDown(DIK_DOWN) )
		SetVelY(-100);
	else
		SetVelY(0);

	m_nPosX += m_nVelX * fElapsedTime;
	m_nPosY += m_nVelY * fElapsedTime;
}

void Bullet::Render() 
{
}

void Bullet::HandleEvent(Event* pEvent) 
{
	if(pEvent->GetEventID() == "target_destroyed")
	{

	}
}

RECT Bullet::GetRect()
{
	RECT cRect = {GetPosX(), GetPosY(), GetPosX()+GetWidth(), GetPosY()+GetHeight() };
	return cRect;
}

bool Bullet::CheckCollision(BaseObject* pBase)
{
	RECT cRect;
	if( IntersectRect( &cRect, &GetRect(), &pBase->GetRect() ) == false  )
		return false;
	return true;
}
