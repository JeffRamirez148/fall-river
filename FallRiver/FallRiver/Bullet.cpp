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
		SetPosX(GetPosX()+30*(int)fElapsedTime);
	else if(pDI->KeyDown(DIK_LEFT) )
		SetPosX(GetPosX()-30*(int)fElapsedTime);
	
	if(pDI->KeyDown(DIK_UP) )
		SetPosX(GetPosY()+30*(int)fElapsedTime);
	else if(pDI->KeyDown(DIK_DOWN) )
		SetPosY(GetPosY()-30*(int)fElapsedTime);

	SetPosX(GetPosX()+int(m_nSpeedX * fElapsedTime) );
	SetPosY(GetPosY()+int(m_nSpeedY * fElapsedTime) );
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
