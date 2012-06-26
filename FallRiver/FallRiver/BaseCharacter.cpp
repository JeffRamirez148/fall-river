#include "BaseCharacter.h"
#include "Enemy.h"

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
}

void BaseCharacter::Render()
{

}

bool BaseCharacter::CheckCollision(IObjects* pBase)
{
	if(BaseObject::CheckCollision(pBase) == true )
	{
		return true;
	}
	return false;
}

RECT BaseCharacter::GetRect()
{
	RECT cRect = {long(GetPosX()), long(GetPosY()), long(GetPosX()+GetWidth()), long(GetPosY()+GetHeight())};

	return cRect;
}