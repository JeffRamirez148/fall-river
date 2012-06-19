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
		/*if(pBase->GetObjectType() == CHA_ENEMY)
		{
			if(pBase->GetRect().right - GetRect().left <= 5 && GetRect().left < pBase->GetRect().right+2)
				SetPosX(pBase->GetRect().right);
			else if(GetRect().right - pBase->GetRect().left <= 5 && GetRect().right > pBase->GetRect().left-2)
				SetPosX(pBase->GetRect().left-GetWidth());

			if(pBase->GetRect().bottom - GetRect().top <= 5 && GetRect().top < pBase->GetRect().bottom+2)
				SetPosY(pBase->GetRect().bottom);
			else if(GetRect().bottom - pBase->GetRect().top <= 5 && GetRect().bottom > pBase->GetRect().top-2)
				SetPosY(pBase->GetRect().top-GetHeight());
		}*/
		return true;
	}
	return false;
}

RECT BaseCharacter::GetRect()
{
	RECT cRect = {long(GetPosX()), long(GetPosY()), long(GetPosX()+GetWidth()), long(GetPosY()+GetHeight())};

	return cRect;
}