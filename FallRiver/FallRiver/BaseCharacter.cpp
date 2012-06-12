#include "BaseCharacter.h"

BaseCharacter::BaseCharacter()
{

}

BaseCharacter::~BaseCharacter()
{

}

void BaseCharacter::AddRef()
{
	// Increase the reference counter
	++m_unRefCount;
}

void BaseCharacter::Release()
{
	--m_unRefCount;

	if( m_unRefCount == 0 )
		delete this;
}

void BaseCharacter::Update(float fElapsedTime)
{
	// Modify the token's position by its velocity
	SetPosX(int(m_nVelX * fElapsedTime));
	SetPosY(int(m_nVelY * fElapsedTime));
}

void BaseCharacter::Render()
{

}

bool BaseCharacter::CheckCollision(BaseObject* pBase)
{
	return true;
}

RECT BaseCharacter::GetRect()
{
	RECT cRect = {GetPosX(), GetPosY(), GetPosX()+GetWidth(), GetPosY()+GetHeight()};

	return cRect;
}