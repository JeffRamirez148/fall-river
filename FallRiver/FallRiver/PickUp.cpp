#include "PickUp.h"
#include "DestroyPickUp.h"
#include "DirectInput.h"

PickUp::PickUp()
{
	m_nObjectType = OBJ_PICKUP;
}

PickUp::~PickUp()
{

}

void PickUp::Update(float fElapsedTime)
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
}

void PickUp::Render() 
{
}

RECT PickUp::GetRect()
{
	RECT cRect = {GetPosX(), GetPosY(), GetPosX()+GetWidth(), GetPosY()+GetHeight() };
	return cRect;
}

bool PickUp::CheckCollision(BaseObject* pBase)
{
	RECT cRect;
	if( IntersectRect( &cRect, &GetRect(), &pBase->GetRect() ) == false  )
		return false;
	return true;
}
