#include "Bush.h"

Bush::Bush()
{
	m_nObjectType = OBJ_BUSH;
}

void Bush::Update(float fElapsedTime)
{
}

void Bush::Render() 
{
}

RECT Bush::GetRect()
{
	RECT cRect = {GetPosX(), GetPosY(), GetPosX()+GetWidth(), GetPosY()+GetHeight() };
	return cRect;
}

bool Bush::CheckCollision(BaseObject* pBase)
{
	RECT cRect;
	if( IntersectRect( &cRect, &GetRect(), &pBase->GetRect() ) == false  )
		return false;
	return true;
}