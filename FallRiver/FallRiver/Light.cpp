#include "Light.h"
#include "Player.h"

Light::Light()
{
	m_nObjectType = OBJ_LIGHT;
	m_pOwner = nullptr;
	m_fRadius = 0;
	m_fCone = 0;
	m_nColor = 0;
}

Light::~Light()
{

}

void Light::Update(float fElapsedTime) 
{
}

void Light::Render() 
{
}

RECT Light::GetRect()
{
	RECT cRect = {long(GetPosX()), long(GetPosY()), long(GetPosX()+GetWidth()), long(GetPosY()+GetHeight()) };
	return cRect;
}

bool Light::CheckCollision(BaseObject* pBase)
{
	RECT cRect;
	if( IntersectRect( &cRect, &GetRect(), &pBase->GetRect() ) == false  )
		return false;
	return true;
}

