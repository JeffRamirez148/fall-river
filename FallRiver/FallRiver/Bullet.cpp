#include "Bullet.h"
#include "DestroyBullet.h"
#include "BaseObject.h"
#include "Event.h"

Bullet::Bullet()
{
	m_nObjectType = OBJ_BULLET;
}

void Bullet::Update(float fElapsedTime) 
{
	SetPosX(int(m_nSpeedX * fElapsedTime) );
	SetPosY(int(m_nSpeedY * fElapsedTime) );

}

void Bullet::Render() 
{
}

void Bullet::HandleEvent(Event* pEvent) 
{
	
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
