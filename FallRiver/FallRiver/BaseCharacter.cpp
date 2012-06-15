#include "BaseCharacter.h"

BaseCharacter::BaseCharacter()
{

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
	return BaseObject::CheckCollision(pBase);
}

RECT BaseCharacter::GetRect()
{
	RECT cRect = {GetPosX(), GetPosY(), GetPosX()+GetWidth(), GetPosY()+GetHeight()};

	return cRect;
}